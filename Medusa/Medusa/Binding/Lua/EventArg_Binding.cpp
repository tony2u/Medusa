// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "EventArg_Binding.h"
#include "Core/Command/EventArg/UserDataEventArg.h"

#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"

#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Node/Input/EventArg/KeyboardEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"

#include "Node/Input/Gesture/EventArg/TapGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DoubleTapGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragBeganGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragingGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragEndGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/DragFailedGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/LongPressBeganGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/LongPressFailedGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/PanBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/PanGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/PanEndGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/PinchGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeMovedGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeFailedGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeSuccessGestureEventArg.h"




MEDUSA_SCRIPT_BINDING_BEGIN;

bool Register_IEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<IEventArg>();
	cls.AddMemberVariable("Handled", &IEventArg::Handled, true);

	
	return true;
}

bool Register_TouchEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<TouchEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_KeyDownEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<KeyDownEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_KeyUpEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<KeyUpEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}


bool Register_CharInputEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<CharInputEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}


bool Register_ScrollEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<ScrollEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_KeyboardEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<KeyboardEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}



bool Register_TapGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<TapGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_DoubleTapGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<DoubleTapGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}


bool Register_DragBeganGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<DragBeganGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_DragingGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<DragingGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_DragEndGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<DragEndGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_DragFailedGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<DragFailedGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_LongPressBeganGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<LongPressBeganGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_LongPressFailedGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<LongPressFailedGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_PanBeginGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<PanBeginGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_PanGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<PanGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_PanEndGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<PanEndGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_PinchGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<PinchGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_SwipeBeginGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<SwipeBeginGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_SwipeMovedGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<SwipeMovedGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_SwipeFailedGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<SwipeFailedGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

bool Register_SwipeSuccessGestureEventArg(IEventArg& e)
{
	LuaState& state = *((UserDataEventArg<LuaState*>&)e).Data();
	auto module = state.BeginModule("ml");
	auto cls = module.BeginClass<SwipeSuccessGestureEventArg>();
	cls.InheritFrom<IEventArg>();


	return true;
}

MEDUSA_SCRIPT_BINDING_END;

#endif