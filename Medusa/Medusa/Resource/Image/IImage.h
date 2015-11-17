// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Render/Render.h"
#include "Core/Geometry/Size2.h"
#include "Core/IO/FileDefines.h"
#include "Core/Memory/MemoryData.h"
#include "Resource/IResource.h"

MEDUSA_BEGIN;

class IImage:public IResource
{
public:

public:
	IImage(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~IImage(void);
	virtual ResourceType Type()const{return ResourceType::Image;}
	static ResourceType ClassGetResourceType(){return ResourceType::Image;}


	virtual ImageFileType ImageType()const=0;
	bool IsBlend() const { return mIsBlend; }
	void SetIsBlend(bool val) { mIsBlend = val; }

	bool HasAlpha()const;

	bool IsPreMultiplyAlpha() const{return mIsPreMultiplyAlpha;}
	bool IsCompressed() const { return mIsCompressed; }
	uint MipMapCount() const { return mMipMapCount; }
	uint FaceCount() const { return mFaceCount; }

	GraphicsTextureType TextureType() const { return mTextureType; }

	GraphicsInternalFormat InternalFormat() const { return mInternalFormat; }
	GraphicsPixelFormat PixelFormat() const { return mPixelFormat; }
	GraphicsPixelDataType PixelDataType() const { return mPixelDataType; }
	uint BytesPerComponent() const;

	const MemoryByteData& Data() const { return mImageData; }
	MemoryByteData& MutableData() { return mImageData; }

	size_t ByteSize()const{return mImageData.Size();}
	Size2U Size() const { return mImageSize; }
	bool IsPOTImageSize()const;

	const HeapString& FilePath() const { return mFilePath; }
	void ReleaseImageData();
	bool HasImageData()const{return mImageData.IsValid();}

	void CopyImage(const Rect2U& rect,const MemoryByteData& imageData,GraphicsPixelFormat pixelFormat,GraphicsPixelDataType srcDataType,int stride=0,bool isFlipY=false,GraphicsPixelConvertMode mode=GraphicsPixelConvertMode::Normal);


	virtual bool Upload();
	virtual uint GetTextureDataSize(uint mipLevel)const=0;
protected:
	HeapString mFilePath;
	
	GraphicsTextureType mTextureType= GraphicsTextureType::Texture2D;
	GraphicsInternalFormat mInternalFormat= GraphicsInternalFormat::RGBA;
	GraphicsPixelFormat mPixelFormat= GraphicsPixelFormat::RGBA;
	GraphicsPixelDataType mPixelDataType= GraphicsPixelDataType::Byte;
	
	Size2U mImageSize;
	MemoryByteData mImageData;

	uint mMipMapCount=1;
	uint mFaceCount=1;
	bool mIsCompressed=false;
	bool mIsPreMultiplyAlpha=false;
	bool mIsBlend=false;
	
};

MEDUSA_END;