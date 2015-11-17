// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

template<typename T>
class NotNullPtr
{
public:
	NotNullPtr(T* ptr) { MEDUSA_ASSERT_NOT_NULL(ptr, ""); mPtr = ptr; }

	template<typename T2>
	NotNullPtr(T2* ptr) { MEDUSA_ASSERT_NOT_NULL(ptr, ""); mPtr = ptr; }

	NotNullPtr(const NotNullPtr& ptr) { MEDUSA_ASSERT_NOT_NULL(ptr, ""); mPtr = ptr.Ptr(); }

	template<typename T2>
	NotNullPtr(const NotNullPtr<T2>& ptr) { MEDUSA_ASSERT_NOT_NULL(ptr, ""); mPtr = ptr.Ptr(); }

	NotNullPtr& operator=(const NotNullPtr& ptr) { MEDUSA_ASSERT_NOT_NULL(ptr, ""); mPtr = ptr.Ptr(); return *this; }

	template<typename T2>
	NotNullPtr& operator=(const NotNullPtr<T2>& ptr) { MEDUSA_ASSERT_NOT_NULL(ptr, ""); mPtr = ptr.Ptr(); return *this; }

	~NotNullPtr() { mPtr = nullptr; }
	T& operator*()const { return *mPtr; }
	T* operator->()const { return mPtr; }
	operator T*()const { return mPtr; }
	T* Ptr()const { return mPtr; }
	T& Reference()const { return *mPtr; }

	NotNullPtr& operator=(T* ptr) { mPtr = ptr; return *this; }
	NotNullPtr& operator++() { ++mPtr; return *this; }
	NotNullPtr& operator--() { --mPtr; return *this; }
	NotNullPtr operator++(int) { T* p = mPtr; ++mPtr; return p; }
	NotNullPtr operator--(int) { T* p = mPtr; --mPtr; return p; }
protected:
	void* operator new (size_t t);
	void  operator delete(void *ptr);
private:
	T* mPtr;
};

MEDUSA_END;