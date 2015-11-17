// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/IEnumerable.h"

MEDUSA_BEGIN;

template<typename T>
struct ICollection :public IEnumerable<T>
{
protected:
	ICollection() :mCount(0) {}
	virtual ~ICollection() {}
public:
	using IEnumerable<T>::GetEnumeratorVirtual;
	typedef IEnumerable<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;

	inline size_t Count() const { return mCount; }
	inline void ForceSetCount(size_t val) { mCount = val; }
	virtual void ReserveSize(size_t size) {}
	inline bool IsEmpty()const { return mCount == 0; }
	inline size_t ByteSize() const { return mCount*sizeof(T); }
public:
	virtual bool IsLinear() const = 0;

	virtual TConstPointerType Items() const = 0;
	virtual TPointerType MutableItems() = 0;

	virtual bool Contains(TParameterType val)const = 0;
	virtual size_t CopyTo(T* outArray, size_t arraySize)const = 0;
protected:
	size_t mCount = 0;
};

MEDUSA_END;