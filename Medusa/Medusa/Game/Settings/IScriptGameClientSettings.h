// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT
#include "MedusaPreDeclares.h"
#include "IGameClientSettings.h"
#include "IScriptSettings.h"

MEDUSA_BEGIN;

class IScriptGameClientSettings :public IGameClientSettings,public IScriptSettings
{
public:
	using IScriptSettings::IScriptSettings;
public:
	virtual bool IsMockEnabled()const override { return GetDefault<bool>("IsMockEnabled", false); }
	virtual bool IsCheatEnabled()const override { return GetDefault<bool>("IsCheatEnabled", false); }
	virtual bool IsDebugEnabled()const override { return GetDefault<bool>("IsDebugEnabled", false); }
	virtual bool IsFileUpdateEnabled()const override { return GetDefault<bool>("IsFileUpdateEnabled", false); }
	virtual ApplicationDebugInfoFlags DebugInfo()const override { return GetDefault<ApplicationDebugInfoFlags>("DebugInfo", ApplicationDebugInfoFlags::None); }
	virtual EngineFeatures EngineFeature()const override { return GetDefault<EngineFeatures>("EngineFeature", EngineFeatures::None); }


	virtual uint MessageVersion()const override { return GetDefault<uint>("MessageVersion", 1); }
	virtual uint LoginServerId()const override { return GetDefault<uint>("LoginServerId", 1); }


	virtual StringRef UpdateServerConfigName()const override{ return GetDefault<StringRef>("UpdateServerConfigName", StringRef::Empty); }
	virtual StringRef UpdateServerUrl()const override { return GetDefault<StringRef>("UpdateServerUrl", StringRef::Empty); }
	virtual PublishVersions Version()const override { return GetDefault<PublishVersions>("Version", PublishVersions::main); }
	virtual PublishDevices Device()const override { return GetDefault<PublishDevices>("Device", PublishDevices::hd); }
	virtual PublishLanguages Language()const override { return GetDefault<PublishLanguages>("Language", PublishLanguages::enus); }


	virtual float MessageTimeout()const override { return GetDefault<float>("MessageTimeout", 5.f); }
	virtual float AutoSaveDuration()const override { return GetDefault<float>("AutoSaveDuration", 5.f); }
	virtual uint MessageRetryTimes()const override { return GetDefault<uint>("MessageRetryTimes", 5); }
	virtual uint MessageRetryInterval()const override { return GetDefault<uint>("MessageRetryInterval", 1000); }

	virtual uint HTTPConnectTimeoutSeconds()const override { return GetDefault<uint>("HTTPConnectTimeoutSeconds", 5); }
	virtual uint HTTPReadTimeoutSeconds()const override { return GetDefault<uint>("HTTPReadTimeoutSeconds", 5); }
	virtual uint HTTPReadLowSpeedLimit()const override { return GetDefault<uint>("HTTPReadLowSpeedLimit", 10); }
	virtual uint HTTPReadLowSpeedTime()const override { return GetDefault<uint>("HTTPReadLowSpeedTime", 10); }

	virtual float ToastShowTime()const override { return GetDefault<float>("ToastShowTime", 0.5f); }

};


MEDUSA_END;

#endif