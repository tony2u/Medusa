// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"

MEDUSA_BEGIN;

class TextureNormalVertex
{
public:
	Point3F Position;
	Point3F Normal;
	Point2F Texcoord;
	Color4F Color;

	TextureNormalVertex(){}

	TextureNormalVertex(const Point3F& position,const Point3F& normal,const Point2F& texcoord,const Color4F& color)
		:Position(position),Normal(normal),Texcoord(texcoord),Color(color){}
	
	void ResetZero()
	{
		Position=Point3F::Zero;
		Normal=Point3F::Zero;
		Texcoord=Point2F::Zero;
		Color=Color4F::Zero;
	}

	TextureNormalVertex& operator=(const TextureNormalVertex& vertex){Position=vertex.Position;Normal=vertex.Normal;Texcoord=vertex.Texcoord;Color=vertex.Color;return *this;}
	bool operator==(const TextureNormalVertex& vertex)const{return Position==vertex.Position&&Normal==vertex.Normal&&Texcoord==vertex.Texcoord&&Color==vertex.Color;}
	bool operator!=(const TextureNormalVertex& vertex)const{return !operator==(vertex);}
	intp HashCode()const{return Position.HashCode()^Normal.HashCode()^Texcoord.HashCode()^Color.HashCode();}
};


MEDUSA_END;
