// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Geometry/Point2.h"
#include "Geometry/Rect2.h"
#include "Geometry/Range.h"
#include "Geometry/Scale2.h"
#include "Core/Collection/List.h"
#include "Core/Math/Math.h"
#include "Core/Siren/SirenDefines.h"

MEDUSA_BEGIN;

template<typename T>
class PointPath2
{
	using PointType = Point2<T>;
	using ScaleType = Scale2<T>;

public:
	PointPath2(void) {}

	const List<PointType >& Points() const { return mPoints; }
	List<PointType >& MutablePoints() { return mPoints; }

	intp HashCode()const { return HashUtility::HashIntArray((const int*)mPoints.Items(), mPoints.Count() * 2); }

	bool Contains(const PointType& pos)const
	{
		UpdateRange();
		return mRangeX.Contains(pos.X) && mRangeY.Contains(pos.Y);
	}

	void Add(const PointType& pos)
	{
		MarkDirty();
		mPoints.Add(pos);
	}
	void AddRange(const List<PointType>& points)
	{
		MarkDirty();
		mPoints.AddRange(points);
	}

	PointType& NewAdd()
	{
		MarkDirty();
		return mPoints.NewAdd();
	}

	void Clear()
	{
		mPoints.Clear();
	}

	float Area()const
	{
		uint count = mPoints.Count();
		if (count < 3)
		{
			return 0.f;
		}

		float s = mPoints[0].Y*(mPoints[count - 1].X - mPoints[1].X);
		FOR_EACH_SIZE_BEGIN_END(i, 1, count - 1)
		{
			s += mPoints[i].Y*(mPoints[i - 1].X - mPoints[(i + 1) % count].X);
		}
		return Math::Abs(s*0.5f);
	}

	T Length()const
	{
		UpdateLength();
		return mLength;
	}

	T GetDistance(const PointPath2& other)const
	{
		MEDUSA_ASSERT(mPoints.Count() == other.mPoints.Count(), "INVALID_POINT_COUNT");

		T length = 0;
		size_t count = mPoints.Count();
		for (size_t i = 0; i < count; ++i)
		{
			length += mPoints[i].GetDistance(other.mPoints[i]);
		}
		return length;
	}


	const Range<T>& RangeX() const { UpdateRange(); return mRangeX; }
	const Range<T>& RangeY() const { UpdateRange(); return mRangeY; }
	Rect2<T> BoundingBox()const
	{
		UpdateRange();
		return Rect2<T>(mRangeX.Min, mRangeY.Min, mRangeX.Length(), mRangeY.Length());
	}

	Point2F Center()const
	{
		UpdateCenter();
		return mCenter;
	}

	float IndicativeAngle()const
	{
		UpdateCenter();
		return Math::Atan2(mPoints[0].Y - mCenter.Y, mPoints[0].X - mCenter.X);
	}

	PointPath2& Combine(const PointPath2& other)
	{
		mPoints.AddRange(other.mPoints);
		MarkDirty();
	}

	PointPath2& Rotate(float radian)
	{
		UpdateCenter();
		float cosine = Math::Cos(radian);
		float sine = Math::Sin(radian);

		for (auto& point : mPoints)
		{
			float qx = (point.X - mCenter.X) * cosine - (point.Y - mCenter.Y) * sine + mCenter.X;
			float qy = (point.X - mCenter.X) * sine + (point.Y - mCenter.Y) * cosine + mCenter.Y;
			point.X = (T)qx;
			point.Y = (T)qy;

		}
		MarkDirty();
		return *this;
	}

	PointPath2& RotateToOrigin()
	{
		return Rotate(-IndicativeAngle());
	}

	PointPath2& Translate(PointType offset)
	{
		for (auto& point : mPoints)
		{
			point += offset;
		}
		MarkDirty();
		return *this;
	}

	PointPath2& TranslateToOrigin()
	{
		UpdateCenter();
		return Translate(-mCenter);
	}


	PointPath2& Scale(ScaleType val)
	{
		for (auto& point : mPoints)
		{
			point.X *= val.X;
			point.Y *= val.Y;
		}
		MarkDirty();
		return *this;
	}

	PointPath2 Resample(uint count)const
	{
		float interval = Length() / (count - 1); // interval length
		float distanceCovered = 0.f;
		PointType prevPoint= mPoints.First();
		PointPath2 newPoints;
		newPoints.Add(mPoints.First());//--- Store first point since we'll never resample it out of existence
		for (size_t i = 1; i < mPoints.Count();)
		{
			const auto& cur = mPoints[i];
			float d = cur.GetDistance(prevPoint);
			if ((distanceCovered + d) >= interval)
			{
				float blend = (interval - distanceCovered) / d;
				prevPoint = Math::LinearInterpolate(prevPoint, cur, blend);
				distanceCovered = 0.f;
				newPoints.NewAdd() = prevPoint;
			}
			else
			{
				prevPoint = mPoints[i];
				distanceCovered += d;
				++i;
			}
		}

		// sometimes we fall a rounding-error short of adding the last point, so add it if so
		if (newPoints.mPoints.Count() == (count - 1))
		{
			newPoints.Add(mPoints.Last());
		}

		return newPoints;
	}

	PointPath2& Vectorize()
	{
		double sum = 0.0;
		for (const auto& i : mPoints)
		{
			sum += i.LengthSquared();
		}
		double magnitude = Math::Sqrt(sum);
		for (auto& i : mPoints)
		{
			i /= (float)magnitude;
		}

		return *this;
	}
protected:
	void MarkDirty()
	{
		mIsCenterDirty = true;
		mIsRangeDirty = true;
		mIsLengthDirty = true;
	}

	void UpdateRange()const
	{
		RETURN_IF_FALSE(mIsRangeDirty);
		mRangeX.Reset();
		mRangeY.Reset();
		for (auto pos : mPoints)
		{
			mRangeX.Expand(pos.X);
			mRangeY.Expand(pos.Y);
		}
		mIsRangeDirty = false;
	}

	void UpdateCenter()const
	{
		RETURN_IF_FALSE(mIsCenterDirty);
		mCenter = PointType::Zero;
		if (!mPoints.IsEmpty())
		{
			for (const auto& item : mPoints)
			{
				mCenter += item;
			}
			mCenter /= mPoints.Count();
		}
		mIsCenterDirty = false;
	}

	void UpdateLength()const
	{
		RETURN_IF_FALSE(mIsLengthDirty);
		mLength = 0;
		size_t count = mPoints.Count();
		for (size_t i = 1; i < count; ++i)
		{
			mLength += mPoints[i - 1].GetDistance(mPoints[i]);
		}
		mIsLengthDirty = false;

	}

protected:
	List<PointType > mPoints;
	mutable PointType mCenter;
	mutable bool mIsCenterDirty = true;

	mutable Range<T> mRangeX;
	mutable Range<T> mRangeY;
	mutable bool mIsRangeDirty = true;

	mutable T mLength = 0;
	mutable bool mIsLengthDirty = true;

};


//[PRE_DECLARE_BEGIN]
typedef PointPath2<int> PointPath2I;
typedef PointPath2<float> PointPath2F;
//[PRE_DECLARE_END]



namespace Siren
{
	template <typename T>
	struct HasCustomSerialization<PointPath2<T>> : std::true_type {};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter, typename T>
	void Serialize(TWriter& writer, const PointPath2<T>& obj)
	{
		using PointType = Point2<T>;
		const auto& items = obj.Points();
		uint count = (uint)items.Count();
		writer.OnListBegin(Siren::GetDataType<PointType>::Type, (uint)count);
		FOR_EACH_UINT32(i, count)
		{
			writer.OnListItemBegin(i);
			Siren::Serialize(writer, items[i]);
			writer.OnListItemEnd(i);
		}

		writer.OnListEnd(count);
	}

	template <typename TReader, typename T>
	bool DeserializeTo(TReader& reader, PointPath2<T>& outObj)
	{
		auto& outItems = outObj.MutablePoints();
		uint outCount;
		byte outType;
		reader.OnListBegin(outType, outCount);
		outItems.Clear();
		outItems.ForceReserveCount(outCount);

		for (uint i = 0; i < outCount; ++i)
		{
			reader.OnListItemBegin(i);
			RETURN_FALSE_IF_FALSE(Siren::DeserializeTo(reader, outItems[i]));
			reader.OnListItemEnd(i);
		}
		reader.OnListEnd();
		return true;
	}
}
MEDUSA_END;
