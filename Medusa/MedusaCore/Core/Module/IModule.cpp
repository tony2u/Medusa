// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IModule.h"
#include "DelegateModule.h"
#include "Core/Log/Log.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

IModule::IModule(const StringRef& name)
	:mModuleName(name)
{

}

IModule::~IModule()
{
	ClearModules();
}


bool IModule::Load(IEventArg& e /*= IEventArg::Empty*/)
{
	RETURN_TRUE_IF_FALSE(IsEnabled());

	RETURN_FALSE_IF_FALSE(OnBeforeLoad(e));

	for (auto& item : mPrevModules)
	{
		RETURN_FALSE_IF_FALSE(OnChildLoad(*item, e));
	}
	RETURN_FALSE_IF_FALSE(OnLoad(e));
	for (auto& item : mNextModules)
	{
		RETURN_FALSE_IF_FALSE(OnChildLoad(*item, e));
	}

	RETURN_FALSE_IF_FALSE(OnAfterLoad(e));

	return true;
}


bool IModule::Reload(IEventArg& e/*= IEventArg::Empty*/)
{
	RETURN_TRUE_IF_FALSE(IsEnabled());
	RETURN_FALSE_IF_FALSE(OnBeforeReload(e));

	for (auto& item : mPrevModules)
	{
		RETURN_FALSE_IF_FALSE(OnChildReload(*item, e));
	}
	RETURN_FALSE_IF_FALSE(OnReload(e));
	for (auto& item : mNextModules)
	{
		RETURN_FALSE_IF_FALSE(OnChildReload(*item, e));
	}

	RETURN_FALSE_IF_FALSE(OnAfterReload(e));

	return true;
}

bool IModule::Unload(IEventArg& e/*= IEventArg::Empty*/)
{
	RETURN_TRUE_IF_FALSE(IsEnabled());
	RETURN_TRUE_IF_FALSE(OnBeforeUnload(e));

	//reverse
	for (auto i = mNextModules.rbegin(); i != mNextModules.rend(); --i)
	{
		auto child = *i;
		RETURN_FALSE_IF_FALSE(OnChildUnload(*child, e));
	}
	RETURN_TRUE_IF_FALSE(OnUnload(e));
	for (auto i = mPrevModules.rbegin(); i != mPrevModules.rend(); --i)
	{
		auto child = *i;
		RETURN_FALSE_IF_FALSE(OnChildUnload(*child, e));
	}
	RETURN_TRUE_IF_FALSE(OnAfterUnload(e));

	return true;
}


void IModule::ClearModules()
{
	//reverse
	for (auto i = mNextModules.rbegin(); i != mNextModules.rend(); --i)
	{
		auto child = *i;
		child->ClearModules();
	}
	mNextModules.Clear();

	for (auto i = mPrevModules.rbegin(); i != mPrevModules.rend(); --i)
	{
		auto child = *i;
		child->ClearModules();
	}
	mPrevModules.Clear();

	mModuleDict.Clear();
}

bool IModule::AddPrevModule(const ModuleType& item)
{
	if (!item->Initialize())
	{
		return false;
	}

	if (mModuleDict.ContainsKey(item->ModuleName()))
	{
		Log::FormatError("Duplicate module name:{}", item->ModuleName());
		return false;
	}

	auto node = mPrevModules.Add(item);
	mModuleDict.Add(item->ModuleName(), node);
	return true;

}

bool IModule::AddPrevModule(const ModuleType& item, bool enabled)
{
	if (AddPrevModule(item))
	{
		item->Enable(enabled);
		return true;
	}
	return false;
}

bool IModule::AddPrevLoadModule(const Delegate<bool(IEventArg& e)>& del, const StringRef& name)
{
	Share<DelegateModule> item(new DelegateModule(name));
	item->LoadHandler = del;
	if (!AddPrevModule(item))
	{
		return false;
	}

	return true;
}

bool IModule::AddNextModule(const ModuleType& item)
{
	if (!item->Initialize())
	{
		return false;
	}

	if (mModuleDict.ContainsKey(item->ModuleName()))
	{
		Log::FormatError("Duplicate module name:{}", item->ModuleName());
		return false;
	}

	auto node=mNextModules.Add(item);
	mModuleDict.Add(item->ModuleName(), node);
	return true;

}

bool IModule::AddNextModule(const ModuleType& item, bool enabled)
{
	if (AddNextModule(item))
	{
		item->Enable(enabled);
		return true;
	}
	return false;
}

bool IModule::AddNextLoadModule(const Delegate<bool(IEventArg& e)>& del, const StringRef& name)
{
	Share<DelegateModule> item(new DelegateModule(name));
	item->LoadHandler = del;
	if (!AddNextModule(item))
	{
		return false;
	}

	return true;
}

bool IModule::AddModuleBefore(StringRef name, const ModuleType& item)
{
	intp index = name.IndexOf('.');
	if (index < 0)
	{
		if (mModuleDict.ContainsKey(item->ModuleName()))
		{
			Log::FormatError("Duplicate module name:{}", item->ModuleName());
			return false;
		}

		auto node = FindModuleHelper(name);
		RETURN_FALSE_IF_NULL(node);

		if (!item->Initialize())
		{
			return false;
		}

		if (mNextModules.ContainsNode(node))
		{
			mNextModules.AddBefore(node, item);
			mModuleDict.Add(item->ModuleName(), node);
			return true;
		}

		if (mPrevModules.ContainsNode(node))
		{
			mPrevModules.AddBefore(node, item);
			mModuleDict.Add(item->ModuleName(), node);
			return true;
		}

	}

	StringRef cur = name.SubString(0, index);
	name = name.SubString(index + 1);
	auto node = FindModuleHelper(cur);
	RETURN_NULL_IF_NULL(node);
	return node->Value->AddModuleBefore(name,item);
	
}

bool IModule::AddModuleAfter(StringRef name, const ModuleType& item)
{
	intp index = name.IndexOf('.');
	if (index < 0)
	{
		if (mModuleDict.ContainsKey(item->ModuleName()))
		{
			Log::FormatError("Duplicate module name:{}", item->ModuleName());
			return false;
		}

		auto node = FindModuleHelper(name);
		RETURN_FALSE_IF_NULL(node);

		if (!item->Initialize())
		{
			return false;
		}

		if (mNextModules.ContainsNode(node))
		{
			mNextModules.AddAfter(node, item);
			mModuleDict.Add(item->ModuleName(), node);
			return true;
		}

		if (mPrevModules.ContainsNode(node))
		{
			mPrevModules.AddAfter(node, item);
			mModuleDict.Add(item->ModuleName(), node);
			return true;
		}

	}

	StringRef cur = name.SubString(0, index);
	name = name.SubString(index + 1);
	auto node = FindModuleHelper(cur);
	RETURN_NULL_IF_NULL(node);
	return node->Value->AddModuleBefore(name, item);
}

bool IModule::RemoveModule(StringRef name)
{
	auto node = mModuleDict.RemoveKeyOptional(name, nullptr);
	if (node != nullptr)
	{
		if (mNextModules.ContainsNode(node))
		{
			mNextModules.Delete(node);
		}

		if (mPrevModules.ContainsNode(node))
		{
			mPrevModules.Delete(node);
		}
		
	}

	return false;
}


IModule::ModuleType IModule::FindModule(StringRef name) const
{
	auto node = FindModuleHelperRecursively(name);
	RETURN_NULL_IF_NULL(node);
	return node->Value;
}

IModule::ModuleList::NodePtr IModule::FindModuleHelper(StringRef name) const
{
	return mModuleDict.GetOptional(name, nullptr);
}

IModule::ModuleList::NodePtr IModule::FindModuleHelperRecursively(StringRef name) const
{
	intp index = name.IndexOf('.');
	if (index<0)
	{
		return FindModuleHelper(name);
	}

	StringRef cur = name.SubString(0, index);
	name = name.SubString(index+1);
	auto node = FindModuleHelper(cur);
	RETURN_NULL_IF_NULL(node);
	return node->Value->FindModuleHelperRecursively(name);
}

bool IModule::EnableModule(StringRef name, bool val)
{
	auto module = FindModule(name);
	RETURN_FALSE_IF_NULL(module);
	module->Enable(val);
	return true;
}
MEDUSA_END;

