// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/GraphicsTypes.h"
#include "Core/Collection/Dictionary.h"
#include "Resource/Texture/ITexture.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;
class FrameBuffer
{
public:
	FrameBuffer();
	virtual ~FrameBuffer();

public:
	void Bind(bool isCurrent)const;
	void AttachRenderBuffer(GraphicsAttachment attachment, RenderBuffer* renderBuffer);
	void AttachTexture(GraphicsAttachment attachment, GraphicsTextureTarget textureTarget, const Share<ITexture>& texture, int level);

	void AttachDepthStencil(GraphicsRenderBufferInternalFormat depthFormat, GraphicsRenderBufferInternalFormat stencilFormat, const Size2U& size);

	RenderBuffer* GetRenderBuffer(GraphicsAttachment attachment);


	RenderBuffer* DetachRenderBuffer(GraphicsAttachment attachment);
	Share<ITexture> DetachTexture(GraphicsAttachment attachment);

	bool Validate()const;
	GraphicsBufferComponentMask ClearMask() const { return mClearMask; }
	uint FrameBufferId() const { return mFrameBuffer; }
	bool IsAttached()const { return !mRenderBuffers.IsEmpty() || !mTextures.IsEmpty(); }

	virtual void Resize(const Size2U& val);
	void Generate();
	void Delete();
protected:
	void UpdateClearMask(GraphicsAttachment attachment, bool isAttach);
protected:
	uint mFrameBuffer;
	GraphicsBufferComponentMask mClearMask;

	Dictionary<GraphicsAttachment, RenderBuffer*, SafeEnumHashCoder> mRenderBuffers;
	Dictionary<GraphicsAttachment, Share<ITexture>, SafeEnumHashCoder> mTextures;


};


MEDUSA_END;