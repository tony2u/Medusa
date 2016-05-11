// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA

#include "LuaMachine.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"
#include "LuaState.h"

MEDUSA_BEGIN;

LuaMachine::LuaMachine(void)
{
}

LuaMachine::~LuaMachine(void)
{
	Uninitialize();
}

bool LuaMachine::Initialize()
{
	OpenNew();
	return true;
}

bool LuaMachine::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mStates);
	return true;
}

LuaState* LuaMachine::OpenNew(bool setCurrent/*=true*/)
{
	LuaState* result = new LuaState();
	if (setCurrent)
	{
		mCurrentState = result;
	}

	mStates.Add(result);
	return result;
}


void LuaMachine::Close(LuaState* state)
{
	if (state != NULL)
	{
		if (mCurrentState == state)
		{
			mCurrentState = NULL;
		}

		mStates.Remove(state);
		SAFE_DELETE(state);
	}
}


void LuaMachine::AddPackagePath(const StringRef& path)
{
	for (auto state : mStates)
	{
		state->AddPackagePath(path);
	}
}

void LuaMachine::SetPackagePath(const StringRef& path)
{
	for (auto state : mStates)
	{
		state->SetPackagePath(path);
	}
}


void LuaMachine::AddPackageLoader(lua_CFunction loader)
{
	for (auto state : mStates)
	{
		state->AddPackageLoader(loader);
	}
}


MEDUSA_END;
#endif