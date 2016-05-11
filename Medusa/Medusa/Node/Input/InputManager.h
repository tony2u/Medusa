// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/IInputHandler.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/HashSet.h"
#include "Core/Task/FrameTask.h"

MEDUSA_BEGIN;

class InputManager:public Singleton<InputManager>,public IInputHandler,public FrameTask
{
	friend class Singleton<InputManager>;
	InputManager();
	~InputManager();

	virtual bool Uninitialize()override;
public:
	void BecomeFirstResponder(INode* node);
	void CancelFirstResponder(INode* node);


	void Register(INode* node);
	void Unregister(INode* node);

	void SetDirty() { mIsDirty = true; }
	virtual void Reset()override;


	virtual void TouchesBegan(TouchEventArg& e)override;
	virtual void TouchesMoved(TouchEventArg& e)override;
	virtual void TouchesEnded(TouchEventArg& e)override;
	virtual void TouchesCancelled(TouchEventArg& e)override;
	virtual void KeyDown(KeyDownEventArg& e)override;
	virtual void KeyUp(KeyUpEventArg& e)override;
	virtual void CharInput(CharInputEventArg& e)override;
	virtual void Scroll(ScrollEventArg& e)override;

	virtual bool ShowKeyboard(INode* node)override;
	virtual bool HideKeyboard(INode* node)override;

protected:
	virtual void OnUpdate(float dt)override;

private:
	void UpdateInputPassingRecursively();

	void TouchesBeganHelper(INode* node,TouchEventArg& e);
	void TouchesMovedHelper(INode* node,TouchEventArg& e);
	void TouchesEndedHelper(INode* node,TouchEventArg& e);
	void TouchesCancelledHelper(INode* node,TouchEventArg& e);
	void MockTouchHelper(INode* node,TouchEventArg& e);
	
	void KeyDownHelper(INode* node,KeyDownEventArg& e);
	void KeyUpHelper(INode* node,KeyUpEventArg& e);
	void CharInputHelper(INode* node,CharInputEventArg& e);
	void ScrollHelper(INode* node,ScrollEventArg& e);

	void KeyboardWillShowHelper(INode* node, KeyboardEventArg& e);
	void KeyboardShowedHelper(INode* node, KeyboardEventArg& e);
	void KeyboardWillHideHelper(INode* node, KeyboardEventArg& e);
	void KeyboardHidedHelper(INode* node, KeyboardEventArg& e);

private:
	INode* mFirstResponder=nullptr;

	HashSet<INode*> mDispatchers;
	bool mIsDirty;
};


MEDUSA_END;