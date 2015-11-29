// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IMaterial.h"
#include "Graphics/State/BlendRenderState.h"
#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/RenderStateMachine.h"
#include "Core/Collection/Linq.h"
#include "Core/Pattern/AutoIncreaseId.h"
#include "Resource/Effect/IEffect.h"

MEDUSA_BEGIN;

IMaterial::IMaterial(ITexture* texture /*= nullptr*/, IEffect* effect /*= nullptr*/, GraphicsDrawMode drawMode /*= GraphicsDrawMode::Triangles*/, const FileIdRef& fileId /*= FileIdRef::Empty*/)
	:IResource(fileId),
	mFirstTexture(nullptr),
	mEffect(effect),
	mDrawMode(drawMode)
{
	mId = AutoIncreaseId<IMaterial>::New();
	SAFE_RETAIN(mEffect);

	if(texture!=nullptr)
	{
		AddTexture(texture);
	}
}

IMaterial::~IMaterial(void)
{
	mTextureSamplerDict.Clear();
	SAFE_RELEASE_DICTIONARY_VALUE(mTextures);
	mFirstTexture = nullptr;

	SAFE_RELEASE(mEffect);

}

void IMaterial::AddTexture(ITexture* texture)
{
	MEDUSA_ASSERT_NOT_NULL(texture, "");
	MEDUSA_ASSERT_FALSE(mTextures.ContainsKey(texture->Unit()), "Duplicate add texture of same unit");
	MEDUSA_ASSERT_FALSE(mTextureSamplerDict.ContainsKey(texture->SamplerName()), "Duplicate add texture of same sampler name");

	texture->Retain();
	mTextures.Add(texture->Unit(), texture);
	mTextureSamplerDict.Add(texture->SamplerName(), texture);
	OnMaterialChanged(RenderableChangedFlags::BatchChanged);

	EnableBlend(texture->IsBlend());

	if (mFirstTexture == nullptr)
	{
		mFirstTexture = texture;
	}
}

ITexture* IMaterial::FirstTexture()const
{
	return mFirstTexture;
}

ITexture* IMaterial::FindTextureBySampler(StringRef smaplerName)
{
	return mTextureSamplerDict.TryGetValueWithFailed(smaplerName, nullptr);
}

void IMaterial::Apply()const
{
	FOR_EACH_COLLECTION(i, mTextures)
	{
		ITexture* texture = i->Value;
		texture->Apply();
	}

	RenderStateSet::Apply();
}

void IMaterial::Restore()const
{
	RenderStateSet::Restore();

	FOR_EACH_COLLECTION(i, mTextures)
	{
		ITexture* texture = i->Value;
		texture->Restore();
	}
}


bool IMaterial::Equals(const IMaterial& material) const
{
	RETURN_FALSE_IF_FALSE(RenderStateSet::Equals(material));
	return Linq::IsEqual(mTextures, material.mTextures);
}

void IMaterial::SetEffect(const IEffect* val)
{
	RETURN_IF_EQUAL(mEffect, val);
	SAFE_ASSIGN_REF(mEffect, val);
	OnMaterialChanged(RenderableChangedFlags::BatchChanged);
}

void IMaterial::SetDrawMode(GraphicsDrawMode val)
{
	RETURN_IF_EQUAL(mDrawMode, val);
	mDrawMode = val;
	OnMaterialChanged(RenderableChangedFlags::BatchChanged);

}

MEDUSA_END;