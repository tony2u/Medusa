// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;
template<typename T>
class UserDataEventArg :public IEventArg
{
public:
	UserDataEventArg(T data) :IEventArg(), mData(data) {}
	UserDataEventArg() :IEventArg() {}
	virtual ~UserDataEventArg(void) {}

public:
	const T& Data() const { return mData; }
	T& MutableData() { return mData; }


	void SetData(const T& val) { mData = val; }
protected:
	T mData;

};


MEDUSA_END;