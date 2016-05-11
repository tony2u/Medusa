// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/variant.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Utility/DateTime.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;



class ApplePropertyListNode:public INonCopyable<ApplePropertyListNode>
{
public:
	struct BinaryHeader
	{
		int ObjectIntByteSize;
		List<int> Offsets;
	};

	using NodeList = List<ApplePropertyListNode*>;
	using NodeDict = Dictionary<HeapString, ApplePropertyListNode*>;
	using DataType = variant<bool, int64, double, DateTime, MemoryData, HeapString, NodeList, NodeDict>;
public:
	ApplePropertyListNode();
	~ApplePropertyListNode(void);

	bool Parse(const pugi::xml_node& node);
	bool Parse(MemoryStream& stream, const BinaryHeader& header, int objIndex);

	void Clear();
public:
	const ApplePropertyListNode& operator[](StringRef name)const;
	const ApplePropertyListNode* Find(StringRef name)const;
	bool Has(StringRef name)const { return Find(name) != nullptr; }


public:
	bool ToBool()const { return To<bool>(); }
	int ToInt()const { return (int)To<int64>(); }
	int64 ToInt64()const { return To<int64>(); }
	float ToFloat()const { return (float)To<double>(); }
	double ToDouble()const { return To<double>(); }
	const DateTime& ToDate()const { return To<DateTime>(); }
	const MemoryData& ToData()const { return To<MemoryData>(); }
	StringRef ToString()const { return To<HeapString>().ToString(); }
	const NodeList& ToList()const { return To<NodeList>(); }
	const NodeDict& ToDict()const { return To<NodeDict>(); }

	template<typename T>
	const T& To()const { return mData.get<T>(); }

public:
	bool ToBool(StringRef name)const { return (*this)[name].ToBool(); }
	int ToInt(StringRef name)const { return (*this)[name].ToInt(); }
	int64 ToInt64(StringRef name)const { return (*this)[name].ToInt64(); }
	float ToFloat(StringRef name)const { return (*this)[name].ToFloat(); }
	double ToDouble(StringRef name)const { return (*this)[name].ToDouble(); }
	const DateTime& ToDate(StringRef name)const { return (*this)[name].ToDate(); }
	const MemoryData& ToData(StringRef name)const { return (*this)[name].ToData(); }
	StringRef ToString(StringRef name)const { return (*this)[name].ToString(); }
	const NodeList& ToList(StringRef name)const { return (*this)[name].ToList(); }
	const NodeDict& ToDict(StringRef name)const { return (*this)[name].ToDict(); }

	template<typename T>
	const T& To(StringRef name)const { return (*this)[name].To<T>(); }

public:
	bool Optional(bool optional)const { return OptionalT<bool>(optional); }
	int Optional(int optional)const { return (int)OptionalT<int64>(optional); }
	int64 Optional(int64 optional)const { return OptionalT<int64>(optional); }
	float Optional(float optional)const { return (float)OptionalT<double>(optional); }
	double Optional(double optional)const { return OptionalT<double>(optional); }
	const DateTime& Optional(const DateTime& optional)const { return OptionalT<DateTime>(optional); }
	const MemoryData& Optional(const MemoryData& optional)const { return OptionalT<MemoryData>(optional); }
	StringRef Optional(const StringRef& optional)const { return mData.is<HeapString>() ? mData.get<HeapString>().ToString() : optional; }

	template<typename T>
	const T& OptionalT(const T& optional)const { return mData.get<T>(optional); }

public:
	bool Optional(StringRef name, bool optional)const { return OptionalT(name,optional); }
	int Optional(StringRef name, int optional)const { return (int)OptionalT(name, (int64)optional); }
	int64 Optional(StringRef name, int64 optional)const { return OptionalT(name, optional); }
	float Optional(StringRef name, float optional)const { return (float)OptionalT(name, (double)optional); }
	double Optional(StringRef name, double optional)const { return OptionalT(name, optional); }
	const DateTime& Optional(StringRef name, const DateTime& optional)const { return OptionalT(name, optional); }
	const MemoryData& Optional(StringRef name, const MemoryData& optional)const { return OptionalT(name, optional); }
	StringRef Optional(StringRef name, const StringRef& optional)const 
	{ 
		const ApplePropertyListNode* node = Find(name);
		if (node != nullptr)
		{
			return node->Optional(optional);
		}
		return optional;
	}


	template<typename T>
	const T& OptionalT(StringRef name, const T& optional)const 
	{
		const ApplePropertyListNode* node = Find(name);
		if (node!=nullptr)
		{
			return node->OptionalT(optional);
		}
		return optional;
	}
protected:
	DataType mData;
};

MEDUSA_END;
