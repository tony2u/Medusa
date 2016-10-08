// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IModule.h"

MEDUSA_BEGIN;

template<typename T>
struct SingletonModule :public IModule
{
	using IModule::IModule;
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty)override
	{
		return T::Instance().Load(e);
	}

	virtual bool OnUnload(IEventArg& e = IEventArg::Empty)override
	{
		return T::Instance().Unload(e);
	}

	virtual bool OnReload(IEventArg& e = IEventArg::Empty)override
	{
		return T::Instance().Reload(e);
	}
};




MEDUSA_END;
