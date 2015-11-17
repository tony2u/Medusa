// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class TriggerEventArg :public IEventArg
{
	MEDUSA_DECLARE_RTTI;
public:
	TriggerEventArg() :IEventArg(), mInt(0),mFloat(0.f) {}
	virtual ~TriggerEventArg(void) {}

	TriggerEventArg(const TriggerEventArg& val)
		:mName(val.mName),mInt(val.mInt), mFloat(val.mFloat), mString(val.mString)
	{

	}
	TriggerEventArg& operator=(const TriggerEventArg& val)
	{
		mName = val.Name();
		mInt = val.Int();
		mFloat = val.Float();
		mString = val.String();
		return *this;
	}
public:
	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	int Int() const { return mInt; }
	void SetInt(int val) { mInt = val; }

	float Float() const { return mFloat; }
	void SetFloat(float val) { mFloat = val; }

	StringRef String() const { return mString; }
	void SetString(const StringRef& val) { mString = val; }
protected:
	HeapString mName;
	
	int mInt;
	float mFloat;
	HeapString mString;
};

MEDUSA_IMPLEMENT_RTTI(TriggerEventArg,IEventArg);

MEDUSA_END;