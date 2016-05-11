// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Geometry/GeometryFactory.h"
#include "Geometry/Rect2.h"
#include "Core/String/StringParser.h"
#include "Geometry/Color4.h"

MEDUSA_BEGIN;



void GeometryFactory::CreateCircleBorder(Point3F center, float radius, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();
	MEDUSA_ASSERT(segmentsCount > 2, "");
	MEDUSA_ASSERT(radius > 0.f, "");

	const float eachRadian = (float)Math::PI2 / segmentsCount;


	outPoints.ReserveSize(segmentsCount);
	Point3F firstPoint(center.X + radius, center.Y);
	outPoints.Append(firstPoint);

	FOR_EACH_SIZE(i, segmentsCount - 1)
	{
		float angle = eachRadian*(i + 1);
		Point3F temp;
		temp.X = center.X + radius*Math::Cos(angle);
		temp.Y = center.Y + radius*Math::Sin(angle);
		outPoints.Append(temp);
	}

	//DrawPolygonBorder
}

void GeometryFactory::CreateCircle(Point3F center, float radius, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();

	MEDUSA_ASSERT(segmentsCount > 2, "");
	MEDUSA_ASSERT(radius > 0.f, "");


	const float eachRadian = Math::PI2 / segmentsCount;

	outPoints.ReserveSize(segmentsCount + 2);



	outPoints.Append(center);

	Point3F firstPoint(center.X + radius, center.Y);
	outPoints.Append(firstPoint);

	FOR_EACH_SIZE(i, segmentsCount - 1)
	{
		float angle = eachRadian*(i + 1);
		Point3F temp;
		temp.X = center.X + radius*Math::Cos(angle);
		temp.Y = center.Y + radius*Math::Sin(angle);
		outPoints.Append(temp);
	}

	outPoints.Append(firstPoint);

	//DrawPolygon
}

void GeometryFactory::CreateArc(Point3F center, float radius, float beginRadian, float endRadian, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();
	MEDUSA_ASSERT(segmentsCount > 1, "");
	MEDUSA_ASSERT(radius > 0.f, "");
	MEDUSA_ASSERT(endRadian > beginRadian, "");
	MEDUSA_ASSERT(beginRadian <= Math::PI2, "");
	MEDUSA_ASSERT(endRadian <= Math::PI2, "");

	const float eachRadian = (float)(endRadian - beginRadian) / segmentsCount;
	outPoints.ReserveSize(segmentsCount + 1);



	FOR_EACH_SIZE(i, segmentsCount + 1)
	{
		float angle = beginRadian + eachRadian*(i);
		Point3F temp;
		temp.X = center.X + radius*Math::Cos(angle);
		temp.Y = center.Y + radius*Math::Sin(angle);
		outPoints.Append(temp);
	}

	//DrawLinesStrip
}

void GeometryFactory::CreateFanBorder(Point3F center, float radius, float beginRadian, float endRadian, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();
	MEDUSA_ASSERT(segmentsCount > 1, "");
	MEDUSA_ASSERT(radius > 0.f, "");
	MEDUSA_ASSERT(endRadian > beginRadian, "");
	MEDUSA_ASSERT(beginRadian <= Math::PI2, "");
	MEDUSA_ASSERT(endRadian <= Math::PI2, "");

	const float eachRadian = (float)(endRadian - beginRadian) / segmentsCount;
	outPoints.ReserveSize(segmentsCount + 2);



	outPoints.Append(center);
	FOR_EACH_SIZE(i, segmentsCount + 1)
	{
		float angle = beginRadian + eachRadian*(i);
		Point3F temp;
		temp.X = center.X + radius*Math::Cos(angle);
		temp.Y = center.Y + radius*Math::Sin(angle);
		outPoints.Append(temp);
	}
	//DrawLinesLoop
}

void GeometryFactory::CreateFan(Point3F center, float radius, float beginRadian, float endRadian, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();
	MEDUSA_ASSERT(segmentsCount > 1, "");
	MEDUSA_ASSERT(radius > 0.f, "");
	MEDUSA_ASSERT(endRadian > beginRadian, "");
	MEDUSA_ASSERT(beginRadian <= Math::PI2, "");
	MEDUSA_ASSERT(endRadian <= Math::PI2, "");

	const float eachRadian = (float)(endRadian - beginRadian) / segmentsCount;
	outPoints.ReserveSize(segmentsCount + 1);


	outPoints.Append(center);

	FOR_EACH_SIZE(i, segmentsCount + 1)
	{
		float angle = beginRadian + eachRadian*(i);

		Point3F temp;
		temp.X = center.X + radius*Math::Cos(angle);
		temp.Y = center.Y + radius*Math::Sin(angle);
		outPoints.Append(temp);
	}

	//DrawTrianglesFan
}

void GeometryFactory::CreateQuadBezier(Point3F origin, Point3F control, Point3F dest, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();
	MEDUSA_ASSERT_NOT_ZERO(segmentsCount, "");

	outPoints.ReserveSize(segmentsCount + 1);
	float t = 0.f;
	float eachT = 1.f / segmentsCount;

	FOR_EACH_SIZE(i, segmentsCount)
	{
		Point3F temp;

		temp.X = powf(1 - t, 2) * origin.X + 2.0f * (1 - t) * t * control.X + t * t * dest.X;
		temp.Y = powf(1 - t, 2) * origin.Y + 2.0f * (1 - t) * t * control.Y + t * t * dest.Y;
		outPoints.Append(temp);
		t += eachT;
	}

	outPoints.Append(dest);

	//DrawLinesStrip
}

void GeometryFactory::CreateCubicBezier(Point3F origin, Point3F control1, Point3F control2, Point3F dest, size_t segmentsCount, List<Point3F>& outPoints)
{
	outPoints.Clear();
	MEDUSA_ASSERT_NOT_ZERO(segmentsCount, "");

	outPoints.ReserveSize(segmentsCount + 1);

	float t = 0.f;
	float eachT = 1.f / segmentsCount;

	FOR_EACH_SIZE(i, segmentsCount)
	{
		Point3F temp;

		temp.X = powf(1 - t, 3) * origin.X + 3.0f * powf(1 - t, 2) * t * control1.X + 3.0f * (1 - t) * t * t * control2.X + t * t * t * dest.X;
		temp.Y = powf(1 - t, 3) * origin.Y + 3.0f * powf(1 - t, 2) * t * control1.Y + 3.0f * (1 - t) * t * t * control2.Y + t * t * t * dest.Y;
		outPoints.Append(temp);
		t += eachT;
	}

	outPoints.Append(dest);

	//DrawLinesStrip
}

Color4B GeometryFactory::CreateColor(StringRef str)
{
	uint val = StringParser::StringTo<uint32>(str, 16);
	return Color4B(val);
}

Color4F GeometryFactory::BlendColor(Color4F dest, Color4F src)
{
	return Color4F(dest.R + (src.R - dest.R)*src.A,
		dest.G + (src.G - dest.G)*src.A,
		dest.B + (src.B - dest.B)*src.A,
		dest.A * src.A
	);
}

Color4B GeometryFactory::BlendColor(Color4B dest, Color4B src)
{
	return BlendColor(dest.To4F(), src.To4F()).To4B();
}

void GeometryFactory::CreateRect(const Rect2F& rect, Array<Point2F, 4>& outPoints)
{
	outPoints.Clear();
	outPoints[0] = rect.LeftBottom();
	outPoints[1] = rect.RightBottom();
	outPoints[2] = rect.RightTop();
	outPoints[3] = rect.LeftTop();
}

MEDUSA_END;
