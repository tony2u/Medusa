// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
#include "Core/Hash/HashUtility.h"
#include "Core/Siren/SirenDefines.h"


MEDUSA_BEGIN;

template<typename T>
class Size2
{
public:
	union
	{
		T Buffer[2];
		struct
		{
			T Width;
			T Height;
		};
	};

	
	const static Size2 Zero;
	const static Size2 One;

public:
	Size2(void){}
	Size2(T width,T height):Width(width),Height(height){}

	template<typename T1>
	Size2(const Size2<T1>& size):Width((T)size.Width),Height((T)size.Height){}

	template<typename T1>
	explicit Size2(T1 val):Width((T)val),Height((T)val){}

	template<typename T1>
	Size2& operator=(const Size2<T1>& size){Width=(T)size.Width;Height=(T)size.Height;return *this;}
	template<typename T1>
	Size2& operator=(T1 val){Width=(T)val;Height=(T)val;return *this;}

	bool operator==(const Size2& size)const{return Math::IsEqual(Width,size.Width)&&Math::IsEqual(Height,size.Height);}

	template<typename T1>
	bool operator==(const Size2<T1>& size)const{return Math::IsEqual(Width,size.Width)&&Math::IsEqual(Height,size.Height);}
	template<typename T1>
	bool operator!=(const Size2<T1>& size)const{return !operator==(size);}
	template<typename T1>
	bool operator>(const Size2<T1>& size)const{return Width>size.Width&&Height>size.Height;}
	template<typename T1>
	bool operator<(const Size2<T1>& size)const{return Width<size.Width&&Height<size.Height;}
	template<typename T1>
	bool operator>=(const Size2<T1>& size)const{return Width>=size.Width&&Height>=size.Height;}
	template<typename T1>
	bool operator<=(const Size2<T1>& size)const{return Width<=size.Width&&Height<=size.Height;}

	template<typename T1>
	Size2 operator+(const Size2<T1>& size)const{return Size2(Width+size.Width,Height+size.Height);}
	template<typename T1>
	Size2 operator-(const Size2<T1>& size)const{return Size2(Width-size.Width,Height-size.Height);}
	template<typename T1>
	Size2& operator+=(const Size2<T1>& size){Width+=size.Width;Height+=size.Height;return *this;}
	template<typename T1>
	Size2& operator-=(const Size2<T1>& size){Width-=size.Width;Height-=size.Height;return *this;}

	template<typename T1>
	Size2 operator*(T1 delta)const{return Size2(Width*delta,Height*delta);}
	template<typename T1>
	Size2& operator*=(T1 delta){Width*=delta;Height*=delta;return *this;}

	template<typename T1>
	Size2 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Size2(Width/delta,Height/delta);}
	template<typename T1>
	Size2& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Width/=delta;Height/=delta;return *this;}

	template<typename T1>
	Size2 operator+(T1 delta)const{return Size2(Width+delta,Height+delta);}
	template<typename T1>
	Size2& operator+=(T1 delta){Width+=delta;Height+=delta;return *this;}

	template<typename T1>
	Size2 operator-(T1 delta)const{return Size2(Width-delta,Height-delta);}
	template<typename T1>
	Size2& operator-=(T1 delta){Width-=delta;Height-=delta;return *this;}

	Size2 operator<<(uint32 delta)const{return Size2(Width<<delta,Height<<delta);}
	Size2& operator<<=(uint32 delta){Width<<=delta;Height<<=delta;return *this;}

	Size2 operator>>(uint32 delta)const{return Size2(Width>>delta,Height>>delta);}
	Size2& operator>>=(uint32 delta){Width>>=delta;Height>>=delta;return *this;}

	Size2& operator++(){++Width;++Height;return *this;}
	Size2& operator--(){--Width;--Height;return *this;}

	Size2 operator++(int){Size2 orign=*this;++Width;++Height;return orign;}
	Size2 operator--(int){Size2 orign=*this;--Width;--Height;return orign;}
	Size2 operator-()const { return Size2(-Width, -Height); }

	template<typename T1>
	friend Size2 operator*(T1 delta,const Size2<T>& size){return Size2(delta*size.Width,delta*size.Height);}

	Size2 Flip()const{return Size2(Height,Width);}
	float Length()const{return Math::Sqrt((float)(Width*Width+Height*Height));}
	T Area()const{return Width*Height;}
	intp HashCode()const{return HashUtility::Hash(Buffer);}
	bool IsEmpty()const{return Math::IsZero(Width)||Math::IsZero(Height);}

	static Size2 LinearInterpolate(const Size2& begin,const Size2& end,float blend)
	{
		return Size2(Math::LinearInterpolate(begin.Width,end.Width,blend),Math::LinearInterpolate(begin.Height,end.Height,blend));
	}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Size2<T> Size2<T>::Zero(0,0);
template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Size2<T> Size2<T>::One(1,1);

//[PRE_DECLARE_BEGIN]
typedef Size2<int> Size2I;
typedef Size2<uint32> Size2U;

typedef Size2<float> Size2F;
//[PRE_DECLARE_END]

#define msizeu(x,y) Size2U(x,y)
#define msizei(x,y) Size2I(x,y)
#define msize(x,y) Size2F(x,y)


namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Size2<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Size2<T>& obj)
	{
		writer.OnStructBegin();
		writer.OnField<T, false>(StringRef("Width", 5), 0, obj.Width);
		writer.OnField<T, false>(StringRef("Height", 6), 1, obj.Height);
		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Size2<T>& outObj)
	{
		reader.OnStructBegin();
		reader.OnField<T, false>(StringRef("Width", 5), 0, outObj.Width);
		reader.OnField<T, false>(StringRef("Height", 6), 1, outObj.Height);
		reader.OnStructEnd();

		return true;
	}
}

MEDUSA_END;


#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
MEDUSA_BEGIN;

template <typename T>
struct LuaTypeMapping <Size2<T>>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const Size2<T>& val)
	{
		LuaStack s(L);
		s.NewTable(0, 2);
		s.Rawset("Width", val.Width);
		s.Rawset("Height", val.Height);
	}

	static Size2<T> Get(lua_State* L, int index)
	{
		Size2<T> result;
		LuaStack s(L);
		result.Width = s.Get<T>("Width",index);
		result.Height = s.Get<T>("Height",index);
		return result;
	}

	static Size2<T> Optional(lua_State* L, int index, const Size2<T>& def)
	{
		return lua_isnoneornil(L, index) ? Size2<T>::Zero : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, Size2<T>& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};
MEDUSA_END;

#endif

