// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "MessageDispatcher.h"
#include "Core/Log/Log.h"
#include "Core/Threading/ScopedLock.h"
#include "Core/Message/Handler/TcpMessageHandler.h"
#include "Core/Message/Handler/MessageHandlerFactory.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Threading/ScopedLock.h"

MEDUSA_BEGIN;


MessageDispatcher::MessageDispatcher(void)
{
	mThread.SetCallback(ThreadCallback(OnMessageThread));
	mThreadEvent.Initialize();
}


MessageDispatcher::~MessageDispatcher(void)
{
	ClearUp();
	mThreadEvent.Uninitialize();
}

bool MessageDispatcher::Initialize()
{
	return Socket::ISocket::InitializeAPI();

}

bool MessageDispatcher::Uninitialize()
{
	Stop();
	ClearUp();
	return Socket::ISocket::UninitializeAPI();
}

void MessageDispatcher::AddMessageServer(ServerType serverType, size_t id, StringRef address, ushort port, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey)
{
	RemoveMessageHandler(id);
	IMessageHandler* loginHandler = MessageHandlerFactory::Instance().Create(serverType, id, address, port, retryTimes, retryInternal, messageVersion, sendCoderType, receiveCoderType, encryptKey);
	AddMessageHandler(loginHandler);
}


void MessageDispatcher::ClearUp()
{
	ScopedLock lock(mMessageMutex);

	SAFE_DELETE_DICTIONARY_VALUE(mMessageHandlers);
	SAFE_DELETE_COLLECTION(mMessages);

}


void MessageDispatcher::AddMessageHandler(IMessageHandler* handler)
{
	ScopedLock lock(mMessageMutex);

	if (mMessageHandlers.ContainsKey(handler->Id()))
	{
		Log::AssertFailedFormat("Duplicate handler by id {}", handler->Id());
	}

	mMessageHandlers.Add(handler->Id(), handler);
}


void MessageDispatcher::RemoveMessageHandler(size_t handlerId)
{
	ScopedLock lock(mMessageMutex);

	IMessageHandler* server = mMessageHandlers.TryGetValueWithFailed(handlerId, nullptr);
	if (server != nullptr)
	{
		mMessageHandlers.RemoveKey(handlerId);
		SAFE_DELETE(server);
	}

}


void MessageDispatcher::Start()
{
	mThread.Start();
}

void MessageDispatcher::Stop()
{
	//mThread.Kill(0);
	mThread.PrepareToCancel();


	mThreadEvent.Set();

	mThread.Join();

}


void MessageDispatcher::Send(IMessage* message)
{
	LOG_ASSERT_NOT_NULL(message);

	size_t handlerId = message->HandlerId();
	if (mMessageHandlers.ContainsKey(handlerId))
	{
		message->Retain();	//ref:2
		mMessages.Add(message);
	}
	else
	{
		Log::AssertFailedFormat("Invalid message handler Id:{}", handlerId);
	}

}


void MessageDispatcher::OnMessageThread(Thread& thread)
{
	while (true)
	{
		MessageDispatcher::Instance().ProcessMessage(thread);
		//Thread::Sleep(0);
		if (thread.IsCancelled())
		{
			break;
		}
	}

}

void MessageDispatcher::ProcessMessage(Thread& thread)
{
	ScopedLock lock(mMessageMutex);

	while (true)
	{
		bool hasMessages = false;
		FOR_EACH_COLLECTION(i, mMessageHandlers)
		{
			IMessageHandler* handler = i->Value;
			if (!handler->IsEmpty())
			{
				hasMessages = true;
				break;
			}
		}

		if (hasMessages)
		{
			break;
		}
		else
		{
			if (!thread.IsCancelled())
			{
				mThreadEvent.Wait();
			}
			else
			{
				break;
			}
		}


	}

	FOR_EACH_COLLECTION(i, mMessageHandlers)
	{
		IMessageHandler* handler = i->Value;
		handler->Process();
	}

}


void MessageDispatcher::Update(float dt)
{
	//running on UI thread
	LinkedList<IMessage*>::NodePtr node = mMessages.FirstNode();
	while (node != nullptr&&node->Value != nullptr)
	{
		IMessage* message = node->Value;
		switch (message->State())
		{
			case MessageState::None:
				message->PrepareReadyForSend();
				node = node->Next;
				break;
			case MessageState::ReadyForSend:
			{
				ScopedLock lock(mMessageMutex);
				IMessageHandler* messageHandler = mMessageHandlers[message->HandlerId()];	//had checked before
				messageHandler->Push(message);	//ref:3
				message->SetState(MessageState::Running);
				node = node->Next;
			}

			mThreadEvent.Set();
			break;
			case MessageState::Running:
				message->Update(dt);
				node = node->Next;
				break;
			case MessageState::ReadyForNext:
				message->PrepareToNextRunning();
				node = node->Next;
				break;
			case MessageState::NextRunning:
				message->Update(dt);
				node = node->Next;
				break;
			case MessageState::Completed:
			case MessageState::ConnectFail:
			{
				if (!message->IsSubMessage())
				{
					message->BeforeEnd();

					//show debug info
					ShowDebugInfo(message);
				}

				node = mMessages.Delete(node);
				SAFE_RELEASE(message);	//ref:0
				break;
			}

		}
	}

}

void MessageDispatcher::ShowDebugInfo(IMessage* message)
{
	RETURN_IF_FALSE(message->IsProfileEnabled());

	StringRef messageName = message->Class().Name();

	Log::FormatInfo("{} Total:{:f3} Send:{:f3} Receive:{:f3}", messageName.c_str(), message->TotalElapsedMilliseconds(), message->SendElapsedMilliseconds(), message->ReceiveElapsedMilliseconds());
	mDebugInfo.Format("{:f3} {:f3} {:f3}", message->TotalElapsedMilliseconds(), message->SendElapsedMilliseconds(), message->ReceiveElapsedMilliseconds());
	OnDebugInfoUpdated(mDebugInfo);
}



MEDUSA_END;
