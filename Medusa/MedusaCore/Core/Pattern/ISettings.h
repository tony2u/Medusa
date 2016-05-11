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

	virtual bool Contains(const StringRef& name)const = 0;

	template<typename T>
	bool TryGet(const StringRef& name, T& outValue)const;

	template<typename T>
	T Get(const StringRef& name)const
	{
		T defaultVal{};
		TryGet(name, defaultVal);
		return defaultVal;
	}

	template<typename T>
	T Optional(const StringRef& name, T defaultVal)const
	{
		TryGet(name, defaultVal);
		return defaultVal;
	}

};

MEDUSA_END;