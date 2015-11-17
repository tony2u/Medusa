// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Collection/Stack.h"


MEDUSA_BEGIN;


template<size_t TSize, typename TId, typename FuncSignature, bool IsPoolEnabled = false>
class ArrayObjectFactory;


template<size_t TSize, typename TId, typename TBase, typename... TArgs, bool IsPoolEnabled>
class ArrayObjectFactory<TSize, TId, TBase*(TArgs...), IsPoolEnabled>
{
public:
	typedef TBase* CreateDerivedCallback(TArgs&&...);
	typedef CreateDerivedCallback* CreatorType;
	typedef Stack<TBase*> ObjectPool;
	~ArrayObjectFactory() { Clear(); }
private:
	CreatorType mMap[TSize];
	ObjectPool mPoolMap[TSize];
	template<typename TDerived>
	static TBase* CreateDerivedHelper(TArgs... args)
	{
		return new TDerived(std::forward<TArgs>(args)...);
	}

public:
	template<typename TDerived>
	void Register(const TId& id) { mMap[id] = &CreateDerivedHelper<TDerived>; }
	void Register(const TId& id, CreatorType creator) { mMap[id] = creator; }
	void UnRegister(const TId& id) { mMap[id] = nullptr; }

	TBase* Create(const TId& id, TArgs... args)
	{
		if (IsPoolEnabled)
		{
			ObjectPool& objectPool = mPoolMap[id];
			if (!objectPool.IsEmpty())
			{
				return objectPool.Pop();
			}
		}
		CreatorType creator = mMap[id];
		if (creator != nullptr)
		{
			return (creator)(std::forward<TArgs>(args)...);
		}
		return nullptr;
	}
	void Recycle(const TId& id, TBase* obj)
	{
		if (IsPoolEnabled)
		{ 
			ObjectPool& objectPool = mPoolMap[id]; 
			objectPool.Push(obj); 
		}
		else
		{
			delete obj;
		}
	}
	void Clear()
	{
		if (!IsPoolEnabled) { return; }
		FOR_EACH_SIZE(i, TSize)
		{
			ObjectPool& objectPool = mPoolMap[i];
			SAFE_DELETE_COLLECTION(objectPool);
		}
	}
};



MEDUSA_END