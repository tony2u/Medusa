// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/Stack.h"

MEDUSA_BEGIN;
template <typename TId, typename TObject, typename TObjectNewer = DefaultNewerById<TObject>, typename THashCoder = DefaultHashCoder, typename TKeyCompare = DefaultCompare, typename TObjectCompare = DefaultCompare >
class IdSingleObjectPool
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

	typedef typename Compile::TypeTraits<TObject>::UnderlyingType TObjectPointeeType;

	typedef Stack<TObject, TObjectCompare> ItemStack;
public:
	IdSingleObjectPool() {}
	virtual ~IdSingleObjectPool() { Clear(); }
public:
	bool IsEmpty()const { return Count() == 0; }
	size_t Count() const { return mItems.Count(); }
public:
	void Clear()
	{
		for (auto i : mItems)
		{
			TId& id = i.Key;
			ItemStack* stack = i.Value;
			SAFE_DELETE_COLLECTION(*stack);
			SAFE_DELETE(stack);

			OnReleaseId(id);
		}
		mItems.Clear();
	}

	TObject Create(TIdParameterType id)
	{
		TObject obj = nullptr;

		if (mItems.ContainsKey(id))
		{
			ItemStack* items = mItems.Get(id);
			if (!items->IsEmpty())
			{
				obj = items->PopCopy();
			}

			if (items->IsEmpty())
			{
				mItems.RemoveKey(id);
				OnReleaseId(id);
				SAFE_DELETE(items);
			}
		}

		if (obj == nullptr)
		{
			obj = TObjectNewer::New(id);
		}
		return obj;
	}

	void Recycle(TIdParameterType id, TObjectParameterType obj)
	{
		ItemStack* stack = mItems.GetOptional(id, nullptr);
		if (stack == nullptr)
		{
			stack = new ItemStack();
			mItems.Add(id, stack);
			OnRetainId(id);
		}
		stack->Push(obj);
	}
protected:
	virtual void OnReleaseId(TIdParameterType id) {}
	virtual void OnRetainId(TIdParameterType id) {}

protected:
	Dictionary<TId, Stack<TObject, TObjectCompare>*, THashCoder, TKeyCompare> mItems;
};
MEDUSA_END;