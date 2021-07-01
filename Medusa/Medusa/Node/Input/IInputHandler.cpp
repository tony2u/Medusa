// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IInputHandler.h"
#include "Node/INode.h"
#include "Node/Input/InputDispatcher.h"
#include "Application/Settings/ApplicationSettings.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/EventArg/KeyboardEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"

MEDUSA_BEGIN;

void IInputHandler::TouchesBegan(TouchEventArg& e)
{
	RaiseEvent(InputEventType::TouchBegan, &e);
}

void IInputHandler::TouchesMoved(TouchEventArg& e)
{
	RaiseEvent(InputEventType::TouchMoved, &e);
}

void IInputHandler::TouchesEnded(TouchEventArg& e)
{
	RaiseEvent(InputEventType::TouchEnded, &e);
}

void IInputHandler::TouchesCancelled(TouchEventArg& e)
{
	RaiseEvent(InputEventType::TouchCancelled, &e);
}

void IInputHandler::KeyDown(KeyDownEventArg& e)
{
	RaiseEvent(InputEventType::KeyDown, &e);
}

void IInputHandler::KeyUp(KeyUpEventArg& e)
{
	RaiseEvent(InputEventType::KeyUp, &e);
}

void IInputHandler::CharInput(CharInputEventArg& e)
{
	RaiseEvent(InputEventType::CharInput, &e);
}

void IInputHandler::Scroll(ScrollEventArg& e)
{
	RaiseEvent(InputEventType::Scroll, &e);
}

void IInputHandler::KeyboardWillShow(KeyboardEventArg& e)
{
	RaiseEvent(InputEventType::KeyboardWillShow, &e);
}

void IInputHandler::KeyboardShowed(KeyboardEventArg& e)
{
	RaiseEvent(InputEventType::KeyboardShowed, &e);
}

void IInputHandler::KeyboardWillHide(KeyboardEventArg& e)
{
	RaiseEvent(InputEventType::KeyboardWillHide, &e);
}

void IInputHandler::KeyboardHided(KeyboardEventArg& e)
{
	RaiseEvent(InputEventType::KeyboardHided, &e);
}

void IInputHandler::CancelOtherHandlers()
{
	if (mNode != nullptr)
	{
		mNode->MutableInput().CancelOtherHandlers(this);
	}
}


void IInputHandler::Enable(bool val)
{
	SetState(val ? InputState::None : InputState::Disabled);
}

bool IInputHandler::RaiseEvent(InputEventType type, IEventArg* e/*=nullptr*/) const
{
	if (mNode && !MEDUSA_FLAG_HAS(mBehaviors, InputBehaviors::DisableEventBinding))
	{
		//switch type
		mDispatcher->FireEvent(type, mNode, e);
	}

#ifdef MEDUSA_SCRIPT
	if (mNode && ApplicationSettings::Instance().HasScriptBinding() && !MEDUSA_FLAG_HAS(mBehaviors, InputBehaviors::DisableScriptBinding))
	{
		mDispatcher->FireScriptBinding(type, mNode, e);
	}
#endif


	return nullptr;
}

void IInputHandler::SetState(InputState state)
{
	RETURN_IF_EQUAL(mState, state);
	StateChangedEvent(mState, state);
	mState = state;
}

MEDUSA_END;
