// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Property/StringPropertySet.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;

class TiledTerrain
{
public:
	TiledTerrain();
	~TiledTerrain();

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }
	int TileId() const { return mTileId; }
	void SetTileId(int val) { mTileId = val; }

	const StringPropertySet& Properties() const { return mProperties; }
	StringPropertySet& MutableProperties() { return mProperties; }

	void SetProperties(const StringPropertySet& val) { mProperties = val; }

private:
	HeapString mName;
	int mTileId;
	StringPropertySet mProperties;

};

MEDUSA_END;
