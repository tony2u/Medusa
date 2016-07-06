// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node_Binding.h"
#include "Core/Event/EventArg/UserDataEventArg.h"

#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Node/INode.h"
#include "Node/Layer/ILayer.h"
#include "Node/Layer/NormalLayer.h"
#include "Node/Scene/IScene.h"
#include "Node/Scene/UIScene.h"
#include "Node/Sprite/Sprite.h"

MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_INode(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<INode>();
	cls.AddConstruct(LUA_ARGS(StringRef));
	cls.AddMemberFunction("ScriptObject", &INode::GetScriptObject);
	cls.AddMemberFunction("SetScriptObject", &INode::SetScriptObject);
	cls.AddMemberFunction("AddChild", &INode::AddChild);



	return true;
}

bool Register_ILayer(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<ILayer>();
	cls.InheritFrom<INode>();

	return true;
}

bool Register_IScene(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<IScene>();
	cls.InheritFrom<INode>();

	typedef  ILayer* (IScene::*PushObjectPtr)(ILayer* layer, NodePushFlags pushFlags);
	cls.AddMemberFunction("PushObject", (PushObjectPtr)&IScene::PushLayer);

	auto pushDelegate = [](IScene* scene, const StringRef& className, NodePushFlags pushFlags)->ILayer* {return scene->PushLayer(className, pushFlags); };
	cls.AddFunctionAsMember("Push", pushDelegate);

	typedef  ILayer* (IScene::*PushLayerExPtr)(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, NodePushFlags pushFlags);
	cls.AddMemberFunction("PushEx", (PushLayerExPtr)&IScene::PushLayerEx);

	return true;
}

bool Register_NormalLayer(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<NormalLayer>();
	cls.InheritFrom<ILayer>();
	cls.AddConstruct(LUA_ARGS(StringRef));
	return true;
}

bool Register_Sprite(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<Sprite>();
	cls.InheritFrom<INode>();
	cls.AddConstruct(LUA_ARGS(StringRef));

	return true;
}

bool Register_UIScene(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<UIScene>();
	cls.InheritFrom<IScene>();
	cls.AddConstruct(LUA_ARGS(StringRef));

	return true;
}


MEDUSA_SCRIPT_BINDING_END;

#endif