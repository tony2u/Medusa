// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Net/Socket/ISocket.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

namespace Socket
{
	SocketError::SocketError_t ISocket::Send( const IStream& stream,int inControlFlag )
	{
		if (mSocketType!=SocketType::TCP)
		{
			return SocketError::Fault;
		}

		//inControlFlag:
		//MSG_DONTROUTE			do not search route table
		//MSG_OOB				receive or send outboard data
		//MSG_PEEK				only peek data,not move data from system data buffer
		//MSG_WAITALL			wait all data
		MemoryByteData messageData=stream.ReadBeginToCurrent(DataReadingMode::DirectMove);
		const char* tempCharBuffer=(const char*)messageData.Data();		
		size_t messageSize=*(size_t*)tempCharBuffer;
		if (messageSize<4)
		{
			Log::AssertFailedFormat("Invalid ISocket::Send message size:{} <4",messageSize);
			return SocketError::Fault;
		}

		intp writtenDataSize=0;		
		intp leftDataSize=messageData.Size();

		SocketError::SocketError_t result=SocketError::Success;
		while(leftDataSize>0) 
		{
			writtenDataSize=send(mSocketDescriptor,tempCharBuffer,static_cast<int>(leftDataSize),inControlFlag);
			if(writtenDataSize<=0)	
			{
				result= SocketError::Fault; 
				break;
			}
			leftDataSize-=writtenDataSize; 
			tempCharBuffer+=writtenDataSize;    
		} 

		if (leftDataSize<=0)
		{
			result=SocketError::Success;
		}
		return result; 
	}

	SocketError::SocketError_t ISocket::SendTo(const AddressInfo& address,const IStream& stream,int inControlFlag )
	{
		if (mSocketType!=SocketType::UDP)
		{
			return SocketError::Fault;
		}
		SocketError::SocketError_t result = SocketError::Success;
		MemoryByteData messageData=stream.ReadToEnd(DataReadingMode::DirectMove);

		const char* tempCharBuffer=(const char*)messageData.Data();		
		intp writtenDataSize=0;		
		intp leftDataSize=messageData.Size();		
		while(leftDataSize>0) 
		{ 
			
			writtenDataSize=sendto(mSocketDescriptor,tempCharBuffer,static_cast<int>(leftDataSize),inControlFlag,address.GenearlAddressPtr(),sizeof(sockaddr));	
			if(writtenDataSize<=0)			
			{        
				result= SocketError::Fault; 
				break;
			} 
			leftDataSize-=writtenDataSize; 
			tempCharBuffer+=writtenDataSize;   

		} 
		if (leftDataSize<=0)
		{
			result=SocketError::Success;
		}
		return result; 
	}

	SocketError::SocketError_t ISocket::Receive(IStream& stream,ReceiveCompleteChecker checker,int inControlFlag )
	{
		if (mSocketType!=SocketType::TCP)
		{
			return SocketError::Fault;
		}
		//inControlFlag:
		//MSG_DONTROUTE			do not search route table
		//MSG_OOB				receive or send outboard data
		//MSG_PEEK				only peek data,not move data from system data buffer
		//MSG_WAITALL			wait all data
		SocketError::SocketError_t result;
		const int tempBufferSize=1024;
		char tempBuffer[tempBufferSize];

		while(true)
		{ 
			intp readDataSize=recv(mSocketDescriptor,tempBuffer,tempBufferSize,inControlFlag);	

			if(readDataSize<0)				
			{ 
				Log::FormatError("SocketError:read size:{}",(int)readDataSize);
				result= SocketError::Fault; 
				break;
			} 
			else if (readDataSize>0)
			{
				stream.WriteData(MemoryByteData::FromStatic((const byte*)tempBuffer,readDataSize));
				if (checker(stream))
				{
					result=SocketError::Success;
					break;
				}

			} 
			else
			{
				Log::FormatError("SocketError:read size:{}",(int)readDataSize);

				result= SocketError::Fault; 
				break;
			}
		} 


		return result; 
	}

	SocketError::SocketError_t ISocket::ReceiveFrom(const AddressInfo& address,IStream& stream,ReceiveCompleteChecker checker,int inControlFlag)
	{
		if (mSocketType!=SocketType::UDP)
		{
			return SocketError::Fault;
		}
		SocketError::SocketError_t result;
		const int tempBufferSize=1024;
		char tempBuffer[tempBufferSize];


		int outFromDataSize=sizeof(sockaddr);

		while(true) 
		{ 
			intp readDataSize=recvfrom(mSocketDescriptor,tempBuffer,tempBufferSize,inControlFlag,address.GenearlAddressPtr(),(socklen_t*)&outFromDataSize);

			if(readDataSize<0)				
			{ 
				result= SocketError::Fault; 
				break;
			} 
			else if(readDataSize>0)
			{
				stream.WriteData(MemoryByteData::FromStatic((const byte*)tempBuffer,readDataSize));
				if (checker(stream))
				{
					result=SocketError::Success;
					break;
				}
			}
			else
			{
				result= SocketError::Fault; 
				break;
			}
		} 

		return result; 
	}


	void ISocket::Close()
	{
#ifdef WIN32
		::closesocket(mSocketDescriptor);
#else
		::close(mSocketDescriptor);
#endif // WIN32
	}

	bool ISocket::ShutDown( SocketPipeType::SocketPipeType_t inControlFlag )
	{

		return shutdown(mSocketDescriptor,inControlFlag)==0;
	}

	bool ISocket::InitializeAPI()
	{
#ifdef WIN32
		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD( 2, 2 );
		int err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) 
		{
			return false;
		}
#endif // WIN32
		return true;
	}

	bool ISocket::UninitializeAPI()
	{
#ifdef WIN32
		WSACleanup();
#endif // WIN32

		return true;
	}


	bool ISocket::Initialize()
	{
		return CreateSocket();
	}

	bool ISocket::Uninitialize()
	{
		return true;
	}

	const char* ISocket::GetProtocolName() const
	{
		if (mSocketType==SocketType::TCP)
		{
			return "tcp";
		}
		else if (mSocketType==SocketType::UDP)
		{
			return "udp";
		} 
		return nullptr;
	}

	SocketProtocolType::SocketProtocolType_t ISocket::GetProtocolType(SocketType::SocketType_t socketType)
	{
		if (socketType==SocketType::TCP)
		{
			return SocketProtocolType::TCP;
		}
		else if (socketType==SocketType::UDP)
		{
			return SocketProtocolType::UDP;
		} 
		return SocketProtocolType::TCP;
	}

	bool ISocket::CreateSocket()
	{
		mSocketDescriptor=socket(mAddress.AddressFamily(),mSocketType,GetProtocolType(mSocketType));
		if (mSocketDescriptor<=0)
		{
			return false;
		}
		return true;
	}

	int ISocket::GetError()
	{
#ifdef WIN32
		return WSAGetLastError();
#else
		return 0;
#endif 
	}

	void ISocket::SetSendTimeout( int milliSeconds )
	{
#ifdef WIN32
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_SNDTIMEO,(char *)&milliSeconds,sizeof(int));
#else
		struct timeval timeout = {milliSeconds*1000,0}; 
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(struct timeval)); 
#endif 
	}

	void ISocket::SetReceiveTimeout( int milliSeconds )
	{
#ifdef WIN32
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_RCVTIMEO,(char *)&milliSeconds,sizeof(int));
#else
		struct timeval timeout = {milliSeconds*1000,0}; 
		setsockopt(mSocketDescriptor,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval)); 
#endif 
	}

	bool ISocket::ParseAddress( StringRef inHostName, ushort port,SocketType::SocketType_t socketType,AddressInfo& outAddress,ProtocolInfo& outProtocolInfo )
	{
		RETURN_FALSE_IF_EMPTY(inHostName);
		outAddress.SetPortID(htons(port));

		//get ip address from host name, allow dotted decimal notation
		HostInfo hostInfo=HostInfo::GetHost(inHostName);
		if(hostInfo.IsValid())
		{
			sockaddr_in temp;
			memcpy(&temp.sin_addr,hostInfo.FirstHostAddress(),hostInfo.HostAddressSize());
			outAddress.SetAddress(temp.sin_addr);
		}
		else
		{
			unsigned int addr=inet_addr(inHostName.c_str());
			outAddress.SetAddress(addr);
		}

		outProtocolInfo=ProtocolInfo::GetProtocol(GetProtocolType(socketType));
		return true;
	}

	void ISocket::SetIsAsync( bool isAsync )
	{
		//unsigned long   ul=   1; 

		//ioctlsocket(mSocketDescriptor,FIONBIO,&ul);

	}

}
MEDUSA_END;
