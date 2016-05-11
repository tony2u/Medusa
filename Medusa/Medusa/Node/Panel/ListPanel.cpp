// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ListPanel.h"
#include "Node/DataSource/IListDataSource.h"
#include "Geometry/Scroll/IScrollMathModel.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;


ListPanel::ListPanel(StringRef name/*=StringRef::Empty*/, ScrollDirection direction /*= ScrollDirection::VerticalFromTop*/)
	:ScrollPanel(name,direction)
{
	Log::AssertFormat(!direction.IsFreeOrNone(), "ListPanel only support one-way scroll");
}

ListPanel::~ListPanel( void )
{
}

bool ListPanel::Initialize()
{
	return true;
}


void ListPanel::SetScrollDirection(ScrollDirection direction)
{
	Log::AssertFormat(!direction.IsFreeOrNone(), "ListPanel only support one-way scroll");
	ScrollPanel::SetScrollDirection(direction);
}

void ListPanel::AddChild(INode* node)
{
	ScrollPanel::AddChild(node);
	mItems.Add(node);
}

bool ListPanel::RemoveChild(INode* node)
{
	bool isSuccess=ScrollPanel::RemoveChild(node);
	if (isSuccess)
	{
		return mItems.Remove(node);
	}

	return isSuccess;
}

void ListPanel::RemoveAllChilds(NodeRemoveFlags flags /*= NodeRemoveFlags::OnlyChildren*/)
{
	ScrollPanel::RemoveAllChilds(flags);
	mItems.Clear();
}

bool ListPanel::DeleteChild(INode* node)
{
	bool isSuccess=ScrollPanel::DeleteChild(node);
	if (isSuccess)
	{
		return mItems.Remove(node);
	}
	return isSuccess;

}

void ListPanel::DeleteAllChilds(NodeRemoveFlags flags /*= NodeRemoveFlags::OnlyChildren*/)
{
	ScrollPanel::DeleteAllChilds(flags);
	mItems.Clear();
}

void ListPanel::Clear(NodeRemoveFlags flags /*= NodeRemoveFlags::OnlyChildren*/)
{
	ScrollPanel::Clear(flags);
	mItems.Clear();
}

INode* ListPanel::GetItemByIndex(uint index) const
{
	return mItems[index];
}

bool ListPanel::InsertItemAt(uint index,INode* item)
{
	mItems.Insert(index,item);
	ScrollPanel::AddChild(item);
	return true;
}


INode* ListPanel::RemoveItemAt(uint index)
{
	if (index>=mItems.Count())
	{
		return nullptr;
	}
	INode* item=mItems[index];
	mItems.RemoveAt(index);
	ScrollPanel::RemoveChild(item);
	return item;
}

bool ListPanel::DeleteItemAt(uint index)
{
	if (index>=mItems.Count())
	{
		return false;
	}
	INode* item=mItems[index];
	mItems.RemoveAt(index);
	ScrollPanel::DeleteChild(item);
	return true;
}

bool ListPanel::RefreshAll()
{
	return true;
}

bool ListPanel::RefreshItem(uint index)
{
	return true;
}


void ListPanel::SetDataSource(IDataSource* dataSource)
{
	Log::AssertFailedFormat("ListPanel didn't support data source");
}



bool ListPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/,NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	Point2F totalMovment=mScrollModel->Offset();
	Rect2F targetBoundingBox=mScrollModel->CurrentWindow();

	//at this point,node tree is changed

	if (GetScrollDirection().IsHorizontal())
	{
		Point2F begin(0,0);
		begin+=totalMovment;

		Rect2F childRect=Rect2F::Zero;
		childRect.Size.Height=mSize.Height;
		childRect.Origin=begin;

		FOR_EACH_COLLECTION(i,mItems)
		{
			INode* child=*i;
			const Size2F& childMeasuredSize=child->MeasuredSize();
			childRect.Size.Width=childMeasuredSize.Width;
			childRect.Origin.X+=childRect.Size.Width;
			child->ArrangeRecursively(childRect,arrangeFlags);
		}

		targetBoundingBox.Size.Height=mSize.Height;
		targetBoundingBox.Size.Width=childRect.Right();
		targetBoundingBox.Origin=begin;
	}
	else
	{
		Point2F begin(0,mSize.Height);
		begin+=totalMovment;

		Rect2F childRect=Rect2F::Zero;
		childRect.Size.Width=mSize.Width;
		childRect.Origin=begin;

		FOR_EACH_COLLECTION(i,mItems)
		{
			INode* child=*i;
			const Size2F& childMeasuredSize=child->MeasuredSize();
			childRect.Size.Height=childMeasuredSize.Height;
			childRect.Origin.Y-=childRect.Size.Height;
			child->ArrangeRecursively(childRect,arrangeFlags);
		}

		targetBoundingBox.Size.Width=mSize.Width;
		targetBoundingBox.Size.Height=childRect.Origin.Y-begin.Y;
		targetBoundingBox.Origin=begin;

	}

	OnInitializeTargetBoundingBox();
	UpdateScrollStatus();
	return true;
}


void ListPanel::OnInitializeTargetBoundingBox()
{

	Rect2F targetBoundingBox=Rect2F::Zero;

	if (!mItems.IsEmpty())
	{
		//try to optimize this
		FOR_EACH_COLLECTION(i,mItems)
		{
			INode* child=*i;
			Rect2F boundingBox=child->GetBoundingBox().To2D();
			targetBoundingBox.Union(boundingBox);
		}
	}

	mScrollModel->Initialize(mSize.To2D(),targetBoundingBox);
}

void ListPanel::OnUpdateTargetBoundingBox()
{

}


MEDUSA_IMPLEMENT_RTTI(ListPanel, IPanel);


MEDUSA_END;
