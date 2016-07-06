// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/ISharable.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;
template<bool TIsAtomic = true>
class ISharableWithName :public ISharable < TIsAtomic >
{
public:
	ISharableWithName(const StringRef& name = StringRef::Empty) :mName(name) {}
	ISharableWithName(HeapString&& name) :mName(name) {}

	virtual ~ISharableWithName(void) {}

	StringRef Name() const { return mName; }
	void SetName(const StringRef& name) { mName = name; }
	bool HasName()const { return !mName.IsEmpty(); }
protected:
	HeapString mName;
};

typedef ISharableWithName<true> ISharableThreadSafeWithName;
typedef ISharableWithName<false> ISharableSingleThreadWithName;
MEDUSA_END;