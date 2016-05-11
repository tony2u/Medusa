// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/Serialization/ISirenSizeCounter.h"

MEDUSA_BEGIN;

class BaseSirenBinarySizeCounter:public ISirenSizeCounter
{
public:
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

	virtual bool OnError() override
	{
		mSize = 0;
		return true;
	}

};

MEDUSA_END;
