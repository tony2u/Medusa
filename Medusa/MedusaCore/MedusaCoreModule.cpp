// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MedusaCoreModule.h"
#include "Core/Script/ScriptEngine.h"

#ifdef MEDUSA_LUA
#include "Core/Binding/Lua/Core_Binding.h"
#endif

#include "Core/Command/Executor/SyncCommandExecutor.h"
#include "Core/Command/Executor/AsyncCommandExecutor.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/Event/EventBus.h"
#include "Core/IO/FileSystem.h"
#include "Core/Module/DelegateModule.h"
#include "Core/Module/SingletonModule.h"
#include "Core/Threading/MainThreadPool.h"

MEDUSA_BEGIN;

MedusaCoreModule::MedusaCoreModule()
	:IModule("MedusaCore")
{

}

bool MedusaCoreModule::Initialize()
{

#ifdef MEDUSA_LUA
	ScriptBinding::Register_Core();
#endif

	Share<DelegateModule> module;

	module = new DelegateModule("ThreadPool");
	module->LoadHandler = [](IEventArg&)
	{
		MainThreadPool::Instance().Initialize();
		return true;
	};

	module->UnloadHandler = [](IEventArg&)
	{
		MainThreadPool::Instance().Uninitialize();
		return true;
	};
	AddPrevModule(module, false);

	module = new DelegateModule("ThreadCommandProcessor");
	module->LoadHandler = [](IEventArg&)
	{
		AsyncCommandExecutor::Instance().Start();
		return true;
	};
	module->UnloadHandler = [](IEventArg&)
	{
		AsyncCommandExecutor::Instance().StopAndClear();
		return true;
	};
	AddPrevModule(module,false);


	module = new DelegateModule("EventDispatcher");
	module->LoadHandler = [](IEventArg&)
	{
		EventBus::Instance().Initialize();
		EventBus::Instance().Start();
		return true;
	};
	module->UnloadHandler = [](IEventArg&)
	{
		EventBus::Instance().Uninitialize();
		return true;
	};
	AddPrevModule(module,false);

	AddNextModule(new SingletonModule<FileSystem>("FileSystem"));
#ifdef MEDUSA_SCRIPT
	AddNextModule(new SingletonModule<ScriptEngine>("ScriptEngine"));
#endif


	return true;
}


bool MedusaCoreModule::AfterUpdate(float dt)
{
	
	return true;
}

bool MedusaCoreModule::BeforeUpdate(float dt)
{
	SyncCommandExecutor::Instance().WaitForComplete();
	return true;
}

bool MedusaCoreModule::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}
bool MedusaCoreModule::OnUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	SyncCommandExecutor::Instance().Clear();

	return true;
}
bool MedusaCoreModule::OnReload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}


MEDUSA_END;

