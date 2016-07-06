// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/HashSet.h"
#include "Core/Event/Channel/ChannelDefines.h"
#include "Core/Pattern/RTTI/RTTIObject.h"

MEDUSA_BEGIN;


class IPoller:public RTTIObject
{
	MEDUSA_RTTI_ROOT(IPoller);
public:
	IPoller(EventLoop* loop = nullptr);
	virtual ~IPoller(void);

	EventLoop* Loop() const { return mLoop; }
	void SetLoop(EventLoop* val) { mLoop = val; }

	bool HasChannel(IEventChannel* channel)const;

	void AddChannel(IEventChannel* channel);
	bool RemoveChannel(IEventChannel* channel);
	virtual ChannelEventResult Poll(uint timeoutMilliseconds = 0) = 0;
	bool IsEmpty()const { return mChannels.IsEmpty(); }
protected:
	EventLoop* mLoop = nullptr;

	List<IEventChannel*> mChannels;
	HashSet<IEventChannel*> mChannelDict;


};

MEDUSA_END;
