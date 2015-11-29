// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/Buffer/IGraphicsBuffer.h"
#include "Graphics/Render/Render.h"
#include "Graphics/State/ArrayBufferRenderState.h"
#include "Graphics/State/ElementArrayBufferRenderState.h"

#include "Graphics/State/RenderStateMachine.h"
#include "Graphics/Render/Render.h"
#include "Core/Log/Log.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;

IGraphicsBuffer::IGraphicsBuffer(GraphicsBufferType bufferType,GraphicsBufferUsage usageType,GraphicsDataType dataType,uint componentCount,bool isNormlized/*=false*/)
	:mUsageType(usageType),
	mDataType(dataType),mComponentCount(componentCount),mIsNormlized(isNormlized)
{
	mIsDataLoaded=false;
	mBufferSize=0;

	if (bufferType==GraphicsBufferType::Array)
	{
		mRenderState=new ArrayBufferRenderState();
	}
	else
	{
		mRenderState=new ElementArrayBufferRenderState();
	}
}


IGraphicsBuffer::~IGraphicsBuffer(void)
{
	DeleteObject();
	SAFE_RELEASE(mRenderState);
}


bool IGraphicsBuffer::Initialize()
{
	//GenObjcet();
	return true;
}


bool IGraphicsBuffer::Uninitialize()
{
	//DeleteObjcet();
	return true;
}


void IGraphicsBuffer::GenObject()
{
	if (mRenderState->Buffer() == 0)
	{
		uint buffer = Render::Instance().GenBuffer();
		RenderingStatics::Instance().IncreaseBuffer();
		mRenderState->SetBuffer(buffer);
	}
}

void IGraphicsBuffer::DeleteObject()
{
	if (mRenderState->Buffer() != 0)
	{
		Render::Instance().DeleteBuffer(mRenderState->Buffer());
		RenderingStatics::Instance().DecreaseBuffer();

		mRenderState->SetBuffer(0);
	}

}

void IGraphicsBuffer::Bind( bool val )
{

	if (val)
	{
		GenObject();

		RenderStateMachine::Instance().Push(mRenderState);
		//Render::Instance().BindBuffer(GetType(),renderState.GetBuffer());
	}
	else
	{
		RenderStateMachine::Instance().Pop(mRenderState);

		//Render::Instance().BindBuffer(GetType(),0);
	}
}


void IGraphicsBuffer::LoadBufferData( size_t size,void* data)
{
	Render::Instance().LoadBufferData(GetType(),static_cast<uint>(size),data,UsageType());
	RenderingStatics::Instance().CountGPUUploadSize(size);
	mIsDataLoaded=true;
	mBufferSize=size;
}

void IGraphicsBuffer::ModifyBufferSubData( size_t offset, size_t size, const void* data )
{
	Log::AssertFormat(offset+size<=mBufferSize,"offset:{}+size:{}={} > buffer size:{}",(uint)offset,(uint)size,(uint)(offset+size),(uint)mBufferSize);
	GenObject();
	Render::Instance().ModifyBufferSubData(GetType(),static_cast<uint>(offset),static_cast<uint>(size),data);
	RenderingStatics::Instance().CountGPUUploadSize(size);

}

void IGraphicsBuffer::SetDirtyRange( size_t minIndex,size_t maxIndex,size_t maxLimit )
{
	mDirtyRange.ExpandRange(minIndex,maxIndex);
	mDirtyRange.ShrinkMax(maxLimit);
}

void IGraphicsBuffer::LimitDirtyRange(size_t maxLimit)
{
	mDirtyRange.ExpandMin(maxLimit);
	mDirtyRange.ShrinkMax((uint)maxLimit);
}

void IGraphicsBuffer::CleanDirty()
{
	mDirtyRange.Reset();
}

void IGraphicsBuffer::Apply()
{
	Bind(true);
	RETURN_IF_FALSE(IsDirty());
	UpdateBufferData();
	CleanDirty();
}

void IGraphicsBuffer::Restore()
{
	Bind(false);
}

void IGraphicsBuffer::DrawArray( GraphicsDrawMode drawMode/*=GraphicsDrawMode::Triangles*/ ) const
{
	DrawArray(drawMode,0,Count());
}

void IGraphicsBuffer::DrawArray( GraphicsDrawMode drawMode,int first,uint count ) const
{
	Render::Instance().DrawArrays(drawMode,first,count);
}


void IGraphicsBuffer::DrawElements( GraphicsDrawMode drawMode/*=GraphicsDrawMode::Triangles*/ ) const
{
	DrawElements(drawMode,Count(),mDataType,nullptr);
}

void IGraphicsBuffer::DrawElements( GraphicsDrawMode drawMode,uint count,GraphicsDataType dataType,const void* indices ) const
{
	Render::Instance().DrawIndices(drawMode,count,dataType,indices);
}



MEDUSA_END;