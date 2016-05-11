// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IModule.h"
#include "Core/Pattern/Delegate.h"

MEDUSA_BEGIN;


struct DelegateModule :public IModule
{
	typedef Delegate<bool(IEventArg& e)> HandlerType;

	using IModule::IModule;

	virtual bool Initialize() override
	{
		if (InitializeHandler)
		{
			return InitializeHandler();
		}
		return true;
	}
	virtual bool Uninitialize()override
	{
		if (UninitializeHandler)
		{
			return UninitializeHandler();
		}
		return true;
	}
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty)override
	{
		if (LoadHandler)
		{
			return LoadHandler(e);
		}
		return true;
	}

	virtual bool OnUnload(IEventArg& e = IEventArg::Empty)override
	{
		if (UnloadHandler)
		{
			return UnloadHandler(e);
		}
		return true;
	}

	virtual bool OnReload(IEventArg& e = IEventArg::Empty)override
	{
		if (ReloadHandler)
		{
			return ReloadHandler(e);
		}
		return true;
	}
public:
	PredicateFunc InitializeHandler;
	PredicateFunc UninitializeHandler;

	HandlerType LoadHandler;
	HandlerType UnloadHandler;
	HandlerType ReloadHandler;

};




MEDUSA_END;
