// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IService.h"

MEDUSA_BEGIN;

IService::IService(size_t id, StringRef host, ushort port)
	:mId(id),mHost(host),mPort(port)
{

}

IService::~IService()
{
}

void IService::Submit( IMessage* message )
{
	SAFE_RETAIN(message);
	mMessageQueue.Push(message);
}



MEDUSA_END;
