// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"


MEDUSA_BEGIN;
class PanGestureRecognizer:public IGestureRecognizer
{
    
public:
	PanGestureRecognizer(INode* node, float minDistance,GestureFlags flags=GestureFlags::None);
	virtual ~PanGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Pan;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);

	const Point2F& Movement() const { return mMovement; }

	virtual bool IsValid()const;
	virtual void Reset();

	virtual bool HasHandler()const{return !OnPan.IsEmpty();}

	PanEvent OnPan;
	PanBeginEvent OnBegin;
	PanEndEvent OnEnd;

	
private:
	float mMinDistance;
    Point2F mCurCenter;
    Point2F mMovement;


};



MEDUSA_END;