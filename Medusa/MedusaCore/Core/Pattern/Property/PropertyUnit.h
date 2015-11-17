// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/Array.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Log/Log.h"
#include "Core/Math/Math.h"
MEDUSA_BEGIN;

template<typename TIndex, typename T, size_t TSize, typename TCompare = DefaultCompare<T> >
class PropertyUnit
{
public:
	const static PropertyUnit Zero;
	const static PropertyUnit One;

	typedef Array<T, TSize, TCompare> ArrayType;
	typedef List<T, TCompare> ListType;
	typedef Dictionary<TIndex, T> DictionaryType;
public:
	PropertyUnit(T val = 0.f)
	{
		mItems.SetAll((T)val);
	}
	PropertyUnit(const ArrayType& item)
	{
		Set(item);
	}
	PropertyUnit(const ListType& item)
	{
		Set(item);
	}
	PropertyUnit(const DictionaryType& item)
	{
		Set(item);
	}

	PropertyUnit(const PropertyUnit& val)
	{
		Set(val);
	}
	PropertyUnit& operator=(const PropertyUnit& val)
	{
		Set(val);
		return *this;
	}

public:
	static StringRef GetPropertyName(TIndex type)
	{
		return type.ToString();
	}
public:
	ArrayType ToArray()const { return mItems; }
	ListType ToList()const
	{
		PropertyUnit::ListType result;
		CopyTo(result);
		return result;
	}
	DictionaryType ToDictionary()const
	{
		PropertyUnit::DictionaryType result;
		CopyTo(result);
		return result;
	}
	DictionaryType ToDictionaryExcludeZero()const
	{
		PropertyUnit::DictionaryType result;
		CopyToExcludeZero(result);
		return result;
	}

	void CopyTo(ArrayType& outArray)const
	{
		outArray = mItems;
	}
	void CopyTo(ListType& outList)const
	{
		outList.Clear();
		outList.AddRange(mItems);
	}
	void CopyTo(DictionaryType& outDict)const
	{
		outDict.Clear();
		FOR_EACH_SIZE(i, TSize)
		{
			outDict.Add((TIndex)i, mItems[i]);
		}
	}
	void CopyToExcludeZero(DictionaryType& outDict)const
	{
		outDict.Clear();
		FOR_EACH_SIZE(i, TSize)
		{
			if (!Math::IsZero(mItems[i]))
			{
				outDict.Add((TIndex)i, mItems[i]);
			}
		}
	}

	void PrintAll()const
	{
		HeapString str("PropertyUnit==>\t");
		FOR_EACH_SIZE(i, TSize)
		{
			TIndex type = (TIndex)i;
			float val = mItems[i];
			str.AppendFormat("{}:{}\n", type.ToString().c_str(), val);
		}
		Log::Info(str);
	}
	void PrintExcludeZero()const
	{
		HeapString str("PropertyUnit==>\t");
		FOR_EACH_SIZE(i, TSize)
		{
			TIndex type = (TIndex)i;
			float val = mItems[i];
			if (!Math::IsZero(val))
			{
				str.AppendFormat("{}:{}\n", type.ToString().c_str(), val);
			}
		}
		Log::Info(str);
	}
public:
	T Get(TIndex index)const
	{
		return mItems[(uint)index];
	}
	T& Mutable(TIndex index)
	{
		return mItems[(uint)index];
	}

	void Set(const ArrayType& item)
	{
		mItems = item;
	}
	void Set(const ListType& item)
	{
		Log::Assert(item.Count() == TIndex::Size, "Invalid item");
		FOR_EACH_SIZE(i, TSize)
		{
			mItems[i] = item[i];
		}
	}
	void Set(const DictionaryType& item)
	{
		FOR_EACH_COLLECTION(i, item)
		{
			TIndex type = i->Key;
			T val = i->Value;
			SetSingle(type, val);
		}
	}
	void Set(const PropertyUnit& val)
	{
		mItems = val.mItems;
	}

	void SetSingle(TIndex type, T val)
	{
		mItems[(uint)type] = val;
	}

	void Add(const PropertyUnit& val)
	{
		FOR_EACH_SIZE(i, TSize)
		{
			mItems[i] += val.mItems[i];
		}
	}
	void Substract(const PropertyUnit& val)
	{
		FOR_EACH_SIZE(i, TSize)
		{
			mItems[i] -= val.mItems[i];

		}
	}
	void Multiply(const PropertyUnit& val)
	{
		FOR_EACH_SIZE(i, TSize)
		{
			mItems[i] *= val.mItems[i];
		}
	}
	void Multiply(T factor)
	{
		FOR_EACH_SIZE(i, TSize)
		{
			mItems[i] *= factor;
		}
	}

	PropertyUnit& operator+=(const PropertyUnit& val) { Add(val); return *this; }
	PropertyUnit& operator-=(const PropertyUnit& val) { Substract(val); return *this; }
	PropertyUnit& operator*=(const PropertyUnit& val) { Multiply(val); return *this; }

	PropertyUnit& operator*=(T factor) { Multiply(factor); return *this; }
	PropertyUnit& operator/=(T factor) { Multiply(1.f / factor); return *this; }
protected:
	ArrayType mItems;
};

template<typename TIndex, typename T, size_t TSize, typename TCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const PropertyUnit<TIndex, T, TSize, TCompare> PropertyUnit<TIndex, T, TSize, TCompare>::Zero(0);

template<typename TIndex, typename T, size_t TSize, typename TCompare>
MEDUSA_WEAK_MULTIPLE_DEFINE const PropertyUnit<TIndex, T, TSize, TCompare> PropertyUnit<TIndex, T, TSize, TCompare>::One(1);

MEDUSA_END;
