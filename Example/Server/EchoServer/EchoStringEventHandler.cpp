// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#include "EchoStringEventHandler.h"
#include "Core/Network/Socket/Handler/SocketConnectionEventHandlerContext.h"
#include "Core/Network/Socket/Connection/SocketConnection.h"
#include "Core/Log/Log.h"
#include "Core/Event/Loop/EventLoop.h"
#include "Core/Network/Socket/TcpServer.h"

bool EchoStringEventHandler::OnRead(IEventHandlerContext* context, HeapString in) const
{
	SocketConnectionEventHandlerContext* tcpConext = (SocketConnectionEventHandlerContext*)context;
	auto& conn = tcpConext->Connection();
	Log::FormatInfo("{}-Receive:{}", conn.Id(), in);
	conn.Write(in);
	Log::FormatInfo("{}-Send:{}", conn.Id(), in);

	/*TcpServer* server = (TcpServer*)conn.Peer();
	Log::FormatInfo("{}-Receive:{}", conn.Id(), in);
	server->Broadcast(conn.Id(), in);
	Log::FormatInfo("Broadcast:{}",  in);*/

	return true;
}

