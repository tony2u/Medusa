// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Size3.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterSize3F(asIScriptEngine* engine)
{
	int r;
	r = engine->RegisterObjectType("Size3F", sizeof(Size3F), asOBJ_VALUE | asOBJ_POD); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Size3F", "float Width", asOFFSET(Size3F, Width)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Size3F", "float Height", asOFFSET(Size3F, Height)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Size3F", "float Depth", asOFFSET(Size3F, Depth)); MEDUSA_ASSERT_SILENT(r >= 0);

}

MEDUSA_SCRIPT_END;


#endif


