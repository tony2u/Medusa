// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Scale3.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterScale3F(asIScriptEngine* engine)
{
	int r;
	r = engine->RegisterObjectType("Scale3F", sizeof(Scale3F), asOBJ_VALUE | asOBJ_POD); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Scale3F", "float X", asOFFSET(Scale3F, X)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Scale3F", "float Y", asOFFSET(Scale3F, Y)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Scale3F", "float Z", asOFFSET(Scale3F, Z)); MEDUSA_ASSERT_SILENT(r >= 0);

}

MEDUSA_SCRIPT_END;


#endif


