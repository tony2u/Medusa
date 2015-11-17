// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"


MEDUSA_BEGIN;

//DO NOT copy LazyStrongPtr to another LazyStrongPtr
//DO NOT delete LazyStrongPtr
//DO NOT put into collections because it cannot be copied
template<typename T, typename TDeleter = DefaultPointerDeleter<T> >
class LazyStrongPtr
{
public:
	explicit LazyStrongPtr(T* ptr = nullptr) :mPtr(ptr) {}

	template<typename T2, typename TDeleter2>
	explicit LazyStrongPtr(T2* ptr) :mPtr(ptr) {}

	LazyStrongPtr(const LazyStrongPtr& ptr) { AllocFrom(ptr.mPtr); }
	LazyStrongPtr(LazyStrongPtr&& ptr)
		:mPtr(ptr.mPtr)
	{
		ptr.mPtr = nullptr;
	}


	template<typename T2, typename TDeleter2>
	LazyStrongPtr(const LazyStrongPtr<T2>& ptr) { AllocFrom((T*)ptr.mPtr); }


	~LazyStrongPtr() { Release(); }
	T& operator*()const { return *mPtr; }
	T* operator->()const { return mPtr; }
	operator T*()const { return mPtr; }

	T* ForcePtr();
	T& ForceReference();

	T* Ptr()const { return mPtr; }
	T& Reference()const { return *mPtr; }


	LazyStrongPtr& operator=(T* ptr) { CopyFrom(ptr); return *this; }
	LazyStrongPtr& operator=(const LazyStrongPtr& ptr) { CopyFrom(ptr.mPtr); return *this; }
	LazyStrongPtr& operator=(LazyStrongPtr&& ptr) 
	{
		if (this!=&ptr)
		{
			Release();
			mPtr = ptr.mPtr;
			ptr.mPtr = nullptr;
		}
		return *this; 
	}



	template<typename T2>
	LazyStrongPtr& operator=(T2* ptr) { CopyFrom((T*)ptr); return *this; }

	template<typename T2, typename TDeleter2>
	LazyStrongPtr& operator=(const LazyStrongPtr<T2>& ptr) { CopyFrom(ptr.mPtr); return *this; }



	void Alloc();
	void Release();
	void CopyFrom(T* ptr);
	void AllocFrom(T* ptr);

	void ForceSet(T* ptr) { mPtr = ptr; }
	bool IsNull()const { return mPtr == nullptr; }
	void MakeSureValid() { if (mPtr == nullptr) { Alloc(); } }
protected:
	void* operator new (size_t t)=delete;
	void  operator delete(void *ptr)=delete;
private:
	T* mPtr;
};

MEDUSA_END;