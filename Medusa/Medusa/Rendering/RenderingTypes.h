// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;



enum class RenderingPriority
{
	Background0 = 0,
	Background1,
	Background2,
	Background3,
	Background4,
	Background5,
	Background6,
	Background7,
	Background8,
	Background9,

	Main0,
	Main1,
	Main2,
	Main3,
	Main4,
	Main5,
	Main6,
	Main7,
	Main8,
	Main9,

	Foreground0,
	Foreground1,
	Foreground2,
	Foreground3,
	Foreground4,
	Foreground5,
	Foreground6,
	Foreground7,
	Foreground8,
	Foreground9,

	Count
};

/*
Managed rendering:
Mix:batch rendering multiple Node's mesh,transform mesh's data 
Single:render one Mesh per time,do not transform Mesh data
*/
enum class RenderingStrategy
{
	MultipleDynamicBatch,
	MultipleStaticBatch,
	SingleDynamicBatch,
	SingleStaticBatch,
	CustomDrawNode,
	CustomDrawMesh,
	InstanceAPIBatch,
	Count
};


enum class RenderingStep { RenderTarget, RenderPass, Material, State, DrawMode, Batch };


enum class RenderQueueChangedFlags
{
	NewNode,
	MeshChanged,
	VisibleChanged,
};





MEDUSA_END;