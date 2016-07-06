// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "LoginMessage.h"
#include "Core/Memory/NetworkBuffer.h"
#include "Core/Log/Log.h"
#include "Core/Network/Message/MessageFactory.h"


LoginMessage::LoginMessage()
{

}

LoginMessage::~LoginMessage(void)
{

}

bool LoginMessage::OnRequest(MessageSocketConnection& connection)
{
	BaseType::OnRequest(connection);
	this->mResponse.SetError(23);
	return true;
}

bool LoginMessage::OnResponse(MessageSocketConnection& connection)
{
	BaseType::OnResponse(connection);
	return true;
}

MEDUSA_IMPLEMENT_MESSAGE(LoginMessage);