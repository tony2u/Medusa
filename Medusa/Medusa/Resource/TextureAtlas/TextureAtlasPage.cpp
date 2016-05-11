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
#include "Resource/TextureAtlas/TextureAtlas.h"

MEDUSA_BEGIN;

TextureAtlasPage::TextureAtlasPage(const FileIdRef& textureFileId)
	:mTextureFileId(textureFileId),
	mPageSize(Size2U::Zero)
{

}

TextureAtlasPage::TextureAtlasPage(int id)
	:mId(id),
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
	region->UpdateMesh(mPageSize);
	if (mAtlas!=nullptr)
	{
		mAtlas->TryAddRegion(region);
	}
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

	mPageSize = mTexture->Size();
	FOR_EACH_COLLECTION(i, mRegions)
	{
		TextureAtlasRegion* region = *i;
		region->UpdateMesh(mPageSize);
	}

	return mTexture;
}

void TextureAtlasPage::SetTexture(ITexture* val)
{
	SAFE_ASSIGN_REF(mTexture, val);
	SetPageSize(mTexture->Size());

}

void TextureAtlasPage::SetAtlas(TextureAtlas* val)
{
	mAtlas = val;
}

void TextureAtlasPage::SetTexcoordUpSide(bool val)
{
	mIsTexcoordUpSide = val;
}

Size2U TextureAtlasPage::Size() const
{
	if (mTexture!=nullptr)
	{
		return mTexture->Size();
	}

	return mPageSize;
}


void TextureAtlasPage::SetPageSize(const Size2U& val)
{
	RETURN_IF_EQUAL(mPageSize, val);
	mPageSize = val;

	//update all mesh texcoord
	FOR_EACH_COLLECTION(i, mRegions)
	{
		TextureAtlasRegion* region = *i;
		region->UpdateMesh(mPageSize);
	}


}


MEDUSA_END;