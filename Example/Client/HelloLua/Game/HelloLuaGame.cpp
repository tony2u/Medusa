// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "HelloLuaGame.h"

HelloLuaGame::HelloLuaGame()
{
	mName="HelloLua";

	System::Instance().Initialize("Resource", "Save", "Temp");

}

bool HelloLuaGame::Start()
{
	ScriptEngine::State()->DoFile("main.lua");
	mGameScriptObject= ScriptEngine::State()->Get("HelloLuaGame");
	
	Point2I pos = mpp(12, 22);
	bool isSuccess = mGameScriptObject.InvokeMember<bool>("Start",pos);
	return isSuccess;
	return true;
}

bool HelloLuaGame::Stop()
{
	return mGameScriptObject.InvokeMember<bool>("Stop");
}


bool HelloLuaGame::Update(float dt)
{
	return mGameScriptObject.InvokeMember<bool>("Update",dt);
}

bool HelloLuaGame::OnLoad(IEventArg& e /*= IEventArg::Empty*/)
{
	ScriptEngine::State()->SetPackagePath("Script");

	return true;
}


MEDUSA_IMPLEMENT_GAME(HelloLuaGame);