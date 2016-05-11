// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

MEDUSA_SCRIPT_BINDING_BEGIN;

bool Register_SirenType(IEventArg& e);
bool Register_SirenAssembly(IEventArg& e);
bool Register_SirenMachine(IEventArg& e);
bool Register_Siren(IEventArg& e);



MEDUSA_SCRIPT_BINDING_END;

#endif
