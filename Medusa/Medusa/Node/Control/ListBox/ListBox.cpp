// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ListBox.h"
#include "Geometry/Scroll/IScrollMathModel.h"
#include "Core/Log/Log.h"
#include "Node/Input/Gesture/SwipeGestureRecognizer.h"
#include "Node/Input/Gesture/EventArg/SwipeBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeFailedGestureEventArg.h"
#include "Node/Input/InputDispatcher.h"
#include "Node/Binding/BaseListDataBinding.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


ListBox::ListBox(StringRef name, ScrollDirection direction)
	:ScrollPanel(name, direction), mSelectedItem(nullptr),
	mCacheEnabed(false),
	mValidRange(RangeI::Init)
{
	Log::AssertFormat(!direction.IsFreeOrNone(), "ListBox only support one-way scroll");

	MutableInput().Enable(true);

}

ListBox::ListBox(StringRef name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:ScrollPanel(name, e)
{
}

ListBox::~ListBox(void)
{
	ClearCache();
}

bool ListBox::Initialize()
{
	return true;
}

void ListBox::ClearCache()
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


void ListBox::SetScrollDirection(ScrollDirection direction)
{
	Log::AssertFormat(!direction.IsFreeOrNone(), "ListBox only support one-way scroll");
	ScrollPanel::SetScrollDirection(direction);
}


bool ListBox::SetBinding(IDataBinding* val)
{
	RETURN_FALSE_IF_FALSE(INode::SetBinding(val));
	ClearCache();
	Clear();
	mItems.Clear();

	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)val;
	listDataBinding->OnItemAdded += Bind(&ListBox::OnItemAdded, this);
	listDataBinding->OnItemRemoved += Bind(&ListBox::OnItemRemoved, this);
	listDataBinding->OnItemUpdated += Bind(&ListBox::OnItemUpdated, this);
	listDataBinding->OnTotalChanged += Bind(&ListBox::OnTotalChanged, this);
	return true;
}


bool ListBox::IsSensitiveToChildLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)
{
	return false;
}

bool ListBox::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
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
			ListBoxItem& item = mItems[i];
			BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
		}

	}

	UpdateScrollStatus();
	return true;
}


void ListBox::OnTotalChanged()
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
	if (!Math::IsZero(mItemFixedSize))
	{
		mResultItemFixedSize = mItemFixedSize;
	}
	else if (listDataBinding->IsFixedSize())
	{
		if (IsVertical())
		{
			mResultItemFixedSize = listDataBinding->GetFixedSize(GetItemLimitSize()).Height;
		}
		else
		{
			mResultItemFixedSize = listDataBinding->GetFixedSize(GetItemLimitSize()).Width;
		}
	}
	else
	{
		mResultItemFixedSize = 0.f;
	}

	mItems.ForceReserveCount(listDataBinding->Count());
	SetupItems();

	//load nodes for items
	for (auto& item : mItems)
	{
		BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
	}

}

void ListBox::OnItemAdded(size_t index)
{
	mScrollModel->ApplyMovement();
	size_t itemCount = mItems.Count();

	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	ListBoxItem newItem;
	newItem.Index = index;
	newItem.Tag = listDataBinding->GetTemplateTag(index);
	newItem.BoundingBox.Size = CalculateBoundingBoxSize(index);

	Rect2F originBoundingBox = Rect2F::Zero;
	if (index < itemCount)
	{
		ListBoxItem& originItem = mItems[index];
		originBoundingBox = originItem.BoundingBox;
	}
	else
	{
		if (index > 0)
		{
			ListBoxItem& originItem = mItems[index - 1];
			originBoundingBox = originItem.BoundingBox;
		}
	}

	auto deltaSize = newItem.BoundingBox.Size - originBoundingBox.Size;
	if (IsVertical())
	{
		deltaSize.Width = 0.f;
	}
	else
	{
		deltaSize.Height = 0.f;
	}

	newItem.BoundingBox.Origin = originBoundingBox.Origin;
	newItem.BoundingBox.Origin.X += deltaSize.Width;
	newItem.BoundingBox.Origin.Y -= deltaSize.Height;

	TryLoadOrRecycleItem(newItem, true);
	mItems.Insert(index, newItem);
	mScrollModel->UpdateWindow(deltaSize);

	if (index < itemCount)
	{
		//update next items' bounding box
		FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
		{
			ListBoxItem& item = mItems[i];
			++item.Index;
			item.BoundingBox.Origin.X += deltaSize.Width;
			item.BoundingBox.Origin.Y -= deltaSize.Height;
		}

		FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
		{
			ListBoxItem& item = mItems[i];
			BREAK_IF_FALSE(TryLoadOrRecycleItem(item));
		}
	}
	
}

void ListBox::OnItemRemoved(size_t index)
{
	mScrollModel->ApplyMovement();

	intp itemCount = (intp)mItems.Count();
	RETURN_IF_FALSE((intp)index < itemCount - 1);

	//remove item in middle
	ListBoxItem& itemRemoved = mItems[index];
	RecycleItemNode(itemRemoved);
	Size2F deltaSize = itemRemoved.BoundingBox.Size;
	if (IsVertical())
	{
		deltaSize.Width = 0.f;
	}
	else
	{
		deltaSize.Height = 0.f;
	}

	mScrollModel->UpdateWindow(-deltaSize);
	mItems.RemoveAt(index);
	--itemCount;

	//update next items' bounding box
	FOR_EACH_INT_BEGIN_END(i, (intp)index, (intp)itemCount - 1)
	{
		ListBoxItem& item = mItems[i];
		--item.Index;
		item.BoundingBox.Origin.X -= deltaSize.Width;
		item.BoundingBox.Origin.Y += deltaSize.Height;
		TryLoadOrRecycleItem(item);
	}

}

void ListBox::OnItemUpdated(size_t index)
{
	mScrollModel->ApplyMovement();
	size_t itemCount = mItems.Count();

	//reload updated item
	ListBoxItem& updatedItem = mItems[index];
	auto originSize = updatedItem.BoundingBox.Size;
	updatedItem.BoundingBox.Size = CalculateBoundingBoxSize(index);
	Size2F deltaSize = updatedItem.BoundingBox.Size - originSize;
	if (IsVertical())
	{
		deltaSize.Width = 0.f;
	}
	else
	{
		deltaSize.Height = 0.f;
	}


	updatedItem.BoundingBox.Origin.X += deltaSize.Width;
	updatedItem.BoundingBox.Origin.Y -= deltaSize.Height;

	if (!deltaSize.IsNearlyZero())
	{
		mScrollModel->UpdateWindow(deltaSize);
		TryLoadOrRecycleItem(updatedItem, true);

		//update next items pos
		FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
		{
			ListBoxItem& item = mItems[i];
			item.BoundingBox.Origin.X += deltaSize.Width;
			item.BoundingBox.Origin.Y -= deltaSize.Height;
			TryLoadOrRecycleItem(item);
		}
	}
	else
	{
		TryLoadOrRecycleItem(updatedItem, true);
	}

}

void ListBox::LoadItemNode(ListBoxItem& item, bool forceReload /*= false*/, bool forceApplyMovement /*= false*/)
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
			item.Node = listDataBinding->Load(item.Index, GetItemLimitSize());
		}

		AddChild(item.Node);
		mValidRange.Expand(item.Index);
		isArrange = true;
		
	}
	else if (forceReload)
	{
		listDataBinding->Load(item.Index, GetItemLimitSize(), item.Node);
		isArrange = true;
	}

	if (isArrange)
	{
		auto nodeSize = item.Node->Size2D();
		if (IsVertical())
		{
			item.BoundingBox.Size.Height = nodeSize.Height;
		}
		else
		{
			item.BoundingBox.Size.Width = nodeSize.Width;
		}

		item.ArrangeNode(mScrollModel->Offset());
	}
	else if (forceApplyMovement)
	{
		item.ApplyMovement(mScrollModel->Offset());
	}
}



void ListBox::RecycleItemNode(ListBoxItem& item)
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

bool ListBox::TryLoadOrRecycleItem(ListBoxItem& item, bool forceReload /*= false*/, bool forceApplyMovement /*= false*/)
{
	if (mScrollModel->IsRectVisible(item.BoundingBox))
	{
		LoadItemNode(item, forceReload,forceApplyMovement);
		return true;
	}
	else
	{
		RecycleItemNode(item);
		return false;
	}
}


void ListBox::OnBeforeMeasure(const Size2F& availableSize)
{
	ScrollPanel::OnBeforeMeasure(availableSize);

	RETURN_IF_NOT_EQUAL(mStretch, Stretch::None);
	RETURN_IF_EQUAL(mSizeToContent, SizeToContent::None);
	RETURN_IF_EQUAL(mSizeToContent, SizeToContent::Mesh);

	//create new items
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	size_t count = listDataBinding->Count();
	Size2F maxSize = Size2F::Zero;

	if (IsVertical())
	{
		if (!Math::IsZero(mResultItemFixedSize))
		{
			maxSize.Height = mResultItemFixedSize*count;
		}
		else
		{
			FOR_EACH_SIZE(i, count)
			{
				Size2F size = mItems[i].BoundingBox.Size;
				maxSize.Height += size.Height;
				maxSize.Width = Math::Max(maxSize.Width, size.Width);
			}
		}


	}
	else
	{
		if (!Math::IsZero(mResultItemFixedSize))
		{
			maxSize.Width = mResultItemFixedSize*count;
		}
		else
		{
			FOR_EACH_SIZE(i, count)
			{
				Size2F size = mItems[i].BoundingBox.Size;
				maxSize.Width += size.Width;
				maxSize.Height = Math::Max(maxSize.Height, size.Height);
			}
		}
	}


	switch (mSizeToContent)
	{
	case SizeToContent::Width:
		SetWidth(maxSize.Width);
		break;
	case SizeToContent::Height:
		SetHeight(maxSize.Height);
		break;
	case SizeToContent::WidthAndHeight:
		SetSize(maxSize);
		break;
	default:
		break;
	}

}

void ListBox::OnMoveChildren()
{
	mScrollModel->ApplyMovement();
	for (auto& item : mItems)
	{
		TryLoadOrRecycleItem(item,false,true);
	}

}


void ListBox::OnSwipeBegin(INode* sender, SwipeBeginGestureEventArg& e)
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

void ListBox::OnSwipeMoved(INode* sender, SwipeMovedGestureEventArg& e)
{
	ScrollPanel::OnSwipeMoved(sender, e);

	if (mSelectedItem != nullptr)
	{
		OnItemUnselected(*this, *mSelectedItem);
		mSelectedItem = nullptr;
	}
}

void ListBox::OnSwipeFailed(INode* sender, SwipeFailedGestureEventArg& e)
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
		const ListBoxItem* item = GetSelectedItem(modelPos);
		if (item != nullptr)
		{
			OnItemClicked(*this, *item);
		}
	}



}

void ListBox::OnSwipeSuccess(INode* sender, SwipeSuccessGestureEventArg& e)
{
	ScrollPanel::OnSwipeSuccess(sender, e);

	if (mSelectedItem != nullptr)
	{
		OnItemUnselected(*this, *mSelectedItem);
		mSelectedItem = nullptr;
	}
}
Size2F ListBox::GetItemLimitSize()const
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

Size2F ListBox::CalculateBoundingBoxSize(size_t index) const
{
	if (!Math::IsZero(mResultItemFixedSize))
	{
		if (IsVertical())
		{
			return Size2F(mSize.Width, mResultItemFixedSize);
		}
		else
		{
			return Size2F(mResultItemFixedSize, mSize.Height);
		}
	}
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	Size2F resultSize= listDataBinding->Measure(index, GetItemLimitSize());
	if (IsVertical())
	{
		resultSize.Width = mSize.Width;
	}
	else
	{
		resultSize.Height = mSize.Height;
	}
	return resultSize;
}

void ListBox::ScrollToIndex(uint index)
{
	const ListBoxItem& item = mItems[index];
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

void ListBox::ScrollByIndex(int index)
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

uint ListBox::CurrentIndex() const
{
	return mValidRange.Min;
}

INode* ListBox::GetNodeByIndex(uint index) const
{
	return mItems[index].Node;
}

const ListBoxItem* ListBox::GetSelectedItem(Point2F pos) const
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



void ListBox::SetupItems()
{
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	size_t count = listDataBinding->Count();
	Rect2F targetBoundingBox = Rect2F::Zero;
	Size2F limitSize = mSize.To2D();

	if (IsVertical())
	{
		targetBoundingBox.Size.Width = mSize.Width;
		float origin = mSize.Height;
		limitSize.Height = 0.f;
		FOR_EACH_SIZE(i, count)
		{
			ListBoxItem& item = mItems[i];

			item.Index = (uint)i;
			item.BoundingBox.Size = CalculateBoundingBoxSize(i);
			origin -= item.BoundingBox.Size.Height;

			item.BoundingBox.Origin.Y = origin;

			item.Tag = listDataBinding->GetTemplateTag((uint)i);
			targetBoundingBox.Size.Height += item.BoundingBox.Size.Height;

		}

		targetBoundingBox.Origin.Y = origin;
	}
	else
	{
		targetBoundingBox.Size.Height = mSize.Height;
		float origin = 0.f;
		limitSize.Width = 0.f;
		FOR_EACH_SIZE(i, count)
		{
			ListBoxItem& item = mItems[i];
			item.Index = (uint)i;
			item.BoundingBox.Size = CalculateBoundingBoxSize(i);
			item.BoundingBox.Origin.X = origin;

			item.Tag = listDataBinding->GetTemplateTag((uint)i);
			targetBoundingBox.Size.Width += item.BoundingBox.Size.Width;
			origin += item.BoundingBox.Size.Width;
		}
	}


	mScrollModel->Initialize(mSize.To2D(), targetBoundingBox);

	
}

MEDUSA_IMPLEMENT_NODE(ListBox);

MEDUSA_END;
