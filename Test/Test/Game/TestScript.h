// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "TestPreDeclares.h"
#ifdef MEDUSA_SCRIPT
#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

class TestScript :public Singleton < TestScript >
{
	friend class Singleton < TestScript > ;
	TestScript();
	~TestScript();
public:
	void RegisterTypes();

	bool InitializeInternal();
	bool UninitializeInternal();



	bool CreateInternalScriptObjects();
	bool DeleteInternalScriptObjects();


	ScriptObject* ConfigObject() const { return mConfigObject; }

public:
	ScriptObject* mConfigObject;
};

MEDUSA_END;
#endif