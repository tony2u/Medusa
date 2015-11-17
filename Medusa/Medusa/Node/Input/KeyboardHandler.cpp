// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "KeyboardHandler.h"
#include "Node/INode.h"

MEDUSA_BEGIN;


KeyboardHandler::KeyboardHandler(INode* node) :IInputHandler(node)
{

}

KeyboardHandler::~KeyboardHandler( void )
{

}

void KeyboardHandler::KeyboardWillShow(KeyboardEventArg& e)
{
	OnWillShow(mNode, e);
}

void KeyboardHandler::KeyboardShowed(KeyboardEventArg& e)
{
	OnShowed(mNode, e);
}

void KeyboardHandler::KeyboardWillHide(KeyboardEventArg& e)
{
	OnWillHide(mNode, e);
}

void KeyboardHandler::KeyboardHided(KeyboardEventArg& e)
{
	OnHided(mNode, e);
}

MEDUSA_END;
