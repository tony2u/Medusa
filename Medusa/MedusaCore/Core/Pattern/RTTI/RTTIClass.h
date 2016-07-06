// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Pattern/INonCopyable.h"

MEDUSA_BEGIN;

class RTTIClass:public INonCopyable
{
public:
	constexpr RTTIClass(const char* className, const std::type_info* typeinfo, const RTTIClass* baseClass = nullptr)
		:mName(className), mInfo(typeinfo), mBaseClass(baseClass)
	{

	}
	constexpr RTTIClass(const char* className, const std::type_info& typeinfo, const RTTIClass* baseClass = nullptr)
		: mName(className), mInfo(&typeinfo), mBaseClass(baseClass)
	{

	}

	constexpr RTTIClass()
		: mInfo(nullptr), mBaseClass(nullptr)
	{

	}
	~RTTIClass() = default;
	bool operator==(const RTTIClass& rhs)const { return mInfo == rhs.mInfo; }
	bool operator!=(const RTTIClass& rhs)const { return mInfo != rhs.mInfo; }
	bool operator<(const RTTIClass& rhs)const { return mInfo < rhs.mInfo; }
	bool operator>(const RTTIClass& rhs)const { return mInfo > rhs.mInfo; }
	bool operator<=(const RTTIClass& rhs)const { return mInfo <= rhs.mInfo; }
	bool operator>=(const RTTIClass& rhs)const { return mInfo >= rhs.mInfo; }

public:

	const StringRef& Name()const { return mName; }
	const RTTIClass* BaseClass() const { return mBaseClass; }
	intp HashCode()const { return mInfo != nullptr ? mInfo->hash_code() : 0; }
	int GetInheritDistance(const RTTIClass* baseClass)const;
	int GetInheritDistance(const RTTIClass& baseClass)const;
	template<typename T> bool IsExactly()const { return *this == T::ClassStatic(); }
private:
	StringRef mName;
	const std::type_info* mInfo = nullptr;
	const RTTIClass* mBaseClass = nullptr;
};


MEDUSA_END;