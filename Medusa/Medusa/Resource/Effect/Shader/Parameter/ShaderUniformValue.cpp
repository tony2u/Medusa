// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ShaderUniformValue.h"
#include "Core/Log/Log.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "ShaderUniform.h"

MEDUSA_BEGIN;

ShaderUniformValue::ShaderUniformValue(StringRef name)
	:mName(name)
{
}


ShaderUniformValue::~ShaderUniformValue()
{
	
}

bool ShaderUniformValue::operator==(const ShaderUniformValue& val) const
{
	return (mData == val.mData)&&(mName==val.mName)&&(mDataType == val.mDataType)&&mIsTransposed == val.mIsTransposed;
}

ShaderUniformValue* ShaderUniformValue::Clone() const
{
	return new ShaderUniformValue(*this);
}

void ShaderUniformValue::Set(int x)
{
	mData = x;
}

void ShaderUniformValue::Set(const Point2I& pos)
{
	mData = pos;
}

void ShaderUniformValue::Set(const Point3I& pos)
{
	mData = pos;
}

void ShaderUniformValue::Set(const Point4I& pos)
{
	mData = pos;
}

void ShaderUniformValue::Set(const Color3B& color)
{
	mData = color;
}

void ShaderUniformValue::Set(const Color4B& color)
{
	mData = color;
}

void ShaderUniformValue::Set(float x)
{
	mData = x;
}

void ShaderUniformValue::Set(const Point2F& pos)
{
	mData = pos;
}

void ShaderUniformValue::Set(const Point3F& pos)
{
	mData = pos;
}

void ShaderUniformValue::Set(const Point4F& pos)
{
	mData = pos;
}

void ShaderUniformValue::Set(const Color3F& color)
{
	mData = color;
}

void ShaderUniformValue::Set(const Color4F& color)
{
	mData = color;
}

void ShaderUniformValue::SetArray1(MemoryFloatData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::Float;
	
}

void ShaderUniformValue::SetArray1(MemoryIntData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::Int;
}

void ShaderUniformValue::SetArray2(MemoryFloatData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::FloatVec2;
}

void ShaderUniformValue::SetArray2(MemoryIntData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::IntVec2;
}

void ShaderUniformValue::SetArray3(MemoryFloatData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::FloatVec3;

}

void ShaderUniformValue::SetArray3(MemoryIntData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::IntVec3;

}

void ShaderUniformValue::SetArray4(MemoryFloatData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::FloatVec4;
}

void ShaderUniformValue::SetArray4(MemoryIntData data)
{
	mData = data;
	mDataType = GraphicsUniformDataType::IntVec4;

}

void ShaderUniformValue::SetMatrix2(MemoryFloatData data, bool isTransposed/*=false*/)
{
	mData = data;
	mIsTransposed = isTransposed;
	mDataType = GraphicsUniformDataType::FloatMat2;
}

void ShaderUniformValue::SetMatrix3(MemoryFloatData data, bool isTransposed/*=false*/)
{
	mData = data;
	mIsTransposed = isTransposed;
	mDataType = GraphicsUniformDataType::FloatMat3;

}

void ShaderUniformValue::SetMatrix3(const Matrix3& matrix)
{
	mData = matrix;
	mDataType = GraphicsUniformDataType::FloatMat3;
}

void ShaderUniformValue::SetMatrix4(MemoryFloatData data, bool isTransposed/*=false*/)
{
	mData = data;
	mIsTransposed = isTransposed;
	mDataType = GraphicsUniformDataType::FloatMat4;

}

void ShaderUniformValue::SetMatrix(const Matrix4& matrix)
{
	mData = matrix;
	mDataType = GraphicsUniformDataType::FloatMat4;

}
bool ShaderUniformValue::Apply(BaseProgramRenderPass& pass)const
{
	auto uniform= pass.FindUniform(mName);
	RETURN_FALSE_IF_NULL(uniform);
	using DataType = variant<int, Point2I, Point3I, Point4I, Color3B, Color4B, float, Point2F, Point3F, Point4F, Color3F, Color4F, Matrix4, Matrix3, MemoryIntData, MemoryFloatData>;

	switch (mData.which())
	{
	case 0:
		uniform->Set(mData.get<int>());
		break;
	case 1:
		uniform->Set(mData.get<Point2I>());
		break;
	case 2:
		uniform->Set(mData.get<Point3I>());
		break;
	case 3:
		uniform->Set(mData.get<Point4I>());
		break;
	case 4:
		uniform->Set(mData.get<Color3B>());
		break;
	case 5:
		uniform->Set(mData.get<Color4B>());
		break;
	case 6:
		uniform->Set(mData.get<float>());
		break;
	case 7:
		uniform->Set(mData.get<Point2F>());
		break;
	case 8:
		uniform->Set(mData.get<Point3F>());
		break;
	case 9:
		uniform->Set(mData.get<Point4F>());
		break;
	case 10:
		uniform->Set(mData.get<Color3F>());
		break;
	case 11:
		uniform->Set(mData.get<Color4F>());
		break;
	case 12:
		uniform->SetMatrix(mData.get<Matrix4>());
		break;
	case 13:
		uniform->SetMatrix3(mData.get<Matrix3>());
		break;
	case 14:
		switch (mDataType)
		{
		case GraphicsUniformDataType::Int:
			uniform->SetArray1(mData.get<MemoryIntData>());
			break;
		case GraphicsUniformDataType::IntVec2:
			uniform->SetArray2(mData.get<MemoryIntData>());
			break;
		case GraphicsUniformDataType::IntVec3:
			uniform->SetArray3(mData.get<MemoryIntData>());
			break;
		case GraphicsUniformDataType::IntVec4:
			uniform->SetArray4(mData.get<MemoryIntData>());
			break;
		default:
			break;
		}

		
		break;
	case 15:
		switch (mDataType)
		{
		case GraphicsUniformDataType::Float:
			uniform->SetArray1(mData.get<MemoryFloatData>());
			break;
		case GraphicsUniformDataType::FloatVec2:
			uniform->SetArray2(mData.get<MemoryFloatData>());
			break;
		case GraphicsUniformDataType::FloatVec3:
			uniform->SetArray3(mData.get<MemoryFloatData>());
			break;
		case GraphicsUniformDataType::FloatVec4:
			uniform->SetArray4(mData.get<MemoryFloatData>());
			break;
		case GraphicsUniformDataType::FloatMat2:
			uniform->SetMatrix2(mData.get<MemoryFloatData>(),mIsTransposed);
			break;
		case GraphicsUniformDataType::FloatMat3:
			uniform->SetMatrix3(mData.get<MemoryFloatData>(), mIsTransposed);
			break;
		case GraphicsUniformDataType::FloatMat4:
			uniform->SetMatrix4(mData.get<MemoryFloatData>(), mIsTransposed);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return true;
}

MEDUSA_END;