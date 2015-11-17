// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Queue.h"
#include "Core/Message/IMessage.h"
#include "Core/String/HeapString.h"
#include "Core/Profile/StopWatch.h"
#include "Core/Coder/CoderType.h"

MEDUSA_BEGIN;

class IMessageHandler
{
public:
	IMessageHandler(size_t id, StringRef hostName, ushort port, uint retryTimes, uint retryInternal, uint messageVersion, CoderType sendCoderType, CoderType receiveCoderType, const MemoryByteData& encryptKey);
	virtual ~IMessageHandler();
public:
	size_t Id() const { return mId; }
	virtual void Push(IMessage* message);
	virtual void Process()=0;
	
	bool IsEmpty()const{return mMessageQueue.IsEmpty();}

	uint RetryTimes() const { return mRetryTimes; }
	void SetRetryTimes(uint val) { mRetryTimes = val; }

	uint RetryInternal() const { return mRetryInternal; }
	void SetRetryInternal(uint val) { mRetryInternal = val; }

	float TotalElapsedMilliseconds()const{return mTotalStopWatch.ElapsedMilliseconds();}
	float ConnectElapsedMilliseconds()const{return mConnectStopWatch.ElapsedMilliseconds();}

protected:
	void FireUIEventAsync(IMessage::MessageEventHandler handler,IMessage* message);
protected:
	size_t mId;
	HeapString mHostName;
	ushort mPort;

	Queue<IMessage*> mMessageQueue;
	uint mRetryTimes;
	uint mRetryInternal;

	StopWatch mTotalStopWatch;
	StopWatch mConnectStopWatch;
	StopWatch mSendStopWatch;
	StopWatch mReceiveStopWatch;

	uint mMessageVersion;
	CoderType mSendCoderType;
	CoderType mReceiveCoderType;

	MemoryByteData mMessageEncryptKey;
	ICoder* mSendCoder;
	ICoder* mReceiveCoder;

};



MEDUSA_END;
