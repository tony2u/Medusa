// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaExtensionPreDeclares.h"

#ifdef MEDUSA_SCRIPT

#include "Core/Pattern/Singleton.h"

MEDUSA_BEGIN;

class MedusaExtensionScript:public Singleton<MedusaExtensionScript>
{
	friend class Singleton<MedusaExtensionScript>;
	MedusaExtensionScript();
	~MedusaExtensionScript();
public:
	void RegisterTypes();

	bool InitializeInternal();
	bool UninitializeInternal();

	bool InitializeExternal();
	bool UninitializeExternal();

	bool CreateInternalScriptObjects() { return true; }
	bool DeleteInternalScriptObjects() { return true; }

	bool CreateExternalScriptObjects() { return true; }
	bool DeleteExternalScriptObjects() { return true; }
public:

};

MEDUSA_END;
#endif