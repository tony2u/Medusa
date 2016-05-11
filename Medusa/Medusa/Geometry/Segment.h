// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
#include "Core/Utility/Utility.h"



MEDUSA_BEGIN;

template<typename T>
class Segment
{
public:
	union
	{
		T Buffer[2];
		struct
		{
			T Position;
			T Length;
		};
	};

	const static Segment Zero;
public:
	Segment(void) :Position(0), Length(0) {}
	Segment(T position, T length) :Position(position), Length(length) { MEDUSA_ASSERT_LESS_EQUAL(position, length, "Invalid segment."); }

	template<typename T1>
	Segment(const Segment<T1>& segment) : Position((T)segment.Position), Length((T)segment.Length) {}

	template<typename T1>
	explicit Segment(T1 val) :Position((T)val), Length((T)val) {}

	template<typename T1>
	Segment& operator=(const Segment<T1>& segment) { Position = (T)segment.Position; Length = (T)segment.Length; return *this; }
	template<typename T1>
	Segment& operator=(T1 val) { Position = (T)val; Length = (T)val; return *this; }

	template<typename T1>
	bool operator==(const Segment<T1>& segment)const { return Math::IsEqual(Position, segment.Position) && Math::IsEqual(Length, segment.Length); }
	template<typename T1>
	bool operator!=(const Segment<T1>& segment)const { return !operator==(segment); }
	template<typename T1>
	bool operator>(const Segment<T1>& segment)const { return Position > segment.Position&&Length > segment.Length; }
	template<typename T1>
	bool operator<(const Segment<T1>& segment)const { return Position < segment.Position&&Length < segment.Length; }
	template<typename T1>
	bool operator>=(const Segment<T1>& segment)const { return Position >= segment.Position&&Length >= segment.Length; }
	template<typename T1>
	bool operator<=(const Segment<T1>& segment)const { return Position <= segment.Position&&Length <= segment.Length; }

	intp HashCode()const { return HashUtility::Hash(Buffer); }

	bool Contains(T val)const
	{
		return val >= Position&&val <= Position + Length;
	}
	void Reset()
	{
		Position = 0;
		Length = 0;
	}

	bool IsEmpty()const
	{
		return Length <= 0;
	}


};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Segment<T> Segment<T>::Zero;

//[PRE_DECLARE_BEGIN]
typedef Segment<int> SegmentI;
typedef Segment<uint32> SegmentU;
typedef Segment<size_t> SegmentS;
typedef Segment<float> SegmentF;

//[PRE_DECLARE_END]
MEDUSA_END;
