// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Node/Input/IInputHandler.h"
#include "Node/Input/EventArg/KeyboardEventArg.h"

MEDUSA_BEGIN;

class KeyboardHandler:public IInputHandler
{
public:
	KeyboardWillShowEvent OnWillShow;
	KeyboardShowedEvent OnShowed;

	KeyboardWillHideEvent OnWillHide;
	KeyboardHidedEvent OnHided;
public:
	KeyboardHandler(INode* node);
	virtual ~KeyboardHandler(void);
	virtual InputType GetInputType()const override{ return InputType::Keyboard; }
public:

	virtual void KeyboardWillShow(KeyboardEventArg& e)override;
	virtual void KeyboardShowed(KeyboardEventArg& e)override;

	virtual void KeyboardWillHide(KeyboardEventArg& e)override;
	virtual void KeyboardHided(KeyboardEventArg& e)override;


};

MEDUSA_END;
