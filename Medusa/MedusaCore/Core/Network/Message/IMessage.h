// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Network/Socket/SocketDefines.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Command/EventArg/IEventArg.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/RTTI/RTTIObject.h"
#include "Core/Profile/StopWatch.h"

#include "MessageErrorReportSuppress.h"

MEDUSA_BEGIN;



enum class MessageError
{
	Success=0,
	ConnectFail=-1,

};

//None->ReadyForSend->Running->Completed/ConnectFail

enum class MessageState
{
	ConnectFail=-1,
	None=0,
	Running=2,
	Completed=3,
};


class IMessage:public RTTIObject
{
	MEDUSA_DECLARE_RTTI_ROOT;

public:
	typedef Delegate<void (IMessage* sender,MessageEventArg)> MessageEventHandler;

	IMessage();
	virtual ~IMessage(void);
public:
	void Retain();
	void Release();
	bool IsDead()const{return mRefCount==0;}
	virtual StringRef ResponseClassName()const{return nullptr;}				
public:
	const MessageEventHandler& SendHandler()  { return mSendHandler; }
	void SetSendHandler(const MessageEventHandler& val) { mSendHandler = val; }

	const MessageEventHandler& ReceiveHandler()  { return mReceiveHandler; }
	void SetReceiveHandler(const MessageEventHandler& val) { mReceiveHandler = val; }

	const MessageEventHandler& CompleteHandler()  { return mCompleteHandler; }
	void SetCompleteHandler(const MessageEventHandler& val) { mCompleteHandler = val; }

	const MessageEventHandler& RootHandler() { return mRootHandler; }
	void SetRootHandler(const MessageEventHandler& val) { mRootHandler = val; }

	void SetError(MessageError val) { mError = val; }
	void SetError(SocketError val);
	virtual int ServerError()const=0;
	virtual int CustomError()const=0;


	MessageState State() const { return mState; }
	void SetState(MessageState val) { mState = val; }

	float Timeout() const { return mTimeout; }
	void SetTimeout(float val) { mTimeout = val;mTimeLeft=mTimeout; }


	virtual bool HasResponse()const{return false;}
	virtual bool IsResultOk()const=0;

	bool IsTimeout()const{return mTimeLeft<0.f;}

	virtual MemoryData SerializeRequest()const{return MemoryData::Empty;};
	virtual void ParseFromRequest(MemoryData data){};
	virtual void PrintRequest()const{};

	virtual MemoryData SerializeResponse()const{return MemoryData::Empty;};
	virtual void ParseFromResponse(MemoryData data){};
	virtual void PrintResponse()const{};

	void Send();
	void Send(MessageEventHandler handler);

	size_t ServiceId() const { return mServiceId; }
	void SetServiceId(size_t val) { mServiceId = val; }


	MessageErrorReportSuppress ErrorReportSuppress() const { return mErrorReportSuppress; }
	void SetErrorReportSuppress(MessageErrorReportSuppress val) { mErrorReportSuppress = val; }

	int GetSocketError() const { return mSocketError; }
	void SetSocketError(int val) { mSocketError = val; }

	bool IsProfileEnabled() const { return mIsProfileEnabled; }
	void EnableProfile(bool val) { mIsProfileEnabled = val; }
	float SendElapsedMilliseconds() const { return mSendElapsedMilliseconds; }
	void SetSendElapsedMilliseconds(float val) { mSendElapsedMilliseconds = val; }

	float ReceiveElapsedMilliseconds() const { return mReceiveElapsedMilliseconds; }
	void SetReceiveElapsedMilliseconds(float val) { mReceiveElapsedMilliseconds = val; }

	float TotalElapsedMilliseconds() const { return mTotalStopWatch.ElapsedMilliseconds(); }
public:
	virtual void BeforeEnd();
	virtual void Mock(){}

	virtual void Update(float dt);
protected:
	MessageError GetError() const { return mError; }
protected:
	size_t mServiceId;
	void* mUserData;

	MessageEventHandler mSendHandler;
	MessageEventHandler mReceiveHandler;
	MessageEventHandler mCompleteHandler;
	MessageEventHandler mRootHandler;

	MessageError mError;
	MessageState mState;
	int mSocketError;
	
	float mTimeout;
	float mTimeLeft;

	bool mIsProfileEnabled;
	
	StopWatch mTotalStopWatch;	
	float mSendElapsedMilliseconds;
	float mReceiveElapsedMilliseconds;
	size_t mRefCount;

	MessageErrorReportSuppress mErrorReportSuppress;


};

MEDUSA_END;
