// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ListBoxItem.h"
#include "Node/INode.h"

MEDUSA_BEGIN;


ListBoxItem::ListBoxItem()
	:BoundingBox(Rect2F::Zero)
{

}

ListBoxItem::~ListBoxItem(void)
{

}

int ListBoxItem::Compare(const ListBoxItem& item) const
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


void ListBoxItem::ArrangeNode(const Point2F& movement, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_IF_NULL(Node);
	Node->ArrangeRecursively(Rect2F(Point2F::Zero, BoundingBox.Size), arrangeFlags);
	mOffset = Node->Position2D();
	Node->SetPosition(BoundingBox.Origin + mOffset + movement);
}

void ListBoxItem::ApplyMovement(const Point2F& movement)
{
	RETURN_IF_NULL(Node);
	Node->SetPosition(BoundingBox.Origin + mOffset + movement);
}

MEDUSA_END;
