// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Scale2.h"
#include "Core/Geometry/Rotation2.h"
#include "Core/Geometry/Matrix2.h"

#include "Core/Geometry/Point3.h"
#include "Core/Geometry/Scale3.h"
#include "Core/Geometry/Rotation3.h"
#include "Core/Geometry/Matrix4.h"
#include "Core/Geometry/Matrix43.h"
#include "Core/Geometry/Matrix3.h"

#include "Core/Geometry/Quaternion.h"
#include "Core/Geometry/EulerAngle.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Array.h"



MEDUSA_BEGIN;

class GeometryFactory
{

public:
	static void CreateRect(const Rect2F& rect,Array<Point2F,4>& outPoints);


	static void CreateCircleBorder(Point3F center,float radius,size_t segmentsCount,List<Point3F>& outPoints);
	static void CreateCircle(Point3F center,float radius,size_t segmentsCount,List<Point3F>& outPoints);

	static void CreateArc(Point3F center,float radius,float beginRadian,float endRadian,size_t segmentsCount,List<Point3F>& outPoints);
	static void CreateFanBorder(Point3F center,float radius,float beginRadian,float endRadian,size_t segmentsCount,List<Point3F>& outPoints);
	static void CreateFan(Point3F center,float radius,float beginRadian,float endRadian,size_t segmentsCount,List<Point3F>& outPoints);
	static void CreateQuadBezier(Point3F origin,Point3F control,Point3F dest,size_t segmentsCount,List<Point3F>& outPoints);
	static void CreateCubicBezier(Point3F origin,Point3F control1,Point3F control2,Point3F dest,size_t segmentsCount,List<Point3F>& outPoints);

	static Color4B CreateColor(StringRef str);
};

MEDUSA_END;
