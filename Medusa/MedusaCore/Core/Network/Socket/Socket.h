// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Network/Socket/SocketDefines.h"
#include "Core/Network/Socket/IPAddress.h"
#include "Core/Network/Socket/IPProtocol.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Event/Channel/ChannelDefines.h"

MEDUSA_BEGIN;

class Socket
{
public:
	Socket(SocketType socketType = SocketType::TCP);

	Socket(const IPAddress& address, const IPProtocol& protocolInfo, SocketType socketType = SocketType::TCP);

	Socket(SOCKET socket, const IPAddress& address, const IPProtocol& protocolInfo, SocketType socketType = SocketType::TCP);

	~Socket();
	static bool InitializeAPI();
	static void UninitializeAPI();
public:
	SOCKET SocketDescriptor() const { return mSocketDescriptor; }
	void SetSocketDescriptor(SOCKET val) { mSocketDescriptor = val; }
	bool IsValid()const { return mSocketDescriptor != (~0); }
public:
	ChannelEventResult SendAsync(int& outWriteSize, const byte* buffer, int bufferSize, int flags = 0);
	ChannelEventResult ReceiveAsync(int& outReadSize, byte* outBuffer, int bufferSize, int flags = 0);

	ChannelEventResult SendAsync(NetworkBuffer& buffer, int flags = 0);
	ChannelEventResult ReceiveAsync(NetworkBuffer& outBuffer, int flags = 0);

	bool CreateSocket();
	void Close();
	bool ShutDown(ChannelPipeType inControlFlag = ChannelPipeType::ReadWrite);

	bool Accept(Socket& outSocket);
	bool Bind();
	bool Listen(unsigned int inQueueLength = 5);
	ChannelEventResult Select(ChannelEventFlags& outFlags, ChannelEventFlags flags, uint millisecondsTimeout = 0);
	ChannelEventResult Connect();
	ChannelEventResult ConnectAsync(uint millisecondsTimeout = 0);

	int GetError()const;

	static int GetSocketError(SOCKET sock = MedusaInvalidSocket);


public:
	const IPAddress& Address()const { return mAddress; }
	void SetAddress(const IPAddress& val) { mAddress = val; }

	IPAddress LocalAddress()const;
	IPAddress RemoteAddress()const;
	bool IsSelfConnected()const;


	const IPProtocol& Protocol() const { return mProtocol; }
	void SetProtocol(const IPProtocol& val) { mProtocol = val; }

	SocketType Type() const { return mSocketType; }
	void SetType(SocketType val) { mSocketType = val; }

	void SetSendTimeout(int milliSeconds);
	void SetReceiveTimeout(int milliSeconds);
	void SetSendBufferSize(uint val);
	void SetReceiveBufferSize(uint val);

	uint GetSendBufferSize()const;
	uint GetReceiveBufferSize()const;

	void EnableAsync(bool isAsync);

	void EnableTcpNoDelay(bool val);
	void EnableReuseAddress(bool val);
	void EnableReusePort(bool val);
	void EnableKeepAlive(bool val);
protected:
	SocketType mSocketType = SocketType::TCP;
	SOCKET mSocketDescriptor = MedusaInvalidSocket;

	IPAddress mAddress;
	IPProtocol mProtocol;
};

MEDUSA_END;