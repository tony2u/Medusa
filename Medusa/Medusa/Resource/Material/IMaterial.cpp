// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IMaterial.h"
#include "Graphics/State/BlendRenderState.h"
#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Core/Collection/Linq.h"
#include "Resource/Effect/IEffect.h"

MEDUSA_BEGIN;

IMaterial::IMaterial(const Share<ITexture>& texture /*= nullptr*/, const Share<IEffect>& effect /*= nullptr*/, GraphicsDrawMode drawMode /*= GraphicsDrawMode::Triangles*/, const FileIdRef& fileId /*= FileIdRef::Empty*/)
	:IResource(fileId),
	mFirstTexture(nullptr),
	mEffect(effect),
	mDrawMode(drawMode)
{
	
	if(texture!=nullptr)
	{
		AddTexture(texture);
	}
}

IMaterial::~IMaterial(void)
{
	mTextureSamplerDict.Clear();
	mTextures.Clear();
	mFirstTexture = nullptr;

	mEffect = nullptr;

}

void IMaterial::AddTexture(const Share<ITexture>& texture)
{
	MEDUSA_ASSERT_NOT_NULL(texture, "");
	MEDUSA_ASSERT_FALSE(mTextures.ContainsKey(texture->Unit()), "Duplicate add texture of same unit");
	MEDUSA_ASSERT_FALSE(mTextureSamplerDict.ContainsKey(texture->SamplerName()), "Duplicate add texture of same sampler name");

	mTextures.Add(texture->Unit(), texture);
	mTextureSamplerDict.Add(texture->SamplerName(), texture);
	OnMaterialChanged(RenderableChangedFlags::BatchChanged);

	EnableBlend(texture->IsBlend());

	if (mFirstTexture == nullptr)
	{
		mFirstTexture = texture;
	}
}

Share<ITexture> IMaterial::FirstTexture()const
{
	return mFirstTexture;
}

Share<ITexture> IMaterial::FindTextureBySampler(StringRef smaplerName)
{
	return mTextureSamplerDict.GetOptional(smaplerName, nullptr);
}

void IMaterial::Apply()const
{
	for (auto& i:mTextures)
	{
		i.Value->Apply();
	}

	RenderStateSet::Apply();
}

void IMaterial::Restore()const
{
	RenderStateSet::Restore();
	for (auto& i : mTextures)
	{
		i.Value->Restore();
	}
}


bool IMaterial::Equals(const IMaterial& material) const
{
	RETURN_FALSE_IF_FALSE(RenderStateSet::Equals(material));
	return Linq::IsEqual(mTextures, material.mTextures);
}

void IMaterial::SetEffect(const Share<IEffect>& val)
{
	RETURN_IF_EQUAL(mEffect, val);
	mEffect = val;
	OnMaterialChanged(RenderableChangedFlags::BatchChanged);
}

void IMaterial::SetDrawMode(GraphicsDrawMode val)
{
	RETURN_IF_EQUAL(mDrawMode, val);
	mDrawMode = val;
	OnMaterialChanged(RenderableChangedFlags::BatchChanged);

}

MEDUSA_END;