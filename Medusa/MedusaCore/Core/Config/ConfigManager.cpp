// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ConfigManager.h"
#include "Core/IO/IFileLoadSavable.h"

MEDUSA_BEGIN;

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager(void)
{

}

void ConfigManager::Load(IFileLoadSavable* item)
{
	mItems.Add(item);
}
void ConfigManager::Clear()
{
	SAFE_DELETE_COLLECTION(mItems);
}


bool ConfigManager::Uninitialize()
{
	//in reverse order
	int count = (int)mItems.Count();
	RETURN_TRUE_IF_ZERO(count);
	FOR_EACH_INT_END_BEGIN(i, count - 1, 0)
	{
		IFileLoadSavable* item = mItems[i];
		item->Unload();
	}
	return true;
}


MEDUSA_END;