// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileSystem_Binding.h"
#include "Core/Command/EventArg/UserDataEventArg.h"

#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Core/IO/FileSystem.h"

MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_FileSystem(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<FileSystem>();

	auto func = [](const FileIdRef& file)->bool
	{
		return FileSystem::Instance().Exists(file);
	};
	//cls.AddFunction("Exists", func);

	cls.AddMemberFunctionAsStatic("Exists", FileSystem::Instance(), &FileSystem::Exists);
	cls.AddMemberFunctionAsStatic("AssertExists", FileSystem::Instance(), &FileSystem::AssertExists);



	return true;
}
MEDUSA_SCRIPT_BINDING_END;

#endif