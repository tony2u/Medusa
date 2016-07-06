// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "MedusaTextureAtlas.h"
#include "TextureAtlasPage.h"
#include "TextureAtlasRegion.h"


MEDUSA_BEGIN;



TextureAtlasPage* MedusaTextureAtlas::OnCreatePage(FileEntry& fileEntry, const FileIdRef& fileId, const IStream& stream)
{
	HeapString outLine;
	List<HeapString> outValues;

	std::unique_ptr<TextureAtlasPage> page(new TextureAtlasPage(0,&fileEntry));
	page->SetTexcoordUpSide(false);

	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, outLine, outValues));
	FileId textureFileId = FileId::ParseFrom(outValues[0]);
	page->SetTextureFileId(textureFileId);

	Size2U pageSize;
	pageSize.Width = (uint)outValues[1].ToInt();
	pageSize.Height = (uint)outValues[2].ToInt();
	page->SetPageSize(pageSize);

	//ignore format,use real image format instead
	//outValues[3]

	//read filter
	if (outValues[4] == "NearestNeighbour")
	{
		page->SetMagFilter(GraphicsTextureMagFilter::Nearest);
		page->SetMinFilter(GraphicsTextureMinFilter::Nearest);
	}
	else// if (outLine == "Linear")
	{
		page->SetMagFilter(GraphicsTextureMagFilter::Linear);
		page->SetMinFilter(GraphicsTextureMinFilter::Linear);
	}

	page->SetFlipPVR(StringParser::StringTo<bool>(outValues[5]));
	page->SetPremultiplyAlpha(StringParser::StringTo<bool>(outValues[6]));


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

TextureAtlasRegion* MedusaTextureAtlas::CreateAtlasRegion(const IStream& stream)
{
	HeapString outLine;
	List<HeapString> outValues;

	//read source texture rect
	Rect2U sourceRect;
	Rect2U textureRect;

	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, outLine, outValues));

	std::unique_ptr<TextureAtlasRegion> region(new TextureAtlasRegion());
	region->SetName(outValues[0]);
	region->SetRotate(StringParser::StringTo<bool>(outValues[1]));

	sourceRect.Origin.X = StringParser::StringTo<uint>(outValues[2]);
	sourceRect.Origin.Y = StringParser::StringTo<uint>(outValues[3]);
	sourceRect.Size.Width = StringParser::StringTo<uint>(outValues[4]);
	sourceRect.Size.Height = StringParser::StringTo<uint>(outValues[5]);


	textureRect.Origin.X = StringParser::StringTo<uint>(outValues[6]);
	textureRect.Origin.Y = StringParser::StringTo<uint>(outValues[7]);
	textureRect.Size.Width = StringParser::StringTo<uint>(outValues[8]);
	textureRect.Size.Height = StringParser::StringTo<uint>(outValues[9]);

	region->SetSourceRect(sourceRect);
	region->SetTextureRect(textureRect);


	return region.release();
}

MEDUSA_END;

