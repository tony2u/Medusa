// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Collection/ICollection.h"
#include "Core/Collection/List.h"
#include "Core/Collection/STLPort.h"
#include "Core/Collection/KeyValuePair.h"

MEDUSA_BEGIN;


template<typename TKey, typename TValue, typename TKeyCompare = EqualCompare, typename TValueCompare = EqualCompare>
class PriorityDictionary :public ICollection < KeyValuePair<TKey, TValue> >
{
public:
	typedef KeyValuePair<TKey, TValue> ItemType;
	typedef PriorityDictionary<TKey, TValue, TKeyCompare,TValueCompare> SelfType;
	typedef List<ItemType, NoCompare> ContainerType;
public:
	typedef ICollection<ItemType> BaseType;
	typedef typename BaseType::TConstPointerType TConstPointerType;
	typedef typename BaseType::TPointerType TPointerType;
	typedef typename BaseType::TParameterType TParameterType;
	typedef typename BaseType::TReturnType TReturnType;
	typedef typename BaseType::TConstReturnType TConstReturnType;
	typedef typename BaseType::TReferenceType TReferenceType;

	typedef typename Compile::TypeTraits<TValue>::ReferenceType TValueReferenceType;
	typedef typename Compile::TypeTraits<TValue>::ConstReturnType TValueConstReturnType;

	typedef typename Compile::TypeTraits<TValue>::PointerType TValuePointerType;
	typedef typename Compile::TypeTraits<TValue>::ConstPointerType TValueConstPointerType;

	typedef typename Compile::TypeTraits<TKey>::ParameterType TKeyParameterType;
	typedef typename Compile::TypeTraits<TValue>::ParameterType TValueParameterType;

	typedef typename Compile::TypeTraits<TKey>::ReferenceType TKeyReferenceType;
	typedef typename Compile::TypeTraits<TKey>::PointerType TKeyPointerType;
	typedef typename Compile::TypeTraits<TKey>::ConstPointerType TKeyConstPointerType;
	typedef typename Compile::TypeTraits<TKey>::ConstReturnType TKeyConstReturnType;

	using IEnumerable<ItemType>::GetEnumeratorVirtual;
	using  ICollection<ItemType>::IsEmpty;
	using  ICollection<ItemType>::ByteSize;
	const static SelfType Empty;
public:
	explicit PriorityDictionary(size_t size = 0) :mItems(size)
	{

	}

	explicit PriorityDictionary(const TValue* item, size_t size) :mItems(item, size)
	{
		BuildHeap();
	}

	template<typename T1>
	PriorityDictionary(const IEnumerable<T1>& items) : mItems(items)
	{
		this->mCount = mItems.Count();
	}

	PriorityDictionary(const PriorityDictionary& items) :mItems(items)
	{
		this->mCount = mItems.Count();
	}

	PriorityDictionary& operator=(const PriorityDictionary& items)
	{
		mItems = items;
		this->mCount = mItems.Count();
		return *this;
	}

	PriorityDictionary(PriorityDictionary&& items)
		:mItems(std::move(items))
	{
		this->mCount = items.mCount;
	}

	PriorityDictionary& operator=(PriorityDictionary&& items)
	{
		if (this != &items)
		{
			mItems = std::move(items);
			this->mCount = items.Count();
		}
		return *this;
	}

	template<typename T1>
	PriorityDictionary(const ICollection<T1>& items) : mItems(items)
	{
		this->mCount = mItems.Count();
	}

	template<typename T1>
	PriorityDictionary& operator=(const PriorityDictionary<TKey, T1>& items)
	{
		mItems = items;
		this->mCount = mItems.Count();
		return *this;
	}

	virtual ~PriorityDictionary(void)
	{

	}
public:
	size_t Size()const { return mItems.Size(); }
	bool IsFull()const { return mItems.IsFull(); }

#pragma region IEnumerable interface
public:
	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class PriorityDictionary <TKey, TValue,TKeyCompare,TValueCompare >;
		explicit Enumerator(ItemType* items, size_t count) :mItems(items), mCount(count), mIndex(count) {}

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
		ItemType* mItems;
		size_t mCount;
		intp mIndex;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
		friend class PriorityDictionary <TKey, TValue, TKeyCompare, TValueCompare >;
		explicit ConstEnumerator(const ItemType* items, size_t count) :mItems(items), mCount(count), mIndex(count) {}

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
		const ItemType* mItems;
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
		explicit ConstInterator(const ItemType* cur) :mCurrent(cur) {}
		TConstReturnType operator*()const { return *mCurrent; }
		TConstPointerType operator->()const { return mCurrent; }
		bool operator==(const ConstInterator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const ConstInterator& other)const { return mCurrent != other.mCurrent; }
		ConstInterator& operator++() { --mCurrent; return *this; }
		ConstInterator operator++(int)const { return ConstInterator(mCurrent - 1); }
		ConstInterator& operator--() { ++mCurrent; return *this; }
		ConstInterator operator--(int)const { return ConstInterator(mCurrent + 1); }
	protected:
		const ItemType* mCurrent;
	};

	class Interator	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit Interator(ItemType* cur) :mCurrent(cur) {}
		TReturnType operator*()const { return *mCurrent; }
		TPointerType operator->()const { return mCurrent; }
		bool operator==(const Interator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const Interator& other)const { return mCurrent != other.mCurrent; }
		Interator& operator++() { --mCurrent; return *this; }
		Interator operator++(int)const { return Interator(mCurrent - 1); }
		Interator& operator--() { ++mCurrent; return *this; }
		Interator operator--(int)const { return Interator(mCurrent + 1); }
	protected:
		ItemType* mCurrent;
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


	virtual size_t CopyTo(ItemType* outArray, size_t arraySize)const
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

	void Push(TKeyParameterType key,TValueParameterType val)
	{
		Push(ItemType(key, val));
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

	static PriorityDictionary* New(TParameterType p1)
	{
		PriorityDictionary* stack = new PriorityDictionary();
		stack->Push(p1);
		return stack;
	}

	inline intp IndexOfValue(TValueParameterType val)const { return IndexOfValue(0, val); }
	inline intp IndexOfValue(size_t srcBegin, TValueParameterType val)const { if (this->mCount <= 0) { return -1; } return IndexOfValue(srcBegin, this->mCount - 1, val); }

	inline intp LastIndexOfValue(TValueParameterType val)const { return LastIndexOfValue(0, val); }
	inline intp LastIndexOfValue(size_t srcBegin, TValueParameterType val)const { if (this->mCount <= 0) { return -1; } return LastIndexOfValue(srcBegin, this->mCount - 1, val); }

	virtual intp IndexOfValue(size_t srcBegin, size_t srcEnd, TValueParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");
		FOR_EACH_UINT_BEGIN_END(i, srcBegin, srcEnd)
		{
			if (TValueCompare::Compare(this->mItems[i].Value, val) == 0)
			{
				return (intp)i;
			}
		}

		return -1;
	}


	virtual intp LastIndexOfValue(size_t srcBegin, size_t srcEnd, TValueParameterType val)const
	{
		MEDUSA_ASSERT_IF(srcEnd >= srcBegin&&srcEnd <= this->mCount, "");

		FOR_EACH_INT_END_BEGIN(i, (intp)srcEnd - 1, (intp)srcBegin - 1)
		{
			if (TValueCompare::Compare(this->mItems[i].Value, val) == 0)
			{
				return (intp)i;
			}
		}
		return -1;
	}

	

	void Update(size_t index,TKeyParameterType newKey)
	{
		TKeyReferenceType originalKey= mItems[index].Key;
		int result = TKeyCompare::Compare(originalKey, newKey);
		RETURN_IF_ZERO(result);
		originalKey = newKey;
		if (result<0)
		{
			//grow
			HeapifyDown(index);
		}
		else
		{
			HeapifyUp(index);
		}

	}

	void HeapifyUp(size_t index)
	{
		size_t parent = GetParent(index);

		while (index > 0 && TKeyCompare::Compare(mItems[parent].Key, mItems[index].Key) > 0)
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

		if (left < mItems.Size())
		{
			if (TKeyCompare::Compare(mItems[left].Key, mItems[index].Key) < 0)
			{
				smallest = left;
			}
		}

		if (right < mItems.Size())
		{
			if (TKeyCompare::Compare(mItems[right].Key, mItems[smallest].Key) < 0)
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


template<typename TKey, typename TValue, typename TKeyCompare, typename TValueCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const PriorityDictionary<TKey, TValue, TKeyCompare, TValueCompare> PriorityDictionary<TKey, TValue, TKeyCompare, TValueCompare>::Empty;

MEDUSA_END;