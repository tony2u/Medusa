// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/System/PublishTarget.h"
#include "Application/ApplicationDebugInfoFlags.h"
#include "Platform/EngineFeatures.h"

MEDUSA_BEGIN;

class IGameClientSettings :public IInitializable
{
public:
	PublishTarget Tag()const { return PublishTarget(Version(), Device(), Language()); }
	PublishTarget ResultTag()const;
	Size2F DesignWinSize()const;
	virtual ~IGameClientSettings(){}
public:
	virtual bool IsMockEnabled()const = 0;
	virtual bool IsCheatEnabled()const = 0;
	virtual bool IsDebugEnabled()const = 0;
	virtual bool IsFileUpdateEnabled()const = 0;
	virtual ApplicationDebugInfoFlags DebugInfo()const = 0;
	virtual EngineFeatures EngineFeature()const = 0;

	virtual uint MessageVersion()const = 0;
	virtual uint LoginServerId()const = 0;

	virtual StringRef UpdateServerConfigName()const = 0;
	virtual StringRef UpdateServerUrl()const = 0;
	virtual PublishVersions Version()const = 0;
	virtual PublishDevices Device()const = 0;
	virtual PublishLanguages Language()const = 0;

	virtual float MessageTimeout()const = 0;
	virtual float AutoSaveDuration()const = 0;
	virtual uint MessageRetryTimes()const = 0;
	virtual uint MessageRetryInterval()const = 0;

	virtual uint HTTPConnectTimeoutSeconds()const = 0;
	virtual uint HTTPReadTimeoutSeconds()const = 0;
	virtual uint HTTPReadLowSpeedLimit()const = 0;
	virtual uint HTTPReadLowSpeedTime()const = 0;

	virtual float ToastShowTime()const = 0;
public:
	virtual uint64 Coders()const { return 0; }
	virtual MemoryByteData CoderKey()const { return MemoryByteData::Empty; }
};


MEDUSA_END;