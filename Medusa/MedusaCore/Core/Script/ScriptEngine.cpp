// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Script/ScriptEngine.h"
#include "CoreLib/Common/angelscript.h"

MEDUSA_BEGIN;

ScriptEngine::ScriptEngine()
{
	mScriptEngine=nullptr;
	mExternalModule = nullptr;
	mInternalModule = nullptr;
}

ScriptEngine::~ScriptEngine()
{
	Uninitialize();
}

void ScriptEngine::OnMessageCallback( const asSMessageInfo *msg, void *param )
{
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	Log::FormatInfo("{} ({}, {}) : {} : {}", msg->section, msg->row, msg->col, type, msg->message);
}



bool ScriptEngine::Initialize()
{
	Uninitialize();
	mScriptEngine= asCreateScriptEngine(ANGELSCRIPT_VERSION);
	mScriptEngine->SetEngineProperty(asEP_BUILD_WITHOUT_LINE_CUES,true);
	mScriptEngine->SetEngineProperty(asEP_AUTO_GARBAGE_COLLECT,false);
	mScriptEngine->SetEngineProperty(asEP_USE_CHARACTER_LITERALS, true);// Set engine to use character literals
	mScriptEngine->SetMessageCallback(asFUNCTION(OnMessageCallback),0,asCALL_CDECL);
	CreateInternalModule();
	CreateExternalModule();

	return true;
}

bool ScriptEngine::Uninitialize()
{
	SAFE_DELETE_DICTIONARY_VALUE(mModules);

	FOR_EACH_COLLECTION(i,mScriptContexts)
	{
		asIScriptContext* context=*i;
		SAFE_RELEASE(context);
	}
	mScriptContexts.Clear();

	mExternalModule = nullptr;
	mInternalModule = nullptr;

	SAFE_RELEASE(mScriptEngine);

	return true;
}

ScriptModule* ScriptEngine::CreateModule( StringRef name )
{
	ScriptModule* module=GetModule(name);
	if (module!=nullptr)
	{
		module->Initialize();
		return module;
	}

	module=new ScriptModule(name);
	module->Initialize();
	mModules.Add(name,module);
	return module;
}

ScriptModule* ScriptEngine::CreateExternalModule()
{
	RETURN_SELF_IF_NOT_NULL(mExternalModule);
	mExternalModule = CreateModule("External");
	return mExternalModule;
}

ScriptModule* ScriptEngine::CreateInternalModule()
{
	RETURN_SELF_IF_NOT_NULL(mInternalModule);
	mInternalModule = CreateModule("Internal");
	return mInternalModule;
}


ScriptModule* ScriptEngine::GetModule( StringRef name )
{
	return mModules.TryGetValueWithFailedByOtherKey(name,name.HashCode(),nullptr);
}

void ScriptEngine::DestoryModule( ScriptModule* module )
{
	StringRef moduelName=module->Name();
	bool isSuccess=mModules.RemoveOtherKey(moduelName,moduelName.HashCode());
	if (isSuccess)
	{
		SAFE_DELETE(module);
	}
}

asIScriptContext* ScriptEngine::GetScriptContext()
{
	FOR_EACH_COLLECTION(i,mScriptContexts)
	{
		asIScriptContext* context=*i;
		if (context->GetState()==asEXECUTION_FINISHED)
		{
			return context;
		}
	}

	asIScriptContext* context=mScriptEngine->CreateContext();
	mScriptContexts.Add(context);
	return context;
}


MEDUSA_END;
#endif
