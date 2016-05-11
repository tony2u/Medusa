// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Socket.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SocketError Socket::Send(const IStream& stream, int inControlFlag)
{
	if (mSocketType != SocketType::TCP)
	{
		return SocketError::Fault;
	}

	//inControlFlag:
	//MSG_DONTROUTE			do not search route table
	//MSG_OOB				receive or send outboard data
	//MSG_PEEK				only peek data,not move data from system data buffer
	//MSG_WAITALL			wait all data
	MemoryData messageData = stream.ReadBeginToCurrent(DataReadingMode::DirectMove);
	const char* tempCharBuffer = (const char*)messageData.Data();
	size_t messageSize = *(size_t*)tempCharBuffer;
	if (messageSize < 4)
	{
		Log::AssertFailedFormat("Invalid ISocket::Send message size:{} <4", messageSize);
		return SocketError::Fault;
	}

	intp writtenDataSize = 0;
	intp leftDataSize = messageData.Size();

	SocketError result = SocketError::Success;
	while (leftDataSize > 0)
	{
		writtenDataSize = send(mSocketDescriptor, tempCharBuffer, static_cast<int>(leftDataSize), inControlFlag);
		if (writtenDataSize <= 0)
		{
			result = SocketError::Fault;
			break;
		}
		leftDataSize -= writtenDataSize;
		tempCharBuffer += writtenDataSize;
	}

	if (leftDataSize <= 0)
	{
		result = SocketError::Success;
	}
	return result;
}

SocketError Socket::SendTo(const AddressInfo& address, const IStream& stream, int inControlFlag)
{
	if (mSocketType != SocketType::UDP)
	{
		return SocketError::Fault;
	}
	SocketError result = SocketError::Success;
	MemoryData messageData = stream.ReadToEnd(DataReadingMode::DirectMove);

	const char* tempCharBuffer = (const char*)messageData.Data();
	intp writtenDataSize = 0;
	intp leftDataSize = messageData.Size();
	while (leftDataSize > 0)
	{

		writtenDataSize = sendto(mSocketDescriptor, tempCharBuffer, static_cast<int>(leftDataSize), inControlFlag, address.GenearlAddressPtr(), sizeof(sockaddr));
		if (writtenDataSize <= 0)
		{
			result = SocketError::Fault;
			break;
		}
		leftDataSize -= writtenDataSize;
		tempCharBuffer += writtenDataSize;

	}
	if (leftDataSize <= 0)
	{
		result = SocketError::Success;
	}
	return result;
}

SocketError Socket::Receive(IStream& stream, int inControlFlag)
{
	if (mSocketType != SocketType::TCP)
	{
		return SocketError::Fault;
	}
	//inControlFlag:
	//MSG_DONTROUTE			do not search route table
	//MSG_OOB				receive or send outboard data
	//MSG_PEEK				only peek data,not move data from system data buffer
	//MSG_WAITALL			wait all data
	SocketError result;
	const int tempBufferSize = 1024;
	char tempBuffer[tempBufferSize];

	while (true)
	{
		intp readDataSize = recv(mSocketDescriptor, tempBuffer, tempBufferSize, inControlFlag);

		if (readDataSize < 0)
		{
			Log::FormatError("SocketError:read size:{}", (int)readDataSize);
			result = SocketError::Fault;
			break;
		}
		else if (readDataSize>0)
		{
			stream.WriteData(MemoryData::FromStatic((const byte*)tempBuffer, readDataSize));
			/*if (checker(stream))
			{
				result = SocketError::Success;
				break;
			}*/

		}
		else
		{
			Log::FormatError("SocketError:read size:{}", (int)readDataSize);

			result = SocketError::Fault;
			break;
		}
	}


	return result;
}

SocketError Socket::ReceiveFrom(const AddressInfo& address, IStream& stream, int inControlFlag)
{
	if (mSocketType != SocketType::UDP)
	{
		return SocketError::Fault;
	}
	SocketError result;
	const int tempBufferSize = 1024;
	char tempBuffer[tempBufferSize];


	int outFromDataSize = sizeof(sockaddr);

	while (true)
	{
		intp readDataSize = recvfrom(mSocketDescriptor, tempBuffer, tempBufferSize, inControlFlag, address.GenearlAddressPtr(), (socklen_t*)&outFromDataSize);

		if (readDataSize < 0)
		{
			result = SocketError::Fault;
			break;
		}
		else if (readDataSize>0)
		{
			stream.WriteData(MemoryData::FromStatic((const byte*)tempBuffer, readDataSize));
			/*if (checker(stream))
			{
				result = SocketError::Success;
				break;
			}*/
		}
		else
		{
			result = SocketError::Fault;
			break;
		}
	}

	return result;
}


void Socket::Close()
{
#ifdef WIN32
	::closesocket(mSocketDescriptor);
#else
	::close(mSocketDescriptor);
#endif // WIN32
	mSocketDescriptor= (SOCKET)(~0);
}

bool Socket::ShutDown(SocketPipeType inControlFlag)
{
	return shutdown(mSocketDescriptor, (int)inControlFlag) == 0;
}

bool Socket::InitializeAPI()
{
#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return false;
	}
#endif // WIN32
	return true;
}

bool Socket::UninitializeAPI()
{
#ifdef WIN32
	WSACleanup();
#endif // WIN32

	return true;
}


const char* Socket::GetProtocolName() const
{
	if (mSocketType == SocketType::TCP)
	{
		return "tcp";
	}
	else if (mSocketType == SocketType::UDP)
	{
		return "udp";
	}
	return nullptr;
}

SocketProtocolType Socket::GetProtocolType(SocketType socketType)
{
	if (socketType == SocketType::TCP)
	{
		return SocketProtocolType::TCP;
	}
	else if (socketType == SocketType::UDP)
	{
		return SocketProtocolType::UDP;
	}
	return SocketProtocolType::TCP;
}

bool Socket::CreateSocket()
{
	if (mSocketDescriptor!= (SOCKET)(~0))
	{
		Close();
	}

	mSocketDescriptor = socket((int)mAddress.AddressFamily(), (int)mSocketType, (int)GetProtocolType(mSocketType));
	if (mSocketDescriptor <= 0)
	{
		mSocketDescriptor = (SOCKET)(~0);
		return false;
	}
	return true;
}

int Socket::GetError()
{
#ifdef WIN32
	return WSAGetLastError();
#else
	return 0;
#endif 
}

bool Socket::Bind()
{
	int result = ::bind(mSocketDescriptor, mAddress.GenearlAddressPtr(), sizeof(sockaddr));
	return result >= 0;
}

Socket* Socket::Accept()
{
	sockaddr socketAddress;
	int len = sizeof(sockaddr);
	SOCKET clientSocketDescriptor = ::accept(mSocketDescriptor, &socketAddress, (socklen_t*)&len);

	if (clientSocketDescriptor <= 0)
	{

		//int errorCode= GetError();
		return nullptr;
	}

	return new Socket(clientSocketDescriptor, socketAddress);
}

void Socket::SetSendTimeout(int milliSeconds)
{
#ifdef WIN32
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&milliSeconds, sizeof(int));
#else
	struct timeval timeout = { milliSeconds * 1000,0 };
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
#endif 
}

void Socket::SetReceiveTimeout(int milliSeconds)
{
#ifdef WIN32
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&milliSeconds, sizeof(int));
#else
	struct timeval timeout = { milliSeconds * 1000,0 };
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
#endif 
}

bool Socket::Listen(unsigned int inQueueLength /*= 5*/)
{
	if (inQueueLength != 0)
	{
		int result = ::listen(mSocketDescriptor, inQueueLength);
		return result == 0;
	}
	return false;
}

SocketError Socket::Select(SocketEventFlags& outFlags, SocketEventFlags flags, uint millisecondsTimeout /*= 0*/)
{
	outFlags = SocketEventFlags::None;

	timeval tval;
	const timeval* timeoutPtr = nullptr;
	if (millisecondsTimeout > 0)
	{
		tval.tv_sec = millisecondsTimeout / 1000;
		tval.tv_usec = (millisecondsTimeout % 1000) * 1000;
		timeoutPtr = &tval;
	}

	if (MEDUSA_FLAG_HAS(flags, SocketEventFlags::Read))
	{
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(mSocketDescriptor, &readSet);

		if (MEDUSA_FLAG_HAS(flags, SocketEventFlags::Write))
		{
			fd_set writeSet;
			FD_ZERO(&writeSet);
			FD_SET(mSocketDescriptor, &writeSet);

			int selectResult = ::select((int)mSocketDescriptor + 1, &readSet, &writeSet, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
			RETURN_OBJECT_IF(selectResult == 0, SocketError::Timeout);
			RETURN_OBJECT_IF(selectResult < 0, SocketError::Fault);

			if (FD_ISSET(mSocketDescriptor, &writeSet))
			{
				MEDUSA_FLAG_ADD(outFlags, SocketEventFlags::Write);
			}

		}
		else
		{
			int selectResult = ::select((int)mSocketDescriptor + 1, &readSet, nullptr, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
			RETURN_OBJECT_IF(selectResult == 0, SocketError::Timeout);
			RETURN_OBJECT_IF(selectResult < 0, SocketError::Fault);
		}

		if (FD_ISSET(mSocketDescriptor, &readSet))
		{
			MEDUSA_FLAG_ADD(outFlags, SocketEventFlags::Read);
		}
	}
	else
	{
		if (MEDUSA_FLAG_HAS(flags, SocketEventFlags::Write))
		{
			fd_set writeSet;
			FD_ZERO(&writeSet);
			FD_SET(mSocketDescriptor, &writeSet);

			int selectResult = ::select((int)mSocketDescriptor + 1, nullptr, &writeSet, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
			RETURN_OBJECT_IF(selectResult == 0, SocketError::Timeout);
			RETURN_OBJECT_IF(selectResult < 0, SocketError::Fault);

			if (FD_ISSET(mSocketDescriptor, &writeSet))
			{
				MEDUSA_FLAG_ADD(outFlags, SocketEventFlags::Write);
			}

		}
	}

	int error;
	int length = sizeof(error);
	//have to get more specific result
	if (getsockopt(mSocketDescriptor, SOL_SOCKET, SO_ERROR, (char*)&error, &length) < 0)	//if success, it'll return 0
	{
		return SocketError::Fault;
	}

	return SocketError::Success;
}

int Socket::Connect()
{
	int connectState = ::connect(mSocketDescriptor, mAddress.GenearlAddressPtr(), sizeof(sockaddr));
	return connectState;
}

SocketError Socket::ConnectAsync(uint millisecondsTimeout /*= 0*/)
{
	int connectState = ::connect(mSocketDescriptor, mAddress.GenearlAddressPtr(), sizeof(sockaddr));	//0:success, !=0: error
	if (connectState == 0)	//connected!
	{
		return SocketError::Success;
	}

	if (errno != EINPROGRESS)	//connect failed immediately, maybe some other errors
	{
		return SocketError::Fault;
	}

	SocketEventFlags outFlags;
	SocketError selectError = Select(outFlags, SocketEventFlags::ReadWrite, millisecondsTimeout);
	if (selectError==SocketError::Timeout)
	{
		return SocketError::Timeout;
	}
	if (selectError == SocketError::Fault)
	{
		return SocketError::InProgress;
	}

	if (outFlags==SocketEventFlags::Write)
	{
		return SocketError::Success;
	}

	return SocketError::Fault;
	
}

bool Socket::ParseAddress(StringRef inHostName, ushort port, SocketType socketType, AddressInfo& outAddress, ProtocolInfo& outProtocolInfo)
{
	RETURN_FALSE_IF_EMPTY(inHostName);
	outAddress.SetPortID(htons(port));

	//get ip address from host name, allow dotted decimal notation
	HostInfo hostInfo = HostInfo::GetHost(inHostName);
	if (hostInfo.IsValid())
	{
		sockaddr_in temp;
		memcpy(&temp.sin_addr, hostInfo.FirstHostAddress(),sizeof(temp.sin_addr));
		outAddress.SetAddress(temp.sin_addr);
	}
	else
	{
		in_addr sAddr; // IPv4地址结构体
		int r = inet_pton((int)SocketAddressFamily::TCPIP, inHostName.c_str(), &sAddr);
		if (r>0)
		{
			outAddress.SetAddress(sAddr);
		}
	}

	outProtocolInfo = ProtocolInfo::GetProtocol(GetProtocolType(socketType));
	return true;
}

void Socket::EnableAsync(bool isAsync)
{
	unsigned long   ul = isAsync ? 1 : 0;
	ioctlsocket(mSocketDescriptor, FIONBIO, &ul);

}

MEDUSA_END;
