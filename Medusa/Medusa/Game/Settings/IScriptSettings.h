// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT
#include "MedusaPreDeclares.h"
#include "Core/Pattern/ISettings.h"
#include "Core/Script/ScriptObject.h"
MEDUSA_BEGIN;

class IScriptSettings :public ISettings
{
public:
	IScriptSettings(ScriptObject* scriptObject=nullptr);
	virtual ~IScriptSettings();
public:
	virtual void* GetAddress(const StringRef& name)const;
	
	template<typename T>
	T Get(const StringRef& name)const	//hide base 
	{
		return *(T*)GetAddress(name);
	}

	template<typename T>
	T GetDefault(const StringRef& name, T defaultVal)const	////hide base 
	{
		T* p = (T*)GetAddress(name);
		if (p != nullptr)
		{
			return *p;
		}
		return defaultVal;
	}
public:
	ScriptObject* GetScriptObject() const { return mScriptObject; }
	void SetScriptObject(ScriptObject* val) { mScriptObject = val; }
protected:
	ScriptObject* mScriptObject;
	
};

template<>
inline StringRef IScriptSettings::Get<StringRef>(const StringRef& name)const
{
	return mScriptObject->Member<StringRef>(name);
}

template<>
inline  StringRef IScriptSettings::GetDefault<StringRef>(const StringRef& name, StringRef defaultVal)const
{
	return mScriptObject->MemberOrDefault<StringRef>(name, defaultVal);
}


MEDUSA_END;

#endif