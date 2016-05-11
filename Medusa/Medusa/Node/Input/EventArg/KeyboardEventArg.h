// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Command/EventArg/IEventArg.h"
#include "Geometry/Rect2.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

class KeyboardEventArg:public IEventArg
{
	MEDUSA_DECLARE_RTTI;
public:
	KeyboardEventArg(){}
	virtual ~KeyboardEventArg(void){}

protected:
	Rect2F mBegin;	// the soft keyboard rectangle when animation begins
	Rect2F mEnd;	// the soft keyboard rectangle when animation ends
	float mDuration;	// the soft keyboard animation duration
};

//[PRE_DECLARE_BEGIN]
typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardWillShowDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardWillShowEvent;

typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardShowedDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardShowedEvent;

typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardWillHideDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardWillHideEvent;

typedef Delegate<void(INode* sender, KeyboardEventArg&)> KeyboardHidedDelegate;
typedef Event<void(INode* sender, KeyboardEventArg&)> KeyboardHidedEvent;
//[PRE_DECLARE_END]

MEDUSA_END;