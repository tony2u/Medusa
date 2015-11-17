// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/InputManager.h"
#include "Core/Log/Log.h"
#include "Node/Input/InputDispatcher.h"
#include "Node/Scene/IScene.h"
#include "Node/Scene/SceneManager.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/EventArg/KeyboardEventArg.h"

#include "Core/Command/Processor/MainCommandProcessor.h"


MEDUSA_BEGIN;
InputManager::InputManager()
{
	mIsDirty = false;
	mFirstResponder = nullptr;
}

InputManager::~InputManager()
{
}


bool InputManager::Uninitialize()
{
	RETURN_FALSE_IF_FALSE(FrameTask::Uninitialize());
	mDispatchers.Clear();
	return true;
}


void InputManager::BecomeFirstResponder(INode* node)
{
	mFirstResponder = node;
}

void InputManager::CancelFirstResponder(INode* node)
{
	if (mFirstResponder==node)
	{
		mFirstResponder = nullptr;
	}
}


void InputManager::Register(INode* node)
{
	bool isSuccess = mDispatchers.TryAdd(node);
	if (isSuccess)
	{
		mIsDirty = true;
	}
}

void InputManager::Unregister(INode* node)
{
	bool isSuccess = mDispatchers.Remove(node);
	if (isSuccess)
	{
		mIsDirty = true;
	}
}


void InputManager::UpdateInputPassingRecursively()
{
	RETURN_IF_FALSE(mIsDirty);
	IScene* scene = SceneManager::Instance().RunningScene();
	scene->ResetInputPassing();

	FOR_EACH_COLLECTION(i, mDispatchers)
	{
		INode* node = *i;
		node->EnableInputPassing();
	}

	mIsDirty = false;


}


void InputManager::Reset()
{
	FOR_EACH_COLLECTION(i, mDispatchers)
	{
		INode* node = *i;
		node->MutableInput().Reset();
	}
}

void InputManager::OnUpdate(float dt)
{

}

bool InputManager::ShowKeyboard(INode* node)
{
	BecomeFirstResponder(node);

	UpdateInputPassingRecursively();
	IScene* scene = SceneManager::Instance().RunningScene();

	KeyboardEventArg e;
	KeyboardWillShowHelper(scene, e);
	KeyboardShowedHelper(scene, e);

	MainCommandProcessor::Instance().WaitForComplete();

	return true;
}

bool InputManager::HideKeyboard(INode* node)
{
	CancelFirstResponder(node);

	UpdateInputPassingRecursively();
	IScene* scene = SceneManager::Instance().RunningScene();
	KeyboardEventArg e;
	KeyboardWillHideHelper(scene, e);
	KeyboardHidedHelper(scene, e);

	MainCommandProcessor::Instance().WaitForComplete();

	return true;
}


void InputManager::TouchesBegan(TouchEventArg& e)
{
	if (mFirstResponder!=nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(mFirstResponder);
			dispatcher.TouchesBegan(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		TouchesBeganHelper(scene, e);
	}
	
	MainCommandProcessor::Instance().WaitForComplete();

}

void InputManager::TouchesMoved(TouchEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(mFirstResponder);
			dispatcher.TouchesMoved(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		TouchesMovedHelper(scene, e);
	}
	
	MainCommandProcessor::Instance().WaitForComplete();

}

void InputManager::TouchesEnded(TouchEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(mFirstResponder);
			dispatcher.TouchesEnded(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		TouchesEndedHelper(scene, e);
		if (e.IsAllTouchEnded())
		{
			Reset();
		}
	}

	MainCommandProcessor::Instance().WaitForComplete();

}

void InputManager::TouchesCancelled(TouchEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(mFirstResponder);
			dispatcher.TouchesCancelled(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		TouchesCancelledHelper(scene, e);
		Reset();
	}
	
	MainCommandProcessor::Instance().WaitForComplete();

}

void InputManager::KeyDown(KeyDownEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyDown(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		KeyDownHelper(scene, e);
	}

	MainCommandProcessor::Instance().WaitForComplete();
}

void InputManager::KeyUp(KeyUpEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyUp(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		KeyUpHelper(scene, e);
	}
	
	MainCommandProcessor::Instance().WaitForComplete();
}

void InputManager::CharInput(CharInputEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.CharInput(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		CharInputHelper(scene, e);
	}
	
	MainCommandProcessor::Instance().WaitForComplete();
}

void InputManager::Scroll(ScrollEventArg& e)
{
	if (mFirstResponder != nullptr)
	{
		InputDispatcher& dispatcher = mFirstResponder->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.Scroll(e);
		}
	}
	else
	{
		UpdateInputPassingRecursively();
		IScene* scene = SceneManager::Instance().RunningScene();
		ScrollHelper(scene, e);
	}

	
	MainCommandProcessor::Instance().WaitForComplete();
}

void InputManager::TouchesBeganHelper(INode* node, TouchEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();

	//Log::LogInfoFormat("Touch Began [{}]:{} %x",count,node->GetName().c_str(),node);

	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];

		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			//Log::LogInfoFormat("{} Touch Began {}:{} %x",i,child->LogicZ(),child->GetName().c_str(),child);

			TouchesBeganHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
			//Log::LogInfoFormat("{} Touch Ignore {}:{} %x",i,child->LogicZ(),child->GetName().c_str(),child);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(node);
			dispatcher.TouchesBegan(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];

		if (child->IsInputPassingEnabled())
		{
			//Log::LogInfoFormat("{} Touch Began Child<=0:{}",i,child->GetName().c_str());
			TouchesBeganHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
			//Log::LogInfoFormat("{} Touch Ignore Child<=0:{}",i,child->GetName().c_str());
		}

		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

}

void InputManager::TouchesMovedHelper(INode* node, TouchEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			TouchesMovedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(node);
			dispatcher.TouchesMoved(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TouchesMovedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::TouchesEndedHelper(INode* node, TouchEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();

	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			TouchesEndedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(node);
			dispatcher.TouchesEnded(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TouchesEndedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		else
		{
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}


void InputManager::TryFireEventHelper(INode* node, TouchEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			TryFireEventHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(node);
			dispatcher.TryFireEvent(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TryFireEventHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::TouchesCancelledHelper(INode* node, TouchEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			TouchesCancelledHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			e.UpdateValidActiveTouches(node);
			dispatcher.TouchesCancelled(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			TouchesCancelledHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::KeyDownHelper(INode* node, KeyDownEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			KeyDownHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyDown(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyDownHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::KeyUpHelper(INode* node, KeyUpEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			KeyUpHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyUp(e);
			RETURN_IF_TRUE(e.Handled);
		}

		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyUpHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::CharInputHelper(INode* node, CharInputEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			CharInputHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.CharInput(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			CharInputHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::ScrollHelper(INode* node, ScrollEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			ScrollHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.Scroll(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			ScrollHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::KeyboardWillShowHelper(INode* node, KeyboardEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			KeyboardWillShowHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyboardWillShow(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyboardWillShowHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::KeyboardShowedHelper(INode* node, KeyboardEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			KeyboardShowedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyboardShowed(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyboardShowedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::KeyboardWillHideHelper(INode* node, KeyboardEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			KeyboardWillHideHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyboardWillHide(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyboardWillHideHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}

void InputManager::KeyboardHidedHelper(INode* node, KeyboardEventArg& e)
{
	NodeList& nodeList = node->MutableChildren();
	size_t count = nodeList.Count();
	intp i = count - 1;
	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		BREAK_IF(child->LogicZ() < 0);

		if (child->IsInputPassingEnabled())
		{
			KeyboardHidedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}

	{
		InputDispatcher& dispatcher = node->MutableInput();
		if (dispatcher.HasHandler())
		{
			dispatcher.KeyboardHided(e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (node->IsModal())
		{
			e.Handled = true;
			return;
		}

	}

	for (; i >= 0; --i)
	{
		INode* child = nodeList[i];
		if (child->IsInputPassingEnabled())
		{
			KeyboardHidedHelper(child, e);
			RETURN_IF_TRUE(e.Handled);
		}
		if (child->IsModal())
		{
			e.Handled = true;
			return;
		}
	}
}




MEDUSA_END;