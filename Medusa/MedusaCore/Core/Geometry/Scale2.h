// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
#include "Core/Hash/HashUtility.h"
#include "Core/Siren/SirenDefines.h"


MEDUSA_BEGIN;

template<typename T>
class Scale2
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
	
	const static Scale2 Zero;
	const static Scale2 One;

public:
	Scale2(void){}
	Scale2(T x,T y):X(x),Y(y){}
	Scale2(const T* items):X(*items),Y(*(items+1)){}

	template<typename T1>
	Scale2(const Scale2<T1>& scale):X((T)scale.X),Y((T)scale.Y){}
	
	template<typename T1>
	Scale2& operator=(const Scale2<T1>& scale){X=(T)scale.X;Y=(T)scale.Y;return *this;}
	template<typename T1>
	Scale2& operator=(T1 val){X=(T)val;Y=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Scale2<T1>& scale)const{return Math::IsEqual(X,scale.X)&&Math::IsEqual(Y,scale.Y);}
	template<typename T1>
	bool operator!=(const Scale2<T1>& scale)const{return !operator==(scale);}
	template<typename T1>
	bool operator>(const Scale2<T1>& scale)const{return X>scale.X&&Y>scale.Y;}
	template<typename T1>
	bool operator<(const Scale2<T1>& scale)const{return X<scale.X&&Y<scale.Y;}
	template<typename T1>
	bool operator>=(const Scale2<T1>& scale)const{return X>=scale.X&&Y>=scale.Y;}
	template<typename T1>
	bool operator<=(const Scale2<T1>& scale)const{return X<=scale.X&&Y<=scale.Y;}

	template<typename T1>
	Scale2 operator+(const Scale2<T1>& scale)const{return Scale2(X+scale.X,Y+scale.Y);}
	template<typename T1>
	Scale2 operator-(const Scale2<T1>& scale)const{return Scale2(X-scale.X,Y-scale.Y);}
	template<typename T1>
	Scale2& operator+=(const Scale2<T1>& scale){X+=scale.X;Y+=scale.Y;return *this;}
	template<typename T1>
	Scale2& operator-=(const Scale2<T1>& scale){X-=scale.X;Y-=scale.Y;return *this;}

	template<typename T1>
	Scale2 operator*(const Scale2<T1>& scale)const { return Scale2(X * scale.X, Y * scale.Y); }
	template<typename T1>
	Scale2 operator/(const Scale2<T1>& scale)const { return Scale2(X / scale.X, Y / scale.Y); }
	template<typename T1>
	Scale2& operator*=(const Scale2<T1>& scale) { X *= scale.X; Y *= scale.Y; return *this; }
	template<typename T1>
	Scale2& operator/=(const Scale2<T1>& scale) { X /= scale.X; Y /= scale.Y; return *this; }
	
	template<typename T1>
	Scale2 operator*(T1 delta)const{return Scale2(X*delta,Y*delta);}
	template<typename T1>
	Scale2 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Scale2(X/delta,Y/delta);}

	Scale2 operator<<(uint32 delta)const{return Scale2(X<<delta,Y<<delta);}
	Scale2 operator>>(uint32 delta)const{return Scale2(X>>delta,Y>>delta);}

	

	template<typename T1>
	Scale2& operator*=(T1 delta){X*=delta;Y*=delta;return *this;}
	template<typename T1>
	Scale2& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;return *this;}
	Scale2& operator<<=(uint32 delta){X<<=delta;Y<<=delta;return *this;}
	Scale2& operator>>=(uint32 delta){X>>=delta;Y>>=delta;return *this;}


	template<typename T1>
	Scale2 operator+(T1 delta)const{return Scale2(X+delta,Y+delta);}
	template<typename T1>
	Scale2 operator-(T1 delta)const{return Scale2(X-delta,Y-delta);}

	template<typename T1>
	Scale2& operator+=(T1 delta){X+=delta;Y+=delta;return *this;}
	template<typename T1>
	Scale2& operator-=(T1 delta){X-=delta;Y-=delta;return *this;}

	Scale2& operator++(){++X;++Y;return *this;}
	Scale2& operator--(){--X;--Y;return *this;}

	Scale2 operator++(int){Scale2 orign=*this;++X;++Y;return orign;}
	Scale2 operator--(int){Scale2 orign=*this;--X;--Y;return orign;}

	template<typename T1>
	friend  Scale2 operator*(T1 delta,const Scale2<T>& scale){return Scale2(delta*scale.X,delta*scale.Y);}

	template<typename T1>
	friend  Scale2 operator/(T1 delta,const Scale2<T>& scale){return Scale2(delta/scale.X,delta/scale.Y);}

	Scale2 CreateInverse()const{return Scale2((T)1/X,(T)1/Y);}

	intp HashCode()const{return HashUtility::Hash(Buffer);}
	static Scale2 LinearInterpolate(const Scale2& begin,const Scale2& end,float blend)
	{
		return Scale2(Math::LinearInterpolate(begin.X,end.X,blend),Math::LinearInterpolate(begin.Y,end.Y,blend));
	}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Scale2<T> Scale2<T>::Zero(0,0);

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Scale2<T> Scale2<T>::One(1,1);

//[PRE_DECLARE_BEGIN]
typedef Scale2<float> Scale2F;
//[PRE_DECLARE_END]

#define mss(x,y) Scale2F(x,y)

namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Scale2<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Scale2<T>& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<T, false>("X", 1, 0, obj.X);
		writer.template OnProperty<T, false>("Y", 1, 1, obj.Y);
		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Scale2<T>& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<T, false>("X", 1, 0, outObj.X);
		reader.template OnProperty<T, false>("Y", 1, 1, outObj.Y);
		reader.OnStructEnd();

		return true;
	}
}


MEDUSA_END;
