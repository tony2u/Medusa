// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NodeFactory_Binding.h"
#include "Core/Command/EventArg/UserDataEventArg.h"
#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Node/NodeFactory.h"


MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_NodeFactory(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");

	auto cls = module.BeginClass<NodeFactory>();

	typedef  Sprite* (NodeFactory::*PushPtr)(const FileIdRef&, const Rect2F&);
	cls.AddMemberFunctionAsStatic("CreateSprite", NodeFactory::Instance(), (PushPtr)&NodeFactory::CreateSprite, LUA_ARGS(const FileIdRef&, Lua::Opt<const Rect2F&>));


	//typedef  IScene* (SceneManager::*PushPtr)(const StringRef&, ScenePushFlags, const IEventArg&);
	//reg.AddMemberFunction("Push", (PushPtr)(&SceneManager::Push));

	return true;
}


MEDUSA_SCRIPT_BINDING_END;

#endif