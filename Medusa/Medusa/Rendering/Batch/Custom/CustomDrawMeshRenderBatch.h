// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Rendering/Batch/IRenderBatch.h"

MEDUSA_BEGIN;

class CustomDrawMeshRenderBatch:public IRenderBatch
{
public:
	CustomDrawMeshRenderBatch();
	virtual ~CustomDrawMeshRenderBatch();
	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

	virtual void AddNode(IRenderable* node)override;
	virtual void RemoveNode(IRenderable* node)override;
	virtual bool IsAvailableFor(size_t newVertexCount, size_t newIndexCount)const override { return false; }
	virtual bool IsAvailableFor(const IRenderable& node)const override { return mNode == nullptr; }

	virtual bool IsEmpty()const override {return mNode!=nullptr;}

	virtual void Clear() override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None) override;
	
	virtual void Apply() override;
	virtual void Restore() override;

	virtual void Prepare()override;
	virtual bool Update()override;
	virtual void Print(HeapString& ioStr, uint level)override;

private:
	IRenderable* mNode;
};


MEDUSA_END;