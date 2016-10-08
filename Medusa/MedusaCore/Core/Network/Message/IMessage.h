// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "MessageDefines.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Chrono/StopWatch.h"
#include "Core/Command/ICommand.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/StaticConstructor.h"

MEDUSA_BEGIN;

/*
Id!=0 && SessionId!=0 : Request need response
Id!=0 && SessionId==0 : Request without response

Id==0 && SessionId!=0 : Reponse to request
Id==0 && SessionId==0 : Heartbeat without response
*/

class IMessage :public ICommand
{
	MEDUSA_RTTI(IMessage,ICommand);
public:
	IMessage(uint fromServiceId = 0, uint toServcieId = 0);
	virtual ~IMessage(void);
public:
	virtual uint StaticId()const = 0;
	uint Version() const { return mVersion; }
	void SetVersion(uint val) { mVersion = val; }
	uint Id() const { return mId; }
	void SetId(uint val) { mId = val; }
	uint SessionId() const { return mSessionId; }
	void SetSessionId(uint val) { mSessionId = val; }
	uint ConnectionId() const { return mConnectionId; }
	void SetConnectionId(uint val) { mConnectionId = val; }

	bool CheckTimeout();

	int MillisecondsTimeout() const { return mMillisecondsTimeout; }
	void SetMillisecondsTimeout(int val) { mMillisecondsTimeout = val; }

	MessageState State() const { return mState; }
	void SetState(MessageState val) { mState = val; }

	bool IsRequest()const;
	bool IsResponse()const;
	MessageBehavior Behavior()const;
	virtual bool NeedResponse()const = 0;
public:
	virtual bool OnSend(MessageSocketConnection& connection);
	virtual bool OnRequest(MessageSocketConnection& connection);
	virtual bool OnResponse(MessageSocketConnection& connection);
	virtual MemoryData SerializeRequest() const { return MemoryData::Empty; }
	virtual MemoryData SerializeResponse() const { return MemoryData::Empty; }
	virtual bool DeserializeRequest(const MemoryData& val) { return true; }
	virtual bool DeserializeResponse(const MemoryData& val) { return true; }

	Event<void(IMessage&, MessageSocketConnection& connection)> OnRequestEvent;
	Event<void(IMessage&, MessageSocketConnection& connection)> OnResponseEvent;
	Event<void(IMessage&, MessageSocketConnection& connection)> OnSendEvent;

protected:
	void* mUserData = nullptr;
	MessageState mState = MessageState::None;

	uint mVersion = 0;	//used to indicate application message version
	uint mId = 0;	//message type id
	uint mSessionId = 0;	//0:response
	uint mConnectionId = 0;	//used to indicate a connection

	StopWatch mTimeoutWatch;
	int mMillisecondsTimeout = 0;
	StopWatch mPerformanceWatch;

	//callbacks
};


//[PRE_DECLARE_BEGIN]
typedef Share<IMessage> ShareMessage;
//[PRE_DECLARE_END]


#define MEDUSA_DECLARE_MESSAGE(className,baseClassName) 													\
		MEDUSA_RTTI(className,baseClassName);\
public:																				\
	const static StaticConstructor mStaticConstructor;							

#define MEDUSA_IMPLEMENT_MESSAGE(className) 																					 \
	const StaticConstructor className::mStaticConstructor([]{MessageFactory::Instance().Register<className>(className::mStaticId);});					 

MEDUSA_END;
