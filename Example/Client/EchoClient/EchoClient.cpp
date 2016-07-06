// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "Core/Network/Socket/TcpClient.h"
#include "Core/Log/Log.h"
#include "Core/Network/Socket/Connection/SocketConnection.h"
#include "Core/Network/Socket/Handler/StringToBufferEventHandler.h"
#include "PrintStringEventHandler.h"
#include "Core/Event/Poll/SelectPoller.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/Network/Socket/Handler/BufferToStringEventHandler.h"
#include "Core/System/Console.h"
#include "Core/Network/Service/TcpClientMessageService.h"
#include "Core/Event/EventBus.h"

USING_MEDUSA;


int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize();
	Log::AddLogger(new WindowsConsoleLogger());
	Log::EnableHeader(false);

	EventHandlerFactory::Instance().Register<PrintStringEventHandler>();
	TcpClientMessageService* service = EventBus::Instance().Register<TcpClientMessageService>("Host=127.0.0.1,Port=9013,Poller=SelectPoller,Connection=SocketConnection,ReadHandlers=BufferToStringEventHandler;PrintStringEventHandler,WriteHandlers=StringToBufferEventHandler");
	auto& client = service->Client();

	client.OnStartConnecting += [](TcpClient& client)
	{
		Log::FormatInfo("Connecting {}", client.RemoteAddress());
	};

	client.OnConnected += [](SocketConnection& conn)
	{
		Log::FormatInfo("Connected:{}", conn.ToString());
	};

	client.OnDisconnected += [](SocketConnection& conn)
	{
		Log::FormatInfo("Disconnect:{}", conn.ToString());
	};

	EventBus::Instance().Start();
	Console::Instance().OnCtrlC += [] {exit(0); };
	HeapString str;
	while (true)
	{
		if (Console::Instance().IsKeyboardHit())
		{
			char c=Console::Instance().ReadChar();
			putchar(c);
			if (c!='\n'&&c!='\r')
			{
				str += c;
			}
			else
			{
				putchar('\n');
				client.Write(str);
				Log::FormatInfo("Send:{}", str);
				str.Clear();
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

