// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/String/StringRef.h"
#include "Core/Message/Handler/IMessageHandler.h"
#include "Core/Message/Handler/TcpMessageHandler.h"
#include "Core/Message/Handler/MockMessageHandler.h"
#include "Core/Config/ServerType.h"

MEDUSA_BEGIN;


class MessageHandlerFactory :public MapObjectFactory<ServerType, IMessageHandler*(size_t, StringRef, ushort, uint, uint, uint, CoderType, CoderType, const MemoryByteData&)>
{
public:
	using MapObjectFactory<ServerType, IMessageHandler*(size_t, StringRef, ushort, uint, uint, uint, CoderType, CoderType, const MemoryByteData&)>::Create;
private:
	MessageHandlerFactory()
	{
		Register<TcpMessageHandler>(ServerType::Tcp);
		Register<MockMessageHandler>(ServerType::Mock);
	}
	~MessageHandlerFactory(){}
public:
	static MessageHandlerFactory& Instance()
	{
		static MessageHandlerFactory factory;
		return factory;
	}



};

MEDUSA_END;
