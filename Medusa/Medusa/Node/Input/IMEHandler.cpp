// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IMEHandler.h"
#include "Node/INode.h"

MEDUSA_BEGIN;

IMEHandler::IMEHandler( INode* node ) 
	:IInputHandler(node)
{

}
IMEHandler::~IMEHandler(void)
{
	
}

void IMEHandler::KeyDown(KeyDownEventArg& e)
{
	IInputHandler::KeyDown(e);
	OnKeyDown(mNode, e);
}

void IMEHandler::KeyUp(KeyUpEventArg& e)
{
	IInputHandler::KeyUp(e);
	OnKeyUp(mNode, e);
}

void IMEHandler::CharInput(CharInputEventArg& e)
{
	IInputHandler::CharInput(e);
	OnCharInput(mNode, e);
}



MEDUSA_END;