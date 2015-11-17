// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/Buffer/RenderBuffer.h"
#include "Graphics/Render/Render.h"

MEDUSA_BEGIN;

RenderBuffer::RenderBuffer( GraphicsRenderBufferInternalFormat internalFormat,const Size2U& size )
	:mInternalFormat(internalFormat),mSize(size),mRenderBuffer(0)
{
	uint maxRenderBufferSize=Render::Instance().GetInteger(GraphicsIntegerName::MaxRenderBufferSize);
	MEDUSA_ASSERT_LESS_EQUAL(size.Width,maxRenderBufferSize,"");
	MEDUSA_ASSERT_LESS_EQUAL(size.Height,maxRenderBufferSize,"");
	Generate();
}

RenderBuffer::~RenderBuffer()
{
	Delete();
}


void RenderBuffer::Generate()
{
	if (mRenderBuffer==0)
	{
		mRenderBuffer=Render::Instance().GenRenderBuffer();
		Bind(true);
		Render::Instance().SetRenderBufferStorage(mInternalFormat,mSize);
		Bind(false);

	}
}

void RenderBuffer::Resize(const Size2U& val)
{
	mSize=val;
	if (mRenderBuffer!=0)
	{
		Bind(true);
		Render::Instance().SetRenderBufferStorage(mInternalFormat,mSize);
		Bind(false);

	}
}


void RenderBuffer::Delete()
{
	if (mRenderBuffer!=0)
	{
		Render::Instance().DeleteRenderBuffer(mRenderBuffer);
	}
}

void RenderBuffer::Bind( bool isCurrent )const
{
	if (isCurrent)
	{
		Render::Instance().BindRenderBuffer(mRenderBuffer);
	}
	else
	{
		Render::Instance().BindRenderBuffer(0);
	}
}

int RenderBuffer::GetRenderBufferParameter( GraphicsRenderBufferParameter parameter ) const
{
	Bind(true);
	int result=Render::Instance().GetRenderBufferParameter(parameter);
	Bind(false);
	return result;
}

MEDUSA_END;