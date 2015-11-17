// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SpotLight.h"

MEDUSA_BEGIN;


SpotLight::SpotLight( const FileIdRef& fileId/*=FileId::Empty*/ ) 
	:ILight(fileId),mViewProjectMatrix(Matrix::Identity)
{

}

void SpotLight::SetExponent( float val )
{
	if (mExponent!=val)
	{
		mExponent = val;
	}
}

void SpotLight::SetConstantAttenuation( float val )
{
	if (mConstantAttenuation!=val)
	{
		mConstantAttenuation = val;
	}
}

void SpotLight::SetLinearAttenuation( float val )
{
	if (mLinearAttenuation!=val)
	{
		mLinearAttenuation = val;
	}
}

void SpotLight::SetQuadraticAttenuation( float val )
{
	if (mQuadraticAttenuation!=val)
	{
		mQuadraticAttenuation = val;
	}
}

MEDUSA_END;
