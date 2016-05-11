// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/Shader/Parameter/IShaderParameter.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;

class ShaderUniform :public IShaderParameter
{
	friend class BaseProgramRenderPass;
private:
	ShaderUniform(BaseProgramRenderPass* effect, int location, StringRef name, GraphicsUniformDataType dataType);
	ShaderUniform(StringRef name, GraphicsUniformDataType dataType);

	virtual ~ShaderUniform();
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

	void GetArray(float* outData);
	void GetArray(int* outData);

protected:
	GraphicsUniformDataType mDataType = GraphicsUniformDataType::None;

#ifdef MEDUSA_RENDER_STATE_CACHE_ENABLED
	int mIntArray[4];
	float mFloatArray[4];

	MemoryIntData mIntData;
	MemoryFloatData mFloatData;
	bool mIsTransposed = false;

#endif

};

MEDUSA_END;