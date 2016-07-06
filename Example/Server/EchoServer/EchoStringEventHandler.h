// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
USING_MEDUSA;
#include "Core/Event/Handler/IEventHandler.h"
#include "Core/String/String.h"
#include "Core/Memory/NetworkBuffer.h"


class EchoStringEventHandler :public EndReadEventHandler<HeapString>
{
	MEDUSA_RTTI(EchoStringEventHandler,IEventHandler);
protected:
	virtual bool OnRead(IEventHandlerContext* context, HeapString in)const;

};

