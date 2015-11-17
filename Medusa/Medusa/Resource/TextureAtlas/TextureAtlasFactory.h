// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Core/Pattern/Delegate.h"
#include "Graphics/GraphicsTypes.h"
#include "TextureAtlasTypes.h"

MEDUSA_BEGIN;



class TextureAtlasFactory :public Singleton<TextureAtlasFactory>, public BaseResourceFactory < TextureAtlas >
{
	friend class Singleton < TextureAtlasFactory > ;
	typedef Delegate<TextureAtlasPage*(const FileIdRef& fileId)> PageCreater;
public:
	TextureAtlasFactory();
	~TextureAtlasFactory();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	TextureAtlas* Create(const FileIdRef& fileId, TextureAtlasFileFormat fileFormat = TextureAtlasFileFormat::Spine, uint atlasPageCount = 1, ResourceShareType shareType = ResourceShareType::Share);
	TextureAtlasRegion* CreateAtlasRegion(StringRef regionName,const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat = TextureAtlasFileFormat::Spine,  uint atlasPageCount = 1);
	TextureAtlasRegion* FindAtlasRegion(TextureAtlas* atlas, StringRef regionName);

private:
	static TextureAtlasPage* CreateSpineAtlasPage(const FileIdRef& fileId);
	static TextureAtlasRegion* CreateSpineAtlasRegion(const IStream& stream);


	PageCreater mPageCreater[(uint)TextureAtlasFileFormat::Count];

private:
	static bool ReadLineToValues(const IStream& stream, const StringRef& name, HeapString& outLine, List<HeapString>& outValues);
	static GraphicsInternalFormat ToImageFormat(const StringRef& val);
	static GraphicsTextureMagFilter ToMagFilter(const StringRef& val);
	static GraphicsTextureMinFilter ToMinFilter(const StringRef& val);
	static GraphicsTextureWrapMode ToWrapS(const StringRef& val);
	static GraphicsTextureWrapMode ToWrapT(const StringRef& val);



	
};

MEDUSA_END;