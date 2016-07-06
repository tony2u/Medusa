// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IEventChannel.h"
#include "Core/Event/Loop/EventLoop.h"

MEDUSA_BEGIN;

IEventChannel::IEventChannel(EventLoop* loop/*=nullptr*/)
	:mLoop(loop), mActiveTimestamp(std::chrono::high_resolution_clock::now())
{
	
}

IEventChannel::~IEventChannel(void)
{
	
}

void IEventChannel::FiredEvents()
{
	ChannelEventFlags val=mFiredEvents;
	mFiredEvents = ChannelEventFlags::None;

	if (MEDUSA_FLAG_HAS(val,ChannelEventFlags::Read))
	{
		OnActive();
		OnRead();
	}
	if (!mIsAlive)
	{
		return;
	}

	if (MEDUSA_FLAG_HAS(val, ChannelEventFlags::Write))
	{
		OnActive();
		OnWrite();
	}

	if (MEDUSA_FLAG_HAS(val, ChannelEventFlags::Timeout))
	{
		OnTimeout();
	}

	if (MEDUSA_FLAG_HAS(val, ChannelEventFlags::Retry))
	{
		OnRetry();
	}

	if (MEDUSA_FLAG_HAS(val, ChannelEventFlags::Fault))
	{
		OnError();
	}
	
	if (MEDUSA_FLAG_HAS(val, ChannelEventFlags::Idle))
	{
		OnIdle();
	}

}

IPoller* IEventChannel::Poller() const
{
	if (mLoop!= nullptr)
	{
		return mLoop->Poller();
	}
	return nullptr;
}


void IEventChannel::SubmitToLoop()
{
	if (IsInPoll(mLoop->Poller()))
	{
		return;
	}

	if (mLoop!=nullptr)
	{
		mLoop->AddChannel(this);
	}
}



void IEventChannel::DetachFromLoop()
{
	if (!IsInPoll(mLoop->Poller()))
	{
		return;
	}

	if (mLoop != nullptr)
	{
		mLoop->RemoveChannel(this);
	}
}

void IEventChannel::Close()
{
	if (mLoop->IsInLoop())
	{
		OnClose();
	}
	else
	{
		mLoop->QueueInLoop([this] {this->OnClose(); });
	}
}


bool IEventChannel::IsIdle(const TimePoint& now) const
{
	if (mIdleMilliseconds>0)
	{
		auto delta = now - mActiveTimestamp;
		auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
		return dt > mIdleMilliseconds;
	}
	return false;
}

void IEventChannel::OnRead()
{
}

void IEventChannel::OnWrite()
{
}

void IEventChannel::OnActive()
{
	mActiveTimestamp = std::chrono::high_resolution_clock::now();
	OnActiveEvent.Invoke(*this);
}

void IEventChannel::OnClose()
{
	mIsAlive = false;
	DetachFromLoop();
	OnCloseEvent(*this);
}

void IEventChannel::OnError()
{
	DetachFromLoop();
	OnErrorEvent(*this);
}


void IEventChannel::OnTimeout()
{

}

void IEventChannel::OnRetry()
{
	DetachFromLoop();
}

MEDUSA_END;

