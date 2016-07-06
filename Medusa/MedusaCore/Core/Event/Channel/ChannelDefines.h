// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;


/*
Success
PartAll	transfer part or all data >0
Fault	 -1 <0
Interrupt
ConnectFault	(maybe other close the connection)
*/
enum class ChannelEventResult
{
	Retry = -4,
	Timeout = -3,
	Fault = -2,
	InProgress = -1,

	Success = 0,
	None=1,

	Interrupt = EINTR,
	ConnectFault = EPIPE,

};



enum class ChannelEventFlags
{
	None = 0,
	Read = 1,
	Write = 2,
	ReadWrite = 3,

	Fault=4,
	Timeout=8,
	Retry=16,
	Idle=32,
};


enum class ChannelPipeType
{
	Read = 0,
	Write = 1,
	ReadWrite = 2

};

enum class ConnectionState
{
	Disconnected,
	Connecting,
	Connected,
	Disconnecting
};


MEDUSA_END;