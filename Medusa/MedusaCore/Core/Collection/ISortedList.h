// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once


#include "Core/Collection/ICollection.h"

MEDUSA_BEGIN;

template<typename T>
class ISortedList:public ICollection<T>
{
protected:
	ISortedList():mItems(nullptr){}
public:
	using IEnumerable<T>::GetEnumeratorVirtual;
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
	inline intp IndexOf(TParameterType val)const{return IndexOf(0,val);}
	inline intp IndexOf(size_t srcBegin,TParameterType val)const{return IndexOf(srcBegin,Count(),val);}

	inline intp LastIndexOf(TParameterType val)const{return LastIndexOf(0,val);}
	inline intp LastIndexOf(size_t srcBegin,TParameterType val)const{return LastIndexOf(srcBegin,Count(),val);}

	inline TConstReturnType First()const{return this->operator[](0);}
	inline TConstReturnType Last()const{return this->operator[](Count()-1);}

	inline TReferenceType First(){return this->operator[](0);}
	inline TReferenceType Last(){return this->operator[](Count()-1);}


	inline bool Contains(TParameterType val)const{return Contains(0,val);}
	inline bool Contains(size_t srcBegin,TParameterType val)const{return Contains(srcBegin,Count(),val);}
	inline bool Contains(size_t srcBegin,size_t srcEnd,TParameterType val)const{return IndexOf(srcBegin,srcEnd,val)>=0;}

	inline bool RemoveFirst(TParameterType val){ return RemoveFirst(0,Count(),val);}
	inline void RemoveFirst(){ RemoveAt(0);}
	inline bool RemoveFirst(size_t srcBegin,size_t srcEnd,TParameterType val)
	{
		intp index=IndexOf(srcBegin,srcEnd,val);
		if (index>=0)
		{
			RemoveAt(index);
			return true;
		}
		return false;
	}

	inline bool RemoveLast(TParameterType val){ return RemoveLast(0,Count(),val);}
	inline void RemoveLast(){ RemoveAt(Count()-1);}

	inline bool RemoveLast(size_t srcBegin,size_t srcEnd,TParameterType val)
	{
		intp index=LastIndexOf(srcBegin,srcEnd,val);
		if (index>=0)
		{
			RemoveAt(index);
			return true;
		}

		return false;
	}
	inline void RemoveAll(TParameterType val){ RemoveAll(0,Count(),val);}

	inline TConstReturnType operator[](size_t index)const
	{
		MEDUSA_ASSERT_IF(index<this->mCount,"");
		return mItems[index];
	}

	virtual TReferenceType operator[](size_t index)
	{
		MEDUSA_ASSERT_IF(index<this->mCount,"");
		return mItems[index];
	}

	inline TConstReturnType Get(size_t index)const
	{
		MEDUSA_ASSERT_IF(index<this->mCount,"");
		return mItems[index];
	}
public:
	virtual intp IndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const=0;
	virtual intp LastIndexOf(size_t srcBegin,size_t srcEnd,TParameterType val)const=0;

	virtual void RemoveIndexes(const IList<size_t>& indexes)=0;

	virtual void RemoveAt(size_t index)=0;
	virtual void RemoveRange(size_t begin,size_t end)=0;
	virtual void RemoveAll(size_t srcBegin,size_t srcEnd,TParameterType val)=0;

	virtual void Add(TParameterType val)=0;
	virtual bool Remove(TParameterType val)=0;
	virtual void Clear()=0;
	virtual void Sort()=0;
protected:
	T* mItems=nullptr;

};

MEDUSA_END;