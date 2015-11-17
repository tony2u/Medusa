// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "MedusaExtensionScript.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

MedusaExtensionScript::MedusaExtensionScript()
{
	
}

MedusaExtensionScript::~MedusaExtensionScript()
{
	UninitializeInternal();
	UninitializeExternal();

}


bool MedusaExtensionScript::InitializeInternal()
{
	return true;
}

bool MedusaExtensionScript::UninitializeInternal()
{
	return true;
}

bool MedusaExtensionScript::InitializeExternal()
{
	return true;
}

bool MedusaExtensionScript::UninitializeExternal()
{
	return true;
}

void MedusaExtensionScript::RegisterTypes()
{
	//asIScriptEngine* engine=ScriptEngine::Instance().GetScriptEngine();


}


MEDUSA_END;

#endif