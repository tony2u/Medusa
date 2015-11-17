// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/IInputHandler.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"


MEDUSA_BEGIN;

class IMEHandler:public IInputHandler
{
public:
	KeyDownEvent OnKeyDown;
	KeyUpEvent OnKeyUp;
	CharInputEvent OnCharInput;
public:
	IMEHandler(INode* node);
	virtual ~IMEHandler(void);
	virtual InputType GetInputType()const override{ return InputType::IME; }

	virtual void KeyDown(KeyDownEventArg& e) override;
	virtual void KeyUp(KeyUpEventArg& e) override;
	virtual void CharInput(CharInputEventArg& e) override;
};



MEDUSA_END;