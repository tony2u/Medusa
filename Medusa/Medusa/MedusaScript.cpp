// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_SCRIPT
#include "MedusaScript.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/String/StringRef.h"
#include "MedusaCoreScript.h"
#include "Node/INode.h"
#include "Node/Layer/ILayer.h"
#include "Node/Scene/IScene.h"
#include "CoreLib/Common/angelscript.h"


MEDUSA_BEGIN;

MedusaScript::MedusaScript()
{
	
}

MedusaScript::~MedusaScript()
{
	UninitializeInternal();
	UninitializeExternal();
}


void MedusaScript::RegisterTypes()
{
	MedusaCoreScript::Instance().RegisterTypes();
	asIScriptEngine* engine = ScriptEngine::Instance().GetScriptEngine();
	HeapString originalNamespace(engine->GetDefaultNamespace());
	engine->SetDefaultNamespace("Medusa");

	/*Script::RegisterINode(engine);
	Script::RegisterILayer(engine);
	Script::RegisterIScene(engine);*/


	engine->SetDefaultNamespace(originalNamespace.c_str());

}


bool MedusaScript::InitializeInternal()
{
	MedusaCoreScript::Instance().InitializeInternal();
	return true;
}

bool MedusaScript::UninitializeInternal()
{
	return true;
}


bool MedusaScript::InitializeExternal()
{
	MedusaCoreScript::Instance().InitializeExternal();

	//load scripts
	ScriptModule* module=ScriptEngine::Instance().ExternalModule();
	module->LoadScript("IGame.cs");
	//module->LoadScript("INode.cs");
	//module->LoadScript("ILayer.cs");
	//module->LoadScript("IScene.cs");



	return true;
}

bool MedusaScript::UninitializeExternal()
{
	MedusaCoreScript::Instance().UninitializeExternal();

	return true;
}




MEDUSA_END;
#endif