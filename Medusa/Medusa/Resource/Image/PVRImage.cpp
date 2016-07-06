// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PVRImage.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Geometry/Size3.h"
#include "Graphics/Render/RenderExtensionNames.h"
#include "Core/Memory/MemoryData.h"
#include "Graphics/GraphicsContext.h"
#include "Lib/Common/PVR/PVRTDecompress.h"

MEDUSA_BEGIN;

PVRImage::PVRImage( const FileIdRef& fileId,const PVRImageHeader& header,MetaDataBlockMap* metaBlocks,MemoryData imageData,bool isCopyImageData, PixelType pixelType)
	:IImage(fileId, pixelType),mHeader(header),mMetaDataBlocks(metaBlocks)
{
	mImageSize.Width=mHeader.Width;
	mImageSize.Height=mHeader.Height;
	mMipMapCount=mHeader.MIPMapCount;
	mFaceCount=mHeader.FaceCount;

	if(isCopyImageData)
	{
		mImageData=imageData.Clone();
	}
	else
	{
		mImageData=imageData;
	}

	mPixelType=mHeader.GetGraphicFormats();
	mIsPreMultiplyAlpha=mHeader.Flags==PVRFlags::Premultiplied;

	if (mFaceCount>1)
	{
		mTextureType=GraphicsTextureType::TextureCubeMap;
	}
}


PVRImage::~PVRImage(void)
{
	for(auto i:*mMetaDataBlocks)
	{
		MetaDataBlockList* list=i.Value;
		SAFE_DELETE_DICTIONARY_VALUE(*list);
	}
	SAFE_DELETE_DICTIONARY_VALUE(*mMetaDataBlocks);
	
}

bool PVRImage::Upload()
{
	int prevVal=Render::Instance().GetInteger(GraphicsIntegerName::UnpackAlignment);
	Render::Instance().SetPixelStore(GraphicsPixelStoreParameter::UnpackAlignment,1);
	bool result=IImage::Upload();
	Render::Instance().SetPixelStore(GraphicsPixelStoreParameter::UnpackAlignment,prevVal);
	return result;
}

PVRImageMetaDataBlock* PVRImage::GetMetaBlock( uint fourCC,uint key ) const
{
	Dictionary<uint,PVRImageMetaDataBlock*>* resultList=mMetaDataBlocks->GetOptional(fourCC,nullptr);
	if(resultList!=nullptr)
	{
		if((resultList)->ContainsKey(key))
		{
			return (resultList)->Get(key);
		}
	}
	return nullptr;
}

Share<PVRImage> PVRImage::CreateFromFile( const FileIdRef& fileId )
{
	const auto* fileEntry = FileSystem::Instance().Find(fileId);
	RETURN_NULL_IF_NULL(fileEntry);
	MemoryData data = fileEntry->ReadAllData();

	return CreateFromMemory(fileId, *fileEntry,data);
}

Share<PVRImage> PVRImage::CreateFromMemory( const FileIdRef& fileId, const FileEntry& fileEntry,MemoryData data )
{
	if (data.IsNull())
	{
		return nullptr;
	}

	//Read header
	PVRImageHeader* header=(PVRImageHeader*)data.Data();

	uint headerAndMetaSize=0;

	if (header->Version==PVRVersionIdentifier::PVR3)
	{
		headerAndMetaSize=sizeof(PVRImageHeader)+header->MetaDataSize;
	}
	else if(header->Version==PVRVersionIdentifier::ReversePVR3)
	{
		header->Flags=(PVRFlags)BitConverter::SwapUInt((uint)header->Flags);
		header->PixelFormat=BitConverter::SwapUInt64(header->PixelFormat);
		header->ColourSpace=(PVRColourSpace)BitConverter::SwapUInt((uint)header->ColourSpace);
		header->ChannelType=(PVRChannelType)BitConverter::SwapUInt((uint)header->ChannelType);
		header->Height=BitConverter::SwapUInt(header->Height);
		header->Width=BitConverter::SwapUInt(header->Width);
		header->Depth=BitConverter::SwapUInt(header->Depth);
		header->SurfaceCount=BitConverter::SwapUInt(header->SurfaceCount);
		header->FaceCount=BitConverter::SwapUInt(header->FaceCount);
		header->MIPMapCount=BitConverter::SwapUInt(header->MIPMapCount);
		header->MetaDataSize=BitConverter::SwapUInt(header->MetaDataSize);
		headerAndMetaSize=sizeof(PVRImageHeader)+header->MetaDataSize;


		uint channelSize=header->GetChannelSize();
		if (channelSize>1)	//If the size of the variable type is greater than 1, then we need to byte swap.
		{
			byte* textureData = data.MutableData() + headerAndMetaSize;
			uint64 textureDataSize=header->GetTextureDataSize();
			for (uint i=0;i<textureDataSize;i+=channelSize)
			{
				BitConverter::SwapBytes((byte*)textureData+i,channelSize);
			}
		}
	}
	else
	{
		MEDUSA_ASSERT_FAILED("NOT support pvr 2");
	}

	if (header->SurfaceCount>1)
	{
		GraphicsAPI api = GraphicsContext::Instance().API();
		if (api == GraphicsAPI::OpenGLES2)
		{
			Log::Error("Texture arrays are not available in OGLES2.0!");
		}
	}

	//Read data
	MemoryData fileTextureData=MemoryData::FromStatic(data.Data()+headerAndMetaSize,(uint)header->GetTextureDataSize());
	//read meta block
	Dictionary<uint,Dictionary<uint,PVRImageMetaDataBlock*>*>* metaBlocks=new Dictionary<uint,Dictionary<uint,PVRImageMetaDataBlock*>*>();
	byte* metaData=(byte*)data.Data()+sizeof(PVRImageHeader);
	while(metaData<(byte*)fileTextureData.Data())
	{
		PVRImageMetaDataBlock* block=new PVRImageMetaDataBlock();
		block->DevFourCC=*(uint*)metaData;
		metaData+=sizeof(uint);
		block->Key=*(uint*)metaData;
		metaData+=sizeof(uint);
		block->DataSize=*(uint*)metaData;
		metaData+=sizeof(uint);
		if (block->DataSize>0)
		{
			block->Data=new byte[block->DataSize];
			Memory::SafeCopy(block->Data,block->DataSize,metaData,block->DataSize);
			metaData+=block->DataSize;
		}

		Dictionary<uint,PVRImageMetaDataBlock*>* innerBlocks=nullptr;
		if(metaBlocks->ContainsKey(block->DevFourCC))
		{
			innerBlocks=metaBlocks->Get(block->DevFourCC);
		}
		else
		{
			innerBlocks=new Dictionary<uint,PVRImageMetaDataBlock*>();
			metaBlocks->Add(block->DevFourCC,innerBlocks);
		}

		if(innerBlocks->ContainsKey(block->Key))
		{
			//duplicate block
			MEDUSA_ASSERT_FAILED("Duplicate block");
		}
		else
		{
			innerBlocks->Add(block->Key,block);
		}
	}

	//check if need to soft decompress
	MemoryData resultTextureData;
	PixelType pixelType= header->GetGraphicFormats();

	
	bool isCopyImageData=true;


	if (pixelType.InternalFormat() !=GraphicsInternalFormat::None)
	{
		if (pixelType.IsCompressed())	//compressed format
		{
			switch (pixelType.InternalFormat())
			{
			case GraphicsInternalFormat::Compressed_RGB_PVRTC_4BPPV1_IMG:
			case GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG:
			case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG:
			case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV1_IMG:
				{
					bool isPVRTCSupported=Render::Instance().IsExtensionSupported(RenderExtensionNames::IMG_texture_compression_pvrtc);
					//compressed
					if (isPVRTCSupported)
					{
						
						resultTextureData=fileTextureData;
						isCopyImageData=true;
					}
					else
					{
						//try to decompress it
						Log::Info("PVRTC not supported. Converting to RGBA8888 instead.");

						bool is2bppPVRTC= pixelType.InternalFormat() ==GraphicsInternalFormat::Compressed_RGB_PVRTC_2BPPV1_IMG|| pixelType.InternalFormat() ==GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV1_IMG;
					

						//Create a near-identical texture header for the decompressed header.
						PVRImageHeader decompressedHeader=*header;
						decompressedHeader.ChannelType=PVRChannelType::UnsignedByteNorm;
						decompressedHeader.ColourSpace=PVRColourSpace::LinearRGB;
						decompressedHeader.PixelFormat=PVRT_PIXEL_ID_4('r','g','b','a',8,8,8,8);
						pixelType = PixelType::RGBA8888;

						//Allocate enough memory for the decompressed data. OGLES1, so only decompress one surface/face.
						uint decompressedDataSize=decompressedHeader.GetTextureDataSize(Math::UIntMaxValue,false,false);
						MemoryData decompressedData=MemoryData::Alloc(decompressedDataSize);

						byte* tempCompressedData = fileTextureData.MutableData();
						byte* tempDecompressData = decompressedData.MutableData();

						Size2U textureSize(decompressedHeader.Width,decompressedHeader.Height);
						//decompress all mip levels
						FOR_EACH_SIZE(i,decompressedHeader.MIPMapCount)
						{
							size_t compressedSize=header->GetTextureDataSize((uint)i,false,false);
							size_t decompressedSize=decompressedHeader.GetTextureDataSize((uint)i,false,false);

							FOR_EACH_SIZE(j,header->FaceCount)
							{
								PVRTDecompressPVRTC((byte*)tempCompressedData,is2bppPVRTC?1:0,textureSize.Width,textureSize.Height,(byte*)tempDecompressData);

								tempCompressedData+=compressedSize;
								tempDecompressData+=decompressedSize;
							}


							textureSize.Width=Math::Max(1U,textureSize.Width>>1);
							textureSize.Height=Math::Max(1U,textureSize.Height>>1);

							
						}

						*header=decompressedHeader;
						
						resultTextureData=decompressedData;
						isCopyImageData=false;

						
					}
				}
				break;
			case GraphicsInternalFormat::Compressed_RGBA_PVRTC_2BPPV2_IMG:
			case GraphicsInternalFormat::Compressed_RGBA_PVRTC_4BPPV2_IMG:
				{
					bool isPVRTC2Supported=Render::Instance().IsExtensionSupported(RenderExtensionNames::IMG_texture_compression_pvrtc2);

					if (isPVRTC2Supported)
					{
						
						resultTextureData=fileTextureData;
						isCopyImageData=true;
					}
					else
					{
						Log::Error("PVRTC2 not supported!");
					}
				}
				break;
#ifdef MEDUSA_IOS
			case GraphicsInternalFormat::Compressed_ETC1_RGB8_OES:
				{
					bool isETCSupported=Render::Instance().IsExtensionSupported(RenderExtensionNames::OES_compressed_ETC1_RGB8_texture);

					if (isETCSupported)
					{
						
						isCopyImageData=true;
						resultTextureData=fileTextureData;
					}
					else
					{
						//try to decompress it
						Log::Info("ETC not supported. Converting to RGBA8888 instead.\n");

						//Create a near-identical texture header for the decompressed header.
						PVRImageHeader decompressedHeader=*header;
						decompressedHeader.ChannelType=PVRChannelType::UnsignedByteNorm;
						decompressedHeader.ColourSpace=PVRColourSpace::LinearRGB;
						decompressedHeader.PixelFormat=PVRT_PIXEL_ID_4('r','g','b','a',8,8,8,8);
						pixelType = PixelType::RGBA8888;

						//Allocate enough memory for the decompressed data. OGLES1, so only decompress one surface/face.
						MemoryData decompressedData;
						decompressedData.ForceSetSize(decompressedHeader.GetTextureDataSize(Math::UIntMaxValue,false,false));
						decompressedData.ForceSetData(new byte[decompressedData.Size()]);
						char* tempCompressedData=(char*)fileTextureData.Data();
						char* tempDecompressData=(char*)decompressedData.Data();

						Size2U textureSize(decompressedHeader.Width,decompressedHeader.Height);
						//decompress all mip levels
						FOR_EACH_SIZE(i,decompressedHeader.MIPMapCount)
						{
							uint compressedSize=header->GetTextureDataSize((uint)i,false,false);
							uint decompressedSize=decompressedHeader.GetTextureDataSize((uint)i,false,false);

							FOR_EACH_SIZE(j,header->FaceCount)
							{
								PVRTDecompressETC(tempCompressedData,textureSize.Width,textureSize.Height,tempDecompressData,0);

								tempCompressedData+=compressedSize;
								tempDecompressData+=decompressedSize;
							}


							textureSize.Width=Math::Max(1U,textureSize.Width>>1);
							textureSize.Height=Math::Max(1U,textureSize.Height>>1);


						}

						*header=decompressedHeader;
						
						resultTextureData=decompressedData;
						isCopyImageData=false;
					}
				}
				break;
#endif
                default:
                    break;
			}
		}
		else
		{
			if (pixelType.Format()==GraphicsPixelFormat::BGRA)
			{
#ifdef MEDUSA_IOS
				//internalFormat=GraphicsInternalFormat::RGBA;
#endif
				bool isBGRA8888Supported=Render::Instance().IsExtensionSupported(RenderExtensionNames::IMG_texture_format_BGRA8888);
				if (!isBGRA8888Supported)
				{
					Log::FormatError("Unable to load GL_BGRA texture as extension {} is unsupported.",RenderExtensionNames::IMG_texture_format_BGRA8888.c_str());
					return nullptr;
				}
			}

			if (pixelType.DataType() ==GraphicsPixelDataType::HalfFloatOES)
			{
				bool isFloat16Supported=Render::Instance().IsExtensionSupported(RenderExtensionNames::OES_texture_half_float);

				if (!isFloat16Supported)
				{
					Log::FormatError("Unable to load GL_HALF_FLOAT_OES texture as extension {} is unsupported.",RenderExtensionNames::OES_texture_half_float.c_str());
					return nullptr;
				}
			}

			if (pixelType.DataType() ==GraphicsPixelDataType::FloatOES)
			{
				bool isFloat32Supported=Render::Instance().IsExtensionSupported(RenderExtensionNames::OES_texture_float.c_str());
				if (!isFloat32Supported)
				{
					Log::FormatError("Unable to load GL_FLOAT texture as extension {} is unsupported.",RenderExtensionNames::OES_texture_float.c_str());
					return nullptr;
				}
			}
			resultTextureData=fileTextureData;
			isCopyImageData=true;
		}
		
	}
	else 
	{
		Log::Error("Unable to load texture as pixel type is unsupported.");
        
        //release meta blocks
        for(auto t:*metaBlocks)
        {
            auto* blockDict=t.Value;
            SAFE_DELETE_DICTIONARY_VALUE(*blockDict);
            delete blockDict;
        }
        delete metaBlocks;
        
		return nullptr;
	}

	return new PVRImage(fileId,*header,metaBlocks,resultTextureData,isCopyImageData,pixelType);
}

uint PVRImage::GetTextureDataSize( uint mipLevel ) const
{
	return mHeader.GetTextureDataSize(mipLevel,false,false);
}

uint PVRImageHeader::GetTextureDataSize( uint mipLevel/*=Math::UIntMaxValue*/,bool includeAllSurfaces/*=true*/,bool includeAllFaces/*=true*/ )const
{
	uint surfaceCount=includeAllSurfaces?SurfaceCount:1;
	uint faceCount=includeAllFaces?FaceCount:1;
	Size3U minDemension(1);

	uint64 pixelFormatHighPart=MEDUSA_UINT64_HIGH(PixelFormat);
	if (pixelFormatHighPart==0)	//it's compressed
	{
		minDemension=GetMinDimensions(PixelFormat);
	}

	uint resultDataSize=0;	//Needs to be 64-bit integer to support 16kx16k and higher sizes, but i think uint is enough!

	if (mipLevel==Math::UIntMaxValue)	//include all mip levels
	{
		Size3U textureSize;

		FOR_EACH_SIZE(i,MIPMapCount)
		{
			textureSize.Width=Math::Max(1U,Width>>i);
			textureSize.Height=Math::Max(1U,Height>>i);
			textureSize.Depth=Math::Max(1U,Depth>>i);

			//If pixel format is compressed, the dimensions need to be padded.
			if (pixelFormatHighPart==0)
			{
				textureSize.Width-=textureSize.Width%minDemension.Width;
				textureSize.Height-=textureSize.Height%minDemension.Height;
				textureSize.Depth-=textureSize.Depth%minDemension.Depth;
			}
			resultDataSize+= GetBitsPerPixel(PixelFormat)*textureSize.Volume();
		}
		
	}
	else
	{
		Size3U textureSize;
		textureSize.Width=Math::Max(1U,Width>>mipLevel);
		textureSize.Height=Math::Max(1U,Height>>mipLevel);
		textureSize.Depth=Math::Max(1U,Depth>>mipLevel);

		//If pixel format is compressed, the dimensions need to be padded.
		if (pixelFormatHighPart==0)
		{
			textureSize.Width-=textureSize.Width%minDemension.Width;
			textureSize.Height-=textureSize.Height%minDemension.Height;
			textureSize.Depth-=textureSize.Depth%minDemension.Depth;
		}

		resultDataSize= GetBitsPerPixel(PixelFormat)*textureSize.Volume();
	}

	return resultDataSize/8*surfaceCount*faceCount;
}

uint PVRImageHeader::GetBitsPerPixel( uint64 pixelFormat )
{
	uint64 pixelFormatHighPart=MEDUSA_UINT64_HIGH(pixelFormat);
	if (pixelFormatHighPart!=0)
	{
		byte* pixelFormatBytes=(byte*)&pixelFormat;
		return pixelFormatBytes[4]+pixelFormatBytes[5]+pixelFormatBytes[6]+pixelFormatBytes[7];
	}
	else
	{
		
		uint pixelFormatLowPart=MEDUSA_LOW_UINT(pixelFormat);
		switch ((PVRPixelFormat)pixelFormatLowPart)
		{
		case PVRPixelFormat::BW1bpp:
			return 1;
		case PVRPixelFormat::PVRTCI_2bpp_RGB:
		case PVRPixelFormat::PVRTCI_2bpp_RGBA:
		case PVRPixelFormat::PVRTCII_2bpp:
			return 2;
		case PVRPixelFormat::PVRTCI_4bpp_RGB:
		case PVRPixelFormat::PVRTCI_4bpp_RGBA:
		case PVRPixelFormat::PVRTCII_4bpp:
		case PVRPixelFormat::ETC1:
		case PVRPixelFormat::EAC_R11_S:
		case PVRPixelFormat::EAC_R11_U:
		case PVRPixelFormat::ETC2_RGB:
		case PVRPixelFormat::ETC2_RGB_A1:
		case PVRPixelFormat::DXT1:
		case PVRPixelFormat::BC4:
			return 4;
		case PVRPixelFormat::DXT2:
		case PVRPixelFormat::DXT3:
		case PVRPixelFormat::DXT4:
		case PVRPixelFormat::DXT5:
		case PVRPixelFormat::BC5:
		case PVRPixelFormat::ETC2_RGBA:
		case PVRPixelFormat::EAC_RG11_S:
		case PVRPixelFormat::EAC_RG11_U:
			return 8;
		case PVRPixelFormat::YUY2:
		case PVRPixelFormat::UYVY:
		case PVRPixelFormat::RGBG8888:
		case PVRPixelFormat::GRGB8888:
			return 16;
		case PVRPixelFormat::SharedExponentR9G9B9E5:
			return 32;
		default:
			break;
		}
		
	}

	return 0;
}

Size3U PVRImageHeader::GetMinDimensions( uint64 pixelFormat )
{
	Size3U result;
	result=1;

	uint pixelFormatLowPart=MEDUSA_LOW_UINT(pixelFormat);
	switch ((PVRPixelFormat)pixelFormatLowPart)
	{
	case PVRPixelFormat::DXT1:
	case PVRPixelFormat::DXT2:
	case PVRPixelFormat::DXT3:
	case PVRPixelFormat::DXT4:
	case PVRPixelFormat::DXT5:
	case PVRPixelFormat::BC4:
	case PVRPixelFormat::BC5:
	case PVRPixelFormat::ETC1:
	case PVRPixelFormat::ETC2_RGB:
	case PVRPixelFormat::ETC2_RGBA:
	case PVRPixelFormat::ETC2_RGB_A1:
	case PVRPixelFormat::EAC_R11_S:
	case PVRPixelFormat::EAC_R11_U:
	case PVRPixelFormat::EAC_RG11_U:
	case PVRPixelFormat::EAC_RG11_S:
		result.Width=4;
		result.Height=4;
		result.Depth=1;
		break;
	case PVRPixelFormat::PVRTCI_4bpp_RGB:
	case PVRPixelFormat::PVRTCI_4bpp_RGBA:
		result.Width=8;
		result.Height=8;
		result.Depth=1;
		break;
	case PVRPixelFormat::PVRTCI_2bpp_RGB:
	case PVRPixelFormat::PVRTCI_2bpp_RGBA:
		result.Width=16;
		result.Height=8;
		result.Depth=1;
		break;
	case PVRPixelFormat::PVRTCII_4bpp:
		result.Width=4;
		result.Height=4;
		result.Depth=1;
		break;
	case PVRPixelFormat::PVRTCII_2bpp:
		result.Width=8;
		result.Height=4;
		result.Depth=1;
		break;
	case PVRPixelFormat::UYVY:
	case PVRPixelFormat::YUY2:
	case PVRPixelFormat::RGBG8888:
	case PVRPixelFormat::GRGB8888:
		result.Width=2;
		result.Height=1;
		result.Depth=1;
		break;
	case PVRPixelFormat::BW1bpp:
		result.Width=8;
		result.Height=1;
		result.Depth=1;
		break;
	default: //Non-compressed formats all return 1.
		break;
	}
	return result;
}

uint PVRImageHeader::GetChannelSize() const
{
	switch(ChannelType)
	{
	case PVRChannelType::SignedFloat:
	case PVRChannelType::UnsignedInteger:
	case PVRChannelType::UnsignedIntegerNorm:
	case PVRChannelType::SignedInteger:
	case PVRChannelType::SignedIntegerNorm:
		return 4;
	case PVRChannelType::UnsignedShort:
	case PVRChannelType::UnsignedShortNorm:
	case PVRChannelType::SignedShort:
	case PVRChannelType::SignedShortNorm:
		return 2;
	case PVRChannelType::UnsignedByte:
	case PVRChannelType::UnsignedByteNorm:
	case PVRChannelType::SignedByte:
	case PVRChannelType::SignedByteNorm:
	default:
		return 1;
	}
}

PixelType PVRImageHeader::GetGraphicFormats() const
{
	uint64 pixelFormatHighPart=MEDUSA_UINT64_HIGH(PixelFormat);
	uint pixelFormatLowPart=MEDUSA_LOW_UINT(PixelFormat);

	if (pixelFormatHighPart==0)
	{
		switch((PVRPixelFormat)pixelFormatLowPart)
		{
		case PVRPixelFormat::PVRTCI_2bpp_RGB:
			return PixelType::PVRTC2RGB;
		case PVRPixelFormat::PVRTCI_2bpp_RGBA:
			return PixelType::PVRTC2RGBA;
		case PVRPixelFormat::PVRTCI_4bpp_RGB:
			return PixelType::PVRTC4RGB;
		case PVRPixelFormat::PVRTCI_4bpp_RGBA:
			return PixelType::PVRTC4RGBA;
		case PVRPixelFormat::PVRTCII_2bpp:
			return PixelType::PVRTC2RGBA_2;
		case PVRPixelFormat::PVRTCII_4bpp:
			return PixelType::PVRTC4RGBA_2;
#ifdef MEDUSA_IOS
		case PVRPixelFormat::ETC1:
			return PixelType::ETC;
#endif
		default:
			return PixelType::None;
		}
	}
	else
	{
		switch(ChannelType)
		{
		case PVRChannelType::SignedFloat:
			{
				switch(PixelFormat)
				{
				case PVRT_PIXEL_ID_4('r','g','b','a',16,16,16,16):
					return PixelType::RGBA16161616;
				case PVRT_PIXEL_ID_3('r','g','b',16,16,16):
					return PixelType::RGB161616;
				case PVRT_PIXEL_ID_2('l','a',16,16):
					return PixelType::IA1616;
				case PVRT_PIXEL_ID_1('l',16):
					return PixelType::I16;
				case PVRT_PIXEL_ID_1('a',16):
					return PixelType::A16;
				case PVRT_PIXEL_ID_4('r','g','b','a',32,32,32,32):
					return PixelType::RGBA32323232;
				case PVRT_PIXEL_ID_3('r','g','b',32,32,32):
					return PixelType::RGB323232;
				case PVRT_PIXEL_ID_2('l','a',32,32):
					return PixelType::IA3232;
				case PVRT_PIXEL_ID_1('l',32):
					return PixelType::I32;
				case PVRT_PIXEL_ID_1('a',32):
					return PixelType::A32;
				default:
					break;
				}

			}
			break;
		case PVRChannelType::UnsignedByteNorm:
			{
				switch(PixelFormat)
				{
				case PVRT_PIXEL_ID_4('r','g','b','a',8,8,8,8):
					return PixelType::RGBA8888;
				case PVRT_PIXEL_ID_3('r','g','b',8,8,8):
					return PixelType::RGB888;
				case PVRT_PIXEL_ID_2('l','a',8,8):
					return PixelType::IA88;
				case PVRT_PIXEL_ID_1('l',8):
					return PixelType::I8;
				case PVRT_PIXEL_ID_1('a',8):
					return PixelType::A8;
				case PVRT_PIXEL_ID_4('b','g','r','a',8,8,8,8):
					return PixelType::BGRA8888;
				default:
					break;
				}
			}
			break;
		case PVRChannelType::UnsignedShortNorm:
			{
				switch(PixelFormat)
				{
				case PVRT_PIXEL_ID_4('r','g','b','a',4,4,4,4):
					return PixelType::RGBA4444;
				case PVRT_PIXEL_ID_4('r','g','b','a',5,5,5,1):
					return PixelType::RGBA5551;
				case PVRT_PIXEL_ID_3('r','g','b',5,6,5):
					return PixelType::RGB565;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	return PixelType::None;
	
}

MEDUSA_END;