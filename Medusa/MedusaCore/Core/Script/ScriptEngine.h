// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT

#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Script/ScriptModule.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

class ScriptEngine:public Singleton<ScriptEngine>,public IInitializable
{
	friend class Singleton<ScriptEngine>;
	ScriptEngine();
	~ScriptEngine();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	ScriptModule* ExternalModule() const { return mExternalModule; }
	ScriptModule* CreateExternalModule();

	ScriptModule* InternalModule() const { return mInternalModule; }
	ScriptModule* CreateInternalModule();


	ScriptModule* CreateModule(StringRef name);
	ScriptModule* GetModule(StringRef name);
	void DestoryModule(ScriptModule* module);
	asIScriptEngine* GetScriptEngine() const { return mScriptEngine; }
	asIScriptContext* GetScriptContext();

private:
	static void OnMessageCallback(const asSMessageInfo *msg, void *param);
private:
	asIScriptEngine* mScriptEngine;

	List<asIScriptContext* > mScriptContexts;
	Dictionary<HeapString,ScriptModule*> mModules;
	ScriptModule* mExternalModule;
	ScriptModule* mInternalModule;
};

MEDUSA_END;
#endif
