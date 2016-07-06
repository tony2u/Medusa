// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "TextureAtlas.h"

MEDUSA_BEGIN;


class CocosTextureAtlas:public TextureAtlas
{
public:
	using TextureAtlas::TextureAtlas;
	virtual TextureAtlasType AtlasType()const { return TextureAtlasType::Cocos; }
protected:
	virtual TextureAtlasPage* OnCreatePage(FileEntry& fileEntry, const FileIdRef& fileId, const IStream& stream) override;
private:
	static Point2U ToPoint(const StringRef& str);
	static Size2U ToSize(const StringRef& str);
	static Rect2U ToRect(const StringRef& str);
	static List<uint> ToUIntList(const StringRef& str);



};

MEDUSA_END;
