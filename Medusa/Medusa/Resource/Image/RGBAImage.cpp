// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RGBAImage.h"
#include "Geometry/Color4.h"
#include "Rendering/RenderingStatics.h"

MEDUSA_BEGIN;

RGBAImage::RGBAImage(const FileIdRef& fileId,Size2U imageSize, PixelType pixelType,bool isPreMultiplyAlpha )
	:IImage(fileId,pixelType)
{
	mImageSize=imageSize;
	mIsPreMultiplyAlpha=isPreMultiplyAlpha;

	if (!HasAlpha())
	{
		mIsPreMultiplyAlpha=false;
	}
	

	uint bytesPerComponent=BytesPerComponent();
	uint imageDataSize=mImageSize.Width*mImageSize.Height*bytesPerComponent;
	mImageData=MemoryData::AllocZero(imageDataSize);
	RenderingStatics::Instance().IncreaseTextureMemorySize(imageDataSize);
}


RGBAImage::~RGBAImage(void)
{

}

void RGBAImage::PreMultiplyAlpha()
{
	/*
	Premultiplied alpha is just a different way of representing alphified pixels. 
	If the separate alpha pixel is (r, g, b, a), then the premultiplied alpha pixel is (ar, ag, ab, a).

	The reason why it's interesting is that linear combinations of pixels (i.e. a1p1 + a2p2) work better in premultiplied alpha space than in separate alpha space.
	*/

	RETURN_IF_FALSE(HasAlpha());
	RETURN_IF_TRUE(mIsPreMultiplyAlpha);

	//deal with RGBA format
	const int bytesPerRow = mImageSize.Width * 4;
	FOR_EACH_SIZE(i,mImageSize.Height)
	{
		FOR_EACH_SIZE(j,mImageSize.Width)
		{
			byte* colorInt=mImageData.MutableData()+i*bytesPerRow+j;
			colorInt[0]=(char)((uint)colorInt[0]*(uint)colorInt[3]>>8);
			colorInt[1]=(char)((uint)colorInt[1]*(uint)colorInt[3]>>8);
			colorInt[2]=(char)((uint)colorInt[2]*(uint)colorInt[3]>>8);
		}
	}

	mIsPreMultiplyAlpha=true;
}


void RGBAImage::RevertMultipliedAlpha()
{
	RETURN_IF_FALSE(HasAlpha());
	RETURN_IF_FALSE(mIsPreMultiplyAlpha);

	const int bytesPerRow = mImageSize.Width * 4;
	FOR_EACH_SIZE(i,mImageSize.Height)
	{
		FOR_EACH_SIZE(j,mImageSize.Width)
		{
			byte* colorInt=mImageData.MutableData()+i*bytesPerRow+j;

			colorInt[0]=(char)((uint)colorInt[0]<<8/(uint)colorInt[3]);
			colorInt[1]=(char)((uint)colorInt[1]<<8/(uint)colorInt[3]);
			colorInt[2]=(char)((uint)colorInt[2]<<8/(uint)colorInt[3]);
		}
	}

	mIsPreMultiplyAlpha=false;

}

uint RGBAImage::GetTextureDataSize( uint mipLevel ) const
{
	return Math::Max(1U,mImageSize.Width>>mipLevel)*Math::Max(1U,mImageSize.Height>>mipLevel)*sizeof(Color4B);
}

MEDUSA_END;