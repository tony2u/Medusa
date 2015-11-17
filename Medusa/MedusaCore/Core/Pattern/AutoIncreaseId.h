// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

template<typename T, bool TIsAtomic = false>
struct AutoIncreaseId
{
	typedef typename std::conditional<TIsAtomic, std::atomic_int, int>::type ValueType;

private:
	static inline ValueType& MinHelper()
	{
		static ValueType min = 0;
		return min;
	}

	static inline ValueType& CurrentHelper()
	{
		static ValueType current = 0;
		return current;
	}

public:
	static inline ValueType Min()
	{
		return MinHelper();
	}

	static inline ValueType New()
	{
		return ++CurrentHelper();
	}

	static inline ValueType Deprecate(uint id)
	{
		MinHelper() = Math::Min((uint)MinHelper(), id);
		return MinHelper();
	}
};

MEDUSA_END;