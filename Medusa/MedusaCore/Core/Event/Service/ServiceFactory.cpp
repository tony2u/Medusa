// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ServiceFactory.h"
#include "Core/Network/Service/MockMessageService.h"
#include "Core/Network/Service/UIMessageService.h"


MEDUSA_BEGIN;

ServiceFactory::ServiceFactory()
{
	//auto register
	Register<MockMessageService>();
	Register<UIMessageService>();
}

MEDUSA_END;
