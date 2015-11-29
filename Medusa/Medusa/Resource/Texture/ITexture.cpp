// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ITexture.h"
#include "Graphics/Render/Render.h"
#include "Resource/Image/IImage.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/ResourceNames.h"
#include "Resource/Effect/Shader/Parameter/ShaderConstant.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"

MEDUSA_BEGIN;

ITexture::ITexture(const FileIdRef& fileId,GraphicsTextureType textureType,StringRef samplerName/*=ShaderSamplerNames::Texture*/,GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/)
	:IResource(fileId), mSamplerName(samplerName), mIsLoaded(false)
{
	mSamplerState=new SamplerRenderState(textureType,unit);
	mSamplerState->SetTexture(Render::Instance().GenTexture());
	mPixelStoreState=new PixelStoreRenderState();
}


ITexture::~ITexture(void)
{
	Render::Instance().DeleteTexture(mSamplerState->Texture());

	SAFE_RELEASE(mSamplerState);
	SAFE_RELEASE(mPixelStoreState);
}

bool ITexture::IsAvailable() const
{
	return Render::Instance().IsTexture(mSamplerState->Texture());
}

void ITexture::Apply()
{
	if (!mSamplerName.IsEmpty())
	{
		BaseProgramRenderPass* pass = RenderingContext::Instance().ProgramRenderPass();
		if (pass != nullptr)
		{
			ShaderConstant* sampler = pass->GetConstant(mSamplerName);
			if (sampler != nullptr)
			{
				sampler->Invalidate();
				sampler->Set((int)mSamplerState->TextureUnit() - (int)GraphicsTextureUnits::Texture0);
			}
			else
			{
				//Log::LogErrorFormat("Cannot find sampler by name:{}",mSamplerName.c_str());
			}
		}

	}

	RenderStateMachine::Instance().Push(mSamplerState);
	RenderStateMachine::Instance().Push(mPixelStoreState);

	Upload();
}

void ITexture::Restore()
{
	RenderStateMachine::Instance().Pop(mPixelStoreState);
	RenderStateMachine::Instance().Pop(mSamplerState);
}


MEDUSA_END;