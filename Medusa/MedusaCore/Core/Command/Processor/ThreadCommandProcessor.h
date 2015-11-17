// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Command/DelegateCommand.h"
#include "Core/Pattern/Singleton.h"
#include "BaseThreadCommandProcessor.h"
#include "Core/Command/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class ThreadCommandProcessor:public Singleton<ThreadCommandProcessor>,public BaseThreadCommandProcessor
{
	friend class Singleton<ThreadCommandProcessor>;
public:
	using BaseThreadCommandProcessor::Receive;
	using BaseThreadCommandProcessor::ReceiveAsync;


	template<typename TSender,typename TEventArg>
	void Receive(TEventHandler<TSender, TEventArg> handler,TSender* sender,const TEventArg& eventArg)
	{
		DelegateCommand* item = new DelegateCommand(Bind(handler, sender, eventArg));
		Receive(item);
	}

	void Receive(DummyEventHandler handler)
	{
		DelegateCommand* item = new DelegateCommand(Bind(handler, nullptr, IEventArg::Empty));
		Receive(item);
	}

private:
	ThreadCommandProcessor(void);
	~ThreadCommandProcessor(void);
};


MEDUSA_END;