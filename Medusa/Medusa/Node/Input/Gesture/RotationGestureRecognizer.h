// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Node/Input/Gesture/IGestureRecognizer.h"
MEDUSA_BEGIN;

class RotationGestureRecognizer:public IGestureRecognizer
{
public:
	RotationGestureRecognizer(INode* node):IGestureRecognizer(node){}
	virtual ~RotationGestureRecognizer(void);
	virtual InputType GetInputType()const{return InputType::Rotation;}

	virtual bool HasHandler()const{return false;}

};



MEDUSA_END;