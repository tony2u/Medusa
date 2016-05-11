// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Size2.h"

MEDUSA_BEGIN;
class RenderBuffer
{
public:
	RenderBuffer(GraphicsRenderBufferInternalFormat internalFormat,const Size2U& size);
	virtual ~RenderBuffer();
public:
	GraphicsRenderBufferInternalFormat InternalFormat() const { return mInternalFormat; }
	void SetInternalFormat(GraphicsRenderBufferInternalFormat val) { mInternalFormat = val; }
	const Size2U& Size() const { return mSize; }
	void SetSize(const Size2U& val) { mSize = val; }

	void Bind(bool isCurrent)const;
	int GetRenderBufferParameter(GraphicsRenderBufferParameter parameter)const;
	uint Id() const { return mRenderBuffer; }

	virtual void Resize(const Size2U& val);

	void Generate();
	void Delete();

private:
	GraphicsRenderBufferInternalFormat mInternalFormat;
	Size2U mSize;
	uint mRenderBuffer;


};


MEDUSA_END;