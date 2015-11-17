// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Pattern/IUpdatable.h"

MEDUSA_BEGIN;

enum class InputType
{
	None = -1,
	Tap = 0,			
	Pinch = 1,		
	Rotation = 2,		
	Swipe = 3,		
	Pan = 4,			
	LongPress = 5,	
	Drag = 6,
	DoubleTap = 7,

	IME = 8,
	Keyboard = 9,

	Size = 10
};

class IInputHandler :public IUpdatable
{
public:
	IInputHandler(INode* node = nullptr) :mNode(node){}
	virtual ~IInputHandler(){ mNode = nullptr; }
	virtual void TouchesBegan(TouchEventArg& e){}
	virtual void TouchesMoved(TouchEventArg& e){}
	virtual void TouchesEnded(TouchEventArg& e){}
	virtual void TouchesCancelled(TouchEventArg& e){}
	virtual void TryFireEvent(TouchEventArg& e){}


	virtual void KeyDown(KeyDownEventArg& e){}
	virtual void KeyUp(KeyUpEventArg& e){}
	virtual void CharInput(CharInputEventArg& e){}
	virtual void Scroll(ScrollEventArg& e){}

	virtual void KeyboardWillShow(KeyboardEventArg& e){};
	virtual void KeyboardShowed(KeyboardEventArg& e){};

	virtual void KeyboardWillHide(KeyboardEventArg& e){};
	virtual void KeyboardHided(KeyboardEventArg& e){};

	virtual bool ShowKeyboard(INode* node) { return false; };
	virtual bool HideKeyboard(INode* node) { return false; };

	virtual void Reset(){}
	virtual bool IsFocus()const{ return false; }

	virtual InputType GetInputType()const { return InputType::None; }

	void CancelOtherHandlers();
	virtual bool NeedUpdate()const { return false; }
protected:
	INode* mNode;
};


MEDUSA_END;