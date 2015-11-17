// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
MEDUSA_BEGIN;

class QuadIndexGraphicsBuffer:public IndexGraphicsBuffer
{
public:
	QuadIndexGraphicsBuffer(uint size=256):IndexGraphicsBuffer(size){}
	virtual ~QuadIndexGraphicsBuffer(void){}
protected:
	virtual void GenerateData(size_t beginIndex);
	void GenerateDataHelper(size_t beginIndex);
	
#ifdef MEDUSA_PRE_GENERATED_INDEX_ENABLED

	const static uint PreGeneratedIndicesQuadCount=10922;
	const static uint PreGeneratedIndicesCount=10922*6;


	const static ushort PreGeneratedIndicesUShort[10922*6];
	const static uint PreGeneratedIndicesUInt[10922*6];
#endif

};


MEDUSA_END;