// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Command/EventArg/IEventArg.h"



MEDUSA_BEGIN;

class ScrollEventArg:public IEventArg
{
	
	MEDUSA_DECLARE_RTTI;
public:
	ScrollEventArg(int pos,size_t status):mScrollPos(pos),mStatus(status){}
	virtual ~ScrollEventArg(void){}

	int GetScrollPos() const { return mScrollPos; }
	void SetScrollPos(int val) { mScrollPos = val; }

	size_t GetStatus() const { return mStatus; }
	void SetStatus(size_t val) { mStatus = val; }
protected:
	int mScrollPos;
	
	size_t mStatus;
};

MEDUSA_END;