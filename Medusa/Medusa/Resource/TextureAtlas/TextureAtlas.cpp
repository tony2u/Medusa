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
}

void TextureAtlas::AddPage(TextureAtlasPage* page)
{
	LOG_ASSERT_NOT_NULL(page);
	mPages.Add(page);
	page->SetAtlas(this);

	const List<TextureAtlasRegion*>& regions = page->Regions();
	FOR_EACH_COLLECTION(i, regions)
	{
		TextureAtlasRegion* region = *i;
		if (!mRegionDict.TryAdd(region->Name(), region))
		{
			Log::AssertFailedFormat("Duplicate region name:{}", region->Name().c_str());
		}
	}
}

TextureAtlasRegion* TextureAtlas::FindRegion(const StringRef& name) const
{
	return mRegionDict.TryGetValueWithFailed(name, nullptr);
}

TextureAtlasPage* TextureAtlas::GetPage(size_t index) const
{
	return mPages[index];
}


MEDUSA_END;