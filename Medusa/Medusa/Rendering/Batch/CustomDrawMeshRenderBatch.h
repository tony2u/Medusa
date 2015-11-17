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
	
	virtual bool IsEmpty()const override {return mNode!=nullptr;}

	virtual void Clear() override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None) override;
	
	virtual void Apply() override;
	virtual void Restore() override;

	virtual void PrepareDraw();
	virtual void FinishDraw();

private:
	IRenderable* mNode;
};


MEDUSA_END;