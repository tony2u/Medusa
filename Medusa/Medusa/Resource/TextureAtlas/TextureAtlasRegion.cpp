// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureAtlasRegion.h"
#include "TextureAtlasPage.h"
#include "Core/Log/Log.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/MaterialFactory.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Map/FileMapOrderItem.h"

MEDUSA_BEGIN;

TextureAtlasRegion::TextureAtlasRegion()
	:mTextureRect(Rect2U::Zero),
	mSourceRect(Rect2U::Zero),
	mIsRotate(false),
	mIsFlip(false)
{
	mPage = nullptr;


}

TextureAtlasRegion::~TextureAtlasRegion()
{

}


TextureAtlasRegion* TextureAtlasRegion::Clone() const
{
	return new TextureAtlasRegion(*this);
}

void TextureAtlasRegion::SetPage(TextureAtlasPage* val)
{
	mPage = val;
}


bool TextureAtlasRegion::UpdateMesh(const Size2U& textureSize)
{
	RETURN_FALSE_IF_NULL(mPage);
	if (IsPolygon())
	{
		//do nothing
	}
	else
	{
		mVertices.ForceReserveCount(4);
		mTexcoords.ForceReserveCount(4);

		Rect2F quadRect(mSourceRect.Origin.X, mSourceRect.Origin.Y, mTextureRect.Size.Width, mTextureRect.Size.Height);
		mVertices[0] = quadRect.LeftBottom();
		mVertices[1] = quadRect.RightBottom();
		mVertices[2] = quadRect.RightTop();
		mVertices[3] = quadRect.LeftTop();

		Rect2F texcoord;
		texcoord.Origin.X = (float)mTextureRect.Origin.X / textureSize.Width;
		if (mPage->IsTexcoordUpSide())
		{
			texcoord.Origin.Y = (float)mTextureRect.Origin.Y / textureSize.Height;
		}
		else
		{
			if (mIsRotate)
			{
				texcoord.Origin.Y = 1.f - (float)(mTextureRect.Origin.Y + mTextureRect.Size.Width) / textureSize.Height;

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

			if (mPage->GetRotateDirection() == RotateDirection::CounterClockWise)
			{
				//rotate back
				mTexcoords[0] = texcoord.RightBottom();
				mTexcoords[1] = texcoord.RightTop();
				mTexcoords[2] = texcoord.LeftTop();
				mTexcoords[3] = texcoord.LeftBottom();
			}
			else
			{
				//clock wise,rotate back
				mTexcoords[0] = texcoord.LeftTop();
				mTexcoords[1] = texcoord.LeftBottom();
				mTexcoords[2] = texcoord.RightBottom();
				mTexcoords[3] = texcoord.RightTop();
			}
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

const Share<ITexture>& TextureAtlasRegion::Texture() const
{
	return mPage->GetTexture();
}

Share<IMaterial> TextureAtlasRegion::CreateMaterial()
{
	auto texture = mPage->LoadTexture();
	return MaterialFactory::Instance().CreateSingleTexture(texture);
}


void TextureAtlasRegion::MapToFileSystem(FileEntry& fileEntry)
{
	mMapFileOrderItem = FileSystem::Instance().MapFileReference(mName, fileEntry, this);
}

void TextureAtlasRegion::UnmapToFileSystem(FileEntry& fileEntry)
{
	if (mMapFileOrderItem != nullptr)
	{
		mMapFileOrderItem->RemoveFileEntryRegion(fileEntry);
		mMapFileOrderItem = nullptr;
	}
}

RotateDirection TextureAtlasRegion::GetRotateDirection() const
{
	if (mIsRotate)
	{
		return mPage->GetRotateDirection();
	}
	return RotateDirection::None;
}

void TextureAtlasRegion::SetRotate(bool val)
{
	RETURN_IF_EQUAL(mIsRotate, val);
	mIsRotate = val;
	if (mPage != nullptr)
	{
		UpdateMesh(mPage->Size());
	}
}

void TextureAtlasRegion::SetTextureRect(const Rect2U& val)
{
	RETURN_IF_EQUAL(mTextureRect, val);
	mTextureRect = val;

	if (mPage != nullptr)
	{
		UpdateMesh(mPage->Size());
	}
}


Rect2U TextureAtlasRegion::ResultTextureRect() const
{
	auto textureSize = mPage->LoadTexture()->Size();
	Rect2U result = mTextureRect;
	if (mIsRotate)
	{
		result.Size.Width = mTextureRect.Size.Height;
		result.Size.Height = mTextureRect.Size.Width;
	}


	if (mPage->IsTexcoordUpSide())
	{

	}
	else
	{
		if (mIsRotate)
		{
			result.Origin.Y = textureSize.Height - (mTextureRect.Origin.Y + mTextureRect.Size.Width);
		}
		else
		{
			result.Origin.Y = textureSize.Height - (mTextureRect.Origin.Y + mTextureRect.Size.Height);
		}

	}



	return result;
}


MEDUSA_END;