// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BMPFont.h"
#include "Resource/Material/MaterialFactory.h"
#include "Core/IO/File.h"
#include "Resource/ResourceNames.h"
#include "Resource/Image/PVRImage.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Texture/ITexture.h"
#include "Core/IO/FileSystem.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"


MEDUSA_BEGIN;

BMPFont::BMPFont(const FontId& fontId) :IFont(fontId)
{

}


BMPFont::~BMPFont(void)
{
}

BMPFont* BMPFont::CreateFromPVR(const FontId& fontId)
{
	TextureAtlasPage* page = new TextureAtlasPage(fontId.ToRef());
	ITexture* texture = page->LoadTexture();

	IImage* image = texture->Image();
	RETURN_NULL_IF_NULL(image);

	PVRImage* pvrImage = (PVRImage*)image;
	PVRImageMetaDataBlock* headerMetaBlock = pvrImage->GetMetaBlock((uint)PVRVersionIdentifier::PVR3, (uint)PVRFontMetaBlockKey::Header);

	PVRFontHeader* fontHeader = (PVRFontHeader*)headerMetaBlock->Data;
	if (fontHeader->Version != 1)	//default is 1 in pvr font
	{
		return nullptr;
	}

	BMPFont* resultFont = new BMPFont(fontId);

	resultFont->SetAscender(fontHeader->Ascent);
	resultFont->SetLineHeight(fontHeader->LineSpace);
	resultFont->SetTotalCharCount(fontHeader->NumCharacters);

	if (fontId.Size() == 0)
	{
		resultFont->SetSize(fontHeader->SpaceWidth);
		resultFont->MutableFontId().SetOriginalSize(fontHeader->SpaceWidth);

	}

	PVRImageMetaDataBlock* charListMetaBlock = pvrImage->GetMetaBlock((uint)PVRVersionIdentifier::PVR3, (uint)PVRFontMetaBlockKey::CharList);
	PVRImageMetaDataBlock* yOffsetMetaBlock = pvrImage->GetMetaBlock((uint)PVRVersionIdentifier::PVR3, (uint)PVRFontMetaBlockKey::YOffset);
	PVRImageMetaDataBlock* metricsMetaBlock = pvrImage->GetMetaBlock((uint)PVRVersionIdentifier::PVR3, (uint)PVRFontMetaBlockKey::Metrics);
	PVRImageMetaDataBlock* kerningMetaBlock = pvrImage->GetMetaBlock((uint)PVRVersionIdentifier::PVR3, (uint)PVRFontMetaBlockKey::Kerning);
	PVRImageMetaDataBlock* rectMetaBlock = pvrImage->GetMetaBlock((uint)PVRVersionIdentifier::PVR3, (uint)PVRFontMetaBlockKey::Rects);

	bool hasSpace = false;

	FOR_EACH_SIZE(i, (uint)fontHeader->NumCharacters)
	{
		FontChar* fontChar = new FontChar();

		fontChar->Id = (wchar_t)((int*)charListMetaBlock->Data)[i];
		fontChar->HBearing.Y = ((int*)yOffsetMetaBlock->Data)[i];
		fontChar->HBearing.X = ((short*)metricsMetaBlock->Data)[i];
		fontChar->HAdvance = ((short*)metricsMetaBlock->Data)[i + 1];

		TextureAtlasRegion* region = new TextureAtlasRegion();
		region->SetId(fontChar->Id);
		region->SetTextureRect(((Rect2U*)rectMetaBlock->Data)[i]);
		page->AddRegion(region);
		fontChar->SetRegion(region);

		resultFont->AddChar(fontChar);

		if (fontChar->Id == ' ')
		{
			resultFont->SetSpaceFontChar(fontChar);
			hasSpace = true;
		}
	}

	resultFont->Atlas()->AddPage(page);

	if (!hasSpace)
	{
		FontChar* fontChar =new FontChar();
		fontChar->Id = ' ';
		fontChar->HAdvance = fontHeader->SpaceWidth;
		
		resultFont->AddChar(fontChar);
		resultFont->SetSpaceFontChar(fontChar);
		
	}

	FOR_EACH_SIZE(i, (uint)fontHeader->NumKerningPairs)
	{
		FontKerning* pair = new FontKerning();
		*pair = ((FontKerning*)kerningMetaBlock->Data)[i];
		resultFont->AddKerning(pair);
	}

	return resultFont;
}

BMPFont* BMPFont::CreateFromBMPBinary(const FontId& fontId, const IStream& stream)
{
	int version = stream.ReadChar();
	if (version != 3)
	{
		Log::FormatError("Invalid fnt binary file format version:{}. Must be 3!", version);
		return nullptr;
	}

	//1.read info line
	stream.ReadChar();
	/*uint infoBlockSize=*/stream.Read<uint>();

	ushort fontSize = stream.Read<ushort>();
	byte infoBitField = (byte)stream.ReadChar();
	bool isBold = (infoBitField & 8) != 0;
	bool isItalic = (infoBitField & 4) != 0;
	/*bool isUnicode=(infoBitField&2)!=0;*/
	/*bool isFixedHeight=(infoBitField&16)!=0;*/
	/*bool isSmooth=(infoBitField&1)!=0;*/
	/*byte charSet=(byte)*/stream.ReadChar();
	/*ushort stretchHeight=*/stream.Read<ushort>();
	/*byte isAtiAlias=(byte)*/stream.ReadChar();
	Padding4I padding;
	padding.Up = stream.ReadChar();
	padding.Right = stream.ReadChar();
	padding.Down = stream.ReadChar();
	padding.Left = stream.ReadChar();
	Point2I spacing;
	spacing.X = stream.ReadChar();
	spacing.Y = stream.ReadChar();
	byte outLineThickness = (byte)stream.ReadChar();
	HeapString faceName = stream.ReadString();

	FontId resultFontId = fontId;
	resultFontId.SetOriginalSize(fontSize);

	std::unique_ptr<BMPFont> bmpFont(new BMPFont(resultFontId));
	bmpFont->SetIsBold(isBold);
	bmpFont->SetIsItalic(isItalic);
	bmpFont->SetPadding(padding);
	bmpFont->SetSpacing(spacing);
	bmpFont->SetOutlineThickness(outLineThickness);

	//read common line
	stream.ReadChar();
	/*uint commonBlockSize=*/stream.Read<uint>();

	ushort lineHeight = stream.Read<ushort>();
	int baseHeight = stream.Read<ushort>();
	Size2U textureSize;
	textureSize.Width = stream.Read<ushort>();
	textureSize.Height = stream.Read<ushort>();
	uint pageCount = stream.Read<ushort>();
	byte commonBitField = (byte)stream.ReadChar();

	int isPacked = (commonBitField & 128) != 0;
	int channelA = stream.ReadChar();
	int channelR = stream.ReadChar();
	int channelG = stream.ReadChar();
	int channelB = stream.ReadChar();

	bmpFont->SetLineHeight(lineHeight);
	bmpFont->SetAscender(baseHeight);
	bmpFont->SetDescender(lineHeight - baseHeight);
	bmpFont->SetImageSize(textureSize);
	bmpFont->SetIsPacked(isPacked == 1);
	bmpFont->SetChannel(Color4B((byte)channelR, (byte)channelG, (byte)channelB, (byte)channelA).To4F());

	//read page lines
	stream.ReadChar();
	/*uint pageBlockSize=*/stream.Read<uint>();

	FOR_EACH_SIZE(i, pageCount)
	{
		HeapString pageFileName = stream.ReadString();
		TextureAtlasPage* page = new TextureAtlasPage(pageFileName);
		page->SetId(i);
		ITexture* texture = page->LoadTexture();
		
		if (texture == nullptr)
		{
			Log::FormatError("Failed to read texture:{}", pageFileName.c_str());
			return nullptr;
		}
		bmpFont->Atlas()->AddPage(page);
	}


	//read chars
	stream.ReadChar();
	uint charBlockSize = stream.Read<uint>();
	uint charCount = charBlockSize / 20;
	bmpFont->SetTotalCharCount(charCount);

	//read all char line
	int pageId;

	bool hasSpace = false;

	FOR_EACH_SIZE(i, charCount)
	{
		FontChar* fontChar = new FontChar();
		TextureAtlasRegion* region = new TextureAtlasRegion();
		region->SetIsTexcoordUpSide(false);

		fontChar->Id = (wchar_t)stream.Read<uint>();
		region->SetId(fontChar->Id);

		Rect2U textureRect;
		textureRect.Origin.X = stream.Read<ushort>();
		textureRect.Origin.Y = stream.Read<ushort>();
		textureRect.Size.Width = stream.Read<ushort>();
		textureRect.Size.Height = stream.Read<ushort>();
		region->SetTextureRect(textureRect);

		fontChar->HBearing.X = stream.Read<short>();
		fontChar->HBearing.Y = stream.Read<short>();
		fontChar->HAdvance = stream.Read<short>();
		pageId = stream.ReadChar();
		fontChar->Channel = stream.ReadChar();

		
		TextureAtlasPage* page= bmpFont->Atlas()->FindPage(pageId);
		if (page == nullptr)
		{
			Log::FormatError("Failed to find page id:{}", pageId);
			return nullptr;
		}
		page->AddRegion(region);
		fontChar->SetRegion(region);

		fontChar->HBearing.Y = (int)(bmpFont->Ascender() - fontChar->HBearing.Y);
		bmpFont->AddChar(fontChar);

		if (fontChar->Id == ' ')
		{
			bmpFont->SetSpaceFontChar(fontChar);
			hasSpace = true;
		}
	}

	if (!hasSpace)
	{
		FontChar* fontChar = new FontChar();
		fontChar->Id = ' ';
		fontChar->HAdvance = (ushort)bmpFont->Size() / 2;
		bmpFont->AddChar(fontChar);
		bmpFont->SetSpaceFontChar(fontChar);
	}


	
	int kerningBlockId = stream.ReadChar();
	if (kerningBlockId != -1)
	{
		//still have kerning pairs
		uint kerningBlockSize = stream.Read<uint>();
		uint kerningCount = kerningBlockSize / 10;

		FOR_EACH_SIZE(i, kerningCount)
		{
			FontKerning* kerning = new FontKerning();
			kerning->First = stream.Read<uint>();
			kerning->Second = stream.Read<uint>();
			kerning->Offset = stream.Read<short>();
			bmpFont->AddKerning(kerning);
		}
	}

	BMPFont* resultFont = bmpFont.release();
	return resultFont;
}

BMPFont* BMPFont::CreateFromBMPText(const FontId& fontId, const IStream& stream)
{
	List<HeapString> outLines;
	stream.ReadAllLinesTo(outLines);

	RETURN_NULL_IF_EMPTY(outLines);
	uint lineIndex = 0;

	//1.read info line
	StringRef infoLine = outLines[lineIndex++];
	int fontSize = 0;
	int isBold = 0;
	int isItalic = 0;
	int isUnicode = 0;
	int stretchHeight = 0;
	int isSmooth = 0;
	int isAtiAlias = 0;
	Padding4I padding = Padding4I::Zero;
	Point2I spacing = Point2I::Zero;
	int outLineThickness = 0;
	StringRef faceNameStr;

	bool isSuccess = StringParser::TryReadKeyValue(infoLine, "info face", "=\"", "\" ", faceNameStr);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "size", '=', ' ', fontSize);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "bold", '=', ' ', isBold);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "bold", '=', ' ', isBold);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "unicode", '=', ' ', isUnicode);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "stretchH", '=', ' ', stretchHeight);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "smooth", '=', ' ', isSmooth);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "aa", '=', ' ', isAtiAlias);

	int paddingBuffer[4];
	isSuccess = StringParser::TryReadKeyValues(infoLine, "padding", '=', ',', ' ', paddingBuffer);
	padding.Up = paddingBuffer[0];
	padding.Down = paddingBuffer[1];
	padding.Left = paddingBuffer[2];
	padding.Right = paddingBuffer[3];

	isSuccess = StringParser::TryReadKeyValues(infoLine, "spacing", '=', ',', ' ', spacing.Buffer);
	isSuccess = StringParser::TryReadKeyValue(infoLine, "outline", '=', ' ', outLineThickness);

	FontId resultFontId = fontId;
	resultFontId.SetOriginalSize(fontSize);

	std::unique_ptr<BMPFont> bmpFont(new BMPFont(resultFontId));
	bmpFont->SetIsBold(isBold == 1);
	bmpFont->SetIsItalic(isItalic == 1);
	bmpFont->SetPadding(padding);
	bmpFont->SetSpacing(spacing);
	bmpFont->SetOutlineThickness(outLineThickness);

	//read common line
	StringRef commonLine = outLines[lineIndex++];
	int lineHeight=0;
	int baseHeight=0;
	Size2U textureSize=Size2U::Zero;
	uint pageCount=0;
	int isPacked=0;
	int channelR=0;
	int channelG=0;
	int channelB=0;
	int channelA=0;

	isSuccess = StringParser::TryReadKeyValue(commonLine, "lineheight", '=', ' ', lineHeight);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "base", '=', ' ', baseHeight);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "scaleW", '=', ' ', textureSize.Width);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "scaleH", '=', ' ', textureSize.Height);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "pages", '=', ' ', pageCount);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "packed", '=', ' ', isPacked);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "alphaChnl", '=', ' ', channelA);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "redChnl", '=', ' ', channelR);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "greenChnl", '=', ' ', channelG);
	isSuccess = StringParser::TryReadKeyValue(commonLine, "blueChnl", '=', ' ', channelB);

	bmpFont->SetLineHeight(lineHeight);
	if (baseHeight==0)
	{
		baseHeight = lineHeight;
	}
	bmpFont->SetAscender(baseHeight);
	bmpFont->SetDescender(lineHeight - baseHeight);
	bmpFont->SetImageSize(textureSize);
	bmpFont->SetIsPacked(isPacked == 1);
	bmpFont->SetChannel(Color4B((byte)channelB, (byte)channelG, (byte)channelB, (byte)channelA).To4F());

	//read page lines
	HeapString pageFileName;
	FOR_EACH_SIZE(i, pageCount)
	{
		StringRef pageLine = outLines[lineIndex++];
		int pageId=0;
		isSuccess = StringParser::TryReadKeyValue(pageLine, "id", '=', ' ', pageId);
		isSuccess = StringParser::TryReadKeyValue(pageLine, "file", "=\"", "\"\n", pageFileName);

		pageFileName.RemoveLast();

		TextureAtlasPage* page = new TextureAtlasPage(pageFileName);
		page->SetId(pageId);
		ITexture* texture = page->LoadTexture();

		if (texture == nullptr)
		{
			Log::FormatError("Failed to read material:{}", pageFileName.c_str());
			return nullptr;
		}
		bmpFont->Atlas()->AddPage(page);
	}

	//read char count line
	StringRef charCountLine = outLines[lineIndex++];
	uint charCount;

	isSuccess = StringParser::TryReadKeyValue(charCountLine, "count", '=', ' ', charCount);
	bmpFont->SetTotalCharCount(charCount);

	//read all char line
	int pageId=0;

	bool hasSpace = false;

	FOR_EACH_SIZE(i, charCount)
	{
		FontChar* fontChar = new FontChar();
		TextureAtlasRegion* region = new TextureAtlasRegion();
		region->SetIsTexcoordUpSide(false);

		fontChar->SetRegion(region);
		Rect2U textureRect;
		StringRef charLine = outLines[lineIndex++];
		isSuccess = StringParser::TryReadKeyValue(charLine, "id", '=', ' ', fontChar->Id);
		isSuccess = StringParser::TryReadKeyValue(charLine, "x", '=', ' ', textureRect.Origin.X);
		isSuccess = StringParser::TryReadKeyValue(charLine, "y", '=', ' ', textureRect.Origin.Y);
		isSuccess = StringParser::TryReadKeyValue(charLine, "width", '=', ' ', textureRect.Size.Width);
		isSuccess = StringParser::TryReadKeyValue(charLine, "height", '=', ' ', textureRect.Size.Height);
		isSuccess = StringParser::TryReadKeyValue(charLine, "xoffset", '=', ' ', fontChar->HBearing.X);
		isSuccess = StringParser::TryReadKeyValue(charLine, "yoffset", '=', ' ', fontChar->HBearing.Y);
		isSuccess = StringParser::TryReadKeyValue(charLine, "xadvance", '=', ' ', fontChar->HAdvance);
		pageId = 0;
		isSuccess = StringParser::TryReadKeyValue(charLine, "page", '=', ' ', pageId);
		isSuccess = StringParser::TryReadKeyValue(charLine, "chnl", '=', ' ', fontChar->Channel);

		region->SetId(fontChar->Id);
		region->SetTextureRect(textureRect);

		auto* page= bmpFont->Atlas()->FindPage(pageId);
		if (page == nullptr)
		{
			Log::FormatError("Failed to find page id:{}", pageId);
			return nullptr;
		}
		page->AddRegion(region);
		fontChar->HBearing.Y = (int)(bmpFont->Ascender() - fontChar->HBearing.Y);

		bmpFont->AddChar(fontChar);

		if (fontChar->Id == ' ')
		{
			bmpFont->SetSpaceFontChar(fontChar);
			hasSpace = true;
		}
	}

	if (!hasSpace)
	{
		FontChar* fontChar = new FontChar();
		fontChar->Id = ' ';
		fontChar->HAdvance = (ushort)bmpFont->Size() / 2;
		bmpFont->AddChar(fontChar);
		bmpFont->SetSpaceFontChar(fontChar);

	}

	if (lineIndex < outLines.Count())
	{
		//still have kerning pairs
		//read kerning count line

		StringRef kerningCountLine = outLines[lineIndex++];
		uint kerningCount=0;
		isSuccess = StringParser::TryReadKeyValue(kerningCountLine, "count", '=', ' ', kerningCount);


		FOR_EACH_SIZE(i, kerningCount)
		{
			FontKerning* kerning = new FontKerning();

			StringRef kerningLine = outLines[lineIndex++];
			//read kerning line

			isSuccess = StringParser::TryReadKeyValue(kerningLine, "first", '=', ' ', kerning->First);
			isSuccess = StringParser::TryReadKeyValue(kerningLine, "second", '=', ' ', kerning->Second);
			isSuccess = StringParser::TryReadKeyValue(kerningLine, "amount", '=', ' ', kerning->Offset);

			bmpFont->AddKerning(kerning);
		}
	}

	if (lineIndex != outLines.Count())
	{
		Log::Error("Failed to parse all lines.");
		return nullptr;
	}

	BMPFont* resultFont = bmpFont.release();
	return resultFont;
}


BMPFont* BMPFont::CreateFromSingleTexture(const FontId& fontId, wchar_t firstChar /*= L'0'*/)
{
	TextureAtlasPage* page = new TextureAtlasPage(fontId.Name);
	ITexture* texture = page->LoadTexture();

	if (page == nullptr)
	{
		Log::FormatError("Failed to read font material:{}", fontId.Name.c_str());
		return nullptr;
	}
	Size2U textureSize = texture->Size();
	uint fontSize = fontId.Size();;
	std::unique_ptr<BMPFont> bmpFont(new BMPFont(fontId));

	bmpFont->SetLineHeight(textureSize.Height);
	bmpFont->SetAscender(textureSize.Height);
	bmpFont->SetDescender(0);
	bmpFont->SetImageSize(textureSize);


	bmpFont->Atlas()->AddPage(page);
	uint charCount = textureSize.Width / fontSize;
	bmpFont->SetTotalCharCount(charCount);

	//read all char line
	bool hasSpace = false;
	uint charWidth = fontSize;
	FOR_EACH_UINT32(i, charCount)
	{
		FontChar* fontChar = new FontChar();
		TextureAtlasRegion* region = new TextureAtlasRegion();
		fontChar->SetRegion(region);

		Rect2U textureRect;

		fontChar->Id = firstChar++;
		textureRect.Origin.X = i*charWidth;
		textureRect.Origin.Y = 0;
		textureRect.Size.Width = charWidth;
		textureRect.Size.Height = textureSize.Height;
		fontChar->HAdvance = (ushort)charWidth;

		fontChar->HBearing.Y = (int)(bmpFont->Ascender());

		region->SetIsTexcoordUpSide(false);
		region->SetTextureRect(textureRect);
		page->AddRegion(region);

		bmpFont->AddChar(fontChar);

		if (fontChar->Id == ' ')
		{
			bmpFont->SetSpaceFontChar(fontChar);

			hasSpace = true;
		}
	}

	if (!hasSpace)
	{
		FontChar* fontChar = new FontChar();
		fontChar->Id = ' ';
		fontChar->HAdvance = (ushort)bmpFont->Size() / 2;
		bmpFont->AddChar(fontChar);
		bmpFont->SetSpaceFontChar(fontChar);


	}

	BMPFont* resultFont = bmpFont.release();
	return resultFont;

}

MEDUSA_END;