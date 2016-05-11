// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

#include "Core/Network/Socket/SocketDefines.h"
#include "Core/Network/Socket/AddressInfo.h"
#include "Core/Network/Socket/HostInfo.h"
#include "Core/Network/Socket/ProtocolInfo.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;

class Socket
{
public:
	Socket(SocketType socketType = SocketType::TCP)
		:mSocketType(socketType)
	{
	}

	Socket(const AddressInfo& address, const ProtocolInfo& protocolInfo, SocketType socketType = SocketType::TCP)
		:Socket(socketType)
	{
		mAddress = address;
		mProtocol = protocolInfo;
	}

	Socket(SOCKET socketDescriptor, const sockaddr& address, SocketType socketType = SocketType::TCP)
		:mSocketType(socketType)
	{
		mSocketDescriptor = socketDescriptor;
		mAddress.SetGeneralAddress(address);
	}

	Socket(ushort port, SocketType socketType = SocketType::TCP)
		:Socket(socketType)
	{
		//set INADDR_ANY to receive any client
		mAddress.SetAddress(INADDR_ANY);
		mAddress.SetPortID(htons(port));
	}

	static bool InitializeAPI();
	static bool UninitializeAPI();
public:
	SOCKET SocketDescriptor() const { return mSocketDescriptor; }
	void SetSocketDescriptor(SOCKET val) { mSocketDescriptor = val; }
	bool IsValid()const { return mSocketDescriptor != (~0); }
public:
	SocketError Send(const IStream& stream, int inControlFlag = 0);
	SocketError SendTo(const AddressInfo& address, const IStream& stream, int inControlFlag = 0);

	SocketError Receive(IStream& stream, int inControlFlag = 0);
	SocketError ReceiveFrom(const AddressInfo& address, IStream& stream, int inControlFlag = 0);
	
	bool CreateSocket();
	void Close();
	bool ShutDown(SocketPipeType inControlFlag = SocketPipeType::ReadWrite);

	Socket* Accept();
	bool Bind();
	bool Listen(unsigned int inQueueLength = 5);
	SocketError Select(SocketEventFlags& outFlags, SocketEventFlags flags, uint millisecondsTimeout = 0);
	int Connect();
	SocketError ConnectAsync(uint millisecondsTimeout = 0);

	static int GetError();
	static bool ParseAddress(StringRef inHostName, ushort port, SocketType socketType, AddressInfo& outAddress, ProtocolInfo& outProtocolInfo);
protected:
	const char* GetProtocolName()const;
	static SocketProtocolType GetProtocolType(SocketType socketType);
public:
	AddressInfo& Address() { return mAddress; }
	void SetAddress(const AddressInfo& val) { mAddress = val; }

	ProtocolInfo Protocol() const { return mProtocol; }
	void SetProtocol(const ProtocolInfo& val) { mProtocol = val; }

	void SetSendTimeout(int milliSeconds);
	void SetReceiveTimeout(int milliSeconds);

	void EnableAsync(bool isAsync);
protected:
	SocketType mSocketType = SocketType::TCP;
	SOCKET mSocketDescriptor = (SOCKET)(~0);

	AddressInfo mAddress;
	ProtocolInfo mProtocol;
};
MEDUSA_END;
