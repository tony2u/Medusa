// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GeometryAlgorithm.h"


MEDUSA_BEGIN;

void GeometryAlgorithm::FindGridsInRange(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, int maxDistance, bool allowDiagnoal)
{
	FOR_EACH_INT32_BEGIN_END(d, 1, (int)maxDistance)
	{
		FindGridsWithDistance(rect, cur, outSpaces, d, allowDiagnoal);
	}
}

void GeometryAlgorithm::FindGridsWithDistance(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, int distance, bool allowDiagnoal)
{
	Point2I pos;

	if (allowDiagnoal)
	{
		//top
		pos.Y = cur.Y + distance;
		FOR_EACH_INT32_BEGIN_END(dx, -distance, distance)
		{
			pos.X = cur.X + dx;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
		//bottom
		pos.Y = cur.Y - distance;
		FOR_EACH_INT32_BEGIN_END(dx, -distance, distance)
		{
			pos.X = cur.X + dx;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//left
		pos.X = cur.X - distance;
		FOR_EACH_INT32_BEGIN_END(dy, -distance + 1, distance - 1)
		{
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//right
		pos.X = cur.X + distance;
		FOR_EACH_INT32_BEGIN_END(dy, -distance + 1, distance - 1)
		{
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
	}
	else
	{
		//right top
		FOR_EACH_INT32_END_BEGIN(dx, distance, 0)
		{
			int dy = distance - dx;
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
		//right bottom
		FOR_EACH_INT32_END_BEGIN(dx, distance, 0)
		{
			int dy = -(distance - dx);
			CONTINUE_IF_ZERO(dy);	//ignore duplicate 0
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//left top
		FOR_EACH_INT32_BEGIN_END(dx, -distance, -1)
		{
			int dy = distance + dx;
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//left bottom
		FOR_EACH_INT32_BEGIN_END(dx, -distance, -1)
		{
			int dy = -(distance + dx);
			CONTINUE_IF_ZERO(dy);	//ignore duplicate 0
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
	}

}

void GeometryAlgorithm::FindGridsNear(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, bool allowDiagnoal)
{
	/*
	-1,1	0,1		1,1
	-1,0	(0,0)	1,0
	-1,-1	0,-1	1,-1
	*/

	Point2I pos = cur;

	//right center
	pos.X = cur.X + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//top center
	pos.X = cur.X;
	pos.Y = cur.Y + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//bottom center
	pos.Y = cur.Y - 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//left center
	pos.X = cur.X - 1;
	pos.Y = cur.Y;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}

	RETURN_IF_FALSE(allowDiagnoal);

	//right top
	pos = cur + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}

	//right bottom
	pos.Y = cur.Y - 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//left top
	pos.X = cur.X - 1;
	pos.Y = cur.Y + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//left bottom
	pos = cur - 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
}


bool GeometryAlgorithm::IsInPolygon(const float* verticesX, const float* verticesY, uintp count, float x, float y)
{
	//  The function will return YES if the point x,y is inside the polygon, or
	//  NO if it is not.  If the point is exactly on the edge of the polygon,
	//  then the function may return YES or NO.
	//
	//  Note that division by zero is avoided because the division is protected
	//  by the "if" clause which surrounds it.

	//http://alienryderflex.com/polygon/

	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		if (((verticesY[i] < y && verticesY[j] >= y) || (verticesY[j] < y && verticesY[i] >= y)) && (verticesX[i] <= x || verticesX[j] <= x))
		{
			oddNodes ^= (verticesX[i] + (y - verticesY[i]) / (verticesY[j] - verticesY[i])*(verticesX[j] - verticesX[i]) < x);
		}
	}

	return oddNodes;
}

bool GeometryAlgorithm::IsInPolygon2(const float* vertices, uintp count, float x, float y)
{
	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		float ix = vertices[i << 1];
		float jx = vertices[j << 1];

		float iy = vertices[(i << 1) + 1];
		float jy = vertices[(j << 1) + 1];

		if (((iy < y && jy >= y) || (jy < y && iy >= y)) && (ix <= x || jx <= x))
		{
			oddNodes ^= (ix + (y - iy) / (jy - iy)*(jx - ix) < x);
		}
	}

	return oddNodes;
}

bool GeometryAlgorithm::IsInPolygon3(const float* vertices, uintp count, float x, float y)
{
	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		float ix = vertices[i * 3];
		float jx = vertices[j * 3];

		float iy = vertices[i * 3 + 1];
		float jy = vertices[j * 3 + 1];

		if (((iy < y && jy >= y) || (jy < y && iy >= y)) && (ix <= x || jx <= x))
		{
			oddNodes ^= (ix + (y - iy) / (jy - iy)*(jx - ix) < x);
		}
	}

	return oddNodes;
}

void GeometryAlgorithm::PreCalculatePolygonTest(const float* verticesX, const float* verticesY, float* outPreCalculatedConstants, float* outPreCalculatedMultiples, uintp count)
{
	uintp  j = count - 1;

	for (uintp i = 0; i < count; j = i++)
	{
		if (Math::IsEqual(verticesY[j], verticesY[i]))
		{
			outPreCalculatedConstants[i] = verticesX[i];
			outPreCalculatedMultiples[i] = 0;
		}
		else
		{
			outPreCalculatedConstants[i] = verticesX[i] - (verticesY[i] * verticesX[j]) / (verticesY[j] - verticesY[i]) + (verticesY[i] * verticesX[i]) / (verticesY[j] - verticesY[i]);
			outPreCalculatedMultiples[i] = (verticesX[j] - verticesX[i]) / (verticesY[j] - verticesY[i]);
		}
	}
}

void GeometryAlgorithm::PreCalculatePolygonTest2(const float* vertices, float* outPreCalculatedConstants, float* outPreCalculatedMultiples, uintp count)
{
	uintp  j = count - 1;

	for (uintp i = 0; i < count; j = i++)
	{
		float ix = vertices[i << 1];
		float jx = vertices[j << 1];

		float iy = vertices[(i << 1) + 1];
		float jy = vertices[(j << 1) + 1];

		if (Math::IsEqual(jy, iy))
		{
			outPreCalculatedConstants[i] = ix;
			outPreCalculatedMultiples[i] = 0;
		}
		else
		{
			outPreCalculatedConstants[i] = ix - (iy * jx) / (jy - iy) + (iy * ix) / (jy - iy);
			outPreCalculatedMultiples[i] = (jx - ix) / (jy - iy);
		}
	}
}

void GeometryAlgorithm::PreCalculatePolygonTest3(const float* vertices, float* outPreCalculatedConstants, float* outPreCalculatedMultiples, uintp count)
{
	uintp  j = count - 1;

	for (uintp i = 0; i < count; j = i++)
	{
		float ix = vertices[i * 3];
		float jx = vertices[j * 3];

		float iy = vertices[i * 3 + 1];
		float jy = vertices[j * 3 + 1];

		if (Math::IsEqual(jy, iy))
		{
			outPreCalculatedConstants[i] = ix;
			outPreCalculatedMultiples[i] = 0;
		}
		else
		{
			outPreCalculatedConstants[i] = ix - (iy * jx) / (jy - iy) + (iy * ix) / (jy - iy);
			outPreCalculatedMultiples[i] = (jx - ix) / (jy - iy);
		}
	}
}
bool GeometryAlgorithm::IsInPolygonWithPreCalculate(const float* verticesX, const float* verticesY, const float* preCalculatedConstants, const float* preCalculatedMultiples, uintp count, float x, float y)
{
	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		if (((verticesY[i] < y && verticesY[j] >= y) || (verticesY[j] < y && verticesY[i] >= y)) && (verticesX[i] <= x || verticesX[j] <= x))
		{
			oddNodes ^= (y*preCalculatedMultiples[i] + preCalculatedConstants[i] < x);
		}
	}

	return oddNodes;
}

bool GeometryAlgorithm::IsInPolygonWithPreCalculate2(const float* vertices, const float* preCalculatedConstants, const float* preCalculatedMultiples, uintp count, float x, float y)
{
	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		float ix = vertices[i << 1];
		float jx = vertices[j << 1];

		float iy = vertices[(i << 1) + 1];
		float jy = vertices[(j << 1) + 1];

		if (((iy < y && jy >= y) || (jy < y && iy >= y)) && (ix <= x || jx <= x))
		{
			oddNodes ^= (y*preCalculatedMultiples[i] + preCalculatedConstants[i] < x);
		}
	}

	return oddNodes;
}

bool GeometryAlgorithm::IsInPolygonWithPreCalculate3(const float* vertices, const float* preCalculatedConstants, const float* preCalculatedMultiples, uintp count, float x, float y)
{
	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		float ix = vertices[i * 3];
		float jx = vertices[j * 3];

		float iy = vertices[i * 3 + 1];
		float jy = vertices[j * 3 + 1];

		if (((iy < y && jy >= y) || (jy < y && iy >= y)) && (ix <= x || jx <= x))
		{
			oddNodes ^= (y*preCalculatedMultiples[i] + preCalculatedConstants[i] < x);
		}
	}

	return oddNodes;
}

MEDUSA_END;


