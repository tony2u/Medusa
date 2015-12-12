// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TextureAtlas.h"
#include "TextureAtlasPage.h"
#include "TextureAtlasRegion.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

TextureAtlas::TextureAtlas(const FileIdRef& fileId)
	:IResource(fileId)
{

}

TextureAtlas::~TextureAtlas()
{
	SAFE_DELETE_COLLECTION(mPages);
	mRegionDict.Clear();
	mRegionIdDict.Clear();
}

void TextureAtlas::AddPage(TextureAtlasPage* page)
{
	LOG_ASSERT_NOT_NULL(page);
	mPages.Add(page);
	if (page->Id()!=-1)
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
			Log::AssertFailedFormat("Duplicate region name:{} id:{}", region->Name(),region->Id());
			return;
		}
	}
}

TextureAtlasRegion* TextureAtlas::FindRegion(const StringRef& name) const
{
	return mRegionDict.TryGetValueWithFailed(name, nullptr);
}

TextureAtlasRegion* TextureAtlas::FindRegion(int id) const
{
	return mRegionIdDict.TryGetValueWithFailed(id, nullptr);
}

TextureAtlasPage* TextureAtlas::FindPage(int id) const
{
	return mPageDict.TryGetValueWithFailed(id, nullptr);
}

bool TextureAtlas::TryAddRegion(TextureAtlasRegion* region)
{
	bool isAdd = false;
	if (!region->Name().IsEmpty())
	{
		isAdd|=mRegionDict.TryAdd(region->Name(), region);
	}

	if (region->Id()!=-1)
	{
		isAdd |= mRegionIdDict.TryAdd(region->Id(), region);
	}
	return isAdd;
	
}

TextureAtlasPage* TextureAtlas::GetPage(size_t index) const
{
	return mPages[index];
}


MEDUSA_END;