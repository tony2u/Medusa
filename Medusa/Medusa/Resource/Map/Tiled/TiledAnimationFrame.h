// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"


MEDUSA_BEGIN;

class TiledAnimationFrame
{
public:
	TiledAnimationFrame(int tileId = 0, uint durationMilliseconds = 0) :
		mTileId(tileId), mDurationMilliseconds(durationMilliseconds)
	{
	}
	bool operator<(const TiledAnimationFrame& obj)const { return mTileId < obj.mTileId; }
	bool operator==(const TiledAnimationFrame& obj)const { return mTileId == obj.mTileId; }


	int TileId() const { return mTileId; }
	void SetTileId(int val) { mTileId = val; }

	uint DurationMilliseconds() const { return mDurationMilliseconds; }
	void SetDurationMilliseconds(uint val) { mDurationMilliseconds = val; }
private:
	int mTileId;
	uint mDurationMilliseconds;
};

MEDUSA_END;
