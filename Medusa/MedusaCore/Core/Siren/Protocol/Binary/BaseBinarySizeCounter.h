// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "MedusaCorePreDeclares.h"

MEDUSA_SIREN_BEGIN;

class BaseBinarySizeCounter
{
public:
	BaseBinarySizeCounter() :mSize(0) {}

	template<typename T>
	static inline uint CountVariableUnsigned(T value)
	{
		uint count = 0;
		while (true)
		{
			T x = value >> 7;
			if (x != 0)
			{
				++count;
				value = x;
			}
			else
			{
				++count;
				break;
			}
		}
		return count;
	}

	void OnError()
	{
		mSize = 0;
	}

	uint Size() const { return mSize; }
protected:
	uint mSize;
};

MEDUSA_SIREN_END;
