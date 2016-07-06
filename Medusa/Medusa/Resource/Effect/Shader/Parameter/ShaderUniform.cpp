// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Parameter/ShaderUniform.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Graphics/Render/Render.h"
#include "Geometry/Matrix3.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Matrix2.h"

#include "Core/Log/Log.h"
#include "Geometry/Color3.h"
#include "Geometry/Color4.h"
#include "Core/Memory/Memory.h"

MEDUSA_BEGIN;

ShaderUniform::ShaderUniform(BaseProgramRenderPass* renderPass, int location, StringRef name, GraphicsUniformDataType dataType)
	:IShaderParameter(renderPass, location, name), mDataType(dataType)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	Memory::SetZero(mIntArray);
	Memory::SetZero(mFloatArray);

#endif
}

ShaderUniform::ShaderUniform(StringRef name, GraphicsUniformDataType dataType)
	:IShaderParameter(name), mDataType(dataType)
{
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	Memory::SetZero(mIntArray);
	Memory::SetZero(mFloatArray);
#endif
}

ShaderUniform::~ShaderUniform()
{

}

void ShaderUniform::Set(int x)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::Bool
		|| mDataType == GraphicsUniformDataType::Int
		|| mDataType == GraphicsUniformDataType::Sampler2D
		|| mDataType == GraphicsUniformDataType::SamplerCube, "ErrorDataType");

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0] == x);
#endif
	Render::Instance().SetUniform(mLocation, x);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0] = x;
#endif

}

void ShaderUniform::Set(const Point2I& pos)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec2 || mDataType == GraphicsUniformDataType::BoolVec2, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0] == pos.X&&mIntArray[1] == pos.Y);
#endif

	Render::Instance().SetUniform(mLocation, pos.X, pos.Y);
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0] = pos.X;
	mIntArray[1] = pos.Y;
#endif
}

void ShaderUniform::Set(const Point3I& pos)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec3 || mDataType == GraphicsUniformDataType::BoolVec3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0] == pos.X&&mIntArray[1] == pos.Y&&mIntArray[2] == pos.Z);
#endif
	Render::Instance().SetUniform(mLocation, pos.X, pos.Y, pos.Z);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0] = pos.X;
	mIntArray[1] = pos.Y;
	mIntArray[2] = pos.Z;
#endif
}

void ShaderUniform::Set(const Point4I& pos)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec4 || mDataType == GraphicsUniformDataType::BoolVec4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0] == pos.X&&mIntArray[1] == pos.Y&&mIntArray[2] == pos.Z&&mIntArray[3] == pos.W);
#endif
	Render::Instance().SetUniform(mLocation, pos.X, pos.Y, pos.Z, pos.W);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0] = pos.X;
	mIntArray[1] = pos.Y;
	mIntArray[2] = pos.Z;
	mIntArray[3] = pos.W;
#endif
}

void ShaderUniform::Set(const Color3B& color)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec3 || mDataType == GraphicsUniformDataType::BoolVec3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0] == (int)color.R&&mIntArray[1] == (int)color.G&&mIntArray[2] == (int)color.B);
#endif
	Render::Instance().SetUniform(mLocation, color.R, color.G, color.B);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0] = color.R;
	mIntArray[1] = color.G;
	mIntArray[2] = color.B;

#endif
}

void ShaderUniform::Set(const Color4B& color)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec4 || mDataType == GraphicsUniformDataType::BoolVec4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntArray[0] == (int)color.R&&mIntArray[1] == (int)color.G&&mIntArray[2] == (int)color.B&&mIntArray[3] == color.A);
#endif
	Render::Instance().SetUniform(mLocation, color.R, color.G, color.B, color.A);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntArray[0] = color.R;
	mIntArray[1] = color.G;
	mIntArray[2] = color.B;
	mIntArray[3] = color.A;
#endif
}

void ShaderUniform::Set(float x)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::Float, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0], x));
#endif

	Render::Instance().SetUniform(mLocation, x);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0] = x;
#endif
}

void ShaderUniform::Set(const Point2F& pos)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec2, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0], pos.X) && Math::IsEqual(mFloatArray[1], pos.Y));
#endif
	Render::Instance().SetUniform(mLocation, pos.X, pos.Y);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0] = pos.X;
	mFloatArray[1] = pos.Y;
#endif
}

void ShaderUniform::Set(const Point3F& pos)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0], pos.X) && Math::IsEqual(mFloatArray[1], pos.Y) && Math::IsEqual(mFloatArray[2], pos.Z));
#endif
	Render::Instance().SetUniform(mLocation, pos.X, pos.Y, pos.Z);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0] = pos.X;
	mFloatArray[1] = pos.Y;
	mFloatArray[2] = pos.Z;

#endif
}

void ShaderUniform::Set(const Point4F& pos)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0], pos.X) && Math::IsEqual(mFloatArray[1], pos.Y) && Math::IsEqual(mFloatArray[2], pos.Z) && Math::IsEqual(mFloatArray[3], pos.W));
#endif
	Render::Instance().SetUniform(mLocation, pos.X, pos.Y, pos.Z, pos.W);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0] = pos.X;
	mFloatArray[1] = pos.Y;
	mFloatArray[2] = pos.Z;
	mFloatArray[3] = pos.W;
#endif
}

void ShaderUniform::Set(const Color3F& color)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0], color.R) && Math::IsEqual(mFloatArray[1], color.G) && Math::IsEqual(mFloatArray[2], color.B));
#endif
	Render::Instance().SetUniform(mLocation, color.R, color.G, color.B);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0] = color.R;
	mFloatArray[1] = color.G;
	mFloatArray[2] = color.B;
#endif
}

void ShaderUniform::Set(const Color4F& color)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&Math::IsEqual(mFloatArray[0], color.R) && Math::IsEqual(mFloatArray[1], color.G) && Math::IsEqual(mFloatArray[2], color.B) && Math::IsEqual(mFloatArray[3], color.A));
#endif

	Render::Instance().SetUniform(mLocation, color.R, color.G, color.B, color.A);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatArray[0] = color.R;
	mFloatArray[1] = color.G;
	mFloatArray[2] = color.B;
	mFloatArray[3] = color.A;
#endif
}

void ShaderUniform::SetArray1(MemoryFloatData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::Float, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data));
#endif

	Render::Instance().SetUniformArray1(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatData = data;
#endif
}

void ShaderUniform::SetArray1(MemoryIntData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::Int || mDataType == GraphicsUniformDataType::Bool, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntData.IsContentEqual(data));
#endif
	Render::Instance().SetUniformArray1(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mIntData = data;
#endif
}

void ShaderUniform::SetArray2(MemoryFloatData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec2, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data));
#endif
	Render::Instance().SetUniformArray2(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mFloatData = data;
#endif
}

void ShaderUniform::SetArray2(MemoryIntData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec2 || mDataType == GraphicsUniformDataType::BoolVec2, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntData.IsContentEqual(data));
#endif
	Render::Instance().SetUniformArray2(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mIntData = data;
#endif
}

void ShaderUniform::SetArray3(MemoryFloatData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data));
#endif
	Render::Instance().SetUniformArray3(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mFloatData = data;
#endif
}

void ShaderUniform::SetArray3(MemoryIntData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec3 || mDataType == GraphicsUniformDataType::BoolVec3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntData.IsContentEqual(data));
#endif

	Render::Instance().SetUniformArray3(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mIntData = data;
#endif
}

void ShaderUniform::SetArray4(MemoryFloatData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatVec4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data));
#endif
	Render::Instance().SetUniformArray4(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mFloatData = data;
#endif
}

void ShaderUniform::SetArray4(MemoryIntData data)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::IntVec4 || mDataType == GraphicsUniformDataType::BoolVec4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mIntData.IsContentEqual(data));
#endif
	Render::Instance().SetUniformArray4(mLocation, (uint)data.Size(), data.Data());
	MarkAssigned();

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mIntData = data;
#endif
}

void ShaderUniform::SetMatrix2(MemoryFloatData data, bool isTransposed/*=false*/)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatMat2, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data)&&mIsTransposed==isTransposed);
#endif
	Render::Instance().SetUniformMatrix2(mLocation, (uint)data.Size() / sizeof(Matrix2), data.Data(), isTransposed);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	mFloatData = data;
	mIsTransposed = isTransposed;
#endif
}

void ShaderUniform::SetMatrix3(MemoryFloatData data, bool isTransposed/*=false*/)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatMat3, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data) && mIsTransposed == isTransposed);
#endif
	Render::Instance().SetUniformMatrix3(mLocation, (uint)data.Size() / sizeof(Matrix3), data.Data(), isTransposed);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	
	mFloatData = data;
	mIsTransposed = isTransposed;
#endif
}

void ShaderUniform::SetMatrix3(const Matrix3& matrix)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatMat3, "ErrorDataType");
	SetMatrix3(MemoryFloatData::FromStatic(matrix.Items(),9*sizeof(float)));
}

void ShaderUniform::SetMatrix4(MemoryFloatData data, bool isTransposed/*=false*/)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatMat4, "ErrorDataType");
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	RETURN_IF_TRUE(mIsAssigned&&mFloatData.IsContentEqual(data) && mIsTransposed == isTransposed);
#endif
	Render::Instance().SetUniformMatrix4(mLocation, (uint)data.Size()/sizeof(Matrix4), data.Data(), isTransposed);
	MarkAssigned();
#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED

	mFloatData = data;
	mIsTransposed = isTransposed;
#endif
}

void ShaderUniform::SetMatrix(const Matrix4& matrix)
{
	MEDUSA_ASSERT(mDataType == GraphicsUniformDataType::FloatMat4, "ErrorDataType");
	SetMatrix4(MemoryFloatData::FromStatic(matrix.Items(), 16 * sizeof(float)));
}

void ShaderUniform::GetArray(float* outData)
{
	Render::Instance().GetUniformArray(mRenderPass->Program(), mLocation, outData);
}

void ShaderUniform::GetArray(int* outData)
{
	Render::Instance().GetUniformArray(mRenderPass->Program(), mLocation, outData);
}

MEDUSA_END;