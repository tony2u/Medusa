// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "TestPreDeclares.h"
#include "Game/Settings/IScriptGameClientSettings.h"

class TestSettings :public IScriptGameClientSettings
{
public:
	using IScriptGameClientSettings::IScriptGameClientSettings;
	virtual ~TestSettings();
public:
	static const TestSettings& Instance();
public:
	virtual bool Initialize() override { return true; }
	virtual bool Uninitialize() override { return true; }
public:
	virtual uint64 Coders()const override { return 0; }
	virtual MemoryByteData CoderKey()const override;
};


