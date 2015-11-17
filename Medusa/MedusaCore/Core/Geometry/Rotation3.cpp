// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Rotation3.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterRotation3F(asIScriptEngine* engine)
{
	int r;
	r = engine->RegisterObjectType("Rotation3F", sizeof(Rotation3F), asOBJ_VALUE | asOBJ_POD); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Rotation3F", "float X", asOFFSET(Rotation3F, X)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Rotation3F", "float Y", asOFFSET(Rotation3F, Y)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Rotation3F", "float Z", asOFFSET(Rotation3F, Z)); MEDUSA_ASSERT_SILENT(r >= 0);

}

MEDUSA_SCRIPT_END;


#endif


