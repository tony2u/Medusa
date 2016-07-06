// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;
template <typename TId, typename TObject, typename TKeyHashCoder = DefaultHashCoder, typename TObjectHashCoder = DefaultHashCoder, typename TKeyCompare = DefaultCompare >
class IdObjectCache
{
public:
	typedef typename Compile::TypeTraits<TObject>::ReferenceType TObjectReferenceType;
	typedef typename Compile::TypeTraits<TObject>::ConstReferenceType TObjectConstReferenceType;

	typedef typename Compile::TypeTraits<TObject>::PointerType TObjectPointerType;
	typedef typename Compile::TypeTraits<TObject>::ConstPointerType TObjectConstPointerType;

	typedef typename Compile::TypeTraits<TId>::ParameterType TIdParameterType;
	typedef typename Compile::TypeTraits<TObject>::ParameterType TObjectParameterType;

	typedef typename Compile::TypeTraits<TId>::ReferenceType TIdReferenceType;

	typedef typename Compile::TypeTraits<TId>::PointerType TIdPointerType;
	typedef typename Compile::TypeTraits<TId>::ConstPointerType TIdConstPointerType;
public:
	IdObjectCache() {}
	virtual ~IdObjectCache() { Clear(); }
public:
	bool IsEmpty()const { return Count() == 0; }
	size_t Count() const { return mItems.Count(); }
	const Dictionary<TId, TObject, TKeyHashCoder, TKeyCompare>& Items()const { return mItems; }
public:
	void Clear()
	{
		SAFE_DELETE_DICTIONARY_VALUE(mItems);
	}

	bool ContainsId(TIdParameterType id)const
	{
		return mItems.ContainsKey(id);
	}

	bool ContainsObject(TObjectParameterType object)const
	{
		return mItems.ContainsValue(object);
	}

	TObjectReferenceType GetObject(TIdParameterType id)
	{
		return mItems.Get(id);
	}
	TObjectConstReferenceType GetObject(TIdParameterType id)const
	{
		return mItems.Get(id);
	}

	TObjectPointerType TryGetObject(TIdParameterType id)
	{
		return mItems.TryGet(id);
	}

	TObjectConstPointerType TryGetObject(TIdParameterType id)const
	{
		return mItems.TryGet(id);
	}

	TObject TryGetObjectWithFailed(TIdParameterType id, TObjectParameterType failedReturn)const
	{
		return mItems.GetOptional(id, failedReturn);
	}

	TObject TryGetObjectWithFailed(TIdParameterType id, TObjectParameterType failedReturn)
	{
		return mItems.GetOptional(id, failedReturn);
	}

	TIdPointerType TryGetId(TObjectParameterType object)
	{
		return mItems.TryGetKey(object);
	}

	TIdConstPointerType TryGetId(TObjectParameterType object)const
	{
		return mItems.TryGetKey(object);
	}

	void Add(TIdParameterType id, TObjectParameterType object)
	{
		mItems.Add(id, object);
	}

	bool RemoveId(TIdParameterType id)
	{
		return mItems.RemoveKey(id);
	}
	bool RemoveObject(TObjectParameterType object)
	{
		return mItems.RemoveValue(object);
	}

	bool DeleteId(TIdParameterType id)
	{
		TObjectPointerType outObject = mItems.TryGet(id);
		if (outObject != nullptr)
		{
			if (RemoveId(id))
			{
				SAFE_DELETE(*outObject);
				return true;
			}
		}

		return false;
	}

	bool DeleteObject(TObjectParameterType object)
	{
		TIdPointerType outId = mItems.TryGetKey(object);
		if (outId != nullptr)
		{
			SAFE_DELETE(object);
			bool result = RemoveId(*outId);
			return result;
		}

		SAFE_DELETE(object);
		return false;
	}

protected:
	Dictionary<TId, TObject, TKeyHashCoder, TObjectHashCoder, TKeyCompare> mItems;
};
MEDUSA_END;