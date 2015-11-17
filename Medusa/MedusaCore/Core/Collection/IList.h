// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once


#include "Core/Collection/ICollection.h"

MEDUSA_BEGIN;

template<typename T>
class IList :public ICollection<T>
{
protected:
	IList() :mItems(nullptr) {}
public:
	using ICollection<T>::GetEnumeratorVirtual;
	using  ICollection<T>::IsEmpty;
	using  ICollection<T>::ByteSize;
	using  ICollection<T>::Count;

	typedef ICollection<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;


public:
	inline intp IndexOf(TParameterType val)const { return IndexOf(0, val); }
	inline intp IndexOf(size_t srcBegin, TParameterType val)const { if (this->mCount <= 0) { return -1; } return IndexOf(srcBegin, this->mCount - 1, val); }

	inline intp LastIndexOf(TParameterType val)const { return LastIndexOf(0, val); }
	inline intp LastIndexOf(size_t srcBegin, TParameterType val)const { if (this->mCount <= 0) { return -1; } return LastIndexOf(srcBegin, this->mCount - 1, val); }

	inline TConstReturnType First()const { return this->operator[](0); }
	inline TConstReturnType Last()const { return this->operator[](this->mCount - 1); }

	inline TReferenceType First() { return this->operator[](0); }
	inline TReferenceType Last() { return this->operator[](this->mCount - 1); }
	inline void Reverse() { if (this->mCount > 0) { Reverse(0, this->mCount - 1); } }


	inline bool Contains(TParameterType val)const { return Contains(0, val); }
	inline bool Contains(size_t srcBegin, TParameterType val)const { return Contains(srcBegin, this->mCount, val); }
	inline bool Contains(size_t srcBegin, size_t srcEnd, TParameterType val)const { return IndexOf(srcBegin, srcEnd, val) >= 0; }

	inline void Push(TParameterType val, size_t count = 1) { Insert(0, val, count); }
	inline void PushRange(const IEnumerable<T>& items) { InsertRange(0, items); }
	inline void PushRange(const ICollection<T>& items) { InsertRange(0, items); }

	inline void Append(TParameterType val, size_t count = 1) { Insert(this->mCount, val, count); }
	inline void AppendRange(const IEnumerable<T>& items) { InsertRange(this->mCount, items); }
	inline void AppendRange(const ICollection<T>& items) { InsertRange(this->mCount, items); }

	inline bool RemoveFirst(TParameterType val) { if (this->mCount > 0) { return RemoveFirst(0, this->mCount, val); } }
	inline void RemoveFirst() { if (this->mCount > 0) { RemoveAt(0); } }
	inline bool RemoveFirst(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		intp index = IndexOf(srcBegin, srcEnd, val);
		if (index >= 0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}

	inline bool RemoveLast(TParameterType val) { if (this->mCount > 0) { return RemoveLast(0, this->mCount, val); }return false; }
	inline void RemoveLast() { if (this->mCount > 0) { RemoveAt(this->mCount - 1); } }
	inline bool RemoveLast(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		intp index = LastIndexOf(srcBegin, srcEnd, val);
		if (index >= 0)
		{
			RemoveAt(index);
			return true;
		}

		return false;
	}
	inline void RemoveAll(TParameterType val) { if (this->mCount > 0) { RemoveAll(0, this->mCount, val); } }


	inline void AddRange(const IEnumerable<T>& items) { InsertRange(this->mCount, items); }
	inline void AddRange(const ICollection<T>& items) { InsertRange(this->mCount, items); }
	inline void RemoveFrom(size_t index) { RemoveRange(index, this->mCount - index); }

	inline TConstReturnType operator[](size_t index)const
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		return mItems[index];
	}
	virtual TReferenceType operator[](size_t index)
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		return mItems[index];
	}

	inline TConstReturnType Get(size_t index)const
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		return mItems[index];
	}
	inline void Set(size_t index, TParameterType val)
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		mItems[index] = val;
	}

#pragma region Unordered
	inline bool RemoveFirstUnordered(TParameterType val) { if (this->mCount > 0) { return RemoveFirstUnordered(0, this->mCount, val); } }
	inline void RemoveFirstUnordered() { if (this->mCount > 0) { RemoveAtUnordered(0); } }
	inline bool RemoveFirstUnordered(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		intp index = IndexOf(srcBegin, srcEnd, val);
		if (index >= 0)
		{
			RemoveAtUnordered(index);
			return true;
		}
		return false;
	}

	inline bool RemoveLastUnordered(TParameterType val) { if (this->mCount > 0) { return RemoveLastUnordered(0, this->mCount, val); }return false; }
	inline bool RemoveLastUnordered(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		intp index = LastIndexOf(srcBegin, srcEnd, val);
		if (index >= 0)
		{
			RemoveAtUnordered(index);
			return true;
		}

		return false;
	}
	inline void RemoveAllUnordered(TParameterType val) { if (this->mCount > 0) { RemoveAllUnordered(0, this->mCount, val); } }
#pragma endregion Unordered


public:

	virtual void SetRange(size_t index, const ICollection<T>& items) = 0;
	virtual void SetRange(size_t index, const IList<T>& items) = 0;
	virtual void SetRange(size_t index, const T* items, size_t count) = 0;


	virtual intp IndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const = 0;
	virtual intp LastIndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const = 0;
	virtual void Reverse(size_t srcBegin, size_t srcEnd) = 0;

	virtual void Insert(size_t index, TParameterType val, size_t count = 1) = 0;
	virtual void InsertRange(size_t index, const IEnumerable<T>& items) = 0;
	virtual void InsertRange(size_t index, const ICollection<T>& items) = 0;
	virtual void InsertRange(size_t index, const IList<T>& items) = 0;
	virtual void InsertRange(size_t index, const T* items, size_t count) = 0;

	virtual void RemoveIndexes(const IList<size_t>& indexes) = 0;

	virtual void RemoveAt(size_t index) = 0;
	virtual void RemoveRange(size_t index, size_t count) = 0;
	virtual void RemoveAll(size_t srcBegin, size_t srcEnd, TParameterType val) = 0;
	virtual void Add(TParameterType val, size_t count = 1) = 0;
	virtual bool Remove(TParameterType val) = 0;
	virtual void Clear() = 0;
	virtual void Sort() = 0;

#pragma region Unordered
	virtual void RemoveAtUnordered(size_t index) = 0;
	virtual void RemoveRangeUnordered(size_t index, size_t count) = 0;
	virtual void RemoveAllUnordered(size_t srcBegin, size_t srcEnd, TParameterType val) = 0;
	virtual bool RemoveUnordered(TParameterType val) = 0;
#pragma endregion Unordered

protected:
	T* mItems = nullptr;

};

MEDUSA_END;