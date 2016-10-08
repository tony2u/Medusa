// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

class Random
{
public:
	constexpr static int  Max = 0x7fff;
	constexpr static float ProbPrecision= 1.f / 0x7fff;
	static Random& Global()
	{
		static Random global;
		return global;
	}
public:
	Random(uint32 seed = 0);
public:
	int Next() { return Rand(); }
	int Next(int min, int max) { return min + Rand() % (max - min + 1); }
	int Next(const RangeI& range);

	int Next(int max) { return Rand() % (max + 1); }
	float NextFloat(float min, float max) { return min + NextFloat()*(max - min); }
	float NextFloat() { return (float)Rand() *ProbPrecision; }
	float NextFloat(const RangeF& range);
	byte NextByte() { return (byte)(Rand() % 256); }
	bool NextBool() { return Rand() % 2 == 0; }
	bool NextBool(float prob) { return (float)Rand() <= prob*Max; }
	void NextBytes(MemoryData& outData);

	void SetSeed(int val) { mSeed = val; }
	void SetSeedFromTick();

	int NextMontecarlo();

private:
	int Rand();
private:
	int mSeed;
};

MEDUSA_END;
