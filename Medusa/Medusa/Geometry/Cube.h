// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Geometry/Size3.h"
#include "Geometry/Rect2.h"
#include "Core/Math/Math.h"
#include "Core/Pattern/LazyValue.h"


MEDUSA_BEGIN;

template<typename T>
class Cube
{
public:
	Point3<T> Origin;
    Size3<T> Size;

	
	const static Cube Zero;


	T Left()const{return Origin.X;}
	T Right()const{return Origin.X+Size.Width;}

	T Bottom()const{return Origin.Y;}
	T Top()const{return Origin.Y+Size.Height;}

	T Near()const{return Origin.Z;}
	T Far()const{return Origin.Z+Size.Depth;}


	Point3<T> LeftBottomNear()const{return Origin;}
	Point3<T> LeftTopNear()const{return Point3<T>(Origin.X,Origin.Y+Size.Height,Origin.Z);}

	Point3<T> RightBottomNear()const{return Point3<T>(Origin.X+Size.Width,Origin.Y,Origin.Z);}
	Point3<T> RightTopNear()const{return Point3<T>(Origin.X+Size.Width,Origin.Y+Size.Height,Origin.Z);}

	Point3<T> LeftBottomFar()const{return Point3<T>(Origin.X,Origin.Y,Origin.Z+Size.Depth);;}
	Point3<T> LeftTopFar()const{return Point3<T>(Origin.X,Origin.Y+Size.Height,Origin.Z+Size.Depth);}

	Point3<T> RightBottomFar()const{return Point3<T>(Origin.X+Size.Width,Origin.Y,Origin.Z+Size.Depth);}
	Point3<T> RightTopFar()const{return Point3<T>(Origin.X+Size.Width,Origin.Y+Size.Height,Origin.Z+Size.Depth);}
public:
	Cube(void){}
	template<typename T1>
	Cube(const Point3<T1>& origin,const Size3<T1>& size):Origin(origin),Size(size){}
	template<typename T1>
	Cube(T1 x,T1 y,T1 z,T1 width,T1 height,T1 depth):Origin((T)x,(T)y,(T)z),Size((T)width,(T)height,(T)depth){}

	template<typename T1>
	Cube(const Cube<T1>& rect):Origin(rect.Origin),Size(rect.Size){}
	template<typename T1>
	Cube& operator=(const Cube<T1>& rect){Origin=rect.Origin;Size=rect.Size;return *this;}
	template<typename T1>
	Cube& operator=(T1 val){Origin=val;Size=val;return *this;}

	template<typename T1>
	bool operator==(const Cube<T1>& rect)const{return Math::IsEqual(Origin,rect.Origin)&&Math::IsEqual(Size,rect.Size);}
	template<typename T1>
	bool operator!=(const Cube<T1>& rect)const{return !operator==(rect);}
	template<typename T1>
	bool operator>(const Cube<T1>& rect)const{return Origin>rect.Origin&&Size>rect.Size;}
	template<typename T1>
	bool operator<(const Cube<T1>& rect)const{return Origin<rect.Origin&&Size<rect.Size;}
	template<typename T1>
	bool operator>=(const Cube<T1>& rect)const{return Origin>=rect.Origin&&Size>=rect.Size;}
	template<typename T1>
	bool operator<=(const Cube<T1>& rect)const{return Origin<=rect.Origin&&Size<=rect.Size;}

	template<typename T1>
	Cube operator+(const Cube<T1>& rect)const{return Cube(Origin+rect.Origin,Size+rect.Size);}
	template<typename T1>
	Cube operator-(const Cube<T1>& rect)const{return Cube(Origin-rect.Origin,Size-rect.Size);}
	template<typename T1>
	Cube& operator+=(const Cube<T1>& rect){Origin+=rect.Origin;Size+=rect.Size;return *this;}
	template<typename T1>
	Cube& operator-=(const Cube<T1>& rect){Origin-=rect.Origin;Size-=rect.Size;return *this;}

	template<typename T1>
	Cube operator*(T1 delta)const{return Cube(Origin*delta,Size*delta);}
	template<typename T1>
	Cube operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Cube(Origin/delta,Size/delta);}

	Cube operator<<(uint32 delta)const{return Cube(Origin<<delta,Size<<delta);}
	Cube operator>>(uint32 delta)const{return Cube(Origin>>delta,Size>>delta);}

	template<typename T1>
	Cube& operator*=(T1 delta){Origin*=delta;Size*=delta;return *this;}
	template<typename T1>
	Cube& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Origin/=delta;Size/=delta;return *this;}
	Cube& operator<<=(uint32 delta){Origin<<=delta;Size<<=delta;return *this;}
	Cube& operator>>=(uint32 delta){Origin>>=delta;Size>>=delta;return *this;}

	Cube& operator++(){++Origin;++Size;return *this;}
	Cube& operator--(){--Origin;--Size;return *this;}

	Cube operator++(int){Cube orign=*this;++Origin;++Size;return orign;}
	Cube operator--(int){Cube orign=*this;--Origin;--Size;return orign;}

	template<typename T1>
	friend  Cube operator*(T1 delta,const  Cube<T>& rect){return Cube(delta*rect.Origin,delta*rect.Size);}

	template<typename T1>
	bool operator==(T1 val)const{return Math::IsEqual(Origin,val)&&Math::IsEqual(Size,val);}
	template<typename T1>
	bool operator!=(T1 val)const{return !operator==(val);}
	template<typename T1>
	bool operator>(T1 val)const{return Origin>val&&Size>val;}
	template<typename T1>
	bool operator<(T1 val)const{return Origin<val&&Size<val;}
	template<typename T1>
	bool operator>=(T1 val)const{return Origin>=val&&Size>=val;}
	template<typename T1>
	bool operator<=(T1 val)const{return Origin<=val&&Size<=val;}


	template<typename T1>
	friend  bool operator==(T1 val,const  Cube<T>& rect){return rect==val;}
	template<typename T1>
	friend  bool operator!=(T1 val,const  Cube<T>& rect){return rect!=val;}
	template<typename T1>
	friend  bool operator>(T1 val,const  Cube<T>& rect){return rect<=val;}
	template<typename T1>
	friend  bool operator<(T1 val,const  Cube<T>& rect){return rect>=val;}
	template<typename T1>
	friend  bool operator>=(T1 val,const  Cube<T>& rect){return rect<val;}
	template<typename T1>
	friend  bool operator<=(T1 val,const  Cube<T>& rect){return rect>val;}

	bool IsZeroDepth()const{return Math::IsZero(Size.Depth);}
	Rect2<T> To2D()const{return Rect2<T>(Origin.To2D(),Size.To2D());}
	intp HashCode()const{return Origin.HashCode()^Size.HashCode();}

	bool Contains(const Point2<T>& point)const
	{
		return point.X>=Left()&&point.X<=Right()&&point.Y>=Bottom()&&point.Y<=Top();
	}

	bool Contains(const Point3<T>& point)const
	{
		return point.X>=Left()&&point.X<=Right()&&point.Y>=Bottom()&&point.Y<=Top()&&point.Z>=Near()&&point.Z<=Far();
	}
};


template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const  Cube<T>  Cube<T>::Zero(0,0,0,0,0,0);
//[PRE_DECLARE_BEGIN]
typedef Cube<uint32> CubeI;
typedef Cube<float> CubeF;
typedef CubeF BoundingBox;
typedef LazyValue<BoundingBox> LazyBoundingBox;
//[PRE_DECLARE_END]
MEDUSA_END;
