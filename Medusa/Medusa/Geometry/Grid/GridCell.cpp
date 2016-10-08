// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridCell.h"
#include "GridMap.h"
MEDUSA_BEGIN;


void GridCell::SetMap(GridMap* val)
{
	mMap = val;
	if (!mMap->AllowDiagonalMove())
	{
		RemoveDirectionCapability(MoveDirection::AllDiagonal);
	}
	else
	{
		AddDirectionCapability(MoveDirection::AllDiagonal);
	}
}

uint GridCell::Id() const
{
	return mMap->ToId(mIndex);
}

MoveDirection GridCell::DirectionCapability() const
{
	return mDirectionCapability;
}


MEDUSA_END;

