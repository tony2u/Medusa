// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/InputManager.h"

#include "Node/Input/Gesture/TapGestureRecognizer.h"
#include "Node/Input/Gesture/DragGestureRecognizer.h"
#include "Node/Input/Gesture/LongPressGestureRecognizer.h"
#include "Node/Input/Gesture/PanGestureRecognizer.h"
#include "Node/Input/Gesture/PinchGestureRecognizer.h"
#include "Node/Input/Gesture/RotationGestureRecognizer.h"
#include "Node/Input/Gesture/SwipeGestureRecognizer.h"
#include "Node/Input/Gesture/DoubleTapGestureRecognizer.h"
#include "Node/Input/Gesture/IGestureRecognizer.h"
#include "Node/Input/Gesture/StrokeGestureRecognizer.h"
#include "Node/Input/IMEHandler.h"
#include "Node/Input/KeyboardHandler.h"
#include "Node/INode.h"
#include "Node/Component/NodeScriptComponent.h"


MEDUSA_BEGIN;

InputDispatcher::InputDispatcher(INode* node) :mNode(node)
{
	mHandlers.SetAll(nullptr);
	mHandlers.ForceSetCount(0);
}

InputDispatcher::~InputDispatcher()
{
	if (!mHandlers.IsEmpty())
	{
		InputManager::Instance().Unregister(mNode);
	}
	SAFE_DELETE_COLLECTION(mHandlers);
}


IInputHandler* InputDispatcher::FindFocusHandler() const
{
	for (auto handler : mHandlers)
	{
		if (handler != nullptr&&handler->IsFocus())
		{
			return handler;
		}
	}
	return nullptr;
}

IInputHandler* InputDispatcher::FindHandler(InputType type) const
{
	return mHandlers[(uint)type];
}

void InputDispatcher::TouchesBegan(TouchEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);
	IInputHandler* focusHandler = FindFocusHandler();
	if (focusHandler != nullptr)
	{
		focusHandler->TouchesBegan(e);
		return;
	}


	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->TouchesBegan(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::TouchesMoved(TouchEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);
	IInputHandler* focusHandler = FindFocusHandler();
	if (focusHandler != nullptr)
	{
		focusHandler->TouchesMoved(e);
		return;
	}

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->TouchesMoved(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::TouchesEnded(TouchEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);
	IInputHandler* focusHandler = FindFocusHandler();
	if (focusHandler != nullptr)
	{
		focusHandler->TouchesEnded(e);
		return;
	}

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->TouchesEnded(e);
		RETURN_IF_TRUE(e.Handled);
	}
}


void InputDispatcher::MockTouch(TouchEventArg& e)
{
	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->MockTouch(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::TouchesCancelled(TouchEventArg& e)
{
	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->TouchesCancelled(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

bool InputDispatcher::Update(float dt)
{
	RETURN_TRUE_IF_EMPTY(mHandlers);
	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		RETURN_FALSE_IF_FALSE(handler->Update(dt));
	}

	return true;
}


void InputDispatcher::Reset()
{
	RETURN_IF_EMPTY(mHandlers);
	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->Reset();
	}

}

void InputDispatcher::KeyDown(KeyDownEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->KeyDown(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::KeyUp(KeyUpEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->KeyUp(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::CharInput(CharInputEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->CharInput(e);
		RETURN_IF_TRUE(e.Handled);
	}
}

void InputDispatcher::Scroll(ScrollEventArg& e)
{
	RETURN_IF_EMPTY(mHandlers);

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		handler->Scroll(e);
		RETURN_IF_TRUE(e.Handled);
	}
}


void InputDispatcher::CancelOtherHandlers(IInputHandler* self)
{
	RETURN_IF_EMPTY(mHandlers);

	for (auto handler : mHandlers)
	{
		CONTINUE_IF_NULL(handler);
		if (handler != self)
		{
			handler->Reset();
		}
	}
}


TapGestureRecognizer* InputDispatcher::AddTapGestureRecognizer()
{
	TapGestureRecognizer* recognizer = (TapGestureRecognizer*)mHandlers[(size_t)InputType::Tap];
	if (recognizer == nullptr)
	{
		recognizer = new TapGestureRecognizer(mNode);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::Tap] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


SwipeGestureRecognizer* InputDispatcher::AddSwipeGestureRecognizer(ScrollDirection direction /*=ScrollDirection::FreeFromCurrent*/, float minMovement/*=5.f*/, float minVelocity/*=30.f*/)
{
	SwipeGestureRecognizer* recognizer = (SwipeGestureRecognizer*)mHandlers[(size_t)InputType::Swipe];
	if (recognizer == nullptr)
	{
		recognizer = new SwipeGestureRecognizer(mNode, direction, minMovement, minVelocity);
		recognizer->SetDispatcher(this);
		recognizer->AddBehaviors(mBehaviors);
		mHandlers[(size_t)InputType::Swipe] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


PanGestureRecognizer* InputDispatcher::AddPanGestureRecognizer(float minDistance/*=5.f*/)
{
	PanGestureRecognizer* recognizer = (PanGestureRecognizer*)mHandlers[(size_t)InputType::Pan];
	if (recognizer == nullptr)
	{
		recognizer = new PanGestureRecognizer(mNode, minDistance);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::Pan] = recognizer;
		IncreaseHandlerCount();

		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


DragGestureRecognizer* InputDispatcher::AddDragGestureRecognizer(float minDistance /*= 5.f*/)
{
	DragGestureRecognizer* recognizer = (DragGestureRecognizer*)mHandlers[(size_t)InputType::Drag];
	if (recognizer == nullptr)
	{
		recognizer = new DragGestureRecognizer(mNode, minDistance);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::Drag] = recognizer;
		IncreaseHandlerCount();

		return recognizer;
	}
	else
	{
		return recognizer;
	}
}

PinchGestureRecognizer* InputDispatcher::AddPinchGestureRecognizer()
{
	PinchGestureRecognizer* recognizer = (PinchGestureRecognizer*)mHandlers[(size_t)InputType::Pinch];
	if (recognizer == nullptr)
	{
		recognizer = new PinchGestureRecognizer(mNode);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::Pinch] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}

TapGestureRecognizer* InputDispatcher::AddTapGestureHandler(TapDelegate handler)
{
	TapGestureRecognizer* recognizer = AddTapGestureRecognizer();
	if (recognizer->OnTap.Contains(handler))
	{
		Log::Error("Duplicate add gesture handler");
		return recognizer;
	}
	recognizer->OnTap += handler;
	return recognizer;
}

bool InputDispatcher::RemoveTapGestureHandler(TapDelegate handler)
{
	TapGestureRecognizer* recognizer = (TapGestureRecognizer*)mHandlers[(size_t)InputType::Tap];
	if (recognizer == nullptr)
	{
		Log::Error("Cannot find handler");
		return false;
	}

	recognizer->OnTap -= handler;
	if (!recognizer->HasHandler())
	{
		SAFE_DELETE(mHandlers[(size_t)InputType::Tap]);
		DecreaseHandlerCount();
	}
	return true;

}

bool InputDispatcher::RemoveAllTapGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Tap]);
	DecreaseHandlerCount();
	return true;
}

SwipeGestureRecognizer* InputDispatcher::AddSwipeGestureHandler(SwipeSuccessDelegate handler, ScrollDirection direction /*=ScrollDirection::FreeFromCurrent*/, float minMovement/*=5.f*/, float minVelocity/*=30.f*/)
{
	SwipeGestureRecognizer* recognizer = AddSwipeGestureRecognizer(direction, minMovement, minVelocity);
	if (recognizer->OnSwipeSuccess.Contains(handler))
	{
		Log::Error("Duplicate add gesture handler");
		return recognizer;
	}
	recognizer->OnSwipeSuccess += handler;
	return recognizer;
}

bool InputDispatcher::RemoveSwipeGestureHandler(SwipeSuccessDelegate handler)
{
	SwipeGestureRecognizer* recognizer = (SwipeGestureRecognizer*)mHandlers[(size_t)InputType::Swipe];
	if (recognizer == nullptr)
	{
		Log::Error("Cannot find handler");
		return false;
	}
	recognizer->OnSwipeSuccess -= handler;
	if (!recognizer->HasHandler())
	{
		SAFE_DELETE(mHandlers[(size_t)InputType::Swipe]);
		DecreaseHandlerCount();
	}
	return true;
}

bool InputDispatcher::RemoveAllSwipeGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Swipe]);
	DecreaseHandlerCount();
	return true;
}

PanGestureRecognizer* InputDispatcher::AddPanGestureHandler(PanDelegate handler, float minDistance/*=5.f*/)
{
	PanGestureRecognizer* recognizer = AddPanGestureRecognizer(minDistance);
	if (recognizer->OnPan.Contains(handler))
	{
		Log::Error("Duplicate add gesture handler");
		return recognizer;
	}
	recognizer->OnPan += handler;
	return recognizer;
}

bool InputDispatcher::RemovePanGestureHandler(PanDelegate handler)
{
	PanGestureRecognizer* recognizer = (PanGestureRecognizer*)mHandlers[(size_t)InputType::Pan];
	if (recognizer == nullptr)
	{
		Log::Error("Cannot find handler");
		return false;
	}
	recognizer->OnPan -= handler;
	if (!recognizer->HasHandler())
	{
		SAFE_DELETE(mHandlers[(size_t)InputType::Pan]);
		DecreaseHandlerCount();
	}
	return true;
}

bool InputDispatcher::RemoveAllPanGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Pan]);
	DecreaseHandlerCount();
	return true;
}

DragGestureRecognizer* InputDispatcher::AddDragGestureHandler(DragBeganDelegate beganHandler, DragingDelegate dragingHandler, DragEndDelegate endHandler, float minDistance /*= 5.f*/)
{
	DragGestureRecognizer* recognizer = AddDragGestureRecognizer(minDistance);
	recognizer->OnDragBegan += beganHandler;
	recognizer->OnDraging += dragingHandler;
	recognizer->OnDragEnd += endHandler;
	return recognizer;
}

bool InputDispatcher::RemoveAllDragGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Drag]);
	DecreaseHandlerCount();
	return true;
}

PinchGestureRecognizer* InputDispatcher::AddPinchGestureHandler(PinchDelegate handler)
{
	PinchGestureRecognizer* recognizer = AddPinchGestureRecognizer();
	if (recognizer->OnPinch.Contains(handler))
	{
		Log::Error("Duplicate add gesture handler");
		return recognizer;
	}
	recognizer->OnPinch += handler;
	return recognizer;
}

bool InputDispatcher::RemovePinchGestureHandler(PinchDelegate handler)
{
	PinchGestureRecognizer* recognizer = (PinchGestureRecognizer*)mHandlers[(size_t)InputType::Pinch];
	if (recognizer == nullptr)
	{
		Log::Error("Cannot find handler");
		return false;
	}
	recognizer->OnPinch -= handler;
	if (!recognizer->HasHandler())
	{
		SAFE_DELETE(mHandlers[(size_t)InputType::Pinch]);
		DecreaseHandlerCount();
	}
	return true;
}

bool InputDispatcher::RemoveAllPinchGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Pinch]);
	DecreaseHandlerCount();
	return true;
}


DoubleTapGestureRecognizer* InputDispatcher::AddDoubleTapGestureRecognizer(float maxDuration/*=0.25f*/)
{
	DoubleTapGestureRecognizer* recognizer = (DoubleTapGestureRecognizer*)mHandlers[(size_t)InputType::DoubleTap];
	if (recognizer == nullptr)
	{
		recognizer = new DoubleTapGestureRecognizer(mNode, maxDuration);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::DoubleTap] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


DoubleTapGestureRecognizer* InputDispatcher::AddDoubleTapGestureHandler(TapDelegate tapHandler, DoubleTapDelegate doubleTapHandler, float maxDuration/*=0.25f*/)
{
	DoubleTapGestureRecognizer* recognizer = AddDoubleTapGestureRecognizer(maxDuration);
	if (recognizer->OnTap.Contains(tapHandler) || recognizer->OnDoubleTap.Contains(doubleTapHandler))
	{
		Log::Error("Duplicate add gesture handler");
		return recognizer;
	}
	recognizer->OnTap += tapHandler;
	recognizer->OnDoubleTap += doubleTapHandler;
	return recognizer;
}


bool InputDispatcher::RemoveDoubleTapGestureHandler(TapDelegate tapHandler, DoubleTapDelegate doubleTapHandler)
{
	DoubleTapGestureRecognizer* recognizer = (DoubleTapGestureRecognizer*)mHandlers[(size_t)InputType::DoubleTap];
	if (recognizer == nullptr)
	{
		Log::Error("Cannot find handler");
		return false;
	}
	recognizer->OnTap -= tapHandler;
	recognizer->OnDoubleTap -= doubleTapHandler;
	if (!recognizer->HasHandler())
	{
		SAFE_DELETE(mHandlers[(size_t)InputType::DoubleTap]);
		DecreaseHandlerCount();
	}
	return true;
}

bool InputDispatcher::RemoveAllDoubleTapGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::DoubleTap]);
	DecreaseHandlerCount();
	return true;
}

void InputDispatcher::IncreaseHandlerCount()
{
	mHandlers.ForceSetCount(mHandlers.Count() + 1);
	if (mHandlers.Count() == 1)
	{
		//first time
		InputManager::Instance().Register(mNode);
	}
}

void InputDispatcher::DecreaseHandlerCount()
{
	mHandlers.ForceSetCount(mHandlers.Count() - 1);
	if (mHandlers.IsEmpty())
	{
		InputManager::Instance().Unregister(mNode);
	}
}


IMEHandler* InputDispatcher::AddIMEHandler()
{
	IMEHandler* recognizer = (IMEHandler*)mHandlers[(size_t)InputType::IME];
	if (recognizer == nullptr)
	{
		recognizer = new IMEHandler(mNode);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::IME] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


IMEHandler* InputDispatcher::AddIMEHandler(CharInputDelegate charInputHandler, KeyDownDelegate keyDownHandler, KeyUpDelegate keyUpHandler)
{
	IMEHandler* recognizer = AddIMEHandler();
	if (charInputHandler != nullptr)
	{
		recognizer->OnCharInput += charInputHandler;
	}
	if (keyDownHandler != nullptr)
	{
		recognizer->OnKeyDown += keyDownHandler;
	}
	if (keyUpHandler != nullptr)
	{
		recognizer->OnKeyUp += keyUpHandler;
	}


	return recognizer;
}

bool InputDispatcher::RemoveAllIMEHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::IME]);
	DecreaseHandlerCount();
	return true;
}


KeyboardHandler* InputDispatcher::AddKeyboardHandler()
{
	KeyboardHandler* recognizer = (KeyboardHandler*)mHandlers[(size_t)InputType::Keyboard];
	if (recognizer == nullptr)
	{
		recognizer = new KeyboardHandler(mNode);
		recognizer->SetDispatcher(this);
		recognizer->AddBehaviors(mBehaviors);
		mHandlers[(size_t)InputType::Keyboard] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


KeyboardHandler* InputDispatcher::AddKeyboardHandler(KeyboardWillShowDelegate willShowHandler, KeyboardShowedDelegate showedHandler, KeyboardWillHideDelegate willHideHandler, KeyboardHidedDelegate hidedHandler)
{
	KeyboardHandler* recognizer = AddKeyboardHandler();
	recognizer->OnWillShow += willShowHandler;
	recognizer->OnShowed += showedHandler;
	recognizer->OnWillHide += willHideHandler;
	recognizer->OnHided += hidedHandler;

	return recognizer;
}



bool InputDispatcher::RemoveAllKeyboardHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Keyboard]);
	DecreaseHandlerCount();
	return true;
}

void InputDispatcher::Monitor(InputEventType type, StringRef handlerName)
{
	Monitor(type).Add(handlerName);
}

StrokeGestureRecognizer* InputDispatcher::AddStrokeGestureRecognizer()
{
	StrokeGestureRecognizer* recognizer = (StrokeGestureRecognizer*)mHandlers[(size_t)InputType::Stroke];
	if (recognizer == nullptr)
	{
		recognizer = new StrokeGestureRecognizer(mNode);
		recognizer->AddBehaviors(mBehaviors);
		recognizer->SetDispatcher(this);
		mHandlers[(size_t)InputType::Stroke] = recognizer;
		IncreaseHandlerCount();
		return recognizer;
	}
	else
	{
		return recognizer;
	}
}


StrokeGestureRecognizer* InputDispatcher::AddStrokeGestureRecognizer(StrokeDelegate onStroke, StrokeFailedDelegate onStrokeFailed/*=nullptr*/)
{
	StrokeGestureRecognizer* recognizer = AddStrokeGestureRecognizer();
	recognizer->OnStroke += onStroke;
	if (onStrokeFailed)
	{
		recognizer->OnStrokeFailed += onStrokeFailed;
	}
	return recognizer;
}

bool InputDispatcher::RemoveStrokeGestureHandler(StrokeDelegate handler)
{
	StrokeGestureRecognizer* recognizer = (StrokeGestureRecognizer*)mHandlers[(size_t)InputType::Stroke];
	if (recognizer == nullptr)
	{
		Log::Error("Cannot find handler");
		return false;
	}

	recognizer->OnStroke -= handler;
	if (!recognizer->HasHandler())
	{
		SAFE_DELETE(mHandlers[(size_t)InputType::Stroke]);
		DecreaseHandlerCount();
	}
	return true;
}

bool InputDispatcher::RemoveAllStrokeGestureHandler()
{
	SAFE_DELETE(mHandlers[(size_t)InputType::Stroke]);
	DecreaseHandlerCount();
	return true;
}

List<HeapString>& InputDispatcher::Monitor(InputEventType type)
{
	return mEventMonitors.NewAdd(type);
}


bool InputDispatcher::IsMonitoring() const
{
	return !mEventMonitors.IsEmpty();
}

void InputDispatcher::Bind(StringRef handlerName, const NodeInputDelegate& handler)
{
	Bind(handlerName) += handler;
}

NodeInputEvent& InputDispatcher::Bind(StringRef handlerName)
{
	return mEventBindings.NewAdd(handlerName);
}

bool InputDispatcher::FireEvent(InputEventType type, INode* node /*= nullptr*/, IEventArg* e/*=nullptr*/)const
{
	RETURN_FALSE_IF_FALSE(IsMonitoring());

	const auto* handerNames = mEventMonitors.TryGet(type);
	RETURN_FALSE_IF_NULL(handerNames);
	RETURN_FALSE_IF_EMPTY(*handerNames);
	bool isHit = false;
	for (const auto& handlerName : *handerNames)
	{
		auto* handlerEvent = mEventBindings.TryGet(handlerName);
		if (handlerEvent != nullptr)
		{
			handlerEvent->Invoke(node, e);
			isHit = true;
		}
	}

	if (!isHit)
	{
		//try to raise up to parent node
		INode* parent = mNode->Parent();
		while (parent != nullptr)
		{
			for (const auto& handlerName : *handerNames)
			{
				isHit |= parent->MutableInput().FireEventHelper(type, handlerName, node, e);
				RETURN_TRUE_IF_TRUE(e != nullptr&&e->Handled);
			}

			RETURN_TRUE_IF_TRUE(isHit);
			parent = parent->Parent();
		}

	}
	return isHit;
}


bool InputDispatcher::FireEventHelper(InputEventType type, StringRef handlerName, INode* node /*= nullptr*/, IEventArg* e /*= nullptr*/)const
{
	auto* handlerEvent = mEventBindings.TryGet(handlerName);
	if (handlerEvent != nullptr)
	{
		handlerEvent->Invoke(node, e);
		return true;
	}

	return false;
}

#ifdef MEDUSA_SCRIPT
bool InputDispatcher::FireScriptBinding(InputEventType type, INode* node /*= nullptr*/, IEventArg* e /*= nullptr*/) const
{
	const auto* handerNames = mEventMonitors.TryGet(type);
	RETURN_FALSE_IF_NULL(handerNames);
	RETURN_FALSE_IF_EMPTY(*handerNames);
	bool isHit = false;

	for (const auto& handlerName : *handerNames)
	{
		auto* scriptComponent = mNode->FindComponent<NodeScriptComponent>();
		if (scriptComponent != nullptr&& scriptComponent->HasMethod(handlerName))
		{
			scriptComponent->HandleEvent(type, handlerName, node, e);
			isHit = true;
		}
	}


	if (!isHit)
	{
		//try to raise up to parent node
		INode* parent = mNode->Parent();
		while (parent != nullptr)
		{
			for (const auto& handlerName : *handerNames)
			{
				isHit |= parent->MutableInput().FireScriptBindingHelper(type, handlerName, node, e);
				RETURN_TRUE_IF_TRUE(e != nullptr&&e->Handled);
			}

			RETURN_TRUE_IF_TRUE(isHit);
			parent = parent->Parent();
		}

	}
	return isHit;
}

bool InputDispatcher::FireScriptBindingHelper(InputEventType type, StringRef handlerName, INode* node /*= nullptr*/, IEventArg* e /*= nullptr*/) const
{
	auto* scriptComponent = mNode->FindComponent<NodeScriptComponent>();
	if (scriptComponent != nullptr&& scriptComponent->HasMethod(handlerName))
	{
		scriptComponent->HandleEvent(type, handlerName, node, e);
		return true;
	}
	return false;
}

#endif
MEDUSA_END;