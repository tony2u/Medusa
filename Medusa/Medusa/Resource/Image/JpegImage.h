// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#ifdef MEDUSA_JPEG
#include "Graphics/Render/Render.h"
#include "Resource/Image/RGBAImage.h"

MEDUSA_BEGIN;

class JpegImage:public RGBAImage
{
public:
	JpegImage(const FileIdRef& fileId,Size2U imageSize,PixelType pixelType,bool isPreMultiplyAlpha);
	virtual ~JpegImage(void);
public:
	virtual ImageFileType ImageType()const{return ImageFileType::jpeg;}

	static Share<JpegImage> CreateFromFile(const FileIdRef& fileId);
	static Share<JpegImage> CreateFromMemory(const FileIdRef& fileId, const FileEntry& fileEntry, MemoryData data);
	bool SaveToFile(StringRef filePath)const;

};

MEDUSA_END;
#endif
