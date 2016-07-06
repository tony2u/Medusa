// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "ChannelDefines.h"
#include "Core/Pattern/Event.h"
#include "Core/Memory/NetworkBuffer.h"

MEDUSA_BEGIN;

class IEventChannel
{
public:
	using TimePoint = std::chrono::time_point< std::chrono::high_resolution_clock>;
public:
	IEventChannel(EventLoop* loop = nullptr);

	virtual ~IEventChannel(void);

	ChannelEventFlags CaredEvents() const { return mCaredEvents; }
	void SetCaredEvents(ChannelEventFlags val) { mCaredEvents = val; }
	void AddCaredEvents(ChannelEventFlags val) { MEDUSA_FLAG_ADD(mCaredEvents, val); }

	ChannelEventFlags GetFiredEvents() const { return mFiredEvents; }
	void SetFiredEvents(ChannelEventFlags val) { mFiredEvents = val; }
	void AddFiredEvents(ChannelEventFlags val) { MEDUSA_FLAG_ADD(mFiredEvents, val); }
	bool HasFiredEvents()const { return mFiredEvents != ChannelEventFlags::None; }

	void BeginRead() { AddCaredEvents(ChannelEventFlags::Read); }
	void BeginWrite() { AddCaredEvents(ChannelEventFlags::Write); }
	void BeginReadWrite() { AddCaredEvents(ChannelEventFlags::ReadWrite); }


	void FiredEvents();
	uint PollIndex() const { return mPollIndex; }
	void SetPollIndex(uint val) { mPollIndex = val; }

	bool IsInPoll(IPoller* poller)const { return mPollIndex != Math::UIntMaxValue&&Poller() == poller; }
	IPoller* Poller()const;

	EventLoop* Loop() const { return mLoop; }
	void SetLoop(EventLoop* val) { mLoop = val; }

	virtual void SubmitToLoop();
	virtual void DetachFromLoop();

	virtual MedusaFileDescriptor EventHandle() const = 0;
	void Close();

public:
	using EventType = Event<void(IEventChannel&)>;
	EventType OnReadEvent;
	EventType OnWriteEvent;
	EventType OnCloseEvent;
	EventType OnErrorEvent;
	EventType OnActiveEvent;
public:
	uint IdleMilliseconds() const { return mIdleMilliseconds; }
	void SetIdleMilliseconds(uint val) { mIdleMilliseconds = val; }

	bool IsIdle(const TimePoint& now)const;
	bool IsAlive()const { return mIsAlive; }
protected:
	virtual void OnRead();
	virtual void OnWrite();
	virtual void OnClose();
	virtual void OnError();
	virtual void OnTimeout();
	virtual void OnRetry();
	virtual void OnIdle() {}
	virtual void OnActive();

protected:
	EventLoop* mLoop = nullptr;
	uint mPollIndex = Math::UIntMaxValue;	//UIntMaxValue to indicate not in poll
	ChannelEventFlags mCaredEvents = ChannelEventFlags::None;
	ChannelEventFlags mFiredEvents = ChannelEventFlags::None;

	const static uint mInitialMessageBufferSize = 4096;	//4K
	NetworkBuffer mReadBuffer;
	NetworkBuffer mWriteBuffer;

	TimePoint mActiveTimestamp;
	uint mIdleMilliseconds = 0;
	bool mIsAlive = true;
};

MEDUSA_END;
