#pragma once
#include "Core/Pattern/Ptr/LazyStrongPtr.h"

MEDUSA_BEGIN;

template<typename T, typename TDeleter>
T* LazyStrongPtr<T, TDeleter>::ForcePtr()
{
	if (mPtr == nullptr)
	{
		Alloc();
	}
	return mPtr;
}

template<typename T, typename TDeleter>
T& LazyStrongPtr<T, TDeleter>::ForceReference()
{
	if (mPtr == nullptr)
	{
		Alloc();
	}
	return *mPtr;
}


template<typename T, typename TDeleter>
void LazyStrongPtr<T, TDeleter>::Alloc()
{
	mPtr = new T();
}

template<typename T, typename TDeleter>
void LazyStrongPtr<T, TDeleter>::Release()
{
	TDeleter::Delete(mPtr);
	mPtr = nullptr;
}

template<typename T, typename TDeleter>
void LazyStrongPtr<T, TDeleter>::CopyFrom(T* ptr)
{
	if (ptr == nullptr)
	{
		Release();
	}
	else
	{
		if (mPtr == nullptr)
		{
			AllocFrom(ptr);
		}
		else
		{
			*mPtr = *ptr;
		}
	}
}

template<typename T, typename TDeleter>
void LazyStrongPtr<T, TDeleter>::AllocFrom(T* ptr)
{
	mPtr = new T(*ptr);
}
MEDUSA_END;