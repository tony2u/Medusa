// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IShape.h"

MEDUSA_BEGIN;

class LinesShape :public IShape
{
	MEDUSA_RTTI(LinesShape, IShape);
public:
	using IShape::IShape;
	virtual ~LinesShape(void);
	virtual bool Initialize()override;

public:
	void AppendPoints(const List<Point3F>& val);
	void AppendPoint(const Point3F& val);
	void ClearPoints();

	void AddLine(const Point3F& from, const Point3F& to);
protected:
	Share<ShapeGeneralMesh> mMesh;

};

MEDUSA_END;
