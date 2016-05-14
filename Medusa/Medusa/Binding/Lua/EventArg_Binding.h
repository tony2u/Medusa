// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_LUA

MEDUSA_SCRIPT_BINDING_BEGIN;


bool Register_IEventArg(IEventArg& e);
bool Register_TouchEventArg(IEventArg& e);
bool Register_KeyDownEventArg(IEventArg& e);
bool Register_KeyUpEventArg(IEventArg& e);
bool Register_CharInputEventArg(IEventArg& e);
bool Register_ScrollEventArg(IEventArg& e);
bool Register_KeyboardEventArg(IEventArg& e);

bool Register_TapGestureEventArg(IEventArg& e);
bool Register_DoubleTapGestureEventArg(IEventArg& e);
bool Register_DragBeganGestureEventArg(IEventArg& e);
bool Register_DragingGestureEventArg(IEventArg& e);
bool Register_DragEndGestureEventArg(IEventArg& e);
bool Register_DragFailedGestureEventArg(IEventArg& e);
bool Register_LongPressBeganGestureEventArg(IEventArg& e);
bool Register_LongPressFailedGestureEventArg(IEventArg& e);
bool Register_PanBeginGestureEventArg(IEventArg& e);
bool Register_PanGestureEventArg(IEventArg& e);
bool Register_PanEndGestureEventArg(IEventArg& e);
bool Register_PinchGestureEventArg(IEventArg& e);
bool Register_SwipeBeginGestureEventArg(IEventArg& e);
bool Register_SwipeMovedGestureEventArg(IEventArg& e);
bool Register_SwipeFailedGestureEventArg(IEventArg& e);
bool Register_SwipeSuccessGestureEventArg(IEventArg& e);






MEDUSA_SCRIPT_BINDING_END;

#endif
