// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Geometry/Rect2.h"
#include "Geometry/Point2.h"

MEDUSA_BEGIN;

class GeometryAlgorithm
{
public:
	static bool IsInPolygon(const float* verticesX, const float* verticesY, uintp countp, float x, float y);
	static bool IsInPolygon2(const float* vertices, uintp count, float x, float y);
	static bool IsInPolygon3(const float* vertices, uintp count, float x, float y);

	static void PrecomputePolygonTest(const float* verticesX, const float* verticesY, float* outPrecomputedConstants, float* outPrecomputedMultiples, uintp count);
	static void PrecomputePolygonTest2(const float* vertices, float* outPrecomputedConstants, float* outPrecomputedMultiples, uintp count);
	static void PrecomputePolygonTest3(const float* vertices, float* outPrecomputedConstants, float* outPrecomputedMultiples, uintp count);

	static bool IsInPolygonWithPrecompute(const float* verticesX, const float* verticesY, const float* precomputedConstants, const float* precomputedMultiples, uintp count, float x, float y);
	static bool IsInPolygonWithPrecompute2(const float* vertices, const float* precomputedConstants, const float* precomputedMultiples, uintp count, float x, float y);
	static bool IsInPolygonWithPrecompute3(const float* vertices, const float* precomputedConstants, const float* precomputedMultiples, uintp count, float x, float y);


};

MEDUSA_END;
