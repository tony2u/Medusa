// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;

template<bool TIsAtomic = true>
class ISharable :public INonCopyable<ISharable<TIsAtomic>>
{
	typedef typename std::conditional<TIsAtomic, std::atomic_int, int>::type ValueType;
public:
	ISharable() :mRefCount(0) {}
	virtual ~ISharable() { mRefCount = 0; }
	int RefCount()const { return mRefCount; }
	bool IsShared()const { return mRefCount > 1; }

	MEDUSA_VIRTUAL int Retain() const { return ++mRefCount; }
	MEDUSA_VIRTUAL int AddRef() const { return ++mRefCount; }
	MEDUSA_VIRTUAL bool Release()const
	{
		if (--mRefCount <= 0)
		{
			delete this;
            return false;
		}
        return true;
	}
protected:
	mutable ValueType mRefCount;
};

typedef ISharable<true> ISharableThreadSafe;
typedef ISharable<false> ISharableSingleThread;


MEDUSA_END;