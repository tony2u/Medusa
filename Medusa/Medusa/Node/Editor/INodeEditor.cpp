// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "INodeEditor.h"


MEDUSA_BEGIN;

NodeCreateFlags INodeEditor::GetChildrenCreateFlags(NodeCreateFlags val)
{
	if (MEDUSA_FLAG_HAS(val,NodeCreateFlags::BindScriptRecursively))
	{
		return val;
	}

	if (MEDUSA_FLAG_HAS(val, NodeCreateFlags::BindScriptSelf))
	{
		MEDUSA_FLAG_REMOVE(val, NodeCreateFlags::BindScriptSelf);
	}

	if (MEDUSA_FLAG_HAS(val, NodeCreateFlags::BindScriptChildren))
	{
		MEDUSA_FLAG_ADD(val, NodeCreateFlags::BindScriptSelf);
	}

	return val;
	
}

MEDUSA_END;
