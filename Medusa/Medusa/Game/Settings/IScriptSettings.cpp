// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_SCRIPT
#include "IScriptSettings.h"

MEDUSA_BEGIN;

IScriptSettings::IScriptSettings(ScriptObject* scriptObject/*=nullptr*/)
	:mScriptObject(scriptObject)
{

}

IScriptSettings::~IScriptSettings()
{
	//SAFE_DELETE(mScriptObject);
}

void* IScriptSettings::GetAddress(const StringRef& name) const
{
	RETURN_NULL_IF_NULL(mScriptObject);
	return mScriptObject->GetMemberAddress(name);
}


MEDUSA_END;
#endif