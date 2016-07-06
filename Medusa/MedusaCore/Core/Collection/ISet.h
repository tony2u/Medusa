// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"

#include "Core/Collection/IEnumerable.h"
#include "Core/Collection/ICollection.h"
#include "Core/Collection/KeyValuePair.h"
#include "Core//Compile/TypeTraits.h"

MEDUSA_BEGIN;

template<typename T,typename TCompare=DefaultCompare >
struct ISet:public ICollection<T>
{
public:
    typedef typename ICollection<T>::TParameterType TParameterType;
public:
	ISet(){}
	virtual ~ISet(){}
public:
	typedef T ValueType;
public:
	virtual void Add(TParameterType val)=0;
	virtual bool TryAdd(TParameterType val)=0;
	virtual bool Remove(TParameterType val)=0;
	virtual void Clear()=0;
public:
	virtual void UnionWith(const ICollection<T>& other)=0;
	virtual void IntersectWith(const ICollection<T>& other)=0;
	virtual void ExceptWith(const ICollection<T>& other)=0;
	virtual void SymmetricExceptWith(const ICollection<T>& other)=0;


	virtual bool IsSubsetOf(const ICollection<T>& other)const=0;
	virtual bool IsSupersetOf(const ICollection<T>& other)const=0;
	virtual bool IsProperSupersetOf(const ICollection<T>& other)const=0;
	virtual bool IsProperSubsetOf(const ICollection<T>& other)const=0;

	virtual bool IsOverlaps(const ICollection<T>& other)const=0;
	virtual bool Equals(const ICollection<T>& other)const=0;

};

MEDUSA_END;