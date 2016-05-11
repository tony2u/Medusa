// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core_Binding.h"
#ifdef MEDUSA_LUA
#include "Core/Script/ScriptEngine.h"
#include "FileSystem_Binding.h"
#include "Siren_Binding.h"



#define MEDUSA_LUA_REGISTER(x) ScriptEngine::Instance().AddNextLoadModule(ScriptBinding::Register_##x, #x)

MEDUSA_SCRIPT_BINDING_BEGIN;

bool Register_Core()
{
	MEDUSA_LUA_REGISTER(FileSystem);

	MEDUSA_LUA_REGISTER(SirenType);
	MEDUSA_LUA_REGISTER(SirenAssembly);
	MEDUSA_LUA_REGISTER(SirenMachine);
	MEDUSA_LUA_REGISTER(Siren);


	return true;
}

MEDUSA_SCRIPT_BINDING_END;
#undef MEDUSA_LUA_REGISTER

#endif