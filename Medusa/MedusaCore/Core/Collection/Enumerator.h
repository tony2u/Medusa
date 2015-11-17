// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/IEnumerator.h"

MEDUSA_BEGIN;

template<typename T,typename TPtr>
class Enumerator
{
public:
	Enumerator(IEnumerator<T, TPtr>* enumator) :mEnumeartor(enumator) { MEDUSA_ASSERT_NOT_NULL(mEnumeartor, "enumator should not be null!"); }
	~Enumerator() { SAFE_DELETE(mEnumeartor); }
	T operator*() { return mEnumeartor->Current(); }
	TPtr operator->() { return mEnumeartor->CurrentPtr(); }

	bool MoveNext() { return mEnumeartor->MoveNext(); }
	void Reset() { return mEnumeartor->Reset(); }

private:
	IEnumerator<T, TPtr>* mEnumeartor;
};

MEDUSA_END;