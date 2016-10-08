// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IButton.h"
#include "Node/Input/Gesture/TapGestureRecognizer.h"
#include "Node/Input/InputDispatcher.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;



IButton::IButton(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/) 
	:INode(name,e), mButtonState(ButtonState::Normal)
{
	mRecognizer=MutableInput().AddTapGestureHandler(Bind(&IButton::OnTapCallback, this));
	mRecognizer->StateChangedEvent+=Bind(&IButton::OnTapStateChanged,this);
	MutableInput().EnableSwallow(true);
	MutableInput().Enable(true);


}

IButton::~IButton( void )
{

}

bool IButton::Initialize()
{
	return true;
}

void IButton::OnTapCallback(INode* sender,TapGestureEventArg& e)
{
	OnTap(sender,e);
}

void IButton::OnTapStateChanged(InputState oldState,InputState newState)
{
	switch (newState)
	{
		case InputState::Begin:
			SetButtonState(IsDisabled() ? ButtonState::DisabledSelected : ButtonState::Selected);
			break;
		case InputState::End:
			SetButtonState(IsDisabled() ? ButtonState::Disabled : ButtonState::Normal);
			break;
		case InputState::None:
			SetButtonState(IsDisabled() ? ButtonState::Disabled : ButtonState::Normal);
			break;
		default:
			break;
	}
}

void IButton::SetButtonState(ButtonState val)
{
	RETURN_IF_EQUAL(mButtonState, val);

	mButtonState = val;
	OnButtonStateChanged();
}


void IButton::DisableButton(bool disable /*= true*/)
{
	if (disable)
	{
		RETURN_IF(IsDisabled());
		SetButtonState(mButtonState == ButtonState::Normal ? ButtonState::Disabled : ButtonState::DisabledSelected);
	}
	else
	{
		RETURN_IF(!IsDisabled());
		SetButtonState(mButtonState == ButtonState::Disabled ? ButtonState::Normal : ButtonState::Selected);
	}
}

void IButton::EnableButton(bool enable /*= true*/)
{
	if (enable)
	{
		RETURN_IF(!IsDisabled());
		SetButtonState(mButtonState == ButtonState::Disabled ? ButtonState::Normal : ButtonState::Selected);
	}
	else
	{
		RETURN_IF(IsDisabled());
		SetButtonState(mButtonState == ButtonState::Normal ? ButtonState::Disabled : ButtonState::DisabledSelected);
	}
}

void IButton::SetIsSelected(bool selected /*= true*/)
{
	if (selected)
	{
		RETURN_IF(IsSelected());
		SetButtonState(mButtonState == ButtonState::Normal ? ButtonState::Selected : ButtonState::DisabledSelected);
	}
	else
	{
		RETURN_IF(!IsSelected());
		SetButtonState(mButtonState == ButtonState::Selected ? ButtonState::Normal : ButtonState::Disabled);
	}
}

void IButton::OnButtonStateChanged()
{

}


MEDUSA_END;
