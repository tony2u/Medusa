// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Render/Render.h"
#include "Resource/Image/IImage.h"

MEDUSA_BEGIN;

class RGBAImage:public IImage
{
public:
	RGBAImage(const FileIdRef& fileId,Size2U imageSize,PixelType pixelType,bool isPreMultiplyAlpha);
	virtual ~RGBAImage(void);
	virtual ImageFileType ImageType()const{return ImageFileType::raw;}

	void PreMultiplyAlpha();
	void RevertMultipliedAlpha();
	virtual uint GetTextureDataSize(uint mipLevel)const;

};

MEDUSA_END;