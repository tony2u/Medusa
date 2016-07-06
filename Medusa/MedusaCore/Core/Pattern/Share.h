// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;

template<typename T>
class Share
{
public:
	using PointeeType = T;
	using PointerType = T*;
public:
	Share() = default;

	Share(std::nullptr_t) { }
	Share(T* ptr) { mPtr = ptr; SAFE_RETAIN(mPtr); }

	template<typename T2,typename std::enable_if<std::is_convertible<T2*,T*>::value,bool>::type isConverted>
	Share(T2* ptr) { mPtr = ptr; SAFE_RETAIN(mPtr); }
	Share(const Share& ptr) { mPtr = ptr.mPtr; SAFE_RETAIN(mPtr); }
	Share& operator=(const Share& ptr)
	{
		SAFE_ASSIGN_REF(mPtr, ptr.mPtr);
		return *this;
	}

	Share(Share&& ptr)
	{
		mPtr = ptr.mPtr;
		ptr.mPtr = nullptr;
	}

	Share& operator=(Share&& ptr)
	{
		SAFE_RELEASE(mPtr);
		mPtr = ptr.mPtr;
		ptr.mPtr = nullptr;
		return *this;
	}

	template<typename T2>
	Share(const Share<T2>& ptr)
	{
		mPtr = ptr.Ptr();
		SAFE_RETAIN(mPtr);
	}

	template<typename T2>
	Share& operator=(const Share<T2>& ptr) { SAFE_ASSIGN_REF(mPtr, ptr.Ptr()); return *this; }

	template<typename T2>
	Share(Share<T2>&& ptr)
	{
		mPtr = ptr.Ptr();
		ptr.SetPtr(nullptr);
	}

	template<typename T2>
	Share& operator=(Share<T2>&& ptr)
	{
		SAFE_RELEASE(mPtr);
		mPtr = ptr.Ptr();
		ptr.SetPtr(nullptr);
		return *this;
	}

	~Share()
	{
		SAFE_RELEASE(mPtr);
	}
	T& operator*()const { return *mPtr; }
	T* operator->()const { return mPtr; }
	//operator T*()const { return mPtr; }
	T* Ptr()const { return mPtr; }
	void SetPtr(T* val) { mPtr = val; }

	T& Reference()const { return *mPtr; }
	explicit operator bool() const { return mPtr!=nullptr; }

	Share& operator=(T* ptr) { SAFE_ASSIGN_REF(mPtr, ptr); return *this; }
	template<typename T2>
	Share& operator=(T2* ptr) { SAFE_ASSIGN_REF(mPtr, ptr); return *this; }



	bool operator==(std::nullptr_t)const { return mPtr == nullptr; }
	bool operator!=(std::nullptr_t)const { return mPtr != nullptr; }

	friend bool operator==(std::nullptr_t,const Share& self){ return self.mPtr == nullptr; }
	friend bool operator!=(std::nullptr_t, const Share& self) { return self.mPtr != nullptr; }

	bool operator==(const Share& ptr)const { return mPtr == ptr.mPtr; }
	bool operator!=(const Share& ptr)const { return mPtr != ptr.mPtr; }

	bool operator==(const T* ptr)const { return mPtr == ptr; }
	bool operator!=(const T* ptr)const { return mPtr != ptr; }
	friend bool operator==(const T* ptr, const Share& self) { return self.mPtr == ptr; }
	friend bool operator!=(const T* ptr, const Share& self) { return self.mPtr != ptr; }


	template<typename T2>
	bool operator==(const T2* ptr)const { return mPtr == ptr; }
	template<typename T2>
	bool operator!=(const T2* ptr)const { return mPtr != ptr; }

	template<typename T2>
	friend bool operator==(const T2* ptr, const Share& self) { return self.mPtr == ptr; }
	template<typename T2>
	friend bool operator!=(const T2* ptr, const Share& self) { return self.mPtr != ptr; }

	template<typename T2>
	bool operator==(const Share<T2>& ptr)const { return mPtr == ptr.mPtr; }
	template<typename T2>
	bool operator!=(const Share<T2>& ptr)const { return mPtr != ptr.mPtr; }

	

	intp HashCode()const { return (intp)mPtr; }

	template<typename T2>
	T2 To()const
	{
		return T2(mPtr);
	}

	template<typename T2>
	T2 Cast()const
	{
		return T2((T2::PointerType)mPtr);
	}

	template<typename T2>
	Share<T2> CastPtr()const
	{
		return Share<T2>((T2*)mPtr);
	}

	template<typename T2>
	T2 Try()const
	{
		if (std::is_convertible<T*, T2::PointerType>::value || std::is_convertible< T2::PointerType, T*>::value)
		{
			return T2(mPtr);
		}
		return nullptr;
	}

private:
	T* mPtr = nullptr;
};

MEDUSA_END;