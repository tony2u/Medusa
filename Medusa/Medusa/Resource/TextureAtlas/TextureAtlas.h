// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Resource/IResource.h"
#include "Core/Collection/Dictionary.h"
#include "Core/IO/IFileLoadable.h"
#include "TextureAtlasDefines.h"

MEDUSA_BEGIN;

class TextureAtlas:public IResource
{
public:
	TextureAtlas(const FileIdRef& fileId);
	virtual ~TextureAtlas();

	virtual ResourceType Type()const{return ResourceType::TextureAtlas;}
	static ResourceType ClassGetResourceType(){ return ResourceType::TextureAtlas; }
	virtual TextureAtlasType AtlasType()const { return TextureAtlasType::None; }

	bool LoadFromFileSystem(const FileIdRef& fileId);
	bool LoadFromNameItem(const FileMapNameItem& nameItem);

	virtual void Unload()override;
public:
	void AddPage(TextureAtlasPage* page);
	TextureAtlasPage* GetPage(size_t index)const;
	size_t PageCount()const{ return mPages.Count(); }
	const List<TextureAtlasPage*>& Pages() const { return mPages; }

	TextureAtlasRegion* FindRegion(const StringRef& name)const;
	TextureAtlasRegion* FindRegion(int id)const;

	TextureAtlasPage* FindPage(int id)const;

	bool TryAddRegion(TextureAtlasRegion* region);

protected:
	virtual TextureAtlasPage* OnCreatePage(const FileIdRef& fileId,const IStream& stream) { return nullptr; }

protected:
	static bool ReadLineToValues(const IStream& stream, const StringRef& name, HeapString& outLine, List<HeapString>& outValues);
	static bool ReadLineToValues(const IStream& stream, HeapString& outLine, List<HeapString>& outValues);
protected:
	List<TextureAtlasPage*> mPages;

	Dictionary<int,TextureAtlasPage*> mPageDict;

	Dictionary<StringRef, TextureAtlasRegion*> mRegionDict;	//for quick access
	Dictionary<int, TextureAtlasRegion*> mRegionIdDict;	//for quick access


};

MEDUSA_END;
