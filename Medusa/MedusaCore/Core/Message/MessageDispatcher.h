// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Message/IMessage.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Threading/Thread.h"
#include "Core/Threading/ThreadEvent.h"

#include "Core/Collection/Dictionary.h"
#include "Core/Collection/LinkedList.h"


#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/Event.h"
#include "Core/Threading/Mutex.h"
#include "Core/Coder/CoderType.h"
#include "Core/Config/ServerType.h"

MEDUSA_BEGIN;

class MessageDispatcher:public Singleton<MessageDispatcher>,public IInitializable
{
	friend class Singleton<MessageDispatcher>;
	MessageDispatcher(void);
	~MessageDispatcher(void);
public:
	void ClearUp();
	void AddMessageHandler(IMessageHandler* handler);
	void RemoveMessageHandler(size_t serverId);

	void AddMessageServer(ServerType serverType, size_t id, StringRef address, ushort port, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey);

	virtual bool Initialize();
	virtual bool Uninitialize();

	void Start();
	void Stop();
	void Send(IMessage* message);
	void Update(float dt);

	void ShowDebugInfo(IMessage* message);

	typedef Delegate<void ( const StringRef&)> DebugInfoUpdateDelegate;
	Event<void ( const StringRef&)> OnDebugInfoUpdated;
private:
	static void OnMessageThread(Thread& thread);
	void ProcessMessage(Thread& thread);
protected:
	Thread mThread;
	LinkedList<IMessage*> mMessages;
	Dictionary<size_t,IMessageHandler*> mMessageHandlers;
	StackString<256> mDebugInfo;

	ThreadEvent mThreadEvent;
	NonRecursiveMutex mMessageMutex;
};

MEDUSA_END;
