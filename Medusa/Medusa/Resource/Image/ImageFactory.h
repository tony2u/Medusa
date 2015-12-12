// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/IO/FileDefines.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Image/IImage.h"

MEDUSA_BEGIN;



class ImageFactory :public Singleton<ImageFactory>, public BaseResourceFactory<IImage>
{
	friend class Singleton<ImageFactory>;
	typedef void(*PixelConverter)(byte* dest, const byte* src);
public:
	static uint GetBytesPerComponent(GraphicsPixelFormat format, GraphicsPixelDataType dataType);

	static void CopyImage(MemoryByteData& destData, GraphicsPixelFormat destFormat, GraphicsPixelDataType destDataType, const Size2U& destImageSize,
		const Rect2U& rect, const MemoryByteData& imageData, GraphicsPixelFormat srcFormat, GraphicsPixelDataType srcDataType, int stride = 0, bool isFlipY = false, GraphicsPixelConvertMode mode = GraphicsPixelConvertMode::Normal);
	MEDUSA_FORCE_INLINE static void CopyPixel(byte* dest, GraphicsPixelFormat destFormat, GraphicsPixelDataType destDataType, const byte* src, GraphicsPixelFormat srcFormat, GraphicsPixelDataType srcDataType, GraphicsPixelConvertMode mode = GraphicsPixelConvertMode::Normal);
public:
	ImageFactory();
	~ImageFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	IImage* CreateFromFile(const FileIdRef& fileId, ResourceShareType shareType = ResourceShareType::Share);
	IImage* CreateFromOrderItem(const FileIdRef& fileId, const FileMapOrderItem& orderItem, ResourceShareType shareType = ResourceShareType::Share);

	IImage* CreateFromMemory(const FileIdRef& fileId, MemoryByteData data, ResourceShareType shareType = ResourceShareType::Share);
private:
	MEDUSA_FORCE_INLINE static void RGB_RGBA_Normal(byte* dest, const byte* src);
	MEDUSA_FORCE_INLINE static void RGB_RGBA_Real(byte* dest, const byte* src);
	MEDUSA_FORCE_INLINE static void RGB_RGBA_Alpha(byte* dest, const byte* src);


	MEDUSA_FORCE_INLINE static void RGBA_RGB_Normal(byte* dest, const byte* src);
	MEDUSA_FORCE_INLINE static void RGBA_RGB_Real(byte* dest, const byte* src);

	MEDUSA_FORCE_INLINE static void Alpha_RGBA_Alpha(byte* dest, const byte* src);


	static PixelConverter GetPixelConverter(GraphicsPixelFormat destFormat, GraphicsPixelDataType destDataType, GraphicsPixelFormat srcFormat, GraphicsPixelDataType srcDataType, GraphicsPixelConvertMode mode);
};

MEDUSA_END;