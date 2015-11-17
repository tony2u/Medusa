// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Collection/ICollection.h"
#include "Core/Collection/STLPort.h"
#include "Core/Memory/Memory.h"


MEDUSA_BEGIN;

template<typename T, size_t TSize, typename TCompare = EqualCompare<T> >
class Array :public ICollection < T >
{
	typedef Array<T, TSize, TCompare> SelfType;

	typedef IEnumerable<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

public:
	const static size_t Size = TSize;

	Array()
	{
		this->mCount = TSize;
	}

	Array(const Array& items)
	{
		Memory::CopyConstructIterator(mItems, items.Items(), items.Count());
		this->mCount = TSize;
	}

	template<typename T1, size_t TSize1>
	Array(const Array<T1, TSize1>& items)
	{
		static_assert(TSize1 <= TSize, "Too big size");
		Memory::CopyConstructIterator(mItems, items.Items(), items.Count());
	}

	bool operator==(const Array& items)const
	{
		return Memory::Compare<T, TCompare>(mItems, items.Items(), items.Count()) == 0;
	}
	bool operator<(const Array& items)const
	{
		return Memory::Compare<T, TCompare>(mItems, items.Items(), items.Count()) < 0;
	}

	Array& operator=(const Array& items)
	{
		Memory::CopyConstructIterator(mItems, items.Items(), items.Count());
		return *this;
	}

	template<typename T1, size_t TSize1>
	Array& operator=(const Array<T1, TSize1>& items)
	{
		static_assert(TSize1 <= TSize, "Too big size");
		Memory::CopyConstructIterator(mItems, items.Items(), items.Count());
		return *this;
	}

	template<typename T1>
	Array(const ICollection<T1>& items)
	{
		MEDUSA_ASSERT_IF(items.Count() <= TSize, "");
		this->mCount = TSize;

		if (items.IsLinear())
		{
			Memory::CopyConstructIterator(mItems, items.Items(), items.Count());
		}
		else
		{
			size_t index = 0;
			FOR_EACH_COLLECTION(i, items)
			{
				Set(index++, *i);
			}
		}
	}

public:
	TReferenceType operator[](size_t index)
	{
		MEDUSA_ASSERT_IF(index < TSize, "");
		return mItems[index];
	}

	TConstReturnType operator[](size_t index)const
	{
		MEDUSA_ASSERT_IF(index < TSize, "");
		return mItems[index];
	}

	TConstReturnType Get(size_t index)const
	{
		MEDUSA_ASSERT_IF(index < TSize, "");
		return mItems[index];
	}

	void Set(size_t index, TParameterType val)
	{
		MEDUSA_ASSERT_IF(index < TSize, "");
		mItems[index] = val;
	}

#pragma region IEnumerable interface
public:
	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class Array < T, TSize, TCompare > ;
		explicit Enumerator(T* items, size_t size) :mItems(items), mSize(size), mIndex(-1) {}

	public:
		virtual TReturnType Current() { return mItems[mIndex]; }
		virtual TPointerType CurrentPtr() { return mItems + mIndex; }
		TReturnType operator*() { return mItems[mIndex]; }
		TPointerType operator->() { return mItems + mIndex; }


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex < (intp)mSize;
		}
		virtual void Reset() { mIndex = -1; }
	protected:
		T* mItems;
		size_t mSize;
		intp mIndex;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class Array < T, TSize, TCompare > ;
		explicit ConstEnumerator(const T* items, size_t size) :mItems(items), mSize(size), mIndex(-1) {}

	public:
		virtual TConstReturnType Current() { return mItems[mIndex]; }
		virtual TConstPointerType CurrentPtr() { return mItems + mIndex; }

		TConstReturnType operator*() { return mItems[mIndex]; }
		TConstPointerType operator->() { return mItems + mIndex; }


		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex < (intp)mSize;
		}
		virtual void Reset() { mIndex = -1; }
	protected:
		const T* mItems;
		size_t mSize;
		intp mIndex;
	};
public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(mItems, TSize); }
	Enumerator GetEnumerator() { return Enumerator(mItems, TSize); }
protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(mItems, TSize); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(mItems, TSize); }
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
	virtual TConstPointerType Items() const { return (T*)mItems; }
	virtual TPointerType MutableItems() { return (T*)mItems; }

	virtual bool Contains(TParameterType val)const
	{
		return IndexOf(0, TSize - 1, val) >= 0;
	}
	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		MEDUSA_ASSERT(arraySize >= TSize, "TOO_BIG_SIZE");
		Memory::CopyConstructIterator(outArray, mItems, TSize);
		return TSize;
	}



#pragma endregion ICollection interface

public:
	void ClearZero()
	{
		Memory::SetZero(mItems, TSize);
	}

	virtual void Add(TParameterType val)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();
	}
	virtual bool Remove(TParameterType val)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();

		return true;
	}

	virtual void Clear()
	{

	}

	virtual intp IndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd > srcBegin&&srcEnd<TSize, "");

		FOR_EACH_SIZE_BEGIN_END(i, srcBegin, srcEnd)
		{
			if (TCompare::Compare(mItems[i], val) == 0)
			{
				return (intp)i;
			}
		}


		return -1;
	}

	virtual intp LastIndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize, "");

		FOR_EACH_SIZE_END_BEGIN(i, srcEnd - 1, srcBegin - 1)
		{
			if (TCompare::Compare(mItems[i], val) == 0)
			{
				return (intp)i;
			}
		}

		return -1;
	}

	virtual void SetAll(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize, "");

		Memory::Set(mItems + srcBegin, val, srcEnd - srcBegin);
	}

	virtual void SetAll(TParameterType val)
	{
		Memory::Set(mItems, val, TSize);
	}

	virtual void ReplaceAll(size_t srcBegin, size_t srcEnd, TParameterType oldValue, TParameterType newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize, "");

		FOR_EACH_SIZE_BEGIN_END(i, srcBegin, srcEnd)
		{
			if (TCompare::Compare(mItems[i], oldValue) == 0)
			{
				mItems[i] = newValue;
			}
		}
	}



	virtual void ReplaceFirst(size_t srcBegin, size_t srcEnd, TParameterType oldValue, TParameterType newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize, "");

		FOR_EACH_SIZE_BEGIN_END(i, srcBegin, srcEnd)
		{
			if (TCompare::Compare(mItems[i], oldValue) == 0)
			{
				mItems[i] = newValue;
				break;
			}
		}

	}

	virtual void ReplaceLast(size_t srcBegin, size_t srcEnd, TParameterType oldValue, TParameterType newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<TSize, "");

		FOR_EACH_SIZE_END_BEGIN(i, srcEnd - 1, srcBegin - 1)
		{
			if (TCompare::Compare(mItems[i], oldValue) == 0)
			{
				mItems[i] = newValue;
				break;
			}
		}

	}

	virtual void Reverse(size_t srcBegin, size_t srcEnd)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd < TSize, "");

		while (srcBegin < srcEnd)
		{
			TParameterType temp = mItems[srcBegin];
			mItems[srcBegin] = mItems[srcEnd];
			mItems[srcEnd] = temp;
			++srcBegin;
			--srcEnd;
		}
	}

protected:
	T mItems[TSize];

};

MEDUSA_END;