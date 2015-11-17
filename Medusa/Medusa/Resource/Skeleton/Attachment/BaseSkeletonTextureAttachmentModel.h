// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ISkeletonAttachmentModel.h"
#include "Core/Geometry/Color4.h"
#include "Core/Geometry/Size3.h"

MEDUSA_BEGIN;


class BaseSkeletonTextureAttachmentModel:public ISkeletonAttachmentModel
{
public:
	BaseSkeletonTextureAttachmentModel(const StringRef& name, TextureAtlasRegion* region);
	virtual ~BaseSkeletonTextureAttachmentModel();

	TextureAtlasRegion* Region() const { return mRegion; }
	
	const Size3F& Size() const { return mSize; }
	void SetSize(const Size3F& val) { mSize = val; }

	const Color4F& Color() const { return mColor; }
	void SetColor(const Color4F& val) { mColor = val; }

protected:
	TextureAtlasRegion* mRegion;
	Size3F mSize;
	Color4F mColor;
};

MEDUSA_END;
