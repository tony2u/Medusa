// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "NodeScriptComponent.h"
#include "Core/Pattern/Component/ComponentFactory.h"
#include "Core/Log/Log.h"
#include "Node/INode.h"

#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/EventArg/KeyboardEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"

MEDUSA_BEGIN;

NodeScriptComponent::NodeScriptComponent(const StringRef& name /*= StringRef::Empty*/, int priority/* = 0*/, void* userData /*= nullptr*/)
	:IScriptComponent(name, priority, userData)
{
}

NodeScriptComponent::~NodeScriptComponent(void)
{

}

bool NodeScriptComponent::Update(float dt)
{
	return mUpdateMethod.Invoke<bool>(mScriptObject, dt);
}

bool NodeScriptComponent::HandleEvent(InputEventType type, StringRef handlerName, INode* sender, IEventArg* e)
{
	switch (type)
	{
	case InputEventType::None:
		break;
	case InputEventType::TouchBegan:
	case InputEventType::TouchMoved:
	case InputEventType::TouchEnded:
	case InputEventType::TouchCancelled:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (TouchEventArg*)e);
		break;
	case InputEventType::KeyDown:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (KeyDownEventArg*)e);
		break;
	case InputEventType::KeyUp:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (KeyUpEventArg*)e);
		break;
	case InputEventType::CharInput:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (CharInputEventArg*)e);
		break;
	case InputEventType::Scroll:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (ScrollEventArg*)e);
		break;
	case InputEventType::KeyboardWillShow:
	case InputEventType::KeyboardShowed:
	case InputEventType::KeyboardWillHide:
	case InputEventType::KeyboardHided:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (KeyboardEventArg*)e);
		break;
	case InputEventType::Tap:
	case InputEventType::TapFailed:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (TapGestureEventArg*)e);
		break;
	case InputEventType::DoubleTap:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (DoubleTapGestureEventArg*)e);
		break;
	case InputEventType::DragBegan:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (DragBeganGestureEventArg*)e);
		break;
	case InputEventType::Draging:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (DragingGestureEventArg*)e);
		break;
	case InputEventType::DragEnd:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (DragEndGestureEventArg*)e);
		break;
	case InputEventType::DragFailed:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (DragFailedGestureEventArg*)e);
		break;
	case InputEventType::LongPressBegan:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (LongPressBeganGestureEventArg*)e);
		break;
	case InputEventType::LongPressFailed:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (LongPressFailedGestureEventArg*)e);
		break;
	case InputEventType::PanBegin:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (PanBeginGestureEventArg*)e);
		break;
	case InputEventType::Pan:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (PanGestureEventArg*)e);
		break;
	case InputEventType::PanEnd:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (PanEndGestureEventArg*)e);
		break;
	case InputEventType::Pinch:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (PinchGestureEventArg*)e);
		break;
	case InputEventType::SwipeBegin:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (SwipeBeginGestureEventArg*)e);
		break;
	case InputEventType::SwipeMoved:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (SwipeMovedGestureEventArg*)e);
		break;
	case InputEventType::SwipeFailed:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (SwipeFailedGestureEventArg*)e);
		break;
	case InputEventType::SwipeSuccess:
		return mScriptObject.InvokeMember<bool>(handlerName, sender, (SwipeSuccessGestureEventArg*)e);
		break;
	default:
		break;
	}
	return true;
}

bool NodeScriptComponent::Enter()
{
	return mEnterMethod.Invoke<bool>(mScriptObject);
}

bool NodeScriptComponent::Exit()
{
	return mExitMethod.Invoke<bool>(mScriptObject);
}

bool NodeScriptComponent::UpdateLogic()
{
	return mUpdateLogicMethod.Invoke<bool>(mScriptObject);
}

bool NodeScriptComponent::ResetLogic()
{
	return mResetLogicMethod.Invoke<bool>(mScriptObject);
}

bool NodeScriptComponent::HasMethod(StringRef name) const
{
	return mScriptObject.Has(name);
}

void NodeScriptComponent::OnScriptObjectChanged()
{
	INode* node = (INode*)mEntity;

#ifdef MEDUSA_LUA
	LuaCustomObjectPtr<INode> ptr{ node,node->ClassName() };
	mScriptObject.Rawset(LuaNames::Node, ptr);
#endif

	mUpdateMethod = mScriptObject.Get("Update");
	Log::Assert(mUpdateMethod != nullptr, "Cannot find NodeScriptComponent method:Update");
	mEnterMethod = mScriptObject.Get("Enter");
	Log::Assert(mEnterMethod != nullptr, "Cannot find NodeScriptComponent method:Enter");
	mExitMethod = mScriptObject.Get("Exit");
	Log::Assert(mExitMethod != nullptr, "Cannot find NodeScriptComponent method:Exit");

	mUpdateLogicMethod = mScriptObject.Get("UpdateLogic");
	Log::Assert(mUpdateLogicMethod != nullptr, "Cannot find NodeScriptComponent method:UpdateLogic");

	mResetLogicMethod = mScriptObject.Get("ResetLogic");
	Log::Assert(mResetLogicMethod != nullptr, "Cannot find NodeScriptComponent method:ResetLogic");

}

MEDUSA_IMPLEMENT_COMPONENT(NodeScriptComponent, IScriptComponent);

MEDUSA_END;

#endif