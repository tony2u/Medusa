// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Geometry/Rect2.h"
#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Core/Collection/Array.h"
#include "Geometry/GeometryDefines.h"

MEDUSA_BEGIN;

class TextureAtlasRegion
{
public:
	TextureAtlasRegion();
	virtual ~TextureAtlasRegion();

	TextureAtlasRegion* Clone()const;
public:
	int Id() const { return mId; }
	void SetId(int val) { mId = val; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	RotateDirection GetRotateDirection()const;
	bool IsRotate() const { return mIsRotate; }
	void SetRotate(bool val);

	const Rect2U& TextureRect() const { return mTextureRect; }
	void SetTextureRect(const Rect2U& val);
	Rect2U ResultTextureRect() const;


	const Size2U& Size() const { return mTextureRect.Size; }
	void SetSize(const Size2U& val) { mTextureRect.Size = val; }

	const Size2U& OriginalSize() const { return mSourceRect.Size; }
	void SetOriginalSize(const Size2U& val) { mSourceRect.Size = val; }

	const Point2U& Offset() const { return mSourceRect.Origin; }
	void SetOffset(const Point2U& val) { mSourceRect.Origin = val; }

	const Rect2U& SourceRect() const { return mSourceRect; }
	void SetSourceRect(const Rect2U& val) { mSourceRect = val; }

	TextureAtlasPage* Page() const { return mPage; }
	void SetPage(TextureAtlasPage* val);

	ITexture* Texture()const;

	bool UpdateMesh(const Size2U& textureSize);
	bool AssertMeshLoaded();

	const List<Point3F>& Vertices()  const { return mVertices; }
	const List<Point2F>& Texcoords() const { return mTexcoords; }

	List<Point3F>& MutableVertices()  { return mVertices; }
	List<Point2F>& MutableTexcoords() { return mTexcoords; }

	const List<uint>& Indices() const { return mIndices; }
	List<uint>& MutableIndices() { return mIndices; }

	bool IsPolygon()const { return !mIndices.IsEmpty(); }

	IMaterial* CreateMaterial();
protected:
	int mId = -1;

	HeapString mName;
	Rect2U mTextureRect;
	Rect2U mSourceRect; //trim

	bool mIsRotate;
	bool mIsFlip;

protected:
	TextureAtlasPage* mPage=nullptr;

	//cached for performance
	List<Point3F> mVertices;
	List<Point2F> mTexcoords;

	List<uint> mIndices;	//used for polygon mode
	
};

MEDUSA_END;
