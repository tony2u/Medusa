// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Memory/MemoryData.h"
#include "Core/String/HeapString.h"



MEDUSA_BEGIN;

template<typename TField>
class SirenStructFieldMetadata
{
public:
	SirenStructFieldMetadata(const char* name, uint length)
		:Name(name,length)
	{

	}
	void SetToDefault(TField& outVal)const
	{
		
	}

	bool HasValue(const TField& val)const
	{
		return HasValueHelper(val);
	}

	const StringRef Name;
private:
	template<typename T>
	bool HasValueHelper(const T& val)const
	{
		return true;
	}

	template<typename T>
	bool HasValueHelper(const T*& val)const
	{
		return val != nullptr;
	}

	template<typename T>
	bool HasValueHelper(T* const& val)const
	{
		return val != nullptr;
	}

	template<typename TKey, typename TValue>
	bool HasValueHelper(const Dictionary<TKey, TValue>& val)const
	{
		return !val.IsEmpty();
	}


	bool HasValueHelper(const HeapString& val)const
	{
		return !val.IsEmpty();
	}

	bool HasValueHelper(const WHeapString& val)const
	{
		return !val.IsEmpty();
	}

	bool HasValueHelper(const MemoryData& val)const
	{
		return !val.IsEmpty();
	}

	template<typename T>
	bool HasValueHelper(const List<T>& val)const
	{
		return !val.IsEmpty();
	}

};

MEDUSA_END;
