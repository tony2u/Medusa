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
#include "Core/IO/Map/FileMapOrderItem.h"
#include "Core/IO/Map/FileMapNameItem.h"

#include "Resource/Texture/TextureFactory.h"

#include "Core/IO/FileInfo.h"

#include "SpineTextureAtlas.h"
#include "MedusaTextureAtlas.h"
#include "CocosTextureAtlas.h"


MEDUSA_BEGIN;

TextureAtlasFactory::TextureAtlasFactory()
{
	mObjectFactory.Register<SpineTextureAtlas>((size_t)TextureAtlasType::Spine);
	mObjectFactory.Register<MedusaTextureAtlas>((size_t)TextureAtlasType::MedusaCustom);
	mObjectFactory.Register<CocosTextureAtlas>((size_t)TextureAtlasType::Cocos);

}

TextureAtlasFactory::~TextureAtlasFactory()
{
	Uninitialize();
}

bool TextureAtlasFactory::Initialize()
{
	//find all atlas in file system
	List<FileMapNameItem*> outAtlasItems;
	FileSystem::Instance().TryGetNameItemsWithExtension(FileExtensions::atlas, outAtlasItems);
	FileSystem::Instance().TryGetNameItemsWithExtension(FileExtensions::matlas, outAtlasItems);
	FileSystem::Instance().TryGetNameItemsWithExtension(FileExtensions::plist, outAtlasItems);
	FileSystem::Instance().TryGetNameItemsWithExtension(FileExtensions::bplist, outAtlasItems);
	for (auto nameItem : outAtlasItems)
	{
		auto atlas = CreateEmpty(nameItem->Name());
		atlas->LoadFromNameItem(*nameItem);
	}

	return true;
}

bool TextureAtlasFactory::Uninitialize()
{
	Clear();
	return true;
}

Share<TextureAtlas> TextureAtlasFactory::CreateEmpty(const FileIdRef& fileId, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		auto atlas = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(atlas);
	}

	auto fileFormat = TryGetAtlasType(fileId.Name);
	Share<TextureAtlas> atlas = mObjectFactory.Create((size_t)fileFormat, fileId);
	if (atlas != nullptr)
	{
		Add(atlas, shareType);
	}

	return atlas;
}

TextureAtlasRegion* TextureAtlasFactory::CreateAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasType fileFormat /*= TextureAtlasFileFormat::None*/)
{
	auto atlas = Create(atlasFileId, fileFormat);
	return atlas->FindRegion(regionName);
}


TextureAtlasRegion* TextureAtlasFactory::CreateAtlasRegion(int regionId, const FileIdRef& atlasFileId, TextureAtlasType fileFormat /*= TextureAtlasFileFormat::None*/)
{
	auto atlas = Create(atlasFileId, fileFormat);
	return atlas->FindRegion(regionId);
}

Share<TextureAtlas> TextureAtlasFactory::Create(const FileIdRef& fileId, TextureAtlasType fileFormat /*= TextureAtlasFileFormat::None*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		auto atlas = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(atlas);
	}

	if (fileFormat == TextureAtlasType::None)
	{
		fileFormat = TryGetAtlasType(fileId.Name);
	}

	if (fileFormat == TextureAtlasType::None)
	{
		Log::AssertFailedFormat("Have no TextureAtlasFileFormat : {} ", fileId);
		return nullptr;
	}

	Share<TextureAtlas> atlas = mObjectFactory.Create((size_t)fileFormat, fileId);
	if (!atlas->LoadFromFileSystem(fileId))
	{
		atlas = nullptr;
	}

	if (atlas)
	{
		Add(atlas, shareType);
	}

	return atlas;
}

Share<TextureAtlas> TextureAtlasFactory::CreateTiledAtlas(const FileIdRef& textureFileId, const Size2U textureSize, const Size2U& tileSize, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType != ResourceShareType::None)
	{
		auto atlas = Find(textureFileId);
		RETURN_SELF_IF_NOT_NULL(atlas);
	}

	std::unique_ptr<TextureAtlas> atlas(new TextureAtlas(textureFileId));
	TextureAtlasPage* page = new TextureAtlasPage(textureFileId);
	page->SetId(0);
	page->SetPageSize(textureSize);
	page->SetTexcoordUpSide(false);	//from up to down
	atlas->AddPage(page);

	uint column = textureSize.Width / tileSize.Width;
	uint row = textureSize.Height / tileSize.Height;
	FOR_EACH_SIZE(i, row)
	{
		FOR_EACH_SIZE(j, column)
		{
			TextureAtlasRegion* region = new TextureAtlasRegion();
			region->SetId((uint)(i*row + j));
			region->SetTextureRect(Rect2U(mpp(j*tileSize.Width, i*tileSize.Height), tileSize));
			page->AddRegion(region);
		}
	}

	Share<TextureAtlas> result = atlas.release();

	Add(result, shareType);
	return result;
}


TextureAtlasType TextureAtlasFactory::TryGetAtlasType(const StringRef& fileName)
{
	auto fileType = FileInfo::ExtractType(fileName);
	switch (fileType)
	{
	case FileType::atlas:
		return TextureAtlasType::Spine;
	case FileType::matlas:
		return TextureAtlasType::MedusaCustom;
	case FileType::plist:
	case FileType::bplist:
		return TextureAtlasType::Cocos;
	default:
		break;
	}

	return TextureAtlasType::None;

}

MEDUSA_END;