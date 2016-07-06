// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "LogDefines.h"
#include "Core/String/HeapString.h"
#include "Core/Threading/ThreadingDefines.h"
#include "Core/Pattern/SwapValue.h"
#include "Core/Threading/Mutex.h"
#include "LogMessage.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class ILogger
{
public:
	using MessageList = SwapValue<List<Share<LogMessage>>>;
	using WMessageList = SwapValue<List<Share<WLogMessage>>>;
public:
	ILogger(StringRef name = StringRef::Empty);
	virtual ~ILogger(void);

	virtual void Update(float dt = 0.f);

public:
	void Add(const Share<LogMessage>& message);
	void Add(const Share<WLogMessage>& message);

protected:
	virtual void Print(const Share<LogMessage>& message)=0;
	virtual void Print(const Share<WLogMessage>& message)=0;
	bool IsCurrentThread()const;
protected:
	HeapString mName;
	ThreadId mCurrentThread = 0;

	MessageList mMessageList;
	WMessageList mWMessageList;
	Mutex mMutex;
};

MEDUSA_END;
