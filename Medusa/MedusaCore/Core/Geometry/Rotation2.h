// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
#include "Core/Hash/HashUtility.h"



MEDUSA_BEGIN;

template<typename T>
class Rotation2
{
public:
	union
	{
		T Buffer[2];
		struct
		{
			T X;
			T Y;
		};
	};
	
	const static Rotation2 Zero;
public:
	Rotation2(void){}
	Rotation2(T x,T y):X(x),Y(y){}
	Rotation2(const T* items):X(*items),Y(*(items+1)){}

	template<typename T1>
	Rotation2(const Rotation2<T1>& rotation):X((T)rotation.X),Y((T)rotation.Y){}
	
	template<typename T1>
	Rotation2& operator=(const Rotation2<T1>& rotation){X=(T)rotation.X;Y=(T)rotation.Y;return *this;}
	template<typename T1>
	Rotation2& operator=(T1 val){X=(T)val;Y=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Rotation2<T1>& rotation)const{return Math::IsEqual(X,rotation.X)&&Math::IsEqual(Y,rotation.Y);}
	template<typename T1>
	bool operator!=(const Rotation2<T1>& rotation)const{return !operator==(rotation);}
	template<typename T1>
	bool operator>(const Rotation2<T1>& rotation)const{return X>rotation.X&&Y>rotation.Y;}
	template<typename T1>
	bool operator<(const Rotation2<T1>& rotation)const{return X<rotation.X&&Y<rotation.Y;}
	template<typename T1>
	bool operator>=(const Rotation2<T1>& rotation)const{return X>=rotation.X&&Y>=rotation.Y;}
	template<typename T1>
	bool operator<=(const Rotation2<T1>& rotation)const{return X<=rotation.X&&Y<=rotation.Y;}

	template<typename T1>
	Rotation2 operator+(const Rotation2<T1>& rotation)const{return Rotation2(X+rotation.X,Y+rotation.Y);}
	template<typename T1>
	Rotation2 operator-(const Rotation2<T1>& rotation)const{return Rotation2(X-rotation.X,Y-rotation.Y);}
	template<typename T1>
	Rotation2& operator+=(const Rotation2<T1>& rotation){X+=rotation.X;Y+=rotation.Y;return *this;}
	template<typename T1>
	Rotation2& operator-=(const Rotation2<T1>& rotation){X-=rotation.X;Y-=rotation.Y;return *this;}
	
	template<typename T1>
	Rotation2 operator*(T1 delta)const{return Rotation2(X*delta,Y*delta);}
	template<typename T1>
	Rotation2 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Rotation2(X/delta,Y/delta);}

	Rotation2 operator<<(uint32 delta)const{return Rotation2(X<<delta,Y<<delta);}
	Rotation2 operator>>(uint32 delta)const{return Rotation2(X>>delta,Y>>delta);}

	

	template<typename T1>
	Rotation2& operator*=(T1 delta){X*=delta;Y*=delta;return *this;}
	template<typename T1>
	Rotation2& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;return *this;}
	Rotation2& operator<<=(uint32 delta){X<<=delta;Y<<=delta;return *this;}
	Rotation2& operator>>=(uint32 delta){X>>=delta;Y>>=delta;return *this;}


	template<typename T1>
	Rotation2 operator+(T1 delta)const{return Rotation2(X+delta,Y+delta);}
	template<typename T1>
	Rotation2 operator-(T1 delta)const{return Rotation2(X-delta,Y-delta);}

	template<typename T1>
	Rotation2& operator+=(T1 delta){X+=delta;Y+=delta;return *this;}
	template<typename T1>
	Rotation2& operator-=(T1 delta){X-=delta;Y-=delta;return *this;}

	Rotation2& operator++(){++X;++Y;return *this;}
	Rotation2& operator--(){--X;--Y;return *this;}

	Rotation2 operator++(int){Rotation2 orign=*this;++X;++Y;return orign;}
	Rotation2 operator--(int){Rotation2 orign=*this;--X;--Y;return orign;}

	template<typename T1>
	friend Rotation2 operator*(T1 delta,const Rotation2<T>& rotation){return Rotation2(delta*rotation.X,delta*rotation.Y);}
	Rotation2 operator-()const { return Point2<T>(-X, -Y); }

	Rotation2 ToDegree()const{return Rotation2(Math::ToDegree(X),Math::ToDegree(Y));}
	Rotation2 ToRadian()const{return Rotation2(Math::ToRadian(X),Math::ToRadian(Y));}
	Rotation2 CreateInverse()const{return Rotation2(-X,-Y);}
	intp HashCode()const{return HashUtility::Hash(Buffer);}
	void WrapToPI() { X = Math::WrapToPI(X); Y = Math::WrapToPI(Y);  }
	void WrapToPI2() { X = Math::WrapToPI2(X); Y = Math::WrapToPI2(Y);  }

	static Rotation2 LinearInterpolate(const Rotation2& begin,const Rotation2& end,float blend)
	{
		return Rotation2(Math::LinearInterpolate(begin.X,end.X,blend),Math::LinearInterpolate(begin.Y,end.Y,blend));
	}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Rotation2<T> Rotation2<T>::Zero(0,0);

//[PRE_DECLARE_BEGIN]
typedef Rotation2<float> Rotation2F;

//[PRE_DECLARE_END]

#define mrr(x,y) Rotation2F(x,y)

MEDUSA_END;
