// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NodeSweeper.h"
#include "Node/INode.h"

#ifdef MEDUSA_SAFE_CHECK
#include "Core/Log/Log.h"
#endif

MEDUSA_BEGIN;

#ifdef MEDUSA_SAFE_CHECK
void NodeSweeper::OnAddFailed(INode* item)const
{
	Log::AssertFailedFormat("Duplicate add dead node:{}", item->Name().c_str());
}
#endif


void NodeSweeper::OnRelease(INode* item)const
{
	if (item->Parent()!=nullptr)
	{
		item->DeleteFromParent();
	}
	else
	{
		delete item;
	}
}


MEDUSA_END;
