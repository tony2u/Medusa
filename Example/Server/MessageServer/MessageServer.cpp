// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#include "Core/Log/Log.h"
#include "Core/Event/Poll/SelectPoller.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/Network/Service/TTcpServerMessageService.h"
#include "Core/Event/EventBus.h"
#include "Core/System/Console.h"
#include "Message/LoginMessage.h"
#include "Core/Network/Message/MessageFactory.h"
#include "Core/IO/FileId.h"
#include "Core/Database/SqlClient.h"
#include "Core/Network/Message/MessageSocketConnection.h"


USING_MEDUSA;
using ServerService = TTcpServerMessageService<MessageSocketConnection>;

int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize(true);
	//Log::AddLogger(new WindowsConsoleLogger());
	Log::EnableHeader(false);

	ServerService* service = EventBus::Instance().Register<ServerService>("Port=9013,IdleMilliseconds=60000,Poller=SelectPoller");
	auto& server = service->Server();

	server.OnStartListening += [](ServerService::ServerType& server)
	{
		Log::FormatInfo("Listening {}:{}", server.Host(), server.Port());
	};

	server.OnNewConnection += [](MessageSocketConnection& conn)
	{
		Log::FormatInfo("Accept:{}", conn.ToString());
	};

	server.OnConnectionClose += [](MessageSocketConnection& conn)
	{
		Log::FormatInfo("Close:{}", conn.ToString());
	};


	EventBus::Instance().Start();


	Console::Instance().OnCtrlC += [] {exit(0); };

	while (true)
	{
		if (false)
		{
			char c = Console::Instance().ReadChar();
			if (c == 'q')
			{
				break;
			}
		}
		else
		{
			Log::Update();
			Thread::Sleep(10);
		}
	}

	return 0;
}

