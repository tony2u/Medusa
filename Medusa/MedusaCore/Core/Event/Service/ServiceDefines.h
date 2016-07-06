// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

enum class ServiceIds
{

	UIMessage = 0,
	MockMessage = 1,

	TcpClient = 2,
	TcpShortClient = 3,

	TcpServer = 4,
	HttpServer = 5,	//not implement yet,could use tcp to simulate a http server

	Count = 6
};

enum class ServiceState
{
	Failed = -1,
	None = 0,
	Running = 1,

	StartPending = 2,
	StopPending = 3,
};

namespace ServicePropertyNames
{
	const extern StringRef Host;
	const extern StringRef Port;
	const extern StringRef Poller;
	const extern StringRef Connection;
	const extern StringRef ReadHandlers;
	const extern StringRef WriteHandlers;
	const extern StringRef ThreadCount;
	const extern StringRef IdleMilliseconds;
	const extern StringRef HeartbeatMilliseconds;





}

MEDUSA_END;
