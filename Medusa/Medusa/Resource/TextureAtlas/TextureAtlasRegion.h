// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Point3.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

class TextureAtlasRegion
{
public:
	TextureAtlasRegion();
	virtual ~TextureAtlasRegion();
public:
	int Id() const { return mId; }
	void SetId(int val) { mId = val; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	bool IsRotate() const { return mIsRotate; }
	void SetIsRotate(bool val);

	const Rect2U& TextureRect() const { return mTextureRect; }
	void SetTextureRect(const Rect2U& val);

	const Size2U& Size() const { return mTextureRect.Size; }
	void SetSize(const Size2U& val) { mTextureRect.Size = val; }

	const Size2U& OriginalSize() const { return mOriginalSize; }
	void SetOriginalSize(const Size2U& val) { mOriginalSize = val; }

	const Point2U& Offset() const { return mOffset; }
	void SetOffset(const Point2U& val) { mOffset = val; }

	TextureAtlasPage* Page() const { return mPage; }
	void SetPage(TextureAtlasPage* val);

	ITexture* Texture()const;

	bool IsTexcoordUpSide() const { return mIsTexcoordUpSide; }
	void SetIsTexcoordUpSide(bool val);

	bool UpdateMesh(const Size2U& textureSize);
	bool AssertMeshLoaded();

	const Array<Point3F, 4>& Vertices()  const{ return mVertices; }
	const Array<Point2F, 4>& Texcoords() const { return mTexcoords; }

	IMaterial* GetMaterial();
protected:
	int mId=-1;
	
	HeapString mName;
	Rect2U mTextureRect;

	//strip 
	Size2U mOriginalSize;
	Point2U mOffset;

	bool mIsRotate;
	bool mIsFlip;
	bool mIsTexcoordUpSide;	//some atlas region's texture rect's Y is down side, we need to convert it back
	
protected:
	TextureAtlasPage* mPage;

	//cached for performance
	Array<Point3F, 4> mVertices;
	Array<Point2F, 4> mTexcoords;

};

MEDUSA_END;
