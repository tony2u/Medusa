// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"

MEDUSA_BEGIN;

class RTTIClass
{
public:
	RTTIClass(StringRef className, const std::type_info* typeinfo,const RTTIClass* baseClass = nullptr)
		:mName(className),mInfo(typeinfo),mBaseClass(baseClass)
	{

	}
	RTTIClass(StringRef className, const std::type_info& typeinfo, const RTTIClass* baseClass = nullptr)
		:mName(className), mInfo(&typeinfo), mBaseClass(baseClass)
	{

	}

	RTTIClass()
		:mInfo(nullptr),mBaseClass(nullptr)
	{

	}
	~RTTIClass() {}
	bool operator==(const RTTIClass& rhs)const { return mInfo == rhs.mInfo; }
	bool operator!=(const RTTIClass& rhs)const { return mInfo != rhs.mInfo; }
	bool operator<(const RTTIClass& rhs)const { return mInfo < rhs.mInfo; }
	bool operator>(const RTTIClass& rhs)const { return mInfo > rhs.mInfo; }
	bool operator<=(const RTTIClass& rhs)const { return mInfo <= rhs.mInfo; }
	bool operator>=(const RTTIClass& rhs)const { return mInfo >= rhs.mInfo; }

	RTTIClass& operator=(const RTTIClass& rhs) { mBaseClass = rhs.mBaseClass; mName = rhs.mName; mInfo = rhs.mInfo; return *this; }
public:
	
	const StringRef& Name()const { return mName; }
	const RTTIClass* BaseClass() const { return mBaseClass; }
	intp HashCode()const { return mInfo!=nullptr?mInfo->hash_code():0; }
	int GetInheritDistance(const RTTIClass* baseClass)const;
	int GetInheritDistance(const RTTIClass& baseClass)const;
	template<typename T> bool IsExactly()const { return *this == T::ClassStatic(); }
private:
	StringRef mName;
	const std::type_info* mInfo;
	const RTTIClass* mBaseClass=nullptr;
};


MEDUSA_END;