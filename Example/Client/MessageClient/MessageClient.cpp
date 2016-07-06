// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
//
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include "Core/Log/Log.h"
#include "Core/Log/win/WindowsConsoleLogger.h"
#include "Core/System/Console.h"
#include "Core/Network/Service/TTcpClientMessageService.h"
#include "Core/Event/EventBus.h"
#include "Message/LoginMessage.h"
#include "Core/Pattern/Share.h"
#include "Core/Network/Message/MessageSocketConnection.h"

USING_MEDUSA;

bool isConnected = false;
using ClientService = TTcpClientMessageService<MessageSocketConnection>;
int _tmain(int argc, _TCHAR* argv[])
{
	Log::Initialize(true);
	//Log::AddLogger(new WindowsConsoleLogger());
	Log::EnableHeader(false);

	ClientService* service = EventBus::Instance().Register<ClientService>("Host=127.0.0.1,Port=9013,Poller=SelectPoller");
	auto& client = service->Client();

	client.OnStartConnecting += [](ClientService::ClientType& client)
	{
		Log::FormatInfo("Connecting {}", client.RemoteAddress());
	};

	client.OnConnected += [](MessageSocketConnection& conn)
	{
		Log::FormatInfo("Connected:{}", conn.ToString());
		isConnected = true;
	};

	client.OnDisconnected += [](MessageSocketConnection& conn)
	{
		Log::FormatInfo("Disconnect:{}", conn.ToString());
	};

	EventBus::Instance().Start();
	Console::Instance().OnCtrlC += [] {exit(0); };
	HeapString str;

	StopWatch mWatch;
	mWatch.Start();
	while (true)
	{
		if (false)
		{
			char c = Console::Instance().ReadChar();
			putchar(c);
			if (c != '\n'&&c != '\r')
			{
				str += c;
			}
			else
			{
				putchar('\n');
				//client.Write(str);
				Log::FormatInfo("Send:{}", str);
				str.Clear();
			}
		}
		else
		{
			Log::Update();
			mWatch.Shot();
			if (isConnected&&mWatch.ElapsedMilliseconds() > 1000.f / 10)
			{
				mWatch.Go();

				FOR_EACH_SIZE(i, 1)
				{
					Share<LoginMessage> loginMessage = new LoginMessage();
					loginMessage->MutableRequest().SetName("Hello");
					loginMessage->MutableRequest().SetOrder(123);
					client.Write(loginMessage.To<ShareMessage>());
				}
				
				//isConnected = false;
			}
			else
			{
				Thread::Sleep(1);
			}

		}
	}



	return 0;
}

