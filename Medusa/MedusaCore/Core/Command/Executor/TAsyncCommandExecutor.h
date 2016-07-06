// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Threading/Thread.h"
#include "Core/Collection/List.h"
#include "Core/Threading/ThreadEvent.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Threading/Mutex.h"
#include "Core/Log/Log.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Threading/Thread.h"
#include "Core/Command/ICommand.h"

MEDUSA_BEGIN;

template<typename TCommand>
class TAsyncCommandExecutor :public Thread
{
public:
	using CommandType = Share<TCommand>;
	static_assert(std::is_same<ICommand, TCommand>::value || std::is_base_of<ICommand, TCommand>::value, "TCommand must inherit from ICommand");
	typedef SwapValue<List<CommandType>> CommandQueue;
protected:
	TAsyncCommandExecutor()
	{

	}
	virtual ~TAsyncCommandExecutor(void)
	{
		Uninitialize();
	}

	virtual bool Initialize()
	{
		mStartEvent.Initialize();
		mCompleteEvent.Initialize();

		return true;
	}
	virtual bool Uninitialize()
	{
		StopAndClear();
		mStartEvent.Uninitialize();
		mCompleteEvent.Uninitialize();
		return true;
	}
public:
	void Clear()
	{
		mCommands.Swap();
		OnProcess();
	}
	void StopAndClear()
	{
		Join();
		Clear();
	}

	void Execute(const CommandType& command)
	{
		RETURN_IF_NULL(command);

		{
			ScopedLock lock(mCommandMutex);
			CommandQueue::ValueRef commands = mCommands.MutableBack();
			commands.Add(command);
		}


		mStartEvent.Set();
	}
	

	void Execute(const List<CommandType>& commands)
	{
		{
			ScopedLock lock(mCommandMutex);
			CommandQueue::ValueRef myCommands = mCommands.MutableBack();
			myCommands.AddRange(commands);
		}

		mStartEvent.Set();
	}

	void WaitForComplete()
	{
		mCompleteEvent.Wait();

	}
protected:
	virtual bool OnBeforeStart() { return true; }
	virtual bool OnBeforeJoin()
	{
		PrepareToCancel();
		mStartEvent.Set();
		return true;
	}

	virtual void OnRun()
	{
		while (!IsCancelled())
		{
			mStartEvent.Wait();

			{
				ScopedLock lock(mCommandMutex);
				mCommands.Swap();
			}

			OnProcess();
			mCompleteEvent.Set();
		}
	}

private:
	void OnProcess()
	{
		CommandQueue::ValueRef commands = mCommands.MutableFront();
		for (auto command : commands)
		{
			command->Execute();
		}
		commands.Clear();
	}

protected:
	ThreadEvent mStartEvent;
	ThreadEvent mCompleteEvent;

	NonRecursiveMutex mCommandMutex;
	CommandQueue mCommands;
};


MEDUSA_END;