// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/Geometry/Size2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "TiledDefines.h"

MEDUSA_BEGIN;

class ITiledLayer
{
public:
	ITiledLayer();
	virtual ~ITiledLayer();
	virtual TiledLayerType Type()const = 0;

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	Point2I Position() const { return mPosition; }
	void SetPosition(Point2I val) { mPosition = val; }

	Size2I Size() const { return mSize; }
	void SetSize(Size2I val) { mSize = val; }
	float Opacity() const { return mOpacity; }
	void SetOpacity(float val) { mOpacity = val; }

	int ZOrder() const { return mZOrder; }
	void SetZOrder(int z) { mZOrder = z; }
	bool IsVisible() const { return mIsVisible; }
	void SetVisible(bool val) { mIsVisible = val; }

	const StringPropertySet& Properties() const { return mProperties; }
	StringPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const StringPropertySet& val) { mProperties = val; }

protected:
	HeapString mName;
	Point2I mPosition;
	Size2I mSize;
	float mOpacity;
	bool mIsVisible;

	StringPropertySet mProperties;
	int mZOrder;
};

MEDUSA_END;
