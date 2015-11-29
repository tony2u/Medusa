// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FontFactory.h"
#include "Resource/Font/BMPFont.h"
#include "Resource/Font/TTFFont.h"
#include "Resource/Material/MaterialFactory.h"
#include "Core/IO/File.h"
#include "Resource/ResourceNames.h"
#include "Resource/Image/PVRImage.h"
#include "Resource/Image/DynamicAtlasRGBAImage.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Texture/ImageTexture.h"
#include "Core/IO/FileSystem.h"
#include "Resource/Texture/TextureFactory.h"


MEDUSA_BEGIN;

FontFactory::FontFactory()
{

}

FontFactory::~FontFactory()
{

}
bool FontFactory::Initialize()
{
	mInitialImageSize = 256;
	mMaxImageSize = Render::Instance().GetInteger(GraphicsIntegerName::MaxTextureSize);

	return true;
}

bool FontFactory::Uninitialize()
{
	Clear();
	return true;
}
void FontFactory::Clear()
{
	RETURN_IF_EMPTY(mItems);
	SAFE_RELEASE_COLLECTION(mCacheItems);
	SAFE_RELEASE_DICTIONARY_VALUE(mItems);

	SAFE_RELEASE_COLLECTION(mRGBAMaterials);
	SAFE_RELEASE_COLLECTION(mRGBMaterials);
	SAFE_RELEASE_COLLECTION(mAlphaMaterials);

}


void FontFactory::ReleaseCache()
{
	SAFE_RELEASE_COLLECTION(mCacheItems);
	Shrink();
}


void FontFactory::Shrink()
{
	RETURN_IF_EMPTY(mItems);
	List<FontId, EqualCompare<FontId> > unusedKeys;
	FOR_EACH_COLLECTION(i, mItems)
	{
		const FontId& fileId = i->Key;
		IFont* item = i->Value;
		if (!item->IsShared())
		{
			unusedKeys.Add(fileId);
		}
	}

	RETURN_IF_EMPTY(unusedKeys);
	FOR_EACH_COLLECTION(i, unusedKeys)
	{
		Remove(*i);
	}


}

bool FontFactory::Remove(const FontId& fontId)
{
	IFont* ani = mItems.RemoveOtherKeyWithValueReturned(fontId, fontId.HashCode(), nullptr);
	RETURN_FALSE_IF_NULL(ani);
	ani->Release();
	return true;
}

IFont* FontFactory::Find(const FontId& fontId) const
{
	return mItems.TryGetValueWithFailedByOtherKey(fontId, fontId.HashCode(), nullptr);
}

bool FontFactory::Add(IFont* val, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	RETURN_FALSE_IF_NULL(val);
	switch (shareType)
	{
		case ResourceShareType::Share:

			if (mItems.TryAdd(val->GetFontId(), val))
			{
				val->Retain();
				return true;
			}
			break;
		case ResourceShareType::ShareAndCache:

			if (mItems.TryAdd(val->GetFontId(), val))
			{
				val->Retain();
				mCacheItems.Add(val);
				val->Retain();

				return true;
			}

			break;
		default:
			return true;
	}

	return false;
}


IFont* FontFactory::Create(const FontId& fontId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IFont* resultFont = Find(fontId);
	RETURN_SELF_IF_NOT_NULL(resultFont);

	FileType fileType = FileInfo::ExtractType(fontId.Name);

	switch (fileType)
	{
		case FileType::png:
		{
			resultFont = BMPFont::CreateFromSingleTexture(fontId);
		}
		break;
		case FileType::pvr:
		{
			resultFont = BMPFont::CreateFromPVR(fontId);
		}
		break;
		case FileType::ttf:
		{
			resultFont = TTFFont::CreateFromFile(fontId);
		}
		break;
		case FileType::fnt:
		{

			const IStream* stream = FileSystem::Instance().ReadFile(fontId.ToRef());
			RETURN_NULL_IF_NULL(stream);

			char c1 = (char)stream->ReadChar();
			char c2 = (char)stream->ReadChar();
			char c3 = (char)stream->ReadChar();

			if (c1 == 'B'&&c2 == 'M'&&c3 == 'F')	//this is a binary file
			{
				resultFont = BMPFont::CreateFromBMPBinary(fontId, *stream);
			}
			else
			{
				SAFE_RELEASE(stream);
				stream = FileSystem::Instance().ReadFile(fontId.ToRef(),FileDataType::Text);
				resultFont = BMPFont::CreateFromBMPText(fontId, *stream);
			}

			SAFE_RELEASE(stream);
		}
		break;
		default:
			return nullptr;
			break;
	}

	Add(resultFont, shareType);
	return resultFont;
}

IFont* FontFactory::CreateFromSingleTexture(const FontId& fontId, wchar_t firstChar /*= L'0'*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		IFont* resultFont = Find(fontId);
		RETURN_SELF_IF_NOT_NULL(resultFont);
	}
	
	BMPFont* resultFont = BMPFont::CreateFromSingleTexture(fontId, firstChar);
	Add(resultFont, shareType);
	return resultFont;
}

IFont* FontFactory::CreateFromMemory(const FontId& fontId, const MemoryByteData& data, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	//TODO: load from data

	IFont* resultFont = Find(fontId);
	RETURN_SELF_IF_NOT_NULL(resultFont);

	FileType fileType = FileInfo::ExtractType(fontId.Name);

	switch (fileType)
	{
		case FileType::pvr:
		{
			resultFont = BMPFont::CreateFromPVR(fontId);
		}
		break;
		case FileType::ttf:
		{
			resultFont = TTFFont::CreateFromFile(fontId);
		}
		break;
		case FileType::fnt:
		{
			const IStream* stream = FileSystem::Instance().ReadFile(fontId.ToRef());
			RETURN_NULL_IF_NULL(stream);

			char c1 = (char)stream->ReadChar();
			char c2 = (char)stream->ReadChar();
			char c3 = (char)stream->ReadChar();

			if (c1 == 'B'&&c2 == 'M'&&c3 == 'F')	//this is a binary file
			{
				resultFont = BMPFont::CreateFromBMPBinary(fontId, *stream);
			}
			else
			{
				SAFE_RELEASE(stream);
				stream = FileSystem::Instance().ReadFile(fontId.ToRef(),FileDataType::Text);
				resultFont = BMPFont::CreateFromBMPText(fontId, *stream);
			}

			SAFE_RELEASE(stream);
		}
		break;
		default:
			return nullptr;
			break;
	}

	Add(resultFont, shareType);
	return resultFont;
}


IMaterial* FontFactory::AddGlyphImage(FontImageDepth destDepth, const Size2U& size, int pitch, const MemoryByteData& imageData, FontImageDepth srcDepth, Size2U& outImageSize, Rect2U& outRect)
{
	outImageSize = Size2U::Zero;
	outRect = Rect2U::Zero;
	RETURN_NULL_IF(size > mMaxImageSize);

	GraphicsInternalFormat destInternalFormat = GraphicsInternalFormat::RGBA;
	GraphicsPixelFormat destPixelFormat = GraphicsPixelFormat::RGBA;
	GraphicsPixelDataType destDataType;

	List<IMaterial*>* materials = nullptr;
	switch (destDepth)
	{
		case FontImageDepth::RGBA:
			materials = &mRGBAMaterials;
			destInternalFormat = GraphicsInternalFormat::RGBA;
			destPixelFormat = GraphicsPixelFormat::RGBA;
			destDataType = GraphicsPixelDataType::Byte;
			break;
		case FontImageDepth::RGB:
			materials = &mRGBMaterials;
			destInternalFormat = GraphicsInternalFormat::RGB;
			destPixelFormat = GraphicsPixelFormat::RGB;
			destDataType = GraphicsPixelDataType::Byte;
			break;
		case FontImageDepth::MonoChrome:
			materials = &mAlphaMaterials;
			destInternalFormat = GraphicsInternalFormat::Alpha;
			destPixelFormat = GraphicsPixelFormat::Alpha;
			destDataType = GraphicsPixelDataType::Byte;
			break;
		default:
			break;
	}

	//GraphicsInternalFormat srcInternalFormat;
	GraphicsPixelFormat srcPixelFormat = GraphicsPixelFormat::RGBA;
	GraphicsPixelDataType srcDataType;
	switch (srcDepth)
	{
		case FontImageDepth::RGBA:
			//srcInternalFormat = GraphicsInternalFormat::RGBA;
			srcPixelFormat = GraphicsPixelFormat::RGBA;
			srcDataType = GraphicsPixelDataType::Byte;
			break;
		case FontImageDepth::RGB:
			//srcInternalFormat = GraphicsInternalFormat::RGB;
			srcPixelFormat = GraphicsPixelFormat::RGB;
			srcDataType = GraphicsPixelDataType::Byte;
			break;
		case FontImageDepth::MonoChrome:
			//srcInternalFormat = GraphicsInternalFormat::Alpha;
			srcPixelFormat = GraphicsPixelFormat::Alpha;
			srcDataType = GraphicsPixelDataType::Byte;

			break;
		default:
			break;
	}
	if (!materials->IsEmpty())
	{
		FOR_EACH_COLLECTION(i, *materials)
		{
			IMaterial* material = *i;
			DynamicAtlasRGBAImage* image = (DynamicAtlasRGBAImage*)material->FirstTexture()->Image();
			if (image->AddImageRect(size, pitch, imageData, srcPixelFormat, srcDataType, outImageSize, outRect, true, GraphicsPixelConvertMode::Alpha))
			{
				return material;
			}
		}
	}

	//at this time all current material is full, add a new image
	DynamicAtlasRGBAImage* image = new DynamicAtlasRGBAImage("TTFFontImage", mInitialImageSize, mMaxImageSize, destInternalFormat, destPixelFormat, false);
	ImageTexture* texture = TextureFactory::Instance().CreateFromImage(image->GetFileId(), image, ShaderSamplerNames::Texture, GraphicsTextureUnits::Texture0);
	IMaterial* material = MaterialFactory::Instance().CreateSingleTexture(texture);
	materials->Add(material);
	SAFE_RETAIN(material);
	if (image->AddImageRect(size, pitch, imageData, srcPixelFormat, srcDataType, outImageSize, outRect, true, GraphicsPixelConvertMode::Alpha))
	{
		return material;
	}
	return nullptr;
}




MEDUSA_END;