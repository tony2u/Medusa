// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ImageFactory.h"
#include "Resource/Image/JpegImage.h"
#include "Resource/Image/PngImage.h"
#include "Resource/Image/PVRImage.h"
#include "Core/IO/FileInfo.h"
#include "Core/Assertion/CommonAssert.h"
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;

ImageFactory::ImageFactory()
{

}

ImageFactory::~ImageFactory()
{

}

bool ImageFactory::Initialize()
{
	return true;
}

bool ImageFactory::Uninitialize()
{
	Clear();
	return true;
}


IImage* ImageFactory::CreateFromFile(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IImage* image = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(image);


	switch (FileInfo::ExtractType(fileId.Name))
	{
	case FileType::jpeg:
		image = JpegImage::CreateFromFile(fileId);
		break;
	case FileType::png:
		image = PngImage::CreateFromFile(fileId);
		break;
	case FileType::gif:
		break;
	case FileType::pvr:
		image = PVRImage::CreateFromFile(fileId);
		break;
	default:
		return nullptr;
		break;
	}

	RETURN_NULL_IF_NULL(image);

	Add(image, shareType);
	return image;
}

IImage* ImageFactory::CreateFromOrderItem(const FileIdRef& fileId, const FileMapOrderItem& orderItem, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	IImage* image = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(image);

	MemoryByteData data = FileSystem::Instance().ReadAllData(orderItem);
	return CreateFromMemory(fileId, data, shareType);

}

IImage* ImageFactory::CreateFromMemory(const FileIdRef& fileId, MemoryByteData data, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	RETURN_NULL_IF_EMPTY(data);
	IImage* image = Find(fileId);
	RETURN_SELF_IF_NOT_NULL(image);


	switch (FileInfo::ExtractType(fileId.Name))
	{
	case FileType::jpeg:
		image = JpegImage::CreateFromMemory(fileId, data);
		break;
	case FileType::png:
		image = PngImage::CreateFromMemory(fileId, data);
		break;
	case FileType::gif:
        return nullptr;
	case FileType::pvr:
		image = PVRImage::CreateFromMemory(fileId, data);
		break;
	default:
		return nullptr;
		break;
	}

	Add(image, shareType);

	return image;
}


uint ImageFactory::GetBytesPerComponent(GraphicsPixelFormat format, GraphicsPixelDataType dataType)
{
	switch (format)
	{
	case GraphicsPixelFormat::RGBA:
	case GraphicsPixelFormat::BGRA:
		switch (dataType.ToUInt())
		{
		case GraphicsPixelDataType::Byte.IntValue:
			return 4;
		case GraphicsPixelDataType::UnsignedShort5551.IntValue:
			return 3;
		case GraphicsPixelDataType::UnsignedShort4444.IntValue:
			return 2;
		default:
			MEDUSA_ASSERT_FAILED("Invalid dataType");
			break;
		}
	case GraphicsPixelFormat::RGB:
		switch (dataType.ToUInt())
		{
		case GraphicsPixelDataType::Byte.IntValue:
			return 3;
		case GraphicsPixelDataType::UnsignedShort565.IntValue:
			return 2;
		default:
			MEDUSA_ASSERT_FAILED("Invalid dataType");
			break;
		}
	case GraphicsPixelFormat::LuminanceAlpha:
		return 2;
	case GraphicsPixelFormat::Luminance:
	case GraphicsPixelFormat::Alpha:
		return 1;
	case GraphicsPixelFormat::DepthComponent:
		switch (dataType.ToUInt())
		{
		case GraphicsPixelDataType::FloatOES.IntValue:
		case GraphicsPixelDataType::UInt.IntValue:
			return 4;
		default:
			MEDUSA_ASSERT_FAILED("Invalid dataType");
			break;
		}
	}
	return 0;
}

void ImageFactory::CopyImage(MemoryByteData& destData, GraphicsPixelFormat destFormat, GraphicsPixelDataType destDataType, const Size2U& destImageSize,
	const Rect2U& rect, const MemoryByteData& imageData, GraphicsPixelFormat srcFormat, GraphicsPixelDataType srcDataType,
	int stride/*=0*/, bool isFlipY/*=false*/, GraphicsPixelConvertMode mode/*=PixelConvertMode::Normal*/)
{
	MEDUSA_ASSERT(rect.Right() <= destImageSize.Width, "");
	MEDUSA_ASSERT(rect.Top() <= destImageSize.Height, "");

	byte* dest = destData.MutableData();
	const byte* src = imageData.Data();
	uint destDepth = ImageFactory::GetBytesPerComponent(destFormat, destDataType);
	uint srcDepth = ImageFactory::GetBytesPerComponent(srcFormat, srcDataType);

	uint rowCount = destDepth*rect.Size.Width;
	if (stride == 0)
	{
		stride = rect.Size.Width*destDepth;
	}

	if (destFormat == srcFormat&&destDataType == srcDataType)
	{
		if (isFlipY)
		{
			FOR_EACH_SIZE(i, rect.Size.Height)
			{
				byte* tempDest = dest + ((rect.Origin.Y + i)*destImageSize.Width + rect.Origin.X)*destDepth;
				const byte* tempSrc = src + (rect.Size.Height - 1 - i)*stride;
				Memory::Copy(tempDest, tempSrc, rowCount);
			}
		}
		else
		{
			FOR_EACH_SIZE(i, rect.Size.Height)
			{
				byte* tempDest = dest + ((rect.Origin.Y + i)*destImageSize.Width + rect.Origin.X)*destDepth;
				const byte* tempSrc = src + i*stride;
				Memory::Copy(tempDest, tempSrc, rowCount);
			}
		}
	}
	else
	{
		PixelConverter converter = GetPixelConverter(destFormat, destDataType, srcFormat, srcDataType, mode);
		if (converter == nullptr)
		{
			MEDUSA_ASSERT_NOT_IMPLEMENT();
			return;
		}

		if (isFlipY)
		{
			FOR_EACH_SIZE(i, rect.Size.Height)
			{
				byte* tempDest = dest + ((rect.Origin.Y + i)*destImageSize.Width + rect.Origin.X)*destDepth;
				const byte* tempSrc = src + (rect.Size.Height - 1 - i)*stride;
				FOR_EACH_SIZE(j, rect.Size.Width)
				{
					converter(tempDest + j*destDepth, tempSrc + j*srcDepth);
				}
			}
		}
		else
		{
			FOR_EACH_SIZE(i, rect.Size.Height)
			{
				byte* tempDest = dest + ((rect.Origin.Y + i)*destImageSize.Width + rect.Origin.X)*destDepth;
				const byte* tempSrc = src + i*stride;
				FOR_EACH_SIZE(j, rect.Size.Width)
				{
					converter(tempDest + j*destDepth, tempSrc + j*srcDepth);
				}
			}
		}
	}
}


MEDUSA_FORCE_INLINE void ImageFactory::CopyPixel(byte* dest, GraphicsPixelFormat destFormat, GraphicsPixelDataType destDataType, const byte* src, GraphicsPixelFormat srcFormat, GraphicsPixelDataType srcDataType, GraphicsPixelConvertMode mode/*=PixelConvertMode::Normal*/)
{
	PixelConverter converter = GetPixelConverter(destFormat, destDataType, srcFormat, srcDataType, mode);
	if (converter == nullptr)
	{
		MEDUSA_ASSERT_NOT_IMPLEMENT();
		return;
	}
	converter(dest, src);
}

MEDUSA_FORCE_INLINE void ImageFactory::RGB_RGBA_Normal(byte* dest, const byte* src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = 0xFF;
}

MEDUSA_FORCE_INLINE void ImageFactory::RGB_RGBA_Real(byte* dest, const byte* src)
{
	int srcColor = dest[0] = src[0];
	srcColor += dest[1] = src[1];
	srcColor += dest[2] = src[2];
	dest[3] = srcColor != 0 ? 0xFF : 0x00;
}


MEDUSA_FORCE_INLINE void ImageFactory::RGB_RGBA_Alpha(byte* dest, const byte* src)
{
	dest[0] = 0xFF;
	dest[1] = 0xFF;
	dest[2] = 0xFF;
	dest[3] = src[0];
}

MEDUSA_FORCE_INLINE void ImageFactory::RGBA_RGB_Normal(byte* dest, const byte* src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

MEDUSA_FORCE_INLINE void ImageFactory::RGBA_RGB_Real(byte* dest, const byte* src)
{
	//alpha blend
	//D=D*(1-A)+S*A=D+(S-D)*A
	//D+=(S-D)*A
	dest[0] += (byte)(((src[0] - dest[0])*(uint)src[3]) / 255);
	dest[1] += (byte)(((src[1] - dest[1])*(uint)src[3]) / 255);
	dest[2] += (byte)(((src[2] - dest[2])*(uint)src[3]) / 255);
}

MEDUSA_FORCE_INLINE void ImageFactory::Alpha_RGBA_Alpha(byte* dest, const byte* src)
{
	dest[0] = 0xFF;
	dest[1] = 0xFF;
	dest[2] = 0xFF;
	dest[3] = src[0];
}

ImageFactory::PixelConverter ImageFactory::GetPixelConverter(GraphicsPixelFormat destFormat, GraphicsPixelDataType destDataType, GraphicsPixelFormat srcFormat, GraphicsPixelDataType srcDataType, GraphicsPixelConvertMode mode)
{
	if (destFormat == GraphicsPixelFormat::RGB&&destDataType == GraphicsPixelDataType::Byte&&srcFormat == GraphicsPixelFormat::RGBA&&srcDataType == GraphicsPixelDataType::Byte)
	{
		if (mode == GraphicsPixelConvertMode::Normal)
		{
			return RGBA_RGB_Normal;
		}
		else if (mode == GraphicsPixelConvertMode::Real)
		{
			return RGBA_RGB_Real;
		}

	}

	if (destFormat == GraphicsPixelFormat::RGBA&&destDataType == GraphicsPixelDataType::Byte&&srcFormat == GraphicsPixelFormat::RGB&&srcDataType == GraphicsPixelDataType::Byte)
	{
		if (mode == GraphicsPixelConvertMode::Normal)
		{
			return RGB_RGBA_Normal;
		}
		else if (mode == GraphicsPixelConvertMode::Real)
		{
			return RGB_RGBA_Real;
		}
		else if (mode == GraphicsPixelConvertMode::Alpha)
		{
			return RGB_RGBA_Alpha;
		}
	}

	if (destFormat == GraphicsPixelFormat::RGBA&&destDataType == GraphicsPixelDataType::Byte&&srcFormat == GraphicsPixelFormat::Alpha&&srcDataType == GraphicsPixelDataType::Byte)
	{
		if (mode == GraphicsPixelConvertMode::Alpha)
		{
			return Alpha_RGBA_Alpha;
		}
	}


	return nullptr;
}


MEDUSA_END;