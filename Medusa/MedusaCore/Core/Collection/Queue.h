// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/ICollection.h"
#include "Core/Collection/STLPort.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/Math.h"

MEDUSA_BEGIN;



template<typename T, class TCompare = EqualCompare >
class Queue :public ICollection < T >
{
	typedef Queue<T, TCompare> SelfType;

public:
	using IEnumerable<T>::GetEnumeratorVirtual;
	using  ICollection<T>::IsEmpty;
	using  ICollection<T>::ByteSize;

	typedef ICollection<T> BaseType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TParameterType TParameterType;

	const static SelfType Empty;
public:
	explicit Queue(size_t size = 0)
	{
		this->mCount = 0;
		mSize = size;
		mHead = -1;
		mTail = -1;
		mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;
	}

	virtual ~Queue(void)
	{
		Memory::DestoryRange(mItems, this->mCount);
		SAFE_FREE(mItems);
	}

	Queue(const Queue& other)
		:mSize(other.mCount),
		mItems(other.mCount != 0 ? (T*)malloc(sizeof(T)*other.mCount) : nullptr),
		mHead(other.mCount != 0 ? 0 : -1),
		mTail(other.mCount != 0 ? other.mCount - 1 : -1)
	{
		this->mCount = other.mCount;
		Memory::SafeCopy(mItems, mSize, other.mItems, other.mCount);
	}

	Queue& operator=(const Queue& other)
	{
		Clear();
		if (!other.IsEmpty())
		{
			Resize(other.mSize);
			mHead = 0;
			mTail = other.mCount - 1;
			Memory::SafeCopy(mItems, mSize, other.mItems, other.mCount);
		}
		else
		{
			SAFE_FREE(mItems);
		}

		return *this;
	}


	Queue(Queue&& other)
		:mSize(other.mSize),
		mItems(other.mItems),
		mHead(other.mHead),
		mTail(other.mTail)
	{
		if (this != &other)
		{
			this->mCount = other.mCount;
			other.mItems = nullptr;
			other.mSize = 0;
			other.mCount = 0;
			other.mHead = 0;
			other.mTail = 0;
		}
	}

	Queue& operator=(Queue&& other)
	{
		if (this != &other)
		{
			Clear();
			SAFE_FREE(this->mItems);
			this->mSize = other.mSize;
			this->mItems = other.mItems;
			this->mCount = other.mCount;
			this->mHead = other.mHead;
			this->mTail = other.mTail;

			other.mItems = nullptr;
			other.mSize = 0;
			other.mCount = 0;
			other.mHead = 0;
			other.mTail = 0;
		}
		return *this;
	}
public:
	size_t Size()const { return mSize; }
	bool IsFull()const { return this->mCount == mSize; }

#pragma region IEnumerable interface
public:
	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class Queue < T, TCompare >;
		explicit Enumerator(T* items, size_t size, size_t head, size_t tail, size_t count) :mItems(items), mSize(size), mHead(head), mTail(tail), mIndex(head - 1), mCount(count), mEnumCount(count) {}

	public:
		virtual TReturnType Current() { return mItems[mIndex]; }
		virtual TPointerType CurrentPtr() { return mItems + mIndex; }

		TReturnType operator*() { return mItems[mIndex]; }
		TPointerType operator->() { return mItems + mIndex; }

		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_ZERO(this->mCount);
			RETURN_FALSE_IF_ZERO(mEnumCount);

			mIndex = (mIndex + 1) % mSize;
			--mEnumCount;

			if (mHead <= mTail)
			{
				return mIndex >= mHead&&mIndex <= mTail;
			}
			else
			{
				return (mIndex >= mHead&&mIndex < (intp)mSize) || (mIndex >= 0 && mIndex <= mTail);
			}
		}
		virtual void Reset() { mIndex = mHead - 1; mEnumCount = this->mCount; }
	protected:
		T* mItems;
		size_t mSize;

		intp mHead;
		intp mTail;

		intp mIndex;
		size_t mCount;
		size_t mEnumCount;

	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class Queue < T, TCompare >;
		explicit ConstEnumerator(const T* items, size_t size, intp head, intp tail, size_t count) :mItems(items), mSize(size), mHead(head), mTail(tail), mIndex(head - 1), mCount(count), mEnumCount(count) {}

	public:
		virtual TConstReturnType Current() { return mItems[mIndex]; }
		virtual TConstPointerType CurrentPtr() { return mItems + mIndex; }

		TConstReturnType operator*() { return mItems[mIndex]; }
		TConstPointerType operator->() { return mItems + mIndex; }

		virtual bool MoveNext()
		{
			RETURN_FALSE_IF_ZERO(this->mCount);
			RETURN_FALSE_IF_ZERO(mEnumCount);

			mIndex = (mIndex + 1) % mSize;
			--mEnumCount;

			if (mHead <= mTail)
			{
				return mIndex >= mHead&&mIndex <= mTail;
			}
			else
			{
				return (mIndex >= mHead&&mIndex < (intp)mSize) || (mIndex >= 0 && mIndex <= mTail);
			}
		}
		virtual void Reset() { mIndex = mHead - 1; mEnumCount = this->mCount; }
	protected:
		const T* mItems;
		size_t mSize;

		intp mHead;
		intp mTail;

		intp mIndex;
		size_t mCount;
		size_t mEnumCount;
	};
public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(mItems, mSize, mHead, mTail, this->mCount); }
	Enumerator GetEnumerator() { return Enumerator(mItems, mSize, mHead, mTail, this->mCount); }
protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(mItems, mSize, mHead, mTail, this->mCount); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(mItems, mSize, mHead, mTail, this->mCount); }

public:
	class ConstInterator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit ConstInterator(const T* begin, const T* end, intp index) :mCurrent(begin), mBegin(begin), mEnd(end), mIndex(index) {}
		TConstReturnType operator*()const { return *mCurrent; }
		TConstPointerType operator->()const { return mCurrent; }
		bool operator==(const ConstInterator& other)const { return mIndex == other.mIndex; }
		bool operator!=(const ConstInterator& other)const { return mIndex != other.mIndex; }
		ConstInterator& operator++()
		{
			++mIndex;
			mCurrent = (mCurrent == mEnd) ? mBegin : mCurrent + 1;
			return *this;
		}
		ConstInterator operator++(int)const
		{
			const T* cur = (mCurrent == mEnd) ? mBegin : mCurrent + 1;
			return ConstInterator(cur, mBegin, mEnd, mIndex + 1);
		}
		ConstInterator& operator--()
		{
			--mIndex;
			mCurrent = (mCurrent == mBegin) ? mEnd : mCurrent - 1;
			return *this;
		}
		ConstInterator operator--(int)const
		{
			const T* cur = (mCurrent == mBegin) ? mEnd : mCurrent - 1;
			return ConstInterator(cur, mBegin, mEnd, mIndex - 1);
		}
	protected:
		const T* mCurrent;
		const T* mBegin;
		const T* mEnd;
		intp mIndex;
	};

	class Interator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit Interator(T* begin, T* end, intp index) :mCurrent(begin), mBegin(begin), mEnd(end), mIndex(index) {}
		TReturnType operator*()const { return *mCurrent; }
		TPointerType operator->()const { return mCurrent; }
		bool operator==(const Interator& other)const { return mIndex == other.mIndex; }
		bool operator!=(const Interator& other)const { return mIndex != other.mIndex; }
		Interator& operator++()
		{
			++mIndex;
			mCurrent = (mCurrent == mEnd) ? mBegin : mCurrent + 1;
			return *this;
		}
		Interator operator++(int)const
		{
			T* cur = (mCurrent == mEnd) ? mBegin : mCurrent + 1;
			return Interator(cur, mBegin, mEnd, mIndex + 1);
		}
		Interator& operator--()
		{
			--mIndex;
			mCurrent = (mCurrent == mBegin) ? mEnd : mCurrent - 1;
			return *this;
		}
		Interator operator--(int)const
		{
			T* cur = (mCurrent == mBegin) ? mEnd : mCurrent - 1;
			return Interator(cur, mBegin, mEnd, mIndex - 1);
		}
	protected:
		T* mCurrent;
		T* mBegin;
		T* mEnd;
		intp mIndex;
	};

	ConstInterator begin()const { return ConstInterator(this->mItems + mHead, this->mItems + mTail, 0); }
	ConstInterator end()const { return ConstInterator(this->mItems + mHead, this->mItems + mTail, this->mCount); }
	Interator begin() { return Interator(this->mItems + mHead, this->mItems + mTail, 0); }
	Interator end() { return Interator(this->mItems + mHead, this->mItems + mTail, this->mCount); }
#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:
	virtual size_t Count() const { return this->mCount; }
	virtual bool IsLinear() const { return true; }
	virtual TConstPointerType Items() const { return mItems; }
	virtual TPointerType MutableItems() { return mItems; }


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		MEDUSA_ASSERT_NOT_NULL(outArray, "null parameter");
		MEDUSA_ASSERT_NOT_ZERO(arraySize, "arraySize==0");
		RETURN_ZERO_IF_ZERO(this->mCount);


		if (mHead <= mTail)
		{
			size_t count = Math::Min(this->mCount, arraySize);
			Memory::SafeCopy(outArray, arraySize, mItems + mHead, this->mCount);
			return count;
		}
		else
		{
			size_t tailSize = mTail + 1;
			size_t count = Math::Min(tailSize, arraySize);
			Memory::SafeCopy(outArray, arraySize, mItems, count);
			RETURN_OBJECT_IF_ZERO(count, tailSize);
			arraySize -= tailSize;
			count = Math::Min((size_t)(mSize - mHead), arraySize);
			Memory::SafeCopy(outArray + tailSize, arraySize, mItems + mHead, count);
			return tailSize + count;
		}
	}

	virtual bool Contains(TParameterType val)const
	{
		size_t index = mHead;
		size_t num2 = this->mCount;
		while (num2-- > 0)
		{
			if (mItems[index] == val)
			{
				return true;
			}
			index = (index + 1) % mSize;
		}
		return false;
	}

#pragma endregion ICollection interface
	void Clear()
	{
		if (mHead <= mTail)
		{
			Memory::DestoryRange(mItems + mHead, mTail - mHead);
		}
		else
		{
			Memory::DestoryRange(mItems, mTail + 1);
			Memory::DestoryRange(mItems + mHead, mSize - mHead);
		}

		this->mCount = 0;
		mHead = -1;
		mTail = -1;
	}

	void Pop()
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount, "Empty");
		Memory::Destory(mItems + mHead);
		mHead = (mHead + 1) % mSize;
		this->mCount--;
	}

	void Push(TParameterType val)
	{
		if (IsFull())
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, this->mCount + 1);
			Resize(newSize);
		}

		if (this->mCount == 0)
		{
			mHead = 0;
			mTail = 0;
		}
		else
		{
			mTail = (mTail + 1) % mSize;
		}
		Memory::CopyConstruct(mItems + mTail, val);

		this->mCount++;
	}

	bool Remove(TParameterType val)
	{
		int index = IndexOf(val);
		if (index < 0)
		{
			return false;
		}

		if (mHead <= mTail)
		{
			Memory::SafeCopyShallow(mItems + index, mTail - index + 1, mItems + index + 1, mTail - index);
			mTail = (mTail - 1) % mSize;
			--this->mCount;
		}
		else
		{
			if (index >= mHead&&index < (intp)mSize)
			{
				Memory::SafeCopyShallow(mItems + index, mSize - index + 1, mItems + index + 1, mSize - index);
				Memory::SafeCopyShallow(mItems, mTail - index + 1, mItems + 1, mTail - index);
				mTail = (mTail - 1) % mSize;
				--this->mCount;
			}
		}

		return true;

	}


	int IndexOf(TParameterType val)const
	{
		if (this->mCount == 0)
		{
			return -1;
		}

		int index = mHead%mSize;
		int count = this->mCount;
		if (mHead <= mTail)
		{
			while (count > 0 && index >= mHead&&index <= mTail)
			{
				if (mItems[index] == val)
				{
					return index;
				}
				index = (index + 1) % mSize;
				--count;
			}
		}
		else
		{
			while (count > 0 && ((index >= mHead&&index < (intp)mSize) || (index >= 0 && index <= mTail)))
			{
				if (mItems[index] == val)
				{
					return index;
				}
				index = (index + 1) % mSize;
				--count;
			}
		}

		return -1;
	}

	TConstReturnType Top()const
	{
		return Head();
	}
	TConstReturnType Head()const
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount, "Empty");
		return mItems[mHead];
	}

	TReturnType Top()
	{
		return Head();
	}
	TReturnType Head()
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount, "Empty");
		return mItems[mHead];
	}

	TConstReturnType Tail()const
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount, "Empty");
		intp tailIndex = (mTail + mSize - 1) % mSize;
		return mItems[tailIndex];
	}

	TReturnType Tail()
	{
		MEDUSA_ASSERT_NOT_ZERO(this->mCount, "Empty");
		intp tailIndex = (mTail + mSize - 1) % mSize;
		return mItems[tailIndex];
	}
	TReturnType PopWithReturn()
	{
		TReturnType var = Head();
		Pop();
		return var;
	}

public:
	virtual void ReserveSize(size_t size)
	{
		Resize(size);
	}
private:
	bool Resize(size_t size)
	{
		//always to extend to bigger size
		RETURN_FALSE_IF(mSize >= size);

		if (mHead <= mTail)
		{
			Memory::Realloc(mItems, mSize, size);
			mSize = size;
		}
		else
		{
			mSize = size;
			T* tempItems = (T*)malloc(mSize*sizeof(T));
			size_t lastCount = this->mCount - mHead;
			Memory::SafeCopyShallow(tempItems, mSize*sizeof(T), mItems + mHead, lastCount);
			Memory::SafeCopyShallow(tempItems + lastCount, (mSize - lastCount)*sizeof(T), mItems, mTail + 1);
			SAFE_FREE(mItems);
			mItems = tempItems;
			mHead = 0;
			mTail = this->mCount - 1;
		}

		return true;
	}



protected:
	T* mItems = nullptr;
	size_t mSize = 0;

	intp mHead = -1;	//pointer to first element
	intp mTail = -1;	//pointer to last element

};


template<typename T, class TCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const Queue<T, TCompare> Queue<T, TCompare>::Empty;

MEDUSA_END;