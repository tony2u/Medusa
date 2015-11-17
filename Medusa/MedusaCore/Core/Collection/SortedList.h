// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/ISortedList.h"
#include "Core/Collection/STLPort.h"
#include "Core/Algorithm/Algorithm.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/Math.h"


MEDUSA_BEGIN;


template<typename T, typename TCompare = EqualCompare<T>, typename TSorter = DefaultCompare<T> >
class SortedList :public ISortedList < T >
{
	typedef SortedList<T, TCompare, TSorter> SelfType;

public:


	typedef ICollection<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

	using ISortedList<T>::IndexOf;
	using ISortedList<T>::LastIndexOf;
	using ISortedList<T>::Add;
	using ISortedList<T>::RemoveAt;
	using ISortedList<T>::RemoveAll;

	//using typename IEnumerable<T>::TConstPointerType;
	// using typename IEnumerable<T>::TPointerType;
	// using typename IEnumerable<T>::TParameterType;
	// using typename IEnumerable<T>::TReturnType;
	// using typename IEnumerable<T>::TConstReturnType;
	// using typename IEnumerable<T>::TReferenceType;

	const static SelfType Empty;
public:
	explicit SortedList(size_t size = 0)
	{
		mSize = size;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;
	}


	SortedList(const SortedList& items)
	{
		mSize = items.Count();
		this->mCount = mSize;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;

		Memory::CopyConstructIterator(this->mItems, items.Items(), mSize);
	}



	SortedList& operator=(const SortedList<T, TCompare, TSorter>& items)
	{
		Clear();
		size_t newCount = items.Count();
		if (mSize >= newCount)
		{
			Memory::CopyConstructIterator(this->mItems, items.Items(), newCount);
			this->mCount = newCount;
			ReleaseExtraSize();
		}
		else
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, newCount);
			Resize(newSize);
			Memory::CopyConstructIterator(this->mItems, items.Items(), newCount);
			this->mCount = newCount;
		}

		return *this;
	}

	template<typename T1, typename TCompare1>
	SortedList& operator=(const SortedList<T1, TCompare1>& items)
	{
		Clear();
		size_t newCount = items.Count();
		if (mSize >= newCount)
		{
			Memory::CopyConstructIterator(this->mItems, items.Items(), newCount);
			this->mCount = newCount;
			ReleaseExtraSize();
		}
		else
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, newCount);
			Resize(newSize);
			Memory::CopyConstructIterator(this->mItems, items.Items(), newCount);
			this->mCount = newCount;
		}


		return *this;
	}

	SortedList(SortedList&& other)
	{
		if (this != &other)
		{
			mSize = other.mSize;
			this->mCount = other.mCount;
			this->mItems = other.mItems;

			other.mItems = nullptr;
			other.mSize = 0;
			other.mCount = 0;
		}
	}

	SortedList& operator=(SortedList&& other)
	{
		if (this != &other)
		{
			Clear();
			SAFE_FREE(this->mItems);
			this->mSize = other.mSize;
			this->mItems = other.mItems;
			this->mCount = other.mCount;
			other.mItems = nullptr;
			other.mCount = 0;
			other.mSize = 0;
		}
		return *this;
	}

	virtual ~SortedList(void)
	{
		Memory::DestoryRange(this->mItems, this->mCount);
		SAFE_FREE(this->mItems);
	}


public:

#pragma region IEnumerable interface
public:

	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class SortedList < T, TCompare, TSorter > ;
		explicit Enumerator(T* items, size_t count) :mItems(items), mCount(count), mIndex(-1) {}

	public:
		virtual TReturnType Current() { return this->mItems[mIndex]; }
		virtual TPointerType CurrentPtr() { return this->mItems + mIndex; }

		TReturnType operator*() { return this->mItems[mIndex]; }
		TPointerType operator->() { return this->mItems + mIndex; }


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex < (int)this->mCount;
		}
		virtual void Reset() { mIndex = -1; }
	protected:
		T* mItems;
		size_t mCount;
		int mIndex;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class SortedList < T, TCompare, TSorter > ;
		explicit ConstEnumerator(const T* items, size_t count) :mItems(items), mCount(count), mIndex(-1) {}

	public:
		virtual TConstReturnType Current() { return this->mItems[mIndex]; }
		virtual TConstPointerType CurrentPtr() { return mItems + mIndex; }

		TConstReturnType operator*() { return this->mItems[mIndex]; }
		TConstPointerType operator->() { return mItems + mIndex; }


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex < (int)this->mCount;
		}
		virtual void Reset() { mIndex = -1; }
	protected:
		const T* mItems;
		size_t mCount;
		int mIndex;
	};
public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(this->mItems, this->mCount); }
	Enumerator GetEnumerator() { return Enumerator(this->mItems, this->mCount); }
protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(this->mItems, this->mCount); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(this->mItems, this->mCount); }

public:
	class ConstInterator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit ConstInterator(const T* cur) :mCurrent(cur) {}
		TConstReturnType operator*()const { return *mCurrent; }
		TConstPointerType operator->()const { return mCurrent; }
		bool operator==(const ConstInterator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const ConstInterator& other)const { return mCurrent != other.mCurrent; }
		ConstInterator& operator++() { ++mCurrent; return *this; }
		ConstInterator operator++(int)const { return ConstInterator(mCurrent + 1); }
		ConstInterator& operator--() { --mCurrent; return *this; }
		ConstInterator operator--(int)const { return ConstInterator(mCurrent - 1); }
	protected:
		const T* mCurrent;
	};

	class Interator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit Interator(T* cur) :mCurrent(cur) {}
		TReturnType operator*()const { return *mCurrent; }
		TPointerType operator->()const { return mCurrent; }
		bool operator==(const Interator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const Interator& other)const { return mCurrent != other.mCurrent; }
		Interator& operator++() { ++mCurrent; return *this; }
		Interator operator++(int)const { return Interator(mCurrent + 1); }
		Interator& operator--() { --mCurrent; return *this; }
		Interator operator--(int)const { return Interator(mCurrent - 1); }
	protected:
		T* mCurrent;
	};
	ConstInterator begin()const { return ConstInterator(this->mItems); }
	ConstInterator end()const { return ConstInterator(this->mItems + this->mCount); }
	Interator begin() { return Interator(this->mItems); }
	Interator end() { return Interator(this->mItems + this->mCount); }
#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:
	virtual bool IsLinear() const { return true; }
	virtual TConstPointerType Items() const { return this->mItems; }
	virtual TPointerType MutableItems() { return this->mItems; }


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		RETURN_ZERO_IF_NULL(this->mItems);
		size_t count = Math::Min(this->mCount, (size_t)arraySize);
		Memory::CopyConstructIterator(outArray, this->mItems, count);
		return count;
	}

	virtual bool Contains(TParameterType val)const { RETURN_FALSE_IF_ZERO(this->mCount); return IndexOf(0, this->mCount - 1, val) >= 0; }

#pragma endregion ICollection interface

#pragma region ISortedList interface

	virtual intp IndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");

		intp firstIndex = Algorithm::BinarySearchFirst<T, TSorter>(this->mItems, val, srcBegin, srcEnd);
		if (firstIndex < 0)
		{
			return firstIndex;
		}

		while (firstIndex < (intp)this->mCount)
		{
			if (TCompare::Compare(this->mItems[firstIndex], val) == 0)
			{
				return firstIndex;
			}
			++firstIndex;
		}

		return -1;
	}


	virtual intp LastIndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");
		intp lastIndex = Algorithm::BinarySearchLast<T, TSorter>(this->mItems, val, srcBegin, srcEnd);
		if (lastIndex < 0)
		{
			return lastIndex;
		}

		while (lastIndex >= 0)
		{
			if (TCompare::Compare(this->mItems[lastIndex], val) == 0)
			{
				return lastIndex;
			}
			--lastIndex;
		}

		return -1;
	}

	virtual void RemoveIndexes(const IList<size_t>& indexes)
	{
		RETURN_IF_EMPTY(indexes);
		RETURN_IF_ZERO(this->mCount);

		size_t emptyIndex = indexes[0];
		size_t indexSize = indexes.Count();
		FOR_EACH_SIZE(i, indexSize)
		{
			size_t index = indexes[i];
			Memory::Destory(this->mItems + index);
			if (i < indexSize - 1)
			{
				size_t nextIndex = indexes[i + 1];
				size_t copyCount = nextIndex - index - 1;
				if (copyCount > 0)
				{
					Memory::SafeCopyShallow(this->mItems + emptyIndex, mSize - emptyIndex, this->mItems + index + 1, copyCount);
					emptyIndex += copyCount;
				}
			}
			else
			{
				size_t copyCount = this->mCount - index - 1;
				if (copyCount > 0)
				{
					Memory::SafeCopyShallow(this->mItems + emptyIndex, mSize - emptyIndex, this->mItems + index + 1, copyCount);
				}
			}
		}

		this->mCount -= indexes.Count();
	}

	virtual void RemoveAt(size_t index)
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		Memory::Destory(this->mItems + index);
		Memory::SafeCopyShallow(this->mItems + index, mSize - index, this->mItems + index + 1, this->mCount - index - 1);
		--this->mCount;

	}

	virtual void RemoveRange(size_t begin, size_t end)
	{
		MEDUSA_ASSERT_IF(end > begin&&end < this->mCount, "");
		Memory::DestoryRange(this->mItems + begin, end - begin);
		Memory::SafeCopyShallow(this->mItems + begin, mSize - begin, this->mItems + end + 1, this->mCount - end - 1);
		this->mCount -= end - begin;
	}

	virtual void RemoveAll(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd < this->mCount, "");

		while (true)
		{
			intp index = IndexOf(srcBegin, srcEnd, val);
			if (index >= 0)
			{
				RemoveAt(index);
			}
			else
			{
				break;
			}
		}
	}

	virtual void Add(TParameterType val)
	{
		size_t newSize = Math::GetNewSizeOneAndHalf(mSize, this->mCount + 1);
		Resize(newSize);

		size_t i = 0;
		if (this->mCount > 0)
		{
			i = Algorithm::BinarySearchLastGreaterThan<T, TSorter>(this->mItems, val, 0, this->mCount - 1);
			if (i == -1)	//not found
			{
				i = this->mCount;	//insert at last
			}
			else
			{
				//insert at i
				Memory::SafeCopyShallow(this->mItems + i + 1, (mSize - i - 1), this->mItems + i, (this->mCount - i));
			}
		}
		Memory::CopyConstruct(this->mItems + i, val);
		++this->mCount;

	}
	virtual bool Remove(TParameterType val)
	{
		intp index = IndexOf(0, this->mCount, val);
		if (index >= 0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}

	virtual void Clear()
	{
		Memory::DestoryRange(this->mItems, this->mCount);
		this->mCount = 0;
	}

	virtual void Sort()
	{
		if (!this->IsEmpty())
		{
			Algorithm::InsertSort<T, TSorter>(*this);
		}
	}
#pragma endregion ISortedList interface


public:
	virtual void ReserveSize(size_t size)
	{
		Resize(size);
	}

	virtual void ReleaseExtraSize()
	{
		RETURN_IF_ZERO(mSize);

		if (this->mCount == 0)
		{
			SAFE_FREE(this->mItems);
			mSize = 0;
		}
		else
		{
			RETURN_IF_EQUAL(mSize, this->mCount);
			mSize = this->mCount;
			Memory::Realloc(this->mItems, mSize);
		}
	}

private:
	bool Resize(size_t size)
	{
		//always to extend to bigger size
		RETURN_FALSE_IF(mSize >= size);

		mSize = size;
		Memory::Realloc(this->mItems, size);

		return true;
	}

protected:
	size_t mSize;

};

template<typename T, typename TCompare, typename TSorter >
MEDUSA_WEAK_MULTIPLE_DEFINE const SortedList<T, TCompare, TSorter> SortedList<T, TCompare, TSorter>::Empty;

MEDUSA_END;