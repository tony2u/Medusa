// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "IPoller.h"

#ifdef MEDUSA_WINDOWS
#include <WinSock2.h>
#endif

MEDUSA_BEGIN;

class SelectPoller :public IPoller
{
	MEDUSA_RTTI(SelectPoller,IPoller);
public:
	using IPoller::IPoller;
	virtual ~SelectPoller(void);

public:
	virtual ChannelEventResult Poll(uint timeoutMilliseconds = 0)override;
protected:
	fd_set mReadSet;	//limit is 64, is ok just for test
	fd_set mWriteSet;

	List<IEventChannel*> mActiveChannels;

};

MEDUSA_END;
