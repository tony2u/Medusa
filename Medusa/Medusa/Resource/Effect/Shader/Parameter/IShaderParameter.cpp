// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Parameter/IShaderParameter.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"
#include "Graphics/Render/Render.h"
#include "Geometry/Matrix43.h"
#include "Geometry/Matrix4.h"
#include "Core/Log/Log.h"


MEDUSA_BEGIN;

IShaderParameter::IShaderParameter(BaseProgramRenderPass* renderPass,int location,StringRef name)
	:mRenderPass(renderPass),mLocation(location),mName(name),mIsAssigned(false)
{

}

IShaderParameter::IShaderParameter(StringRef name)
	:mName(name)
{

}

IShaderParameter::~IShaderParameter()
{

}

void IShaderParameter::Validate() const
{
	if (!mIsAssigned)
	{
		Log::AssertFailedFormat("Forget to assign:{}",mName);
	}
}

void IShaderParameter::MarkAssigned()
{
	if (mIsAssigned)
	{
		//Log::LogInfoFormat("Duplicate assignment:{}",mName.c_str());
	}

	mIsAssigned=true;
}

void IShaderParameter::Invalidate()
{
	mIsAssigned=false;
}

MEDUSA_END;