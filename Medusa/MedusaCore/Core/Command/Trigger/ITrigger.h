// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;


enum class TriggerState
{
	None,
	Open,
	Closed,
};


class ITrigger
{
public:
	ITrigger():mState(TriggerState::None){}
	virtual ~ITrigger(void){}
	virtual bool Initialize(){return true;}

	bool IsDead()const{return mState==TriggerState::Closed;}


	virtual void Open()=0;
	virtual void Close()=0;

	virtual void Update(float dt)=0;

protected:
    TriggerState mState;
};


MEDUSA_END;