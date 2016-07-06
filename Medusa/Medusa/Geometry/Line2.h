// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Geometry/Point2.h"
#include "Core/Math/Math.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

template<typename T>
class Line2
{
public:
	using PointType = Point2<T>;
public:
	union
	{
		T Buffer[4];
		struct
		{
			PointType Begin;
			PointType End;
		};
	};
public:
	Line2(void) {}
	template<typename T1>
	Line2(const Point2<T1>& begin, const Point2<T1>& end) :Begin(begin), End(end) {}
	Line2(const PointType& begin, const PointType& end) :Begin(begin), End(end) {}

	template<typename T1>
	Line2(T1 beginX, T1 beginY, T1 endX, T1 endY) : Begin((T)beginX, (T)beginY), End((T)endX, (T)endY) {}

	Line2(T beginX, T beginY, T endX, T endY) :Begin(beginX, beginY), End(endX, endY) {}

	template<typename T1>
	Line2(const Line2<T1>& line) : Begin(line.Begin), End(line.End) {}
	template<typename T1>
	Line2& operator=(const Line2<T1>& line) { Begin = line.Begin; End = line.End; return *this; }

	template<typename T1>
	bool operator==(const Line2<T1>& line)const { return Math::IsEqual(Begin, line.Begin) && Math::IsEqual(End, line.End); }
	template<typename T1>
	bool operator!=(const Line2<T1>& line)const { return !operator==(line); }

	template<typename T1>
	bool operator<(const Line2<T1>& line)const { return Begin < line.Begin&&End < line.End; }
	template<typename T1>
	bool operator<=(const Line2<T1>& line)const { return Begin <= line.Begin&&End <= line.End; }

	template<typename T1>
	bool operator>(const Line2<T1>& line)const { return Begin > line.Begin&&End > line.End; }
	template<typename T1>
	bool operator>=(const Line2<T1>& line)const { return Begin >= line.Begin&&End >= line.End; }

	intp HashCode()const { return Begin.HashCode() ^ End.HashCode(); }

	float Length()const
	{
		return Begin.GetDistance(End);
	}

	List<PointType> Sample(uint count)const
	{
		assert(count > 2);
		//count should >2
		List<PointType> result;
		result.Add(Begin);
		PointType delta = End - Begin;
		delta /= (count - 1);

		FOR_EACH_UINT32_BEGIN_END(i, 1, count - 2)
		{
			result.NewAdd() = Begin + delta*i;
		}

		result.Add(End);
		return result;
	}

	List<PointType> SampleWithoutBeginEnd(uint count)const
	{
		assert(count > 0);
		//count should >2
		List<PointType> result;
		PointType delta = End - Begin;
		delta /= (count + 1);

		FOR_EACH_UINT32_BEGIN_END(i, 1, count)
		{
			result.NewAdd() = Begin + delta*i;
		}

		return result;
	}
};


//[PRE_DECLARE_BEGIN]
typedef Line2<int> Line2I;
typedef Line2<float> Line2F;
//[PRE_DECLARE_END]
MEDUSA_END;
