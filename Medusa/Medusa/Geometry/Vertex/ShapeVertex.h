// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Geometry/Color4.h"
#include "Geometry/Point3.h"

MEDUSA_BEGIN;

class ShapeVertex
{
public:
	Point3F Position;
	Color4F Color;

	ShapeVertex(){}

	ShapeVertex(const Point3F& position,const Color4F& color)
		:Position(position),Color(color){}
	
	void ResetZero()
	{
		Position=Point3F::Zero;
		Color=Color4F::Zero;
	}

	ShapeVertex& operator=(const ShapeVertex& vertex){Position=vertex.Position;Color=vertex.Color;return *this;}
	bool operator==(const ShapeVertex& vertex)const{return Position==vertex.Position&&Color==vertex.Color;}
	bool operator!=(const ShapeVertex& vertex)const{return !operator==(vertex);}
	intp HashCode()const{return Position.HashCode()^Color.HashCode();}
};


MEDUSA_END;
