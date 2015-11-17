// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Geometry/Quad.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"

MEDUSA_BEGIN;

struct FontCharVertex
{
	Point2F TexCoord;
	Point3F Vertex;
};

//[PRE_DECLARE_BEGIN]
typedef Quad<FontCharVertex> FontCharQuad;
//[PRE_DECLARE_END]
MEDUSA_END;