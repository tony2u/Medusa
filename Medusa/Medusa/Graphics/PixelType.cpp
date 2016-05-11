// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PixelType.h"

MEDUSA_BEGIN;

PixelType::PixelType()
{

}

PixelType::PixelType(GraphicsInternalFormat internalFormat, GraphicsPixelFormat pixelFormat, GraphicsPixelDataType pixelDataType)
	:mInternalFormat(internalFormat), mFormat(pixelFormat), mDataType(pixelDataType)
{

}

PixelType::~PixelType(void)
{

}


bool PixelType::IsCompressed() const
{
	switch (mInternalFormat)
	{
	case GraphicsInternalFormat::Compressed_RGB_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG:
	case GraphicsInternalFormat::Compressed_ETC1_RGB8_OES:
	case GraphicsInternalFormat::S3TC_DXT1:
	case GraphicsInternalFormat::S3TC_DXT3:
	case GraphicsInternalFormat::S3TC_DXT5:
	case GraphicsInternalFormat::ATC_RGB:
	case GraphicsInternalFormat::ATC_RGBA_EXPLICIT_ALPHA:
	case GraphicsInternalFormat::ATC_RGBA_INTERPOLATED_ALPHA:
		return true;
	default:
		return false;
	}
}

size_t PixelType::ByteSize() const
{
	switch (mInternalFormat)
	{
	case GraphicsInternalFormat::BGRA:
		return 32;
	case GraphicsInternalFormat::RGBA:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 32;
		case GraphicsPixelDataType::UnsignedShort4444:
		case GraphicsPixelDataType::UnsignedShort5551:
			return 16;
		case GraphicsPixelDataType::HalfFloatOES:
			return 64;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 128;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::RGB:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 24;
		case GraphicsPixelDataType::UnsignedShort565:
			return 16;
		case GraphicsPixelDataType::HalfFloatOES:
			return 48;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 96;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::Alpha:
	case GraphicsInternalFormat::Luminance:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 8;
		case GraphicsPixelDataType::HalfFloatOES:
			return 16;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 32;
		default:
			break;
		}
		break;

	case GraphicsInternalFormat::LuminanceAlpha:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 16;
		case GraphicsPixelDataType::HalfFloatOES:
			return 32;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 64;
		default:
			break;
		}
		break;

	case GraphicsInternalFormat::DepthComponent:
		switch (mDataType)
		{
		case GraphicsPixelDataType::HalfFloatOES:
			return 16;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 32;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::Compressed_RGB_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG:
	case GraphicsInternalFormat::Compressed_ETC1_RGB8_OES:
	case GraphicsInternalFormat::S3TC_DXT1:
	case GraphicsInternalFormat::ATC_RGB:
		return 4;
	case GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG:
		return 2;
	case GraphicsInternalFormat::S3TC_DXT3:
	case GraphicsInternalFormat::S3TC_DXT5:
	case GraphicsInternalFormat::ATC_RGBA_EXPLICIT_ALPHA:
	case GraphicsInternalFormat::ATC_RGBA_INTERPOLATED_ALPHA:
		return 8;
	default:
		break;
	}
	return 0;
}


size_t PixelType::BytesPerComponent() const
{
	switch (mInternalFormat)
	{
	case GraphicsInternalFormat::BGRA:
		return 4;
	case GraphicsInternalFormat::RGBA:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 4;
		case GraphicsPixelDataType::UnsignedShort4444:
		case GraphicsPixelDataType::UnsignedShort5551:
			return 2;
		case GraphicsPixelDataType::HalfFloatOES:
			return 8;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 16;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::RGB:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 3;
		case GraphicsPixelDataType::UnsignedShort565:
			return 2;
		case GraphicsPixelDataType::HalfFloatOES:
			return 6;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 12;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::Alpha:
	case GraphicsInternalFormat::Luminance:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 1;
		case GraphicsPixelDataType::HalfFloatOES:
			return 2;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 4;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::LuminanceAlpha:
		switch (mDataType)
		{
		case GraphicsPixelDataType::Byte:
			return 2;
		case GraphicsPixelDataType::HalfFloatOES:
			return 4;
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 8;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::DepthComponent:
		switch (mDataType)
		{
		case GraphicsPixelDataType::FloatOES:
		case GraphicsPixelDataType::UInt:
			return 4;
		default:
			break;
		}
		break;
	case GraphicsInternalFormat::Compressed_RGB_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG:
	case GraphicsInternalFormat::Compressed_ETC1_RGB8_OES:
	case GraphicsInternalFormat::S3TC_DXT1:
	case GraphicsInternalFormat::ATC_RGB:
		return 1;
	case GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG:
		return 1;
	case GraphicsInternalFormat::S3TC_DXT3:
	case GraphicsInternalFormat::S3TC_DXT5:
	case GraphicsInternalFormat::ATC_RGBA_EXPLICIT_ALPHA:
	case GraphicsInternalFormat::ATC_RGBA_INTERPOLATED_ALPHA:
		return 1;
	default:
		break;
	}
	return 0;
}

bool PixelType::HasAlpha() const
{
	switch (mInternalFormat)
	{
	case GraphicsInternalFormat::RGBA:
	case GraphicsInternalFormat::LuminanceAlpha:
	case GraphicsInternalFormat::Alpha:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG:
	case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG:
		return true;
	default:
		return false;
	}
}

const PixelType PixelType::None;

const PixelType PixelType::BGRA8888(GraphicsInternalFormat::BGRA, GraphicsPixelFormat::BGRA, GraphicsPixelDataType::Byte);
const PixelType PixelType::RGBA8888(GraphicsInternalFormat::RGBA, GraphicsPixelFormat::RGBA, GraphicsPixelDataType::Byte);
const PixelType PixelType::RGBA4444(GraphicsInternalFormat::RGBA, GraphicsPixelFormat::RGBA, GraphicsPixelDataType::UnsignedShort4444);
const PixelType PixelType::RGBA5551(GraphicsInternalFormat::RGBA, GraphicsPixelFormat::RGBA, GraphicsPixelDataType::UnsignedShort5551);
const PixelType PixelType::RGB565(GraphicsInternalFormat::RGB, GraphicsPixelFormat::RGB, GraphicsPixelDataType::UnsignedShort565);
const PixelType PixelType::RGB888(GraphicsInternalFormat::RGB, GraphicsPixelFormat::RGB, GraphicsPixelDataType::Byte);
const PixelType PixelType::A8(GraphicsInternalFormat::Alpha, GraphicsPixelFormat::Alpha, GraphicsPixelDataType::Byte);
const PixelType PixelType::I8(GraphicsInternalFormat::Luminance, GraphicsPixelFormat::Luminance, GraphicsPixelDataType::Byte);
const PixelType PixelType::IA88(GraphicsInternalFormat::LuminanceAlpha, GraphicsPixelFormat::LuminanceAlpha, GraphicsPixelDataType::Byte);
const PixelType PixelType::RGBA16161616(GraphicsInternalFormat::RGBA, GraphicsPixelFormat::RGBA, GraphicsPixelDataType::HalfFloatOES);
const PixelType PixelType::RGB161616(GraphicsInternalFormat::RGB, GraphicsPixelFormat::RGB, GraphicsPixelDataType::HalfFloatOES);
const PixelType PixelType::A16(GraphicsInternalFormat::Alpha, GraphicsPixelFormat::Alpha, GraphicsPixelDataType::HalfFloatOES);
const PixelType PixelType::I16(GraphicsInternalFormat::Luminance, GraphicsPixelFormat::Luminance, GraphicsPixelDataType::HalfFloatOES);
const PixelType PixelType::IA1616(GraphicsInternalFormat::LuminanceAlpha, GraphicsPixelFormat::LuminanceAlpha, GraphicsPixelDataType::HalfFloatOES);
const PixelType PixelType::RGBA32323232(GraphicsInternalFormat::RGBA, GraphicsPixelFormat::RGBA, GraphicsPixelDataType::FloatOES);
const PixelType PixelType::RGB323232(GraphicsInternalFormat::RGB, GraphicsPixelFormat::RGB, GraphicsPixelDataType::FloatOES);
const PixelType PixelType::A32(GraphicsInternalFormat::Alpha, GraphicsPixelFormat::Alpha, GraphicsPixelDataType::FloatOES);
const PixelType PixelType::I32(GraphicsInternalFormat::Luminance, GraphicsPixelFormat::Luminance, GraphicsPixelDataType::FloatOES);
const PixelType PixelType::IA3232(GraphicsInternalFormat::LuminanceAlpha, GraphicsPixelFormat::LuminanceAlpha, GraphicsPixelDataType::FloatOES);


const PixelType PixelType::PVRTC2RGB(GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG, GraphicsPixelFormat::None, GraphicsPixelDataType::None);
const PixelType PixelType::PVRTC2RGBA(GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG, GraphicsPixelFormat::None, GraphicsPixelDataType::None);
const PixelType PixelType::PVRTC4RGB(GraphicsInternalFormat::Compressed_RGB_PVRTC_4BPPV1_IMG, GraphicsPixelFormat::None, GraphicsPixelDataType::None);
const PixelType PixelType::PVRTC4RGBA(GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG, GraphicsPixelFormat::None, GraphicsPixelDataType::None);
const PixelType PixelType::PVRTC2RGBA_2(GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG, GraphicsPixelFormat::None, GraphicsPixelDataType::None);
const PixelType PixelType::PVRTC4RGBA_2(GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG, GraphicsPixelFormat::None, GraphicsPixelDataType::None);

const PixelType PixelType::ETC(GraphicsInternalFormat::Compressed_ETC1_RGB8_OES, GraphicsPixelFormat::None, GraphicsPixelDataType::None);

const PixelType PixelType::S3TC_DXT1(GraphicsInternalFormat::S3TC_DXT1, GraphicsPixelFormat::None, GraphicsPixelDataType::Byte);
const PixelType PixelType::S3TC_DXT3(GraphicsInternalFormat::S3TC_DXT3, GraphicsPixelFormat::None, GraphicsPixelDataType::Byte);
const PixelType PixelType::S3TC_DXT5(GraphicsInternalFormat::S3TC_DXT5, GraphicsPixelFormat::None, GraphicsPixelDataType::Byte);

const PixelType PixelType::ATC_RGB(GraphicsInternalFormat::ATC_RGB, GraphicsPixelFormat::None, GraphicsPixelDataType::Byte);
const PixelType PixelType::ATC_RGBA_EXPLICIT_ALPHA(GraphicsInternalFormat::ATC_RGBA_EXPLICIT_ALPHA, GraphicsPixelFormat::None, GraphicsPixelDataType::Byte);
const PixelType PixelType::ATC_RGBA_INTERPOLATED_ALPHA(GraphicsInternalFormat::ATC_RGBA_INTERPOLATED_ALPHA, GraphicsPixelFormat::None, GraphicsPixelDataType::Byte);

MEDUSA_END;