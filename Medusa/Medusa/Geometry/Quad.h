// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

template<typename T>
class Quad
{
public:
	T LeftBottom;
    T RightBottom;
    T RightTop;
    T LeftTop;

	Quad(){}
	Quad(const T& val)
		:LeftBottom(val),LeftTop(val),RightBottom(val),RightTop(val)
	{

	}
	void SetAll(const T& val)
	{
		LeftBottom=val;
		LeftTop=val;
		RightBottom=val;
		RightTop=val;
	}

	
	Quad(const T& leftBottom,const T& rightBottom,const T& rightTop, const T& leftTop)
		:LeftBottom(leftBottom),RightBottom(rightBottom),RightTop(rightTop), LeftTop(leftTop) {}

	template<typename T1>
	Quad(const Quad<T1>& quad):LeftBottom(quad.LeftBottom),LeftTop(quad.LeftTop),RightBottom(quad.RightBottom),RightTop(quad.RightTop){}

	template<typename T1>
	Quad(const Array<T1,4>& items):LeftBottom(items[0]),RightBottom(items[1]),RightTop(items[2]),LeftTop(items[3]){}

	template<typename T1>
	Quad& operator=(const Quad<T1>& quad){LeftBottom=quad.LeftBottom;LeftTop=quad.LeftTop;RightBottom=quad.RightBottom;RightTop=quad.RightTop;return *this;}

	template<typename T1>
	Quad& operator=(const Array<T1,4>& items){LeftBottom=items[0];RightBottom=items[1];RightTop=items[2];LeftTop=items[3];return *this;}


	template<typename T1>
	bool operator==(const Quad<T1>& quad)const{return Math::IsEqual(LeftBottom,quad.LeftBottom)&&Math::IsEqual(LeftTop,quad.LeftTop)&&Math::IsEqual(RightBottom,quad.RightBottom)&&Math::IsEqual(RightTop,quad.RightTop);}
	template<typename T1>
	bool operator!=(const Quad<T1>& quad)const{return !operator==(quad);}
};




MEDUSA_END;
