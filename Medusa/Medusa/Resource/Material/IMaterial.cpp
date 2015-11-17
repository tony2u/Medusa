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

MEDUSA_BEGIN;


IMaterial::IMaterial(const FileIdRef& fileId/*=FileId::Empty*/):IResource(fileId),mFirstTexture(nullptr)
{
	mId = AutoIncreaseId<IMaterial>::New();
}

IMaterial::IMaterial(ITexture* texture,const FileIdRef& fileId/*=FileId::Empty*/):IResource(fileId),mFirstTexture(nullptr)
{
	mId = AutoIncreaseId<IMaterial>::New();
	AddTexture(texture);

}


IMaterial::~IMaterial(void)
{
	mTextureSamplerDict.Clear();
	SAFE_RELEASE_DICTIONARY_VALUE(mTextures);
	mFirstTexture=nullptr;
}

void IMaterial::AddTexture( ITexture* texture )
{
	MEDUSA_ASSERT_NOT_NULL(texture,"");
	MEDUSA_ASSERT_FALSE(mTextures.ContainsKey(texture->Unit()),"Duplicate add texture of same unit");
	MEDUSA_ASSERT_FALSE(mTextureSamplerDict.ContainsKey(texture->SamplerName()),"Duplicate add texture of same sampler name");

	texture->Retain();
	mTextures.Add(texture->Unit(),texture);
	mTextureSamplerDict.Add(texture->SamplerName(), texture);

	EnableBlend(texture->IsBlend());
	
	if (mFirstTexture==nullptr)
	{
		mFirstTexture=texture;
	}
}

ITexture* IMaterial::FirstTexture()const
{
	return mFirstTexture;
}

ITexture* IMaterial::FindTextureBySampler( StringRef smaplerName )
{
	return mTextureSamplerDict.TryGetValueWithFailed(smaplerName,nullptr);
}

void IMaterial::Apply()const
{
	FOR_EACH_COLLECTION(i,mTextures)
	{
		ITexture* texture=i->Value;
		texture->Apply();
	}

	RenderStateSet::Apply();
}

void IMaterial::Restore()const
{
	RenderStateSet::Restore();

	FOR_EACH_COLLECTION(i,mTextures)
	{
		ITexture* texture=i->Value;
		texture->Restore();
	}
}

void IMaterial::OnUpdateHashCode(intp& outHashCode)
{
	//RenderStateCollection::OnUpdateHashCode(outHashCode);
	FOR_EACH_COLLECTION(i,mTextures)
	{
		ITexture* texture=i->Value;
		outHashCode^=(intp)texture;
	}
}

bool IMaterial::Equals(const IMaterial& material) const
{
	RETURN_FALSE_IF_FALSE(RenderStateSet::Equals(material));
	return Linq::IsEqual(mTextures,material.mTextures);
}


MEDUSA_END;