// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"

#ifdef MEDUSA_SCRIPT
#include "Core/Script/ScriptDefines.h"
MEDUSA_BEGIN;

class IScriptSettings
{
public:
	IScriptSettings(ScriptObject scriptObject = nullptr);
	virtual ~IScriptSettings();
public:
	bool Contains(const StringRef& name)const
	{
		return mScriptObject.Has(name);
	}

	template<typename T>
	bool TryGet(const StringRef& name, T& outValue)const
	{
		return mScriptObject.TryGet(name, outValue);
	}

	template<typename T>
	T Get(const StringRef& name)const
	{
		return mScriptObject.Get<T>(name);
	}

	template<typename T>
	T Optional(const StringRef& name, const T& defaultVal)const
	{
		return mScriptObject.Optional(name, defaultVal);
	}

public:
	ScriptObject& GetScriptObject() { return mScriptObject; }
	void SetScriptObject(const ScriptObject& val) { mScriptObject = val; }
protected:
	ScriptObject mScriptObject;

};

MEDUSA_END;

#endif