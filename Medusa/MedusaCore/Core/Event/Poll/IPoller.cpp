// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IPoller.h"
#include "Core/Event/Channel/IEventChannel.h"

MEDUSA_BEGIN;

IPoller::IPoller(EventLoop* loop/*=nullptr*/)
	:mLoop(loop)
{
	
}

IPoller::~IPoller(void)
{
	
}


bool IPoller::HasChannel(IEventChannel* channel) const
{
	return mChannelDict.Contains(channel);
}


void IPoller::AddChannel(IEventChannel* channel)
{
	mChannels.Add(channel);
	mChannelDict.Add( channel);
	channel->SetPollIndex((uint)mChannels.Count()-1);
}

bool IPoller::RemoveChannel(IEventChannel* channel)
{
	if (mChannelDict.Remove(channel))
	{
		mChannels.RemoveAt(channel->PollIndex());
		channel->SetPollIndex(Math::UIntMaxValue);
		return true;
	}
	return false;
}

MEDUSA_END;
