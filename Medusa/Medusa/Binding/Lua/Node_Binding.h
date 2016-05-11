// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_LUA

MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_INode(IEventArg& e);
bool Register_ILayer(IEventArg& e);
bool Register_IScene(IEventArg& e);
bool Register_NormalLayer(IEventArg& e);
bool Register_Sprite(IEventArg& e);
bool Register_UIScene(IEventArg& e);

MEDUSA_SCRIPT_BINDING_END;

#endif
