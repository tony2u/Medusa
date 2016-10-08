// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GeometryAlgorithm.h"


MEDUSA_BEGIN;


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

void GeometryAlgorithm::PrecomputePolygonTest(const float* verticesX, const float* verticesY, float* outPrecomputedConstants, float* outPrecomputedMultiples, uintp count)
{
	uintp  j = count - 1;

	for (uintp i = 0; i < count; j = i++)
	{
		if (Math::IsEqual(verticesY[j], verticesY[i]))
		{
			outPrecomputedConstants[i] = verticesX[i];
			outPrecomputedMultiples[i] = 0;
		}
		else
		{
			outPrecomputedConstants[i] = verticesX[i] - (verticesY[i] * verticesX[j]) / (verticesY[j] - verticesY[i]) + (verticesY[i] * verticesX[i]) / (verticesY[j] - verticesY[i]);
			outPrecomputedMultiples[i] = (verticesX[j] - verticesX[i]) / (verticesY[j] - verticesY[i]);
		}
	}
}

void GeometryAlgorithm::PrecomputePolygonTest2(const float* vertices, float* outPrecomputedConstants, float* outPrecomputedMultiples, uintp count)
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
			outPrecomputedConstants[i] = ix;
			outPrecomputedMultiples[i] = 0;
		}
		else
		{
			outPrecomputedConstants[i] = ix - (iy * jx) / (jy - iy) + (iy * ix) / (jy - iy);
			outPrecomputedMultiples[i] = (jx - ix) / (jy - iy);
		}
	}
}

void GeometryAlgorithm::PrecomputePolygonTest3(const float* vertices, float* outPrecomputedConstants, float* outPrecomputedMultiples, uintp count)
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
			outPrecomputedConstants[i] = ix;
			outPrecomputedMultiples[i] = 0;
		}
		else
		{
			outPrecomputedConstants[i] = ix - (iy * jx) / (jy - iy) + (iy * ix) / (jy - iy);
			outPrecomputedMultiples[i] = (jx - ix) / (jy - iy);
		}
	}
}
bool GeometryAlgorithm::IsInPolygonWithPrecompute(const float* verticesX, const float* verticesY, const float* precomputedConstants, const float* precomputedMultiples, uintp count, float x, float y)
{
	uintp  j = count - 1;
	bool  oddNodes = false;

	for (uintp i = 0; i < count; j = i++)
	{
		if (((verticesY[i] < y && verticesY[j] >= y) || (verticesY[j] < y && verticesY[i] >= y)) && (verticesX[i] <= x || verticesX[j] <= x))
		{
			oddNodes ^= (y*precomputedMultiples[i] + precomputedConstants[i] < x);
		}
	}

	return oddNodes;
}

bool GeometryAlgorithm::IsInPolygonWithPrecompute2(const float* vertices, const float* precomputedConstants, const float* precomputedMultiples, uintp count, float x, float y)
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
			oddNodes ^= (y*precomputedMultiples[i] + precomputedConstants[i] < x);
		}
	}

	return oddNodes;
}

bool GeometryAlgorithm::IsInPolygonWithPrecompute3(const float* vertices, const float* precomputedConstants, const float* precomputedMultiples, uintp count, float x, float y)
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
			oddNodes ^= (y*precomputedMultiples[i] + precomputedConstants[i] < x);
		}
	}

	return oddNodes;
}



MEDUSA_END;


