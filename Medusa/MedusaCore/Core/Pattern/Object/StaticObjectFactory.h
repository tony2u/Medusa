// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "CorePlatform/CorePlatform.h"
#include "Core/Assertion/CommonAssert.h"

#include "Core/Pattern/Delegate.h"
#include "Core/Collection/STLPort.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

template<typename TId, typename FuncSignature, typename THashCoder = DefaultHashCoder<TId>>
class StaticObjectFactory;

template<typename TId, typename TBase, typename... TArgs, typename THashCoder>
class StaticObjectFactory<TId, TBase*(TArgs...), THashCoder>
{
public:
	typedef TBase* CreateDerivedCallback(TArgs...);
	typedef CreateDerivedCallback* CreatorType;
	~StaticObjectFactory() { Clear(); }
private:
	typedef Dictionary<TId, CreatorType, THashCoder> MapType;
	typedef Dictionary<TId, TBase*, THashCoder> ObjectDict;
	MapType mMap;
	ObjectDict mObjectDict;

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
	}
	void Register(const TId& id, CreatorType creator)
	{
		mMap.Add(id, creator);
	}

	template<typename TDerived>
	bool TryRegister(const TId& id)
	{
		return mMap.TryAdd(id, &CreateDerivedHelper<TDerived>);
	}
	bool TryRegister(const TId& id, CreatorType creator)
	{
		return mMap.TryAdd(id, creator);
	}
	bool UnRegister(const TId& id)
	{
		TBase* obj = mObjectDict.RemoveKeyOptional(id, nullptr);
		SAFE_DELETE(obj);
		return mMap.RemoveKey(id);
	}

	TBase* Create(const TId& id, TArgs... args)
	{
		TBase* obj = mObjectDict.GetOptional(id, nullptr);
		if (obj == nullptr)
		{
			CreatorType* outCreator = mMap.TryGet(id);
			if (outCreator != nullptr)
			{
				obj = (*outCreator)(std::forward<TArgs>(args)...);
				mObjectDict.Add(id, obj);
			}
		}

		return obj;
	}
	
	void Clear()
	{
		SAFE_DELETE_DICTIONARY_VALUE(mObjectDict);
		mMap.Clear();
	}
};





MEDUSA_END;

