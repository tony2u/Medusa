// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"

#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Core/Math/Math.h"
#include "Core/System/BitConverter.h"
#include "Core/Siren/SirenDefines.h"
MEDUSA_BEGIN;

template<typename T>
class Padding4
{
public:
	union
	{
		T Buffer[4];
		struct
		{
			T Left;
			T Right;
			T Up;
			T Down;
		};
	};

	const static Padding4 Zero;
	const static Padding4 Min;
	const static Padding4 Max;

public: 

public:
	Padding4(void){}
	Padding4(T left,T right,T up,T down):Left(left),Right(right),Up(up),Down(down){}
	Padding4(const T* items):Left(*items),Right(*(items+1)),Up(*(items+2)),Down(*(items+3)){}

	template<typename T1>
	Padding4(const Padding4<T1>& point):Left((T)point.Left),Right((T)point.Right),Up((T)point.Up),Down((T)point.Down){}

	
	template<typename T1>
	Padding4& operator=(const Padding4<T1>& point){Left=(T)point.Left;Right=(T)point.Right;Up=(T)point.Up;Down=(T)point.Down;return *this;}

	template<typename T1>
	Padding4& operator=(T1 val){Left=(T)val;Right=(T)val;Up=(T)val;Down=(T)val;return *this;}

	template<typename T1>
	bool operator==(const Padding4<T1>& point)const{return Math::IsEqual(Left,point.Left)&&Math::IsEqual(Right,point.Right)&&Math::IsEqual(Up,point.Up)&&Math::IsEqual(Down,point.Down);}
	template<typename T1>
	bool operator!=(const Padding4<T1>& point)const{return !operator==(point);}
	template<typename T1>
	bool operator>(const Padding4<T1>& point)const{return Left>point.Left&&Right>point.Right&&Up>point.Up&&Down>point.Down;}
	template<typename T1>
	bool operator<(const Padding4<T1>& point)const{return Left<point.Left&&Right<point.Right&&Up<point.Up&&Down<point.Down;}
	template<typename T1>
	bool operator>=(const Padding4<T1>& point)const{return Left>=point.Left&&Right>=point.Right&&Up>=point.Up&&Down>=point.Down;}
	template<typename T1>
	bool operator<=(const Padding4<T1>& point)const{return Left<=point.Left&&Right<=point.Right&&Up<=point.Up&&Down<=point.Down;}

	template<typename T1>
	Padding4 operator+(const Padding4<T1>& point)const{return Padding4(Left+point.Left,Right+point.Right,Up+point.Up,Down+point.Down);}
	template<typename T1>
	Padding4 operator-(const Padding4<T1>& point)const{return Padding4(Left-point.Left,Right-point.Right,Up-point.Up,Down-point.Down);}
	template<typename T1>
	Padding4& operator+=(const Padding4<T1>& point){Left+=point.Left;Right+=point.Right;Up+=point.Up;Down+=point.Down;return *this;}
	template<typename T1>
	Padding4& operator-=(const Padding4<T1>& point){Left-=point.Left;Right-=point.Right;Up-=point.Up;Down-=point.Down;return *this;}

	Padding4 operator-()const{return Padding4(-Left,-Right,-Up,-Down);}


	template<typename T1>
	Padding4 operator*(T1 delta)const{return Padding4(Left*delta,Right*delta,Up*delta,Down*delta);}
	template<typename T1>
	Padding4 operator/(T1 delta)const{MEDUSA_ASSERT_NOT_ZERO(delta,"");return Padding4(Left/delta,Right/delta,Up/delta,Down/delta);}
	Padding4 operator<<(uint32 delta)const{return Padding4(Left<<delta,Right<<delta,Up<<delta,Down<<delta);}
	Padding4 operator>>(uint32 delta)const{return Padding4(Left>>delta,Right>>delta,Up>>delta,Down>>delta);}

	template<typename T1>
	Padding4& operator*=(T1 delta){Left*=delta;Right*=delta;Up*=delta;Down*=delta;return *this;}
	template<typename T1>
	Padding4& operator/=(T1 delta){MEDUSA_ASSERT_NOT_ZERO(delta,"");Left/=delta;Right/=delta;Up/=delta;Down/=delta;return *this;}
	Padding4& operator<<=(uint32 delta){Left<<=delta;Right<<=delta;Up<<=delta;Down<<=delta;return *this;}
	Padding4& operator>>=(uint32 delta){Left>>=delta;Right>>=delta;Up>>=delta;Down>>=delta;return *this;}

	template<typename T1>
	Padding4 operator+(T1 delta)const{return Padding4(Left+delta,Right+delta,Up+delta,Down+delta);}
	template<typename T1>
	Padding4 operator-(T1 delta)const{return Padding4(Left-delta,Right-delta,Up-delta,Down-delta);}

	template<typename T1>
	Padding4& operator+=(T1 delta){Left+=delta;Right+=delta;Up+=delta;Down+=delta;return *this;}
	template<typename T1>
	Padding4& operator-=(T1 delta){Left-=delta;Right-=delta;Up-=delta;Down-=delta;return *this;}

	Padding4& operator++(){++Left;++Right;++Up;++Down;return *this;}
	Padding4& operator--(){--Left;--Right;--Up;--Down;return *this;}

	Padding4 operator++(int){Padding4 orign=*this;++Left;++Right;++Up;++Down;return orign;}
	Padding4 operator--(int){Padding4 orign=*this;--Left;--Right;--Up;--Down;return orign;}

	template<typename T1>
	friend  Padding4 operator*(T1 delta,const Padding4<T>& point){return Padding4(delta*point.Left,delta*point.Right,delta*point.Up,delta*point.Down);}

	template<typename T1>
	bool operator==(T1 val)const{return Math::IsEqual(Left,val)&&Math::IsEqual(Right,val)&&Math::IsEqual(Up,val)&&Math::IsEqual(Down,val);}
	template<typename T1>
	bool operator!=(T1 val)const{return !operator==(val);}
	template<typename T1>
	bool operator>(T1 val)const{return Left>val&&Right>val&&Up>val&&Down>val;}
	template<typename T1>
	bool operator<(T1 val)const{return Left<val&&Right<val&&Up<val&&Down<val;}
	template<typename T1>
	bool operator>=(T1 val)const{return Left>=val&&Right>=val&&Up>=val&&Down>=val;}
	template<typename T1>
	bool operator<=(T1 val)const{return Left<=val&&Right<=val&&Up<=val&&Down<=val;}


	template<typename T1>
	friend  bool operator==(T1 val,const Padding4<T>& point){return point==val;}
	template<typename T1>
	friend  bool operator!=(T1 val,const Padding4<T>& point){return point!=val;}
	template<typename T1>
	friend  bool operator>(T1 val,const Padding4<T>& point){return point<=val;}
	template<typename T1>
	friend  bool operator<(T1 val,const Padding4<T>& point){return point>=val;}
	template<typename T1>
	friend  bool operator>=(T1 val,const Padding4<T>& point){return point<val;}
	template<typename T1>
	friend  bool operator<=(T1 val,const Padding4<T>& point){return point>val;}

	intp HashCode()const{return HashUtility::Hash(Buffer);}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Padding4<T> Padding4<T>::Zero(0,0,0,0);


//[PRE_DECLARE_BEGIN]
typedef Padding4<int> Padding4I;
typedef Padding4<float> Padding4F;

//[PRE_DECLARE_END]

namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Padding4<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Padding4<T>& obj)
	{
		writer.OnStructBegin();
		writer.template OnField<T, false>(StringRef("Left", 4), 0, obj.Left);
		writer.template OnField<T, false>(StringRef("Right", 5), 1, obj.Right);
		writer.template OnField<T, false>(StringRef("Up", 2), 2, obj.Up);
		writer.template OnField<T, false>(StringRef("Down", 4), 3, obj.Down);

		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Padding4<T>& outObj)
	{
		reader.OnStructBegin();
		reader.template OnField<T, false>(StringRef("Left", 4), 0, outObj.Left);
		reader.template OnField<T, false>(StringRef("Right", 5), 1, outObj.Right);
		reader.template OnField<T, false>(StringRef("Up", 2), 2, outObj.Up);
		reader.template OnField<T, false>(StringRef("Down", 4), 3, outObj.Down);

		reader.OnStructEnd();

		return true;
	}
}

MEDUSA_END;
