// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IInputHandler.h"
#include "Node/INode.h"
#include "Node/Input/InputDispatcher.h"

MEDUSA_BEGIN;

void IInputHandler::CancelOtherHandlers()
{
	if (mNode != nullptr)
	{
		mNode->MutableInput().CancelOtherHandlers(this);
	}
}

MEDUSA_END;