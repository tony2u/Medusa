// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"
#include "Node/Input/Gesture/Stroke/SingleStrokeTemplate.h"
#include "Node/Input/Gesture/Stroke/SingleStrokeLibrary.h"
MEDUSA_BEGIN;


class StrokeGestureRecognizer :public IGestureRecognizer
{
public:
	StrokeGestureRecognizer(INode* node);
	virtual ~StrokeGestureRecognizer(void);
	virtual InputType GetInputType()const { return InputType::Stroke; }

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();

	virtual bool HasHandler()const { return !OnStroke.IsEmpty(); }

	SingleStrokeLibrary& MutableLibrary() { return mLibrary; }

public:
	StrokeEvent OnStroke;
	StrokeFailedEvent OnStrokeFailed;
private:
	SingleStrokeLibrary mLibrary;
	SingleStrokeTemplate mStroke;
};



MEDUSA_END;