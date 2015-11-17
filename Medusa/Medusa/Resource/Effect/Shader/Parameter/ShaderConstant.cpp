// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstant.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Graphics/Render/Render.h"
#include "Core/Geometry/Matrix3.h"
#include "Core/Geometry/Matrix.h"
#include "Core/Log/Log.h"
#include "Core/Geometry/Color3.h"
#include "Core/Geometry/Color4.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

ShaderConstant::ShaderConstant( BaseProgramRenderPass* renderPass,int location,StringRef name ,GraphicsUniformDataType dataType)
	:IShaderParameter(renderPass,location,name),mDataType(dataType)
{
	Memory::SetZero(mIntArray);
	Memory::SetZero(mFloatArray);

	mIntDataCount=0;
	mIntData=nullptr;
	mFloatDataCount=0;
	mFloatData=nullptr;
	mIsTransposed=false;

}

ShaderConstant::~ShaderConstant()
{

}

void ShaderConstant::Set( int x )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::Bool
		||mDataType==GraphicsUniformDataType::Int
		||mDataType==GraphicsUniformDataType::Sampler2D
		||mDataType==GraphicsUniformDataType::SamplerCube,"ErrorDataType");

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0]==x);
#endif
	Render::Instance().SetUniform(mLocation,x);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0]=x;
#endif

}

void ShaderConstant::Set( const Point2I& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec2||mDataType==GraphicsUniformDataType::BoolVec2,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0]==pos.X&&mIntArray[1]==pos.Y);
#endif

	Render::Instance().SetUniform(mLocation,pos.X,pos.Y);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0]=pos.X;
	mIntArray[1]=pos.Y;
#endif
}

void ShaderConstant::Set( const Point3I& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec3||mDataType==GraphicsUniformDataType::BoolVec3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0]==pos.X&&mIntArray[1]==pos.Y&&mIntArray[2]==pos.Z);
#endif
	Render::Instance().SetUniform(mLocation,pos.X,pos.Y,pos.Z);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0]=pos.X;
	mIntArray[1]=pos.Y;
	mIntArray[2]=pos.Z;
#endif
}

void ShaderConstant::Set( const Point4I& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec4||mDataType==GraphicsUniformDataType::BoolVec4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0]==pos.X&&mIntArray[1]==pos.Y&&mIntArray[2]==pos.Z&&mIntArray[3]==pos.W);
#endif
	Render::Instance().SetUniform(mLocation,pos.X,pos.Y,pos.Z,pos.W);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0]=pos.X;
	mIntArray[1]=pos.Y;
	mIntArray[2]=pos.Z;
	mIntArray[3]=pos.W;
#endif
}

void ShaderConstant::Set( const Color3B& color )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec3||mDataType==GraphicsUniformDataType::BoolVec3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0]==(int)color.R&&mIntArray[1]==(int)color.G&&mIntArray[2]==(int)color.B);
#endif
	Render::Instance().SetUniform(mLocation,color.R,color.G,color.B);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0]=color.R;
	mIntArray[1]=color.G;
	mIntArray[2]=color.B;

#endif
}

void ShaderConstant::Set( const Color4B& color )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec4||mDataType==GraphicsUniformDataType::BoolVec4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0]==(int)color.R&&mIntArray[1]==(int)color.G&&mIntArray[2]==(int)color.B&&mIntArray[3]==color.A);
#endif
	Render::Instance().SetUniform(mLocation,color.R,color.G,color.B,color.A);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0]=color.R;
	mIntArray[1]=color.G;
	mIntArray[2]=color.B;
	mIntArray[3]=color.A;
#endif
}

void ShaderConstant::Set( float x )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::Float,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0],x));
#endif

	Render::Instance().SetUniform(mLocation,x);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0]=x;
#endif
}

void ShaderConstant::Set( const Point2F& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec2,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0],pos.X)&&Math::IsEqual(mFloatArray[1],pos.Y));
#endif
	Render::Instance().SetUniform(mLocation,pos.X,pos.Y);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0]=pos.X;
	mFloatArray[1]=pos.Y;
#endif
}

void ShaderConstant::Set( const Point3F& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0],pos.X)&&Math::IsEqual(mFloatArray[1],pos.Y)&&Math::IsEqual(mFloatArray[2],pos.Z));
#endif
	Render::Instance().SetUniform(mLocation,pos.X,pos.Y,pos.Z);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0]=pos.X;
	mFloatArray[1]=pos.Y;
	mFloatArray[2]=pos.Z;
	
#endif
}

void ShaderConstant::Set( const Point4F& pos )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0],pos.X)&&Math::IsEqual(mFloatArray[1],pos.Y)&&Math::IsEqual(mFloatArray[2],pos.Z)&&Math::IsEqual(mFloatArray[3],pos.W));
#endif
	Render::Instance().SetUniform(mLocation,pos.X,pos.Y,pos.Z,pos.W);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0]=pos.X;
	mFloatArray[1]=pos.Y;
	mFloatArray[2]=pos.Z;
	mFloatArray[3]=pos.W;
#endif
}

void ShaderConstant::Set( const Color3F& color )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0],color.R)&&Math::IsEqual(mFloatArray[1],color.G)&&Math::IsEqual(mFloatArray[2],color.B));
#endif
	Render::Instance().SetUniform(mLocation,color.R,color.G,color.B);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0]=color.R;
	mFloatArray[1]=color.G;
	mFloatArray[2]=color.B;
#endif
}

void ShaderConstant::Set( const Color4F& color )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0],color.R)&&Math::IsEqual(mFloatArray[1],color.G)&&Math::IsEqual(mFloatArray[2],color.B)&&Math::IsEqual(mFloatArray[3],color.A));
#endif

	Render::Instance().SetUniform(mLocation,color.R,color.G,color.B,color.A);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0]=color.R;
	mFloatArray[1]=color.G;
	mFloatArray[2]=color.B;
	mFloatArray[3]=color.A;
#endif
}

void ShaderConstant::SetArray1( uint count,const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::Float,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data);
#endif

	Render::Instance().SetUniformArray1(mLocation,count,data);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
#endif
}

void ShaderConstant::SetArray1( uint count,const int* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::Int||mDataType==GraphicsUniformDataType::Bool,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntDataCount==count&&mIntData==data);
#endif
	Render::Instance().SetUniformArray1(mLocation,count,data);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntDataCount=count;
	mIntData=data;
#endif
}

void ShaderConstant::SetArray2( uint count,const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec2,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data);
#endif
	Render::Instance().SetUniformArray2(mLocation,count,data);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
#endif
}

void ShaderConstant::SetArray2( uint count,const int* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec2||mDataType==GraphicsUniformDataType::BoolVec2,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntDataCount==count&&mIntData==data);
#endif
	Render::Instance().SetUniformArray2(mLocation,count,data);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntDataCount=count;
	mIntData=data;
#endif
}

void ShaderConstant::SetArray3( uint count,const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data);
#endif
	Render::Instance().SetUniformArray3(mLocation,count,data);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
#endif
}

void ShaderConstant::SetArray3( uint count,const int* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec3||mDataType==GraphicsUniformDataType::BoolVec3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntDataCount==count&&mIntData==data);
#endif

	Render::Instance().SetUniformArray3(mLocation,count,data);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntDataCount=count;
	mIntData=data;
#endif
}

void ShaderConstant::SetArray4( uint count,const float* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatVec4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data);
#endif
	Render::Instance().SetUniformArray4(mLocation,count,data);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
#endif
}

void ShaderConstant::SetArray4( uint count,const int* data )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::IntVec4||mDataType==GraphicsUniformDataType::BoolVec4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntDataCount==count&&mIntData==data);
#endif
	Render::Instance().SetUniformArray4(mLocation,count,data);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntDataCount=count;
	mIntData=data;
#endif
}

void ShaderConstant::SetMatrix2( uint count,const float* data,bool isTransposed/*=false*/ )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatMat2,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data&&mIsTransposed==isTransposed);
#endif
	Render::Instance().SetUniformMatrix2(mLocation,count,data,isTransposed);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
	mIsTransposed=isTransposed;
#endif
}

void ShaderConstant::SetMatrix3( uint count,const float* data,bool isTransposed/*=false*/ )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatMat3,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data&&mIsTransposed==isTransposed);
#endif
	Render::Instance().SetUniformMatrix3(mLocation,count,data,isTransposed);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
	mIsTransposed=isTransposed;
#endif
}

void ShaderConstant::SetMatrix3( const Matrix3& matrix )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatMat3,"ErrorDataType");
	SetMatrix3(1,matrix.Items());
}

void ShaderConstant::SetMatrix4( uint count,const float* data,bool isTransposed/*=false*/ )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatMat4,"ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatDataCount==count&&mFloatData==data&&mIsTransposed==isTransposed);
#endif
	Render::Instance().SetUniformMatrix4(mLocation,count,data,isTransposed);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatDataCount=count;
	mFloatData=data;
	mIsTransposed=isTransposed;
#endif
}

void ShaderConstant::SetMatrix( const Matrix& matrix )
{
	MEDUSA_ASSERT(mDataType==GraphicsUniformDataType::FloatMat4,"ErrorDataType");
	SetMatrix4(1,matrix.Items());
}

void ShaderConstant::GetArray( float* outData )
{
	Render::Instance().GetUniformArray(mRenderPass->Program(),mLocation,outData);
}

void ShaderConstant::GetArray( int* outData )
{
	Render::Instance().GetUniformArray(mRenderPass->Program(),mLocation,outData);
}

MEDUSA_END;