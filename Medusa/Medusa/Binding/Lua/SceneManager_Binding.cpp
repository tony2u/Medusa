// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SceneManager_Binding.h"
#include "Core/Event/EventArg/UserDataEventArg.h"
#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Node/Scene/SceneManager.h"
#include "Node/Scene/IScene.h"


MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_SceneManager(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");

	auto cls = module.BeginClass<SceneManager>();

	cls.AddFunction("Push", [](const StringRef& className, NodePushFlags pushFlag)->IScene* {return SceneManager::Instance().Push(className, pushFlag); });
	cls.AddFunction("PushObject", [](IScene* scene, NodePushFlags pushFlag) {SceneManager::Instance().Push(scene, pushFlag); });

	cls.AddFunction("ReplaceTo", [](const StringRef& className, NodePopFlags popFlags, NodePushFlags pushFlag)->IScene* {return SceneManager::Instance().ReplaceTo(className, popFlags, pushFlag); });
	cls.AddFunction("ReplaceToObject", [](IScene* scene, NodePopFlags popFlags, NodePushFlags pushFlag) {SceneManager::Instance().ReplaceTo(scene, popFlags, pushFlag); });

	cls.AddFunction("Pop", [](NodePopFlags popFlags) {return SceneManager::Instance().Pop( popFlags); });

	//typedef  IScene* (SceneManager::*PushPtr)(const StringRef&, NodePushFlags, const IEventArg&);
	//reg.AddMemberFunction("Push", (PushPtr)(&SceneManager::Push));

	return true;
}

MEDUSA_SCRIPT_BINDING_END;

#endif