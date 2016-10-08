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
	TableBoxItem();
	~TableBoxItem(void);
	bool operator<(const TableBoxItem& item)const { return Index < item.Index; }
	bool operator==(const TableBoxItem& item)const { return Index == item.Index; }

	int Compare(const TableBoxItem& item)const;
	void ArrangeNode(const Point2F& movement, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None);
	void ApplyMovement(const Point2F& movement);

	float Width()const { return BoundingBox.Width(); }
	float Height()const { return BoundingBox.Height(); }

	TableBox* Parent() const { return mParent; }
	void SetParent(TableBox* val) { mParent = val; }

	void Initialzie(TableBox* parent, uint index,const Size2F& itemFixedSize);

	uint Row()const;
	uint Column()const;

public:
	INode* Node = nullptr;
	size_t Index = 0;
	int Tag = 0;

	Rect2F BoundingBox;
private:
	Point2F mOffset{ 0.f,0.f };
	TableBox* mParent=nullptr;
};

MEDUSA_END;
