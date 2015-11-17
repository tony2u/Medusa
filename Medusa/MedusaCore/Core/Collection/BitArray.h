// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Core/Collection/ICollection.h"
#include "Core/Collection/STLPort.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

template<size_t TSize>
class BitArray:public ICollection<bool>
{
	typedef BitArray<TSize> SelfType;

public:
	const static size_t Size=TSize/(sizeof(size_t)*8)+1;

	BitArray()
	{
		mCount=Size;
	}

	BitArray(const BitArray& items)
	{
		Memory::SafeCopy(mItems,Size,items.Items(),items.Count());
	}

	template<size_t TSize1>
	BitArray(const BitArray<TSize1>& items)
	{
		static_assert(TSize1 <= TSize, "Too big size");
		Memory::SafeCopy(mItems,Size,items.Items(),items.Count());
	}

	BitArray& operator=(const BitArray& items)
	{
		Memory::SafeCopy(mItems,Size,items.Items(),items.Count());
		return *this;
	}

	template<size_t TSize1>
	BitArray& operator=(const BitArray<TSize1>& items)
	{
		static_assert(TSize1 <= TSize, "Too big size");
		Memory::SafeCopy(mItems,Size,items.Items(),items.Count());
		return *this;
	}

	
	BitArray(const ICollection<bool>& items)
	{
		MEDUSA_ASSERT_IF(items.Count()<=Size,"");

		if (items.IsLinear())
		{
			Memory::SafeCopy(mItems,Size,items.Items(),items.Count());
		}
		else
		{
			size_t index=0;
			FOR_EACH_COLLECTION_VIRTUAL(i,items)
			{
				Set(index++,*i);
			}
		}
	}

public:
	bool operator[](size_t index)const
	{
		return Get(index);
	}

	bool Get(size_t index)const
	{
		MEDUSA_ASSERT_IF(index<TSize,"");

		size_t firstIndex=index/(sizeof(size_t)*8)+1;
		size_t secondIndex=index%(sizeof(size_t)*8);
		return ((mItems[firstIndex]<<secondIndex)&1)==1;
	}

	void Set(size_t index,bool val)
	{
		MEDUSA_ASSERT_IF(index<TSize,"");
		size_t firstIndex=index/(sizeof(size_t)*8)+1;
		size_t secondIndex=index%(sizeof(size_t)*8);
		mItems[firstIndex]|=(1>>secondIndex);
	}

#pragma region IEnumerable interface
protected:
	virtual IEnumerator<TConstReturnType,TConstPointerType>* GetEnumeratorVirtualHelper()const{MEDUSA_ASSERT_NOT_IMPLEMENT();return nullptr;}
	virtual IEnumerator<TReturnType,TPointerType>* GetEnumeratorVirtualHelper(){MEDUSA_ASSERT_NOT_IMPLEMENT();return nullptr;}


#pragma endregion IEnumerable interface

#pragma region ICollection interface
public:
	virtual bool IsLinear() const{return true;}
	virtual TConstPointerType Items() const {MEDUSA_ASSERT_NOT_IMPLEMENT();return nullptr; }
	virtual TPointerType MutableItems() { MEDUSA_ASSERT_NOT_IMPLEMENT(); return nullptr; }


	virtual bool Contains(bool val)const
	{
		return IndexOf(0,Size,val)>=0;
	}
	virtual size_t CopyTo(bool* outArray, size_t arraySize)const
	{
		MEDUSA_ASSERT_IF(arraySize<=TSize,"");
		FOR_EACH_SIZE(i,TSize)
		{
			*outArray++=Get(i);
		}
		return TSize;
	}



#pragma endregion ICollection interface

public:
	void ClearZero()
	{
		Memory::SetZero(mItems,Size);
	}

	virtual void Add(size_t val)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();
	}
	virtual bool Remove(size_t val)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();

		return true;
	}

	virtual void Clear()
	{

	}

	virtual int IndexOf(size_t srcBegin,size_t srcEnd,bool val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=TSize,"");

		FOR_EACH_COLLECTION_BEGIN_END(i,srcBegin,srcEnd)
		{
			if(Get(i)==val)
			{
				return (int)i;
			}
		}


		return -1;
	}

	virtual int LastIndexOf(size_t srcBegin,size_t srcEnd,bool val)const
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=TSize,"");

		FOR_EACH_COLLECTION_END_BEGIN(i,srcEnd-1,srcBegin-1)
		{
			if(Get(i)==val)
			{
				return (int)i;
			}
		}

		return -1;
	}

	virtual void SetAll(size_t srcBegin,size_t srcEnd,bool val)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=TSize,"");
		FOR_EACH_UINT_BEGIN_END(i,(int)srcBegin,(int)srcEnd)
		{
			Set(i,val);
		}
	}

	virtual void SetAll(bool val)
	{
		if (val)
		{
			Memory::Set(mItems,0xFFFFFFFF,Size);
		}
		else
		{
			Memory::SetZero(mItems,Size);
		}
	}

	virtual void ReplaceAll(size_t srcBegin,size_t srcEnd,bool oldValue,bool newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=TSize,"");

		FOR_EACH_COLLECTION_BEGIN_END(i,srcBegin,srcEnd)
		{
			if(Get(i)==newValue)
			{
				Set(i,newValue);
			}
		}
	}



	virtual void ReplaceFirst(size_t srcBegin,size_t srcEnd,bool oldValue,bool newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=TSize,"");

		FOR_EACH_COLLECTION_BEGIN_END(i,srcBegin,srcEnd)
		{
			if(Get(i)==oldValue)
			{
				Set(i,newValue);
				break;
			}
		}

	}

	virtual void ReplaceLast(size_t srcBegin,size_t srcEnd,bool oldValue,bool newValue)
	{
		MEDUSA_ASSERT_IF(srcEnd>srcBegin&&srcEnd<=TSize,"");

		FOR_EACH_COLLECTION_END_BEGIN(i,srcEnd-1,srcBegin-1)
		{
			if(Get(i)==oldValue)
			{
				Set(i,newValue);
				break;
			}
		}

	}
	
protected:
	size_t mItems[Size];

};

MEDUSA_END;