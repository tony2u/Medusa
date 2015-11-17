// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "DeleteSelfAction.h"
#include "Node/INode.h"
#include "Node/NodeSweeper.h"

MEDUSA_BEGIN;

DeleteSelfAction::DeleteSelfAction():BaseInstantAction()
{
}


DeleteSelfAction::~DeleteSelfAction(void)
{
}


bool DeleteSelfAction::OnAction()
{
	INode* node = (INode*)mTarget;
	NodeSweeper::Instance().Add(node);
	return true;
}

DeleteSelfAction* DeleteSelfAction::Create()
{
	return new DeleteSelfAction();
}

DeleteSelfAction* DeleteSelfAction::Clone() const 
{
	return new DeleteSelfAction();
}

IAction* DeleteSelfAction::Reverse() const 
{
	return new DeleteSelfAction();
}

MEDUSA_END;
