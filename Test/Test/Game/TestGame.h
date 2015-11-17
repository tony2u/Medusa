// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "TestPreDeclares.h"

class TestGame:public IGame
{
	MEDUSA_DECLARE_GAME();
public:
	static TestGame& Instance();
	const TestSettings& Config()const;
	const TestPlayer& Player()const;

public:
	TestGame();
	virtual ~TestGame();

	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Start()override;
public:
	virtual bool OnPrepareSettings()override;

	virtual bool OnLoadSettings()override;
	virtual bool OnLoadPlayer()override;

#pragma region Script
	virtual bool OnRegisterScriptTypes()override;

	virtual bool OnLoadInternalScripts()override;
	virtual bool OnUnloadInternalScripts()override;
	virtual bool OnCreateInternalScriptObjects()override;

#pragma endregion Script
protected:
	//virtual bool Start();
	//virtual bool Stop();
private:

};
