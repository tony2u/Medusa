// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/List.h"
#include "Core/Event/EventArg/IEventArg.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Command/DelegateCommand.h"


MEDUSA_BEGIN;

template<typename TCommand,typename TLock>
class TSyncCommandExecutor
{
public:
	static_assert(std::is_same<ICommand, TCommand>::value || std::is_base_of<ICommand, TCommand>::value, "TCommand must inherit from ICommand");
	using CommandType = Share<TCommand>;
public:
	typedef SwapValue<List<CommandType>> CommandQueue;
	TSyncCommandExecutor(void) {}
	virtual ~TSyncCommandExecutor(void)
	{
		ClearWithoutRun();
	}
public:
	template<typename TCommand>
	bool Contains()const
	{
		return Contains(TCommand::ClassStatic());
	}

	bool Contains(const RTTIClass& rttiClass)const
	{
		for (const auto& command : mCommands.Front())
		{
			RETURN_TRUE_IF_TRUE(command->IsA(rttiClass));
		}

		for (const auto& command : mCommands.Back())
		{
			RETURN_TRUE_IF_TRUE(command->IsA(rttiClass));
		}

		return false;
	}



	bool WaitForComplete()
	{
		TLock lock(mMutex);
		mCommands.Swap();
		CommandQueue::ValueRef commands = mCommands.MutableFront();
		if (!commands.IsEmpty())
		{
			for (auto item : commands)
			{
				item->Execute();
			}
			commands.Clear();
			return true;
		}
		return false;
	}
	void Clear()
	{
		{
			CommandQueue::ValueRef commands = mCommands.MutableFront();
			for (auto item : commands)
			{
				item->Execute();
			}
			commands.Clear();
		}

		{
			CommandQueue::ValueRef commands = mCommands.MutableBack();
			for (auto item : commands)
			{
				item->Execute();
			}
			commands.Clear();
		}
	}
	void ClearWithoutRun()
	{
		mCommands.MutableFront().Clear();
		mCommands.MutableBack().Clear();
	}


	template<typename TSender, typename TEventArg>
	void Execute(TEventHandler<TSender, TEventArg> handler, TSender* sender, TEventArg eventArg)
	{
		if (handler.IsValid() && eventArg != nullptr)
		{
			handler.Invoke(sender, eventArg);
		}
	}

	void Execute(DummyEventHandler handler)
	{
		if (handler)
		{
			handler(nullptr, IEventArg::Empty);
		}
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
		for(auto command: commands)
		{
			command->Execute();
		}
	}

	void ExecuteAsync(const CommandType& command)
	{
		RETURN_IF_NULL(command);
		TLock lock(mMutex);
		CommandQueue::ValueRef commands = mCommands.MutableBack();
		commands.Add(command);
	}

	void ExecuteAsync(Action action)
	{
		CommandType item = new DelegateCommand(action);
		ExecuteAsync(item);
	}

	void ExecuteAsync(ActionWithUserData action, void* userData)
	{
		CommandType item = new DelegateCommand(Bind(action, userData));
		ExecuteAsync(item);
	}

	void ExecuteAsync(const List<CommandType>& commands)
	{
		TLock lock(mMutex);
		CommandQueue::ValueRef myCommands = mCommands.MutableBack();
		myCommands.AddRange(commands);
	}

	bool HasFront()const { return !mCommands.Front().IsEmpty(); }
	bool HasBack()const { return !mCommands.Back().IsEmpty(); }

protected:
	CommandQueue mCommands;
	typename TLock::MutexType mMutex;
};


MEDUSA_END;