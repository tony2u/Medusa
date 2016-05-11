// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Medusa.h"
USING_MEDUSA;

class HelloLuaGame:public IGame
{
	MEDUSA_DECLARE_GAME();
public:
	HelloLuaGame();
	virtual ~HelloLuaGame()=default;

	virtual bool Start();
	virtual bool Stop();
	virtual bool Update(float dt)override;

protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
protected:
	ScriptObject mGameScriptObject;

};
