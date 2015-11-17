// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Buffer/ListGraphicsBuffer.h"
#include "Core/Geometry/Point3.h"


MEDUSA_BEGIN;


class VertexGraphicsBuffer:public ListGraphicsBuffer<Point3F>
{
public:
	VertexGraphicsBuffer(uint size=256):ListGraphicsBuffer(GraphicsBufferType::Array,GraphicsBufferUsage::DynamicDraw,GraphicsDataType::Float,Point3F::Size,false,size){}
};

MEDUSA_END;