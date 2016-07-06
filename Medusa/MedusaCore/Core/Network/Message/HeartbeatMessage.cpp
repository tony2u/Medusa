// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "HeartbeatMessage.h"
#include "Core/Log/Log.h"
#include "MessageFactory.h"

MEDUSA_BEGIN;


HeartbeatMessage::~HeartbeatMessage(void)
{
	
}

bool HeartbeatMessage::OnRequest(MessageSocketConnection&)
{
	Log::FormatInfo("Heartbeat");
	return true;
}

MEDUSA_IMPLEMENT_MESSAGE(HeartbeatMessage);

MEDUSA_END;