// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Message/Handler/TcpMessageHandler.h"
#include "Core/Log/Log.h"
#include "Core/Net/Socket/AddressInfo.h"
#include "Core/Net/Socket/ProtocolInfo.h"
#include "Core/Message/MessageFactory.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Message/Handler/MessageHandlerFactory.h"
#include "Core/Threading/Thread.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Profile/AutoStopWatch.h"
#include "Core/Coder/ICoder.h"





MEDUSA_BEGIN;

TcpMessageHandler::TcpMessageHandler(size_t id, StringRef hostName, ushort port, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey)
	:IMessageHandler(id,hostName,port,retryTimes,retryInternal,messageVersion,sendCoderType,receiveCoderType,encryptKey),mSendMessageStream(mInitialMessageBufferSize),mReceiveMessageStream(mInitialMessageBufferSize)
{
	Socket::AddressInfo addressInfo;
	Socket::ProtocolInfo protocolInfo;
	Socket::ISocket::ParseAddress(hostName,port,Socket::SocketType::TCP,addressInfo,protocolInfo);
	mSocket.SetAddress(addressInfo);
	mSocket.SetProtocol(protocolInfo);

}

TcpMessageHandler::~TcpMessageHandler()
{

}

Socket::ClientSocket& TcpMessageHandler::GetSocket()
{
	bool isSuccess=mSocket.Initialize();
	Log::Assert(isSuccess,"Failed to initialize socket");

	/*mSocket.SetSendTimeout(5000);
	mSocket.SetReceiveTimeout(5000);*/

	return mSocket;
}

void TcpMessageHandler::Process()
{
	RETURN_IF_EMPTY(mMessageQueue);
	AutoStopWatch totalAutoStopWatch(mTotalStopWatch);
	

	bool isSuccess=mSocket.Initialize();
    mConnectStopWatch.Start();
    
    int curRetryTimes=0;
	if(isSuccess)
	{
		int socketError=mSocket.Connect();
		if (socketError<0)
		{
			int retryTimes=mRetryTimes;
			while(socketError<0&&retryTimes>0)
			{
				mSocket.Close();
				isSuccess=mSocket.Initialize();

				Thread::Sleep(mRetryInternal);
				socketError=mSocket.Connect();
				--retryTimes;
                curRetryTimes++;
			}
		}

		mConnectStopWatch.Shot();

		if (socketError<0)
		{
			GiveUpAllMessages();
		}
		else
		{
			while(mMessageQueue.Count()>0)
			{
				IMessage* message=mMessageQueue.Head();
				mMessageQueue.Pop();
				SendMessage(message);
				message->SetSendElapsedMilliseconds(mSendStopWatch.ElapsedMilliseconds());
				message->SetReceiveElapsedMilliseconds(mReceiveStopWatch.ElapsedMilliseconds());

				SAFE_RELEASE(message);
			}
		}

		mSocket.Close();
		//mSocket.ShutDown(Socket::SocketPipeType::ReadWrite);
	}
	else
	{
		GiveUpAllMessages();
		mConnectStopWatch.Shot();
	}

#ifdef MEDUSA_DEBUG
	Log::FormatInfo("MessageConnect:{:f3} {}",mConnectStopWatch.ElapsedMilliseconds(),curRetryTimes);
#endif
}


void TcpMessageHandler::GiveUpAllMessages()
{
	while(mMessageQueue.Count()>0)
	{
		IMessage* message=mMessageQueue.Head();
		mMessageQueue.Pop();
		message->SetError(MessageError::ConnectFail);
		message->SetSocketError(errno);
		FailSocket(message);

		SAFE_RELEASE(message);
	}
}

IMessage* TcpMessageHandler::SendMessage( IMessage* message )
{
	Socket::SocketError::SocketError_t socketError;
	MemoryByteData buffer=message->SerializeRequest();

	mSendMessageStream.Rewind();
	StringRef messageName=message->Class().Name();
	uint32 messageNameSize=(uint)messageName.Length()+1;
	uint32 messageAllSize=(uint32)(messageNameSize+buffer.Size())+(uint32)(sizeof(uint32)*2);
	if (messageAllSize<4)
	{
		Log::AssertFailedFormat("Invalid messageAllSize:{} <4 and messageNameSize:{}",messageAllSize,messageNameSize);
		message->SetState(MessageState::ConnectFail);
		FireUIEventAsync(message->ReceiveHandler(),message);
		return message;
	}


	mSendMessageStream.Write(messageAllSize);
	mSendMessageStream.Write(mMessageVersion);
	mSendMessageStream.Write(messageNameSize);
	mSendMessageStream.WriteString(messageName,true);
	mSendMessageStream.WriteData(buffer);

	//encrypt
	MemoryByteData sendData=mSendMessageStream.ReadBeginToCurrent(DataReadingMode::DirectMove);
	sendData.ForceOffsetDataAndSize(sizeof(uint));
	MemoryByteData encryptedSendData=mSendCoder->Code(sendData);
	mSendMessageStream.Rewind();
	mSendMessageStream.Write(encryptedSendData.ByteSize());
	mSendMessageStream.WriteData(encryptedSendData);


	int timeout=(int)(message->Timeout()*1000);
	mSocket.SetSendTimeout(timeout);
	mSocket.SetReceiveTimeout(timeout);


	{
		AutoStopWatch autoSendStopWatch(mSendStopWatch);
		socketError=mSocket.Send(mSendMessageStream);
	}


	message->SetError(socketError);

	if (socketError==Socket::SocketError::Success)
	{
		Log::FormatInfo("Send:{}",message->Class().Name().c_str());
	}


	FireUIEventAsync(message->SendHandler(),message);

	if (socketError==Socket::SocketError::Success)
	{
		mReceiveMessageStream.Rewind();

		{
			AutoStopWatch autoReceiveStopWatch(mReceiveStopWatch);
			socketError=mSocket.Receive(mReceiveMessageStream,Bind(&TcpMessageHandler::OnReceiveCompeleteCheck,this));
		}
		

		message->SetError(socketError);

		if (socketError==Socket::SocketError::Success)
		{
			uint64 receiveLength=mReceiveMessageStream.Position();
			mReceiveMessageStream.Rewind();
			/*uint length=*/mReceiveMessageStream.Read<uint>();
			//decrypt
			MemoryByteData receivedData=mReceiveMessageStream.LeftBuffer();
			receivedData.ForceSetSize((size_t)receiveLength-sizeof(uint));
			MemoryByteData encryptedReceiveData=mReceiveCoder->Code(receivedData);
			mReceiveMessageStream.WriteData(encryptedReceiveData);


			mReceiveMessageStream.Rewind();
			/*uint length=*/mReceiveMessageStream.Read<uint>();

			uint version=mReceiveMessageStream.Read<uint>();
			if (version<mMessageVersion)
			{
				//incompatible message version
				Log::AssertFailedFormat("Error message version:{}< {}",version,mMessageVersion);

				message->SetSocketError(errno);
				message->SetState(MessageState::ConnectFail);
				FireUIEventAsync(message->ReceiveHandler(),message);
			}
			else
			{
				/*uint nameLength=*/mReceiveMessageStream.Read<uint>();
				StringRef responseMessageName=mReceiveMessageStream.ReadString();

				StringRef expectedResponseClassName=message->ResponseClassName();
				if (expectedResponseClassName==responseMessageName)
				{

					message->SetError(socketError);
					MemoryByteData receiveData=mReceiveMessageStream.ReadData((size_t)(receiveLength-mReceiveMessageStream.Position()),DataReadingMode::DirectMove);
					message->ParseFromResponse(receiveData);
					Log::FormatInfo("Receive:{}",responseMessageName.c_str());

					message->SetState(MessageState::Completed);
					FireUIEventAsync(message->ReceiveHandler(),message);
				}
				else
				{
					Log::AssertFailedFormat("Error response id:{} for {}",responseMessageName.c_str(),message->Class().Name().c_str());

					message->SetSocketError(errno);
					message->SetState(MessageState::ConnectFail);
					FireUIEventAsync(message->ReceiveHandler(),message);
				}
			}
		}
		else
		{
			Log::FormatError("Cannot Receive response for:{}",message->Class().Name().c_str());

			message->SetSocketError(errno);
			message->SetState(MessageState::ConnectFail);
			FireUIEventAsync(message->ReceiveHandler(),message);
		}
	}
	else
	{
		Log::FormatError("Cannot Send:{}",message->Class().Name().c_str());

		message->SetSocketError(errno);
		message->SetState(MessageState::ConnectFail);
		FireUIEventAsync(message->ReceiveHandler(),message);

	}

	return message;
}

void TcpMessageHandler::FailSocket( IMessage* message )
{
	char buffer[1024];
	int errorCode= mSocket.GetError();
#ifdef WIN32
	strerror_s(buffer,errorCode);
#else
	strerror_r(errorCode, buffer, 1024);
#endif


	Log::FormatError("Connect error:{} {}",errorCode,buffer);
	message->SetState(MessageState::ConnectFail);

	//give up all message?
	while (!mMessageQueue.IsEmpty()) 
	{
		IMessage* tempMessage=mMessageQueue.Head();
		tempMessage->SetError(MessageError::ConnectFail);
		tempMessage->SetState(MessageState::ConnectFail);
		mMessageQueue.Pop();
	}

	mSocket.ShutDown(Socket::SocketPipeType::ReadWrite);
}

bool TcpMessageHandler::OnReceiveCompeleteCheck( const IStream& stream )
{
	RETURN_FALSE_IF(stream.Length()<sizeof(size_t));

	uintp pos=stream.Position();
	stream.Rewind();
	size_t length=stream.Read<size_t>();
	bool isComplted=(length==pos-sizeof(size_t));
	stream.SetPosition(pos);

	return isComplted;
}

MEDUSA_END;
