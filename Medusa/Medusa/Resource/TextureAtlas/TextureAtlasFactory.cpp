// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureAtlasFactory.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"

#include "Core/IO/FileSystem.h"
#include "Core/IO/Stream/IStream.h"

MEDUSA_BEGIN;

TextureAtlasFactory::TextureAtlasFactory()
{
	mPageCreater[(uint)TextureAtlasFileFormat::Spine] = PageCreater(CreateSpineAtlasPage);
}

TextureAtlasFactory::~TextureAtlasFactory()
{

}

bool TextureAtlasFactory::Initialize()
{
	return true;
}

bool TextureAtlasFactory::Uninitialize()
{
	Clear();
	return true;
}

TextureAtlas* TextureAtlasFactory::CreateEmpty(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		TextureAtlas* atlas = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(atlas);
	}

	TextureAtlas* result = new TextureAtlas(fileId);
	Add(result, shareType);
	return result;
}

TextureAtlasRegion* TextureAtlasFactory::CreateAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/)
{
	TextureAtlas* atlas = Create(atlasFileId, fileFormat, atlasPageCount);
	return atlas->FindRegion(regionName);
}


TextureAtlasRegion* TextureAtlasFactory::CreateAtlasRegion(int regionId, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/)
{
	TextureAtlas* atlas = Create(atlasFileId, fileFormat, atlasPageCount);
	return atlas->FindRegion(regionId);
}

TextureAtlas* TextureAtlasFactory::Create(const FileIdRef& fileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	{
		TextureAtlas* atlas = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(atlas);
	}

	std::unique_ptr<TextureAtlas> atlas(new TextureAtlas(fileId));
	//read file

	if (atlasPageCount == 1)
	{
		TextureAtlasPage* page = mPageCreater[(uint)fileFormat](fileId);
		atlas->AddPage(page);
	}
	else
	{
		FOR_EACH_UINT32(i, atlasPageCount)
		{
			TextureAtlasPage* page = mPageCreater[(uint)fileFormat](FileIdRef(fileId.Name, i));
			atlas->AddPage(page);
		}
	}

	TextureAtlas* result = atlas.release();

	Add(result, shareType);
	return result;
}


TextureAtlasPage* TextureAtlasFactory::CreateSpineAtlasPage(const FileIdRef& fileId)
{
	const IStream* stream = FileSystem::Instance().ReadFile(fileId,FileDataType::Text);
	RETURN_NULL_IF_NULL(stream);

	HeapString outLine;
	List<HeapString> outValues;
	//read page name
	do
	{
		//may be some empty lines at beginning
		outLine.Clear();
		stream->ReadLineToString(outLine, false);
	} while (outLine.IsEmpty());

	std::unique_ptr<TextureAtlasPage> page(new TextureAtlasPage(outLine));

	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(*stream, "size", outLine, outValues));
	Size2U pageSize;
	pageSize.Width = (uint)outValues[0].ToInt();
	pageSize.Height = (uint)outValues[1].ToInt();
	page->SetPageSize(pageSize);

	//ignore format
	outLine.Clear();
	RETURN_NULL_IF_FALSE(stream->ReadLineToString(outLine, false));

	//read filter
	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(*stream, "filter", outLine, outValues));
	page->SetMagFilter(ToMagFilter(outValues[0]));
	page->SetMinFilter(ToMinFilter(outValues[1]));

	//read wrap
	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(*stream, "repeat", outLine, outValues));
	page->SetWrapS(ToWrapS(outValues[0]));
	page->SetWrapT(ToWrapT(outValues[0]));

	//read regions
	TextureAtlasRegion* region = nullptr;
	do
	{
		region = CreateSpineAtlasRegion(*stream);
		if (region != nullptr)
		{
			page->AddRegion(region);
		}
	} while (region != nullptr);


	return page.release();
}


TextureAtlasRegion* TextureAtlasFactory::CreateSpineAtlasRegion(const IStream& stream)
{
	HeapString outLine;
	List<HeapString> outValues;
	outLine.Clear();
	RETURN_NULL_IF_FALSE(stream.ReadLineToString(outLine, false));

	std::unique_ptr<TextureAtlasRegion> region(new TextureAtlasRegion());
	region->SetName(outLine);

	//read rotate
	outLine.Clear();
	RETURN_NULL_IF_FALSE(ReadLineToValues(stream, "rotate", outLine, outValues));
	region->SetIsRotate(StringParser::StringTo<bool>(outValues[0]));

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
	region->SetIsTexcoordUpSide(false);

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


bool TextureAtlasFactory::ReadLineToValues(const IStream& stream, const StringRef& name, HeapString& outLine, List<HeapString>& outValues)
{
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(stream.ReadLineToString(outLine, false));
	outValues.Clear();

	intp index = outLine.IndexOf(':');
	RETURN_FALSE_IF(index < 0);

	uintp count =(uintp) index;
	const char* p = outLine.c_str();
	while (*p == StdString::ConstValues<char>::Space)	//may be some line has whitespaces at beginning
	{
		++p;
		--count;
	}

	if (StdString::CompareN(name.c_str(), p, count) != 0)
	{
		//name not fit
		return false;
	}

	outLine.RemoveAt(0, index + 1);	//remove name
	outLine.TrimAll();
	outValues.Clear();

	return StringParser::Split(outLine.ToString(), StringRef(","), outValues);
}

GraphicsInternalFormat TextureAtlasFactory::ToImageFormat(const StringRef& val)
{
	if (val == "Alpha")
	{
		return GraphicsInternalFormat::Alpha;
	}
	else if (val == "Intensity")
	{
		return GraphicsInternalFormat::Luminance;
	}
	else if (val == "LuminanceAlpha")
	{
		return GraphicsInternalFormat::LuminanceAlpha;
	}
	else if (val == "RGB565")
	{
		return GraphicsInternalFormat::RGBA;
	}
	else if (val == "RGBA4444")
	{
		return GraphicsInternalFormat::RGBA;
	}
	else if (val == "RGB888")
	{
		return GraphicsInternalFormat::RGB;
	}
	else if (val == "RGBA8888")
	{
		return GraphicsInternalFormat::RGB;
	}

	return GraphicsInternalFormat::RGBA;

}

GraphicsTextureMagFilter TextureAtlasFactory::ToMagFilter(const StringRef& val)
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

GraphicsTextureMinFilter TextureAtlasFactory::ToMinFilter(const StringRef& val)
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

GraphicsTextureWrapMode TextureAtlasFactory::ToWrapS(const StringRef& val)
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

GraphicsTextureWrapMode TextureAtlasFactory::ToWrapT(const StringRef& val)
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