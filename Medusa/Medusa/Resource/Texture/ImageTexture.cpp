// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ImageTexture.h"
#include "Resource/Image/IImage.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;

ImageTexture::ImageTexture(const FileIdRef& fileId,IImage* image,StringRef samplerName/*=ShaderSamplerNames::Texture*/,GraphicsTextureUnits unit/*=GraphicsTextureUnits::Texture0*/)
	:ITexture(fileId,image->TextureType(),samplerName,unit),
	mImage(image)
{
	SAFE_RETAIN(mImage);
}


ImageTexture::~ImageTexture(void)
{
	if (mIsLoaded&&mImage != nullptr)
	{
		RenderingStatics::Instance().DecreaseTextureGPUSize(mImage->ByteSize());
		mIsLoaded = false;
	}

	SAFE_RELEASE(mImage);
}

void ImageTexture::Upload()
{
	RETURN_IF_TRUE(mIsLoaded);
	mImage->Upload();
	mIsLoaded = true;
}


void ImageTexture::ResetDefaultParameters()
{
	if (mImage->BytesPerComponent() != 4 || mImage->ImageType() == ImageFileType::pvr)
	{
		// glTexImage2d requires rows to be 4-byte aligned, so we have to remind him of this
		mPixelStoreState->SetUnpackAlignment(1);
	}

	if (mImage->GetPixelType().DataType()==GraphicsPixelDataType::FloatOES||mImage->GetPixelType().DataType() ==GraphicsPixelDataType::HalfFloatOES)
	{
		if (mImage->MipMapCount()==1)
		{
			mSamplerState->SetMinFilter(GraphicsTextureMinFilter::Nearest);
			mSamplerState->SetMagFilter(GraphicsTextureMagFilter::Nearest);
		}
		else
		{
			mSamplerState->SetMinFilter(GraphicsTextureMinFilter::NearestMipMapNearest);
			mSamplerState->SetMagFilter(GraphicsTextureMagFilter::Nearest);
		}
	}
	else
	{
		if (mImage->MipMapCount()==1)
		{
			mSamplerState->SetMinFilter(GraphicsTextureMinFilter::Linear);
			mSamplerState->SetMagFilter(GraphicsTextureMagFilter::Linear);
		}
		else
		{
			mSamplerState->SetMinFilter(GraphicsTextureMinFilter::LinearMipMapNearest);
			mSamplerState->SetMagFilter(GraphicsTextureMagFilter::Linear);
		}
	}

	if (!mImage->IsPOTImageSize())
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

bool ImageTexture::IsBlend() const
{
	return mImage->HasAlpha();
}

Size2U ImageTexture::Size() const
{
	return mImage->Size();
}

MEDUSA_END;