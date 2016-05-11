// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

enum class SocketAddressFamily:ushort
{
	TCPIP = AF_INET,
	Unix = AF_UNIX
};


enum class SocketType
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
};


enum class SocketProtocolType
{
	TCP = IPPROTO_TCP,
	UDP = IPPROTO_UDP
};



/*
Success
PartAll	transfer part or all data >0
Fault	 -1 <0
Interrupt
ConnectFault	(maybe other close the connection)
*/
enum class SocketError
{
	Timeout = -3,
	Fault = -2,
	InProgress=-1,

	Success = 0,

	Interrupt = EINTR,
	ConnectFault = EPIPE,

};



enum class SocketPipeType
{
	Read = 0,
	Write = 1,
	ReadWrite = 2

};


enum class SocketEventFlags
{
	None = 0,
	Read = 1,
	Write = 2,

	ReadWrite = 3,


};

MEDUSA_END;
