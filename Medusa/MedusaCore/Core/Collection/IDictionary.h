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

template<typename TKey,typename TValue,typename TKeyValuePair >
struct IDictionary:public ICollection<TKeyValuePair>
{
public:
    typedef typename ICollection<TKeyValuePair>::TParameterType TParameterType;
public:
	IDictionary(){}
	virtual ~IDictionary(){}
public:
	typedef TKey KeyType;
	typedef TValue ValueType;
	typedef TKeyValuePair KeyValuePairType;

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


	typedef ICollection<TKey> KeyCollectionType;
	typedef ICollection<TValue> ValueCollectionType;
public:
	TValueConstReturnType operator[](TKeyParameterType key)const{return Get(key);}
	TValueReferenceType operator[](TKeyParameterType key){return Get(key);}
public:
	//virtual KeyCollectionType& GetKeys()const=0;
	//virtual ValueCollectionType& GetValues()const=0;
	virtual bool ContainsKey(TKeyParameterType key)const=0;
	virtual bool ContainsValue(TValueParameterType value)const=0;

	virtual TValueReferenceType Get(TKeyParameterType key)=0;
	virtual TValueConstReturnType Get(TKeyParameterType key)const=0;
	virtual void Set(TKeyParameterType key,TValueParameterType value)=0;

	virtual TValuePointerType TryGet(TKeyParameterType key)=0;
	virtual TKeyPointerType TryGetKey(TValueParameterType value)=0;

	virtual TValueConstPointerType TryGet(TKeyParameterType key)const=0;
	virtual TKeyConstPointerType TryGetKey(TValueParameterType value)const=0;

	virtual TValueConstReturnType GetOptional(TKeyParameterType key,TValueParameterType failedReturn)const=0;

	virtual void Add(TKeyParameterType key,TValueParameterType value)=0;
	virtual bool TryAdd(TKeyParameterType key,TValueParameterType value)=0;


	virtual bool RemoveKey(TKeyParameterType key)=0;
	virtual bool RemoveValue(TValueParameterType value)=0;


	virtual TValue RemoveKeyOptional(TKeyParameterType key,TValueParameterType failedReturn)=0;

	virtual void Add(TParameterType val)=0;
	virtual bool TryAdd(TParameterType val)=0;
	virtual bool Remove(TParameterType val)=0;
	virtual void Clear()=0;
};

MEDUSA_END;