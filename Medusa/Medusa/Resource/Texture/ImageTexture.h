// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Texture/ITexture.h"

MEDUSA_BEGIN;

class ImageTexture:public ITexture
{
public:
	ImageTexture(const FileIdRef& fileId, const Share<IImage>& image, StringRef samplerName = ShaderSamplerNames::Texture, GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0);
	virtual ~ImageTexture(void);
public:
	virtual Share<IImage> Image() const { return mImage; }

	virtual bool IsBlend()const;
	virtual Size2U Size() const;
	virtual void ResetDefaultParameters();

protected:
	virtual void Upload();
protected:
	Share<IImage> mImage;
};

MEDUSA_END;