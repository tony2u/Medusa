// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/IInitializable.h"
#include "Rendering/RenderingTypes.h"
MEDUSA_BEGIN;

/*

nodes->get model->get meshes->pack to batch mesh
*/
struct IRenderGroup:public IInitializable
{
public:
	IRenderGroup() {}
	virtual ~IRenderGroup() {}
public:
	virtual bool Add(IRenderBatch* batch) { return false; }
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None) = 0;
	virtual void Print(HeapString& ioStr, uint level) {}

};


MEDUSA_END;