// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Buffer/ListGraphicsBuffer.h"


MEDUSA_BEGIN;

#ifdef MEDUSA_GLES

class IndexGraphicsBuffer:public ListGraphicsBuffer<ushort,Math::UShortMaxValue>
{
public:
	IndexGraphicsBuffer(uint size=256):ListGraphicsBuffer(GraphicsBufferType::Elements,GraphicsBufferUsage::DynamicDraw,GraphicsDataType::UShort,1,false,size){}
	virtual ~IndexGraphicsBuffer(void){}

	void AdjustData(size_t fromIndex,short delta);
};

#else
class IndexGraphicsBuffer:public ListGraphicsBuffer<uint32,Math::UIntMaxValue>
{
public:
	IndexGraphicsBuffer(uint size=256):ListGraphicsBuffer(GraphicsBufferType::Elements,GraphicsBufferUsage::DynamicDraw,GraphicsDataType::UInt,1,false,size){}
	virtual ~IndexGraphicsBuffer(void){}
	void AdjustData(size_t fromIndex, int delta);
};

#endif

MEDUSA_END;