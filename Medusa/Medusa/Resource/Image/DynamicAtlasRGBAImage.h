// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Image/RGBAImage.h"
#include "Core/Algorithm/Pack/SkylineBinPack.h"

MEDUSA_BEGIN;

class DynamicAtlasRGBAImage:public RGBAImage
{
public:
	DynamicAtlasRGBAImage(const FileIdRef& fileId,Size2U initImageSize,Size2U maxImageSize,GraphicsInternalFormat internalFormat,GraphicsPixelFormat imageFormat,bool isPreMultiplyAlpha);
	virtual ~DynamicAtlasRGBAImage(void);
public:
	Size2U MaxImageSize() const { return mMaxImageSize; }
	void SetMaxImageSize(Size2U val) { mMaxImageSize = val; }

	bool IsExpandable() const { return mMaxImageSize<=mImageSize; }

	bool AddImageRect(const Size2U& size,int pitch,const MemoryByteData& imageData,GraphicsPixelFormat pixelFormat,GraphicsPixelDataType srcDataType,Size2U& outImageSize,Rect2U& outRect,bool isFlipY=false,GraphicsPixelConvertMode mode=GraphicsPixelConvertMode::Normal);
protected:
	SkylineBinPack mPack;
	Size2U mMaxImageSize;
	
};

MEDUSA_END;