// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/INode.h"
#include "Node/Input/Gesture/EventArg/TapGestureEventArg.h"
#include "Node/Input/Gesture/IGestureRecognizer.h"

MEDUSA_BEGIN;

enum class ButtonState
{
	Normal = 0,
	Selected = 1,
	Disabled = 2,
	DisabledSelected = 3
};

class IButton :public INode
{
	MEDUSA_DECLARE_RTTI;
public:
	TapEvent OnTap;
public:
	IButton(StringRef name=StringRef::Empty);
	virtual ~IButton(void);
	virtual bool Initialize() override;

	bool IsDisabled() const { return mButtonState == ButtonState::Disabled || mButtonState == ButtonState::DisabledSelected; }
	void DisableButton(bool disable = true);
	void EnableButton(bool enable = true);


	bool IsSelected() const { return mButtonState == ButtonState::Selected || mButtonState == ButtonState::DisabledSelected; }
	void SetIsSelected(bool selected = true);

	ButtonState GetButtonState() const { return mButtonState; }
	void SetButtonState(ButtonState val);
protected:
	void OnTapStateChanged(InputState oldState, InputState newState);

	virtual void OnTapCallback(INode* sender,TapGestureEventArg& e);
	virtual void OnButtonStateChanged();
protected:
	TapGestureRecognizer* mRecognizer;
	ButtonState mButtonState;

};

MEDUSA_END;
