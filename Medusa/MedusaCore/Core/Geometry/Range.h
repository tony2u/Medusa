// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Math/Math.h"
#include "Core/Utility/Utility.h"
#include "Core/Siren/SirenDefines.h"


MEDUSA_BEGIN;

template<typename T>
class Range
{
public:
	union
	{
		T Buffer[2];
		struct
		{
			T Min;
			T Max;
		};
	};

	const static Range Init;
public:
	Range(void) :Min(Math::Values<T>::Max), Max(Math::Values<T>::Min) {}
	Range(T min, T max) :Min(min), Max(max) { MEDUSA_ASSERT_LESS_EQUAL(min, max, "Invalid range."); }

	template<typename T1>
	Range(const Range<T1>& range) : Min((T)range.Min), Max((T)range.Max) {}

	template<typename T1>
	explicit Range(T1 val) :Min((T)val), Max((T)val) {}

	template<typename T1>
	Range& operator=(const Range<T1>& range) { Min = (T)range.Min; Max = (T)range.Max; return *this; }
	template<typename T1>
	Range& operator=(T1 val) { Min = (T)val; Max = (T)val; return *this; }

	template<typename T1>
	bool operator==(const Range<T1>& range)const { return Math::IsEqual(Min, range.Min) && Math::IsEqual(Max, range.Max); }
	template<typename T1>
	bool operator!=(const Range<T1>& range)const { return !operator==(range); }
	template<typename T1>
	bool operator>(const Range<T1>& range)const { return Min > range.Min&&Max > range.Max; }
	template<typename T1>
	bool operator<(const Range<T1>& range)const { return Min < range.Min&&Max < range.Max; }
	template<typename T1>
	bool operator>=(const Range<T1>& range)const { return Min >= range.Min&&Max >= range.Max; }
	template<typename T1>
	bool operator<=(const Range<T1>& range)const { return Min <= range.Min&&Max <= range.Max; }

	intp HashCode()const { return HashUtility::Hash(Buffer); }

	void FixMin()
	{
		if (Min > Max)
		{
			Min = Max;
		}
	}

	void FixMax()
	{
		if (Max < Min)
		{
			Max = Min;
		}
	}
	void ExpandMin(T val)
	{
		if (Min > val)
		{
			Min = val;
		}
	}

	void ShrinkMin(T val)
	{
		if (Min < val)
		{
			Min = val;
		}
	}


	void ExpandMax(T val)
	{
		if (Max < val)
		{
			Max = val;
		}
	}

	void ShrinkMax(T val)
	{
		if (Max > val)
		{
			Max = val;
		}
	}

	void Expand(Range<T> other)
	{
		ExpandMin(other.Min);
		ExpandMax(other.Max);
	}

	void Expand(T val)
	{
		ExpandMin(val);
		ExpandMax(val);
	}

	void ExpandRange(T from, T to)
	{
		ExpandMin(from);
		ExpandMax(to);
	}

	void ExpandRangeFrom(T from, T to)
	{
		ExpandMin(from);
		Max = to;
	}


	bool Contains(T val)const
	{
		return val >= Min&&val <= Max;
	}
	void Reset()
	{
		Min = Math::Values<T>::Max;
		Max = Math::Values<T>::Min;
	}

	bool IsEmpty()const
	{
		return Min >= Max;
	}

	T Length()const
	{
		return Max - Min;
	}

	T Center()const
	{
		return Min + (Max - Min) / 2;
	}

	T Count()const
	{
		return Max - Min + 1;
	}

	T CalculateMinDockMovement(T to)const
	{
		T d1 = to - Min;
		T d2 = to - Max;
		return (Math::Abs(d1) < Math::Abs(d2)) ? d1 : d2;
	}

	T MovementFromMin(T val)const
	{
		return val - Min;
	}

	T MovementToMax(T val)const
	{
		return Max - val;
	}

	int Compare(const Range<T>& range)const
	{
		if (Min >= range.Max)
		{
			return 1;
		}
		else if (Max <= range.Min)
		{
			return -1;
		}
		return 0;
	}

	T Clamp(T val)const
	{
		return Math::Clamp(val, Min, Max);
	}

};

template<typename T>
MEDUSA_WEAK_MULTIPLE_DEFINE const Range<T> Range<T>::Init;

//[PRE_DECLARE_BEGIN]
typedef Range<int> RangeI;
typedef Range<uint32> RangeU;
typedef Range<size_t> RangeS;
typedef Range<float> RangeF;
//[PRE_DECLARE_END]

namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<Range<T>> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const Range<T>& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<T, false>("Min", 3, 0, obj.Min);
		writer.template OnProperty<T, false>("Max", 3, 1, obj.Max);
		writer.OnStructEnd();
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, Range<T>& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<T, false>("Min", 3, 0, outObj.Min);
		reader.template OnProperty<T, false>("Max", 3, 1, outObj.Max);
		reader.OnStructEnd();

		return true;
	}
}


MEDUSA_END;
