// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "AppCompatibilityModule.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/IO/Directory.h"
#include "Core/System/System.h"
#include "Core/Siren/Siren.h"

MEDUSA_BEGIN;



AppCompatibilityModule::AppCompatibilityModule()
	:IModule("Compatibility")
{

}

AppCompatibilityModule::~AppCompatibilityModule()
{

}

bool AppCompatibilityModule::Initialize()
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
	return true;
}

bool AppCompatibilityModule::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	AppCompatibility prevCompatibility;
	HeapString writePath = System::Instance().GetWritablePath("/AppCompatibility.bin");
	if (File::Exists(writePath))
	{
		MemoryData data = File::ReadAllData(writePath);
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


			return true;
		}
		else
		{
			File::Delete(writePath);
		}

	}

	//save a copy
	MemoryData data = Siren::SerializeBinary(mCompatibility);
	File::WriteAllData(writePath, data);
	return true;
}

bool AppCompatibilityModule::OnUnload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}

bool AppCompatibilityModule::OnReload(IEventArg& e /*= IEventArg::Empty*/)
{
	return true;
}


MEDUSA_END;