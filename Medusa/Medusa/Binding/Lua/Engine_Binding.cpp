// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Engine_Binding.h"
#ifdef MEDUSA_LUA
#include "Core/Script/ScriptEngine.h"

#include "Binding/Lua/Geometry_Binding.h"
#include "Binding/Lua/Node_Binding.h"
#include "Binding/Lua/EventArg_Binding.h"
#include "Binding/Lua/LayerFactory_Binding.h"

#include "Binding/Lua/SceneFactory_Binding.h"
#include "Binding/Lua/SceneManager_Binding.h"
#include "Binding/Lua/NodeFactory_Binding.h"
#include "Binding/Lua/NodeDefines_Binding.h"
#include "Binding/Lua/EngineConstants_Binding.h"




#define MEDUSA_LUA_REGISTER(x) ScriptEngine::Instance().AddNextLoadModule(ScriptBinding::Register_##x, #x)

MEDUSA_SCRIPT_BINDING_BEGIN;
bool Register_Engine()
{

	MEDUSA_LUA_REGISTER(INode);
	MEDUSA_LUA_REGISTER(Sprite);

	MEDUSA_LUA_REGISTER(ILayer);
	MEDUSA_LUA_REGISTER(NormalLayer);
	MEDUSA_LUA_REGISTER(LayerFactory);


	MEDUSA_LUA_REGISTER(IScene);
	MEDUSA_LUA_REGISTER(UIScene);

	MEDUSA_LUA_REGISTER(SceneFactory);
	MEDUSA_LUA_REGISTER(SceneManager);

	MEDUSA_LUA_REGISTER(NodeFactory);

	//events
	MEDUSA_LUA_REGISTER(IEventArg);
	MEDUSA_LUA_REGISTER(TouchEventArg);
	MEDUSA_LUA_REGISTER(KeyDownEventArg);
	MEDUSA_LUA_REGISTER(KeyUpEventArg);
	MEDUSA_LUA_REGISTER(CharInputEventArg);
	MEDUSA_LUA_REGISTER(ScrollEventArg);
	MEDUSA_LUA_REGISTER(KeyboardEventArg);
	MEDUSA_LUA_REGISTER(TapGestureEventArg);
	MEDUSA_LUA_REGISTER(DoubleTapGestureEventArg);
	MEDUSA_LUA_REGISTER(DragBeganGestureEventArg);
	MEDUSA_LUA_REGISTER(DragingGestureEventArg);
	MEDUSA_LUA_REGISTER(DragEndGestureEventArg);
	MEDUSA_LUA_REGISTER(DragFailedGestureEventArg);
	MEDUSA_LUA_REGISTER(LongPressBeganGestureEventArg);
	MEDUSA_LUA_REGISTER(LongPressFailedGestureEventArg);
	MEDUSA_LUA_REGISTER(PanBeginGestureEventArg);
	MEDUSA_LUA_REGISTER(PanGestureEventArg);
	MEDUSA_LUA_REGISTER(PanEndGestureEventArg);
	MEDUSA_LUA_REGISTER(PinchGestureEventArg);
	MEDUSA_LUA_REGISTER(SwipeBeginGestureEventArg);
	MEDUSA_LUA_REGISTER(SwipeMovedGestureEventArg);
	MEDUSA_LUA_REGISTER(SwipeFailedGestureEventArg);
	MEDUSA_LUA_REGISTER(SwipeSuccessGestureEventArg);


	MEDUSA_LUA_REGISTER(NodeCreateFlags);
	MEDUSA_LUA_REGISTER(NodeDeleteFlags);
	MEDUSA_LUA_REGISTER(NodePushFlags);
	MEDUSA_LUA_REGISTER(NodePopFlags);

	MEDUSA_LUA_REGISTER(PublishDevices);
	MEDUSA_LUA_REGISTER(PublishLanguages);
	MEDUSA_LUA_REGISTER(PublishVersions);
	MEDUSA_LUA_REGISTER(ApplicationDebugInfoFlags);
	MEDUSA_LUA_REGISTER(NodeEditors);



	return true;
}
MEDUSA_SCRIPT_BINDING_END;

#undef MEDUSA_LUA_REGISTER
#endif