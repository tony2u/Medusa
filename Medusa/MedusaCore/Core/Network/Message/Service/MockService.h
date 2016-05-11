// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "IService.h"

MEDUSA_BEGIN;

class MockService:public IService
{
public:
	MockService(size_t id, StringRef host, ushort port);
	virtual ~MockService();
	virtual ServiceType Type()const override { return ServiceType::Mock; }

};
MEDUSA_END;
