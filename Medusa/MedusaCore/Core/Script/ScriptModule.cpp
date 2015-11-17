// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Script/ScriptModule.h"
#include "Core/Script/ScriptEngine.h"
#include "CoreLib/Common/angelscript.h"

MEDUSA_BEGIN;

ScriptModule::ScriptModule(StringRef name) :mName(name)
{
	mScriptModule = nullptr;
	mScriptBuilder = nullptr;
}

ScriptModule::~ScriptModule()
{
	Uninitialize();
}

bool ScriptModule::Initialize()
{
	Uninitialize();
	mScriptBuilder = new CScriptBuilder();
	mScriptBuilder->SetIncludeCallback(OnInclude, nullptr);

	mScriptBuilder->StartNewModule(ScriptEngine::Instance().GetScriptEngine(), mName.c_str());
	mScriptModule = mScriptBuilder->GetModule();



	return true;
}

bool ScriptModule::Uninitialize()
{
	if (mScriptModule != nullptr)
	{
		mScriptModule->Discard();
		mScriptModule = nullptr;
	}
	SAFE_DELETE(mScriptBuilder);

	return true;
}


void ScriptModule::UnloadAllScripts()
{
	mScriptBuilder->StartNewModule(ScriptEngine::Instance().GetScriptEngine(), mName.c_str());
	mScriptModule = mScriptBuilder->GetModule();
}

int ScriptModule::OnInclude(const char *include, const char *from, CScriptBuilder *builder, void *userParam)
{
	MemoryByteData fileData = FileSystem::Instance().ReadAllData(include);
	if (!fileData.IsNull())
	{
		StringRef str(fileData.Cast<char>());
		builder->AddSectionFromMemory(include, str.c_str(), (uint)str.Length());
	}
	else
	{
		Log::FormatError("Cannot read script:{}", include);
	}

	return 0;
}

bool ScriptModule::LoadScript(FileIdRef scriptFile)
{

	MemoryByteData fileData = FileSystem::Instance().ReadAllData(scriptFile);
	if (!fileData.IsNull())
	{
		StringRef str(fileData.Cast<char>());
		mScriptBuilder->AddSectionFromMemory(scriptFile.Name.c_str(), str.c_str(), (uint)str.Length());
		return true;
	}
	else
	{
		Log::FormatError("Cannot read script:{}", scriptFile.Name);
		return false;
	}

	return true;
}


bool ScriptModule::Build()
{
	return mScriptBuilder->BuildModule() >= 0;
}

ScriptObject* ScriptModule::NewObject(StringRef className)
{
	asIObjectType* scriptObjectType = mScriptModule->GetObjectTypeByName(className.c_str());
	RETURN_NULL_IF_NULL(scriptObjectType);

	HeapString factoryName = className;
	factoryName += "@ ";
	factoryName += className;
	factoryName += "()";
	asIScriptFunction* factory = scriptObjectType->GetFactoryByDecl(factoryName.c_str());
	RETURN_NULL_IF_NULL(factory);

	asIScriptContext* context = ScriptEngine::Instance().GetScriptContext();
	context->Prepare(factory);
	context->Execute();
	asIScriptObject* scriptObject = *(asIScriptObject**)context->GetAddressOfReturnValue();

	return new ScriptObject(scriptObject);
}

ScriptObject* ScriptModule::NewObjectWithInt(StringRef className, int address)
{
	asIObjectType* scriptObjectType = mScriptModule->GetObjectTypeByName(className.c_str());
	if (scriptObjectType == nullptr)
	{
		Log::FormatError("Cannot find class by {}", className.c_str());
	}
	RETURN_NULL_IF_NULL(scriptObjectType);

	HeapString factoryName = className;
	factoryName += "@ ";
	factoryName += className;
	factoryName += "(int address)";
	asIScriptFunction* factory = scriptObjectType->GetFactoryByDecl(factoryName.c_str());
	if (factory == nullptr)
	{
		Log::FormatError("Cannot find class factory by {}", factoryName.c_str());
	}
	RETURN_NULL_IF_NULL(factory);

	asIScriptContext* context = ScriptEngine::Instance().GetScriptContext();
	context->Prepare(factory);
	context->SetArgDWord(0, address);

	context->Execute();
	asIScriptObject* scriptObject = *(asIScriptObject**)context->GetAddressOfReturnValue();

	return new ScriptObject(scriptObject);
}


bool ScriptModule::NewObjects(StringRef className, size_t count, List<ScriptObject*>& outObjects)
{
	outObjects.Clear();
	asIObjectType* scriptObjectType = mScriptModule->GetObjectTypeByName(className.c_str());
	RETURN_FALSE_IF_NULL(scriptObjectType);

	HeapString factoryName = className;
	factoryName += "@ ";
	factoryName += className;
	factoryName += "()";
	asIScriptFunction* factory = scriptObjectType->GetFactoryByDecl(factoryName.c_str());
	RETURN_FALSE_IF_NULL(factory);
	asIScriptContext* context = ScriptEngine::Instance().GetScriptContext();

	List<ScriptObject*> result;
	FOR_EACH_SIZE(i, count)
	{
		context->Prepare(factory);
		context->Execute();
		asIScriptObject* scriptObject = *(asIScriptObject**)context->GetAddressOfReturnValue();
		ScriptObject* temp = new ScriptObject(scriptObject);
		outObjects.Add(temp);
	}

	return true;

}
MEDUSA_END;
#endif
