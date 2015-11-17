// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "JpegImage.h"
#include "Core/IO/File.h"
#include "Core/IO/FileSystem.h"
#include "Lib/Common/jpeg/jpeglib.h"


MEDUSA_BEGIN;
//#define  MEDUSA_JPEG_USER_MEM_SUPPORTED 


void* AllocSmallCallback(j_common_ptr cinfo, int pool_id, uint sizeofobject)
{
	return nullptr;
}

void* AllocLargeCallback(j_common_ptr cinfo, int pool_id, uint sizeofobject)
{
	return nullptr;

}

JSAMPARRAY AllocSArrayCallback(j_common_ptr cinfo, int pool_id, JDIMENSION samplesperrow, JDIMENSION numrows)
{
	return nullptr;

}

JBLOCKARRAY AllocBArrayCallback(j_common_ptr cinfo, int pool_id, JDIMENSION blocksperrow, JDIMENSION numrows)
{
	return nullptr;

}

void FreePoolCallback(j_common_ptr cinfo, int pool_ids)
{

}


JpegImage::JpegImage(const FileIdRef& fileId,Size2U imageSize,GraphicsInternalFormat internalFormat,GraphicsPixelFormat imageFormat,bool isPreMultiplyAlpha )
	:RGBAImage(fileId,imageSize,internalFormat,imageFormat,isPreMultiplyAlpha)
{
	
}


JpegImage::~JpegImage(void)
{
}


JpegImage* JpegImage::CreateFromFile( const FileIdRef& fileId ) 
{
	MemoryByteData data=FileSystem::Instance().ReadAllData(fileId);
	return CreateFromMemory(fileId,data);
}

JpegImage* JpegImage::CreateFromMemory(const FileIdRef& fileId, MemoryByteData data ) 
{
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_decompress( &cinfo );
	
	jpeg_mem_src( &cinfo, (byte*)data.Data(), static_cast<unsigned long>(data.Size()) );

	/* reading the image header which contains image information */
	jpeg_read_header( &cinfo, (boolean)true );

	// we only support RGB or grayscale
	/*if (cinfo.jpeg_color_space != JCS_RGB)
	{
		if (cinfo.jpeg_color_space == JCS_GRAYSCALE || cinfo.jpeg_color_space == JCS_YCbCr)
		{
			cinfo.out_color_space = JCS_RGB;
		}
	}*/

	cinfo.out_color_space = JCS_RGB;

#ifdef MEDUSA_JPEG_USER_MEM_SUPPORTED
	cinfo.mem->alloc_small=AllocSmallCallback;
	cinfo.mem->alloc_large=AllocLargeCallback;
	cinfo.mem->alloc_sarray=AllocSArrayCallback;
	cinfo.mem->alloc_barray=AllocBArrayCallback;
	cinfo.mem->free_pool=FreePoolCallback;
	cinfo.mem->max_memory_to_use=1024*1024*10;		//(10M)

#endif

	jpeg_start_decompress( &cinfo );

	short width=(short)cinfo.image_width;
	short height = (short)cinfo.image_height;

	JpegImage* result=new JpegImage(fileId,Size2U(width,height),GraphicsInternalFormat::RGB,GraphicsPixelFormat::RGB,false);
	MEDUSA_ASSERT_NOT_NULL(result,"");
	byte* imageData=result->MutableData().MutableData();

	uint rowSize=width*cinfo.output_components;
	JSAMPROW row_pointer[1] = {0};

	while(cinfo.output_scanline<cinfo.image_height)
	{
		row_pointer[0]=(byte*)imageData+(cinfo.output_height - cinfo.output_scanline-1)*rowSize;
		jpeg_read_scanlines(&cinfo,row_pointer,1);
	}

	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );

	return result;

}

bool JpegImage::SaveToFile(StringRef filePath ) const
{
	MEDUSA_ASSERT_NOT_EMPTY(filePath,"");

	FileStream fs;
	if (!fs.Open(filePath,FileOpenMode::DestoryWriteOrCreate,FileDataType::Binary))
	{
		return false;
	}

	jpeg_compress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_compress( &cinfo );

	jpeg_stdio_dest(&cinfo,fs.GetFile());

	cinfo.image_width = mImageSize.Width;    /* image width and height, in pixels */
	cinfo.image_height = mImageSize.Height;
	cinfo.input_components = 3;       /* # of color components per pixel */
	cinfo.in_color_space = JCS_RGB;       /* colorspace of input image */

	jpeg_set_defaults(&cinfo);

	jpeg_start_compress(&cinfo, TRUE);

	uint rowSize=mImageSize.Width*3;
	JSAMPROW row_pointer[1] = {0};
	const byte* imageData=mImageData.Data();

	while (cinfo.next_scanline < cinfo.image_height) 
	{
		row_pointer[0] =(byte*) & imageData[cinfo.next_scanline * rowSize];
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	return true;
}



MEDUSA_END;