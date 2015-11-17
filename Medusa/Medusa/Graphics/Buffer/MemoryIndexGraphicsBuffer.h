// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Buffer/MemoryGraphicsBuffer.h"

MEDUSA_BEGIN;

template<typename T>
class MemoryIndexGraphicsBuffer:public MemoryGraphicsBuffer<T>
{
public:
	MemoryIndexGraphicsBuffer(GraphicsDataType dataType,GraphicsBufferUsage usageType,uint componentCount,bool isNormlized=false):MemoryGraphicsBuffer<T>(GraphicsBufferType::Elements,usageType,dataType,componentCount,isNormlized){}
};

MEDUSA_END;