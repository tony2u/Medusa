// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Queue.h"

#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Command/DelegateCommand.h"


MEDUSA_BEGIN;

template<typename TLock>
class QueueCommandProcessor
{
public:
	typedef Queue<ICommand*> CommandQueue;
	QueueCommandProcessor(void) {}
	virtual ~QueueCommandProcessor(void)
	{
		ClearWithoutRun();
	}
public:
	void WaitForComplete()
	{
		TLock lock(mMutex);
		while (!mCommands.IsEmpty())
		{
			ICommand* item = mCommands.PopWithReturn();
			item->Execute();
			SAFE_RELEASE(item);
		}
	}

	void Clear()
	{
		WaitForComplete();
	}

	void ClearWithoutRun()
	{
		SAFE_RELEASE_COLLECTION(mCommands);
	}


	template<typename TCommand>
	bool Contains()const
	{
		return Contains(TCommand::ClassStatic());
	}

	bool Contains(const RTTIClass& rttiClass)const
	{
		for (const ICommand* command:mCommands)
		{
			RETURN_TRUE_IF_TRUE(command->IsA(rttiClass));
		}
		return false;
	}

	template<typename TSender, typename TEventArg>
	void Receive(TEventHandler<TSender, TEventArg> handler, TSender* sender, TEventArg eventArg)
	{
		if (eventArg != nullptr)
		{
			handler.TryInvoke(sender, eventArg);
		}
	}

	void Receive(DummyEventHandler handler)
	{
		handler.TryInvoke(nullptr, IEventArg::Empty);
	}

	template<typename TSender, typename TEventArg>
	void ReceiveAsync(TEventHandler<TSender, TEventArg> handler, TSender* sender, TEventArg eventArg)
	{
		DelegateCommand* item = new DelegateCommand(Bind(handler, sender, eventArg));
		ReceiveAsync(item);
	}

	void ReceiveAsync(DummyEventHandler handler)
	{
		DelegateCommand* item = new DelegateCommand(Bind(handler, nullptr, IEventArg::Empty));
		ReceiveAsync(item);
	}

	void Receive(ICommand* command)
	{
		RETURN_IF_NULL(command);
		command->Execute();
	}


	void Receive(Action0 action)
	{
		DelegateCommand command(action);
		Receive(&command);
	}
	void Receive(Action1 action, void* userData)
	{
		DelegateCommand command(Bind(action, userData));
		Receive(&command);
	}

	void Receive(const List<ICommand*>& commands)
	{
		FOR_EACH_COLLECTION(i, commands)
		{
			ICommand* command = *i;
			command->Execute();
		}
	}

	void ReceiveAsync(ICommand* command)
	{
		RETURN_IF_NULL(command);
		TLock lock(mMutex);
		mCommands.Push(command);
		SAFE_RETAIN(command);
	}

	void ReceiveAsync(Action0 action)
	{
		DelegateCommand* command = new DelegateCommand(action);
		ReceiveAsync(command);
	}
	void ReceiveAsync(Action1 action, void* userData)
	{
		DelegateCommand* command = new DelegateCommand(Bind(action, userData));
		ReceiveAsync(command);
	}

	void ReceiveAsync(const List<ICommand*>& commands)
	{
		TLock lock(mMutex);
		for (auto command:commands)
		{
			mCommands.Push(command);
		}
		SAFE_RETAIN_COLLECTION(commands);
	}
protected:
	CommandQueue mCommands;
	typename TLock::MutexType mMutex;
};


typedef QueueCommandProcessor<ScopedNoLock> SimpleQueueCommandProcessor;
typedef QueueCommandProcessor<ScopedLock> SafeQueueCommandProcessor;


MEDUSA_END;