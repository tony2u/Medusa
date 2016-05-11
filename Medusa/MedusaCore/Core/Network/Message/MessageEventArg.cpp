// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Network/Message/MessageEventArg.h"
MEDUSA_BEGIN;

MessageEventArg::MessageEventArg( IMessage* message ) :mMessage(message)
{
	SAFE_RETAIN(mMessage);
}

MessageEventArg::MessageEventArg( const MessageEventArg& e )
{
	mMessage=e.mMessage;
	SAFE_RETAIN(mMessage);
}

MessageEventArg::~MessageEventArg(void)
{
	SAFE_RELEASE(mMessage);
}

MEDUSA_END;
