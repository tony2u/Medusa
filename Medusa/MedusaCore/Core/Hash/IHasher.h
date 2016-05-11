// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Memory/MemoryData.h"
#include "HasherType.h"

MEDUSA_BEGIN;


class IHasher
{
public:
	virtual ~IHasher(void){}
public:
	virtual HasherType Type()const = 0;
	virtual void Process(const byte* input, size_t length)=0;
	virtual void Final()=0;
	virtual void Reset()=0;
	virtual HeapString ToString()const=0;

	void Process(const void* input, size_t length);
	void Process(const StringRef& str);
	void Process(const WStringRef& str);


	template<typename T>
	void Process(const TMemoryData<T>& data)
	{
		Process((byte*)data.Data(), data.ByteSize());
	}

};

MEDUSA_END;
