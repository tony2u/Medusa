// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT

#include "Core/Pattern/Singleton.h"
#include "Core/String/HeapString.h"
#include "Core/Script/ScriptObject.h"
#include "Core/Collection/Dictionary.h"
#include "Core/IO/FileIdRef.h"
MEDUSA_BEGIN;

class ScriptModule
{
public:
	ScriptModule(StringRef name);
	~ScriptModule();
public:
	bool Initialize();
	bool Uninitialize();
	void UnloadAllScripts();
	bool Build();

	StringRef Name()const{return mName;}


	bool LoadScript( FileIdRef scriptFile);


	ScriptObject* NewObject(StringRef className);
	ScriptObject* NewObjectWithInt(StringRef className,int address);

	bool NewObjects(StringRef className,size_t count,List<ScriptObject*>& outObjects);

	asIScriptModule* GetScriptModule() const { return mScriptModule; }

private:
	static int OnInclude(const char *include, const char *from, CScriptBuilder *builder, void *userParam);
private:
	HeapString mName;
	asIScriptModule* mScriptModule;
	CScriptBuilder* mScriptBuilder;
};

MEDUSA_END;
#endif
