// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Render/Render.h"
#include "Geometry/Size2.h"
#include "Core/IO/FileDefines.h"
#include "Core/Memory/MemoryData.h"
#include "Resource/IResource.h"
#include "Graphics/PixelType.h"

MEDUSA_BEGIN;

class IImage :public IResource
{
public:
	IImage(const FileIdRef& fileId , PixelType pixelType);
	virtual ~IImage(void);
	virtual ResourceType Type()const { return ResourceType::Image; }
	static ResourceType ClassGetResourceType() { return ResourceType::Image; }


	virtual ImageFileType ImageType()const = 0;

	bool HasAlpha()const { return mPixelType.HasAlpha(); }

	bool IsPreMultiplyAlpha() const { return mIsPreMultiplyAlpha; }
	bool IsCompressed() const { return mPixelType.IsCompressed(); }
	uint MipMapCount() const { return mMipMapCount; }
	uint FaceCount() const { return mFaceCount; }

	PixelType GetPixelType() const { return mPixelType; }
	void SetPixelType(PixelType val) { mPixelType = val; }

	GraphicsTextureType TextureType() const { return mTextureType; }
	uint BytesPerComponent() const { return (uint)mPixelType.BytesPerComponent(); }

	const MemoryData& Data() const { return mImageData; }
	MemoryData& MutableData() { return mImageData; }

	size_t ByteSize()const { return mImageData.Size(); }
	Size2U Size() const { return mImageSize; }
	bool IsPOTImageSize()const;

	const HeapString& FilePath() const { return mFilePath; }
	void ReleaseImageData();
	bool HasImageData()const { return mImageData.IsValid(); }

	void CopyImage(const Rect2U& rect, const MemoryData& imageData, PixelType srcPixelFormat, int stride = 0, bool isFlipY = false, GraphicsPixelConvertMode mode = GraphicsPixelConvertMode::Normal);

	virtual bool Upload();
	virtual uint GetTextureDataSize(uint mipLevel)const = 0;
protected:
	HeapString mFilePath;

	GraphicsTextureType mTextureType = GraphicsTextureType::Texture2D;
	PixelType mPixelType;

	Size2U mImageSize;
	MemoryData mImageData;

	uint mMipMapCount = 1;
	uint mFaceCount = 1;
	bool mIsPreMultiplyAlpha = false;

};

MEDUSA_END;