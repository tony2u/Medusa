// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Graphics/Render/Render.h"
#include "Resource/Image/IImage.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

/*
File format:
Header (52B)+MetaData(0+bytes)+TextureData
TextureData format:
for each mip-map level in mip-map count
{
	for each surface in surface count
	{
		for each face in face count
		{
			for each slice in Depth
			{
				for each Row in Height
				{
					for each Pixel in Width
					{
						Byte data[Size Based on PixelFormat]
					}
				}
			}
		}
	}
}

*/

enum class PVRChannelType
{
	UnsignedByteNorm,
	SignedByteNorm,
	UnsignedByte,
	SignedByte,
	UnsignedShortNorm,
	SignedShortNorm,
	UnsignedShort,
	SignedShort,
	UnsignedIntegerNorm,
	SignedIntegerNorm,
	UnsignedInteger,
	SignedInteger,
	SignedFloat
};

enum class PVRPixelFormat
{
	PVRTCI_2bpp_RGB=0,
	PVRTCI_2bpp_RGBA=1,
	PVRTCI_4bpp_RGB=2,
	PVRTCI_4bpp_RGBA=3,
	PVRTCII_2bpp=4,
	PVRTCII_4bpp=5,
	ETC1=6,
	DXT1=7,
	DXT2=8,
	DXT3=9,
	DXT4=10,
	DXT5=11,
	//These formats are identical to some DXT formats.
	BC1=7,
	BC2=9,
	BC3=11,
	//These are currently unsupported:
	BC4=12,
	BC5=13,
	BC6=14,
	BC7=15,
	//These are supported
	UYVY=16,
	YUY2=17,
	BW1bpp=18,
	SharedExponentR9G9B9E5=19,
	RGBG8888=20,
	GRGB8888=21,
	ETC2_RGB=22,
	ETC2_RGBA=23,
	ETC2_RGB_A1=24,
	EAC_R11_U=25,
	EAC_R11_S=26,
	EAC_RG11_U=27,
	EAC_RG11_S=28
};


enum class PVRVersionIdentifier
{
	PVR3 = 0x03525650,// 'P''V''R'3
	ReversePVR3= 0x50565203
};	// 3 'R' 'V' 'P'

enum class PVRFlags 
{
	None=0, 
	Premultiplied=0x02 
};

enum class PVRColourSpace 
{ 
	LinearRGB= 0,
	StandardRGB= 1 
};

enum class PVRFontMetaBlockKey 
{
	Header= (int)0xFCFC0050, 
	CharList= (int)0xFCFC0051,
	Rects= (int)0xFCFC0052,
	Metrics=(int)0xFCFC0053, 
	YOffset= (int)0xFCFC0054,
	Kerning=(int)0xFCFC0055 
};


//Generate a 4 channel PixelID.
#define PVRT_PIXEL_ID_4(C1Name, C2Name, C3Name, C4Name, C1Bits, C2Bits, C3Bits, C4Bits) ( ( (uint64)C1Name) + ( (uint64)C2Name<<8) + ( (uint64)C3Name<<16) + ( (uint64)C4Name<<24) + ( (uint64)C1Bits<<32) + ( (uint64)C2Bits<<40) + ( (uint64)C3Bits<<48) + ( (uint64)C4Bits<<56) )
//Generate a 1 channel PixelID.
#define PVRT_PIXEL_ID_3(C1Name, C2Name, C3Name, C1Bits, C2Bits, C3Bits)( PVRT_PIXEL_ID_4(C1Name, C2Name, C3Name, 0, C1Bits, C2Bits, C3Bits, 0) )
//Generate a 2 channel PixelID.
#define PVRT_PIXEL_ID_2(C1Name, C2Name, C1Bits, C2Bits) ( PVRT_PIXEL_ID_4(C1Name, C2Name, 0, 0, C1Bits, C2Bits, 0, 0) )
//Generate a 3 channel PixelID.
#define PVRT_PIXEL_ID_1(C1Name, C1Bits) ( PVRT_PIXEL_ID_4(C1Name, 0, 0, 0, C1Bits, 0, 0, 0))


#pragma pack(push,4)	//the compiler will pack using the max member size(e.g 8) automatically. this line is necessary
struct PVRImageHeader
{
	PVRVersionIdentifier Version;
	PVRFlags Flags;
	uint64 PixelFormat;
	PVRColourSpace ColourSpace;
	PVRChannelType ChannelType;
	uint Height;
	uint Width;
	uint Depth;
	uint SurfaceCount;
	uint FaceCount;
	uint MIPMapCount;
	uint MetaDataSize;

	uint GetTextureDataSize(uint mipLevel=Math::UIntMaxValue,bool includeAllSurfaces=true,bool includeAllFaces=true)const;
	static uint GetBitsPerPixel(uint64 pixelFormat);
	static Size3U GetMinDimensions(uint64 pixelFormat);
	uint GetChannelSize()const;
	void GetGraphicFormats(GraphicsInternalFormat& outInternalFormat,GraphicsPixelFormat& outPixelFormat,GraphicsPixelDataType& outPixelType)const;

};
#pragma pack(pop)

struct PVRImageMetaDataBlock 
{
	uint DevFourCC;	//A 4cc descriptor of the data type's creator. Values equating to values between 'P' 'V' 'R' 0 and 'P' 'V' 'R' 255 will be used by our headers.
	uint Key;			//A DWORD (enum value) identifying the data type, and thus how to read it.
	uint DataSize;	//Size of the Data member.
	byte* Data;			//Data array, can be absolutely anything, the loader needs to know how to handle it based on DevFOURCC and Key. Use new operator to assign to it.

	PVRImageMetaDataBlock():DevFourCC(0),Key(0),DataSize(0),Data(nullptr){}
	~PVRImageMetaDataBlock()
	{
		SAFE_DELETE_ARRAY(Data);
	}
	bool operator==(const PVRImageMetaDataBlock& block)const
	{
		return DevFourCC==block.DevFourCC&&Key==block.Key&&DataSize==block.DataSize&&Data==block.Data;
	}
};


// 12 bytes
struct PVRFontHeader				
{
	byte	Version;				// Version of PVRFont.
	byte	SpaceWidth;			// The width of the 'Space' character
	short	NumCharacters;			// Total number of characters contained in this file
	short	NumKerningPairs;		// Number of characters which kern against each other
	short	Ascent;				// The height of the character, in pixels, from the base line
	short	LineSpace;				// The base line to base line dimension, in pixels.
	short	BorderWidth;			// px Border around each character
};


class PVRImage:public IImage
{
public:
	typedef Dictionary<uint,PVRImageMetaDataBlock*> MetaDataBlockList;
	typedef Dictionary<uint,MetaDataBlockList*> MetaDataBlockMap;
public:
	PVRImage(const FileIdRef& fileId,const PVRImageHeader& header,MetaDataBlockMap* metaBlocks,MemoryByteData imageData,bool isCopyImageData,bool isCompressed);
	virtual ~PVRImage(void);
	virtual ImageFileType ImageType()const{return ImageFileType::pvr;}
	const PVRImageHeader& Header() const { return mHeader; }
	void SetHeader(PVRImageHeader val) { mHeader = val; }
	virtual bool Upload();

	MetaDataBlockMap* MetaDataBlocks() const { return mMetaDataBlocks.get(); }
	PVRImageMetaDataBlock* GetMetaBlock(uint fourCC,uint key)const;

	static PVRImage* CreateFromFile(const FileIdRef& fileId);
	static PVRImage* CreateFromMemory(const FileIdRef& fileId,MemoryByteData data);
	virtual uint GetTextureDataSize(uint mipLevel)const;

private:
	PVRImageHeader mHeader;
	std::unique_ptr<MetaDataBlockMap> mMetaDataBlocks;
    
};

MEDUSA_END;