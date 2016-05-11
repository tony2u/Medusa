// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/Memory/MemoryData.h"
#include "ISirenWriter.h"

MEDUSA_BEGIN;

class ISirenSizeCounter:public ISirenWriter
{
public:
	virtual ~ISirenSizeCounter() = 0;
public:
	uint Size() const { return mSize; }
protected:
	uint mSize = 0;
};

MEDUSA_END;