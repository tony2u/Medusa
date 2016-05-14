// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NodeDefines_Binding.h"
#include "Core/Command/EventArg/UserDataEventArg.h"

#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Node/NodeDefines.h"


MEDUSA_SCRIPT_BINDING_BEGIN;


bool Register_NodeCreateFlags(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<NodeCreateFlags>();

	cls.AddConst("None", NodeCreateFlags::None);
	cls.AddConst("BindScriptSelf", NodeCreateFlags::BindScriptSelf);
	cls.AddConst("BindScriptChildren", NodeCreateFlags::BindScriptChildren);
	cls.AddConst("BindScriptRecursively", NodeCreateFlags::BindScriptRecursively);
	cls.AddConst("Count", NodeCreateFlags::Count);

	return true;
}


bool Register_NodePushFlags(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<NodePushFlags>();

	cls.AddConst("None", NodePushFlags::None);
	cls.AddConst("BindScriptSelf", NodePushFlags::BindScriptSelf);
	cls.AddConst("BindScriptChildren", NodePushFlags::BindScriptChildren);
	cls.AddConst("BindScriptRecursively", NodePushFlags::BindScriptRecursively);

	cls.AddConst("ShowPrev", NodePushFlags::ShowPrev);
	cls.AddConst("SuppressUpdateLogic", NodePushFlags::SuppressUpdateLogic);
	cls.AddConst("DisableTouch", NodePushFlags::DisableTouch);
	cls.AddConst("HideAllPrevs", NodePushFlags::HideAllPrevs);
	cls.AddConst("SaveStatusBeforePush", NodePushFlags::SaveStatusBeforePush);

	return true;
}


bool Register_NodePopFlags(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<NodePopFlags>();

	cls.AddConst("None", NodePopFlags::None);
	cls.AddConst("ShowCurrent", NodePopFlags::ShowCurrent);
	cls.AddConst("SuppressUpdateLogic", NodePopFlags::SuppressUpdateLogic);
	cls.AddConst("DisableTouch", NodePopFlags::DisableTouch);

	cls.AddConst("IgnorePrev", NodePopFlags::IgnorePrev);
	cls.AddConst("DeleteCurrent", NodePopFlags::DeleteCurrent);
	cls.AddConst("DeleteCurrentAsync", NodePopFlags::DeleteCurrentAsync);
	cls.AddConst("RestoreStatusAfterPop", NodePopFlags::RestoreStatusAfterPop);

	return true;
}

bool Register_NodeDeleteFlags(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginEnum<NodeDeleteFlags>();

	cls.AddConst("None", NodeDeleteFlags::None);
	cls.AddConst("Async", NodeDeleteFlags::Async);

	return true;
}


MEDUSA_SCRIPT_BINDING_END;

#endif