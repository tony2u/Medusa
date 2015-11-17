// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Math/Random/Random.h"
#include "Core/Pattern/Nullable.h"

MEDUSA_BEGIN;

class NormalDistribution
{
public:
	NormalDistribution(Random& random, double mean = 0.f, double sigma = 1.f);
public:
	double Mean() const { return mMean; }
	void SetMean(double val) { mMean = val; }

	double Sigma() const { return mSigma; }
	void SetSigma(double val) { mSigma = val; }

public:
	static void Generate(double& outResult1, double outResult2, Random& random, double mean = 0.f, double sigma = 1.f);
	double Next(Random& random, bool isKeep = true);
	double Next(bool isKeep = true);

private:
	Random& mRandom;

	double mMean;	
	double mSigma;	

	Nullable<double> mOtherResult;
};

MEDUSA_END;
