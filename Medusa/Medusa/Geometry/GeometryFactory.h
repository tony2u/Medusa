// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Geometry/Point2.h"
#include "Geometry/Scale2.h"
#include "Geometry/Rotation2.h"
#include "Geometry/Matrix2.h"

#include "Geometry/Point3.h"
#include "Geometry/Scale3.h"
#include "Geometry/Rotation3.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Matrix43.h"
#include "Geometry/Matrix3.h"

#include "Geometry/Quaternion.h"
#include "Geometry/EulerAngle.h"
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
	static Color4B BlendColor(Color4B dest, Color4B src);
	static Color4F BlendColor(Color4F dest, Color4F src);


};

MEDUSA_END;
