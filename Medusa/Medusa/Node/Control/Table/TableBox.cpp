// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TableBox.h"
#include "Geometry/Scroll/IScrollMathModel.h"
#include "Core/Log/Log.h"
#include "Node/Input/Gesture/SwipeGestureRecognizer.h"
#include "Node/Input/Gesture/EventArg/SwipeBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeFailedGestureEventArg.h"
#include "Node/NodeFactory.h"
#include "Node/Input/InputDispatcher.h"
#include "Node/Binding/BaseListDataBinding.h"

MEDUSA_BEGIN;


TableBox::TableBox(StringRef name, ScrollDirection direction)
	:ScrollPanel(name, direction), mSelectedItem(nullptr),
	mCacheEnabed(false),
	mValidRange(RangeI::Init)
{
	Log::AssertFormat(!direction.IsFreeOrNone(), "TableBox only support one-way scroll");

	MutableInput().Enable(true);

}

TableBox::TableBox(StringRef name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:ScrollPanel(name, e)
{
}

TableBox::~TableBox(void)
{
	ClearCache();
}

bool TableBox::Initialize()
{
	return true;
}

void TableBox::ClearCache()
{
	SAFE_DELETE_COLLECTION(mSingleTypeItemCache);
	for (auto i : mMultipleTypeItemCache)
	{
		Queue<INode*>* nodes = i.Value;
		SAFE_DELETE_COLLECTION(*nodes);
		SAFE_DELETE(nodes);
	}
	mSingleTypeItemCache.Clear();
}


void TableBox::SetScrollDirection(ScrollDirection direction)
{
	Log::AssertFormat(!direction.IsFreeOrNone(), "TableBox only support one-way scroll");
	ScrollPanel::SetScrollDirection(direction);
}


bool TableBox::SetBinding(IDataBinding* val)
{
	RETURN_FALSE_IF_FALSE(INode::SetBinding(val));

	ClearCache();
	Clear();
	mItems.Clear();

	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)val;
	listDataBinding->EnableFixedSize(true);

	listDataBinding->OnItemAdded += Bind(&TableBox::OnItemAdded, this);
	listDataBinding->OnItemRemoved += Bind(&TableBox::OnItemRemoved, this);
	listDataBinding->OnItemUpdated += Bind(&TableBox::OnItemUpdated, this);
	listDataBinding->OnTotalChanged += Bind(&TableBox::OnTotalChanged, this);
	return true;
}


bool TableBox::IsSensitiveToChildLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)
{
	return false;
}

bool TableBox::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	RETURN_TRUE_IF_NULL(mBinding);
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	size_t itemCount = listDataBinding->Count();

	if (mItems.IsEmpty() && itemCount != 0)
	{
		OnTotalChanged();
	}
	else
	{

		Point2F totalMovment = mScrollModel->Offset();
		SetupItems();
		mScrollModel->ScrollBy(totalMovment);

		//check items
		FOR_EACH_SIZE(i, itemCount)
		{
			TableBoxItem& item = mItems[i];
			BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
		}

	}

	UpdateScrollStatus();
	return true;
}


void TableBox::OnTotalChanged()
{
	mScrollModel->ApplyMovement();

	//clear current items
	for (auto& item : mItems)
	{
		if (item.Node != nullptr)
		{
			RecycleItemNode(item);
		}
	}
	mItems.Clear();
	mValidRange = RangeI::Init;

	//create new items
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	//update item fixed size
	if (!mItemFixedSize.IsNearlyZero())
	{
		mResultItemFixedSize = mItemFixedSize;
	}
	else
	{
		mResultItemFixedSize = listDataBinding->GetFixedSize(GetItemLimitSize());
	}

	UpdateRowColumnCount();


	mItems.ForceReserveCount(listDataBinding->Count());
	SetupItems();
	//load nodes for items
	for (auto& item : mItems)
	{
		BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
	}
}

void TableBox::UpdateRowColumnCount()
{
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;

	if (IsVertical())
	{
		mColumnCount = (uint)Math::Floor(mSize.Width / mResultItemFixedSize.Width);
		mRowCount = listDataBinding->Count() / mColumnCount + 1;
	}
	else
	{
		mColumnCount = (uint)Math::Floor(mSize.Height / mResultItemFixedSize.Height);
		mRowCount = listDataBinding->Count() / mColumnCount + 1;
	}
}

Rect2F TableBox::CalculateTotalBoundingBox() const
{
	Rect2F targetBoundingBox = Rect2F::Zero;

	if (IsVertical())
	{
		targetBoundingBox.Size.Width = mColumnCount*mResultItemFixedSize.Width;
		targetBoundingBox.Size.Height = mRowCount*mResultItemFixedSize.Height;
		targetBoundingBox.Origin.Y = mSize.Height - targetBoundingBox.Size.Height;
	}
	else
	{
		targetBoundingBox.Size.Width = mRowCount*mResultItemFixedSize.Width;
		targetBoundingBox.Size.Height = mColumnCount*mResultItemFixedSize.Height;
	}

	return targetBoundingBox;
}

void TableBox::OnItemAdded(size_t index)
{
	mScrollModel->ApplyMovement();
	size_t itemCount = mItems.Count();

	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	TableBoxItem newItem;
	newItem.Initialzie(this, index, mResultItemFixedSize);
	newItem.Tag = listDataBinding->GetTemplateTag(index);

	TryLoadOrRecycleItem(newItem, true);
	mItems.Insert(index, newItem);

	auto newBoundingBox = CalculateTotalBoundingBox();
	auto deltaSize = newBoundingBox.Size - mScrollModel->CurrentWindow().Size;
	mScrollModel->UpdateWindow(deltaSize);

	if (index < itemCount)
	{
		//update next items' bounding box
		FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
		{
			TableBoxItem& item = mItems[i];
			item.Initialzie(this, i, mResultItemFixedSize);
		}
		FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
		{
			TableBoxItem& item = mItems[i];
			BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
		}
	}

}

void TableBox::OnItemRemoved(size_t index)
{
	mScrollModel->ApplyMovement();

	intp itemCount = (intp)mItems.Count();
	RETURN_IF_FALSE((intp)index < itemCount - 1);

	//remove item in middle
	TableBoxItem& itemRemoved = mItems[index];
	RecycleItemNode(itemRemoved);

	auto newBoundingBox = CalculateTotalBoundingBox();
	auto deltaSize = newBoundingBox.Size - mScrollModel->CurrentWindow().Size;
	mScrollModel->UpdateWindow(deltaSize);
	mItems.RemoveAt(index);
	--itemCount;

	//update next items' bounding box
	FOR_EACH_INT_BEGIN_END(i, (intp)index, (intp)itemCount - 1)
	{
		TableBoxItem& item = mItems[i];
		item.Initialzie(this, i, mResultItemFixedSize);
	}

	FOR_EACH_INT_BEGIN_END(i, (intp)index, (intp)itemCount - 1)
	{
		TableBoxItem& item = mItems[i];
		BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
	}
}

void TableBox::OnItemUpdated(size_t index)
{
	mScrollModel->ApplyMovement();
	//size not changed
	TableBoxItem& updatedItem = mItems[index];
	TryLoadOrRecycleItem(updatedItem, true);

}

void TableBox::LoadItemNode(TableBoxItem& item, bool forceReload /*= false*/, bool forceApplyMovement /*= false*/)
{
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	int newType = listDataBinding->GetTemplateTag(item.Index);
	if (item.Tag != newType)
	{
		RecycleItemNode(item);
		forceApplyMovement = true;
	}
	bool isArrange = false;

	if (item.Node == nullptr)
	{
		if (mCacheEnabed)
		{
			Queue<INode*>* nodeQueue = nullptr;
			if (!listDataBinding->HasMultipleTag())
			{
				nodeQueue = &mSingleTypeItemCache;
			}
			else
			{
				nodeQueue = mMultipleTypeItemCache.GetOptional(item.Tag, nullptr);
			}

			if (nodeQueue != nullptr && !nodeQueue->IsEmpty())
			{
				item.Node = nodeQueue->Head();
				nodeQueue->Pop();
				mValidRange.Expand(item.Index);
			}
		}

		if (item.Node == nullptr)
		{
			item.Node = listDataBinding->Load(item.Index, mResultItemFixedSize);
		}

		AddChild(item.Node);
		mValidRange.Expand(item.Index);
		isArrange = true;

	}
	else if (forceReload)
	{
		listDataBinding->Load(item.Index, mResultItemFixedSize, item.Node);
		isArrange = true;
	}

	if (isArrange)
	{
		item.ArrangeNode(mScrollModel->Offset());
	}
	else if (forceApplyMovement)
	{
		item.ApplyMovement(mScrollModel->Offset());
	}
}



void TableBox::RecycleItemNode(TableBoxItem& item)
{
	RETURN_IF_NULL(item.Node);
	if (mValidRange.Min == (int)item.Index)
	{
		++mValidRange.Min;
	}
	else if (mValidRange.Max == (int)item.Index)
	{
		--mValidRange.Max;
	}

	if (mCacheEnabed)
	{
		RemoveChild(item.Node);
		BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
		Queue<INode*>* nodeQueue = nullptr;
		if (!listDataBinding->HasMultipleTag())
		{
			nodeQueue = &mSingleTypeItemCache;
		}
		else
		{
			nodeQueue = mMultipleTypeItemCache.GetOptional(item.Tag, nullptr);
			if (nodeQueue == nullptr)
			{
				nodeQueue = new Queue<INode*>();
				mMultipleTypeItemCache.Add(item.Tag, nodeQueue);
			}
		}

		nodeQueue->Push(item.Node);
	}
	else
	{
		DeleteChild(item.Node);
	}

	item.Node = nullptr;

}

bool TableBox::TryLoadOrRecycleItem(TableBoxItem& item, bool forceReload /*= false*/, bool forceApplyMovement /*= false*/)
{
	if (mScrollModel->IsRectVisible(item.BoundingBox))
	{
		LoadItemNode(item, forceReload, forceApplyMovement);
		return true;
	}
	else
	{
		RecycleItemNode(item);
		return false;
	}
}


void TableBox::OnBeforeMeasure(const Size2F& availableSize)
{
	ScrollPanel::OnBeforeMeasure(availableSize);

	RETURN_IF_NOT_EQUAL(mStretch, Stretch::None);
	RETURN_IF_EQUAL(mSizeToContent, SizeToContent::None);
	RETURN_IF_EQUAL(mSizeToContent, SizeToContent::Mesh);

	//create new items
	auto totalBoundingBox = CalculateTotalBoundingBox();

	switch (mSizeToContent)
	{
	case SizeToContent::Width:
		SetWidth(totalBoundingBox.Size.Width);
		break;
	case SizeToContent::Height:
		SetHeight(totalBoundingBox.Size.Height);
		break;
	case SizeToContent::WidthAndHeight:
		SetSize(totalBoundingBox.Size);
		break;
	default:
		break;
	}

}

void TableBox::OnMoveChildren()
{
	mScrollModel->ApplyMovement();
	for (auto& item : mItems)
	{
		TryLoadOrRecycleItem(item, false, true);
	}

}


void TableBox::OnSwipeBegin(INode* sender, SwipeBeginGestureEventArg& e)
{
	ScrollPanel::OnSwipeBegin(sender, e);

	SwipeGestureRecognizer* recognizer = (SwipeGestureRecognizer*)e.Recognizer;
	const Point2F& pos = recognizer->BeginPos();
	Point2F modelPos = mScrollModel->ConvertToWindowSpace(pos);
	mSelectedItem = GetSelectedItem(modelPos);
	if (mSelectedItem != nullptr)
	{
		OnItemSelected(*this, *mSelectedItem);
	}

}

void TableBox::OnSwipeMoved(INode* sender, SwipeMovedGestureEventArg& e)
{
	ScrollPanel::OnSwipeMoved(sender, e);

	if (mSelectedItem != nullptr)
	{
		OnItemUnselected(*this, *mSelectedItem);
		mSelectedItem = nullptr;
	}
}

void TableBox::OnSwipeFailed(INode* sender, SwipeFailedGestureEventArg& e)
{
	ScrollPanel::OnSwipeFailed(sender, e);

	if (mSelectedItem != nullptr)
	{
		OnItemUnselected(*this, *mSelectedItem);
		mSelectedItem = nullptr;
	}

	if (e.Recognizer->State() == InputState::End)
	{
		SwipeGestureRecognizer* recognizer = (SwipeGestureRecognizer*)e.Recognizer;
		const Point2F& pos = recognizer->CurPos();
		Point2F modelPos = mScrollModel->ConvertToWindowSpace(pos);
		const TableBoxItem* item = GetSelectedItem(modelPos);
		if (item != nullptr)
		{
			OnItemClicked(*this, *item);
		}
	}



}

void TableBox::OnSwipeSuccess(INode* sender, SwipeSuccessGestureEventArg& e)
{
	ScrollPanel::OnSwipeSuccess(sender, e);

	if (mSelectedItem != nullptr)
	{
		OnItemUnselected(*this, *mSelectedItem);
		mSelectedItem = nullptr;
	}
}
Size2F TableBox::GetItemLimitSize()const
{
	Size2F size = mSize.To2D();
	if (IsVertical())
	{
		size.Height = 0.f;
	}
	else
	{
		size.Width = 0.f;
	}
	return size;
}



Size2F TableBox::CalculateBoundingBoxSize(size_t index) const
{
	return mResultItemFixedSize;
}

void TableBox::ScrollToIndex(uint index)
{
	const TableBoxItem& item = mItems[index];
	if (IsVertical())
	{
		Point2F offset(item.BoundingBox.Origin.X, mSize.Height - (item.BoundingBox.Origin.Y + item.BoundingBox.Size.Height));
		ScrollTo(offset);
	}
	else
	{
		ScrollTo(item.BoundingBox.Origin);
	}
}

void TableBox::ScrollByIndex(int index)
{
	RETURN_IF_ZERO(index);
	RETURN_IF_EMPTY(mItems);
	uint currentIndex = CurrentIndex();

	if (index > 0)
	{
		currentIndex += index;
		currentIndex = Math::Min(currentIndex, (uint)mItems.Count() - 1);
		ScrollToIndex(currentIndex);
	}
	else
	{
		index += currentIndex;
		if (index < 0)
		{
			index = 0;
		}
		ScrollToIndex(index);
	}
}

uint TableBox::CurrentIndex() const
{
	return mValidRange.Min;
}

INode* TableBox::GetNodeByIndex(uint index) const
{
	return mItems[index].Node;
}

const TableBoxItem* TableBox::GetSelectedItem(Point2F pos) const
{
	FOR_EACH_INT_BEGIN_END(i, mValidRange.Min, mValidRange.Max)
	{
		auto& item = mItems[i];

		if (item.Node != nullptr&&item.BoundingBox.Contains(pos))
		{
			if (item.Node->HitTestParent(pos))
			{
				return &item;
			}
		}

	}

	return nullptr;
}



void TableBox::SetupItems()
{
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	size_t count = listDataBinding->Count();
	Rect2F targetBoundingBox = CalculateTotalBoundingBox();
	FOR_EACH_SIZE(i, count)
	{
		TableBoxItem& item = mItems[i];
		item.Initialzie(this, i, mResultItemFixedSize);
	}

	mScrollModel->Initialize(mSize.To2D(), targetBoundingBox);
}

MEDUSA_IMPLEMENT_NODE(TableBox);

MEDUSA_END;
