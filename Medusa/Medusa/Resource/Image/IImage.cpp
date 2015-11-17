// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IImage.h"
#include "Core/Math/Math.h"
#include "Rendering/RenderingStatics.h"
#include "Core/Geometry/Size3.h"
#include "Resource/Image/ImageFactory.h"

MEDUSA_BEGIN;

IImage::IImage(const FileIdRef& fileId/*=FileId::Empty*/)
	:IResource(fileId), mFilePath(fileId.Name)
{

}


IImage::~IImage(void)
{
	if (mImageData.IsValid())
	{
		RenderingStatics::Instance().DecreaseTextureMemorySize(mImageData.Size());
	}
}

bool IImage::HasAlpha() const
{
	switch (mInternalFormat)
	{
	case GraphicsInternalFormat::RGBA:
	case GraphicsInternalFormat::LuminanceAlpha:
	case GraphicsInternalFormat::Alpha:
		return true;
	default:
		return false;
	}

}


uint IImage::BytesPerComponent() const
{
	return ImageFactory::GetBytesPerComponent(mPixelFormat, mPixelDataType);
}


bool IImage::Upload()
{
	GraphicsTextureTarget startTextureTarget;
	if (mTextureType == GraphicsTextureType::Texture2D)
	{
		startTextureTarget = GraphicsTextureTarget::Texture2D;
	}
	else
	{
		startTextureTarget = GraphicsTextureTarget::TextureCubeMapPositiveX;
	}

	if (mIsCompressed)
	{
		//PVR files are never row aligned.

		byte* tempData = mImageData.MutableData();
		Size2U mipImageSize = mImageSize;

		FOR_EACH_SIZE(i, mMipMapCount)
		{
			size_t currentImageDataSize = GetTextureDataSize((uint)i);
			GraphicsTextureTarget textureTarget = startTextureTarget;
			FOR_EACH_SIZE(j, mFaceCount)
			{
				Render::Instance().LoadCompressedTexture(textureTarget, (int)i, mInternalFormat, mipImageSize, 0, (uint)currentImageDataSize, tempData);
				tempData += currentImageDataSize;
				textureTarget = (GraphicsTextureTarget)((uint)textureTarget + 1);
			}

			mipImageSize.Width = Math::Max(1U, mipImageSize.Width >> 1);
			mipImageSize.Height = Math::Max(1U, mipImageSize.Height >> 1);

		}
	}
	else
	{
		byte* tempData = mImageData.MutableData();
		Size2U mipImageSize = mImageSize;

		FOR_EACH_SIZE(i, mMipMapCount)
		{
			size_t currentImageDataSize = GetTextureDataSize((uint)i);
			GraphicsTextureTarget textureTarget = startTextureTarget;
			FOR_EACH_SIZE(j, mFaceCount)
			{
				Render::Instance().LoadTexture(textureTarget, (uint)i, mInternalFormat, mipImageSize, 0, mPixelFormat, mPixelDataType, tempData);
				tempData += currentImageDataSize;
				textureTarget = (GraphicsTextureTarget)((uint)textureTarget + 1);
			}

			mipImageSize.Width = Math::Max(1U, mipImageSize.Width >> 1);
			mipImageSize.Height = Math::Max(1U, mipImageSize.Height >> 1);
		}
	}

	RenderingStatics::Instance().IncreaseTextureGPUSize(ByteSize());	//TODO: more concrete size
	return true;
}

bool IImage::IsPOTImageSize() const
{
	return Math::IsPowerOfTwo(mImageSize.Width) && Math::IsPowerOfTwo(mImageSize.Height);
}

void IImage::ReleaseImageData()
{
	mImageData.ForceRelease();
	RenderingStatics::Instance().DecreaseTextureMemorySize(mImageData.Size());

}

void IImage::CopyImage(const Rect2U& rect, const MemoryByteData& imageData, GraphicsPixelFormat pixelFormat, GraphicsPixelDataType srcDataType, int stride/*=0*/, bool isFlipY/*=false*/, GraphicsPixelConvertMode mode/*=PixelConvertMode::Normal*/)
{
	ImageFactory::CopyImage(mImageData, mPixelFormat, mPixelDataType, mImageSize, rect, imageData, pixelFormat, srcDataType, stride, isFlipY, mode);
}


MEDUSA_END;