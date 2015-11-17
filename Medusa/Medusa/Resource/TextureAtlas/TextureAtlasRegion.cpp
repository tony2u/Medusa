// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureAtlasRegion.h"
#include "TextureAtlasPage.h"
#include "Core/Log/Log.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/Effect/EffectFactory.h"

MEDUSA_BEGIN;

TextureAtlasRegion::TextureAtlasRegion()
	:mTextureRect(Rect2U::Zero),
	mOriginalSize(Size2U::Zero),
	mOffset(Point2U::Zero),
	mIsRotate(false),
	mIsFlip(false),
	mIsTexcoordUpSide(true)
{

}

TextureAtlasRegion::~TextureAtlasRegion()
{

}

void TextureAtlasRegion::SetPage(TextureAtlasPage* val)
{
	mPage = val;

}

bool TextureAtlasRegion::UpdateMesh(const Size2U& textureSize)
{
	Rect2F quadRect(mOffset.X, mOffset.Y, mTextureRect.Size.Width, mTextureRect.Size.Height);
	mVertices[0] = quadRect.LeftBottom();
	mVertices[1] = quadRect.RightBottom();
	mVertices[2] = quadRect.RightTop();
	mVertices[3] = quadRect.LeftTop();

	Rect2F texcoord;
	texcoord.Origin.X = (float)mTextureRect.Origin.X / textureSize.Width;
	if (mIsTexcoordUpSide)
	{
		texcoord.Origin.Y = (float)mTextureRect.Origin.Y / textureSize.Height;
	}
	else
	{
		if (mIsRotate)
		{
			texcoord.Origin.Y = 1.f - (float)(mTextureRect.Origin.Y+mTextureRect.Size.Width) / textureSize.Height;

		}
		else
		{
			texcoord.Origin.Y = 1.f - (float)(mTextureRect.Origin.Y + mTextureRect.Size.Height) / textureSize.Height;

		}
	}

	if (mIsRotate)
	{
		texcoord.Size.Width = (float)mTextureRect.Size.Height / textureSize.Width;
		texcoord.Size.Height = (float)mTextureRect.Size.Width / textureSize.Height;

		mTexcoords[0] = texcoord.RightBottom();
		mTexcoords[1] = texcoord.RightTop();
		mTexcoords[2] = texcoord.LeftTop();
		mTexcoords[3] = texcoord.LeftBottom();

	}
	else
	{
		texcoord.Size.Width = (float)mTextureRect.Size.Width / textureSize.Width;
		texcoord.Size.Height = (float)mTextureRect.Size.Height / textureSize.Height;

		mTexcoords[0] = texcoord.LeftBottom();
		mTexcoords[1] = texcoord.RightBottom();
		mTexcoords[2] = texcoord.RightTop();
		mTexcoords[3] = texcoord.LeftTop();
	}




	return true;

}

bool TextureAtlasRegion::AssertMeshLoaded()
{
	if (mPage != nullptr)
	{
		mPage->LoadTexture();
		return true;
	}
	else
	{
		Log::AssertFailedFormat("Region:{} has no page!", mName.c_str());
		return false;
	}
}

ITexture* TextureAtlasRegion::Texture() const
{
	return mPage->GetTexture();
}

void TextureAtlasRegion::UpdateMeshEffectAndMaterial(IMesh* mesh)
{
	LOG_ASSERT_NOT_NULL(mesh);
	ITexture* texture = mPage->LoadTexture();

	IMaterial* material = MaterialFactory::Instance().Create(texture->GetFileId(), texture);
	IEffect* effect = EffectFactory::Instance().CreateSinglePassDefault(RenderPassNames::Texture);

	mesh->SetEffect(effect);
	mesh->SetMaterial(material);
}

void TextureAtlasRegion::SetIsRotate(bool val)
{
	RETURN_IF_EQUAL(mIsRotate, val);
	mIsRotate = val;
}


MEDUSA_END;