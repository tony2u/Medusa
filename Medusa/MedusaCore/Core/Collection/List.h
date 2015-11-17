// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/IList.h"
#include "Core/Memory/Memory.h"
#include "Core/Collection/STLPort.h"
#include "Core/Algorithm/Algorithm.h"
#include "Core/Math/Math.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;


template<typename T, class TCompare = EqualCompare<T> >
class List :public IList < T >
{
	typedef List<T, TCompare> SelfType;

public:
	using IList<T>::IndexOf;
	using IList<T>::LastIndexOf;
	using IList<T>::First;
	using IList<T>::Last;
	using IList<T>::Reverse;
	using IList<T>::Contains;
	using IList<T>::Push;
	using IList<T>::PushRange;
	using IList<T>::AddRange;
	using IList<T>::Append;
	using IList<T>::AppendRange;
	using IList<T>::RemoveFirst;
	using IList<T>::RemoveLast;
	using IList<T>::RemoveAll;
	using IList<T>::IsEmpty;

	using IList<T>::Count;

	using IList<T>::operator [];


	typedef IList<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

	const static SelfType Empty;
public:
	using IEnumerable<T>::GetEnumeratorVirtual;
public:
	explicit List(size_t size = 0)
	{
		this->mCount = 0;
		mSize = size;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;
	}

	explicit List(const T* items, size_t size)
	{
		this->mCount = size;
		mSize = size;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;
		SetRange(0, items, size);
	}

	explicit List(const T& val, size_t count)
	{
		this->mCount = count;
		mSize = count;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;
		SetAll(val);
	}

	template<typename T1>
	List(const IEnumerable<T1>& items)
	{
		this->mCount = 0;
		mSize = 0;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;

		FOR_EACH_COLLECTION_VIRTUAL(i, items)
		{
			Append(*i);
		}
	}

	template<typename TInterator>
	List(TInterator begin, TInterator end)
	{
		this->mCount = 0;
		mSize = 0;
		this->mItems = nullptr;

		FOR_EACH_COLLECTION_BEGIN_END(i, begin, end)
		{
			Append(*i);
		}
	}

	List(const List& items)
	{
		mSize = items.Count();
		this->mCount = mSize;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;

		Memory::CopyConstructIterator(this->mItems, items.Items(), mSize);
	}

	template<typename T1>
	List(const ICollection<T1>& items)
	{
		mSize = items.Count();
		this->mCount = mSize;
		this->mItems = mSize != 0 ? (T*)malloc(sizeof(T)*mSize) : nullptr;

		if (items.IsLinear())
		{
			Memory::CopyConstructIterator(this->mItems, items.Items(), mSize);
		}
		else
		{
			FOR_EACH_COLLECTION_VIRTUAL(i, items)
			{
				Append(*i);
			}
		}
	}

	List& operator=(const List<T, TCompare>& items)
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
	List& operator=(const List<T1, TCompare1>& items)
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

	virtual ~List(void)
	{
		RETURN_IF_NULL(this->mItems);
		Memory::DestoryRange(this->mItems, this->mCount);
		SAFE_FREE(this->mItems);
	}

	List(List&& other)
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

	List& operator=(List&& other)
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


public:
	size_t Size()const { return mSize; }
	bool IsFull()const { return this->mCount == mSize; }

#pragma region IEnumerable interface
public:
	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class List < T, TCompare >;
		explicit Enumerator(T* items, size_t count) :mItems(items), mCount(count), mIndex(-1) {}

	public:
		virtual TReturnType Current() { return this->mItems[mIndex]; }
		virtual TPointerType CurrentPtr() { return this->mItems + mIndex; }

		TReturnType operator*() { return this->mItems[mIndex]; }
		TPointerType operator->() { return this->mItems + mIndex; }

		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex < (intp)this->mCount;
		}
		virtual void Reset() { mIndex = -1; }
	protected:
		T* mItems;
		size_t mCount;
		intp mIndex;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class List < T, TCompare >;
		explicit ConstEnumerator(const T* items, size_t count) :mItems(items), mCount(count), mIndex(-1) {}

	public:
		virtual TConstReturnType Current() { return this->mItems[mIndex]; }
		virtual TConstPointerType CurrentPtr() { return this->mItems + mIndex; }

		TConstReturnType operator*() { return this->mItems[mIndex]; }
		TConstPointerType operator->() { return this->mItems + mIndex; }

		virtual bool MoveNext()
		{
			++mIndex;
			return mIndex < (intp)this->mCount;
		}
		virtual void Reset() { mIndex = -1; }
	protected:
		const T* mItems;
		size_t mCount;
		intp mIndex;
	};

public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(this->mItems, this->mCount); }
	Enumerator GetEnumerator() { return Enumerator(this->mItems, this->mCount); }
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

protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(this->mItems, this->mCount); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(this->mItems, this->mCount); }


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

#pragma region IList interface

	virtual void SetRange(size_t index, const ICollection<T>& items)
	{
		MEDUSA_ASSERT_IF(index <= this->mCount, "");

		if (items.IsLinear())
		{
			SetRange(index, items.Items(), items.Count());
		}
		else
		{
			size_t count = items.Count();
			size_t newCount = index + count;
			if (newCount > this->mCount)
			{
				size_t j = this->mCount;
				FOR_EACH_COLLECTION_VIRTUAL(i, items)
				{
					if (j == 0)
					{
						Append(*i);
						break;
					}
					else
					{
						--j;
						this->Set(index, *i);
						++index;
					}
				}
			}
			else
			{
				FOR_EACH_COLLECTION_VIRTUAL(i, items)
				{
					this->Set(index, *i);
					++index;
				}
			}
		}
	}

	virtual void SetRange(size_t index, const IList<T>& items)
	{
		SetRange(index, items.Items(), items.Count());
	}

	virtual void SetRange(size_t index, const T* items, size_t count)
	{
		MEDUSA_ASSERT_IF(index <= this->mCount, "");
		size_t newCount = index + count;

		if (newCount > this->mCount)
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, newCount);
			Resize(newSize);
			if (newCount > this->mCount)
			{
				this->mCount = newCount;
			}
		}

		Memory::CopyConstructIterator(this->mItems + index, items, count);
	}

	virtual void SetRange(size_t index, const T& items, size_t count)
	{
		MEDUSA_ASSERT_IF(index <= this->mCount, "");
		size_t newCount = index + count;

		if (newCount > this->mCount)
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, newCount);
			Resize(newSize);
			if (newCount > this->mCount)
			{
				this->mCount = newCount;
			}
		}

		Memory::CopyConstructRange(this->mItems + index, items, count);
	}

	virtual void SetAll(TParameterType val)
	{
		Memory::Set(this->mItems, val, this->mCount);
	}


	virtual intp IndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");
		FOR_EACH_UINT_BEGIN_END(i, srcBegin, srcEnd)
		{
			if (TCompare::Compare(this->mItems[i], val) == 0)
			{
				return (intp)i;
			}
		}

		return -1;
	}


	virtual intp LastIndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");

		FOR_EACH_INT_END_BEGIN(i, (intp)srcEnd - 1, (intp)srcBegin - 1)
		{
			if (TCompare::Compare(this->mItems[i], val) == 0)
			{
				return (intp)i;
			}
		}


		return -1;
	}

	template<typename TOther>
	inline intp IndexOfOther(TOther val)const { return IndexOfOther(0, val); }
	template<typename TOther>
	inline intp IndexOfOther(size_t srcBegin, TOther val)const { if (this->mCount <= 0) { return -1; } return IndexOfOther(srcBegin, this->mCount - 1, val); }

	template<typename TOther>
	inline intp LastIndexOfOther(TOther val)const { return LastIndexOfOther(0, val); }
	template<typename TOther>
	inline intp LastIndexOfOther(size_t srcBegin, TOther val)const { if (this->mCount <= 0) { return -1; } return LastIndexOfOther(srcBegin, this->mCount - 1, val); }

	template<typename TOther>
	intp IndexOfOther(size_t srcBegin, size_t srcEnd, TOther val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");
		FOR_EACH_UINT_BEGIN_END(i, srcBegin, srcEnd)
		{
			if (this->mItems[i] == val)
			{
				return (intp)i;
			}
		}

		return -1;
	}

	template<typename TOther>
	intp LastIndexOfOther(size_t srcBegin, size_t srcEnd, TOther val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");

		FOR_EACH_INT_END_BEGIN(i, (intp)srcEnd - 1, (intp)srcBegin - 1)
		{
			if (this->mItems[i] == val)
			{
				return (intp)i;
			}
		}


		return -1;
	}


	virtual void Reverse(size_t srcBegin, size_t srcEnd)
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");

		while (srcBegin < srcEnd)
		{
			Math::Swap(this->mItems[srcBegin], this->mItems[srcEnd]);
			++srcBegin;
			--srcEnd;
		}
	}

	virtual void Insert(size_t index, TParameterType val, size_t count = 1)
	{
		RETURN_IF_ZERO(count);
		MEDUSA_ASSERT_IF(index < this->mCount + count, "");
		if (this->mCount + count > mSize)
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, this->mCount + count);
			Resize(newSize);
		}


		if (this->mCount > 0 && index != this->mCount)
		{
			Memory::SafeCopyShallow(this->mItems + index + count, mSize - index - count, this->mItems + index, this->mCount - index);
		}

		if (count == 1)
		{
			Memory::CopyConstruct(this->mItems + index, val);
		}
		else
		{
			Memory::CopyConstructRange(this->mItems + index, val, count);
		}
		this->mCount += count;
	}

	virtual void InsertRange(size_t index, const T* items, size_t count)
	{
		RETURN_IF_ZERO(count);
		MEDUSA_ASSERT_IF(index < this->mCount + count, "");

		size_t newSize = Math::GetNewSizeOneAndHalf(mSize, this->mCount + count);
		Resize(newSize);

		if (this->mCount > 0 && index != this->mCount)
		{
			Memory::SafeCopyShallow(this->mItems + index + count, mSize - index - count, this->mItems + index, this->mCount - index);
		}

		Memory::CopyConstructIterator(this->mItems + index, items, count);
		this->mCount += count;
	}

	virtual void InsertRange(size_t index, const IList<T>& items)
	{
		InsertRange(index, items.Items(), items.Count());
	}

	virtual void InsertRange(size_t index, const ICollection<T>& items)
	{
		MEDUSA_ASSERT_IF(index <= this->mCount, "");
		if (items.IsLinear())
		{
			InsertRange(index, items.Items(), items.Count());
		}
		else
		{
			FOR_EACH_COLLECTION_VIRTUAL(i, items)
			{
				Insert(index, *i);
				++index;
			}
		}

	}

	virtual void InsertRange(size_t index, const IEnumerable<T>& items)
	{
		MEDUSA_ASSERT_IF(index <= this->mCount, "");
		FOR_EACH_COLLECTION_VIRTUAL(i, items)
		{
			Insert(index, *i);
			++index;
		}

	}

	virtual void RemoveAt(size_t index)
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		Memory::Destory(this->mItems + index);
		Memory::SafeCopyShallow(this->mItems + index, mSize - index, this->mItems + index + 1, this->mCount - index - 1);
		--this->mCount;
	}


	virtual void RemoveRange(size_t index, size_t count)
	{
		MEDUSA_ASSERT_IF(index + count <= this->mCount, "");
		Memory::DestoryRange(this->mItems + index, count);
		Memory::SafeCopyShallow(this->mItems + index, mSize - index, this->mItems + index + count, this->mCount - index - count);
		this->mCount -= count;
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

	virtual void RemoveAll(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd < this->mCount, "");
		while (true)
		{
			intp index = IndexOf(srcBegin, srcEnd, val);
			if (index >= 0)
			{
				RemoveAt(index);
				srcBegin = index;
				--srcEnd;
			}
			else
			{
				break;
			}
		}
	}
#pragma region Unordered
	virtual void RemoveAtUnordered(size_t index)
	{
		MEDUSA_ASSERT_IF(index < this->mCount, "");
		Memory::Destory(this->mItems + index);
		if (index + 1 < this->mCount)
		{
			Memory::SafeCopyShallow(this->mItems + index, mSize - index, this->mItems + this->mCount - 1, 1);
		}
		--this->mCount;
	}


	virtual void RemoveRangeUnordered(size_t index, size_t count)
	{
		MEDUSA_ASSERT_IF(index + count <= this->mCount, "");
		Memory::DestoryRange(this->mItems + index, count);
		size_t leftCount = this->mCount - index - count;
		size_t leftIndex = index + count;
		if (leftCount > count)
		{
			leftCount = count;
			leftIndex = this->mCount - count;
		}

		Memory::SafeCopyShallow(this->mItems + index, mSize - index, this->mItems + leftIndex, leftCount);
		this->mCount -= count;
	}

	virtual void RemoveAllUnordered(size_t srcBegin, size_t srcEnd, TParameterType val)
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd < this->mCount, "");
		while (true)
		{
			intp index = IndexOf(srcBegin, srcEnd, val);
			if (index >= 0)
			{
				RemoveAtUnordered(index);
				srcBegin = index;
				--srcEnd;
			}
			else
			{
				break;
			}
		}
	}

	virtual bool RemoveUnordered(TParameterType val)
	{
		RETURN_FALSE_IF_ZERO(this->mCount);
		intp index = IndexOf(0, this->mCount - 1, val);
		if (index >= 0)
		{
			RemoveAtUnordered(index);
			return true;
		}
		return false;
	}

#pragma endregion Unordered

	virtual void Add(TParameterType val, size_t count = 1)
	{
		Append(val, count);
	}

	virtual bool Remove(TParameterType val)
	{
		RETURN_FALSE_IF_ZERO(this->mCount);
		intp index = IndexOf(0, this->mCount - 1, val);
		if (index >= 0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}

	virtual void Clear()
	{
		RETURN_IF_ZERO(this->mCount);
		Memory::DestoryRange(this->mItems, this->mCount);
		this->mCount = 0;
	}

	virtual void Sort()
	{
		if (!IsEmpty())
		{
			Algorithm::InsertSortHelper<T, TCompare>(this->mItems, 0, this->mCount - 1);
		}
	}


#pragma endregion IList interface
public:
	template<typename... TArgs>
	void Emplace(TArgs&&... args)
	{
		EmplaceBack(std::forward<TArgs>(args)...);
	}

	template<typename... TArgs>
	void EmplaceBack(TArgs&&... args)
	{
		if (IsFull())
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, mSize + 1);
			Resize(newSize);
		}
		Memory::Construct(this->mItems + this->mCount, std::forward<TArgs>(args)...);
		++this->mCount;
	}

	TReferenceType NewAdd()
	{
		if (IsFull())
		{
			size_t newSize = Math::GetNewSizeOneAndHalf(mSize, mSize + 1);
			Resize(newSize);
		}

		Memory::Construct(this->mItems + this->mCount);
		return this->mItems[this->mCount++];
	}

	bool Offset(size_t originalIndex, intp offset)
	{
		RETURN_FALSE_IF(originalIndex >= this->mCount);
		if (offset == 0)
		{
			return true;
		}
		else
		{
			byte itemMemory[sizeof(T)];
			Memory::SafeCopyShallow((T*)itemMemory, 1, this->mItems + originalIndex, 1);

			if (offset > 0)
			{
				size_t maxOffset = this->mCount - 1 - originalIndex;
				RETURN_FALSE_IF((size_t)offset > maxOffset);
				if (offset == 1)
				{
					Memory::SafeCopyShallowOne(this->mItems + originalIndex, this->mItems + originalIndex + offset);
				}
				else
				{
					Memory::SafeCopyShallow(this->mItems + originalIndex, this->mCount - originalIndex, this->mItems + originalIndex + 1, offset);
				}

			}
			else
			{
				RETURN_FALSE_IF(originalIndex + offset < 0);
				if (offset == -1)
				{
					Memory::SafeCopyShallowOne(this->mItems + originalIndex, this->mItems + originalIndex + offset);
				}
				else
				{
					Memory::SafeCopyShallow(this->mItems + originalIndex + offset + 1, this->mCount - originalIndex - offset, this->mItems + originalIndex + offset, -offset);
				}
			}
			Memory::SafeCopyShallowOne(this->mItems + originalIndex + offset, (T*)itemMemory);
		}

		return true;
	}

	template<typename TInterator>
	void AddRange(TInterator begin, TInterator end)
	{
		FOR_EACH_COLLECTION_BEGIN_END(i, begin, end)
		{
			Add(*i);
		}
	}

	void PushRange(const IList<T>& items) { InsertRange(0, items); }

	template<typename TInterator>
	void PushRange(TInterator begin, TInterator end)
	{
		FOR_EACH_COLLECTION_BEGIN_END(i, begin, end)
		{
			Push(*i);
		}
	}

	void AppendRange(const IList<T>& items) { InsertRange(this->mCount, items); }

	template<typename TInterator>
	void AppendRange(TInterator begin, TInterator end)
	{
		FOR_EACH_COLLECTION_BEGIN_END(i, begin, end)
		{
			Append(*i);
		}
	}


	template<size_t size>
	void AppendRange(const T(&items)[size])
	{
		AppendRange(items, size);
	}

	void AppendRange(const T* items, size_t count)
	{
		size_t newSize = Math::GetNewSizeOneAndHalf(mSize, this->mCount + count);
		Resize(newSize);

		Memory::CopyConstructIterator(this->mItems + this->mCount, items, count);
		this->mCount += count;
	}

	void Merge(const List<T>& items)
	{
		FOR_EACH_COLLECTION(i, items)
		{
			if (!Contains(*i))
			{
				Add(*i);
			}
		}
	}

	void Merge(const IList<T>& items)
	{
		FOR_EACH_COLLECTION_VIRTUAL(i, items)
		{
			if (!Contains(*i))
			{
				Add(*i);
			}
		}
	}

	void ForceReserveCount(size_t newCount)
	{
		ReserveSize(newCount);
		ForceSetCount(newCount);
		ForceConstructAll();
	}

	void ForceSetCount(size_t newCount)
	{
		MEDUSA_ASSERT_IF(newCount <= mSize, "");
		this->mCount = newCount;
	}

	void ForceConstructAll()
	{
		Memory::ConstructRange(this->mItems, this->mCount);
	}

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

	MemoryData<T> ToData()const { return MemoryData<T>::FromStatic(this->mItems, this->mCount); }
private:
	bool Resize(size_t size)
	{
		//always to extend to bigger size
		RETURN_FALSE_IF(mSize >= size);
		Memory::Realloc(this->mItems, size);
		mSize = size;
		return true;
	}

protected:
	size_t mSize = 0;

};

template<typename T, class TCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const List<T, TCompare> List<T, TCompare>::Empty;

MEDUSA_END;