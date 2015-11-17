// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Point2.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;

void RegisterPoint2F(asIScriptEngine* engine)
{
	int r;
	r = engine->RegisterObjectType("Point2F", sizeof(Point2F), asOBJ_VALUE | asOBJ_POD); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Point2F", "float X", asOFFSET(Point2F, X)); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectProperty("Point2F", "float Y", asOFFSET(Point2F, Y)); MEDUSA_ASSERT_SILENT(r >= 0);

}

MEDUSA_SCRIPT_END;


#endif


