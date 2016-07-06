// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"

#include "Geometry/Scale2.h"
#include "Core/Math/Math.h"
#include "Core/System/BitConverter.h"


MEDUSA_BEGIN;

template<typename T>
class Scale3
{
public:
	union
	{
		T Buffer[3];
		struct
		{
			T X;
			T Y;
			T Z;
		};
	};

	
	const static Scale3 Zero;
	const static Scale3 One;

public:
	Scale3(void){}
	Scale3(T x,T y,T z=1):X(x),Y(y),Z(z){}
	Scale3(const T* items):X(*items),Y(*(items+1)),Z(*(items+2)){}

	template<typename T1>
	Scale3(const Scale3<T1>& scale):X((T)scale.X),Y((T)scale.Y),Z((T)scale.Z){}

	template<typename T1>
	Scale3(const Scale2<T1>& scale):X((T)scale.X),Y((T)scale.Y),Z(1){}

	template<typename T1>
	Scale3& operator=(const Scale3<T1>& scale){X=(T)scale.X;Y=(T)scale.Y;Z=(T)scale.Z;return *this;}

	template<typename T1>
	Scale3& operator=(const Scale2<T1>& scale){X=(T)scale.X;Y=(T)scale.Y;Z=(T)1;return *this;}

	template<typename T1>
	Scale3& operator=(T1 val){X=(T)val;Y=(T)val;Z=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Scale3<T1>& scale)const{return Math::IsEqual(X,scale.X)&&Math::IsEqual(Y,scale.Y)&&Math::IsEqual(Z,scale.Z);}
	template<typename T1>
	bool operator!=(const Scale3<T1>& scale)const{return !operator==(scale);}
	template<typename T1>
	bool operator>(const Scale3<T1>& scale)const{return X>scale.X&&Y>scale.Y&&Z>scale.Z;}
	template<typename T1>
	bool operator<(const Scale3<T1>& scale)const{return X<scale.X&&Y<scale.Y&&Z<scale.Z;}
	template<typename T1>
	bool operator>=(const Scale3<T1>& scale)const{return X>=scale.X&&Y>=scale.Y&&Z>=scale.Z;}
	template<typename T1>
	bool operator<=(const Scale3<T1>& scale)const{return X<=scale.X&&Y<=scale.Y&&Z<=scale.Z;}

	template<typename T1>
	Scale3 operator+(const Scale3<T1>& scale)const{return Scale3(X+scale.X,Y+scale.Y,Z+scale.Z);}
	template<typename T1>
	Scale3 operator-(const Scale3<T1>& scale)const{return Scale3(X-scale.X,Y-scale.Y,Z-scale.Z);}
	template<typename T1>
	Scale3& operator+=(const Scale3<T1>& scale){X+=scale.X;Y+=scale.Y;Z+=scale.Z;return *this;}
	template<typename T1>
	Scale3& operator-=(const Scale3<T1>& scale){X-=scale.X;Y-=scale.Y;Z-=scale.Z;return *this;}

	template<typename T1>
	Scale3 operator*(const Scale3<T1>& scale)const { return Scale3(X * scale.X, Y * scale.Y, Z * scale.Z); }
	template<typename T1>
	Scale3 operator/(const Scale3<T1>& scale)const { return Scale3(X / scale.X, Y / scale.Y, Z / scale.Z); }
	template<typename T1>
	Scale3& operator*=(const Scale3<T1>& scale) { X *= scale.X; Y *= scale.Y; Z *= scale.Z; return *this; }
	template<typename T1>
	Scale3& operator/=(const Scale3<T1>& scale) { X /= scale.X; Y /= scale.Y; Z /= scale.Z; return *this; }

	template<typename T1>
	Scale3 operator*(T1 delta)const{return Scale3(X*delta,Y*delta,Z*delta);}
	template<typename T1>
	Scale3 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Scale3(X/delta,Y/delta,Z/delta);}
	Scale3 operator<<(uint32 delta)const{return Scale3(X<<delta,Y<<delta,Z<<delta);}
	Scale3 operator>>(uint32 delta)const{return Scale3(X>>delta,Y>>delta,Z>>delta);}

	template<typename T1>
	Scale3& operator*=(T1 delta){X*=delta;Y*=delta;Z*=delta;return *this;}
	template<typename T1>
	Scale3& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");X/=delta;Y/=delta;Z/=delta;return *this;}
	Scale3& operator<<=(uint32 delta){X<<=delta;Y<<=delta;Z<<=delta;return *this;}
	Scale3& operator>>=(uint32 delta){X>>=delta;Y>>=delta;Z>>=delta;return *this;}

	template<typename T1>
	Scale3 operator+(T1 delta)const{return Scale3(X+delta,Y+delta,Z+delta);}
	template<typename T1>
	Scale3 operator-(T1 delta)const{return Scale3(X-delta,Y-delta,Z-delta);}

	template<typename T1>
	Scale3& operator+=(T1 delta){X+=delta;Y+=delta;Z+=delta;return *this;}
	template<typename T1>
	Scale3& operator-=(T1 delta){X-=delta;Y-=delta;Z-=delta;return *this;}

	Scale3& operator++(){++X;++Y;++Z;return *this;}
	Scale3& operator--(){--X;--Y;--Z;return *this;}

	Scale3 operator++(int){Scale3 orign=*this;++X;++Y;++Z;return orign;}
	Scale3 operator--(int){Scale3 orign=*this;--X;--Y;--Z;return orign;}

	template<typename T1>
	friend Scale3 operator*(T1 delta,const Scale3<T>& scale){return Scale3(delta*scale.X,delta*scale.Y,delta*scale.Z);}

	template<typename T1>
	friend Scale3 operator/(T1 delta,const Scale3<T>& scale){return Scale3(delta/scale.X,delta/scale.Y,delta/scale.Z);}
	Scale3 CreateInverse()const{return Scale3((T)1/X,(T)1/Y,(T)1/Z);}

	Scale2<T> To2D()const{return Scale2<T>(X,Y);}
	intp HashCode()const{return HashUtility::Hash(Buffer);}

	static Scale3 LinearInterpolate(const Scale3& begin,const Scale3& end,float blend)
	{
		return Scale3(Math::LinearInterpolate(begin.X,end.X,blend),Math::LinearInterpolate(begin.Y,end.Y,blend),Math::LinearInterpolate(begin.Z,end.Z,blend));
	}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Scale3<T> Scale3<T>::Zero(0,0,0);
template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Scale3<T> Scale3<T>::One(1,1,1);

//[PRE_DECLARE_BEGIN]
typedef Scale3<int> Scale3I;
typedef Scale3<float> Scale3F;
//[PRE_DECLARE_END]

#define msssi(x,y,z) Scale3I(x,y,z)
#define msss(x,y,z) Scale3F(x,y,z)

MEDUSA_END;


#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
MEDUSA_BEGIN;

template <typename T>
struct LuaTypeMapping <Scale3<T>>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const Scale3<T>& val)
	{
		LuaStack s(L);
		s.NewTable(0, 3);
		s.Rawset("X", val.X);
		s.Rawset("Y", val.Y);
		s.Rawset("Z", val.Z);
	}

	static Scale3<T> Get(lua_State* L, int index)
	{
		Scale3<T> result;
		LuaStack s(L);
		result.X = s.Get<T>("X",index);
		result.Y = s.Get<T>("Y",index);
		result.Z = s.Get("Z", (T)1,index);
		return result;
	}

	static Scale3<T> Optional(lua_State* L, int index, const Scale3<T>& def)
	{
		return lua_isnoneornil(L, index) ? Scale3<T>::Zero : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, Scale3<T>& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};
MEDUSA_END;

#endif
