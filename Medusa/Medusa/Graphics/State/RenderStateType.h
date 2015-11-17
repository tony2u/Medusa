// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;


enum class RenderStateType :uint
{
	None=0,
	Count = 11,

	Array = 1,
	Blend = 2,
	DepthStencil = 4,
	ElementArrayBuffer = 8,
	Feature = 16,

	PixelStore = 32,
	Program = 64,
	RenderTarget=128,
	Rasterizer = 256,
	Sampler = 512,
	Scissor = 1024,

};

MEDUSA_END;
