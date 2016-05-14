// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SceneFactory_Binding.h"
#include "Core/Command/EventArg/UserDataEventArg.h"
#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Node/Scene/SceneFactory.h"
#include "Node/Scene/IScene.h"


MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_SceneFactory(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");

	auto cls = module.BeginClass<SceneFactory>();

	cls.AddFunction("Create", [](const StringRef& className, const FileIdRef& editorFile,NodeCreateFlags flags)->IScene* {return SceneFactory::Instance().Create(className, editorFile,IEventArg::Empty, flags); });

	//typedef  IScene* (SceneManager::*PushPtr)(const StringRef&, ScenePushFlags, const IEventArg&);
	//reg.AddMemberFunction("Push", (PushPtr)(&SceneManager::Push));

	return true;
}

MEDUSA_SCRIPT_BINDING_END;

#endif