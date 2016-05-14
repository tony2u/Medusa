// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/System/PublishTarget.h"
#include "Application/ApplicationDebugInfoFlags.h"
#include "Platform/EngineFeatures.h"
#include "Core/Module/IModule.h"
#include "Core/IO/FileId.h"
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

class ApplicationSettings :public Singleton<ApplicationSettings>, public IModule
{
	ApplicationSettings();
	virtual ~ApplicationSettings() = default;
	friend class Singleton<ApplicationSettings>;
public:
	void SetSettingsFile(FileIdRef val) { mSettingsFile = val; }

	PublishTarget Tag()const {return mTag;}
	PublishTarget ResultTag()const;
	Size2F DesignWinSize()const;
	Size2F ResultWinSize()const;
	ApplicationDebugInfoFlags ResultDebugInfo() const;

public:
	PublishVersions Version()const { return mTag.Version; }
	void SetVersion(PublishVersions val) { mTag.Version = val; }
	PublishDevices Device()const { return mTag.Device; }
	void SetDevice(PublishDevices val) { mTag.Device = val; }
	PublishLanguages Language()const { return mTag.Language; }
	void SetLanguage(PublishLanguages val) { mTag.Language = val; }

	ApplicationDebugInfoFlags DebugInfo() const { return mDebugInfo; }
	void SetDebugInfo(ApplicationDebugInfoFlags val) { mDebugInfo = val; }

	bool IsDebug() const { return mIsDebug; }
	void SetDebug(bool val) { mIsDebug = val; }

	EngineFeatures Features() const { return mFeatures; }
	EngineFeatures& MutableFeatures() { return mFeatures; }

	void SetFeatures(EngineFeatures val) { mFeatures = val; }

	bool HasScriptBinding() const;
	void EnableScriptBinding(bool val) { mHasScriptBinding = val; }

	const List<HeapString>& NodeEditors() const { return mNodeEditors; }

	void Apply()const;
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty)override;
protected:
	FileId mSettingsFile;
	ApplicationDebugInfoFlags mDebugInfo;
	PublishTarget mTag;
	EngineFeatures mFeatures;
	bool mIsDebug = false;
	bool mHasScriptBinding=false;
	
	List<HeapString> mNodeEditors;	//find editors in order
};


MEDUSA_END;