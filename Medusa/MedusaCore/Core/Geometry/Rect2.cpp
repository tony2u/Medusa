// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Rect2.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterRect2F(asIScriptEngine* engine)
{
	int r;
	r = engine->RegisterObjectType("Rect2F", sizeof(Rect2F), asOBJ_VALUE | asOBJ_POD); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Rect2F", "Point2F Origin", asOFFSET(Rect2F, Origin)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Rect2F", "Size2F Size", asOFFSET(Rect2F, Size)); MEDUSA_ASSERT_SILENT(r >= 0);

}

MEDUSA_SCRIPT_END;


#endif


