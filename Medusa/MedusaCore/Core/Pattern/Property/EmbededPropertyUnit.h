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

template<typename TDevided, typename T, size_t TSize>
class EmbededPropertyUnit
{
public:
	const static EmbededPropertyUnit Zero;
	const static EmbededPropertyUnit One;

	typedef Array<T, TSize> ArrayType;
	typedef List<T> ListType;
	typedef Dictionary<uint, T> DictionaryType;
public:
	EmbededPropertyUnit(T val = 0.f)
	{
		T* p = MutableItems();
		Memory::Set(p, val, TSize);
	}
	EmbededPropertyUnit(const ArrayType& item)
	{
		Set(item);
	}
	EmbededPropertyUnit(const ListType& item)
	{
		Set(item);
	}
	EmbededPropertyUnit(const DictionaryType& item)
	{
		Set(item);
	}

	EmbededPropertyUnit(const EmbededPropertyUnit& val)
	{
		Set(val);
	}
	EmbededPropertyUnit& operator=(const EmbededPropertyUnit& val)
	{
		Set(val);
		return *this;
	}

public:
	ArrayType ToArray()const
	{
		EmbededPropertyUnit::ListType result;
		CopyTo(result);
		return result;
	}

	ListType ToList()const
	{
		EmbededPropertyUnit::ListType result;
		CopyTo(result);
		return result;
	}
	DictionaryType ToDictionary()const
	{
		EmbededPropertyUnit::DictionaryType result;
		CopyTo(result);
		return result;
	}
	DictionaryType ToDictionaryExcludeZero()const
	{
		EmbededPropertyUnit::DictionaryType result;
		CopyToExcludeZero(result);
		return result;
	}

	void CopyTo(ArrayType& outArray)const
	{
		const T* p = Items();
		FOR_EACH_SIZE(i, TSize)
		{
			outArray[i] = p[i];
		}
	}
	void CopyTo(ListType& outList)const
	{
		outList.Clear();
		const T* p = Items();
		FOR_EACH_SIZE(i, TSize)
		{
			outList.Add(p[i]);
		}

	}
	void CopyTo(DictionaryType& outDict)const
	{
		outDict.Clear();
		const T* p = Items();
		FOR_EACH_SIZE(i, TSize)
		{
			outDict.Add(i, p[i]);
		}
	}
	void CopyToExcludeZero(DictionaryType& outDict)const
	{
		outDict.Clear();
		const T* p = Items();

		FOR_EACH_SIZE(i, TSize)
		{
			if (!Math::IsZero(p[i]))
			{
				outDict.Add(i, p[i]);
			}
		}
	}

	void PrintAll()const
	{
		const T* p = Items();

		HeapString str("EmbededPropertyUnit==>\t");
		FOR_EACH_SIZE(i, TSize)
		{
			uint type = (uint)i;
			float val = (float)p[i];
			str.AppendFormat("{}:{}\n",type,val);
		}
		Log::Info(str);
	}
	void PrintExcludeZero()const
	{
		const T* p = Items();

		HeapString str("EmbededPropertyUnit==>\t");
		FOR_EACH_SIZE(i, TSize)
		{
			uint type = (uint)i;
			float val = (float)p[i];
			if (!Math::IsZero(val))
			{
				str.AppendFormat("{}:{}\n",type, val);
			}
		}
		Log::Info(str);
	}
public:
	T Sum()const
	{
		T sum = (T)0;
		const T* p = Items();

		FOR_EACH_SIZE(i, TSize)
		{
			sum += p[i];
		}
		return sum;
	}
	T Get(uint index)const
	{
		const T* p = Items();
		return p[(uint)index];
	}
	T& Mutable(uint index)
	{
		T* p = MutableItems();
		return p[(uint)index];
	}

	void Set(const ArrayType& item)
	{
		Memory::SafeCopy(MutableItems(), TSize, item.Items(), TSize);
	}
	void Set(const ListType& item)
	{
		Log::Assert(item.Count() == TSize, "Invalid item");
		Memory::SafeCopy(MutableItems(), TSize, item.Items(), TSize);
	}
	void Set(const DictionaryType& item)
	{
		for (auto i : item)
		{
			uint type = i.Key;
			T val = i.Value;
			SetSingle(type, val);
		}
	}
	void Set(const EmbededPropertyUnit& val)
	{
		Memory::SafeCopy(MutableItems(), TSize, val.Items(), TSize);
	}

	void SetSingle(uint type, T val)
	{
		T* p = MutableItems();
		p[(uint)type] = val;
	}

	void Add(const EmbededPropertyUnit& val)
	{
		T* p = MutableItems();
		const T* q = val.Items();
		FOR_EACH_SIZE(i, TSize)
		{
			p[i] += q[i];
		}
	}
	void Substract(const EmbededPropertyUnit& val)
	{
		T* p = MutableItems();
		const T* q = val.Items();
		FOR_EACH_SIZE(i, TSize)
		{
			p[i] -= q[i];
		}
	}
	void Multiply(const EmbededPropertyUnit& val)
	{
		T* p = MutableItems();
		const T* q = val.Items();
		FOR_EACH_SIZE(i, TSize)
		{
			p[i] *= q[i];
		}
	}
	void Multiply(T factor)
	{
		T* p = MutableItems();
		FOR_EACH_SIZE(i, TSize)
		{
			p[i] *= factor;
		}
	}

	EmbededPropertyUnit& operator+=(const EmbededPropertyUnit& val) { Add(val); return *this; }
	EmbededPropertyUnit& operator-=(const EmbededPropertyUnit& val) { Substract(val); return *this; }
	EmbededPropertyUnit& operator*=(const EmbededPropertyUnit& val) { Multiply(val); return *this; }
	EmbededPropertyUnit& operator*=(T factor) { Multiply(factor); return *this; }
	EmbededPropertyUnit& operator/=(T factor) { Multiply(1.f / factor); return *this; }

	EmbededPropertyUnit operator+(const EmbededPropertyUnit& val)const { EmbededPropertyUnit result(*this); result.Add(val); return result; }
	EmbededPropertyUnit operator-(const EmbededPropertyUnit& val)const { EmbededPropertyUnit result(*this); result.Substract(val); return result; }
	EmbededPropertyUnit operator*(const EmbededPropertyUnit& val) const { EmbededPropertyUnit result(*this); result.Multiply(val); return result; }
	EmbededPropertyUnit operator*(T factor)const { EmbededPropertyUnit result(*this); result.Multiply(factor); return result; }
	EmbededPropertyUnit operator/(T factor) const { EmbededPropertyUnit result(*this); result.Multiply(1.f / factor); return result; }
protected:
	const T* Items()const { return (const T*)this; }
	T* MutableItems() { return (T*)this; }
};

template<typename TDevided, typename T, size_t TSize>
MEDUSA_WEAK_MULTIPLE_DEFINE const EmbededPropertyUnit<TDevided, T, TSize> EmbededPropertyUnit<TDevided, T, TSize>::Zero(0);

template<typename TDevided, typename T, size_t TSize>
MEDUSA_WEAK_MULTIPLE_DEFINE const EmbededPropertyUnit<TDevided, T, TSize> EmbededPropertyUnit<TDevided, T, TSize>::One(1);

MEDUSA_END;
