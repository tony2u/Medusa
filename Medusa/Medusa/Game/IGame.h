// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Runnable/DefaultRunnable.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/IUpdatable.h"
#include "Core/Pattern/StaticConstructor.h"
#include "Core/String/HeapString.h"
//#include "Core/IO/Updater/FileUpdaterMessageType.h"
#include "Core/Config/AppCompatibility.h"
#include "GameFeatures.h"

MEDUSA_BEGIN;
/*
??????????,?????????????
??????????????,?????????????????????,???????????????

*/
class IGame:public IInitializable,public DefaultRunnable,public IUpdatable
{
public:
	IGame(void);
	virtual ~IGame(void);
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Start()override;

	virtual bool Load();

	virtual bool Update(float dt)override;

	StringRef Name() const { return mName; }
	void SetName(StringRef val) { mName = val; }
	virtual const IGameClientSettings* BaseSettings() const { return mSettings; }
	virtual const IPlayer* BasePlayer() const { return mPlayer; }
	GameFeatures Features() const { return mFeatures; }

protected:
	virtual void OnSetupGraphicsContext();

	virtual bool OnPrepareFileSystem();
	virtual bool OnPrepareSettings() { return true; }

	virtual bool OnLoadSettings() { return true; }
	virtual bool OnLoadFileSystem();

#pragma region Script
	virtual bool OnRegisterScriptTypes();

	virtual bool OnLoadInternalScripts();
	virtual bool OnUnloadInternalScripts();
	virtual bool OnBuildInternalScripts();
	virtual bool OnCreateInternalScriptObjects();

	virtual bool OnLoadExternalScripts();
	virtual bool OnUnloadExternalScripts();
	virtual bool OnBuildExternalScripts();
	virtual bool OnCreateExternalScriptObjects();
#pragma endregion Script

	virtual bool OnLoadFileUpdater();


	virtual bool OnLoadPlayer() { return true; }
	virtual void OnCheckCompatibility();

	virtual bool OnLoadCustomConfigs() { return true; }

	/*virtual void OnShowFileUpdaterMessage(FileUpdater* sender, FileUpdaterMessageType message);*/
	virtual void OnMessageDebugInfo(const StringRef& debugInfo);

	virtual void OnInitializeCompleted();
	virtual void OnLoadCompleted();


protected:
	HeapString mName;
	IGameClientSettings* mSettings;
	IPlayer* mPlayer;
	GameFeatures mFeatures;
	AppCompatibility mCompatibility;
};


#define MEDUSA_DECLARE_GAME() 													\
private:																				\
	const static StaticConstructor mStaticConstructor;							\
	static void RegisterSelfToApplication();

#define MEDUSA_IMPLEMENT_GAME(className) 																					 \
	const StaticConstructor className::mStaticConstructor(RegisterSelfToApplication);					 \
	void className::RegisterSelfToApplication(){Application::Instance().RegisterGame(DefaultNewer<className*>::New);}

MEDUSA_END;
