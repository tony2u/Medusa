// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Collection/ILinkedList.h"
#include "Core/Assertion/CommonAssert.h"

MEDUSA_BEGIN;


template<typename T, typename TCompare = EqualCompare<T> >
class LinkedList :public ILinkedList < T >
{
public:
	typedef LinkedList<T, TCompare> SelfType;
	typedef ILinkedList<T> BaseType;
	typedef typename BaseType::NodePtr NodePtr;
	typedef typename IEnumerable<T>::TConstPointerType TConstPointerType;
	typedef typename IEnumerable<T>::TPointerType TPointerType;
	typedef typename IEnumerable<T>::TParameterType TParameterType;
	typedef typename IEnumerable<T>::TReturnType TReturnType;
	typedef typename IEnumerable<T>::TConstReturnType TConstReturnType;
	typedef typename IEnumerable<T>::TReferenceType TReferenceType;
	typedef typename IEnumerable<T>::TConstReferenceType TConstReferenceType;


	const static SelfType Empty;
public:
	LinkedList()
	{
		mHead.Next = &mTail;
		mTail.Prev = &mHead;
	}

	template<typename T1>
	LinkedList(const IEnumerable<T1>& items)
	{
		this->mCount = 0;
		mHead.Next = &mTail;
		mTail.Prev = &mHead;
		CopyFrom(items);
	}

	LinkedList(const LinkedList& items)
	{
		this->mCount = 0;
		mHead.Next = &mTail;
		mTail.Prev = &mHead;
		CopyFrom(items);
	}

	LinkedList& operator=(const LinkedList& items)
	{
		this->mCount = 0;
		mHead.Next = &mTail;
		mTail.Prev = &mHead;
		CopyFrom(items);
		return *this;
	}

	LinkedList(LinkedList&& other)
	{
		if (this != &other)
		{
			this->mCount = other.mCount;
			mHead = other.mHead;
			mTail = other.mTail;

			other.mHead.Next = &other.mTail;
			other.mTail.Prev = &other.mHead;
			other.mCount = 0;
		}
	}

	LinkedList& operator=(LinkedList&& other)
	{
		if (this != &other)
		{
			Clear();
			this->mCount = other.mCount;
			mHead = other.mHead;
			mTail = other.mTail;

			other.mHead.Next = &other.mTail;
			other.mTail.Prev = &other.mHead;
			other.mCount = 0;
		}
		return *this;
	}

	template<typename T1>
	LinkedList& operator=(const LinkedList<T1>& items)
	{
		this->mCount = 0;
		mHead.Next = &mTail;
		mTail.Prev = &mHead;
		CopyFrom(items.ConstBegin(), items.ConstEnd());
		return *this;
	}

	virtual ~LinkedList(void)
	{
		Clear();
	}


public:

	NodePtr operator[](size_t index)
	{
		MEDUSA_ASSERT_IF(index < this->mCount + 1, "");
		NodePtr node = mHead.Next;
		while (index != 0)
		{
			--index;
			MEDUSA_ASSERT_NOT_NULL(node, "");
			node = node->Next;
		}
		return node;
	}

	const NodePtr operator[](size_t index)const
	{
		MEDUSA_ASSERT_IF(index < this->mCount + 1, "");
		NodePtr node = mHead.Next;
		while (index != 0)
		{
			--index;
			MEDUSA_ASSERT_NOT_NULL(node, "");
			node = node->Next;
		}
		return node;
	}

#pragma region IEnumerable interface
public:

	class Enumerator :public IEnumerator < TReturnType, TPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit Enumerator(NodePtr head, NodePtr tail) :mHead(head), mTail(tail), mIndex(head) {}
		virtual TReturnType Current() { return mIndex->Value; }
		virtual TPointerType CurrentPtr() { return &(mIndex->Value); }

		TReturnType operator*() { return mIndex->Value; }
		TPointerType operator->() { return &(mIndex->Value); }

		virtual bool MoveNext()
		{
			mIndex = mIndex->Next;
			return mIndex != mTail;
		}
		virtual void Reset() { mIndex = mHead; }
	protected:
		NodePtr mHead;
		NodePtr mTail;

		NodePtr mIndex;
	};

	class ConstEnumerator :public IEnumerator < TConstReturnType, TConstPointerType >	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		explicit ConstEnumerator(const LinkedListNode<T>* head, const LinkedListNode<T>* tail) :mHead(head), mTail(tail), mIndex(head) {}
		virtual TConstReturnType Current() { return mIndex->Value; }
		virtual TConstPointerType CurrentPtr() { return &(mIndex->Value); }

		TConstReturnType operator*() { return mIndex->Value; }
		TConstPointerType operator->() { return &(mIndex->Value); }


		virtual bool MoveNext()
		{
			mIndex = mIndex->Next;
			return mIndex != mTail;
		}
		virtual void Reset() { mIndex = mHead; }
	protected:
		const LinkedListNode<T>* mHead;
		const LinkedListNode<T>* mTail;

		const LinkedListNode<T>* mIndex;
	};
public:
	ConstEnumerator GetEnumerator()const { return ConstEnumerator(&mHead, &mTail); }
	Enumerator GetEnumerator() { return Enumerator(&mHead, &mTail); }
protected:
	virtual IEnumerator<TConstReturnType, TConstPointerType>* GetEnumeratorVirtualHelper()const { return new ConstEnumerator(&mHead, &mTail); }
	virtual IEnumerator<TReturnType, TPointerType>* GetEnumeratorVirtualHelper() { return new Enumerator(&mHead, &mTail); }
public:
	class ConstInterator
	{
	public:
		explicit ConstInterator(const LinkedListNode<T>* cur) :mCurrent(cur) {}
		TConstReturnType operator*()const { return mCurrent->Value; }
		TConstPointerType operator->()const { return &(mCurrent->Value); }
		bool operator==(const ConstInterator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const ConstInterator& other)const { return mCurrent != other.mCurrent; }
		ConstInterator& operator++() { mCurrent=mCurrent->Next; return *this; }
		ConstInterator operator++(int)const { return ConstInterator(mCurrent->Next); }
		ConstInterator& operator--() { mCurrent=mCurrent->Prev; return *this; }
		ConstInterator operator--(int)const { return ConstInterator(mCurrent->Prev); }
	protected:
		const LinkedListNode<T>* mCurrent;
	};

	class Interator
	{
	public:
		explicit Interator(LinkedListNode<T>* cur) :mCurrent(cur) {}
		TReturnType operator*()const { return mCurrent->Value; }
		TPointerType operator->()const { return &(mCurrent->Value); }
		bool operator==(const Interator& other)const { return mCurrent == other.mCurrent; }
		bool operator!=(const Interator& other)const { return mCurrent != other.mCurrent; }
		Interator& operator++() { mCurrent = mCurrent->Next; return *this; }
		Interator operator++(int)const { return Interator(mCurrent->Next); }
		Interator& operator--() { mCurrent = mCurrent->Prev; return *this; }
		Interator operator--(int)const { return Interator(mCurrent->Prev); }
	protected:
		LinkedListNode<T>* mCurrent;
	};
	ConstInterator begin()const { return ConstInterator(mHead.Next); }
	ConstInterator end()const { return ConstInterator(&mTail); }
	Interator begin() { return Interator(mHead.Next); }
	Interator end() { return Interator(&mTail); }

	ConstInterator rbegin()const { return ConstInterator(mTail.Prev); }
	ConstInterator rend()const { return ConstInterator(&mHead); }
	Interator rbegin() { return Interator(mTail.Prev); }
	Interator rend() { return Interator(&mHead); }

#pragma endregion IEnumerable interface


#pragma region ICollection interface

public:
	virtual bool IsLinear() const { return false; }
	virtual TConstPointerType Items() const
	{
		//MEDUSA_NOT_IMPLEMENT();
		return nullptr;
	}
	virtual TPointerType MutableItems()
	{
		//MEDUSA_NOT_IMPLEMENT();
		return nullptr;
	}
	virtual bool Contains(TParameterType val)const
	{
		NodePtr node = FindFirst(val);
		return node != nullptr;
	}


	virtual size_t CopyTo(T* outArray, size_t arraySize)const
	{
		size_t index = 0;
		for (NodePtr node = mHead.Next; node != &mTail; node = node->Next)
		{
			Memory::CopyConstruct(outArray + index, node->Value);
			++index;
		}
		return index;
	}



#pragma endregion ICollection interface


#pragma region ILinkedList interface
public:
	virtual void AddAfter(NodePtr node, NodePtr newNode)
	{
		MEDUSA_ASSERT_NOT_NULL(node, "");
		MEDUSA_ASSERT_NOT_NULL(newNode, "");

		newNode->Prev = node;
		newNode->Next = node->Next;
		if (node->Next != nullptr)
		{
			node->Next->Prev = newNode;
		}
		node->Next = newNode;
		++this->mCount;
	}
	NodePtr AddAfter(NodePtr node, TParameterType val)
	{
		NodePtr newNode = new LinkedListNode<T>(val);
		AddAfter(node, newNode);
		return newNode;
	}
	virtual void AddBefore(NodePtr node, NodePtr newNode)
	{
		MEDUSA_ASSERT_NOT_NULL(node, "");
		MEDUSA_ASSERT_NOT_NULL(newNode, "");
		newNode->Next = node;
		newNode->Prev = node->Prev;

		if (node->Prev != nullptr)
		{
			node->Prev->Next = newNode;
		}
		node->Prev = newNode;
		++this->mCount;
	}

	NodePtr AddBefore(NodePtr node, TParameterType val)
	{
		NodePtr newNode = new LinkedListNode<T>(val);
		AddBefore(node, newNode);
		return newNode;
	}

	virtual void AddFirst(NodePtr node)
	{
		MEDUSA_ASSERT_NOT_NULL(node, "");

		AddAfter(&mHead, node);
	}
	virtual void AddLast(NodePtr node)
	{
		MEDUSA_ASSERT_NOT_NULL(node, "");

		AddBefore(&mTail, node);
	}

	virtual NodePtr FindFirst(TParameterType val)const
	{
		for (NodePtr node = mHead.Next; node != &mTail; node = node->Next)
		{
			if (TCompare::Compare(node->Value, val) == 0)
			{
				return node;
			}
		}

		return nullptr;
	}

	template<typename T2, typename TCompare2>
	NodePtr FindFirstWithOtherKey(T2 val)const
	{
		for (NodePtr node = mHead.Next; node != &mTail; node = node->Next)
		{
			if (TCompare2::Compare(node->Value, val) == 0)
			{
				return node;
			}
		}

		return nullptr;
	}

	virtual NodePtr FindLast(TParameterType val)const
	{
		for (NodePtr node = mTail.Prev; node != &mHead; node = node->Prev)
		{
			if (TCompare::Compare(node->Value, val) == 0)
			{
				return node;
			}
		}

		return nullptr;
	}

	NodePtr FindLastLess(TParameterType val)const
	{
		for (NodePtr node = mTail.Prev; node != &mHead; node = node->Prev)
		{
			if (TCompare::Compare(node->Value, val) < 0)
			{
				return node;
			}
		}

		return nullptr;
	}


	template<typename T2, typename TCompare2>
	NodePtr FindLast(T2 val)const
	{
		for (NodePtr node = mTail.Prev; node != &mHead; node = node->Prev)
		{
			if (TCompare2::Compare(node->Value, val) == 0)
			{
				return node;
			}
		}

		return nullptr;
	}

	template<typename T2, typename TCompare2>
	NodePtr FindLastLess(T2 val)const
	{
		for (NodePtr node = mTail.Prev; node != &mHead; node = node->Prev)
		{
			if (TCompare2::Compare(node->Value, val) < 0)
			{
				return node;
			}
		}

		return nullptr;
	}

	virtual NodePtr Remove(NodePtr node)
	{
		MEDUSA_ASSERT_NOT_NULL(node, "");
		if (node->Prev != nullptr)
		{
			node->Prev->Next = node->Next;
		}

		if (node->Next != nullptr)
		{
			node->Next->Prev = node->Prev;
		}
		--this->mCount;
		return node->Next;
	}


	virtual NodePtr Delete(NodePtr node)
	{
		NodePtr oldNode = node;
		node = Remove(node);
		SAFE_DELETE(oldNode);
		return node;
	}


	virtual NodePtr FirstNode()const
	{
		if (mHead.Next == &mTail)
		{
			return nullptr;
		}
		return mHead.Next;
	}

	virtual NodePtr LastNode()const
	{
		if (mTail.Prev == &mHead)
		{
			return nullptr;
		}
		return mTail.Prev;
	}

	const NodePtr Tail()const
	{
		return &mTail;
	}

	NodePtr Tail()
	{
		return &mTail;
	}

	const NodePtr Head()const
	{
		return &mHead;
	}

	NodePtr Head()
	{
		return &mHead;
	}

	TConstReferenceType First()const
	{
		return mHead.Next->Value;
	}

	TReferenceType First()
	{
		return mHead.Next->Value;
	}

	TConstReferenceType Last()const
	{
		return mTail.Prev->Value;
	}

	TReferenceType Last()
	{
		return mTail.Prev->Value;
	}

	virtual bool ContainsNode(NodePtr node)const
	{
		for (NodePtr node1 = mHead.Next; node1 != &mTail; node1 = node1->Next)
		{
			if (node1 == node)
			{
				return true;
			}
		}
		return false;
	}

	virtual void RemoveAll(TParameterType val)
	{
		for (NodePtr node = mHead.Next; node != &mTail;)
		{
			if (TCompare::Compare(node->Value, val) == 0)
			{
				node->Prev->Next = node->Next;
				if (node->Next != nullptr)
				{
					node->Next->Prev = node->Prev;
				}
				node = node->Next;

				NodePtr tempNode = node;
				SAFE_DELETE(tempNode);
			}
			else
			{
				node = node->Next;
			}
		}
		this->mCount = 0;
	}
	virtual NodePtr Add(TParameterType val)
	{
		NodePtr newNode = new LinkedListNode<T>(val);
		AddLast(newNode);
		return newNode;
	}

	NodePtr NewAddNode()
	{
		NodePtr newNode = new LinkedListNode<T>();
		AddLast(newNode);
		return newNode;
	}

	TReferenceType NewAdd()
	{
		return NewAddNode()->Value;
	}

	virtual bool Remove(TParameterType val)
	{
		NodePtr node = FindFirst(val);
		if (node != nullptr)
		{
			Remove(node);
			return true;
		}
		return false;
	}

	virtual void Clear()
	{
		this->mCount = 0;
		for (NodePtr node = mHead.Next; node != &mTail;)
		{
			NodePtr tempNode = node;
			node = node->Next;
			SAFE_DELETE(tempNode);
		}

		mHead.Next = &mTail;
		mTail.Prev = &mHead;
	}

#pragma endregion ILinkedList interface

protected:
	LinkedListNode<T> mHead;
	LinkedListNode<T> mTail;
};


template<typename T, class TCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const LinkedList<T, TCompare> LinkedList<T, TCompare>::Empty;

MEDUSA_END;