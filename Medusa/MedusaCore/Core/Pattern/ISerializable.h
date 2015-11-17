// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

class ISerializable
{
public:
	virtual MemoryByteData Serialize(const MemoryByteData& data)const = 0;
	virtual MemoryByteData Unserialize(const MemoryByteData& data)const = 0;
};

MEDUSA_END;