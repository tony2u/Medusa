// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/Size2.h"
#include "Core/Geometry/Color4.h"
#include "Core/IO/FileDefines.h"
#include "Core/Memory/MemoryData.h"

MEDUSA_BEGIN;

class TiledImage
{
public:
	TiledImage();
	~TiledImage();

	StringRef Source() const { return mSource; }
	void SetSource(const StringRef& val) { mSource = val; }

	const Size2I& Size() const { return mSize; }
	void SetSize(Size2I val) { mSize = val; }

	Color4B TransparentColor() const { return mTransparentColor; }
	void SetTransparentColor(Color4B val) { mTransparentColor = val; }

	FileType EmbeddedFileType() const { return mEmbeddedFileType; }
	void SetEmbeddedFileType(FileType val) { mEmbeddedFileType = val; }

	const MemoryByteData& EmbeddedImageData() const { return mEmbeddedImageData; }
	void SetEmbeddedImageData(const MemoryByteData& val) { mEmbeddedImageData = val; }
private:
	HeapString mSource;
	Size2I mSize;
	Color4B mTransparentColor;

	FileType mEmbeddedFileType;
	MemoryByteData mEmbeddedImageData;
	
};

MEDUSA_END;
