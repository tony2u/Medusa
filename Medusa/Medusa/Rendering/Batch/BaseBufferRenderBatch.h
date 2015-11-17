// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Rendering/Batch/IRenderBatch.h"
#include "Rendering/RenderableChangedFlags.h"
#include "Graphics/Buffer/VertexGraphicsBuffer.h"
#include "Graphics/Buffer/IndexGraphicsBuffer.h"
#include "Graphics/Buffer/TexCoordGraphicsBuffer.h"
#include "Graphics/Buffer/ColorGraphicsBuffer.h"
#include "Graphics/Buffer/NormalGraphicsBuffer.h"
MEDUSA_BEGIN;

class BaseBufferRenderBatch:public IRenderBatch
{
public:
	BaseBufferRenderBatch(RenderingStrategy renderingStrategy);
	virtual ~BaseBufferRenderBatch();

	virtual void ReleaseBuffer()override;

	virtual void Prepare() override;
	virtual void AddNode(IRenderable* node)override;
	virtual void RemoveNode(IRenderable* node) override;
	virtual void Clear() override;

	virtual bool Initialize() override;
	virtual bool Uninitialize()override;
	virtual void Apply() override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None)override;
	virtual void Restore() override;

	virtual void Print(HeapString& ioStr, uint level)override;
	virtual bool IsEmpty()const override { return mNodes.IsEmpty(); }

protected:

	virtual void AddNodeToBuffer(uint& refVertexIndex, uint& refIndexIndex,  IRenderable& node);
	virtual void UpdateNodeToBuffer(uint& refVertexIndex, uint& refIndexIndex,  IRenderable& node, RenderableChangedFlags changedFlags);
	virtual void TrimBuffer(size_t vertexIndex, size_t indexIndex);
	void PrintNodes()const;

protected:
	List<IRenderable*> mNodes;

	VertexGraphicsBuffer mVertexBufferObject;
	TexCoordGraphicsBuffer mTexcoordBufferObject;
	ColorGraphicsBuffer mColorBufferObject;
	NormalGraphicsBuffer mNormalBufferObject;
	IndexGraphicsBuffer mIndexBufferObject;
};


MEDUSA_END;