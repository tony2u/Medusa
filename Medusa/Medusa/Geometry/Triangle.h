// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Geometry/Point2.h"
#include "Geometry/Point3.h"


MEDUSA_BEGIN;

template<typename T,template<typename T1> class TPoint>
class Triangle_t
{
public:
	union
	{
		T Buffer[sizeof(TPoint<T>)/sizeof(T)*3];
		struct
		{
			TPoint<T> P1;
			TPoint<T> P2;
			TPoint<T> P3;
		};
	};

	const static Triangle_t Zero;

public:
	Triangle_t(void){}
	Triangle_t(TPoint<T> p1,TPoint<T> p2,TPoint<T> p3):P1(p1),P2(p2),P3(p3){}

	template<typename T1,template<typename> class TPoint1>
	Triangle_t(const Triangle_t<T1,TPoint>& triangle):P1(triangle.P1),P2(triangle.P2),P3(triangle.P3){}

	template<typename T1,template<typename> class TPoint1>
	Triangle_t& operator=(const Triangle_t<T1,TPoint>& triangle){P1=triangle.P1;P2=triangle.P2;P3=triangle.P3;return *this;}
	template<typename T1>
	Triangle_t& operator=(T1 val){P1=val;P2=val;P3=val;return *this;}

	template<typename T1,template<typename> class TPoint1>
	bool operator==(const Triangle_t<T1,TPoint>& triangle)const{return Math::IsEqual(P1,triangle.P1)&&Math::IsEqual(P2,triangle.P2)&&Math::IsEqual(P3,triangle.P3);}
	template<typename T1,template<typename> class TPoint1>
	bool operator!=(const Triangle_t<T1,TPoint>& triangle)const{return !operator==(triangle);}
	template<typename T1,template<typename> class TPoint1>
	bool operator>(const Triangle_t<T1,TPoint>& triangle)const{return P1>triangle.P1&&P2>triangle.P2&&P3>triangle.P3;}
	template<typename T1,template<typename> class TPoint1>
	bool operator<(const Triangle_t<T1,TPoint>& triangle)const{return P1<triangle.P1&&P2<triangle.P2&&P3<triangle.P3;}
	template<typename T1,template<typename> class TPoint1>
	bool operator>=(const Triangle_t<T1,TPoint>& triangle)const{return P1>=triangle.P1&&P2>=triangle.P2&&P3>=triangle.P3;}
	template<typename T1,template<typename> class TPoint1>
	bool operator<=(const Triangle_t<T1,TPoint>& triangle)const{return P1<=triangle.P1&&P2<=triangle.P2&&P3<=triangle.P3;}

	template<typename T1,template<typename> class TPoint1>
	Triangle_t operator+(const Triangle_t<T1,TPoint>& triangle)const{return Triangle_t(P1+triangle.P1,P2+triangle.P2,P3+triangle.P3);}
	template<typename T1,template<typename> class TPoint1>
	Triangle_t operator-(const Triangle_t<T1,TPoint>& triangle)const{return Triangle_t(P1-triangle.P1,P2-triangle.P2,P3-triangle.P3);}
	template<typename T1,template<typename> class TPoint1>
	Triangle_t& operator+=(const Triangle_t<T1,TPoint>& triangle){P1+=triangle.P1;P2+=triangle.P2;P3+=triangle.P3;return *this;}
	template<typename T1,template<typename> class TPoint1>
	Triangle_t& operator-=(const Triangle_t<T1,TPoint>& triangle){P1-=triangle.P1;P2-=triangle.P2;P3-=triangle.P3;return *this;}

	template<typename T1>
	Triangle_t operator*(T1 delta)const{return Triangle_t(P1*delta,P2*delta,P3*delta);}
	template<typename T1>
	Triangle_t operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Triangle_t(P1/delta,P2/delta,P3/delta);}

	template<typename T1>
	Triangle_t& operator*=(T1 delta){P1*=delta;P2*=delta;P3*=delta;return *this;}
	template<typename T1>
	Triangle_t& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");P1/=delta;P2/=delta;P3/=delta;return *this;}

	Triangle_t& operator++(){++P1;++P2;++P3;return *this;}
	Triangle_t& operator--(){--P1;--P2;--P3;return *this;}

	Triangle_t operator++(int){Triangle_t orign=*this;++P1;++P2;++P3;return orign;}
	Triangle_t operator--(int){Triangle_t orign=*this;--P1;--P2;--P3;return orign;}

	template<typename T1>
    friend  Triangle_t operator*(T1 delta,const Triangle_t<T,TPoint>& triangle){return Triangle_t(delta*triangle.P1,delta*triangle.P2,delta*triangle.P3);}

	float Area()const
	{
		TPoint<T> v1=(P2-P1);
		TPoint<T> v2=(P3-P1);

		return v1.CrossMultiply(v2)*0.5f;
	}
};

template<typename T,template<typename> class TPoint>
MEDUSA_WEAK_MULTIPLE_DEFINE const Triangle_t<T,TPoint> Triangle_t<T,TPoint>::Zero(TPoint<T>::Zero,TPoint<T>::Zero,TPoint<T>::Zero);

//[PRE_DECLARE_BEGIN]
typedef Triangle_t<int,Point2> Triangle2I;
typedef Triangle_t<float,Point2> Triangle2F;

typedef Triangle_t<int,Point3> Triangle3I;
typedef Triangle_t<float,Point3> Triangle3F;

typedef Triangle3I Triangle;
typedef Triangle3F TriangleF;
//[PRE_DECLARE_END]

MEDUSA_END;
