// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Point2.h"
#include "Geometry/GeometryDefines.h"

MEDUSA_BEGIN;


class GridCell
{
public:
	GridCell() = default;
	GridCell(const Point2I& index):mIndex(index){}
	GridCell(int x,int y) :mIndex(x,y) {}


	bool operator==(const GridCell& other)const { return mIndex == other.mIndex; }

	GridMap* Map() const { return mMap; }
	void SetMap(GridMap* val);

	uint Id() const;

	int X()const { return mIndex.X; }
	int Y()const { return mIndex.Y; }
	const Point2I& Index() const { return mIndex; }
	void SetIndex(const Point2I& val) { mIndex = val; }
	void SetIndex(int x, int y) { mIndex.X = x; mIndex.Y = y; }

	uint Capability() const { return mCapability; }
	void SetCapability(uint val) { mCapability = val; }
	void AddCapability(uint val) { MEDUSA_FLAG_ADD(mCapability, val); }

	bool IsWalkable(uint agentCapabily)const { return (mCapability&agentCapabily) == mCapability; }	//agent capability include cell's capability
	bool HasDirection(MoveDirection toDirection)const { return MEDUSA_FLAG_HAS(mDirectionCapability, toDirection); }	//agent capability include cell's capability
	MoveDirection DirectionCapability() const;
	void SetDirectionCapability(MoveDirection val) { mDirectionCapability = val; }
	void RemoveDirectionCapability(MoveDirection val) { MEDUSA_FLAG_REMOVE(mDirectionCapability,val); }
	void AddDirectionCapability(MoveDirection val) { MEDUSA_FLAG_ADD(mDirectionCapability, val); }
	void OverlapDirectionCapability(MoveDirection val) { MEDUSA_FLAG_INTERSECT(mDirectionCapability, val); }

	void* UserData() const { return mUserData; }
	void SetUserData(void* val) { mUserData = val; }
protected:
	GridMap* mMap = nullptr;
	Point2I mIndex{ 0,0 };
	uint mCapability = 0;	//limit other to pass
	MoveDirection mDirectionCapability = MoveDirection::All8;	//limit directions to pass into this

	void* mUserData = nullptr;
	
};

MEDUSA_END;
