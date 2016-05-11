// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SpineTextureAtlas.h"
#include "TextureAtlasPage.h"
#include "TextureAtlasRegion.h"


MEDUSA_BEGIN;

TextureAtlasPage* SpineTextureAtlas::OnCreatePage(const FileIdRef& fileId, const IStream& stream)
{
	HeapString outLine;
	List<HeapString> outValues;
	//read page name
	do
	{
		//may be some empty lines at beginning
		outLine.Clear();
		stream.ReadLineToString(outLine, false);
	} while (outLine.IsEmpty());


	std::unique_ptr<TextureAtlasPage> page(new TextureAtlasPage(0));
	FileId textureFileId = FileId::ParseFrom(outLine);
	page->SetTextureFileId(textureFileId);

	page->SetTexcoordUpSide(false);
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(ReadLineToValues(stream, "size", outLine, outValues));
	Size2U pageSize;
	pageSize.Width = (uint)outValues[0].ToInt();
	pageSize.Height = (uint)outValues[1].ToInt();
	page->SetPageSize(pageSize);

	//ignore format
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(stream.ReadLineToString(outLine, false));

	//read filter
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(ReadLineToValues(stream, "filter", outLine, outValues));
	page->SetMagFilter(ToMagFilter(outValues[0]));
	page->SetMinFilter(ToMinFilter(outValues[1]));

	//read wrap
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(ReadLineToValues(stream, "repeat", outLine, outValues));
	page->SetWrapS(ToWrapS(outValues[0]));
	page->SetWrapT(ToWrapT(outValues[0]));

	//read regions
	TextureAtlasRegion* region = nullptr;
	do
	{
		region = CreateAtlasRegion(stream);
		if (region != nullptr)
		{
			page->AddRegion(region);
		}
	} while (region != nullptr);


	return page.release();
}

TextureAtlasRegion* SpineTextureAtlas::CreateAtlasRegion(const IStream& stream)
{
	HeapString outLine;
	List<HeapString> outValues;
	outLine.Clear();
	RETURN_NULL_IF_FALSE(stream.ReadLineToString(outLine, false));

	std::unique_ptr<TextureAtlasRegion> region(new TextureAtlasRegion());

	outLine += FileExtensions::png;	//add .png
	region->SetName(outLine);

	//read rotate
	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "rotate", outLine, outValues));
	region->SetRotate(StringParser::StringTo<bool>(outValues[0]));

	//read texture rect
	Rect2U textureRect;
	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "xy", outLine, outValues));
	textureRect.Origin.X = StringParser::StringTo<uint>(outValues[0]);
	textureRect.Origin.Y = StringParser::StringTo<uint>(outValues[1]);

	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "size", outLine, outValues));
	textureRect.Size.Width = StringParser::StringTo<uint>(outValues[0]);
	textureRect.Size.Height = StringParser::StringTo<uint>(outValues[1]);

	region->SetTextureRect(textureRect);

	//read trim
	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "orig", outLine, outValues));
	Size2U originalSize;
	originalSize.Width = StringParser::StringTo<uint>(outValues[0]);
	originalSize.Height = StringParser::StringTo<uint>(outValues[1]);
	region->SetOriginalSize(originalSize);

	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "offset", outLine, outValues));
	Point2U offset;
	offset.X = StringParser::StringTo<uint>(outValues[0]);
	offset.Y = StringParser::StringTo<uint>(outValues[1]);
	region->SetOffset(offset);

	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "index", outLine, outValues));	//ignore index

	return region.release();
}

GraphicsTextureMagFilter SpineTextureAtlas::ToMagFilter(const StringRef& val)
{
	if (val == "Nearest")
	{
		return GraphicsTextureMagFilter::Nearest;
	}
	else if (val == "Linear")
	{
		return GraphicsTextureMagFilter::Linear;
	}

	return GraphicsTextureMagFilter::Nearest;
}

GraphicsTextureMinFilter SpineTextureAtlas::ToMinFilter(const StringRef& val)
{
	if (val == "Nearest")
	{
		return GraphicsTextureMinFilter::Nearest;
	}
	else if (val == "Linear")
	{
		return GraphicsTextureMinFilter::Linear;
	}
	else if (val == "MipMap")
	{
		return GraphicsTextureMinFilter::Nearest;	//ignore
	}
	else if (val == "MipMapNearestNearest")
	{
		return GraphicsTextureMinFilter::NearestMipMapNearest;
	}
	else if (val == "MipMapLinearNearest")
	{
		return GraphicsTextureMinFilter::LinearMipMapNearest;
	}
	else if (val == "MipMapNearestLinear")
	{
		return GraphicsTextureMinFilter::NearestMipMapLinear;
	}
	else if (val == "MipMapLinearLinear")
	{
		return GraphicsTextureMinFilter::LinearMipMapLinear;
	}

	return GraphicsTextureMinFilter::Nearest;
}

GraphicsTextureWrapMode SpineTextureAtlas::ToWrapS(const StringRef& val)
{
	if (val == "none")
	{
		return GraphicsTextureWrapMode::ClampToEdge;
	}

	if (val.BeginWith("x"))
	{
		return GraphicsTextureWrapMode::Repeat;
	}
	if (val.BeginWith("y"))
	{
		return GraphicsTextureWrapMode::ClampToEdge;
	}
	else
	{
		return GraphicsTextureWrapMode::Repeat;
	}



}

GraphicsTextureWrapMode SpineTextureAtlas::ToWrapT(const StringRef& val)
{
	if (val == "none")
	{
		return GraphicsTextureWrapMode::ClampToEdge;
	}

	if (val.BeginWith("y"))
	{
		return GraphicsTextureWrapMode::Repeat;
	}

	if (val.BeginWith("x"))
	{
		return GraphicsTextureWrapMode::ClampToEdge;
	}
	else
	{
		return GraphicsTextureWrapMode::Repeat;
	}
}


MEDUSA_END;

