// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TableBoxItem.h"
#include "Node/INode.h"
#include "TableBox.h"

MEDUSA_BEGIN;


TableBoxItem::TableBoxItem()
	:BoundingBox(Rect2F::Zero)
{

}

TableBoxItem::~TableBoxItem(void)
{

}

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


void TableBoxItem::ArrangeNode(const Point2F& movement, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_IF_NULL(Node);
	Node->ArrangeRecursively(Rect2F(Point2F::Zero, BoundingBox.Size), arrangeFlags);
	mOffset = Node->Position2D();
	Node->SetPosition(BoundingBox.Origin + mOffset + movement);
}

void TableBoxItem::ApplyMovement(const Point2F& movement)
{
	RETURN_IF_NULL(Node);
	Node->SetPosition(BoundingBox.Origin + mOffset + movement);
}


void TableBoxItem::Initialzie(TableBox* parent, uint index, const Size2F& itemFixedSize)
{
	mParent = parent;
	Index = index;
	BoundingBox.Size = itemFixedSize;

	//init bounding box
	if (parent->IsVertical())
	{
		BoundingBox.Origin.X = Column()*itemFixedSize.Width;
		BoundingBox.Origin.Y = parent->Height() - (Row() + 1)*itemFixedSize.Height;
	}
	else
	{
		BoundingBox.Origin.X = Row()*itemFixedSize.Width;
		BoundingBox.Origin.Y = Column()*itemFixedSize.Height;
	}

}

uint TableBoxItem::Column() const
{
	return Index%mParent->ColumnCount();
}

uint TableBoxItem::Row() const
{
	return Index / mParent->ColumnCount();
}

MEDUSA_END;

