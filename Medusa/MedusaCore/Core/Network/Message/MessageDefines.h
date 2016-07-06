// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

enum class MessageError
{
	Success=0,
	ConnectFail=-1,
	Timeout = -2,


};

//None->ReadyForSend->Running->Completed/ConnectFail

enum class MessageState
{
	ConnectFail=-1,
	None=0,
	Running=2,
	Completed=3,
};

enum class MessageBehavior
{
	RequestResponse,
	RequestWithoutResponse,
	Response,
	HeartbeatWithoutResponse,
};


MEDUSA_END;
