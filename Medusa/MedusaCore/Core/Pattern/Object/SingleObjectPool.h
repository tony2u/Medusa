// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;
template <typename TObject, typename TObjectCompare = DefaultCompare<TObject>, typename TObjectNewer = DefaultNewer<TObject>>
class SingleObjectPool
{
public:
	typedef typename Compile::TypeTraits<TObject>::ReferenceType TObjectReferenceType;
	typedef typename Compile::TypeTraits<TObject>::ConstReferenceType TObjectConstReferenceType;

	typedef typename Compile::TypeTraits<TObject>::PointerType TObjectPointerType;
	typedef typename Compile::TypeTraits<TObject>::ConstPointerType TObjectConstPointerType;

	typedef typename Compile::TypeTraits<TObject>::ParameterType TObjectParameterType;

	typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

	typedef List<TObject, TObjectCompare> ItemCollection;
public:
	SingleObjectPool() {}
	virtual ~SingleObjectPool() { Clear(); }
public:
	bool IsEmpty()const { return Count() == 0; }
	size_t Count() const { return mItems.Count(); }
public:
	void Clear()
	{
		SAFE_DELETE_COLLECTION(mItems);
	}

	TObject Create()
	{
		if (!mItems.IsEmpty())
		{
			TObject obj = mItems.Last();
			mItems.RemoveLast();
			return obj;
		}
		return TObjectNewer::New();
	}

	void Recycle(TObjectParameterType obj)
	{
		mItems.Append(obj);
	}

protected:
	ItemCollection mItems;
};
MEDUSA_END;