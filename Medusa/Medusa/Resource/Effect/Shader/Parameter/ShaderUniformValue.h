// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/GraphicsTypes.h"
#include "Core/Pattern/variant.h"
#include "Core/Memory/MemoryData.h"
#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Geometry/Point4.h"
#include "Geometry/Color3.h"
#include "Geometry/Color4.h"
#include "Geometry/Matrix4.h"
#include "Geometry/Matrix3.h"

MEDUSA_BEGIN;

class ShaderUniformValue
{
	using DataType = variant<int, Point2I, Point3I, Point4I, Color3B, Color4B, float, Point2F, Point3F, Point4F, Color3F, Color4F, Matrix4, Matrix3, MemoryIntData, MemoryFloatData>;
public:
	ShaderUniformValue(StringRef name);
	virtual ~ShaderUniformValue();

	ShaderUniformValue(const ShaderUniformValue& val) = default;
	ShaderUniformValue& operator=(const ShaderUniformValue& val) = default;

	bool operator==(const ShaderUniformValue& val)const;
	bool operator!=(const ShaderUniformValue& val)const { return !(*this == val); }


	ShaderUniformValue* Clone()const;
public:
	void Set(int x);
	void Set(const Point2I& pos);
	void Set(const Point3I& pos);
	void Set(const Point4I& pos);
	void Set(const Color3B& color);
	void Set(const Color4B& color);

	void Set(float x);
	void Set(const Point2F& pos);
	void Set(const Point3F& pos);
	void Set(const Point4F& pos);
	void Set(const Color3F& color);
	void Set(const Color4F& color);

	void SetArray1(MemoryFloatData data);
	void SetArray2(MemoryFloatData data);
	void SetArray3(MemoryFloatData data);
	void SetArray4(MemoryFloatData data);

	void SetArray1(MemoryIntData data);
	void SetArray2(MemoryIntData data);
	void SetArray3(MemoryIntData data);
	void SetArray4(MemoryIntData data);

	void SetMatrix2(MemoryFloatData data, bool isTransposed = false);
	void SetMatrix3(MemoryFloatData data, bool isTransposed = false);
	void SetMatrix4(MemoryFloatData data, bool isTransposed = false);

	void SetMatrix(const Matrix4& matrix);
	void SetMatrix3(const Matrix3& matrix);

	bool Apply(BaseProgramRenderPass& pass)const;
	intp HashCode()const { return mName.HashCode(); }
	StringRef Name() const { return mName; }
protected:
	HeapString mName;
	DataType mData;
	
	GraphicsUniformDataType mDataType = GraphicsUniformDataType::None;
	bool mIsTransposed;



};

MEDUSA_END;