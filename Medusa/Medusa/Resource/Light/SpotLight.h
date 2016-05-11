// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Light/ILight.h"
#include "Geometry/Matrix4.h"

MEDUSA_BEGIN;

class SpotLight:public ILight
{
public:
	SpotLight(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~SpotLight(void){}

	virtual GraphicsLightType LightType()const{return GraphicsLightType::Spot;}

	float Cutoff() const { return mCutoff; }
	void SetCutoff(float val) { mCutoff = val; }

	float Exponent() const { return mExponent; }
	void SetExponent(float val);

	float ConstantAttenuation() const { return mConstantAttenuation; }
	void SetConstantAttenuation(float val);

	float LinearAttenuation() const { return mLinearAttenuation; }
	void SetLinearAttenuation(float val);

	float QuadraticAttenuation() const { return mQuadraticAttenuation; }
	void SetQuadraticAttenuation(float val);

	const Matrix4& ViewProjectMatrix() const { return mViewProjectMatrix; }
	void SetViewProjectMatrix(const Matrix4& val) { mViewProjectMatrix = val; }
private:
	float mCutoff;	//GL_SPOT_CUTOFF (0<90)

	float mExponent;	//GL_SPOT_EXPONENT 

	float mConstantAttenuation;
	float mLinearAttenuation;	
	float mQuadraticAttenuation;	

	Matrix4 mViewProjectMatrix;
	
};

MEDUSA_END;
