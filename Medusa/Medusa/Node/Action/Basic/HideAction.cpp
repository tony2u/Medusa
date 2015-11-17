// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "HideAction.h"
#include "Node/INode.h"
#include "ShowAction.h"

MEDUSA_BEGIN;

HideAction::HideAction():BaseInstantAction()
{
}


HideAction::~HideAction(void)
{
}


bool HideAction::OnAction()
{
	INode* node = (INode*)mTarget;
	node->SetVisible(false);
	return true;
}

HideAction* HideAction::Create()
{
	return new HideAction();
}

HideAction* HideAction::Clone() const 
{
	return new HideAction();
}

IAction* HideAction::Reverse() const 
{
	return new ShowAction();
}

MEDUSA_END;
