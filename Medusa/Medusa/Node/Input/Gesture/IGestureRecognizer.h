// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/Input/IInputHandler.h"
#include "Core/Collection/List.h"
#include "Node/Input/Touch.h"
#include "Node/Input/EventArg/TouchEventArg.h"

MEDUSA_BEGIN;




class IGestureRecognizer:public IInputHandler
{

public:
	IGestureRecognizer(INode* node);
	virtual ~IGestureRecognizer(void);

	virtual bool Update(float dt){return true;}

	bool HasTouch()const{return mTouchEventArg.IsValid();}

	virtual bool IsValid()const=0;
	virtual bool HasHandler()const=0;


protected:
	bool IsValidTouch(const Touch& touch)const;
	bool HasValidTouch(const List<Touch>& touches)const;

	Touch TransformToNodeSpace(const Touch& touch)const;
	bool TryTransformToNodeSpace(const Touch& touch,Touch& outTouch)const;
protected:
	TouchEventArg mTouchEventArg;

};



MEDUSA_END;