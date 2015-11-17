// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledImage.h"

MEDUSA_BEGIN;

TiledImage::TiledImage()
	:mSize(Size2I::Zero),
	mTransparentColor(Color4B::Black),
	mEmbeddedFileType(FileType::Unknown)
{
}

TiledImage::~TiledImage()
{
}

MEDUSA_END;