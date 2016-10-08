// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IDataSource.h"

MEDUSA_BEGIN;
template<typename T>
class TDataSource:public IDataSource
{
public:
	using IDataSource::IDataSource;
	TDataSource(const T& data, const FileIdRef& fileId = FileIdRef::Empty)
		:IDataSource(fileId)
		,mData(data)
	{
	}
	virtual ~TDataSource(void){}
public:
	const T& Get() const { return mData; }
	T& Mutable() { return mData; }
	void Set(const T& val) { RETURN_IF_EQUAL(mData,val);mData = val; OnTotalChanged();}
protected:
	T mData;

};


MEDUSA_END;