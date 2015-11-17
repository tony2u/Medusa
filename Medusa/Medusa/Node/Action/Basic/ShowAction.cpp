// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShowAction.h"
#include "Node/INode.h"
#include "HideAction.h"

MEDUSA_BEGIN;

ShowAction::ShowAction():BaseInstantAction()
{
}


ShowAction::~ShowAction(void)
{
}


bool ShowAction::OnAction()
{
	INode* node = (INode*)mTarget;
	node->SetVisible(true);
	return true;
}

ShowAction* ShowAction::Create()
{
	return new ShowAction();
}

ShowAction* ShowAction::Clone() const 
{
	return new ShowAction();
}

IAction* ShowAction::Reverse() const 
{
	return new HideAction();
}

MEDUSA_END;
