// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_LUA

MEDUSA_SCRIPT_BINDING_BEGIN;

bool Register_PublishDevices(IEventArg& e);
bool Register_PublishLanguages(IEventArg& e);
bool Register_PublishVersions(IEventArg& e);
bool Register_ApplicationDebugInfoFlags(IEventArg& e);
bool Register_NodeEditors(IEventArg& e);





MEDUSA_SCRIPT_BINDING_END;

#endif
