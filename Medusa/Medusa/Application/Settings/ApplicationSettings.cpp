// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ApplicationSettings.h"
#include "Core/System/Environment.h"
#include "Geometry/Size2.h"
#include "Core/Log/Log.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/IO/FileSystem.h"
#include "IJsonSettings.h"
#include "Application/Application.h"
#include "Node/Editor/NodeEditorFactory.h"

MEDUSA_BEGIN;

ApplicationSettings::ApplicationSettings()
	:IModule("Settings")
{
	mTag.Version = PublishVersions::main;
	mTag.Language = PublishLanguages::enus;
	mTag.Device = PublishDevices::hd;

#ifdef MEDUSA_DEBUG
	mIsDebug = true;
#else
	mIsDebug = false;
#endif

	Retain();
}

PublishTarget ApplicationSettings::ResultTag() const
{
#ifdef MEDUSA_WINDOWS
	return Tag();
#else
	if (IsDebug())
	{
		return Tag();
	}
	else
	{
		return Environment::Instance().Target();
	}
#endif

}


Size2F ApplicationSettings::DesignWinSize() const
{
	PublishDevices device = ResultTag().Device;
	switch (device.ToInt())
	{
	case PublishDevices::sd.IntValue:
		return Size2F(480, 320);
	case PublishDevices::hd.IntValue:
		return Size2F(MEDUSA_SCREEN_WIDTH, MEDUSA_SCREEN_HEIGHT);		//retina will *2
	default:
		Log::AssertFailed("Error device");
		break;
	}
	return Size2F::Zero;
}


Size2F ApplicationSettings::ResultWinSize() const
{
#ifdef MEDUSA_WINDOWS
	if (mDebugWinSize != Size2F::Zero)
	{
		return mDebugWinSize;
	}

	return DesignWinSize();
#else

#ifdef MEDUSA_DEBUG
	if (IsDebug() && !Environment::Instance().IsArm())
	{
		return DesignWinSize();	//simulator
	}
#endif

	uint width;
	uint height;
	Environment::Instance().GetScreenSize(width, height);
	return Size2U(width, height);
#endif

}

ApplicationDebugInfoFlags ApplicationSettings::ResultDebugInfo() const
{
#ifdef MEDUSA_DEBUG
	return mDebugInfo;
#endif
	return ApplicationDebugInfoFlags::None;
}

bool ApplicationSettings::HasScriptBinding() const
{
#ifdef MEDUSA_SCRIPT
	return mHasScriptBinding;
#else
	return false;
#endif
}

bool ApplicationSettings::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	if (!mSettingsFile.IsEmpty())
	{
		auto type = mSettingsFile.Type();
		if (type == FileType::json)
		{
			rapidjson::Document root;
			auto data = FileSystem::Instance().ReadAllData(mSettingsFile);
			const char* beginDoc = (const char*)data.Data();

			root.Parse<rapidjson::kParseStopWhenDoneFlag>(beginDoc);
			if (root.HasParseError())
			{
				rapidjson::ParseErrorCode errorCode = root.GetParseError();
				Log::AssertFailedFormat("Invalid json format:{}. ErrorCode:{}", mSettingsFile.Name.c_str(), errorCode);
				return false;
			}

			IJsonSettings settings(&root);

			mOrientation = (UIOrientation)settings.Optional("Orientation", (uint)UIOrientation::LandscapeLeft);
			mDebugInfo = (ApplicationDebugInfoFlags)settings.Optional("DebugInfo", (uint)ApplicationDebugInfoFlags::None);
			mTag.Version = (PublishVersions)settings.Optional("Version", PublishVersions::main.IntValue);
			mTag.Language = (PublishLanguages)settings.Optional("Language", PublishLanguages::enus.IntValue);
			mTag.Device = (PublishDevices)settings.Optional("Device", PublishDevices::hd.IntValue);
			mFeatures = (EngineFeatures)settings.Optional("Features", (uint)EngineFeatures::None);
			mIsDebug = settings.Optional("IsDebug", false);
			StringRef nodeEditors = settings.Optional("NodeEditors", StringRef::Empty);
			StringParser::Split(nodeEditors, ".", mNodeEditors);
			for (auto& str : mNodeEditors)
			{
				str.Push('.');
			}

			auto debugWinSizeNode = settings.JsonValue()->FindMember("DebugWinSize");
			if (debugWinSizeNode != settings.JsonValue()->MemberEnd())
			{
				mDebugWinSize.Width = debugWinSizeNode->value.Get("Width", 0.f);
				mDebugWinSize.Height = debugWinSizeNode->value.Get("Height", 0.f);
			}
		}
		else if (type == FileType::lua)
		{
#ifdef MEDUSA_LUA
			ScriptObject settings = ScriptEngine::State()->DoFileWithReturn(mSettingsFile);

			mOrientation = (UIOrientation)settings.Optional("Orientation", (uint)UIOrientation::LandscapeLeft);
			mDebugInfo = (ApplicationDebugInfoFlags)settings.Optional("DebugInfo", (uint)ApplicationDebugInfoFlags::None);
			mTag.Version = (PublishVersions)settings.Optional("Version", PublishVersions::main.IntValue);
			mTag.Language = (PublishLanguages)settings.Optional("Language", PublishLanguages::enus.IntValue);
			mTag.Device = (PublishDevices)settings.Optional("Device", PublishDevices::hd.IntValue);
			mFeatures = (EngineFeatures)settings.Optional("Features", (uint)EngineFeatures::None);
			mIsDebug = settings.Optional("IsDebug", false);
			StringRef nodeEditors = settings.Optional("NodeEditors", StringRef::Empty);
			StringParser::Split(nodeEditors, ".", mNodeEditors);
			for (auto& str : mNodeEditors)
			{
				str.Push('.');
			}

			auto debugWinSizeNode= settings.Get("DebugWinSize");
			if (debugWinSizeNode)
			{
				mDebugWinSize.Width = debugWinSizeNode.Optional("Width", 0.f);
				mDebugWinSize.Height = debugWinSizeNode.Optional("Height", 0.f);
			}
#else
			Log::AssertFailedFormat("Engine not enable lua feature for :{}", mSettingsFile.Name);
			return false;
#endif

		}
		else
		{
			Log::FormatError("Unsupport settings file:{}", mSettingsFile.Name);
			return false;
		}
	}

	Application::Instance().EnableModule("Core.ThreadCommandProcessor", MEDUSA_FLAG_HAS(mFeatures, EngineFeatures::SupportThreadEvent));
	Application::Instance().EnableModule("Core.Message", MEDUSA_FLAG_HAS(mFeatures, EngineFeatures::SupportMessage));
	Application::Instance().EnableModule("Core.FileUpdater", MEDUSA_FLAG_HAS(mFeatures, EngineFeatures::SupportFileUpdating));

	Apply();
	return true;
}



void ApplicationSettings::Apply() const
{
	if (!mNodeEditors.IsEmpty())
	{
		NodeEditorFactory::Instance().EnableAll(false);
		for (auto editor : mNodeEditors)
		{
			NodeEditorFactory::Instance().Enable(editor, true);
		}
	}

}

MEDUSA_END;