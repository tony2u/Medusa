// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "GeometryDefines.h"
#include "Point2.h"
#include "Scale2.h"

MEDUSA_BEGIN;

class Geometry
{
public:
	static Point2F DockToRect(const Rect2F& rect, DockPoint dock, const Point2F& relativePosition = Point2F::Zero);
	static Point2F ApplyMargin(const Rect2F& selfRect, const Rect2F& parentRect, MarginEdges marginEdges, const ThicknessF& margin);

	static void StretchToRect(const Size2F& selfSize, const Rect2F& rect, Stretch stretch, const Scale2F& strecthPercent, Scale2F& outScale, Size2F& outSize);

};

MEDUSA_END;
