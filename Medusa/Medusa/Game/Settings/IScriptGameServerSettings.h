// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT
#include "MedusaPreDeclares.h"
#include "IGameServerSettings.h"
#include "IScriptSettings.h"

MEDUSA_BEGIN;

class IScriptGameServerSettings :public IGameServerSettings,public IScriptSettings
{
public:
	using IScriptSettings::IScriptSettings;
};


MEDUSA_END;

#endif