// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_PNG
#include "PngImage.h"
#include "Core/IO/File.h"
#include "Core/IO/FileSystem.h"
#include "Lib/Common/png/png.h"
#include "Lib/Common/png/pngstruct.h"

MEDUSA_BEGIN;
//#define  MEDUSA_PNG_USER_MEM_SUPPORTED 

#ifdef MEDUSA_WINDOWS
#pragma warning(push)
#pragma warning(disable:4611)
#endif

struct PngImageSource
{
	byte* mData;
	int mSize;
	int mOffset;
};

void PngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	PngImageSource* isource = (PngImageSource*)png_get_io_ptr(png_ptr);

	if ((int)(isource->mOffset + length) <= isource->mSize)
	{
		memcpy(data, isource->mData + isource->mOffset, length);
		isource->mOffset += static_cast<int>(length);
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

png_voidp PngMallocCallback(png_structp png_ptr, png_size_t length)
{
	return malloc(length);
}

void PngFreeCallback(png_structp png_ptr, png_voidp data)
{
	free(data);
}

void PngErrorCallback(png_structp png_ptr, png_const_charp error_message)
{
	FileEntry* fileEntry = (FileEntry*)(png_ptr->error_ptr);
	Log::FormatInfo("PngImage {} Error:{}", fileEntry->Name(), error_message);

}

void PngWarningCallback(png_structp png_ptr, png_const_charp error_message)
{
	FileEntry* fileEntry = (FileEntry*)(png_ptr->error_ptr);
	Log::FormatInfo("PngImage {} Warning:{}", fileEntry->Name(), error_message);
}


PngImage::PngImage(const FileIdRef& fileId,Size2U imageSize, PixelType pixelType,bool isPreMultiplyAlpha )
	:RGBAImage(fileId,imageSize,pixelType,isPreMultiplyAlpha)
{

}


PngImage::~PngImage(void)
{
}

Share<PngImage> PngImage::CreateFromFile( const FileIdRef& fileId )
{
	const auto* fileEntry = FileSystem::Instance().Find(fileId);
	RETURN_NULL_IF_NULL(fileEntry);
	MemoryData data = fileEntry->ReadAllData();
	if (data.IsNull())
	{
		return nullptr;
	}
	return CreateFromMemory(fileId, *fileEntry,data);
}

Share<PngImage> PngImage::CreateFromMemory(const FileIdRef& fileId,const FileEntry& fileEntry, MemoryData data )
{
	MEDUSA_ASSERT(data.Size()>8,"");

	//check if it's png
	png_byte header[8]={0};
	Memory::SafeCopy((byte*)header,8,data.Data(),8);
	MEDUSA_ASSERT_ZERO(png_sig_cmp(header,0,8),"");

#ifdef MEDUSA_PNG_USER_MEM_SUPPORTED
	png_structp png_ptr=png_create_read_struct_2(PNG_LIBPNG_VER_STRING,(png_voidp)&fileEntry,nullptr,nullptr,nullptr,PngMallocCallback,PngFreeCallback);

#else
	png_structp png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING,(png_voidp)&fileEntry,PngErrorCallback,PngWarningCallback);
#endif

	MEDUSA_ASSERT_NOT_NULL(png_ptr,"");

	png_infop  info_ptr=png_create_info_struct(png_ptr);
	if (info_ptr==nullptr)
	{
		png_destroy_read_struct(&png_ptr,nullptr,nullptr);
		MEDUSA_ASSERT_FAILED("");
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,nullptr);
		MEDUSA_ASSERT_FAILED("");
	}

	PngImageSource imageSource;
	imageSource.mData=(byte*)data.Data();
	imageSource.mSize=static_cast<int>(data.Size());
	imageSource.mOffset=0;

	png_set_read_fn(png_ptr,&imageSource,PngReadCallback);



	// read png
	// PNG_TRANSFORM_EXPAND: perform set_expand()
	// PNG_TRANSFORM_PACKING: expand 1, 2 and 4-bit samples to bytes
	// PNG_TRANSFORM_STRIP_16: strip 16-bit samples to 8 bits
	// PNG_TRANSFORM_GRAY_TO_RGB: expand grayscale samples to RGB (or GA to RGBA)
	//png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB, 0);

	//get image info
	png_read_info(png_ptr, info_ptr);

	uint width=png_get_image_width(png_ptr,info_ptr);
	uint height=png_get_image_height(png_ptr,info_ptr);
	int colorType=png_get_color_type(png_ptr,info_ptr);
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	// force palette images to be expanded to 24-bit RGB
	// it may include alpha channel
	if (colorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_palette_to_rgb(png_ptr);
	}
	// low-bit-depth grayscale images are to be expanded to 8 bits
	if (colorType == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
	{
		bit_depth = 8;
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	// expand any tRNS chunk data into a full alpha channel
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png_ptr);
	}  
	// reduce images with 16-bit samples to 8 bits
	if (bit_depth == 16)
	{
		png_set_strip_16(png_ptr);            
	} 

	// Expanded earlier for grayscale, now take care of palette and rgb
	if (bit_depth < 8) {
		png_set_packing(png_ptr);
	}
	// update info
	png_read_update_info(png_ptr, info_ptr);
	//bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	colorType = png_get_color_type(png_ptr, info_ptr);

	PixelType pixelType = PixelType::None;
	switch (colorType)
	{
	case PNG_COLOR_TYPE_GRAY:
		pixelType = PixelType::I8;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		pixelType = PixelType::IA88;
		break;
	case PNG_COLOR_TYPE_RGB:
		pixelType = PixelType::RGB888;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		pixelType = PixelType::RGBA8888;
		break;
	default:
		pixelType = PixelType::RGBA8888;
		break;
	}

	Share<PngImage> result=new PngImage(fileId,Size2U(width,height), pixelType,false);
	MEDUSA_ASSERT_NOT_NULL(result,"");
	byte* imageData=result->MutableData().MutableData();
	png_bytepp rowPointers=new png_bytep[height];
	png_size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	FOR_EACH_SIZE(i,height)
	{
		rowPointers[i]=imageData+(height-1-i)*rowbytes;	//reverse the rows
	}

	png_read_image(png_ptr,rowPointers);
	png_read_end(png_ptr, nullptr);

	SAFE_DELETE_ARRAY(rowPointers);

	if (png_ptr!=nullptr)
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,nullptr);
	}

	return result;
}

bool PngImage::SaveToFile(StringRef filePath ) const
{
	MEDUSA_ASSERT_NOT_EMPTY(filePath,"");

	FileStream fs;
	if (!fs.Open(filePath,FileOpenMode::DestoryWriteOrCreate,FileDataType::Binary))
	{
		return false;
	}

#ifdef MEDUSA_PNG_USER_MEM_SUPPORTED
	png_structp png_ptr=png_create_write_struct_2(PNG_LIBPNG_VER_STRING,(png_voidp)&mFileId,nullptr,nullptr,nullptr,PngMallocCallback,PngFreeCallback);

#else
	png_structp png_ptr=png_create_write_struct(PNG_LIBPNG_VER_STRING,(png_voidp)&mFileId,nullptr,nullptr);
#endif

	MEDUSA_ASSERT_NOT_NULL(png_ptr,"");

	png_infop  info_ptr=png_create_info_struct(png_ptr);
	if (info_ptr==nullptr)
	{
		png_destroy_write_struct(&png_ptr,nullptr);
		MEDUSA_ASSERT_FAILED("");
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr,&info_ptr);
		MEDUSA_ASSERT_FAILED("");
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr,&info_ptr);
		MEDUSA_ASSERT_FAILED("");
	}

	png_init_io(png_ptr, fs.GetFile());

	int colorType=HasAlpha()?PNG_COLOR_TYPE_RGB_ALPHA:PNG_COLOR_TYPE_RGB;


	png_set_IHDR(png_ptr, info_ptr, mImageSize.Width, mImageSize.Height, 8, colorType,PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_colorp palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof (png_color));
	png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);

	png_write_info(png_ptr, info_ptr);

	png_set_packing(png_ptr);

	png_bytepp row_pointers = (png_bytep *)malloc(mImageSize.Height * sizeof(png_bytep));
	MEDUSA_ASSERT_NOT_NULL(row_pointers,"");


	uint bytesPerRow=mImageSize.Width*(HasAlpha()?4:3);
	//RevertMultipliedAlpha();		//TODO: return a copy of image data if premultipled alpha

	const byte* imageData=mImageData.Data();
	FOR_EACH_SIZE(i,mImageSize.Height)
	{
		row_pointers[i]=(byte*)imageData+i*bytesPerRow;
	}
	png_write_image(png_ptr,row_pointers);
	SAFE_FREE(row_pointers);

	png_write_end(png_ptr, info_ptr);

	png_free(png_ptr, palette);
	palette = nullptr;
	png_destroy_write_struct(&png_ptr, &info_ptr);

	return true;
}


#ifdef MEDUSA_WINDOWS
#pragma warning(pop)
#endif

MEDUSA_END;
#endif