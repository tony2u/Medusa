// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Queue.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Command/DelegateCommand.h"


MEDUSA_BEGIN;

template<typename TCommand, typename TLock>
class TQueueCommandExecutor
{
public:
	using CommandType = Share<TCommand>;
	typedef Queue<CommandType> CommandQueue;
	TQueueCommandExecutor(void) {}
	virtual ~TQueueCommandExecutor(void)
	{
		ClearWithoutRun();
	}
public:
	void WaitForComplete()
	{
		TLock lock(mMutex);
		while (!mCommands.IsEmpty())
		{
			auto& item = mCommands.PopWithReturn();
			item->Execute();
		}
	}

	void Clear()
	{
		WaitForComplete();
	}

	void ClearWithoutRun()
	{
		mCommands.Clear();
	}


	template<typename TCommand>
	bool Contains()const
	{
		return Contains(TCommand::ClassStatic());
	}

	bool Contains(const RTTIClass& rttiClass)const
	{
		for (const auto& command : mCommands)
		{
			RETURN_TRUE_IF_TRUE(command->IsA(rttiClass));
		}
		return false;
	}

	template<typename TSender, typename TEventArg>
	void Execute(TEventHandler<TSender, TEventArg> handler, TSender* sender, TEventArg eventArg)
	{
		if (eventArg != nullptr)
		{
			handler.TryInvoke(sender, eventArg);
		}
	}

	void Execute(DummyEventHandler handler)
	{
		handler.TryInvoke(nullptr, IEventArg::Empty);
	}

	template<typename TSender, typename TEventArg>
	void ExecuteAsync(TEventHandler<TSender, TEventArg> handler, TSender* sender, TEventArg eventArg)
	{
		CommandType item = new DelegateCommand(Bind(handler, sender, eventArg));
		ExecuteAsync(item);
	}

	void ExecuteAsync(DummyEventHandler handler)
	{
		CommandType item = new DelegateCommand(Bind(handler, nullptr, IEventArg::Empty));
		ExecuteAsync(item);
	}

	void Execute(const CommandType& command)
	{
		RETURN_IF_NULL(command);
		command->Execute();
	}


	void Execute(Action action)
	{
		action();
	}
	void Execute(ActionWithUserData action, void* userData)
	{
		action(userData);
	}

	void Execute(const List<CommandType>& commands)
	{
		for (auto comamnd : commands)
		{
			command->Execute();
		}
	}

	void ExecuteAsync(const CommandType& command)
	{
		RETURN_IF_NULL(command);
		TLock lock(mMutex);
		mCommands.Push(command);
	}

	void ExecuteAsync(Action action)
	{
		CommandType command = new DelegateCommand(action);
		ExecuteAsync(command);
	}
	void ExecuteAsync(ActionWithUserData action, void* userData)
	{
		CommandType command = new DelegateCommand(Bind(action, userData));
		ExecuteAsync(command);
	}

	void ExecuteAsync(const List<CommandType>& commands)
	{
		TLock lock(mMutex);
		for (auto command : commands)
		{
			mCommands.Add(command);
		}
	}
protected:
	CommandQueue mCommands;
	typename TLock::MutexType mMutex;
};


typedef TQueueCommandExecutor<ICommand, ScopedNoLock> SimpleQueueCommandProcessor;
typedef TQueueCommandExecutor<ICommand, ScopedLock> SafeQueueCommandProcessor;


MEDUSA_END;