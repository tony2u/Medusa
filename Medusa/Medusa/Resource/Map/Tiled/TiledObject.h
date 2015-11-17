// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/Point2.h"
#include "Core/Geometry/Size2.h"
#include "Core/Pattern/Property/StringPropertySet.h"


MEDUSA_BEGIN;
class TiledObject
{
public:
	TiledObject();
	~TiledObject();
	bool operator<(const TiledObject& obj)const { return mId < obj.mId; }
	bool operator==(const TiledObject& obj)const { return mId == obj.mId; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }
	StringRef Type() const { return mType; }
	void SetType(const StringRef& val) { mType = val; }

	Point2I Position() const { return mPosition; }
	void SetPosition(Point2I val) { mPosition = val; }

	Size2I Size() const { return mSize; }
	void SetSize(Size2I val) { mSize = val; }

	bool IsVisible() const { return mIsVisible; }
	void SetVisible(bool val) { mIsVisible = val; }

	float Rotation() const { return mRotation; }
	void SetRotation(float val) { mRotation = val; }

	TiledTile* Tile() const { return mTile; }
	void SetTile(TiledTile* val) { mTile = val; }

	const StringPropertySet& Properties() const { return mProperties; }
	StringPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const StringPropertySet& val) { mProperties = val; }

	EllipseI * Ellipse() const { return mEllipse; }
	void SetEllipse(EllipseI * val) { mEllipse = val; }

	PolygonI* Polygon() const { return mPolygon; }
	void SetPolygon(PolygonI* val) { mPolygon = val; }

	PolygonI* Polyline() const { return mPolyline; }
	void SetPolyline(PolygonI* val) { mPolyline = val; }
private:
	int mId;
	HeapString mName;
	HeapString mType;
	
	Point2I mPosition;
	Size2I mSize;
	bool mIsVisible;
	float mRotation;
	
	TiledTile* mTile;	//An reference to a tile (optional).
	
	StringPropertySet mProperties;
	EllipseI *mEllipse;
	PolygonI* mPolygon;
	PolygonI* mPolyline;
};

MEDUSA_END;
