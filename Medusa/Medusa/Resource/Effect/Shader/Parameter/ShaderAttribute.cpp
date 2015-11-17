// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Parameter/ShaderAttribute.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Graphics/Render/Render.h"
#include "Graphics/Buffer/IGraphicsBuffer.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

ShaderAttribute::ShaderAttribute( BaseProgramRenderPass* renderPass,uint index,StringRef name,GraphicsAttributeDataType dataType )
	:IShaderParameter(renderPass,index,name),mIsArrayEnabled(false),mDataType(dataType)
{

}

ShaderAttribute::~ShaderAttribute()
{

}

void ShaderAttribute::EnableArray( bool isEnabled )
{
	//Each generic vertex attribute array is initially disabled and isn't accessed when glDrawElements, glDrawRangeElements, glDrawArrays, glMultiDrawArrays, or glMultiDrawElements is called.
	//RETURN_IF(mIsArrayEnabled==isEnabled);
	mIsArrayEnabled=isEnabled;
	Render::Instance().EnableVertexAttributeArray(mLocation,mIsArrayEnabled);
}

void ShaderAttribute::Set( float x )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::Float,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttribute(mLocation,x);
	MarkAssigned();
}

void ShaderAttribute::Set( const Point2F& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::FloatVec2,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttribute(mLocation,pos);
	MarkAssigned();
}

void ShaderAttribute::Set( const Point3F& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::FloatVec3,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttribute(mLocation,pos);
	MarkAssigned();
}

void ShaderAttribute::Set( const Point4F& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::FloatVec4,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttribute(mLocation,pos);
	MarkAssigned();
}
void ShaderAttribute::SetArray1( const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::Float,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttributeArray1(mLocation,data);
	MarkAssigned();
}

void ShaderAttribute::SetArray2( const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::FloatVec2,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttributeArray2(mLocation,data);
	MarkAssigned();
}

void ShaderAttribute::SetArray3( const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::FloatVec3,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttributeArray3(mLocation,data);
	MarkAssigned();
}

void ShaderAttribute::SetArray4( const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsAttributeDataType::FloatVec4,"ErrorDataType");
	EnableArray(true);
	Render::Instance().SetVertexAttributeArray4(mLocation,data);
	MarkAssigned();
}

void ShaderAttribute::SetPointer( uint componentCount,GraphicsDataType type,bool isNormalized/*=false*/,uint stride/*=0*/,const void* data/*=nullptr*/ )
{
	switch(mDataType)
	{
	case GraphicsAttributeDataType::FloatVec2:
		MEDUSA_ASSERT(componentCount==2&&type==GraphicsDataType::Float,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatVec3:
		MEDUSA_ASSERT(componentCount==3&&type==GraphicsDataType::Float,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatVec4:
		MEDUSA_ASSERT(componentCount==4&&type==GraphicsDataType::Float,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatMat2:
		MEDUSA_ASSERT(componentCount==4&&type==GraphicsDataType::Float,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatMat3:
		MEDUSA_ASSERT(componentCount==9&&type==GraphicsDataType::Float,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatMat4:
		MEDUSA_ASSERT(componentCount==16&&type==GraphicsDataType::Float,"ErrorDataType");
		break;
	default:
		MEDUSA_ASSERT_FAILED("ErrorDataType");
		break;
	}

	EnableArray(true);
	Render::Instance().SetVertexAttributePointer(mLocation,componentCount,type,isNormalized,stride,data);
	MarkAssigned();
}

void ShaderAttribute::SetPointerFromBufferObject( const IGraphicsBuffer& bufferObject ,uint stride/*=0*/,int offset/*=0*/)
{
	switch(mDataType)
	{
	case GraphicsAttributeDataType::FloatVec2:
		MEDUSA_ASSERT(bufferObject.ComponentCount()==2,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatVec3:
		MEDUSA_ASSERT(bufferObject.ComponentCount()==3,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatVec4:
		MEDUSA_ASSERT(bufferObject.ComponentCount()==4,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatMat2:
		MEDUSA_ASSERT(bufferObject.ComponentCount()==4,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatMat3:
		MEDUSA_ASSERT(bufferObject.ComponentCount()==9,"ErrorDataType");
		break;
	case GraphicsAttributeDataType::FloatMat4:
		MEDUSA_ASSERT(bufferObject.ComponentCount()==16,"ErrorDataType");
		break;
	default:
		MEDUSA_ASSERT_FAILED("ErrorDataType");
		break;
	}

	EnableArray(true);
	Render::Instance().SetVertexAttributePointer(mLocation,bufferObject.ComponentCount(),bufferObject.DataType(),bufferObject.IsNormlized(),stride,(const void*)(intp)offset);
	MarkAssigned();
}


MEDUSA_END;