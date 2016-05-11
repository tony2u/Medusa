// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Pattern/IUpdatable.h"
#include "InputDefines.h"
#include "Core/IO/FileId.h"
#include "Core/Pattern/Event.h"

MEDUSA_BEGIN;

typedef Delegate<void(InputState, InputState)> InputStateChangedHandler;
typedef Event<bool(INode* sender, IEventArg* e)> NodeInputEvent;
using NodeInputDelegate = NodeInputEvent::DelegateType;

class IInputHandler :public IUpdatable
{
public:
	Event<void(InputState, InputState)> StateChangedEvent;
public:
	IInputHandler(INode* node = nullptr) :mNode(node) {}
	virtual ~IInputHandler() { mNode = nullptr; }
	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void MockTouch(TouchEventArg& e) {}

	virtual void KeyDown(KeyDownEventArg& e);
	virtual void KeyUp(KeyUpEventArg& e);
	virtual void CharInput(CharInputEventArg& e);
	virtual void Scroll(ScrollEventArg& e);

	virtual void KeyboardWillShow(KeyboardEventArg& e);;
	virtual void KeyboardShowed(KeyboardEventArg& e);;

	virtual void KeyboardWillHide(KeyboardEventArg& e);;
	virtual void KeyboardHided(KeyboardEventArg& e);;

	virtual bool ShowKeyboard(INode* node) { return false; };
	virtual bool HideKeyboard(INode* node) { return false; };

	virtual void Reset() {}

	virtual InputType GetInputType()const { return InputType::None; }

	void CancelOtherHandlers();
	virtual bool NeedUpdate()const { return false; }

	FileIdRef AudioEffect() const { return mAudioEffect.ToRef(); }
	void SetAudioEffect(const FileIdRef& val) { mAudioEffect = val; }

	InputBehaviors Behaviors() const { return mBehaviors; }
	void SetBehaviors(InputBehaviors val) { mBehaviors = val; }
	void AddBehaviors(InputBehaviors val) { MEDUSA_FLAG_ADD(mBehaviors, val); }


	InputDispatcher* Dispatcher() const { return mDispatcher; }
	void SetDispatcher(InputDispatcher* val) { mDispatcher = val; }

	InputState State() const { return mState; }
	void SetState(InputState state);
	void Enable(bool val);
	virtual bool IsFocus()const { return mState == InputState::Valid; }

protected:
	bool RaiseEvent(InputEventType type, IEventArg* e=nullptr)const;
protected:
	InputDispatcher* mDispatcher = nullptr;
	
	INode* mNode = nullptr;
	FileId mAudioEffect;
	InputBehaviors mBehaviors = InputBehaviors::None;
	InputState mState = InputState::None;

};


MEDUSA_END;