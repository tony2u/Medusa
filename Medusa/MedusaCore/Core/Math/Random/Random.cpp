// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Math/Random/Random.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Profile/PerformanceCounter.h"

MEDUSA_BEGIN;



Random::Random(uint32 seed/*=0*/)
{
	mSeed = seed == 0 ? (int)PerformanceCounter::Ticks() : seed;
}

void Random::SetSeedFromTick()
{
	mSeed = (int)PerformanceCounter::Ticks();
}

int Random::Rand()
{
	//http://www.cse.yorku.ca/~oz/marsaglia-rng.html
	//https://software.intel.com/en-us/articles/fast-random-number-generator-on-the-intel-pentiumr-4-processor/
	//fast rand
	mSeed = (214013 * mSeed + 2531011);
	return (mSeed >> 16) & 0x7FFF;
}

void Random::NextBytes(MemoryData& outData)
{
	byte* buffer = outData.MutableData();
	size_t size = outData.Size();
	FOR_EACH_SIZE(i, size)
	{
		buffer[i] = NextByte();
	}
}

int Random::NextMontecarlo()
{
	//the prob: a number be selected is equal to the number itself
	while (true)
	{
		int r1 = Rand();
		int r2 = Rand();
		if (r2 < r1)
		{
			return r1;
		}
	}
}


MEDUSA_END;
