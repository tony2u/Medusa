// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "CocosTextureAtlas.h"
#include "TextureAtlasPage.h"
#include "TextureAtlasRegion.h"
#include "Core/IO/Format/ApplePropertyListReader.h"
#include "Core/IO/Path.h"

MEDUSA_BEGIN;


TextureAtlasPage* CocosTextureAtlas::OnCreatePage(FileEntry& fileEntry, const FileIdRef& fileId, const IStream& stream)
{
	ApplePropertyListReader reader;
	auto data = stream.ReadToEnd();
	auto fileFormat = reader.CheckFormat(fileId.Name);
	if (!reader.LoadFromData(fileId, data, fileFormat))
	{
		Log::AssertFailedFormat("Invalid plist:{}", fileId);
		return nullptr;
	}
	std::unique_ptr<TextureAtlasPage> page(new TextureAtlasPage(0,&fileEntry));
	page->SetTexcoordUpSide(false);


	const ApplePropertyListNode& root = reader.Root();
	auto& metadata = root["metadata"];
	int format = metadata.ToInt("format");
	//auto pixelFormat = metadata.Optional("pixelFormat", StringRef::Empty);//RGBA8888
	auto premultiplyAlpha = metadata.Optional("premultiplyAlpha", false);
	auto sizeStr = metadata.ToString("size");
	auto size = ToSize(sizeStr);
	auto textureFileName = metadata.ToString("textureFileName");
	auto textureFileId = FileId::ParseFrom(textureFileName);
	page->SetTextureFileId(textureFileId);
	page->SetPremultiplyAlpha(premultiplyAlpha);
	page->SetPageSize(size);


	page->SetRotateDirection( RotateDirection::ClockWise);

	// check the format
	Log::AssertFormat(format >= 0 && format <= 3, "Invalid cocos texture atlas format:{}", format);

	const auto& frames = root.ToDict("frames");
	for (const auto& item : frames)
	{
		StringRef spriteName = item.Key;
		spriteName = Path::GetFileName(spriteName);	//get pure file name
		const auto& frame = *item.Value;
		std::unique_ptr<TextureAtlasRegion> region(new TextureAtlasRegion());
		region->SetName(spriteName);

		if (format == 2 || format == 1)	//from cocostudio
		{
			Rect2U rect = ToRect(frame.ToString("frame"));
			Point2I offset = ToPoint(frame.ToString("offset"));
			bool isRotated = frame.ToBool("rotated");
			Size2U sourceSize = ToSize(frame.ToString("sourceSize"));

			region->SetRotate(isRotated);
			region->SetTextureRect(rect);
			region->SetOriginalSize(sourceSize);

			//cocos offset is from picture center, so we have to transform to left-bottom
			Point2U realOffset;
			realOffset.X = sourceSize.Width / 2 + offset.X - rect.Width() / 2;
			realOffset.Y = sourceSize.Height / 2 - offset.Y - rect.Height() / 2;
			region->SetOffset(realOffset);
		}
		else if (format == 3)	//from texture packer
		{
			//max rect 
			//can support polygon 
			Size2U spriteSize = ToSize(frame.ToString("spriteSize"));
			Point2I spriteOffset = ToPoint(frame.ToString("spriteOffset"));
			Size2U spriteSourceSize = ToSize(frame.ToString("spriteSourceSize"));
			Rect2U textureRect = ToRect(frame.ToString("textureRect"));
			textureRect.Size = spriteSize;	//cocos not use this
			bool textureRotated = frame.ToBool("textureRotated");

			region->SetRotate(textureRotated);
			region->SetTextureRect(textureRect);
			region->SetOriginalSize(spriteSourceSize);

			//cocos offset is from picture center, so we have to transform to left-bottom
			Point2U realOffset;
			realOffset.X = spriteSize.Width / 2 + spriteOffset.X - textureRect.Width() / 2;
			realOffset.Y = spriteSize.Height / 2 - spriteOffset.Y - textureRect.Height() / 2;
			region->SetOffset(realOffset);

			auto* verticesNode = frame.Find("vertices");
			if (verticesNode != nullptr)
			{
				//has polygon
				auto vertices = ToUIntList(verticesNode->ToString());
				auto verticesUV = ToUIntList(frame.ToString("verticesUV"));
				auto triangles = ToUIntList(frame.ToString("triangles"));

				uint vertexCount = (uint)vertices.Count() / 2;
				FOR_EACH_SIZE(i, vertexCount)
				{
					auto& newVertex = region->MutableVertices().NewAdd();
					newVertex.X = vertices[i * 2];
					newVertex.Y = spriteSize.Height- vertices[i * 2 + 1];
					newVertex.Z = 0.f;

					auto& newTexcoord = region->MutableTexcoords().NewAdd();
					newTexcoord.X = ((float)verticesUV[i * 2]) / size.Width;
					newTexcoord.Y = 1.f - ((float)verticesUV[i * 2 + 1] ) / size.Height;


				}

				region->MutableIndices() = triangles;
			}

			auto aliasesList = frame["aliases"].ToList();
			for (auto aliaaItem : aliasesList)
			{
				auto aliasName = aliaaItem->ToString();
				auto* cloneRegion = region->Clone();
				cloneRegion->SetName(aliasName);
				page->AddRegion(cloneRegion);
			}

		}

		page->AddRegion(region.release());
	}



	return page.release();
}



Point2U CocosTextureAtlas::ToPoint(const StringRef& str)
{
	//{130,168}
	intp index = str.IndexOf(',');
	StringRef val1 = str.SubString(1, index - 1);
	StringRef val2 = str.SubString(index + 1, str.Length() - index - 1);
	Point2U val;
	val.X = StringParser::StringTo<uint>(val1);
	val.Y = StringParser::StringTo<uint>(val2);

	return val;
}

Size2U CocosTextureAtlas::ToSize(const StringRef& str)
{
	//{130,168}
	intp index = str.IndexOf(',');
	StringRef val1 = str.SubString(1, index - 1);
	StringRef val2 = str.SubString(index + 1, str.Length() - index - 1);
	Size2U size;
	size.Width = StringParser::StringTo<uint>(val1);
	size.Height = StringParser::StringTo<uint>(val2);

	return size;
}

Rect2U CocosTextureAtlas::ToRect(const StringRef& str)
{
	//{{1,189},{137,186}}
	Rect2U val;

	intp index = str.IndexOf(',');
	StringRef valStr = str.SubString(2, index - 2);
	val.Origin.X = StringParser::StringTo<uint>(valStr);
	++index;	//,

	valStr = str.SubStringTo(index, '}');
	val.Origin.Y = StringParser::StringTo<uint>(valStr);
	index += valStr.Length() + 3;

	valStr = str.SubStringTo(index, ',');
	val.Size.Width = StringParser::StringTo<uint>(valStr);
	index += valStr.Length() + 1;

	valStr = str.SubStringTo(index, '}');
	val.Size.Height = StringParser::StringTo<uint>(valStr);

	return val;
}

List<uint> CocosTextureAtlas::ToUIntList(const StringRef& str)
{
	List<uint> val;
	StringParser::SplitToValues<char>(str, " ", val);
	return val;
}

MEDUSA_END;

