// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Game/IGame.h"
#include "Core/IO/FileSystem.h"
#include "Game/Settings/IGameClientSettings.h"
#include "Game/Player/IPlayer.h"
#include "Core/String/StringTable/StringTable.h"
#include "Core/Command/Processor/MainCommandProcessor.h"
#include "Core/Command/Processor/ThreadCommandProcessor.h"
#include "Core/Message/MessageDispatcher.h"
#include "Core/System/System.h"

#include "Core/IO/File.h"
#include "Node/Scene/SceneManager.h"
#include "Node/Editor/SceneEditorFactory.h"
#include "Core/Script/ScriptEngine.h"
#include "MedusaScript.h"
#include "Content/Content.h"
#include "Graphics/ResolutionAdapter.h"
#include "Core/System/Environment.h"
#include "Core/Siren/Siren.h"


MEDUSA_BEGIN;

IGame::IGame(void)
	:mSettings(nullptr),
	mPlayer(nullptr)
{
	/*
	Sometimes, if play or cache's file format has been changed, but there is already a save file in "Save" dir.
	At this time, if the player update the app, it'll cause the new app cannot load previous saved file.
	Our strategy is to delete all files in "Save" dir.
	If you need to do this, here's the example:
	++version
	mCompatibility.set_operation(CoreProto::AppCompatibility_InitializeOperation_RemoveAllCache);

	*/
	mCompatibility.SetVersion(1);
	mCompatibility.SetOperation(AppInitializeOperation::RemoveAllCache);

}

IGame::~IGame(void)
{
	SAFE_DELETE(mSettings);
	SAFE_DELETE(mPlayer);
}

void IGame::OnSetupGraphicsContext()
{
}


bool IGame::Initialize()
{
	if (mFeatures.IsSupportThreadEvent())
	{
		ThreadCommandProcessor::Instance().Start();
	}

	if (mFeatures.IsSupportMessage())
	{
		MessageDispatcher::Instance().Initialize();
		MessageDispatcher::Instance().Start();
		MessageDispatcher::Instance().OnDebugInfoUpdated += Bind(&IGame::OnMessageDebugInfo, this);
	}

	RETURN_FALSE_IF_FALSE(OnPrepareSettings());
	RETURN_FALSE_IF_FALSE(OnPrepareFileSystem());
	
	if (mFeatures.IsSupportScript())
	{
		OnRegisterScriptTypes();
		OnLoadInternalScripts();
		OnBuildInternalScripts();
		OnCreateInternalScriptObjects();
	}

	if (mFeatures.IsSupportSceneEditor())
	{
		SceneEditorFactory::Instance().Initialize();
	}

	RETURN_FALSE_IF_FALSE(OnLoadSettings());
	RETURN_FALSE_IF_FALSE(OnLoadFileSystem());

	OnCheckCompatibility();
	OnSetupGraphicsContext();

#ifdef MEDUSA_DEBUG
	if (BaseSettings()!=nullptr&&BaseSettings()->IsDebugEnabled()&&!Environment::Instance().IsArm())
	{
		ResolutionAdapter::Instance().Initialize(BaseSettings()->DesignWinSize());
	}
	else
	{
		ResolutionAdapter::Instance().Initialize(Environment::Instance().ScreenSize());
	}

#else
	ResolutionAdapter::Instance().Initialize(Environment::Instance().ScreenSize());
#endif

	if (mFeatures.IsSupportFileUpdating())
	{
		RETURN_FALSE_IF_FALSE(OnLoadFileUpdater());
		OnInitializeCompleted();
	}
	else
	{
		RETURN_FALSE_IF_FALSE(OnLoadCustomConfigs());	//load custom config
		RETURN_FALSE_IF_FALSE(OnLoadPlayer());

		if (mFeatures.IsSupportScript())
		{
			RETURN_FALSE_IF_FALSE(OnLoadExternalScripts());
			RETURN_FALSE_IF_FALSE(OnBuildExternalScripts());
			RETURN_FALSE_IF_FALSE(OnCreateExternalScriptObjects());
		}

		OnLoadCompleted();
	}

	return true;
}


bool IGame::Load()
{
	StringTable::Instance().Unload();
	FileSystem::Instance().Uninitialize();
	if (mSettings!=nullptr)
	{
		mSettings->Uninitialize();
	}

	//reload
	RETURN_FALSE_IF_FALSE(OnPrepareSettings());
	RETURN_FALSE_IF_FALSE(OnPrepareFileSystem());
	RETURN_FALSE_IF_FALSE(OnLoadSettings());	//reload config
	RETURN_FALSE_IF_FALSE(OnLoadFileSystem());

	RETURN_FALSE_IF_FALSE(OnLoadCustomConfigs());	//load custom config
	RETURN_FALSE_IF_FALSE(OnLoadPlayer());

	RETURN_FALSE_IF_FALSE(OnLoadExternalScripts());
	RETURN_FALSE_IF_FALSE(OnBuildExternalScripts());
	RETURN_FALSE_IF_FALSE(OnCreateExternalScriptObjects());

	OnLoadCompleted();

	return true;
}


bool IGame::Update(float dt)
{
	RETURN_FALSE_IF_FALSE(IsRunning());

	return true;
}

bool IGame::Start()
{
	RETURN_FALSE_IF_FALSE(DefaultRunnable::Start());
	return true;
}


bool IGame::Uninitialize()
{
#ifdef MEDUSA_SCRIPT
	if (mFeatures.IsSupportScript())
	{
		RETURN_FALSE_IF_FALSE(OnUnloadInternalScripts());
		RETURN_FALSE_IF_FALSE(OnUnloadExternalScripts());
		ScriptEngine::Instance().Uninitialize();
	}
#endif

	if (mFeatures.IsSupportMessage())
	{
		MessageDispatcher::Instance().Uninitialize();
	}

	MainCommandProcessor::Instance().ClearWithoutRun();
	if (mFeatures.IsSupportThreadEvent())
	{
		ThreadCommandProcessor::Instance().StopAndClear();
	}

	StringTable::Instance().Unload();
	FileSystem::Instance().Uninitialize();
	if (mSettings!=nullptr)
	{
		mSettings->Uninitialize();
	}

	if (mPlayer != nullptr)
	{
		mPlayer->Save();
	}
	SAFE_DELETE(mPlayer);


	return true;
}


#pragma region Script
bool IGame::OnRegisterScriptTypes()
{
#ifdef MEDUSA_SCRIPT
	ScriptEngine::Instance().Initialize();
	MedusaScript::Instance().RegisterTypes();
#endif
	return true;
}


bool IGame::OnLoadInternalScripts()
{
#ifdef MEDUSA_SCRIPT
	MedusaScript::Instance().InitializeInternal();
#endif
	return true;
}
bool IGame::OnUnloadInternalScripts()
{
#ifdef MEDUSA_SCRIPT
	MedusaScript::Instance().UninitializeInternal();
#endif
	return true;
}

bool IGame::OnBuildInternalScripts()
{
#ifdef MEDUSA_SCRIPT
	return ScriptEngine::Instance().InternalModule()->Build();
#else
	return true;
#endif
}

bool IGame::OnCreateInternalScriptObjects()
{
#ifdef MEDUSA_SCRIPT
	MedusaScript::Instance().CreateInternalScriptObjects();
#endif
	return true;
}

bool IGame::OnLoadExternalScripts()
{
#ifdef MEDUSA_SCRIPT
	MedusaScript::Instance().InitializeExternal();
#endif
	return true;
}

bool IGame::OnUnloadExternalScripts()
{
#ifdef MEDUSA_SCRIPT
	MedusaScript::Instance().UninitializeExternal();
#endif
	return true;
}

bool IGame::OnCreateExternalScriptObjects()
{
#ifdef MEDUSA_SCRIPT
	MedusaScript::Instance().CreateExternalScriptObjects();
#endif
	return true;
}

bool IGame::OnBuildExternalScripts()
{
#ifdef MEDUSA_SCRIPT
	return ScriptEngine::Instance().ExternalModule()->Build();
#else
	return true;
#endif

}

#pragma endregion Script

bool IGame::OnPrepareFileSystem()
{
	System::Instance().Initialize("Res", "Save", "Temp");
	Content::RegisterToFileSystem();
	if (mSettings!=nullptr)
	{
		FileSystem::Instance().Initialize(mSettings->Coders(), mSettings->CoderKey());
	}
	else
	{
		FileSystem::Instance().Initialize();
	}

	return true;
}

bool IGame::OnLoadFileSystem()
{
	//initialize file system
	if (mSettings!=nullptr)
	{
		FileSystem::Instance().ApplyTag(mSettings->ResultTag());
	}
	

	return true;
}

bool IGame::OnLoadFileUpdater()
{
	if (mSettings!=nullptr&&mSettings->IsFileUpdateEnabled())
	{
		/*FileUpdater::Instance().Initialize(FileSystem::Instance().GetVersion(),
			mSettings->UpdateServerUrl(),
			mSettings->UpdateServerConfigName(),
			mSettings->HTTPConnectTimeoutSeconds(),
			mSettings->HTTPReadTimeoutSeconds(),
			mSettings->HTTPReadLowSpeedLimit(),
			mSettings->HTTPReadLowSpeedTime());

		FileUpdater::Instance().SetShowMessageHandler(Bind(&IGame::OnShowFileUpdaterMessage, this));*/
	}

	return true;
}


void IGame::OnCheckCompatibility()
{
	AppCompatibility prevCompatibility;
	HeapString writePath = System::Instance().GetWritablePath("/AppCompatibility.bin");
	if (File::Exists(writePath))
	{
		MemoryByteData data = File::ReadAllData(writePath);
		bool isSuccess = Siren::DeserializeBinaryTo(data, prevCompatibility);
		if (isSuccess)
		{
			if (mCompatibility.Version() != prevCompatibility.Version())
			{
				switch (mCompatibility.Operation())
				{
				case AppInitializeOperation::RemoveAllCache:
					//cleanup save path
					Directory::RemoveDirRecursively(System::Instance().WritablePath());
					Log::Info("Removed all cache because of compatibility!");
					break;
				default:
					break;
				}
			}


			return;
		}
		else
		{
			File::Delete(writePath);
		}

	}

	//save a copy
	MemoryByteData data = Siren::SerializeBinary(mCompatibility);
	File::WriteAllDataTo(data, writePath);
}

//void IGame::OnShowFileUpdaterMessage(FileUpdater* sender, FileUpdaterMessageType message)
//{
//	SceneManager::Instance().ShowToast(StringTable::Instance().GetString(message.ToString()));
//}

void IGame::OnMessageDebugInfo(const StringRef& debugInfo)
{
	//show debug on rendering status
}



void IGame::OnInitializeCompleted()
{
	Log::Info("*****Application Initialize*****");
	PublishTarget resultTag = mSettings!=nullptr?mSettings->ResultTag():Environment::Instance().Target();
	HeapString versionStr = resultTag.Version.ToString();
	HeapString deviceStr = resultTag.Device.ToString();
	HeapString languageStr = resultTag.Language.ToString();
	Log::FormatInfo("Version:{}", versionStr.c_str());
	Log::FormatInfo("Device:{}", deviceStr.c_str());
	Log::FormatInfo("Language:{}", languageStr.c_str());
	auto winSize = ResolutionAdapter::Instance().WinSize();
	Log::FormatInfo("WinSize:{},{}", (uint)winSize.Width, (uint)winSize.Height);

}

void IGame::OnLoadCompleted()
{
	Log::Info("*****Application Load*****");
	PublishTarget resultTag = mSettings != nullptr ? mSettings->ResultTag() : Environment::Instance().Target();
	HeapString versionStr = resultTag.Version.ToString();
	HeapString deviceStr = resultTag.Device.ToString();
	HeapString languageStr = resultTag.Language.ToString();
	Log::FormatInfo("Version:{}", versionStr.c_str());
	Log::FormatInfo("Device:{}", deviceStr.c_str());
	Log::FormatInfo("Language:{}", languageStr.c_str());
	auto winSize = ResolutionAdapter::Instance().WinSize();
	Log::FormatInfo("WinSize:{},{}", (uint)winSize.Width, (uint)winSize.Height);
}



MEDUSA_END;

