// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "CorePlatform/CorePlatform.h"
#include "Core/Assertion/CommonAssert.h"


#include "Core/Pattern/Delegate.h"
#include "Core/Collection/STLPort.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/Stack.h"

MEDUSA_BEGIN;

template<typename TId, typename FuncSignature, typename THashCoder = DefaultHashCoder<TId>, bool IsPoolEnabled = false>
class MapObjectFactory;

template<typename TId, typename TBase, typename... TArgs, typename THashCoder, bool IsPoolEnabled>
class MapObjectFactory<TId, TBase*(TArgs...), THashCoder, IsPoolEnabled>
{
public:
	typedef TBase* CreateDerivedCallback(TArgs...);
	typedef CreateDerivedCallback* CreatorType;
	typedef Dictionary<TId, CreatorType, THashCoder> MapType;
	typedef Stack<TBase*> ObjectPool;
	typedef Dictionary<TId, ObjectPool*, THashCoder> ObjectPoolDict;
	~MapObjectFactory() { Clear(); }

	const MapType& CreatorMap()const { return mMap; }

	bool Contains(const TId& id)const
	{
		return mMap.ContainsKey(id);
	}
private:
	
	MapType mMap;
	ObjectPoolDict mPoolDict;

	template<typename TDerived>
	static TBase* CreateDerivedHelper(TArgs... args)
	{
		return new TDerived(std::forward<TArgs>(args)...);
	}

public:
	template<typename TDerived>
	void Register(const TId& id)
	{
		mMap.Add(id, &CreateDerivedHelper<TDerived>);
		if (IsPoolEnabled)
		{
			mPoolDict.Add(id, new ObjectPool());
		}
	}
	void Register(const TId& id, CreatorType creator)
	{
		mMap.Add(id, creator);
		if (IsPoolEnabled)
		{
			mPoolDict.Add(id, new ObjectPool());
		}
	}

	template<typename TDerived>
	bool TryRegister(const TId& id)
	{
		if (mMap.TryAdd(id, &CreateDerivedHelper<TDerived>))
		{
			if (IsPoolEnabled)
			{
				mPoolDict.Add(id, new ObjectPool());
			}
			return true;
		}
		return false;
	}
	bool TryRegister(const TId& id, CreatorType creator)
	{
		if (mMap.TryAdd(id, creator))
		{
			if (IsPoolEnabled)
			{
				mPoolDict.Add(id, new ObjectPool());
			}return true;
		}
		return false;;
	}
	bool UnRegister(const TId& id)
	{
		if (IsPoolEnabled)
		{
			ObjectPool* objectPool = mPoolDict.GetOptional(id, nullptr);
			if (objectPool != nullptr)
			{
				SAFE_DELETE_COLLECTION(*objectPool);
				delete objectPool;
			}
		}
		return mMap.RemoveKey(id);
	}

	TBase* Create(const TId& id, TArgs... args)
	{
		if (IsPoolEnabled)
		{
			ObjectPool* objectPool = mPoolDict.GetOptional(id, nullptr);
			if (objectPool != nullptr&&!objectPool->IsEmpty())
			{
				return objectPool->PopCopy();
			}
		}
		CreatorType* outCreator = mMap.TryGet(id);
		if (outCreator != nullptr)
		{
			return (*outCreator)(std::forward<TArgs>(args)...);
		}
		return nullptr;
	}

	void Recycle(const TId& id, TBase* obj)
	{
		if (IsPoolEnabled)
		{
			ObjectPool* objectPool = mPoolDict.GetOptional(id, nullptr);
			if (objectPool != nullptr)
			{
				objectPool->Push(obj);
			}
		}
		else
		{
			delete obj;
		}
	}
	void Clear()
	{
		if (!IsPoolEnabled) { return; }
		FOR_EACH_COLLECTION(i, mPoolDict)
		{
			ObjectPool* objectPool = i->Value;
			SAFE_DELETE_COLLECTION(*objectPool);
			delete objectPool;
		}
		mPoolDict.Clear();
	}
};





MEDUSA_END;

