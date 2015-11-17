// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/System/PublishTarget.h"

MEDUSA_BEGIN;

class FileIdRef
{
public:
	FileIdRef():Order(0){}
	FileIdRef(const StringRef& name, uint order=0):Name(name),Order(order){}

	template<uint TSize>
	FileIdRef(const StackString<TSize>& name,uint order=0):Name(name),Order(order){}

	FileIdRef(const HeapString& name,uint order=0):Name(name),Order(order){}
	FileIdRef(const char* name,uint order=0):Name(name),Order(order){}
	FileIdRef(const std::basic_string<char, std::char_traits<char>, std::allocator<char> >& str,uint order=0):Name(str),Order(order){}

	~FileIdRef(){}
	bool operator<(const FileIdRef& fileId)const;
	void operator=(const FileIdRef& fileId){Name = fileId.Name;Order = fileId.Order;}
	bool operator==(const FileIdRef& fileId)const{return Name==fileId.Name && Order == fileId.Order;}
	bool operator!=(const FileIdRef& fileId)const{return Name!=fileId.Name || Order != fileId.Order;}
	bool IsValid()const{return !Name.IsEmpty();}

	HeapString ToString(const PublishTarget& tag = PublishTarget::MatchAll)const;

	intp HashCode()const
	{
		return Name.HashCode()^Order;
	}
public:
	StringRef Name;	//performance hit
	uint Order;
	const static FileIdRef Empty;
};

MEDUSA_END;
