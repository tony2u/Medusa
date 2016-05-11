// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Engine_Binding.h"
#ifdef MEDUSA_LUA
#include "Core/Script/ScriptEngine.h"

#include "Binding/Lua/Geometry_Binding.h"
#include "Binding/Lua/Node_Binding.h"

#include "Binding/Lua/LayerFactory_Binding.h"

#include "Binding/Lua/SceneFactory_Binding.h"
#include "Binding/Lua/SceneManager_Binding.h"
#include "Binding/Lua/NodeFactory_Binding.h"


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



	return true;
}
MEDUSA_SCRIPT_BINDING_END;

#undef MEDUSA_LUA_REGISTER
#endif