// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "CoreLib/Common/rapidjson.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

class IJsonSettings
{
public:
	IJsonSettings(rapidjson::Value* val) :mJsonValue(val) {}
	virtual ~IJsonSettings() = default;

	bool Contains(const StringRef& name)const
	{
		return mJsonValue->HasMember(name.c_str());
	}

	template<typename T>
	bool TryGet(const StringRef& name, T& outValue)const
	{
		if (Contains(name))
		{
			outValue = Get<T>(name);
			return true;
		}
		return false;
	}

	template<typename T>
	T Get(const StringRef& name)const
	{
		T defaultVal{};
		return mJsonValue->GetMember(name.c_str(), defaultVal);
	}

	template<typename T>
	T Optional(const StringRef& name, const T& defaultVal)const
	{
		return mJsonValue->GetMember(name.c_str(), defaultVal);
	}

	template<>
	StringRef Optional(const StringRef& name, const StringRef& defaultVal)const
	{
		return mJsonValue->GetMember(name.c_str(), defaultVal.c_str());
	}
public:
	rapidjson::Value* JsonValue() const { return mJsonValue; }
	void SetJsonValue(rapidjson::Value* val) { mJsonValue = val; }
protected:
	rapidjson::Value* mJsonValue=nullptr;
	
};


MEDUSA_END;

