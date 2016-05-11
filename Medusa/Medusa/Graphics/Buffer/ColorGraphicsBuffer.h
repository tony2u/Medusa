// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Buffer/ListGraphicsBuffer.h"
#include "Geometry/Color4.h"

MEDUSA_BEGIN;


class ColorGraphicsBuffer:public ListGraphicsBuffer<Color4F>
{
public:
	ColorGraphicsBuffer(uint size=256):ListGraphicsBuffer(GraphicsBufferType::Array,GraphicsBufferUsage::DynamicDraw,GraphicsDataType::Float,Color4F::Size,false,size){}
};

MEDUSA_END;