// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Command/DelegateCommand.h"
#include "Core/Pattern/Singleton.h"
#include "TAsyncCommandExecutor.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class AsyncCommandExecutor :public Singleton<AsyncCommandExecutor>, public TAsyncCommandExecutor<ICommand>
{
	AsyncCommandExecutor(void);
	~AsyncCommandExecutor(void);
	friend class Singleton<AsyncCommandExecutor>;
public:
	using TAsyncCommandExecutor::Execute;

	template<typename TSender, typename TEventArg>
	void Execute(TEventHandler<TSender, TEventArg> handler, TSender* sender, const TEventArg& eventArg)
	{
		CommandType item = new DelegateCommand(Bind(handler, sender, eventArg));
		Execute(item);
	}

	void Execute(DummyEventHandler handler)
	{
		CommandType item = new DelegateCommand(Bind(handler, nullptr, IEventArg::Empty));
		Execute(item);
	}
};


MEDUSA_END;