// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"

MEDUSA_BEGIN;
class PinchGestureRecognizer:public IGestureRecognizer
{
public:
	PinchGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None);
	virtual ~PinchGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Pinch;}

	float GetPinchBeginDistance() const { return mPinchBeginDistance; }
	float GetPinchEndDistance() const { return mPinchEndDistance; }
	float GetScaleFactor()const{return mPinchEndDistance/mPinchBeginDistance;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
    
	virtual bool IsValid()const;
    
    void Reset();

	virtual bool HasHandler()const{return !OnPinch.IsEmpty();}

	PinchEvent OnPinch;

private:
	float mPinchBeginDistance;
	float mPinchEndDistance;

};



MEDUSA_END;