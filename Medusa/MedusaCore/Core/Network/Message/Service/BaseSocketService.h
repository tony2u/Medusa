// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Network/Socket/Socket.h"
#include "BaseThreadService.h"

MEDUSA_BEGIN;

class BaseSocketService:public BaseThreadService
{
public:
	BaseSocketService(size_t id, StringRef host, ushort port);
	virtual ~BaseSocketService();
public:
protected:
	Socket mSocket;
};
MEDUSA_END;
