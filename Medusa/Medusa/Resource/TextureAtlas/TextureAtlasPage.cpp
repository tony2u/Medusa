// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureAtlasPage.h"
#include "Resource/Texture/ITexture.h"
#include "TextureAtlasRegion.h"
#include "Resource/Texture/TextureFactory.h"
#include "Core/Log/Log.h"
#include "Resource/Texture/ImageTexture.h"

MEDUSA_BEGIN;

TextureAtlasPage::TextureAtlasPage(const FileIdRef& fileId)
	:mFileId(fileId),
	mPageSize(Size2U::Zero)
{

}

TextureAtlasPage::~TextureAtlasPage()
{
	SAFE_RELEASE(mTexture);
	SAFE_DELETE_COLLECTION(mRegions);
}

void TextureAtlasPage::AddRegion(TextureAtlasRegion* region)
{
	mRegions.Add(region);
	region->SetPage(this);
}

ITexture* TextureAtlasPage::LoadTexture()
{
	RETURN_SELF_IF_NOT_NULL(mTexture);
	mTexture = TextureFactory::Instance().CreateFromFile(mTextureFileId.ToRef());
	if (mTexture == nullptr)
	{
		Log::AssertFailedFormat("Cannot load texture:{}-{}", mTextureFileId.Name.c_str(), (uint)mTextureFileId.Order);
		return nullptr;
	}

	SAFE_RETAIN(mTexture);

	mTexture->SetMagFilter(mMagFilter);
	mTexture->SetMinFilter(mMinFilter);
	mTexture->SetWrapS(mWrapS);
	mTexture->SetWrapT(mWrapT);

	Size2U textureSize = mTexture->Size();
	FOR_EACH_COLLECTION(i, mRegions)
	{
		TextureAtlasRegion* region = *i;
		region->UpdateMesh(textureSize);
	}

	return mTexture;
}

Size2U TextureAtlasPage::Size() const
{
	if (mTexture!=nullptr)
	{
		return mTexture->Size();
	}

	return mPageSize;
}


MEDUSA_END;