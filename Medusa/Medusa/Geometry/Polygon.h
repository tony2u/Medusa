// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Geometry/Point2.h"
#include "Geometry/Rect2.h"
#include "Geometry/Range.h"
#include "Core/Collection/List.h"
#include "Core/Math/Math.h"
#include "Geometry/GeometryAlgorithm.h"


MEDUSA_BEGIN;

template<typename T>
class Polygon
{
public:
	bool IsPreCalculatedEnabled() const { return mPreCalculatedEnabled; }
	void EnablePreCalculated(bool val)
	{
		RETURN_IF_EQUAL(mPreCalculatedEnabled, val);
		mPreCalculatedEnabled = val;
		UpdatePreCalculates();
	}

	void UpdatePreCalculates()
	{
		mPreCalculatedConstants.Clear();
		mPreCalculatedConstants.ReleaseExtraSize();
		mPreCalculatedMultiples.Clear();
		mPreCalculatedMultiples.ReleaseExtraSize();

		if (mPreCalculatedEnabled)
		{
			mPreCalculatedConstants.ReserveSize(mVertices.Count());
			mPreCalculatedMultiples.ReserveSize(mVertices.Count());

			GeometryAlgorithm::PreCalculatePolygonTest2((const float*)mVertices.Items(), (float*)mPreCalculatedConstants.MutableItems(), (float*)mPreCalculatedMultiples.MutableItems(), mVertices.Count());
			mPreCalculatedConstants.ForceSetCount(mVertices.Count());
			mPreCalculatedMultiples.ForceSetCount(mVertices.Count());
		}
	}

	bool IsRangeEnabled() const { return mRangeEnabled; }

	void EnableRange(bool val) { RETURN_IF_EQUAL(mRangeEnabled, val); mRangeEnabled = val; UpdateRange(); }
	void UpdateRange()
	{
		mRangeX.Reset();
		mRangeY.Reset();
		if (mRangeEnabled)
		{
			FOR_EACH_COLLECTION(i, mVertices)
			{
				const Point2<T>& pos = *i;
				mRangeX.Expand(pos.X);
				mRangeY.Expand(pos.Y);
			}
		}
	}

	void Update()
	{
		UpdateRange();
		UpdatePreCalculates();
	}
public:
	Polygon(void) :mPreCalculatedEnabled(false) {}

	template<typename T1>
	Polygon(const Polygon<T1>& polygon) : mVertices(polygon.mVertices) {}
	template<typename T1>
	Polygon& operator=(const Polygon<T1>& polygon) { mVertices = polygon.mVertices;  return *this; }

	const List<Point2<T> >& Vertices() const { return mVertices; }
	List<Point2<T> >& MutableVertices() { return mVertices; }


	intp HashCode()const { return HashUtility::HashIntArray((const int*)mVertices.Items(), mVertices.Count() * 2); }

	bool Contains(const Point2<T>& pos)const
	{
		if (mRangeEnabled)
		{
			return ContainsInRange(pos);
		}
		return ContainsInPolygon(pos);
	}
	bool ContainsInRange(const Point2<T>& pos)const
	{
		if (mRangeEnabled)
		{
			return mRangeX.Contains(pos.X) && mRangeY.Contains(pos.Y);
		}
		return false;

	}

	bool ContainsInPolygon(const Point2<T>& pos)const
	{
		if (mRangeEnabled)
		{
			if (!mRangeX.Contains(pos.X) || !mRangeY.Contains(pos.Y))
			{
				return false;
			}
		}

		if (mPreCalculatedEnabled&&!mPreCalculatedConstants.IsEmpty() && !mPreCalculatedMultiples.IsEmpty())
		{
			return GeometryAlgorithm::IsInPolygonWithPreCalculate2((const float*)mVertices.Items(), (const float*)mPreCalculatedConstants.Items(), (const float*)mPreCalculatedMultiples.Items(), mVertices.Count(), pos.X, pos.Y);
		}
		else
		{
			return GeometryAlgorithm::IsInPolygon2((const float*)mVertices.Items(), mVertices.Count(), pos.X, pos.Y);
		}
	}

	void AddVertex(const Point2<T>& pos)
	{
		mVertices.Add(pos);
	}

	Point2<T>& NewVertex()
	{
		return mVertices.NewAdd();
	}

	float Area()const
	{
		uint count = mVertices.Count();
		if (count < 3)
		{
			return 0.f;
		}

		float s = mVertices[0].Y*(mVertices[count - 1].X - mVertices[1].X);
		FOR_EACH_SIZE_BEGIN_END(i, 1, count - 1)
		{
			s += mVertices[i].Y*(mVertices[i - 1].X - mVertices[(i + 1) % count].X);
		}
		return Math::Abs(s*0.5f);
	}

	const Range<T>& RangeX() const { return mRangeX; }
	const Range<T>& RangeY() const { return mRangeY; }
	Rect2<T> BoundingBox()const { return Rect2<T>(mRangeX.Min,mRangeY.Min,mRangeX.Length(),mRangeY.Length()); }
protected:
	List<Point2<T> > mVertices;
	List<float> mPreCalculatedConstants;
	List<float> mPreCalculatedMultiples;
	bool mPreCalculatedEnabled;

	Range<T> mRangeX;
	Range<T> mRangeY;
	bool mRangeEnabled;

};


//[PRE_DECLARE_BEGIN]
typedef Polygon<int> PolygonI;
typedef Polygon<float> PolygonF;
//[PRE_DECLARE_END]
MEDUSA_END;
