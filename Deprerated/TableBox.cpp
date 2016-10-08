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
	mCacheEnabed(false)
{
	SetSizeToContent(SizeToContent::WidthAndHeight);
	Log::AssertFormat(!direction.IsFreeOrNone(), "TableBox only support one-way scroll");

	MutableInput().Enable(true);

}

TableBox::TableBox(StringRef name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:ScrollPanel(name, e)
{
	SetSizeToContent(SizeToContent::WidthAndHeight);
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
	listDataBinding->OnItemAdded += Bind(&TableBox::OnItemAdded, this);
	listDataBinding->OnItemRemoved += Bind(&TableBox::OnItemRemoved, this);
	listDataBinding->OnItemUpdated += Bind(&TableBox::OnItemUpdated, this);
	listDataBinding->OnTotalChanged += Bind(&TableBox::OnTotalChanged, this);

	OnTotalChanged();
	return true;
}


bool TableBox::IsSensitiveToChildLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)
{
	return false;
}

bool TableBox::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	static bool isDebug = false;
	if (isDebug)
	{
		return true;
	}
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
		Rect2F targetBoundingBox = Rect2F::Zero;
		RETURN_TRUE_IF_ZERO(itemCount);
		//at this point, self size is changed

		if (IsVertical())
		{
			targetBoundingBox.Size.Width = mSize.Width;
			float origin = mSize.Height;

			Size2F limitSize = mSize.To2D();
			limitSize.Height = 0.f;

			FOR_EACH_SIZE(i, itemCount)
			{
				TableBoxItem& item = mItems[i];

				origin -= item.BoundingBox.Size.Height;
				item.Position.Y = origin;
				targetBoundingBox.Size.Height += item.BoundingBox.Size.Height;

			}
			targetBoundingBox.Origin.Y = origin;
		}
		else
		{
			Size2F limitSize = mSize.To2D();
			limitSize.Width = 0.f;

			targetBoundingBox.Size.Height = mSize.Height;
			float origin = 0.f;
			FOR_EACH_SIZE(i, itemCount)
			{
				TableBoxItem& item = mItems[i];
				item.Position.X = origin;

				targetBoundingBox.Size.Width += item.BoundingBox.Size.Width;
				origin += item.BoundingBox.Size.Width;
			}
		}

		mScrollModel->Initialize(mSize.To2D(), targetBoundingBox);
		mScrollModel->ScrollBy(totalMovment);

		//check items
		FOR_EACH_SIZE(i, itemCount)
		{
			TableBoxItem& item = mItems[i];

			if (mScrollModel->IsRectVisible(item.BoundingBox))
			{
				if (item.Node == nullptr)
				{
					CreateItemNode(item);
				}
				else
				{
					ReloadItemNode(item);
				}
			}
			else
			{
				if (item.Node != nullptr)
				{
					RecycleItemNode(item);
				}
				item.Node = nullptr;
			}

			if (item.Node != nullptr)
			{
				item.ArrangeNode(totalMovment, arrangeFlags);
			}
		}

	}

	UpdateScrollStatus();
	return true;
}


void TableBox::OnItemAdded(size_t index)
{
	mScrollModel->ApplyMovement();

	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;

	size_t itemCount = mItems.Count();
	if (index < itemCount)
	{
		//insert
		TableBoxItem newItem;
		newItem.Index = index;
		newItem.Tag = listDataBinding->GetTemplateTag(index);
		newItem.Position = mItems[index].Position;

		mItems.Insert(index, newItem);

		//update next items' bounding box
		Point2F totalMovemnt = mScrollModel->Offset();

		if (IsVertical())
		{
			FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
			{
				TableBoxItem& item = mItems[i];
				++item.Index;
				item.Position.Y -= newItem.BoundingBox.Size.Height;

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node = nullptr;
				}

				item.ApplyMovement(totalMovemnt);
			}
		}
		else
		{
			FOR_EACH_UINT_BEGIN_END(i, index + 1, itemCount - 1)
			{
				TableBoxItem& item = mItems[i];
				++item.Index;
				item.Position.X += newItem.BoundingBox.Size.Width;
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node = nullptr;
				}
				item.ApplyMovement(totalMovemnt);
			}
		}

		mScrollModel->UpdateWindow(newItem.BoundingBox.Size);

		if (mScrollModel->IsRectVisible(newItem.BoundingBox))
		{
			CreateItemNode(newItem);
		}

	}
	else
	{
		//append
		TableBoxItem& newItem = mItems.NewAdd();
		newItem.Index = index;
		newItem.Tag = listDataBinding->GetTemplateTag(index);
		newItem.Position = mItems[index - 1].Position;

		if (IsVertical())
		{
			newItem.Position.Y -= newItem.BoundingBox.Size.Height;
		}
		else
		{
			newItem.Position.X += newItem.BoundingBox.Size.Width;
		}

		mScrollModel->UpdateWindow(newItem.BoundingBox.Size);

		if (mScrollModel->IsRectVisible(newItem.BoundingBox))
		{
			CreateItemNode(newItem);
		}

	}


}

void TableBox::OnItemRemoved(size_t index)
{
	mScrollModel->ApplyMovement();

	size_t itemCount = mItems.Count();
	RETURN_IF_FALSE(index < itemCount);
	if (index < itemCount - 1)
	{
		//remove item in middle
		TableBoxItem& itemRemoved = mItems[index];
		mScrollModel->UpdateWindow(-itemRemoved.BoundingBox.Size);


		//update next items' bounding box
		Point2F totalMovemnt = mScrollModel->Offset();

		if (IsVertical())
		{
			FOR_EACH_UINT_BEGIN_END(i, index, itemCount - 1)
			{
				TableBoxItem& item = mItems[i];
				--item.Index;
				item.Position.Y += itemRemoved.BoundingBox.Size.Height;
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node = nullptr;
				}

				item.ApplyMovement(totalMovemnt);
			}
		}
		else
		{
			FOR_EACH_UINT_BEGIN_END(i, index, itemCount - 1)
			{
				TableBoxItem& item = mItems[i];
				--item.Index;
				item.Position.X -= itemRemoved.BoundingBox.Size.Width;
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node = nullptr;
				}

				item.ApplyMovement(totalMovemnt);
			}
		}

		RecycleItemNode(itemRemoved);
		mItems.RemoveAt(index);
	}
	else
	{
		//remove the last
		TableBoxItem& itemRemoved = mItems[index];
		mScrollModel->UpdateWindow(-itemRemoved.BoundingBox.Size);

		RecycleItemNode(itemRemoved);
		mItems.RemoveAt(index);

	}


}

void TableBox::OnItemUpdated(size_t index, size_t length)
{
	mScrollModel->ApplyMovement();
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;

	size_t newCount = listDataBinding->Count();
	size_t itemCount = mItems.Count();
	if (itemCount != newCount)
	{
		if (itemCount == 0 || newCount == 0)
		{
			OnTotalChanged();
			return;
		}
	}

	//reload updated item
	if (index + length <= itemCount)
	{

		if (IsVertical())
		{
			TableBoxItem& beginItem = mItems[index];
			float origin = beginItem.Position.Y;
			origin += beginItem.BoundingBox.Size.Height;	//get prev origin
			Size2F deltaSize = Size2F::Zero;

			FOR_EACH_SIZE_BEGIN_END(i, index, index + length - 1)
			{
				TableBoxItem& item = mItems[i];
				Size2F originalSize = item.BoundingBox.Size;

				origin -= item.BoundingBox.Size.Height;
				item.Position.Y = origin;

				Size2F sizeChanged = item.BoundingBox.Size - originalSize;
				deltaSize += sizeChanged;
				mScrollModel->UpdateWindow(sizeChanged);

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
					else
					{
						ReloadItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node = nullptr;
				}

			}


			Point2F totalMovemnt = mScrollModel->Offset();
			//update next items pos
			FOR_EACH_UINT_BEGIN_END(i, index + length, itemCount - 1)
			{
				TableBoxItem& item = mItems[i];
				item.Position.X -= deltaSize.Width;
				item.Position.Y -= deltaSize.Height;

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
				}

				item.ApplyMovement(totalMovemnt);
			}

			AssertValid();
		}
		else
		{
			TableBoxItem& beginItem = mItems[index];
			float origin = beginItem.Position.X;
			origin -= beginItem.BoundingBox.Size.Width;	//get prev origin
			Size2F deltaSize = Size2F::Zero;


			FOR_EACH_SIZE_BEGIN_END(i, index, index + length - 1)
			{
				TableBoxItem& item = mItems[i];
				Size2F originalSize = item.BoundingBox.Size;

				origin += item.BoundingBox.Size.Width;
				item.Position.X = origin;

				Size2F sizeChanged = item.BoundingBox.Size - originalSize;
				deltaSize += sizeChanged;
				mScrollModel->UpdateWindow(sizeChanged);

				ReloadItemNode(item);
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
					else
					{
						ReloadItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node = nullptr;
				}
			}

			Point2F totalMovemnt = mScrollModel->Offset();
			//update next items pos
			FOR_EACH_UINT_BEGIN_END(i, index + length, itemCount - 1)
			{
				TableBoxItem& item = mItems[i];
				item.Position.X += deltaSize.Width;
				item.Position.Y += deltaSize.Height;

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node == nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node != nullptr)
					{
						RecycleItemNode(item);
					}
				}

				item.ApplyMovement(totalMovemnt);
			}

			AssertValid();
		}
	}

	//remove items
	if (newCount < itemCount)
	{
		FOR_EACH_SIZE_BEGIN_END(i, newCount - 1, itemCount - 1)
		{
			//remove the last
			TableBoxItem& itemRemoved = mItems[i];
			mScrollModel->UpdateWindow(-itemRemoved.BoundingBox.Size);

			RecycleItemNode(itemRemoved);
			mItems.RemoveAt(i);
			Log::FormatInfo("Reload remove:{}", (int)i);
		}
	}
	else if (newCount > itemCount)
	{
		//or add new items
		FOR_EACH_SIZE_BEGIN_END(i, itemCount - 1, newCount - 1)
		{
			TableBoxItem& newItem = mItems.NewAdd();
			newItem.Index = (uint)i;
			newItem.Tag = listDataBinding->GetTemplateTag((uint)i);
			newItem.Position = mItems[i - 1].Position;

			if (IsVertical())
			{
				newItem.Position.Y -= newItem.BoundingBox.Size.Height;
			}
			else
			{
				newItem.Position.X += newItem.BoundingBox.Size.Width;
			}

			mScrollModel->UpdateWindow(newItem.BoundingBox.Size);
			CreateItemNode(newItem);
			Log::FormatInfo("Reload create:{}", (uint)i);

		}
	}
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

	//create new items
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	if (!mItemFixedSize.IsNearlyZero())
	{
		mResultItemFixedSize = mItemFixedSize;
	}
	else
	{
		mResultItemFixedSize = listDataBinding->Measure(0, GetItemLimitSize());	//get item fixed size
	}

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
			TableBoxItem& item = mItems.NewAdd();

			item.Index = (uint)i;
			origin -= item.BoundingBox.Size.Height;

			item.Position.Y = origin;

			item.Tag = listDataBinding->GetTemplateTag((uint)i);
			item.Node = nullptr;

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
			TableBoxItem& item = mItems.NewAdd();
			item.Index = (uint)i;
			item.Position.X = origin;

			item.Tag = listDataBinding->GetTemplateTag((uint)i);
			item.Node = nullptr;

			targetBoundingBox.Size.Width += item.BoundingBox.Size.Width;
			origin += item.BoundingBox.Size.Width;
		}
	}


	mScrollModel->Initialize(mSize.To2D(), targetBoundingBox);

	//load nodes for items
	for (auto& item : mItems)
	{
		if (mScrollModel->IsRectVisible(item.BoundingBox))
		{
			if (item.Node == nullptr)
			{
				CreateItemNode(item);
			}
		}
		else
		{
			if (item.Node != nullptr)
			{
				RecycleItemNode(item);
			}
		}
	}
}

void TableBox::RecycleItemNode(TableBoxItem& item)
{
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

void TableBox::CreateItemNode(TableBoxItem& item)
{
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;

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
		}
	}



	if (item.Node == nullptr)
	{
		item.Node = listDataBinding->Load(item.Index, mResultItemFixedSize);
		item.Node->EnableLayout(false);
	}
	else
	{
		listDataBinding->Load(item.Index, mResultItemFixedSize, item.Node);
	}

	AddChild(item.Node);
	item.ArrangeNode(mResultItemFixedSize, mScrollModel->Offset());
}


void TableBox::ReloadItemNode(TableBoxItem& item)
{
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	int newType = listDataBinding->GetTemplateTag(item.Index);
	if (item.Tag == newType)
	{
		if (item.Node == nullptr)
		{
			item.Node = listDataBinding->Load(item.Index, mResultItemFixedSize);
			AddChild(item.Node);
		}
		else
		{
			listDataBinding->Load(item.Index, mResultItemFixedSize, item.Node);
		}

		item.ArrangeNode(mResultItemFixedSize, mScrollModel->Offset());

	}
	else
	{
		RecycleItemNode(item);
		CreateItemNode(item);
	}

}

void TableBox::OnBeforeMeasure(const Size2F& availableSize)
{
	ScrollPanel::OnBeforeMeasure(availableSize);

	RETURN_IF_NOT_EQUAL(mStretch, Stretch::None);
	RETURN_IF_EQUAL(mSizeToContent, SizeToContent::None);
	RETURN_IF_EQUAL(mSizeToContent, SizeToContent::Mesh);

	//create new items
	BaseListDataBinding* listDataBinding = (BaseListDataBinding*)mBinding;
	size_t count = listDataBinding->Count();
	Size2F targetBoundingBox = Size2F::Zero;
	if (IsVertical())
	{
		uint columnCount = (uint)Math::Floor(mSize.Width / mResultItemFixedSize.Width);
		int rowCount= count / columnCount +1;
		targetBoundingBox.Width = columnCount*mResultItemFixedSize.Width;	//align to item size
		targetBoundingBox.Height = rowCount*mResultItemFixedSize.Height;
	}
	else
	{
		uint rowCount = (uint)Math::Floor(mSize.Height / mResultItemFixedSize.Height);
		int columnCount = count / rowCount + 1;
		targetBoundingBox.Width = columnCount*mResultItemFixedSize.Width;	//align to item size
		targetBoundingBox.Height = rowCount*mResultItemFixedSize.Height;
	}

	switch (mSizeToContent)
	{
	case SizeToContent::Width:
		SetWidth(targetBoundingBox.Width);
		break;
	case SizeToContent::Height:
		SetHeight(targetBoundingBox.Height);
		break;
	case SizeToContent::WidthAndHeight:
		SetSize(targetBoundingBox);
		break;
	default:
		break;
	}

}

void TableBox::OnMoveChildren()
{
	mScrollModel->ApplyMovement();
	Point2F totalMovement = mScrollModel->Offset();

	for (auto& item : mItems)
	{
		if (mScrollModel->IsRectVisible(Rect2F(item.Position,mResultItemFixedSize)))
		{
			if (item.Node == nullptr)
			{
				CreateItemNode(item);
			}
		}
		else
		{
			if (item.Node != nullptr)
			{
				RecycleItemNode(item);
			}
		}

		item.ApplyMovement(totalMovement);

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


bool TableBox::AssertValid() const
{
#ifdef MEDUSA_SAFE_CHECK
	Point3F totalMovement = mScrollModel->Offset();
	float origin = mSize.Height;
	size_t count = mItems.Count();
	FOR_EACH_SIZE(i, count)
	{
		const TableBoxItem& item = mItems[i];
		origin -= item.BoundingBox.Size.Height;

		if (!Math::IsEqual(item.Position.Y, origin))
		{
			Log::AssertFailedFormat("Error");
			return false;
		}

		if (item.Node != nullptr)
		{
			Point3F pos = item.Node->Position();
			pos -= totalMovement;
			pos.Y -= origin;
			if (pos != Point3F::Zero)
			{
				Log::AssertFailedFormat("Error");
				return false;
			}
		}
	}
#endif

	return true;


}


void TableBox::ScrollToIndex(uint index)
{
	const TableBoxItem& item = mItems[index];
	if (IsVertical())
	{
		Point2F offset(item.Position.X, mSize.Height - (item.Position.Y + mItemFixedSize.Height));
		ScrollTo(offset);
	}
	else
	{
		ScrollTo(item.Position);
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
	//not often used, and item's count is usually not big, so the perf is ok.
	//to maintain a index var is improving a lot complexity.
	 mScrollModel->OffsetY();


	size_t count = mItems.Count();
	FOR_EACH_SIZE(i, count)
	{
		if (mItems[i].Node != nullptr)
		{
			return (uint)i;
		}
	}
	return 0;
}

INode* TableBox::GetNodeByIndex(uint index) const
{
	return mItems[index].Node;
}

const TableBoxItem* TableBox::GetSelectedItem(Point2F pos) const
{
	int column = (int)Math::Floor(pos.X / mResultItemFixedSize.Width);
	int row = (int)Math::Floor((mSize.Height - pos.Y) / mResultItemFixedSize.Height);
	uint columnCount = (uint)Math::Floor(mSize.Width / mResultItemFixedSize.Width);
	int index = row*columnCount + column;
	if (index < mItems.Count())
	{
		return &mItems[index];
	}

	return nullptr;
}
MEDUSA_IMPLEMENT_NODE(TableBox);

MEDUSA_END;
