// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/Shader/Parameter/IShaderParameter.h"
#include "Core/Collection/List.h"


MEDUSA_BEGIN;

class ShaderConstant:public IShaderParameter
{
	friend class BaseProgramRenderPass;
private:
	ShaderConstant(BaseProgramRenderPass* effect,int location,StringRef name,GraphicsUniformDataType dataType);
	~ShaderConstant();
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




	void SetArray1(uint count,const float* data);
	void SetArray2(uint count,const float* data);
	void SetArray3(uint count,const float* data);
	void SetArray4(uint count,const float* data);

	void SetArray1(uint count,const int* data);
	void SetArray2(uint count,const int* data);
	void SetArray3(uint count,const int* data);
	void SetArray4(uint count,const int* data);

	void SetMatrix2(uint count,const float* data,bool isTransposed=false);
	void SetMatrix3(uint count,const float* data,bool isTransposed=false);
	void SetMatrix4(uint count,const float* data,bool isTransposed=false);

	void SetMatrix(const Matrix& matrix);
	void SetMatrix3(const Matrix3& matrix);

	void GetArray(float* outData);
	void GetArray(int* outData);

protected:
	GraphicsUniformDataType mDataType;

	int mIntArray[4];
	float mFloatArray[4];

	uint mIntDataCount;
	const int* mIntData;

	uint mFloatDataCount;
	const float* mFloatData;

	bool mIsTransposed;
};

MEDUSA_END;