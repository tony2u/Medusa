// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Rect2.h"
#include "Node/NodeDefines.h"

MEDUSA_BEGIN;

class TableBoxItem
{
public:
	bool operator<(const TableBoxItem& item)const { return Index < item.Index; }
	bool operator==(const TableBoxItem& item)const { return Index == item.Index; }

	int Compare(const TableBoxItem& item)const;
	void ArrangeNode(const Size2F& itemSize, const Point2F& movement, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None);
	void ApplyMovement(const Point2F& movement);

public:
	INode* Node = nullptr;
	size_t Index = 0;
	int Tag = 0;

	Point2F Position{ 0.f,0.f };
};

MEDUSA_END;
