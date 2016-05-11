// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"



MEDUSA_BEGIN;


class DoubleTapGestureRecognizer:public IGestureRecognizer
{
public:
	DoubleTapGestureRecognizer(INode* node,float maxDuration=0.25f);
	virtual ~DoubleTapGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::DoubleTap;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void MockTouch(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();
	virtual bool HasHandler()const{return !OnTap.IsEmpty()||!OnDoubleTap.IsEmpty();}


	TapEvent OnTap;
	DoubleTapEvent OnDoubleTap;

private:
	Touch mBeganTouch;
	Touch mFirstSuccessTouch;

	float mMaxDuration;
	double mBeginTimeStamp;

};



MEDUSA_END;