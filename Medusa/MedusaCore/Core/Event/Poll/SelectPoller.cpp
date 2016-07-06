// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SelectPoller.h"
#include "Core/Event/Channel/IEventChannel.h"
#include "Core/Network/Socket/Socket.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

SelectPoller::~SelectPoller(void)
{

}

ChannelEventResult SelectPoller::Poll(uint timeoutMilliseconds /*= 0*/)
{
	FD_ZERO(&mReadSet);
	FD_ZERO(&mWriteSet);
	fd_set* readSetPtr = nullptr;
	fd_set* writeSetPtr = nullptr;

	MedusaFileDescriptor maxEventHandle = 0;
	for (auto channel : mChannels)
	{
		auto caredEvents = channel->CaredEvents();
		auto fd = channel->EventHandle();
		if (MEDUSA_FLAG_HAS(caredEvents, ChannelEventFlags::Read))
		{
			FD_SET(fd, &mReadSet);
			readSetPtr = &mReadSet;
		}

		if (MEDUSA_FLAG_HAS(caredEvents, ChannelEventFlags::Write))
		{
			FD_SET(fd, &mWriteSet);
			writeSetPtr = &mWriteSet;
		}

		maxEventHandle = Math::Max(maxEventHandle, fd);
	}

	if (readSetPtr == nullptr&&writeSetPtr == nullptr)
	{
		return ChannelEventResult::None;	//no event to select
	}

	timeval tval;
	const timeval* timeoutPtr = nullptr;
	if (timeoutMilliseconds >= 0)
	{
		tval.tv_sec = timeoutMilliseconds / 1000;
		tval.tv_usec = (timeoutMilliseconds % 1000) * 1000;
		timeoutPtr = &tval;
	}

	int selectResult = ::select((int)maxEventHandle + 1, readSetPtr, writeSetPtr, nullptr, timeoutPtr);	//>0 :count -1:error 0:timeout
	if (selectResult < 0)
	{
		int err = Socket::GetSocketError();
		Log::FormatError("Invalid select:{}", err);
		mActiveChannels = mChannels;

		for (auto channel : mActiveChannels)
		{
			channel->AddFiredEvents(ChannelEventFlags::Fault);
			channel->FiredEvents();
		}
		mActiveChannels.Clear();
		return ChannelEventResult::Fault;
	}
	else if (selectResult==0)
	{
		return ChannelEventResult::Timeout;
	}

	auto now = std::chrono::high_resolution_clock::now();
	//fill active channels
	for (auto channel : mChannels)
	{
		auto caredEvents = channel->CaredEvents();
		auto fd = channel->EventHandle();

		if (MEDUSA_FLAG_HAS(caredEvents, ChannelEventFlags::Read) && FD_ISSET(fd, &mReadSet))
		{
			channel->AddFiredEvents(ChannelEventFlags::Read);
		}

		if (MEDUSA_FLAG_HAS(caredEvents, ChannelEventFlags::Write) && FD_ISSET(fd, &mWriteSet))
		{
			channel->AddFiredEvents(ChannelEventFlags::Write);
		}

		int err = Socket::GetSocketError(fd);
		switch (err)
		{
		case 0:	//no error
			break;
		case EINPROGRESS:
		case EINTR:
		case EISCONN:
		case EWOULDBLOCK:
		case ETIMEDOUT:
			channel->AddFiredEvents(ChannelEventFlags::Timeout);
		
			break;
		case EAGAIN:
		case EADDRINUSE:
		case EADDRNOTAVAIL:
		case ECONNREFUSED:
		case ENETUNREACH:
			channel->AddFiredEvents(ChannelEventFlags::Retry);
			break;

		case EACCES:
		case EPERM:
		case EAFNOSUPPORT:
		case EALREADY:
		case EBADF:
		case EFAULT:
		case ENOTSOCK:
		default:
			channel->AddFiredEvents(ChannelEventFlags::Fault);
			break;
		}

		if (channel->HasFiredEvents())
		{
			mActiveChannels.Add(channel);
		}
		else if (channel->IsIdle(now))
		{
			channel->AddFiredEvents(ChannelEventFlags::Idle);
			mActiveChannels.Add(channel);
		}
	}

	//invoke events
	if (!mActiveChannels.IsEmpty())
	{
		for (auto channel : mActiveChannels)
		{
			channel->FiredEvents();
		}

		mActiveChannels.Clear();
	}
	else
	{
		return ChannelEventResult::None;
	}
	
	return ChannelEventResult::Success;

}


MEDUSA_END;

