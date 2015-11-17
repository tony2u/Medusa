// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/ICollection.h"
#include "Core/Collection/List.h"

#include "Core/Collection/STLPort.h"

MEDUSA_BEGIN;


template<typename T, class TCompare = EqualCompare<T>, class TSorter = DefaultCompare<T>>
class PriorityQueue :public ICollection < T >
{
	typedef PriorityQueue<T, TCompare, TSorter> SelfType;
	typedef List<T, TCompare> ContainerType;
public:

	typedef ICollection<T> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

	using IEnumerable<T>::GetEnumeratorVirtual;
	using  ICollection<T>::IsEmpty;
	using  ICollection<T>::ByteSize;
	const static SelfType Empty;
public:
	explicit PriorityQueue(size_t size = 0) :mItems(size)
	{

	}

	explicit PriorityQueue(const T* item, size_t size) :mItems(item, size)
	{
		BuildHeap();
	}

	template<typename T1>
	PriorityQueue(const IEnumerable<T1>& items) : mItems(items)
	{
		this->mCount = mItems.Count();
	}

	PriorityQueue(const PriorityQueue& items) :mItems(items)
	{
		this->mCount = mItems.Count();
	}

	PriorityQueue& operator=(const PriorityQueue& items)
	{
		mItems = items;
		this->mCount = mItems.Count();
		return *this;
	}

	PriorityQueue(PriorityQueue&& items) 
		:mItems(std::move(items))
	{
		this->mCount = items.mCount;
	}

	PriorityQueue& operator=(PriorityQueue&& items)
	{
		if (this != &items)
		{
			mItems = std::move(items);
			this->mCount = items.Count();
		}
		return *this;
	}


	template<typename T1>
	PriorityQueue(const ICollection<T1>& items) : mItems(items)
	{
		this->mCount = mItems.Count();
	}

	template<typename T1>
	PriorityQueue& operator=(const PriorityQueue<T1>& items)
	{
		mItems = items;
		this->mCount = mItems.Count();
		return *this;
	}

	virtual ~PriorityQueue(void)
	{

	}
public:
	size_t Size()const { return mItems.Size(); }
	bool IsFull()const { return mItems.IsFull(); }

#pragma region IEnumerable interface
public:
	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class PriorityQueue < T, TCompare, TSorter >;
		explicit Enumerator(T* items, size_t count) :mItems(items), mCount(count), mIndex(count) {}

	public:
		virtual TReturnType Current() { return mItems[mIndex]; }
		virtual TPointerType CurrentPtr() { return this->mItems + mIndex; }

		TReturnType operator*() { return mItems[mIndex]; }
		TPointerType operator->() { return this->mItems + mIndex; }

		virtual bool MoveNext()
		{
			--mIndex;
			return mIndex >= 0;
		}
		virtual void Reset() { mIndex = this->mCount; }
	protected:
		T* mItems;
		size_t mCount;
		intp mIndex;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class PriorityQueue < T, TCompare,TSorter > ;
		explicit ConstEnumerator(const T* items, size_t count) :mItems(items), mCount(count), mIndex(count) {}

	public:
		virtual TConstReturnType Current() { return mItems[mIndex]; }
		virtual TConstPointerType CurrentPtr() { return mItems + mIndex; }

		TConstReturnType operator*() { return mItems[mIndex]; }
		TConstPointerType operator->() { return mItems + mIndex; }

		virtual bool MoveNext()
		{
			--mIndex;
			return mIndex >= 0;
		}
		virtual void Reset() { mIndex = this->mCount; }
	protected:
		const T* mItems;
		size_t mCount;
		intp mIndex;
	};
public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(mItems.Items(), mItems.Count()); }
	Enumerator GetEnumerator() { return Enumerator(mItems.MutableItems(), mItems.Count()); }
protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(mItems.Items(), mItems.Count()); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(mItems.MutableItems(), mItems.Count()); }
public:
	class ConstInterator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit ConstInterator(const T* cur) :mCurrent(cur) {}
		TConstReturnType operator*()const { return *mCurrent; }
		TConstPointerType operator->()const { return mCurrent; }
		bool operator==(const ConstInterator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const ConstInterator& other)const { return mCurrent != other.mCurrent; }
		ConstInterator& operator++() { --mCurrent; return *this; }
		ConstInterator operator++(int)const { return ConstInterator(mCurrent - 1); }
		ConstInterator& operator--() { ++mCurrent; return *this; }
		ConstInterator operator--(int)const { return ConstInterator(mCurrent + 1); }
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
		Interator& operator++() { --mCurrent; return *this; }
		Interator operator++(int)const { return Interator(mCurrent - 1); }
		Interator& operator--() { ++mCurrent; return *this; }
		Interator operator--(int)const { return Interator(mCurrent + 1); }
	protected:
		T* mCurrent;
	};
	ConstInterator begin()const { return ConstInterator(this->mItems.Items() + mItems.Count() - 1); }
	ConstInterator end()const { return ConstInterator(this->mItems.Items() - 1); }
	Interator begin() { return Interator(this->mItems.MutableItems() + mItems.Count() - 1); }
	Interator end() { return Interator(this->mItems.MutableItems() - 1); }

#pragma endregion IEnumerable interface


#pragma region ICollection interface
public:

	virtual bool IsLinear() const { return mItems.IsLinear(); }
	virtual TConstPointerType Items() const { return mItems.Items(); }
	virtual TPointerType MutableItems() { return mItems.MutableItems(); }


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		return mItems.CopyTo(outArray, arraySize);
	}

	void Clear()
	{
		mItems.Clear();
		this->mCount = 0;
	}

	virtual bool Contains(TParameterType val)const { return mItems.Contains(val); }

	bool Remove(TParameterType val)
	{
		intp index = IndexOf(val);
		if (index >= 0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}
	void RemoveAt(size_t index)
	{
		mItems[index] = mItems.Last();
		Pop();
	}

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


#pragma endregion ICollection interface

	void Push(TParameterType val)
	{
		mItems.Append(val);
		this->mCount = mItems.Count();
		HeapifyUp(this->mCount - 1);
	}

	TReferenceType Pop()
	{
		MEDUSA_ASSERT_NOT_EMPTY(mItems, "Empty");
		std::swap(mItems[0], mItems[this->mCount - 1]);
		TReferenceType last = mItems.Last();
		mItems.RemoveLast();
		this->mCount = mItems.Count();
		HeapifyDown(0);
		return last;
	}

	TConstReturnType Top()const
	{
		return mItems.First();
	}

	TReferenceType PopOr(TParameterType val)
	{
		if (mItems.IsEmpty())
		{
			return val;
		}
		return Pop();
	}

	TReferenceType TopOr(TParameterType val)const
	{
		if (mItems.IsEmpty())
		{
			return val;
		}
		return mItems.First();
	}

	static PriorityQueue* New(TParameterType p1)
	{
		PriorityQueue* stack = new PriorityQueue();
		stack->Push(p1);
		return stack;
	}



	inline intp IndexOf(TParameterType val)const { return mItems.IndexOf(val); }
	inline intp IndexOf(size_t srcBegin, TParameterType val)const { return mItems.IndexOf(srcBegin, val); }

	inline intp LastIndexOf(TParameterType val)const { return mItems.LastIndexOf(val); }
	inline intp LastIndexOf(size_t srcBegin, TParameterType val)const { return mItems.LastIndexOf(srcBegin, val); }

	intp IndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const { return mItems.IndexOf(srcBegin, srcEnd, val); }
	intp LastIndexOf(size_t srcBegin, size_t srcEnd, TParameterType val)const { return mItems.LastIndexOf(srcBegin, srcEnd, val); }


	template<typename TOther>
	inline intp IndexOfOther(TOther val)const { return mItems.IndexOfOther(val); }
	template<typename TOther>
	inline intp IndexOfOther(size_t srcBegin, TOther val)const { return mItems.IndexOfOther(srcBegin, val); }

	template<typename TOther>
	inline intp LastIndexOfOther(TOther val)const { return mItems.LastIndexOfOther(val); }
	template<typename TOther>
	inline intp LastIndexOfOther(size_t srcBegin, TOther val)const { return mItems.LastIndexOfOther(srcBegin, val); }

	template<typename TOther>
	intp IndexOfOther(size_t srcBegin, size_t srcEnd, TOther val)const { return mItems.IndexOfOther(srcBegin, srcEnd, val); }
	template<typename TOther>
	intp LastIndexOfOther(size_t srcBegin, size_t srcEnd, TOther val)const { return mItems.LastIndexOfOther(srcBegin, srcEnd, val); }

	void HeapifyUp(size_t index)
	{
		size_t parent = GetParent(index);

		while (index > 0 && TSorter::Compare(mItems[parent], mItems[index]) > 0)
		{
			std::swap(mItems[index], mItems[parent]);
			index = parent;
			parent = GetParent(index);
		}
	}

	void HeapifyDown(size_t index)
	{
		size_t left = GetLeftChild(index);
		size_t right = GetRightChild(index);
		size_t smallest = index;

		if (left < mItems.Count())
		{
			if (TSorter::Compare(mItems[left], mItems[index]) < 0)
			{
				smallest = left;
			}
		}

		if (right < mItems.Count())
		{
			if (TSorter::Compare(mItems[right], mItems[smallest]) < 0)
			{
				smallest = right;
			}
		}

		if (smallest != index)
		{
			std::swap(mItems[index], mItems[smallest]);
			HeapifyDown(smallest);
		}
	}

	void BuildHeap()
	{
		int count = (int)this->Count;
		RETURN_IF(count < 2);
		for (int i = count / 2 - 1; i >= 0; i--)
		{
			HeapifyDown(i, count);
		}
	}
protected:
	static size_t GetParent(size_t index)
	{
		return (index - 1) / 2;
	}

	static size_t GetLeftChild(size_t index)
	{
		return index * 2 + 1;
	}

	static size_t GetRightChild(size_t index)
	{
		return index * 2 + 2;
	}


protected:
	ContainerType mItems;
};

template<typename T, class TCompare,typename TSorter>
MEDUSA_WEAK_MULTIPLE_DEFINE const PriorityQueue<T, TCompare, TSorter> PriorityQueue<T, TCompare, TSorter>::Empty;

MEDUSA_END;