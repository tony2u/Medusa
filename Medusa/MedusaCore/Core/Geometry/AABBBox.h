// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"


MEDUSA_BEGIN;

template<typename T,template<typename T1> class TPoint>
class AABBBox_t
{
public:
	union
	{
		T Buffer[sizeof(TPoint<T>)/sizeof(T)*2];
		struct
		{
			TPoint<T> Min;
			TPoint<T> Max;
		};
	};

	const static AABBBox_t Zero;

public:
	AABBBox_t(void){}
	AABBBox_t(TPoint<T> min,TPoint<T> max):Min(min),Max(max){}

	template<typename T1,template<typename> class TPoint1>
	AABBBox_t(const AABBBox_t<T1,TPoint>& aabb):Min(aabb.Min),Max(aabb.Max){}

	template<typename T1,template<typename> class TPoint1>
	AABBBox_t& operator=(const AABBBox_t<T1,TPoint>& aabb){Min=aabb.Min;Max=aabb.Max;return *this;}
	template<typename T1>
	AABBBox_t& operator=(T1 val){Min=val;Max=val;return *this;}

	template<typename T1,template<typename> class TPoint1>
	bool operator==(const AABBBox_t<T1,TPoint>& aabb)const{return Math::IsEqual(Min,aabb.Min)&&Math::IsEqual(Max,aabb.Max);}
	template<typename T1,template<typename> class TPoint1>
	bool operator!=(const AABBBox_t<T1,TPoint>& aabb)const{return !operator==(aabb);}
	template<typename T1,template<typename> class TPoint1>
	bool operator>(const AABBBox_t<T1,TPoint>& aabb)const{return Min>aabb.Min&&Max>aabb.Max;}
	template<typename T1,template<typename> class TPoint1>
	bool operator<(const AABBBox_t<T1,TPoint>& aabb)const{return Min<aabb.Min&&Max<aabb.Max;}
	template<typename T1,template<typename> class TPoint1>
	bool operator>=(const AABBBox_t<T1,TPoint>& aabb)const{return Min>=aabb.Min&&Max>=aabb.Max;}
	template<typename T1,template<typename> class TPoint1>
	bool operator<=(const AABBBox_t<T1,TPoint>& aabb)const{return Min<=aabb.Min&&Max<=aabb.Max;}

	template<typename T1,template<typename> class TPoint1>
	AABBBox_t operator+(const AABBBox_t<T1,TPoint>& aabb)const{return AABBBox_t(Min+aabb.Min,Max+aabb.Max);}
	template<typename T1,template<typename> class TPoint1>
	AABBBox_t operator-(const AABBBox_t<T1,TPoint>& aabb)const{return AABBBox_t(Min-aabb.Min,Max-aabb.Max);}
	template<typename T1,template<typename> class TPoint1>
	AABBBox_t& operator+=(const AABBBox_t<T1,TPoint>& aabb){Min+=aabb.Min;Max+=aabb.Max;return *this;}
	template<typename T1,template<typename> class TPoint1>
	AABBBox_t& operator-=(const AABBBox_t<T1,TPoint>& aabb){Min-=aabb.Min;Max-=aabb.Max;return *this;}

	template<typename T1>
	AABBBox_t operator*(T1 delta)const{return AABBBox_t(Min*delta,Max*delta);}
	template<typename T1>
	AABBBox_t operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return AABBBox_t(Min/delta,Max/delta);}

	template<typename T1>
	AABBBox_t& operator*=(T1 delta){Min*=delta;Max*=delta;return *this;}
	template<typename T1>
	AABBBox_t& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Min/=delta;Max/=delta;return *this;}

	AABBBox_t& operator++(){++Min;++Max;return *this;}
	AABBBox_t& operator--(){--Min;--Max;return *this;}

	AABBBox_t operator++(int){AABBBox_t orign=*this;++Min;++Max;return orign;}
	AABBBox_t operator--(int){AABBBox_t orign=*this;--Min;--Max;return orign;}

	template<typename T1>
	bool operator==(T1 val)const{return Math::IsEqual(Min,val)&&Math::IsEqual(Max,val);}
	template<typename T1>
	bool operator!=(T1 val)const{return !operator==(val);}
	template<typename T1>
	bool operator>(T1 val)const{return Min>val&&Max>val;}
	template<typename T1>
	bool operator<(T1 val)const{return Min<val&&Max<val;}
	template<typename T1>
	bool operator>=(T1 val)const{return Min>=val&&Max>=val;}
	template<typename T1>
	bool operator<=(T1 val)const{return Min<=val&&Max<=val;}


	template<typename T1>
	friend  bool operator==(T1 val,const AABBBox_t& aabb){return aabb==val;}
	template<typename T1>
	friend  bool operator!=(T1 val,const AABBBox_t& aabb){return aabb!=val;}
	template<typename T1>
	friend  bool operator>(T1 val,const AABBBox_t& aabb){return aabb<=val;}
	template<typename T1>
	friend  bool operator<(T1 val,const AABBBox_t& aabb){return aabb>=val;}
	template<typename T1>
	friend  bool operator>=(T1 val,const AABBBox_t& aabb){return aabb<val;}
	template<typename T1>
	friend  bool operator<=(T1 val,const AABBBox_t& aabb){return aabb>val;}

public:
	void AddPoint(const TPoint<T>& point)
	{
		Min.UpdateEachToMin(point);
		Max.UpdateEachToMax(point);
	}
};

template<typename T,template<typename> class TPoint>
MEDUSA_WEAK_MULTIPLE_DEFINE const AABBBox_t<T,TPoint> AABBBox_t<T,TPoint>::Zero(TPoint<T>::Max,TPoint<T>::Min);


typedef AABBBox_t<int,Point2> AABBBox2I;
typedef AABBBox_t<float,Point2> AABBBox2F;

typedef AABBBox_t<int,Point3> AABBBox3I;
typedef AABBBox_t<float,Point3> AABBBox3F;

typedef AABBBox3I AABBBoxI;
typedef AABBBox3F AABBBoxF;


MEDUSA_END;
