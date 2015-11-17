// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Buffer/IGraphicsBuffer.h"
#include "Graphics/Render/Render.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

template<typename T>
class MemoryGraphicsBuffer:public IGraphicsBuffer
{
public:
	using IGraphicsBuffer::LoadBufferData;
public:
	MemoryGraphicsBuffer(GraphicsBufferType bufferType,GraphicsBufferUsage usageType,GraphicsDataType dataType,uint componentCount,bool isNormlized=false):IGraphicsBuffer(bufferType,usageType,dataType,componentCount,isNormlized){}
	virtual ~MemoryGraphicsBuffer(void){}

public:
	virtual uint Count()const{return static_cast<uint>(mData.Size());}

	void Clear()
	{
		mData.Release();
	}

	bool IsEmpty()const{return mData.IsNull();}
	void SetData(MemoryData<T> val) { mData = val; SetDirtyRange(0,mData.Size()-1,mData.Size()-1);}
	void SetDataAndSize(T* data,size_t size){mData.ForceSetDataAndSize(data,size);SetDirtyRange(0,mData.Size()-1,mData.Size()-1);}

	virtual void UpdateBufferData()
	{
		LoadBufferData(mData.ByteSize(),mData.MutableData());
	}
protected:
	MemoryData<T> mData;
};

MEDUSA_END;