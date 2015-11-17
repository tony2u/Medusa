// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

class ISettings
{
public:
	virtual ~ISettings() {}
	virtual void* GetAddress(const StringRef& name)const = 0;

	bool Contains(const StringRef& name)const
	{
		return GetAddress(name) != nullptr;
	}

	template<typename T>
	T Get(const StringRef& name)const
	{
		return *(T*)GetAddress(name);
	}

	template<typename T>
	T GetDefault(const StringRef& name, T defaultVal)const
	{
		T* p = (T*)GetAddress(name);
		if (p != nullptr)
		{
			return *p;
		}
		return defaultVal;
	}

	/*
	template<typename T>
	bool Set(const StringRef& name, T val)
	{
	T* p = (T*)GetAddress(name);
	if (p != nullptr)
	{
	*p = val;
	return true;
	}
	return false;
	}
	*/
};

MEDUSA_END;