// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IDataSource.h"

MEDUSA_BEGIN;
template<typename T>
class UserDataSource:public IDataSource
{
	MEDUSA_DECLARE_RTTI;
public:
	UserDataSource(T data):IDataSource(),mData(data){}
	UserDataSource():IDataSource(){}
	virtual ~UserDataSource(void){}

public:
	T Data() const { return mData; }
	const T& GetDataRef() const { return mData; }
	T& GetDataRef() { return mData; }
	void SetData(T val) { RETURN_IF_EQUAL(mData,val);mData = val; Commit();}

protected:
	T mData;

};


MEDUSA_END;