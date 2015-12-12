// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Graphics/GraphicsTypes.h"
#include "Core/Geometry/Size2.h"
#include "Core/IO/FileId.h"

MEDUSA_BEGIN;

class TextureAtlasPage
{
public:
	TextureAtlasPage(const FileIdRef& fileId);
	TextureAtlasPage(int id);

	virtual ~TextureAtlasPage();

	int Id() const { return mId; }
	void SetId(int val) { mId = val; }

	GraphicsTextureMagFilter MagFilter() const { return mMagFilter; }
	void SetMagFilter(GraphicsTextureMagFilter val) { mMagFilter = val; }

	GraphicsTextureMinFilter MinFilter() const { return mMinFilter; }
	void SetMinFilter(GraphicsTextureMinFilter val) { mMinFilter = val; }

	GraphicsTextureWrapMode WrapS() const { return mWrapS; }
	void SetWrapS(GraphicsTextureWrapMode val) { mWrapS = val; }

	GraphicsTextureWrapMode WrapT() const { return mWrapT; }
	void SetWrapT(GraphicsTextureWrapMode val) { mWrapT = val; }

	const List<TextureAtlasRegion*>& Regions() const { return mRegions; }

	void AddRegion(TextureAtlasRegion* region);

	Size2U Size()const;
	void SetPageSize(const Size2U& val);

	bool IsLoaded()const{ return mTexture != nullptr; }

	ITexture* LoadTexture();
	ITexture* GetTexture() const { return mTexture; }
	void SetTexture(ITexture* val);

	FileIdRef GetFileId() const { return mFileId.ToRef(); }
	void SetFileId(FileIdRef val) { mFileId = val; }

	TextureAtlas* Atlas() const { return mAtlas; }
	void SetAtlas(TextureAtlas* val);

	
protected:
	TextureAtlas* mAtlas=nullptr;

	FileId mFileId;

	GraphicsTextureMagFilter mMagFilter= GraphicsTextureMagFilter::Linear;
	GraphicsTextureMinFilter mMinFilter= GraphicsTextureMinFilter::Linear;
	GraphicsTextureWrapMode mWrapS= GraphicsTextureWrapMode::ClampToEdge;
	GraphicsTextureWrapMode mWrapT= GraphicsTextureWrapMode::ClampToEdge;
	List<TextureAtlasRegion*> mRegions;

protected:
	int mId=-1;

	Size2U mPageSize;//always equal with texture size
	ITexture* mTexture=nullptr;	//cached,lazy load
};

MEDUSA_END;
