// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MedusaCoreModule.h"
#include "Core/Script/ScriptEngine.h"

#ifdef MEDUSA_LUA
#include "Core/Binding/Lua/Core_Binding.h"
#endif

#include "Core/Command/Processor/MainCommandProcessor.h"
#include "Core/Command/Processor/ThreadCommandProcessor.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/Network/Message/MessageDispatcher.h"
#include "Core/IO/FileSystem.h"
#include "Core/Module/DelegateModule.h"
#include "Core/Threading/ThreadPool.h"

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

	DelegateModule* module = nullptr;

	module = new DelegateModule("ThreadPool");
	module->LoadHandler = [](IEventArg&)
	{
		ThreadPool::Instance().Initialize();
		return true;
	};

	module->UnloadHandler = [](IEventArg&)
	{
		ThreadPool::Instance().Uninitialize();
		return true;
	};
	AddPrevModule(module, false);
	SAFE_RELEASE(module);

	module = new DelegateModule("ThreadCommandProcessor");
	module->LoadHandler = [](IEventArg&)
	{
		ThreadCommandProcessor::Instance().Start();
		return true;
	};
	module->UnloadHandler = [](IEventArg&)
	{
		ThreadCommandProcessor::Instance().StopAndClear();
		return true;
	};
	AddPrevModule(module,false);
	SAFE_RELEASE(module);


	module = new DelegateModule("Message");
	module->LoadHandler = [](IEventArg&)
	{
		MessageDispatcher::Instance().Initialize();
		MessageDispatcher::Instance().Start();
		return true;
	};
	module->UnloadHandler = [](IEventArg&)
	{
		MessageDispatcher::Instance().Uninitialize();
		return true;
	};
	AddPrevModule(module,false);
	SAFE_RELEASE(module);


	AddNextModule(FileSystem::InstancePtr());
#ifdef MEDUSA_SCRIPT
	AddNextModule(ScriptEngine::InstancePtr());
#endif


	return true;
}


bool MedusaCoreModule::AfterUpdate(float dt)
{
	return true;
}

bool MedusaCoreModule::BeforeUpdate(float dt)
{
	MainCommandProcessor::Instance().WaitForComplete();
	return true;
}

bool MedusaCoreModule::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}
bool MedusaCoreModule::OnUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	MainCommandProcessor::Instance().Clear();

	return true;
}
bool MedusaCoreModule::OnReload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}


MEDUSA_END;

