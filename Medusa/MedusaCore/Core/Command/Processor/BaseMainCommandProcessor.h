// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/List.h"

#include "Core/Command/EventArg/IEventArg.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Command/DelegateCommand.h"


MEDUSA_BEGIN;

template<typename TLock>
class BaseMainCommandProcessor
{
public:
	typedef SwapValue<List<ICommand*>> CommandQueue;
	BaseMainCommandProcessor(void) {}
	virtual ~BaseMainCommandProcessor(void)
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
		for (const ICommand* command : mCommands.Front())
		{
			RETURN_TRUE_IF_TRUE(command->IsA(rttiClass));
		}

		for (const ICommand* command : mCommands.Back())
		{
			RETURN_TRUE_IF_TRUE(command->IsA(rttiClass));
		}

		return false;
	}



	void WaitForComplete()
	{
		TLock lock(mMutex);
		mCommands.Swap();
		CommandQueue::ValueRef commands = mCommands.MutableFront();
		while (!commands.IsEmpty())
		{
			FOR_EACH_COLLECTION(i, commands)
			{
				ICommand* item = *i;
				item->Execute();
				SAFE_RELEASE(item);
			}
			commands.Clear();
		}
	}
	void Clear()
	{
		{
			CommandQueue::ValueRef commands = mCommands.MutableFront();
			FOR_EACH_COLLECTION(i, commands)
			{
				ICommand* item = *i;
				item->Execute();
				SAFE_RELEASE(item);
			}
			commands.Clear();
		}

		{
			CommandQueue::ValueRef commands = mCommands.MutableBack();
			FOR_EACH_COLLECTION(i, commands)
			{
				ICommand* item = *i;
				item->Execute();
				SAFE_RELEASE(item);
			}
			commands.Clear();
		}
	}
	void ClearWithoutRun()
	{
		{
			CommandQueue::ValueRef commands = mCommands.MutableFront();
			SAFE_RELEASE_COLLECTION(commands);
		}

	{
		CommandQueue::ValueRef commands = mCommands.MutableBack();
		SAFE_RELEASE_COLLECTION(commands);
	}
	}


	template<typename TSender, typename TEventArg>
	void Receive(TEventHandler<TSender,TEventArg> handler, TSender* sender, TEventArg eventArg)
	{
		if (handler.IsValid() && eventArg != nullptr)
		{
			handler.Invoke(sender, eventArg);
		}
	}

	void Receive(DummyEventHandler handler)
	{
		if (handler)
		{
			handler(nullptr, IEventArg::Empty);
		}
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
		CommandQueue::ValueRef commands = mCommands.MutableBack();
		commands.Push(command);
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
		CommandQueue::ValueRef myCommands = mCommands.MutableBack();
		myCommands.AddRange(commands);
		SAFE_RETAIN_COLLECTION(commands);
	}
protected:
	CommandQueue mCommands;
	typename TLock::MutexType mMutex;
};


MEDUSA_END;