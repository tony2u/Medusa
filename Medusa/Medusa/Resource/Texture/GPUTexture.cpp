// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GPUTexture.h"
#include "Resource/Image/IImage.h"

MEDUSA_BEGIN;


GPUTexture::GPUTexture( const FileIdRef& fileId,const Size2U& size,GraphicsTextureType textureType/*=GraphicsTextureType::Texture2D*/,
					   GraphicsTextureTarget textureTarget/*=GraphicsTextureTarget::Texture2D*/,
						PixelType pixelType /*= PixelType::RGB888*/,
					   int level/*=0*/,
					   int border/*=0*/,
					   StringRef samplerName/*=StringRef::Empty*/,
					   GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/)
	:ITexture(fileId,textureType,samplerName,unit),
	mSize(size),
	mTextureTarget(textureTarget),
	mPixelType(pixelType),
	mLevel(level),
	mBorder(border)
{

}


GPUTexture::~GPUTexture(void)
{
	
}

void GPUTexture::Upload() 
{
	RETURN_IF_TRUE(mIsLoaded);
	//data may be a null pointer. In this case, texture memory is allocated to accommodate a texture of width width and height height.
	//You can then download subtextures to initialize this texture memory. 
	Render::Instance().LoadTexture(mTextureTarget,mLevel, mPixelType,mSize,mBorder, nullptr);
	mIsLoaded=true;
}


void GPUTexture::ResetDefaultParameters()
{
	mSamplerState->SetMagFilter(GraphicsTextureMagFilter::Linear);
	mSamplerState->SetMinFilter(GraphicsTextureMinFilter::Linear);

	if (Math::IsPowerOfTwo(mSize.Width)&&Math::IsPowerOfTwo(mSize.Height))
	{
		mSamplerState->SetWrapS(GraphicsTextureWrapMode::ClampToEdge);
		mSamplerState->SetWrapT(GraphicsTextureWrapMode::ClampToEdge);
	}
	else
	{
		mSamplerState->SetWrapS(GraphicsTextureWrapMode::Repeat);
		mSamplerState->SetWrapT(GraphicsTextureWrapMode::Repeat);
	}


}

bool GPUTexture::IsBlend() const
{
	return false;
}


MEDUSA_END;