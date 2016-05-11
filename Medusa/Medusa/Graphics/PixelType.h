// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "GraphicsTypes.h"

MEDUSA_BEGIN;


class PixelType
{
public:
	PixelType();
	PixelType(GraphicsInternalFormat internalFormat, GraphicsPixelFormat pixelFormat, GraphicsPixelDataType pixelDataType);
	~PixelType(void);

	bool operator==(const PixelType& val)const { return mInternalFormat == val.mInternalFormat&&mFormat == val.mFormat&&mDataType == val.mDataType; }
	bool operator!=(const PixelType& val)const { return mInternalFormat != val.mInternalFormat || mFormat != val.mFormat || mDataType != val.mDataType; }

	GraphicsInternalFormat InternalFormat() const { return mInternalFormat; }
	void SetInternalFormat(GraphicsInternalFormat val) { mInternalFormat = val; }

	GraphicsPixelFormat Format() const { return mFormat; }
	void SetFormat(GraphicsPixelFormat val) { mFormat = val; }

	GraphicsPixelDataType DataType() const { return mDataType; }
	void SetDataType(GraphicsPixelDataType val) { mDataType = val; }

	bool IsCompressed()const;
	size_t ByteSize()const;
	size_t BytesPerComponent() const;

	bool HasAlpha()const;

	bool IsValid()const { return mInternalFormat != GraphicsInternalFormat::None; }
private:
	GraphicsInternalFormat mInternalFormat = GraphicsInternalFormat::None;
	GraphicsPixelFormat mFormat = GraphicsPixelFormat::None;
	GraphicsPixelDataType mDataType = GraphicsPixelDataType::None;
public:
	const static PixelType None;

	const static PixelType BGRA8888;
	const static PixelType RGBA8888;
	const static PixelType RGBA4444;
	const static PixelType RGBA5551;
	const static PixelType RGB565;
	const static PixelType RGB888;
	const static PixelType A8;
	const static PixelType I8;
	const static PixelType IA88;
	const static PixelType RGBA16161616;
	const static PixelType RGB161616;
	const static PixelType A16;
	const static PixelType I16;
	const static PixelType IA1616;

	const static PixelType RGBA32323232;
	const static PixelType RGB323232;
	const static PixelType A32;
	const static PixelType I32;
	const static PixelType IA3232;

	const static PixelType PVRTC2RGB;
	const static PixelType PVRTC2RGBA;
	const static PixelType PVRTC4RGB;
	const static PixelType PVRTC4RGBA;
	const static PixelType PVRTC2RGBA_2;
	const static PixelType PVRTC4RGBA_2;


	const static PixelType ETC;

	const static PixelType S3TC_DXT1;
	const static PixelType S3TC_DXT3;
	const static PixelType S3TC_DXT5;

	const static PixelType ATC_RGB;
	const static PixelType ATC_RGBA_EXPLICIT_ALPHA;
	const static PixelType ATC_RGBA_INTERPOLATED_ALPHA;
};

MEDUSA_END;
