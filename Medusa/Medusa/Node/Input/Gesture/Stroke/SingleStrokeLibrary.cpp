// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
//SIREN_BODY_INCLUDE_BEGIN
#include "SingleStrokeLibrary.h"
//SIREN_BODY_INCLUDE_END

MEDUSA_BEGIN;

SingleStrokeLibrary::SingleStrokeLibrary()
{
//SIREN_BODY_CONSTRUCT_BEGIN
//SIREN_BODY_CONSTRUCT_END
}

SingleStrokeLibrary::~SingleStrokeLibrary()
{
//SIREN_BODY_DESTRUCT_BEGIN
	SAFE_DELETE_COLLECTION(mTemplates);
//SIREN_BODY_DESTRUCT_END
}


void SingleStrokeLibrary::Add(SingleStrokeTemplate* val)
{
	val->Normalize(StrokePointCount, SquareSize, mIgnoreRotation);
	mTemplates.Add(val);
}


double SingleStrokeLibrary::DistanceAtAngle(const PointPath2F& from, const PointPath2F& to, float rotation)const
{
	auto copy = from;
	copy.Rotate(rotation);
	return copy.GetDistance(to);
}

double SingleStrokeLibrary::DistanceAtBestAngle(const PointPath2F& from, const PointPath2F& to)const
{
	float startRange = -AngleRange();
	float endRange = AngleRange();
	float x1 = mGoldenRatio * startRange + (1.f - mGoldenRatio) * endRange;
	double f1 = DistanceAtAngle(from, to, x1);
	float x2 = (1.f - mGoldenRatio) * startRange + mGoldenRatio * endRange;
	double f2 = DistanceAtAngle(from, to, x2);
	while (fabs(endRange - startRange) > mAnglePrecision)
	{
		if (f1 < f2)
		{
			endRange = x2;
			x2 = x1;
			f2 = f1;
			x1 = mGoldenRatio * startRange + (1.f - mGoldenRatio) * endRange;
			f1 = DistanceAtAngle(from, to, x1);
		}
		else
		{
			startRange = x1;
			x1 = x2;
			f1 = f2;
			x2 = (1.f - mGoldenRatio) * startRange + mGoldenRatio * endRange;
			f2 = DistanceAtAngle(from, to, x2);
		}
	}
	return Math::Min(f1, f2);
}



double SingleStrokeLibrary::OptimalCosineDistance(const PointPath2F& from, const PointPath2F& to)const // for Protractor
{
	double a = 0.0;
	double b = 0.0;

	uint count = (uint)from.Points().Count();
	// Compute protractor a and b values
	// a = sum_i( xt_i*xg_i + yt_i*yg_i)
	// b = sum_i( xt_i*yg_i - yt_i*xg_i)
	FOR_EACH_UINT32(i, count)
	{
		const auto& p1 = from.Points()[i];
		const auto& p2 = to.Points()[i];
		a += p1.X*p2.X + p1.Y*p2.Y;
		b += p1.X*p2.Y - p1.Y*p2.X;
	}

	float angle = Math::Atan((float)(b / a));
	return Math::Acos(float(a * Math::Cos(angle) + b * Math::Sin(angle)));
}


bool SingleStrokeLibrary::OnLoaded()
{
	for (auto* item : mTemplates)
	{
		item->CalculateVectors();
	}
	return true;
}

const SingleStrokeTemplate* SingleStrokeLibrary::Recognize(float& outScore, SingleStrokeTemplate& val, SingleStrokeRecognizeAlgorithm algorithm /*= SingleStrokeRecognizeAlgorithm::Protractor*/) const
{
	if (mTemplates.IsEmpty())
	{
		return nullptr;
	}

	val.Normalize(StrokePointCount, SquareSize, mIgnoreRotation);
	const SingleStrokeTemplate* result = nullptr;

	//--- Initialize best distance to the largest possible number
	//--- That way everything will be better than that
	double bestDistance = Math::DoubleMaxValue;
	//--- We haven't found a good match yet
	outScore = 0.0;

	for (const auto* item : mTemplates)
	{
		double distance;
		//--- Calculate the total distance of each point in the passed in
		//---  shape against the corresponding point in the template
		//--- We'll rotate the shape a few degrees in each direction to
		//---  see if that produces a better match
		if (algorithm == SingleStrokeRecognizeAlgorithm::Protractor)
			distance = OptimalCosineDistance(val.Vectors(), item->Vectors());
		else
			distance = DistanceAtBestAngle(val.Path(), item->Path());

		if (distance < bestDistance)
		{
			bestDistance = distance;
			result = item;
		}
	}

	//--- Turn the distance into a percentage by dividing it by
	//---  half the maximum possible distance (across the diagonal
	//---  of the square we scaled everything too)
	//--- Distance = how different they are
	//--- Subtract that from 1 (100%) to get the similarity
	if (algorithm == SingleStrokeRecognizeAlgorithm::Protractor)
	{
		outScore = (float)bestDistance ? (float)(1.f / bestDistance) : Math::FloatMaxValue;
	}
	else
	{
		outScore = 1.f - (float)(bestDistance / mSquareDiagonalHalf);
	}

	return result;
}


//SIREN_BODY_METADATA_BEGIN
SIREN_METADATA(SingleStrokeLibrary, 19);
SIREN_FIELD_METADATA_STRUCT(0, SingleStrokeLibrary, Templates, 9);
//SIREN_BODY_METADATA_END

MEDUSA_END;