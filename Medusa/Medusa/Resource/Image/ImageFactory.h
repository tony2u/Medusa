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
#include "Graphics/PixelType.h"

MEDUSA_BEGIN;



class ImageFactory :public Singleton<ImageFactory>, public BaseResourceFactory<IImage>
{
	friend class Singleton<ImageFactory>;
	typedef void(*PixelConverter)(byte* dest, const byte* src);
public:
	static void CopyImage(MemoryData& destData, PixelType destFormat, const Size2U& destImageSize, const Rect2U& rect, const MemoryData& imageData, PixelType srcFormat, int stride = 0, bool isFlipY = false, GraphicsPixelConvertMode mode = GraphicsPixelConvertMode::Normal);
	MEDUSA_FORCE_INLINE static void CopyPixel(byte* dest, PixelType destFormat, const byte* src, PixelType srcFormat, GraphicsPixelConvertMode mode = GraphicsPixelConvertMode::Normal);
public:
	ImageFactory();
	~ImageFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	IImage* CreateFromFile(const FileIdRef& fileId, ResourceShareType shareType = ResourceShareType::Share);
	IImage* CreateFromOrderItem(const FileIdRef& fileId, const FileMapOrderItem& orderItem, ResourceShareType shareType = ResourceShareType::Share);

	IImage* CreateFromMemory(const FileIdRef& fileId, const FileEntry& fileEntry, MemoryData data, ResourceShareType shareType = ResourceShareType::Share);
private:
	MEDUSA_FORCE_INLINE static void RGB_RGBA_Normal(byte* dest, const byte* src);
	MEDUSA_FORCE_INLINE static void RGB_RGBA_Real(byte* dest, const byte* src);
	MEDUSA_FORCE_INLINE static void RGB_RGBA_Alpha(byte* dest, const byte* src);


	MEDUSA_FORCE_INLINE static void RGBA_RGB_Normal(byte* dest, const byte* src);
	MEDUSA_FORCE_INLINE static void RGBA_RGB_Real(byte* dest, const byte* src);

	MEDUSA_FORCE_INLINE static void Alpha_RGBA_Alpha(byte* dest, const byte* src);


	static PixelConverter GetPixelConverter(PixelType destFormat, PixelType srcFormat, GraphicsPixelConvertMode mode);
};

MEDUSA_END;