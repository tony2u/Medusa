// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

#include "Core/Log/Log.h"
#include "Core/Network/Socket/TcpServer.h"
#include "Core/Network/Socket/Connection/SocketConnection.h"

#include "EchoStringEventHandler.h"
#include "Core/Event/Poll/SelectPoller.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/Network/Socket/Handler/StringToBufferEventHandler.h"
#include "Core/Network/Socket/Handler/BufferToStringEventHandler.h"
#include "Core/Network/Service/TcpServerMessageService.h"
#include "Core/Event/EventBus.h"
#include "Core/System/Console.h"


USING_MEDUSA;

int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize();
	Log::AddLogger(new WindowsConsoleLogger());
	Log::EnableHeader(false);

	EventHandlerFactory::Instance().Register<EchoStringEventHandler>();
	TcpServerMessageService* service = EventBus::Instance().Register<TcpServerMessageService>("Host=127.0.0.1,Port=9013,IdleMilliseconds=60000,Poller=SelectPoller,Connection=SocketConnection,ReadHandlers=BufferToStringEventHandler;EchoStringEventHandler,WriteHandlers=StringToBufferEventHandler");
	auto& server = service->Server();

	server.OnStartListening += [](TcpServer& server)
	{
		Log::FormatInfo("Listening {}:{}", server.Host(), server.Port());
	};

	server.OnNewConnection += [](SocketConnection& conn)
	{
		Log::FormatInfo("Accept:{}", conn.ToString());
	};

	server.OnConnectionClose += [](SocketConnection& conn)
	{
		Log::FormatInfo("Close:{}", conn.ToString());
	};


	EventBus::Instance().Start();
	Console::Instance().OnCtrlC += [] {exit(0); };

	while (true)
	{
		if (Console::Instance().IsKeyboardHit())
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

