// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "Node/Panel/ScrollPanel.h"
#include "TableBoxItem.h"
#include "Core/Collection/Queue.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/Event.h"
#include "Node/Binding/TListDataBinding.h"

MEDUSA_BEGIN;

/*
Pull to refresh
auto load on bottom
cache
vary type child
fixed size
*/
class TableBox :public ScrollPanel
{
	MEDUSA_NODE(TableBox, ScrollPanel);
public:
	typedef Delegate<void(TableBox& sender, const TableBoxItem& item)> ItemSelectedDelegate;
	typedef Delegate<void(TableBox& sender, const TableBoxItem& item)> ItemUnselectedDelegate;
	typedef Delegate<void(TableBox& sender, const TableBoxItem& item)> ItemClickedDelegate;

	typedef Event<void(TableBox& sender, const TableBoxItem& item)> ItemSelectedEvent;
	typedef Event<void(TableBox& sender, const TableBoxItem& item)> ItemUnselectedEvent;
	typedef Event<void(TableBox& sender, const TableBoxItem& item)> ItemClickedEvent;

	ItemUnselectedEvent OnItemUnselected;
	ItemSelectedEvent OnItemSelected;
	ItemClickedEvent OnItemClicked;
public:
	TableBox(StringRef name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	TableBox(StringRef name, ScrollDirection direction);
	virtual ~TableBox(void);
	virtual bool Initialize() override;

	Size2F ItemFixedSize() const { return mItemFixedSize; }
	void SetItemFixedSize(Size2F val) { mItemFixedSize = val; }
public:
	virtual void SetScrollDirection(ScrollDirection direction)override;
	virtual bool SetBinding(IDataBinding* val)override;

	virtual void ScrollToIndex(uint index);
	virtual void ScrollByIndex(int index);

	virtual uint CurrentIndex()const;
	INode* GetNodeByIndex(uint index)const;
protected:
	virtual void OnMoveChildren()override;

	virtual bool ArrangeChildren(const Rect2F& limitRect = Rect2F::Zero, NodeLayoutArrangeFlags arrangeFlags = NodeLayoutArrangeFlags::None)override;
	virtual bool IsSensitiveToChildLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)override;

	void OnItemAdded(size_t index);
	void OnItemRemoved(size_t index);
	void OnItemUpdated(size_t index, size_t length);
	void OnTotalChanged();

	virtual void OnSwipeBegin(INode* sender, SwipeBeginGestureEventArg& e)override;
	virtual void OnSwipeMoved(INode* sender, SwipeMovedGestureEventArg& e)override;
	virtual void OnSwipeFailed(INode* sender, SwipeFailedGestureEventArg& e)override;
	virtual void OnSwipeSuccess(INode* sender, SwipeSuccessGestureEventArg& e)override;

protected:
	void RecycleItemNode(TableBoxItem& item);
	void CreateItemNode(TableBoxItem& item);
	void ReloadItemNode(TableBoxItem& item);
protected:
	virtual void OnBeforeMeasure(const Size2F& availableSize)override;
	void ClearCache();
	bool AssertValid()const;
	const TableBoxItem* GetSelectedItem(Point2F pos)const;
protected:
	List<TableBoxItem> mItems;
	const TableBoxItem* mSelectedItem = nullptr;

	Queue<INode*> mSingleTypeItemCache;	//node cache for single type
	Dictionary<uint, Queue<INode*>* > mMultipleTypeItemCache;	//node cache for multiple type
	bool mCacheEnabed = false;

	Size2F mItemFixedSize{ 0.f,0.f };
	Size2F mResultItemFixedSize{ 0.f,0.f };
};

MEDUSA_ENABLE_STATIC_CONSTRUCTOR(TableBox);

MEDUSA_END;
