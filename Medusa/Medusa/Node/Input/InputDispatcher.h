// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/IInputHandler.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/Array.h"
#include "Core/Geometry/ScrollDirection.h"

MEDUSA_BEGIN;

class InputDispatcher:public IInputHandler
{
public:
	InputDispatcher(INode* node);
	~InputDispatcher();
public:
	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void TryFireEvent(TouchEventArg& e);

	virtual void KeyDown(KeyDownEventArg& e);
	virtual void KeyUp(KeyUpEventArg& e);
	virtual void CharInput(CharInputEventArg& e);
	virtual void Scroll(ScrollEventArg& e);
	virtual bool Update(float dt);
	virtual void Reset();

public:
	TapGestureRecognizer* AddTapGestureRecognizer();
	SwipeGestureRecognizer* AddSwipeGestureRecognizer(ScrollDirection direction = ScrollDirection::FreeFromCurrent,float minMovement=5.f,float minVelocity=30.f);
	PanGestureRecognizer* AddPanGestureRecognizer(float minDistance=5.f);
	PinchGestureRecognizer* AddPinchGestureRecognizer();
	DoubleTapGestureRecognizer* AddDoubleTapGestureRecognizer(float maxDuration=0.25f);
	IMEHandler* AddIMEHandler();
	KeyboardHandler* AddKeyboardHandler();



	bool HasHandler()const{return !mHandlers.IsEmpty();}
public:
	void CancelOtherHandlers(IInputHandler* self);

	TapGestureRecognizer* AddTapGestureHandler(TapDelegate handler);
	bool RemoveTapGestureHandler(TapDelegate handler);
	bool RemoveAllTapGestureHandler();

	SwipeGestureRecognizer* AddSwipeGestureHandler(SwipeSuccessDelegate handler,ScrollDirection direction = ScrollDirection::FreeFromCurrent,float minMovement=5.f,float minVelocity=30.f);
	bool RemoveSwipeGestureHandler(SwipeSuccessDelegate handler);
	bool RemoveAllSwipeGestureHandler();

	PanGestureRecognizer* AddPanGestureHandler(PanDelegate handler,float minDistance=5.f);
	bool RemovePanGestureHandler(PanDelegate handler);
	bool RemoveAllPanGestureHandler();

	PinchGestureRecognizer* AddPinchGestureHandler(PinchDelegate handler);
	bool RemovePinchGestureHandler(PinchDelegate handler);
	bool RemoveAllPinchGestureHandler();


	DoubleTapGestureRecognizer* AddDoubleTapGestureHandler(TapDelegate tapHandler,DoubleTapDelegate doubleTapHandler,float maxDuration=0.25f);
	bool RemoveDoubleTapGestureHandler(TapDelegate tapHandler,DoubleTapDelegate doubleTapHandler);
	bool RemoveAllDoubleTapGestureHandler();

	//bool RegisterLongPressGesture(LongPressGestureRecognizer target,float minPressDuration,float allowMovement,bool enableTouch=true);

	/*bool RegisterTapGesture(const string& id,EventTarget target,bool enableTouch=true);

	bool RegisterLongPressGesture(EventTarget target,float minPressDuration,float allowMovement,bool enableTouch=true);
	bool RegisterLongPressGesture(const string& id,EventTarget target,float minPressDuration,float allowMovement,bool enableTouch=true);


	bool RegisterDragGesture(EventTarget target, float minDistance=0, bool enableTouch=true);
	bool RegisterDragGesture(const string& id, EventTarget target, float minDistance=0, bool enableTouch=true);

	bool RegisterSwipeGesture(EventTarget target,Direction::GestureDirection_t direction,float minMoveDuration, float minMovement,float minVelocity,bool enableTouch=true);
	bool RegisterSwipeGesture(const string& id,EventTarget target,Direction::GestureDirection_t direction,float minMoveDuration, float minMovement,float minVelocity,bool enableTouch=true);*/

	IMEHandler* AddIMEHandler(CharInputDelegate charInputHandler,KeyDownDelegate keyDownHandler,KeyUpDelegate keyUpHandler);
	bool RemoveAllIMEHandler();

	KeyboardHandler* AddKeyboardHandler(KeyboardWillShowDelegate willShowHandler, KeyboardShowedDelegate showedHandler, KeyboardWillHideDelegate willHideHandler, KeyboardHidedDelegate hidedHandler);
	bool RemoveAllKeyboardHandler();

	INode* Node() const { return mNode; }
private:
	IInputHandler* FindFocusHandler()const;
	void IncreaseHandlerCount();
	void DecreaseHandlerCount();

private:
	INode* mNode;
	Array<IInputHandler*,(size_t)InputType::Size> mHandlers;
};


MEDUSA_END;