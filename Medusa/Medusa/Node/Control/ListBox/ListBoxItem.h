// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Geometry/Rect2.h"
#include "Node/NodeDefines.h"
#include "Node/NodeLayoutArrangeFlags.h"

MEDUSA_BEGIN;

class ListBoxItem
{
public:
	ListBoxItem();
	~ListBoxItem(void);
	bool operator<(const ListBoxItem& item)const{return Index<item.Index;}
	bool operator==(const ListBoxItem& item)const { return Index == item.Index; }

	int Compare(const ListBoxItem& item)const;
	void ApplyBoundingBox();
	void ArrangeNode(const Point2F& movement,NodeLayoutArrangeFlags arrangeFlags=NodeLayoutArrangeFlags::None);
	void ApplyMovement(const Point2F& movement);
public:
	INode* Node;
	size_t Index;
	int Type;

	Rect2F BoundingBox;
};

MEDUSA_END;
