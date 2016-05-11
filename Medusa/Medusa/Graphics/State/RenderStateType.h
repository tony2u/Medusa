// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;


enum class RenderStateType :uint
{
	None = 0,
	Count = 12,

	Array = 1 << 0,
	Blend = 1 << 1,
	DepthStencil = 1 << 2,
	ElementArrayBuffer = 1 << 3,
	Feature = 1 << 4,

	PixelStore = 1 << 5,
	Program = 1 << 6,
	RenderTarget = 1 << 7,
	Rasterizer = 1 << 8,
	Sampler = 1 << 9,
	Scissor = 1 << 10,
	ShaderUniform = 1 << 11

};

MEDUSA_END;
