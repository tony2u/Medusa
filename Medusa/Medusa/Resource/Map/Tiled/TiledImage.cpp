// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledImage.h"
#include "TmxTiledMap.h"
#include "Core/Coder/Crypt/Base64Decoder.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/Texture/TextureFactory.h"
#include "Resource/Texture/ImageTexture.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"


MEDUSA_BEGIN;

TiledImage::TiledImage()
	:mSize(Size2I::Zero),
	mTransparentColor(Color4B::Black),
	mEmbeddedFileType(FileType::None)
{
}

TiledImage::~TiledImage()
{
	if (mTexturePage != nullptr)
	{
		mTexturePage->Atlas()->Release();
	}
		
}

bool TiledImage::Parse(const pugi::xml_node& node)
{
	// Read all the attribute into member variables.
	mSource = node.attribute("source").as_string(nullptr);
	if (mSource.IsEmpty())
	{
		Log::AssertFailed("Invalid image xml node source attribute");
		return false;
	}

	mSize.Width = node.attribute("width").as_int(0);
	mSize.Height = node.attribute("height").as_int(0);

	const char* transparentColorStr = node.attribute("trans").as_string(nullptr);
	mTransparentColor = TmxTiledMap::ParseColor(transparentColorStr);


	StringRef formatStr = node.attribute("format").as_string(nullptr);

	if (formatStr == "png")
	{
		mEmbeddedFileType=FileType::png;
	}
	else if (formatStr == "jpg")
	{
		mEmbeddedFileType=FileType::jpeg;
	}
	else if (!formatStr.IsEmpty())
	{
		Log::FormatError("Unsupported image type:{}", formatStr.c_str());
		return false;
	}

	pugi::xml_node dataNode = node.child("data");
	if (!dataNode.empty())
	{
		StringRef encodingStr = node.attribute("encoding").as_string(nullptr);
		StringRef compressionStr = node.attribute("compression").as_string(nullptr);
		if (encodingStr != "base64")
		{
			Log::FormatError("Unsupported encoding type:{}", encodingStr.c_str());
			return false;
		}

		const char* text = dataNode.value();
		Base64Decoder decoder;
		mEmbeddedImageData = decoder.Code(text);
	}

	return true;
}


bool TiledImage::LoadTiledTexture(Size2I tileSize)
{
	auto* textureAtlas=TextureAtlasFactory::Instance().CreateTiledAtlas(mSource, mSize, tileSize);
	RETURN_FALSE_IF_NULL(textureAtlas);
	mTexturePage = textureAtlas->FindPage(0);
	if (mTexturePage!=nullptr)
	{
		SAFE_RETAIN(mTexturePage->Atlas());
	}
	return true;
}


ITexture* TiledImage::LoadSeparateTexture()const
{
	return TextureFactory::Instance().CreateFromFile(mSource);
}

MEDUSA_END;