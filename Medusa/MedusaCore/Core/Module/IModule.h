// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/LinkedList.h"
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Pattern/ISharable.h"


MEDUSA_BEGIN;

class IModule :public IInitializable, public ISharableSingleThread
{
	typedef LinkedList<IModule*> ModuleList;
public:
	IModule(const StringRef& name);
	virtual ~IModule();


	bool Load(IEventArg& e = IEventArg::Empty);
	bool Unload(IEventArg& e = IEventArg::Empty);
	bool Reload(IEventArg& e = IEventArg::Empty);
	void ClearModules();

	bool AddPrevModule(IModule* item);
	bool AddPrevModule(IModule* item, bool enabled);
	bool AddPrevLoadModule(const Delegate<bool(IEventArg& e)>& del, const StringRef& name);

	bool AddNextModule(IModule* item);
	bool AddNextModule(IModule* item, bool enabled);
	bool AddNextLoadModule(const Delegate<bool(IEventArg& e)>& del, const StringRef& name);

	bool RemoveModule(StringRef name);

	IModule* FindModule(StringRef name)const;
	bool EnableModule(StringRef name, bool val);

	bool AddModuleBefore(StringRef name, IModule* item);
	bool AddModuleAfter(StringRef name, IModule* item);


public:
	StringRef ModuleName() const { return mModuleName; }
	void SetModuleName(StringRef val) { mModuleName = val; }

	bool IsEnabled() const { return mEnabled; }
	void Enable(bool val) { mEnabled = val; }
protected:
	virtual bool OnBeforeLoad(IEventArg& e = IEventArg::Empty) { return true; }
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) { return true; }
	virtual bool OnAfterLoad(IEventArg& e = IEventArg::Empty) { return true; }

	virtual bool OnBeforeUnload(IEventArg& e = IEventArg::Empty) { return true; }
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) { return true; }
	virtual bool OnAfterUnload(IEventArg& e = IEventArg::Empty) { return true; }

	virtual bool OnBeforeReload(IEventArg& e = IEventArg::Empty) { return true; }
	virtual bool OnReload(IEventArg& e = IEventArg::Empty) { return true; }
	virtual bool OnAfterReload(IEventArg& e = IEventArg::Empty) { return true; }


	virtual bool OnChildLoad(IModule& child, IEventArg& e = IEventArg::Empty) { return child.Load(e); }
	virtual bool OnChildUnload(IModule& child, IEventArg& e = IEventArg::Empty) { return child.Unload(e); }
	virtual bool OnChildReload(IModule& child, IEventArg& e = IEventArg::Empty) { return child.Reload(e); }
protected:
	ModuleList::NodePtr FindModuleHelper(StringRef name)const;
	ModuleList::NodePtr FindModuleHelperRecursively(StringRef name)const;

protected:
	HeapString mModuleName;
	bool mEnabled = true;

	ModuleList mPrevModules;
	ModuleList mNextModules;

	Dictionary<StringRef, ModuleList::NodePtr> mModuleDict;

};

MEDUSA_END;