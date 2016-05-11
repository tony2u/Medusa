// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Siren_Binding.h"
#include "Core/Command/EventArg/UserDataEventArg.h"

#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
#include "Core/Siren/Siren.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/IO/FileIdRef.h"


MEDUSA_SCRIPT_BINDING_BEGIN;

bool Register_SirenType(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<ISirenType>();
	cls.AddMemberProperty("Name", &ISirenType::Name, &ISirenType::SetName);
	cls.AddMemberPropertyGet("FullName", &ISirenType::FullName);


	return true;
}

bool Register_SirenAssembly(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<SirenAssembly>();
	cls.AddMemberProperty("Name", &SirenAssembly::Name, &SirenAssembly::SetName);
	cls.AddMemberFunction("FindType", &SirenAssembly::FindType);

	typedef bool (SirenAssembly::*AddReferencePtr)(const FileIdRef& file);
	cls.AddMemberFunction("AddReference", (AddReferencePtr)&SirenAssembly::AddReference);


	typedef bool (SirenAssembly::*ParsePtr)(const FileIdRef& file);
	cls.AddMemberFunction("ParseFile", (ParsePtr)&SirenAssembly::Parse);

	return true;
}


bool Register_SirenMachine(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<SirenMachine>();
	cls.AddMemberFunctionAsStatic("FindAssembly", SirenMachine::Instance(), &SirenMachine::FindAssembly);
	cls.AddMemberFunctionAsStatic("NewAssembly", SirenMachine::Instance(), &SirenMachine::NewAssembly);

	typedef SirenAssembly* (SirenMachine::*LoadAssemblyPtr)(const FileIdRef& file);
	cls.AddMemberFunctionAsStatic("LoadAssembly", SirenMachine::Instance(), (LoadAssemblyPtr)&SirenMachine::LoadAssembly);
	cls.AddMemberFunctionAsStatic("FindType", SirenMachine::Instance(), &SirenMachine::FindType);


	return true;
}


bool Register_Siren(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto sirenModule = module.BeginModule("Siren");

	auto serializePtr = [](const ISirenType& type, ScriptObject obj)->HeapString {return Siren::SerializeScript(obj, type, SirenCoderType::Compact); };
	auto deserializePtr = [](const ISirenType& type, HeapString data)->ScriptObject {return Siren::DeserializeScript(*ScriptEngine::State(),data,type,SirenCoderType::Compact); };
	auto deserializeToPtr = [](ScriptObject& obj,const ISirenType& type, HeapString data)->bool {return Siren::DeserializeScriptTo(obj, data, type, SirenCoderType::Compact); };

	sirenModule.AddFunction("Serialize", serializePtr);
	sirenModule.AddFunction("Deserialize", deserializePtr);
	sirenModule.AddFunction("DeserializeTo", deserializePtr);


	return true;
}


MEDUSA_SCRIPT_BINDING_END;

#endif