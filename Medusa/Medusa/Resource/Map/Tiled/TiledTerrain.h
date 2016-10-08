// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Property/VariantPropertySet.h"
#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class TiledTerrain
{
public:
	TiledTerrain();
	~TiledTerrain();
	bool operator==(const TiledTerrain& val)const { return mTileId == val.mTileId; }

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }
	int TileId() const { return mTileId; }
	void SetTileId(int val) { mTileId = val; }

	const VariantPropertySet& Properties() const { return mProperties; }
	VariantPropertySet& MutableProperties() { return mProperties; }

	void SetProperties(const VariantPropertySet& val) { mProperties = val; }
	bool Parse(const pugi::xml_node& node);

private:
	HeapString mName;
	int mTileId;
	VariantPropertySet mProperties;

};

MEDUSA_END;
