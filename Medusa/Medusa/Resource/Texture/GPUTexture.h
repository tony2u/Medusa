// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Texture/ITexture.h"
#include "Graphics/GraphicsPixelDataType.h"

MEDUSA_BEGIN;

class GPUTexture:public ITexture
{
public:
	GPUTexture(const FileIdRef& fileId,const Size2U& size,GraphicsTextureType textureType=GraphicsTextureType::Texture2D,GraphicsTextureTarget textureTarget=GraphicsTextureTarget::Texture2D,GraphicsInternalFormat internalFormat=GraphicsInternalFormat::RGB,
		int level=0,int border=0,GraphicsPixelFormat pixelFormat=GraphicsPixelFormat::RGB,GraphicsPixelDataType pixelType=GraphicsPixelDataType::Byte,StringRef samplerName=StringRef::Empty,GraphicsTextureUnits unit=GraphicsTextureUnits::Texture0);
	virtual ~GPUTexture(void);
public:
	virtual IImage* Image() const{return nullptr;}

	virtual bool IsBlend()const;
	virtual Size2U Size() const{return mSize;}
	virtual void ResetDefaultParameters();

	GraphicsTextureTarget TextureTarget() const { return mTextureTarget; }
	GraphicsInternalFormat Internalformat() const { return mInternalformat; }
	int Level() const { return mLevel; }
	int Border() const { return mBorder; }
	GraphicsPixelFormat PixelFormat() const { return mPixelFormat; }
	GraphicsPixelDataType PixelType() const { return mPixelType; }

protected:
	virtual void Upload();
protected:
	Size2U mSize;
	GraphicsTextureTarget mTextureTarget;
	GraphicsInternalFormat mInternalformat;
	int mLevel;
	int mBorder;
	GraphicsPixelFormat mPixelFormat;
	GraphicsPixelDataType mPixelType;
};

MEDUSA_END;