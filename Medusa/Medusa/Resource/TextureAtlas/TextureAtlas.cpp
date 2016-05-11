// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureAtlas.h"
#include "TextureAtlasPage.h"
#include "TextureAtlasRegion.h"
#include "Core/Log/Log.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Map/FileMapOrderItem.h"
#include "Core/IO/Map/FileMapNameItem.h"

MEDUSA_BEGIN;

TextureAtlas::TextureAtlas(const FileIdRef& fileId)
	:IResource(fileId)
{

}

TextureAtlas::~TextureAtlas()
{
	Unload();
}

bool TextureAtlas::LoadFromFileSystem(const FileIdRef& fileId)
{
	if (fileId.Order == 0)
	{
		//try to auto find all pages
		FileIdRef fileIdCopy = fileId;

		while (true)
		{
			if (FileSystem::Instance().Exists(fileIdCopy))
			{
				const IStream* stream = FileSystem::Instance().Read(fileIdCopy, FileDataType::Text);
				Log::AssertNotNullFormat(stream, "Cannot find file:", fileIdCopy);
				auto* page = OnCreatePage(fileIdCopy, *stream);
				RETURN_FALSE_IF_NULL(page);
				page->SetId(mPages.Count());
				AddPage(page);
				++fileIdCopy.Order;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		const IStream* stream = FileSystem::Instance().Read(fileId, FileDataType::Text);
		Log::AssertNotNullFormat(stream, "Cannot find file:", fileId);
		auto* page = OnCreatePage(fileId, *stream);
		RETURN_FALSE_IF_NULL(page);
		AddPage(page);
	}

	return true;
}

bool TextureAtlas::LoadFromNameItem(const FileMapNameItem& nameItem)
{
	for (auto order : nameItem.Items())
	{
		auto orderItem = order.Value;
		auto* fileEntry = orderItem->MutableFileEntry();	//only get first entry, ignore others with lower priority
		const IStream* stream = fileEntry->Read(FileDataType::Text);
		auto* page = OnCreatePage(orderItem->GetFileId(), *stream);
		RETURN_FALSE_IF_NULL(page);
		AddPage(page);

		for (auto* region : page->Regions())
		{
			FileSystem::Instance().MapFileReference(region->Name(), *fileEntry, region);
		}
	}

	return true;
}

void TextureAtlas::Unload()
{
	SAFE_DELETE_COLLECTION(mPages);
	mRegionDict.Clear();
	mRegionIdDict.Clear();
}

void TextureAtlas::AddPage(TextureAtlasPage* page)
{
	LOG_ASSERT_NOT_NULL(page);
	mPages.Add(page);
	if (page->Id() != -1)
	{
		if (!mPageDict.TryAdd(page->Id(), page))
		{
			Log::AssertFailedFormat("Duplicate page id:{} id:{}", page->Id());
			return;
		}
	}

	page->SetAtlas(this);

	const List<TextureAtlasRegion*>& regions = page->Regions();
	FOR_EACH_COLLECTION(i, regions)
	{
		TextureAtlasRegion* region = *i;
		if (!TryAddRegion(region))
		{
			Log::AssertFailedFormat("Duplicate region name:{} id:{}", region->Name(), region->Id());
			return;
		}
	}
}

TextureAtlasRegion* TextureAtlas::FindRegion(const StringRef& name) const
{
	return mRegionDict.GetOptional(name, nullptr);
}

TextureAtlasRegion* TextureAtlas::FindRegion(int id) const
{
	return mRegionIdDict.GetOptional(id, nullptr);
}

TextureAtlasPage* TextureAtlas::FindPage(int id) const
{
	return mPageDict.GetOptional(id, nullptr);
}

bool TextureAtlas::TryAddRegion(TextureAtlasRegion* region)
{
	bool isAdd = false;
	if (!region->Name().IsEmpty())
	{
		isAdd |= mRegionDict.TryAdd(region->Name(), region);
	}

	if (region->Id() != -1)
	{
		isAdd |= mRegionIdDict.TryAdd(region->Id(), region);
	}
	return isAdd;

}

TextureAtlasPage* TextureAtlas::GetPage(size_t index) const
{
	return mPages[index];
}


bool TextureAtlas::ReadLineToValues(const IStream& stream, const StringRef& name, HeapString& outLine, List<HeapString>& outValues)
{
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(stream.ReadLineToString(outLine, false));
	outValues.Clear();

	intp index = outLine.IndexOf(':');
	RETURN_FALSE_IF(index < 0);

	uintp count = (uintp)index;
	const char* p = outLine.c_str();
	while (*p == StdString::ConstValues<char>::Space)	//may be some line has white spaces at beginning
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

bool TextureAtlas::ReadLineToValues(const IStream& stream, HeapString& outLine, List<HeapString>& outValues)
{
	outLine.Clear();
	RETURN_FALSE_IF_FALSE(stream.ReadLineToString(outLine, false));
	outValues.Clear();

	return StringParser::Split(outLine.ToString(), StringRef(","), outValues);
}

MEDUSA_END;