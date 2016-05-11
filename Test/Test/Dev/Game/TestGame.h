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
public:
	TestGame();
	virtual ~TestGame();

	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Start()override;
private:
};
