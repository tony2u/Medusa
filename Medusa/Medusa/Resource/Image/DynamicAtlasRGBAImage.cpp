// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "DynamicAtlasRGBAImage.h"
#include "Core/Geometry/Size3.h"
#include "Resource/Image/ImageFactory.h"

MEDUSA_BEGIN;

DynamicAtlasRGBAImage::DynamicAtlasRGBAImage(const FileIdRef& fileId,Size2U initImageSize,Size2U maxImageSize,GraphicsInternalFormat internalFormat,GraphicsPixelFormat imageFormat,bool isPreMultiplyAlpha )
	:RGBAImage(fileId,initImageSize,internalFormat,imageFormat,isPreMultiplyAlpha),
	mPack(initImageSize),mMaxImageSize(maxImageSize)
{
	mImageData.ClearZero();
}


DynamicAtlasRGBAImage::~DynamicAtlasRGBAImage(void)
{

}

bool DynamicAtlasRGBAImage::AddImageRect(const Size2U& size,int pitch,const MemoryByteData& imageData,GraphicsPixelFormat pixelFormat,GraphicsPixelDataType srcDataType,
								  Rect2U& outRect, bool isFlipY/*=false*/,GraphicsPixelConvertMode mode/*=PixelConvertMode::Normal*/)
{
	RETURN_FALSE_IF(size>mMaxImageSize);
	outRect=mPack.Insert(size,SkylineBinPack::LevelChoiceHeuristic::LevelBottomLeft);
	if (outRect!=Rect2U::Zero)
	{
		outRect.Size-=1;	//should -1 to remove edge
		CopyImage(outRect,imageData,pixelFormat,srcDataType,pitch,isFlipY,mode);
		return true;
	}

	RETURN_FALSE_IF(mImageSize>=mMaxImageSize);	//is full


	//try to expand
	//1.new a bigger image
	Size2U newImageSize=mImageSize;
	do 
	{
		newImageSize.Width=Math::Min((uint)Math::NextPOT(newImageSize.Width),mMaxImageSize.Width);
		newImageSize.Height=Math::Min((uint)Math::NextPOT(newImageSize.Height),mMaxImageSize.Width);
		mPack.GrowSize(mImageSize);	//not re layout the original rects,maybe do it in the future
		outRect=mPack.Insert(size,SkylineBinPack::LevelChoiceHeuristic::LevelBottomLeft);
		if (outRect!=Rect2U::Zero)
		{
			MemoryByteData newImageData=MemoryByteData::Alloc(mImageSize.Area()*BytesPerComponent());
			//2.copy image data to new image

			ImageFactory::CopyImage(newImageData,mPixelFormat,mPixelDataType,newImageSize,Rect2U(Point2F::Zero,mImageSize),mImageData,mPixelFormat,mPixelDataType,0,false,GraphicsPixelConvertMode::Normal);
			mImageSize=newImageSize;
			mImageData=newImageData;

			//draw new image
			outRect.Size-=1;//should -1 to remove edge
			CopyImage(outRect,imageData,pixelFormat,srcDataType,pitch,isFlipY,mode);
			return true;
		}

	} while (newImageSize<mMaxImageSize);

	return false;
}

MEDUSA_END;