// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#ifdef MEDUSA_SCRIPT
#include "TestScript.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/String/StringRef.h"
//#include "MedusaExtensionScript.h"


MEDUSA_BEGIN;

TestScript::TestScript()
{
	mConfigObject = nullptr;
}

TestScript::~TestScript()
{
	UninitializeInternal();
}


bool TestScript::InitializeInternal()
{
	//MedusaExtensionScript::Instance().InitializeInternal();

	//load scripts
	ScriptModule* configModule = ScriptEngine::Instance().InternalModule();
	configModule->LoadScript("TestSettings.cs");

	return true;
}

bool TestScript::UninitializeInternal()
{
	DeleteInternalScriptObjects();
	
	//MedusaExtensionScript::Instance().UninitializeInternal();
	return true;
}


void TestScript::RegisterTypes()
{

	//MedusaExtensionScript::Instance().RegisterTypes();



}

bool TestScript::CreateInternalScriptObjects()
{
	RETURN_TRUE_IF_NOT_NULL(mConfigObject);

	mConfigObject = ScriptEngine::Instance().InternalModule()->NewObject(MACRO_TO_STRING(TestSettings));
	Log::AssertNotNullFormat(mConfigObject, "Cannot create:{}", MACRO_TO_STRING(TestSettings));
	return mConfigObject != nullptr;
}

bool TestScript::DeleteInternalScriptObjects()
{
	SAFE_DELETE(mConfigObject);
	return true;
}


MEDUSA_END;
#endif