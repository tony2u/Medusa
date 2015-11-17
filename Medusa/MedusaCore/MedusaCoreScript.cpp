// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "MedusaCoreScript.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/String/StringRef.h"
#include "CoreLib/Common/angelscript/add_on/scriptmath/scriptmath.h"

#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Size2.h"
#include "Core/Geometry/Size3.h"

#include "CoreLib/Common/angelscript.h"


MEDUSA_BEGIN;

MedusaCoreScript::MedusaCoreScript()
{
	
}

MedusaCoreScript::~MedusaCoreScript()
{
	UninitializeInternal();
	UninitializeExternal();
}


bool MedusaCoreScript::InitializeInternal()
{
	//load scripts
	return true;
}

bool MedusaCoreScript::UninitializeInternal()
{
	return true;
}

bool MedusaCoreScript::InitializeExternal()
{
	//load scripts
	return true;
}

bool MedusaCoreScript::UninitializeExternal()
{
	return true;
}

void MedusaCoreScript::RegisterTypes()
{
	asIScriptEngine* engine=ScriptEngine::Instance().GetScriptEngine();

	RegisterStdString(engine);
	RegisterScriptArray(engine, true);
	RegisterScriptDictionary(engine);
	RegisterScriptAny(engine);
	RegisterScriptHandle(engine);
	RegisterScriptMath(engine);

	//string
	Script::RegisterStringRef(engine);
	Script::RegisterHeapString(engine);

	//geometry
	Script::RegisterColor4F(engine);
	Script::RegisterPoint2F(engine);
	Script::RegisterPoint3F(engine);
	Script::RegisterRotation3F(engine);
	Script::RegisterScale3F(engine);
	Script::RegisterSize2F(engine);
	Script::RegisterSize3F(engine);

	Script::RegisterRect2F(engine);

}


MEDUSA_END;
#endif