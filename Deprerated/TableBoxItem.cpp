// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TableBoxItem.h"
#include "Node/INode.h"

MEDUSA_BEGIN;


int TableBoxItem::Compare(const TableBoxItem& item) const
{
	if (Index > item.Index)
	{
		return 1;
	}
	else if (Index < item.Index)
	{
		return -1;
	}
	return 0;
}


void TableBoxItem::ArrangeNode(const Size2F& itemSize, const Point2F& movement, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_IF_NULL(Node);
	Node->ArrangeRecursively(Rect2F(Position,itemSize), arrangeFlags);
	Node->SetPosition(Position + movement);
}

void TableBoxItem::ApplyMovement(const Point2F& movement)
{
	RETURN_IF_NULL(Node);
	Node->SetPosition(Position + movement);
}

MEDUSA_END;
