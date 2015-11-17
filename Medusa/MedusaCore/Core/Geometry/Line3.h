// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Point3.h"
#include "Core/Math/Math.h"


MEDUSA_BEGIN;

template<typename T>
class Line3
{
public:
	union
	{
		T Buffer[6];
		struct
		{
			Point3<T> Begin;
			Point3<T> End;
		};
	};
public:
	Line3(void){}
	template<typename T1>
	Line3(const Point3<T1>& begin,const Point3<T1>& end):Begin(begin),End(end){}
	Line3(const Point3<T>& begin,const Point3<T>& end):Begin(begin),End(end){}

	template<typename T1>
	Line3(T1 beginX,T1 beginY,T1 endX,T1 endY):Begin((T)beginX,(T)beginY),End((T)endX,(T)endY){}
	
	Line3(T beginX,T beginY,T endX,T endY):Begin(beginX,beginY),End(endX,endY){}

	template<typename T1>
	Line3(const Line3<T1>& line):Begin(line.Begin),End(line.End){}
	template<typename T1>
	Line3& operator=(const Line3<T1>& line){Begin=line.Begin;End=line.End;return *this;}

	template<typename T1>
	bool operator==(const Line3<T1>& line)const{return Math::IsEqual(Begin,line.Begin)&&Math::IsEqual(End,line.End);}
	template<typename T1>
	bool operator!=(const Line3<T1>& line)const{return !operator==(line);}

	template<typename T1>
	bool operator<(const Line3<T1>& line)const{return Begin<line.Begin&&End<line.End;}
	template<typename T1>
	bool operator<=(const Line3<T1>& line)const{return Begin<=line.Begin&&End<=line.End;}

	template<typename T1>
	bool operator>(const Line3<T1>& line)const{return Begin>line.Begin&&End>line.End;}
	template<typename T1>
	bool operator>=(const Line3<T1>& line)const{return Begin>=line.Begin&&End>=line.End;}

	intp HashCode()const{return Begin.HashCode()^End.HashCode();}
};


//[PRE_DECLARE_BEGIN]
typedef Line3<int> Line3I;
typedef Line3<float> Line3F;
//[PRE_DECLARE_END]
MEDUSA_END;
