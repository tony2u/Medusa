// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "NormalDistribution.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;
/*
http://en.wikipedia.org/wiki/Normal_distribution
*/

NormalDistribution::NormalDistribution(Random& random, double mean /*= 0.f*/, double sigma /*= 1.f*/)
	: mRandom(random),mMean(mean), mSigma(sigma)
{

}

double NormalDistribution::Next(bool isKeep /*= true*/)
{
	return Next(mRandom, isKeep);
}

double NormalDistribution::Next(Random& random, bool isKeep /*= true*/)
{
	double result;
	if (mOtherResult.HasValue() && isKeep)
	{
		result = mOtherResult.Value();
		mOtherResult.Clear();
	}
	else
	{
		double v1, v2, s;
		do
		{
			// reject bad values
			v1 = 2 * random.NextFloat() - 1.0;	//-1.f~1.f
			v2 = 2 * random.NextFloat() - 1.0;	//-1.f~1.f
			s = v1 * v1 + v2 * v2;
		} while (s >= 1.0);

		double multiplier = Math::Sqrt(-2.0 * Math::Log(s) / s);
		result = multiplier * v1;

		if (isKeep)
		{
			mOtherResult.SetValue(multiplier*v2);
		}
	}
	return (result * mSigma + mMean);
}



void NormalDistribution::Generate(double& outResult1, double outResult2, Random& random, double mean /*= 0.f*/, double sigma /*= 1.f*/)
{
	double v1, v2, s;
	do
	{
		// reject bad values
		v1 = 2 * random.NextFloat() - 1.0;	//-1.f~1.f
		v2 = 2 * random.NextFloat() - 1.0;	//-1.f~1.f
		s = v1 * v1 + v2 * v2;
	} while (s >= 1.0);

	double multiplier = Math::Sqrt(-2.0 * Math::Log(s) / s);
	outResult1 = multiplier * v1*sigma + mean;
	outResult2 = multiplier * v2*sigma + mean;
}




MEDUSA_END;
