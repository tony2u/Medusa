// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Command/ICommand.h"
#include "Core/Pattern/Delegate.h"


MEDUSA_BEGIN;


struct DelegateCommand :public ICommand
{
	typedef Delegate<void()> HandlerType;

	DelegateCommand(const HandlerType& handler)
		:Handler(handler)
	{
		
	}

	virtual ~DelegateCommand()
	{
		
	}
	
	virtual bool OnExecute()override
	{
		Handler.TryInvoke();
		return true;
	}

	HandlerType Handler;
};

template<typename TSender, typename TEventArg>
using TEventHandler = Delegate<void(TSender*, TEventArg)>;

//[PRE_DECLARE_BEGIN]

typedef Delegate<void(void* sender, IEventArg&)> EventHandler;
typedef Delegate<void(void*, IEventArg)> DummyEventHandler;

//[PRE_DECLARE_END]


MEDUSA_END;
