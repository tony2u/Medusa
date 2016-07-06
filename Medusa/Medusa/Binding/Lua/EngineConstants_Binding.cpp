// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "EngineConstants_Binding.h"
#include "Core/Event/EventArg/UserDataEventArg.h"

#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Core/System/PublishDevices.h"
#include "Core/System/PublishLanguages.h"
#include "Core/System/PublishVersions.h"
#include "Application/ApplicationDebugInfoFlags.h"
#include "Node/Editor/NodeEditorFactory.h"


MEDUSA_SCRIPT_BINDING_BEGIN;


bool Register_PublishDevices(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<PublishDevices>("PublishDevices");

	cls.AddConst("None", PublishDevices::None.IntValue);
	cls.AddConst("sd", PublishDevices::sd.IntValue);
	cls.AddConst("hd", PublishDevices::hd.IntValue);

	return true;
}

bool Register_PublishLanguages(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<PublishLanguages>("PublishLanguages");

	cls.AddConst("None", PublishLanguages::None.IntValue);
	cls.AddConst("enus", PublishLanguages::enus.IntValue);
	cls.AddConst("zhcn", PublishLanguages::zhcn.IntValue);

	return true;
}


bool Register_PublishVersions(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<PublishVersions>("PublishVersions");

	cls.AddConst("None", PublishVersions::None.IntValue);
	cls.AddConst("main", PublishVersions::main.IntValue);
	cls.AddConst("free", PublishVersions::free.IntValue);

	return true;
}

bool Register_ApplicationDebugInfoFlags(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<ApplicationDebugInfoFlags>();

	cls.AddConst("None", ApplicationDebugInfoFlags::None);
	cls.AddConst("Performance", ApplicationDebugInfoFlags::Performance);
	cls.AddConst("GPU", ApplicationDebugInfoFlags::GPU);
	cls.AddConst("Touch", ApplicationDebugInfoFlags::Touch);

	return true;
}

bool Register_NodeEditors(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginTable("NodeEditors");

	for (auto& kv: NodeEditorFactory::Instance().Editors())
	{
		auto* editor = kv.Value;
		auto ext= editor->ExtensionString();
		cls.AddConst(editor->Name(), ext);
	}

	return true;
}


MEDUSA_SCRIPT_BINDING_END;

#endif