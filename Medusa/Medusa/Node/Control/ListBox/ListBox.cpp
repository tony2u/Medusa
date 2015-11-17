// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ListBox.h"
#include "Node/DataSource/IListDataSource.h"
#include "Core/Math/Model/IScrollMathModel.h"
#include "Core/Log/Log.h"
#include "Node/Input/Gesture/SwipeGestureRecognizer.h"
#include "Node/Input/Gesture/EventArg/SwipeBeginGestureEventArg.h"
#include "Node/Input/Gesture/EventArg/SwipeFailedGestureEventArg.h"


MEDUSA_BEGIN;


ListBox::ListBox(StringRef name/*=StringRef::Empty*/, ScrollDirection direction /*= ScrollDirection::VerticalFromTop*/)
	:ScrollPanel(name,direction),mSelectedItem(nullptr),
	mCacheEnabed(false)
{
	SetSizeToContent(SizeToContent::WidthAndHeight);
	Log::AssertFormat(!direction.IsFreeOrNone(),"ListBox only support one-way scroll");
}

ListBox::~ListBox( void )
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
	FOR_EACH_COLLECTION(i,mMultipleTypeItemCache)
	{
		Queue<INode*>* nodes=i->Value;
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


void ListBox::SetDataSource(IDataSource* dataSource)
{
	Log::AssertFormat(dataSource->IsA<IListDataSource>(),"ListBox only support DataSource inherit from IListDataSource.");

	RETURN_IF_EQUAL(mDataSource,dataSource);

	ClearCache();
	Clear();
	mItems.Clear();

	SAFE_ASSIGN_REF(mDataSource,dataSource);

	IListDataSource* listDataSource=(IListDataSource*)dataSource;
	listDataSource->OnItemAdded+=Bind(&ListBox::OnItemAdded,this);
	listDataSource->OnItemRemoved+=Bind(&ListBox::OnItemRemoved, this);
	listDataSource->OnItemUpdated+=Bind(&ListBox::OnItemUpdated, this);
	listDataSource->OnDataChanged+=Bind(&ListBox::OnDataChanged, this);

	if (mParent!=nullptr)
	{
		OnDataChanged(*mDataSource);
	}
}

bool ListBox::IsSensitiveToChildLayoutChanged(const ILayoutable& sender,NodeLayoutChangedFlags changedFlag)
{
	return false;
}

bool ListBox::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/,NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	static bool isDebug = false;
	if (isDebug)
	{
		return true;
	}
	RETURN_TRUE_IF_NULL(mDataSource);
	IListDataSource* listDataSource=(IListDataSource*)mDataSource;
	size_t itemCount=listDataSource->Count();

	if (mItems.IsEmpty()&&itemCount!=0)
	{
		OnDataChanged(*mDataSource);
	}
	else
	{

		Point2F totalMovment=mScrollModel->Offset();
		Rect2F targetBoundingBox=Rect2F::Zero;
		RETURN_TRUE_IF_ZERO(itemCount);
		//at this point, self size is changed

		if(IsVertical())
		{
			targetBoundingBox.Size.Width=mSize.Width;
			float origin=mSize.Height;

			Size2F limitSize=mSize.To2D();
			limitSize.Height=0.f;

			FOR_EACH_SIZE(i,itemCount)
			{
				ListBoxItem& item=mItems[i];

				item.BoundingBox.Size=CalculateBoundingBoxSize((uint)i);
				origin-=item.BoundingBox.Size.Height;
				item.BoundingBox.Origin.Y=origin;
				targetBoundingBox.Size.Height+=item.BoundingBox.Size.Height;

			}

			targetBoundingBox.Origin.Y=origin;
		}
		else
		{
			Size2F limitSize=mSize.To2D();
			limitSize.Width=0.f;

			targetBoundingBox.Size.Height=mSize.Height;
			float origin=0.f;
			FOR_EACH_SIZE(i,itemCount)
			{
				ListBoxItem& item=mItems[i];
				item.BoundingBox.Size=CalculateBoundingBoxSize((uint)i);
				item.BoundingBox.Origin.X=origin;

				targetBoundingBox.Size.Width+=item.BoundingBox.Size.Width;
				origin+=item.BoundingBox.Size.Width;
			}
		}

		mScrollModel->Initialize(mSize.To2D(),targetBoundingBox);
		mScrollModel->ScrollBy(totalMovment);

		//check items
		FOR_EACH_SIZE(i,itemCount)
		{
			ListBoxItem& item=mItems[i];

			if (mScrollModel->IsRectVisible(item.BoundingBox))
			{
				if (item.Node==nullptr)
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
				if (item.Node!=nullptr)
				{
					RecycleItemNode(item);
				}
				item.Node=nullptr;
			}

			if (item.Node!=nullptr)
			{
				item.ArrangeNode(totalMovment,arrangeFlags);
			}
		}

	}

	UpdateScrollStatus();
	return true;
}


void ListBox::OnItemAdded(size_t index)
{
	mScrollModel->ApplyMovement();

	IListDataSource* listDataSource=(IListDataSource*)mDataSource;

	size_t itemCount=mItems.Count();
	if(index<itemCount)
	{
		//insert
		ListBoxItem newItem;
		newItem.Index=index;
		newItem.Type=listDataSource->GetItemType(index);
		newItem.BoundingBox.Size=CalculateBoundingBoxSize(index);
		newItem.BoundingBox.Origin=mItems[index].BoundingBox.Origin;

		mItems.Insert(index,newItem);

		//update next items' bounding box
		Point2F totalMovemnt=mScrollModel->Offset();

		if (IsVertical())
		{
			FOR_EACH_UINT_BEGIN_END(i,index+1,itemCount-1)
			{
				ListBoxItem& item=mItems[i];
				++item.Index;
				item.BoundingBox.Origin.Y-=newItem.BoundingBox.Size.Height;

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node!=nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node=nullptr;
				}

				item.ApplyMovement(totalMovemnt);
			}
		}
		else
		{
			FOR_EACH_UINT_BEGIN_END(i,index+1,itemCount-1)
			{
				ListBoxItem& item=mItems[i];
				++item.Index;
				item.BoundingBox.Origin.X+=newItem.BoundingBox.Size.Width;
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node!=nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node=nullptr;
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
		ListBoxItem& newItem=mItems.NewAdd();
		newItem.Index=index;
		newItem.Type=listDataSource->GetItemType(index);
		newItem.BoundingBox.Size=CalculateBoundingBoxSize(index);
		newItem.BoundingBox.Origin=mItems[index-1].BoundingBox.Origin;

		if (IsVertical())
		{
			newItem.BoundingBox.Origin.Y-=newItem.BoundingBox.Size.Height;
		}
		else
		{
			newItem.BoundingBox.Origin.X+=newItem.BoundingBox.Size.Width;
		}

		mScrollModel->UpdateWindow(newItem.BoundingBox.Size);

		if (mScrollModel->IsRectVisible(newItem.BoundingBox))
		{
			CreateItemNode(newItem);
		}

	}


}

void ListBox::OnItemRemoved(size_t index)
{
	mScrollModel->ApplyMovement();

	size_t itemCount=mItems.Count();
	RETURN_IF_FALSE(index<itemCount);
	if (index<itemCount-1)
	{
		//remove item in middle
		ListBoxItem& itemRemoved=mItems[index];
		mScrollModel->UpdateWindow(-itemRemoved.BoundingBox.Size);


		//update next items' bounding box
		Point2F totalMovemnt=mScrollModel->Offset();

		if (IsVertical())
		{
			FOR_EACH_UINT_BEGIN_END(i,index,itemCount-1)
			{
				ListBoxItem& item=mItems[i];
				--item.Index;
				item.BoundingBox.Origin.Y+=itemRemoved.BoundingBox.Size.Height;
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node!=nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node=nullptr;
				}

				item.ApplyMovement(totalMovemnt);
			}
		}
		else
		{
			FOR_EACH_UINT_BEGIN_END(i,index,itemCount-1)
			{
				ListBoxItem& item=mItems[i];
				--item.Index;
				item.BoundingBox.Origin.X-=itemRemoved.BoundingBox.Size.Width;
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node!=nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node=nullptr;
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
		ListBoxItem& itemRemoved=mItems[index];
		mScrollModel->UpdateWindow(-itemRemoved.BoundingBox.Size);

		RecycleItemNode(itemRemoved);
		mItems.RemoveAt(index);

	}


}

void ListBox::OnItemUpdated(size_t index, size_t length)
{
	mScrollModel->ApplyMovement();
	IListDataSource* listDataSource=(IListDataSource*)mDataSource;

	size_t newCount=listDataSource->Count();
	size_t itemCount=mItems.Count();
	if(itemCount!=newCount)
	{
		if (itemCount==0||newCount==0)
		{
			OnDataChanged(*mDataSource);
			return;
		}
	}

	//reload updated item
	if (index+length<=itemCount)
	{

		if (IsVertical())
		{
			ListBoxItem& beginItem=mItems[index];
			float origin=beginItem.BoundingBox.Origin.Y;
			origin+=beginItem.BoundingBox.Size.Height;	//get prev origin
			Size2F deltaSize = Size2F::Zero;

			FOR_EACH_SIZE_BEGIN_END(i,index,index+length-1)
			{
				ListBoxItem& item=mItems[i];
				Size2F originalSize=item.BoundingBox.Size;

				item.BoundingBox.Size=CalculateBoundingBoxSize(index);
				origin-=item.BoundingBox.Size.Height;
				item.BoundingBox.Origin.Y=origin;
				
				Size2F sizeChanged = item.BoundingBox.Size - originalSize;
				deltaSize += sizeChanged;
				mScrollModel->UpdateWindow(sizeChanged);

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
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
					if (item.Node!=nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node=nullptr;
				}

			}


			Point2F totalMovemnt=mScrollModel->Offset();
			//update next items pos
			FOR_EACH_UINT_BEGIN_END(i,index+length,itemCount-1)
			{
				ListBoxItem& item=mItems[i];
				item.BoundingBox.Origin.X -= deltaSize.Width;
				item.BoundingBox.Origin.Y -= deltaSize.Height;

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node!=nullptr)
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
			ListBoxItem& beginItem=mItems[index];
			float origin=beginItem.BoundingBox.Origin.X;
			origin-=beginItem.BoundingBox.Size.Width;	//get prev origin
			Size2F deltaSize = Size2F::Zero;


			FOR_EACH_SIZE_BEGIN_END(i,index,index+length-1)
			{
				ListBoxItem& item=mItems[i];
				Size2F originalSize=item.BoundingBox.Size;

				item.BoundingBox.Size=CalculateBoundingBoxSize(index);
				origin+=item.BoundingBox.Size.Width;
				item.BoundingBox.Origin.X=origin;

				Size2F sizeChanged = item.BoundingBox.Size - originalSize;
				deltaSize += sizeChanged;
				mScrollModel->UpdateWindow(sizeChanged);

				ReloadItemNode(item);
				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
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
					if (item.Node!=nullptr)
					{
						RecycleItemNode(item);
					}
					item.Node=nullptr;
				}
			}

			Point2F totalMovemnt=mScrollModel->Offset();
			//update next items pos
			FOR_EACH_UINT_BEGIN_END(i,index+length,itemCount-1)
			{
				ListBoxItem& item=mItems[i];
				item.BoundingBox.Origin.X += deltaSize.Width;
				item.BoundingBox.Origin.Y += deltaSize.Height;

				if (mScrollModel->IsRectVisible(item.BoundingBox))
				{
					if (item.Node==nullptr)
					{
						CreateItemNode(item);
					}
				}
				else
				{
					if (item.Node!=nullptr)
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
	if (newCount<itemCount)
	{
		FOR_EACH_SIZE_BEGIN_END(i,newCount-1,itemCount-1)
		{
			//remove the last
			ListBoxItem& itemRemoved=mItems[i];
			mScrollModel->UpdateWindow(-itemRemoved.BoundingBox.Size);

			RecycleItemNode(itemRemoved);
			mItems.RemoveAt(i);
			Log::FormatInfo("Reload remove:{}",(int)i);
		}
	}
	else if (newCount>itemCount)
	{
		//or add new items
		FOR_EACH_SIZE_BEGIN_END(i,itemCount-1,newCount-1)
		{
			ListBoxItem& newItem=mItems.NewAdd();
			newItem.Index=(uint)i;
			newItem.Type=listDataSource->GetItemType((uint)i);
			newItem.BoundingBox.Size=CalculateBoundingBoxSize((uint)i);
			newItem.BoundingBox.Origin=mItems[i-1].BoundingBox.Origin;

			if (IsVertical())
			{
				newItem.BoundingBox.Origin.Y-=newItem.BoundingBox.Size.Height;
			}
			else
			{
				newItem.BoundingBox.Origin.X+=newItem.BoundingBox.Size.Width;
			}

			mScrollModel->UpdateWindow(newItem.BoundingBox.Size);
			CreateItemNode(newItem);
			Log::FormatInfo("Reload create:{}",(uint)i);

		}
	}
}

void ListBox::OnDataChanged(const IDataSource& dataSource)
{
	mScrollModel->ApplyMovement();

	//clear current items
	FOR_EACH_COLLECTION(i,mItems)
	{
		ListBoxItem& item=*i;
		if (item.Node!=nullptr)
		{
			RecycleItemNode(item);
		}
	}
	mItems.Clear();

	//create new items
	IListDataSource* listDataSource=(IListDataSource*)mDataSource;
	size_t count=listDataSource->Count();
	Rect2F targetBoundingBox=Rect2F::Zero;
	Size2F limitSize=mSize.To2D();

	if(IsVertical())
	{
		targetBoundingBox.Size.Width=mSize.Width;
		float origin=mSize.Height;
		limitSize.Height=0.f;
		FOR_EACH_SIZE(i,count)
		{
			ListBoxItem& item=mItems.NewAdd();

			item.Index=(uint)i;
			item.BoundingBox.Size=CalculateBoundingBoxSize((uint)i);
			origin-=item.BoundingBox.Size.Height;

			item.BoundingBox.Origin.Y=origin;

			item.Type=listDataSource->GetItemType((uint)i);
			item.Node=nullptr;

			targetBoundingBox.Size.Height+=item.BoundingBox.Size.Height;

		}

		targetBoundingBox.Origin.Y=origin;
	}
	else
	{
		targetBoundingBox.Size.Height=mSize.Height;
		float origin=0.f;
		limitSize.Width=0.f;
		FOR_EACH_SIZE(i,count)
		{
			ListBoxItem& item=mItems.NewAdd();
			item.Index=(uint)i;
			item.BoundingBox.Size=CalculateBoundingBoxSize((uint)i);
			item.BoundingBox.Origin.X=origin;

			item.Type=listDataSource->GetItemType((uint)i);
			item.Node=nullptr;

			targetBoundingBox.Size.Width+=item.BoundingBox.Size.Width;
			origin+=item.BoundingBox.Size.Width;
		}
	}


	mScrollModel->Initialize(mSize.To2D(),targetBoundingBox);

	//load nodes for items
	FOR_EACH_COLLECTION(i,mItems)
	{
		ListBoxItem& item=*i;
		if (mScrollModel->IsRectVisible(item.BoundingBox))
		{
			if (item.Node==nullptr)
			{
				CreateItemNode(item);
			}
		}
		else
		{
			if (item.Node!=nullptr)
			{
				RecycleItemNode(item);
			}
		}
	}
}

void ListBox::RecycleItemNode(ListBoxItem& item)
{
	if (mCacheEnabed)
	{
		RemoveChild(item.Node);

		IListDataSource* listDataSource=(IListDataSource*)mDataSource;
		Queue<INode*>* nodeQueue=nullptr;
		if (listDataSource->IsFixedType())
		{
			nodeQueue=&mSingleTypeItemCache;
		}
		else
		{
			nodeQueue=mMultipleTypeItemCache.TryGetValueWithFailed(item.Type,nullptr);
			if (nodeQueue==nullptr)
			{
				nodeQueue=new Queue<INode*>();
				mMultipleTypeItemCache.Add(item.Type,nodeQueue);
			}
		}

		nodeQueue->Push(item.Node);
	}
	else
	{
		DeleteChild(item.Node);
	}

	item.Node=nullptr;

}

void ListBox::CreateItemNode(ListBoxItem& item)
{
	IListDataSource* listDataSource=(IListDataSource*)mDataSource;

	if (mCacheEnabed)
	{
		Queue<INode*>* nodeQueue=nullptr;
		if (listDataSource->IsFixedType())
		{
			nodeQueue=&mSingleTypeItemCache;
		}
		else
		{
			nodeQueue=mMultipleTypeItemCache.TryGetValueWithFailed(item.Type,nullptr);
		}

		if (nodeQueue!=nullptr&&!nodeQueue->IsEmpty())
		{
			item.Node=nodeQueue->Head();
			nodeQueue->Pop();
		}
	}

	Size2F limitSize=GetItemLimitSize();

	if(item.Node==nullptr)
	{
		item.Node=listDataSource->CreateItem(item.Index,limitSize);
		item.Node->EnableLayout(false);
	}
	else
	{
		listDataSource->ReloadItem(item.Node,item.Index,limitSize);
	}

	AddChild(item.Node);
	item.ArrangeNode(mScrollModel->Offset());
}


void ListBox::ReloadItemNode(ListBoxItem& item)
{
	IListDataSource* listDataSource=(IListDataSource*)mDataSource;
	int newType=listDataSource->GetItemType(item.Index);
	if (item.Type==newType)
	{

		Size2F limitSize=GetItemLimitSize();
		if(item.Node==nullptr)
		{
			item.Node=listDataSource->CreateItem(item.Index,limitSize);
			AddChild(item.Node);
		}
		else
		{
			listDataSource->ReloadItem(item.Node,item.Index,limitSize);
		}

		item.ArrangeNode(mScrollModel->Offset());

	}
	else
	{
		RecycleItemNode(item);
		CreateItemNode(item);
	}

}

void ListBox::OnMoveChildren()
{
	

	mScrollModel->ApplyMovement();
	Point2F totalMovement=mScrollModel->Offset();

	FOR_EACH_COLLECTION(i,mItems)
	{
		ListBoxItem& item=*i;

		if (mScrollModel->IsRectVisible(item.BoundingBox))
		{
			if (item.Node==nullptr)
			{
				CreateItemNode(item);
			}
		}
		else
		{
			if (item.Node!=nullptr)
			{
				RecycleItemNode(item);
			}
		}

		item.ApplyMovement(totalMovement);

	}

}


void ListBox::OnSwipeBegin(INode* sender,SwipeBeginGestureEventArg& e)
{
	ScrollPanel::OnSwipeBegin(sender,e);

	SwipeGestureRecognizer* recognizer=(SwipeGestureRecognizer*)e.Recognizer;
	const Point2F& pos=recognizer->BeginPos();
	Point2F modelPos=mScrollModel->ConvertToWindowSpace(pos);
	mSelectedItem=GetSelectedItem(modelPos);
	if(mSelectedItem!=nullptr)
	{
		OnItemSelected(*this,*mSelectedItem);
	}

}

void ListBox::OnSwipeMoved(INode* sender,SwipeMovedGestureEventArg& e)
{
	ScrollPanel::OnSwipeMoved(sender,e);

	if (mSelectedItem!=nullptr)
	{
		OnItemUnselected(*this,*mSelectedItem);
		mSelectedItem=nullptr;
	}
}

void ListBox::OnSwipeFailed(INode* sender,SwipeFailedGestureEventArg& e)
{
	ScrollPanel::OnSwipeFailed(sender,e);

	if (mSelectedItem!=nullptr)
	{
		OnItemUnselected(*this,*mSelectedItem);
		mSelectedItem=nullptr;
	}

	SwipeGestureRecognizer* recognizer=(SwipeGestureRecognizer*)e.Recognizer;
	const Point2F& pos=recognizer->CurPos();
	Point2F modelPos=mScrollModel->ConvertToWindowSpace(pos);
	const ListBoxItem* item=GetSelectedItem(modelPos);
	if(item!=nullptr)
	{
		OnItemClicked(*this,*item);
	}

}

void ListBox::OnSwipeSuccess(INode* sender,SwipeSuccessGestureEventArg& e)
{
	ScrollPanel::OnSwipeSuccess(sender,e);

	if (mSelectedItem!=nullptr)
	{
		OnItemUnselected(*this,*mSelectedItem);
		mSelectedItem=nullptr;
	}
}
Size2F ListBox::GetItemLimitSize()const
{
	if (IsVertical())
	{
		return msize(mSize.Width,0.f);
	}
	else
	{
		return msize(0.f,mSize.Height);
	}
}

bool ListBox::AssertValid() const
{
#ifdef MEDUSA_SAFE_CHECK
	Point3F totalMovement=mScrollModel->Offset();
	float origin=mSize.Height;
	size_t count=mItems.Count();
	FOR_EACH_SIZE(i,count)
	{
		const ListBoxItem& item=mItems[i];
		origin-=item.BoundingBox.Size.Height;

		if(!Math::IsEqual(item.BoundingBox.Origin.Y,origin))
		{
			Log::AssertFailedFormat("Error");
			return false;
		}

		if (item.Node!=nullptr)
		{
			Point3F pos=item.Node->Position();
			pos-=totalMovement;
			pos.Y-=origin;
			if (pos!=Point3F::Zero)
			{
				Log::AssertFailedFormat("Error");
				return false;
			}
		}
	}
#endif

	return true;

	
}

Size2F ListBox::CalculateBoundingBoxSize(size_t index) const
{
	if (IsVertical())
	{
		IListDataSource* listDataSource=(IListDataSource*)mDataSource;
		Size2F size=listDataSource->CalculateItemSize(index,msize(mSize.Width,0.f));
		size.Width=mSize.Width;
		return size;
	}
	else
	{
		IListDataSource* listDataSource=(IListDataSource*)mDataSource;
		Size2F size=listDataSource->CalculateItemSize(index,msize(0.f,mSize.Height));
		size.Height=mSize.Height;
		return size;
	}
}

void ListBox::ScrollToIndex(uint index)
{
	const ListBoxItem& item=mItems[index];
	if (IsVertical())
	{
		Point2F offset(item.BoundingBox.Origin.X,mSize.Height-(item.BoundingBox.Origin.Y+item.BoundingBox.Size.Height));
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
	uint currentIndex=CurrentIndex();

	if (index>0)
	{
		currentIndex+=index;
		currentIndex=Math::Min(currentIndex,(uint)mItems.Count()-1);
		ScrollToIndex(currentIndex);
	}
	else
	{
		index+=currentIndex;
		if (index<0)
		{
			index=0;
		}
		ScrollToIndex(index);
	}
}

uint ListBox::CurrentIndex() const
{
	//not often used, and item's count is usually not big, so the perf is ok.
	//to maintain a index var is improving a lot complexity.

	size_t count=mItems.Count();
	FOR_EACH_SIZE(i,count)
	{
		if (mItems[i].Node!=nullptr)
		{
			return (uint)i;
		}
	}
	return 0;
}

INode* ListBox::GetNodeByIndex(uint index) const
{
	return mItems[index].Node;
}

const ListBoxItem* ListBox::GetSelectedItem(Point2F pos) const
{
	size_t count=mItems.Count();
	FOR_EACH_SIZE(i,count)
	{
		const ListBoxItem& item=mItems[i];
		if (item.Node!=nullptr&&item.BoundingBox.Contains(pos))
		{
			return &item;
		}
	}

	return nullptr;
}
MEDUSA_IMPLEMENT_RTTI(ListBox, ScrollPanel);

MEDUSA_END;
