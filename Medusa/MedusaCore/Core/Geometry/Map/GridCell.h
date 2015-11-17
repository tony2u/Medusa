// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Geometry/Point2.h"

MEDUSA_BEGIN;


class GridCell
{
public:
	GridCell() :mIndex(Point2I::Zero), mId(0), mCapability(0) {}
	uint Id() const { return mId; }
	void SetId(uint val) { mId = val; }

	int IndexX()const { return mIndex.X; }
	int IndexY()const { return mIndex.Y; }
	const Point2I& Index() const { return mIndex; }
	void SetIndex(const Point2I& val) { mIndex = val; }
	void SetIndex(int x, int y) { mIndex.X = x; mIndex.Y = y; }

	uint Capability() const { return mCapability; }
	void SetCapability(uint val) { mCapability = val; }
	bool IsWalkable(uint agentCapabily)const { return (mCapability&agentCapabily)==mCapability; }	//agent capability include cell's capability
	bool operator==(const GridCell& other)const { return mId == other.mId; }

protected:
	Point2I mIndex;
	uint mId;	//id in map
	uint mCapability;	//limit other to pass
	
};

MEDUSA_END;
