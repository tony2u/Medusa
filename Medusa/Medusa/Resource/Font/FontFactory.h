// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Dictionary.h"
#include "Resource/Font/FontId.h"
#include "Geometry/Size2.h"
#include "Resource/IResourceFactory.h"
#include "Core/IO/FileId.h"
#include "FontId.h"
#include "IFont.h"

MEDUSA_BEGIN;

class FontFactory :public Singleton<FontFactory>, public IResourceFactory < FontId, IFont >
{
	friend class Singleton < FontFactory > ;
public:
	FontFactory();
	~FontFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
	virtual void Shrink();
	virtual void Clear();
	virtual void ReleaseCache();

	virtual bool Remove(const FontId& fontId);
	virtual Share<IFont> Find(const FontId& fontId)const;
	virtual bool Add(const Share<IFont>& val, ResourceShareType shareType = ResourceShareType::Share);
public:
	Share<IFont> Create(const FontId& fontId, ResourceShareType shareType = ResourceShareType::Share);
	Share<IFont> CreateFromSingleTexture(const FontId& fontId, wchar_t firstChar = L'0', ResourceShareType shareType = ResourceShareType::Share);
	Share<IFont> CreateFromMemory(const FontId& fontId, const MemoryData& data, ResourceShareType shareType = ResourceShareType::Share);

	bool Exists(const StringRef& fontName)const;
	StringRef ExistsOr(const StringRef& fontName, const StringRef& optional)const;
	StringRef ExistsOrDefault(const StringRef& fontName)const;

	bool Exists(const FileIdRef& fontName)const;
	FileIdRef ExistsOr(const FileIdRef& fileId, const FileIdRef& optional)const;
	FileIdRef ExistsOrDefault(const FileIdRef& fileId)const;

private:
	Dictionary<FontId, Share<IFont>, DefaultHashCoder, EqualCompare > mItems;
	List<Share<IFont>> mCacheItems;
};

MEDUSA_END;