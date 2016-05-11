// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Collection/Array.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

template<typename T>
class Thickness
{
public:
	union
	{
		T Buffer[4];
		struct
		{
			T Left;
			T Right;
			T Bottom;
			T Top;
		};
	};

	const static Thickness Zero;

	Thickness(){}
	Thickness(const T& val)
		:Left(val),Top(val),Right(val),Bottom(val)
	{

	}

	Thickness(const T& leftAndRight,const T& bottomAndTop)
		:Left(leftAndRight),Right(leftAndRight),Bottom(bottomAndTop), Top(bottomAndTop) {}

	Thickness(const T& left,const T& right,const T& bottom,const T& top)
		:Left(left),Right(right),Bottom(bottom), Top(top) {}

	void SetAll(const T& val)
	{
		Left=val;
		Top=val;
		Right=val;
		Bottom=val;
	}

	void ResetZero()
	{
		memset(Buffer,0,sizeof(T)*4);
	}

	template<typename T1>
	Thickness(const Thickness<T1>& val):Left(val.Left),Top(val.Top),Right(val.Right),Bottom(val.Bottom){}

	template<typename T1>
	Thickness(const Array<T1,4>& items):Left(items[0]),Right(items[1]),Bottom(items[2]),Top(items[3]){}

	template<typename T1>
	Thickness& operator=(const Thickness<T1>& val){Left=val.Left;Top=val.Top;Right=val.Right;Bottom=val.Bottom;return *this;}

	template<typename T1>
	Thickness& operator=(const Array<T1,4>& items){Left=items[0];Right=items[1];Bottom=items[2];Top=items[3];return *this;}


	template<typename T1>
	bool operator==(const Thickness<T1>& val)const{return Math::IsEqual(Left,val.Left)&&Math::IsEqual(Top,val.Top)&&Math::IsEqual(Right,val.Right)&&Math::IsEqual(Bottom,val.Bottom);}
	template<typename T1>
	bool operator!=(const Thickness<T1>& val)const{return !operator==(val);}
};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Thickness<T> Thickness<T>::Zero(0,0,0,0);

//[PRE_DECLARE_BEGIN]
typedef Thickness<float> ThicknessF;

//[PRE_DECLARE_END]


MEDUSA_END;
