// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BaseSocketService.h"
#include "Core/Log/Log.h"
#include "Core/Network/Socket/AddressInfo.h"
#include "Core/Network/Socket/ProtocolInfo.h"
#include "Core/Network/Message/MessageFactory.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Threading/Thread.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Profile/AutoStopWatch.h"


MEDUSA_BEGIN;

BaseSocketService::BaseSocketService(size_t id, StringRef host, ushort port)
	:BaseThreadService(id,host,port)
{
	AddressInfo addressInfo;
	ProtocolInfo protocolInfo;
	Socket::ParseAddress(host,port,SocketType::TCP,addressInfo,protocolInfo);
	mSocket.SetAddress(addressInfo);
	mSocket.SetProtocol(protocolInfo);

}

BaseSocketService::~BaseSocketService()
{

}


MEDUSA_END;
