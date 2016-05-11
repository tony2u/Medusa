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
	static void FindGridsInRange(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, int maxDistance, bool allowDiagnoal);
	static void FindGridsWithDistance(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, int distance, bool allowDiagnoal);
	static void FindGridsNear(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces,bool allowDiagnoal);


	template<typename T>
	static inline T ManhattanDistance(const Point2<T>& from, const Point2<T>& to)
	{
		//ManhattanDistance means the distance in south-north added with east-west, D(I,J)=|XI-XJ|+|YI-YJ|
		return Math::Abs(from.X - to.X) + Math::Abs(from.Y - to.Y);
	}

	template<typename T>
	static inline T EuclideanDistance(const Point2<T>& from, const Point2<T>& to)
	{
		//stright line distance
		return (T)from.GetDistance(to);
	}

	template<typename T>
	static inline T DiagonalDistanceEqually(const Point2<T>& from, const Point2<T>& to)
	{
		//corner ditance, suppose cost equal to straight line
		return Math::Max(Math::Abs(from.X - to.X), Math::Abs(from.Y - to.Y));
	}

	template<typename T>
	static inline T DiagonalDistanceEx(const Point2<T>& from, const Point2<T>& to)
	{
		//corner ditance, suppose cost sqrt(2) to straight line
		T absx = Math::Abs(from.X - to.X);
		T absy = Math::Abs(from.Y - to.Y);
		T diagonal = Math::Min(absx, absy);
		T straight = absx + absy;
		return Math::Sqrt2*diagonal + straight - 2 * diagonal;
	}

	static bool IsInPolygon(const float* verticesX, const float* verticesY, uintp countp, float x, float y);
	static bool IsInPolygon2(const float* vertices, uintp count, float x, float y);
	static bool IsInPolygon3(const float* vertices, uintp count, float x, float y);

	static void PreCalculatePolygonTest(const float* verticesX, const float* verticesY, float* outPreCalculatedConstants, float* outPreCalculatedMultiples, uintp count);
	static void PreCalculatePolygonTest2(const float* vertices, float* outPreCalculatedConstants, float* outPreCalculatedMultiples, uintp count);
	static void PreCalculatePolygonTest3(const float* vertices, float* outPreCalculatedConstants, float* outPreCalculatedMultiples, uintp count);

	static bool IsInPolygonWithPreCalculate(const float* verticesX, const float* verticesY, const float* preCalculatedConstants, const float* preCalculatedMultiples, uintp count, float x, float y);
	static bool IsInPolygonWithPreCalculate2(const float* vertices, const float* preCalculatedConstants, const float* preCalculatedMultiples, uintp count, float x, float y);
	static bool IsInPolygonWithPreCalculate3(const float* vertices, const float* preCalculatedConstants, const float* preCalculatedMultiples, uintp count, float x, float y);
};

MEDUSA_END;
