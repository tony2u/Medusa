// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

namespace Socket
{
	namespace SocketAddressFamily
	{
		enum SocketAddressFamily_t
		{
			TCPIP=AF_INET,
			Unix=AF_UNIX
		};
	}
	

	namespace SocketType
	{
		enum SocketType_t
		{
			TCP=SOCK_STREAM,
			UDP=SOCK_DGRAM
		};
	}
	

	namespace SocketProtocolType
	{
		enum SocketProtocolType_t
		{
			TCP=IPPROTO_TCP,
			UDP=IPPROTO_UDP
		};
	}
	
		 

	/*
	Success 
	PartAll	transfer part or all data >0
	Fault	 -1 <0
	Interrupt	
	ConnectFault	(maybe other close the connection)
	*/
	namespace SocketError
	{
		enum SocketError_t
		{
			Success=0,
			Fault=-1,
			Interrupt=EINTR,
			ConnectFault=EPIPE,
			Timeout=-2,


		};
	}
	

	
	namespace SocketPipeType
	{
		enum SocketPipeType_t
		{
			Read=0,
			Write=1,
			ReadWrite=2
		};

	}
	
}

MEDUSA_END;
