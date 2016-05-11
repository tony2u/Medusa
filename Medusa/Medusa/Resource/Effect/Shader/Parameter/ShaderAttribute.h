// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/Shader/Parameter/IShaderParameter.h"

MEDUSA_BEGIN;

class ShaderAttribute :public IShaderParameter
{
	friend class BaseProgramRenderPass;
private:
	ShaderAttribute(BaseProgramRenderPass* renderPass, uint index, StringRef name, GraphicsAttributeDataType dataType);
	virtual ~ShaderAttribute();
public:
	virtual void Set(float x);
	virtual void Set(const Point2F& pos);
	virtual void Set(const Point3F& pos);
	virtual void Set(const Point4F& pos);

	void SetArray1(const float* data);
	void SetArray2(const float* data);
	void SetArray3(const float* data);
	void SetArray4(const float* data);

	void SetPointer(uint componentCount, GraphicsDataType type, bool isNormalized = false, uint stride = 0, const void* data = nullptr);
	void SetPointerFromBufferObject(const IGraphicsBuffer& bufferObject, uint stride = 0, int offset = 0);


	void EnableArray(bool isEnabled);
	bool IsArrayEnabled() const { return mIsArrayEnabled; }

	GraphicsAttributeDataType DataType() const { return mDataType; }
private:
	bool mIsArrayEnabled = false;
	GraphicsAttributeDataType mDataType = GraphicsAttributeDataType::None;;

};

MEDUSA_END;