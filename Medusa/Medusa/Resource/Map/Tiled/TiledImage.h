// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Geometry/Size2.h"
#include "Geometry/Color4.h"
#include "Core/IO/FileDefines.h"
#include "Core/Memory/MemoryData.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

class TiledImage
{
public:
	TiledImage();
	~TiledImage();

	FileIdRef Source() const { return mSource; }
	void SetSource(const FileIdRef& val) { mSource = val; }

	const Size2I& Size() const { return mSize; }
	void SetSize(Size2I val) { mSize = val; }

	Color4B TransparentColor() const { return mTransparentColor; }
	void SetTransparentColor(Color4B val) { mTransparentColor = val; }

	FileType EmbeddedFileType() const { return mEmbeddedFileType; }
	void SetEmbeddedFileType(FileType val) { mEmbeddedFileType = val; }

	const MemoryData& EmbeddedImageData() const { return mEmbeddedImageData; }
	void SetEmbeddedImageData(const MemoryData& val) { mEmbeddedImageData = val; }

	bool Parse(const pugi::xml_node& node);

	bool LoadTiledTexture(Size2I tileSize);
	Share<ITexture> LoadSeparateTexture()const;

	TextureAtlasPage* TexturePage() const { return mTexturePage; }

private:
	FileId mSource;
	Size2I mSize;
	Color4B mTransparentColor;

	FileType mEmbeddedFileType;
	MemoryData mEmbeddedImageData;
	
	TextureAtlasPage* mTexturePage=nullptr;
	Share<TextureAtlas> mTextureAtlas;
};

MEDUSA_END;
