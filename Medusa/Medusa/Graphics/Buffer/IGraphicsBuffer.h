// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/BaseBufferRenderState.h"
#include "Core/Geometry/Range.h"
#include "Core/Pattern/IInitializable.h"
#include "BufferObjectChangeFlags.h"


MEDUSA_BEGIN;

class IGraphicsBuffer:public IInitializable
{
public:
	IGraphicsBuffer(GraphicsBufferType bufferType,GraphicsBufferUsage usageType,GraphicsDataType dataType,uint componentCount,bool isNormlized=false);
	virtual ~IGraphicsBuffer(void);
public:
	uint ComponentCount() const { return mComponentCount; }
	GraphicsDataType DataType() const { return mDataType; }
	GraphicsBufferUsage UsageType() const { return mUsageType; }
	void SetUsageType(GraphicsBufferUsage val) { mUsageType = val; }
	bool IsNormlized() const { return mIsNormlized; }
	void SetIsNormlized(bool val) { mIsNormlized = val; }

	virtual bool Initialize();
	virtual bool Uninitialize();
	void Apply();
	void Restore();


	void CleanDirty();
	bool IsDirty(){return !mDirtyRange.IsEmpty();}
	void SetDirtyRange(size_t minIndex,size_t maxIndex,size_t maxLimit);
	void LimitDirtyRange(size_t maxLimit);


	virtual uint Count()const=0;

	BaseBufferRenderState* MutableRenderState(){return mRenderState;}
	const BaseBufferRenderState* RenderState()const{return mRenderState;}
	GraphicsBufferType GetType()const{return mRenderState->BufferType();}

	virtual bool IsAvailableFor(size_t newCount)const{return true;}

	virtual void DrawArray(GraphicsDrawMode drawMode=GraphicsDrawMode::Triangles)const;
	virtual void DrawArray(GraphicsDrawMode drawMode,int first,uint count)const;

	virtual void DrawElements(GraphicsDrawMode drawMode=GraphicsDrawMode::Triangles)const;
	virtual void DrawElements(GraphicsDrawMode drawMode,uint count,GraphicsDataType dataType,const void* indices)const;
protected:
	void GenObject();
	void DeleteObject();
	void Bind(bool val);

	void LoadBufferData(size_t size,void* data);
	void ModifyBufferSubData(size_t offset, size_t size, const void* data);

	virtual void UpdateBufferData()=0;
	RangeS mDirtyRange;

	bool mIsDataLoaded;
	BaseBufferRenderState* mRenderState;

	GraphicsBufferUsage mUsageType;
	GraphicsDataType mDataType;
	uint mComponentCount;

	bool mIsNormlized;
	size_t mBufferSize;
};

MEDUSA_END;