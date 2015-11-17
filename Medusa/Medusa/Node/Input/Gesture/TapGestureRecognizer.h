// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"

MEDUSA_BEGIN;


class TapGestureRecognizer:public IGestureRecognizer
{
public:
	TapGestureRecognizer(INode* node,GestureFlags flags=GestureFlags::None,const FileIdRef& audioEffect=FileIdRef::Empty);
	virtual ~TapGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Tap;}

	virtual void TouchesBegan(TouchEventArg& e);
	virtual void TouchesMoved(TouchEventArg& e);
	virtual void TouchesEnded(TouchEventArg& e);
	virtual void TouchesCancelled(TouchEventArg& e);
	virtual void TryFireEvent(TouchEventArg& e);

	virtual bool IsValid()const;
	virtual void Reset();

	virtual bool HasHandler()const{return !OnTap.IsEmpty();}


	TapEvent OnTap;
	TapFailedEvent OnTapFailed;

private:
	Touch mBeganTouch;
};



MEDUSA_END;