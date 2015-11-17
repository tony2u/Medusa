// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Render/Render.h"
#include "Resource/Image/RGBAImage.h"
#include "PngImageColorType.h"

MEDUSA_BEGIN;

class PngImage:public RGBAImage
{
	
public:
	PngImage(const FileIdRef& fileId,Size2U imageSize,GraphicsInternalFormat internalFormat,GraphicsPixelFormat imageFormat,bool isPreMultiplyAlpha);
	virtual ~PngImage(void);
public:
	virtual ImageFileType ImageType()const{return ImageFileType::png;}

	static PngImage* CreateFromFile(const FileIdRef& fileId);
	static PngImage* CreateFromMemory(const FileIdRef& fileId,MemoryByteData data);
	bool SaveToFile(StringRef filePath)const;

};

MEDUSA_END;