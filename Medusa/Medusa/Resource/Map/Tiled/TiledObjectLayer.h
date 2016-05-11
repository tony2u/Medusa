// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ITiledLayer.h"
#include "Geometry/Color4.h"
#include "Core/Collection/List.h"
#include "TiledObject.h"

MEDUSA_BEGIN;

class TiledObjectLayer : public ITiledLayer
{
public:
	TiledObjectLayer();
	virtual ~TiledObjectLayer();
	virtual TiledLayerType Type()const override { return TiledLayerType::Object; }
	bool Parse(const pugi::xml_node& node);

	Color4B Color() const { return mColor; }
	void SetColor(Color4B val) { mColor = val; }

	const List<TiledObject>& Objects() const { return mObjects; }
	TiledObject& NewObject() { return mObjects.NewAdd(); }
private:
	Color4B mColor;
	
	List<TiledObject> mObjects;
	
};

MEDUSA_END;
