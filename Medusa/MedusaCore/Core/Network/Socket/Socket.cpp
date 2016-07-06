// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Socket.h"
#include "Core/IO/Stream/IStream.h"
#include "Core/Log/Log.h"
#include "Core/Memory/NetworkBuffer.h"

#ifdef MEDUSA_WINDOWS
#define _WINSOCKAPI_
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"wsock32.lib")		//add socket lib, or it'll be failed
#endif

MEDUSA_BEGIN;



bool Socket::InitializeAPI()
{
#ifdef MEDUSA_WINDOWS
	static bool isInitialized = false;
	if (!isInitialized)
	{
		isInitialized = true;
		WORD wVersionRequested;
		WSADATA wsaData;
		wVersionRequested = MAKEWORD(2, 2);
		int err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			return false;
		}
		atexit(Socket::UninitializeAPI);

	}

#endif // WIN32
	return true;
}

void Socket::UninitializeAPI()
{
#ifdef MEDUSA_WINDOWS
	WSACleanup();
#endif // WIN32
}


Socket::Socket(SocketType socketType /*= SocketType::TCP*/)
	:mSocketType(socketType)
{
	InitializeAPI();
}

Socket::Socket(const IPAddress& address, const IPProtocol& protocolInfo, SocketType socketType /*= SocketType::TCP*/)
	: Socket(MedusaInvalidSocket, address, protocolInfo, socketType)
{

}

Socket::Socket(SOCKET socket, const IPAddress& address, const IPProtocol& protocolInfo, SocketType socketType /*= SocketType::TCP*/)
	: mSocketDescriptor(socket),
	mAddress(address),
	mProtocol(protocolInfo),
	mSocketType(socketType)
{
	InitializeAPI();
}

Socket::~Socket()
{
	
}

void Socket::Close()
{
	if (mSocketDescriptor != MedusaInvalidSocket)
	{
#ifdef MEDUSA_WINDOWS
		::closesocket(mSocketDescriptor);
#else
		::close(mSocketDescriptor);
#endif // MEDUSA_WINDOWS
		mSocketDescriptor = MedusaInvalidSocket;
	}
}

bool Socket::ShutDown(ChannelPipeType inControlFlag)
{
	return shutdown(mSocketDescriptor, (int)inControlFlag) == 0;
}


void Socket::EnableAsync(bool isAsync)
{
	unsigned long   ul = isAsync ? 1 : 0;
#ifdef MEDUSA_IOS
	fcntl(mSocketDescriptor, F_SETFL, O_NONBLOCK);
#else
	ioctlsocket(mSocketDescriptor, FIONBIO, &ul);
#endif
}

void Socket::EnableKeepAlive(bool val)
{
	int optval = val ? 1 : 0;
	::setsockopt(mSocketDescriptor, SOL_SOCKET, SO_KEEPALIVE, (const char*)&optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::EnableReusePort(bool val)
{
#ifdef SO_REUSEPORT
	int optval = val ? 1 : 0;
	int ret = ::setsockopt(mSocketDescriptor, SOL_SOCKET, SO_REUSEPORT, (const char*)&optval, static_cast<socklen_t>(sizeof optval));
	if (ret < 0 && val)
	{
		Log::AssertFailed("SO_REUSEPORT failed.");
	}
#endif
}

void Socket::EnableReuseAddress(bool val)
{
	int optval = val ? 1 : 0;
	::setsockopt(mSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::EnableTcpNoDelay(bool val)
{
	int optval = val ? 1 : 0;
	::setsockopt(mSocketDescriptor, IPPROTO_TCP, TCP_NODELAY, (const char*)&optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::SetSendTimeout(int milliSeconds)
{
#ifdef MEDUSA_WINDOWS
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&milliSeconds, sizeof(int));
#else
	struct timeval timeout = { milliSeconds * 1000,0 };
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
#endif 
}

void Socket::SetReceiveTimeout(int milliSeconds)
{
#ifdef MEDUSA_WINDOWS
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&milliSeconds, sizeof(int));
#else
	struct timeval timeout = { milliSeconds * 1000,0 };
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
#endif 
}

void Socket::SetSendBufferSize(uint val)
{
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_SNDBUF, (char *)&val, sizeof(val));
}

void Socket::SetReceiveBufferSize(uint val)
{
	setsockopt(mSocketDescriptor, SOL_SOCKET, SO_RCVBUF, (char *)&val, sizeof(val));
}

uint Socket::GetSendBufferSize() const
{
	uint val;
	int len = sizeof(val);
	getsockopt(mSocketDescriptor, SOL_SOCKET, SO_SNDBUF, (char *)&val, &len);
	return val;
}


uint Socket::GetReceiveBufferSize() const
{
	uint val;
	int len = sizeof(val);
	getsockopt(mSocketDescriptor, SOL_SOCKET, SO_RCVBUF, (char *)&val, &len);
	return val;
}

bool Socket::CreateSocket()
{
	if (mSocketDescriptor != MedusaInvalidSocket)
	{
		Close();
	}

	mSocketDescriptor = socket((int)mAddress.Family(), (int)mSocketType, (int)IPProtocol::GetProtocolType(mSocketType));
	if (mSocketDescriptor <= 0)
	{
		mSocketDescriptor = MedusaInvalidSocket;
		return false;
	}
	else if (mSocketDescriptor == MedusaInvalidSocket)
	{
		int err = GetError();
		char errBuffer[1024];
		strerror_s(errBuffer, err);
		Log::FormatError("Failed to CreateSocket. {}", errBuffer);
		return false;
	}

	return true;
}

int Socket::GetError()const
{
#ifdef MEDUSA_WINDOWS
	return WSAGetLastError();
#else
	int error;
	int length = sizeof(error);
	//have to get more specific result
	if (getsockopt(mSocketDescriptor, SOL_SOCKET, SO_ERROR, (char*)&error, &length) < 0)	//if success, it'll return 0
	{
		return errno;
	}
	return error;
#endif 
}

int Socket::GetSocketError(SOCKET sock /*= MedusaInvalidSocket*/)
{
	if (sock != MedusaInvalidSocket)
	{
		int error;
		int length = sizeof(error);
		//have to get more specific result
		if (getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&error, &length) == 0)	//if success, it'll return 0
		{
			return error;
		}
	}

#ifdef MEDUSA_WINDOWS
	return WSAGetLastError();
#else
	return errno;
#endif

}

IPAddress Socket::LocalAddress() const
{
	return IPAddress::Local(mSocketDescriptor);
}

IPAddress Socket::RemoteAddress() const
{
	return IPAddress::Remote(mSocketDescriptor);
}


bool Socket::IsSelfConnected() const
{
	IPAddress local = LocalAddress();
	IPAddress remote = RemoteAddress();
	if (local.Family() == SocketAddressFamily::IP)
	{
		return local.Port() == remote.Port() && Memory::Equals(&local.IP().sin_addr, &remote.IP().sin_addr,1);
	}
	else if (local.Family() == SocketAddressFamily::IP6)
	{
		return local.Port() == remote.Port() && Memory::Equals(&local.IP6().sin6_addr, &remote.IP6().sin6_addr,1);
	}
	return false;
}

bool Socket::Bind()
{
	int result = ::bind(mSocketDescriptor, mAddress.GenearlPtr(), sizeof(sockaddr));
	return result >= 0;
}

bool Socket::Accept(Socket& outSocket)
{
	IPAddress address;
	sockaddr socketAddress;
	int len = sizeof(sockaddr);
	SOCKET clientSocketDescriptor = ::accept(mSocketDescriptor, &socketAddress, (socklen_t*)&len);

	if (clientSocketDescriptor <= 0)
	{
		//int errorCode= GetError();
		return nullptr;
	}
	address.SetGenearlAddress(socketAddress);

	outSocket.SetType(mSocketType);
	outSocket.SetSocketDescriptor(clientSocketDescriptor);
	outSocket.SetAddress(address);
	outSocket.SetProtocol(mProtocol);
	outSocket.EnableAsync(true);
	return true;
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

ChannelEventResult Socket::Select(ChannelEventFlags& outFlags, ChannelEventFlags flags, uint32_t millisecondsTimeout /*= 0*/)
{
	outFlags = ChannelEventFlags::None;

	timeval tval;
	const timeval* timeoutPtr = nullptr;
	if (millisecondsTimeout > 0)
	{
		tval.tv_sec = millisecondsTimeout / 1000;
		tval.tv_usec = (millisecondsTimeout % 1000) * 1000;
		timeoutPtr = &tval;
	}

	if (MEDUSA_FLAG_HAS(flags, ChannelEventFlags::Read))
	{
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(mSocketDescriptor, &readSet);

		if (MEDUSA_FLAG_HAS(flags, ChannelEventFlags::Write))
		{
			fd_set writeSet;
			FD_ZERO(&writeSet);
			FD_SET(mSocketDescriptor, &writeSet);

			int selectResult = ::select((int)mSocketDescriptor + 1, &readSet, &writeSet, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
			RETURN_OBJECT_IF(selectResult == 0, ChannelEventResult::Timeout);
			RETURN_OBJECT_IF(selectResult < 0, ChannelEventResult::Fault);

			if (FD_ISSET(mSocketDescriptor, &writeSet))
			{
				MEDUSA_FLAG_ADD(outFlags, ChannelEventFlags::Write);
			}

		}
		else
		{
			int selectResult = ::select((int)mSocketDescriptor + 1, &readSet, nullptr, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
			RETURN_OBJECT_IF(selectResult == 0, ChannelEventResult::Timeout);
			RETURN_OBJECT_IF(selectResult < 0, ChannelEventResult::Fault);
		}

		if (FD_ISSET(mSocketDescriptor, &readSet))
		{
			MEDUSA_FLAG_ADD(outFlags, ChannelEventFlags::Read);
		}
	}
	else
	{
		if (MEDUSA_FLAG_HAS(flags, ChannelEventFlags::Write))
		{
			fd_set writeSet;
			FD_ZERO(&writeSet);
			FD_SET(mSocketDescriptor, &writeSet);

			int selectResult = ::select((int)mSocketDescriptor + 1, nullptr, &writeSet, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
			RETURN_OBJECT_IF(selectResult == 0, ChannelEventResult::Timeout);
			RETURN_OBJECT_IF(selectResult < 0, ChannelEventResult::Fault);

			if (FD_ISSET(mSocketDescriptor, &writeSet))
			{
				MEDUSA_FLAG_ADD(outFlags, ChannelEventFlags::Write);
			}

		}
	}

	int error;
	int length = sizeof(error);
	//have to get more specific result
	if (getsockopt(mSocketDescriptor, SOL_SOCKET, SO_ERROR, (char*)&error, &length) < 0)	//if success, it'll return 0
	{
		return ChannelEventResult::Fault;
	}

	return ChannelEventResult::Success;
}

ChannelEventResult Socket::Connect()
{
	int connectState = ::connect(mSocketDescriptor, mAddress.GenearlPtr(), sizeof(sockaddr_in));
	if (connectState == 0)	//connected!
	{
		return ChannelEventResult::Success;
	}

	int err = GetError();
	switch (err)
	{
	case EINPROGRESS:
	case EINTR:
	case EISCONN:
	case EWOULDBLOCK:
		return ChannelEventResult::InProgress;
	case EAGAIN:
	case EADDRINUSE:
	case EADDRNOTAVAIL:
	case ECONNREFUSED:
	case ENETUNREACH:
		return ChannelEventResult::Retry;
	case EACCES:
	case EPERM:
	case EAFNOSUPPORT:
	case EALREADY:
	case EBADF:
	case EFAULT:
	case ENOTSOCK:
	default:
		return ChannelEventResult::Fault;
		break;
	}

}

ChannelEventResult Socket::ConnectAsync(uint32_t millisecondsTimeout /*= 0*/)
{
	int connectState = ::connect(mSocketDescriptor, mAddress.GenearlPtr(), sizeof(sockaddr));	//0:success, !=0: error
	if (connectState == 0)	//connected!
	{
		return ChannelEventResult::Success;
	}

	int err = GetError();
	if (err != EWOULDBLOCK&&err != EINPROGRESS)	//connect failed immediately, maybe some other errors
	{
		return ChannelEventResult::Fault;
	}


	ChannelEventFlags outFlags;
	ChannelEventResult selectError = Select(outFlags, ChannelEventFlags::ReadWrite, millisecondsTimeout);
	if (selectError == ChannelEventResult::Timeout)
	{
		return ChannelEventResult::Timeout;
	}
	if (selectError == ChannelEventResult::Fault)
	{
		return ChannelEventResult::InProgress;
	}

	if (outFlags == ChannelEventFlags::Write)
	{
		return ChannelEventResult::Success;
	}

	return ChannelEventResult::Fault;

}



ChannelEventResult Socket::SendAsync(int& outWriteSize, const byte* buffer, int bufferSize, int flags /*= 0*/)
{
	int writtenDataSize = ::send(mSocketDescriptor, (const char*)buffer, bufferSize, flags);
	if (writtenDataSize < 0)
	{
		if (errno == EINTR)
			return ChannelEventResult::Interrupt;

		if (errno == EAGAIN)
		{
			return ChannelEventResult::InProgress;
		}

		return ChannelEventResult::Fault;
	}
	else if (writtenDataSize == 0)
	{
		int error=GetError();
		Log::FormatError("Read error:{}", error);
		return ChannelEventResult::Fault;
	}
	else
	{
		outWriteSize = writtenDataSize;
		return ChannelEventResult::Success;
	}
}

ChannelEventResult Socket::SendAsync(NetworkBuffer& buffer, int flags /*= 0*/)
{
	while (buffer.ReadableCount() > 0)
	{
		int writtenDataSize = 0;
		auto socketError = SendAsync(writtenDataSize, buffer.ReadBegin(), (int)buffer.ReadableCount());
		if (socketError == ChannelEventResult::Success)
		{
			buffer.Retrieve(writtenDataSize);
		}
		else
		{
			return socketError;
		}
	}

	return ChannelEventResult::Success;
}

ChannelEventResult Socket::ReceiveAsync(int& outReadSize, byte* outBuffer, int bufferSize, int flags /*= 0*/)
{
	outReadSize = 0;
	int readDataSize = ::recv(mSocketDescriptor, (char*)outBuffer, bufferSize, flags);

	if (readDataSize < 0)
	{
		int err = GetError();
		if (err == EAGAIN)
		{
			return ChannelEventResult::InProgress;
		}
		else if (err == EWOULDBLOCK)
		{
			// No more data to read right now.
			return ChannelEventResult::InProgress;
		}
		else
		{
			return ChannelEventResult::Fault;
		}
	}
	else if (readDataSize == 0)
	{
		//socket has been closed
		int error = GetError();
		Log::FormatError("Read error:{}", error);

		int socketError= GetSocketError(mSocketDescriptor);
		Log::FormatError("Read socket error:{}", socketError);

		return ChannelEventResult::ConnectFault;
	}
	else
	{
		//read success
		outReadSize = readDataSize;
		return ChannelEventResult::Success;
	}

}

ChannelEventResult Socket::ReceiveAsync(NetworkBuffer& outBuffer, int flags /*= 0*/)
{
	while (true)
	{
		int outReadSize = 0;
		outBuffer.TryAdjust();
		size_t writableSize = outBuffer.WritableCount();
		auto socketError = ReceiveAsync(outReadSize, outBuffer.WriteBegin(), (int)writableSize);
		if (socketError == ChannelEventResult::Success)
		{
			outBuffer.HasWritten(outReadSize);	//read all data
			return ChannelEventResult::Success;
		}
		else if(socketError==ChannelEventResult::InProgress)
		{
			return socketError;
		}
		else
		{
			return socketError;
		}
	}
	return ChannelEventResult::Success;

}

MEDUSA_END;