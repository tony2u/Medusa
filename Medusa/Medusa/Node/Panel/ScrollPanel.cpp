// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ScrollPanel.h"
#include "Node/Input/Gesture/SwipeGestureRecognizer.h"
#include "Node/Input/InputDispatcher.h"
#include "Core/Log/Log.h"
#include "Graphics/ResolutionAdapter.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/Effect/EffectFactory.h"
#include "Resource/ResourceNames.h"
#include "Node/NodeFactory.h"
#include "Node/Action/Basic/FadeBySpeedAction.h"
#include "Core/Math/Model/SpringScrollMathModel.h"

MEDUSA_BEGIN;

ScrollPanel::ScrollPanel(StringRef name/*=StringRef::Empty*/, ScrollDirection direction /*=ScrollDirection::FreeFromCurrent*/)
	:IPanel(name),
	mScrollBarColor(Color4F::Silver)
{
	EnableClipToBound(true);
	mSwipeGestureRecognizer = MutableInput().AddSwipeGestureRecognizer(direction);

	mSwipeGestureRecognizer->OnSwipeBegin += Bind(&ScrollPanel::OnSwipeBegin,this);
	mSwipeGestureRecognizer->OnSwipeMoved += Bind(&ScrollPanel::OnSwipeMoved, this);
	mSwipeGestureRecognizer->OnSwipeFailed += Bind(&ScrollPanel::OnSwipeFailed, this);
	mSwipeGestureRecognizer->OnSwipeSuccess += Bind(&ScrollPanel::OnSwipeSuccess, this);

	mScrollModel = new SpringScrollMathModel(direction);
}

ScrollPanel::~ScrollPanel(void)
{
	SAFE_DELETE(mScrollModel);
}

bool ScrollPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/, NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	FOR_EACH_COLLECTION(i, mNodes)
	{
		INode* child = *i;
		CONTINUE_IF(mManagedNodes.Contains(child));
		child->ArrangeRecursively(limitRect, arrangeFlags);
	}

	OnInitializeTargetBoundingBox();
	UpdateScrollStatus();
	return true;
}

bool ScrollPanel::IsVertical() const
{
	return GetScrollDirection().IsVertical();
}

bool ScrollPanel::IsHorizontal() const
{
	return GetScrollDirection().IsHorizontal();
}


ScrollDirection ScrollPanel::GetScrollDirection() const
{
	return mSwipeGestureRecognizer->Direction();
}


void ScrollPanel::SetScrollDirection(ScrollDirection direction)
{
	RETURN_IF_EQUAL(mSwipeGestureRecognizer->Direction(), direction);
	mSwipeGestureRecognizer->SetDirection(direction);
	mScrollModel->SetDirection(direction);

	UpdateScrollStatus();
}


void ScrollPanel::SetScrollModel(IScrollMathModel* val)
{
	SAFE_ASSIGN(mScrollModel, val);
}

void ScrollPanel::OnSwipeBegin(INode* sender, SwipeBeginGestureEventArg& e)
{
	mScrollModel->Focus();
	UpdateScrollStatus();
}

void ScrollPanel::OnSwipeMoved(INode* sender, SwipeMovedGestureEventArg& e)
{
	Point2F movement = mSwipeGestureRecognizer->MovementOnDirection();
	mScrollModel->StaticScroll(movement);
	OnMoveChildren();

	UpdateScrollStatus();
}

void ScrollPanel::OnSwipeFailed(INode* sender, SwipeFailedGestureEventArg& e)
{
	mScrollModel->Release();
	UpdateScrollStatus();
}

void ScrollPanel::OnSwipeSuccess(INode* sender, SwipeSuccessGestureEventArg& e)
{
	Point2F velocity = mSwipeGestureRecognizer->CurrentVelocityOnDirection();
	mScrollModel->StartScrolling(velocity);
	UpdateScrollStatus();
}

void ScrollPanel::ScrollTo(Point2F offset)
{
	mScrollModel->ScrollTo(offset);
	OnMoveChildren();
	UpdateScrollStatus();
}

void ScrollPanel::ScrollBy(Point2F movement)
{
	mScrollModel->ScrollBy(movement);
	OnMoveChildren();
	UpdateScrollStatus();
}


void ScrollPanel::ScrollToStart()
{
	mScrollModel->ScrollToStart();
	OnMoveChildren();
	UpdateScrollStatus();
}

void ScrollPanel::ScrollToEnd()
{
	mScrollModel->ScrollToEnd();
	OnMoveChildren();
	UpdateScrollStatus();
}

void ScrollPanel::UpdateScrollStatus()
{
	OnUpdateScrollBar();
}


void ScrollPanel::OnMoveChildren()
{
	Point3F movement = mScrollModel->Movement();
	mScrollModel->ApplyMovement();
	FOR_EACH_COLLECTION(i, mNodes)
	{
		INode* child = *i;
		CONTINUE_IF(mManagedNodes.Contains(child));
		child->Move(movement);
	}
}


void ScrollPanel::OnInitializeTargetBoundingBox()
{

	Rect2F targetBoundingBox = Rect2F::Zero;
	if (mNodes.Count() > mManagedNodes.Count())
	{
		//try to optimize this
		FOR_EACH_COLLECTION(i, mNodes)
		{
			INode* child = *i;
			CONTINUE_IF(mManagedNodes.Contains(child));
			Rect2F boundingBox = child->GetBoundingBox().To2D();
			targetBoundingBox.Union(boundingBox);
		}
	}

	mScrollModel->Initialize(mSize.To2D(), targetBoundingBox);
}


void ScrollPanel::OnUpdateScrollBar()
{


	{
		bool isShowHorizontal = false;
		switch (mHorizontalScrollBarVisibility)
		{
			case ScrollBarVisibility::Disabled:
				if (mHorizontalScrollBar != nullptr)
				{
					DeleteChild(mHorizontalScrollBar);
					mHorizontalScrollBar = nullptr;
				}
				break;
			case ScrollBarVisibility::VisibleIfNeed:
			case ScrollBarVisibility::Auto:
				isShowHorizontal = mScrollModel->NeedHorizontalScrollBar();
				if (!isShowHorizontal&&mHorizontalScrollBar != nullptr&&mHorizontalScrollBar->IsVisible())
				{
					mHorizontalScrollBar->StopAllActions();
					mHorizontalScrollBar->SetVisible(false);
				}
				break;
			case ScrollBarVisibility::AlwaysVisible:
				isShowHorizontal = true;
				break;
			default:
				break;
		}

		if (isShowHorizontal)
		{
			float offset = mScrollModel->HorizontalScrollBarOffset();
			float scrollBarWidth = mScrollModel->HorizontalScrollBarWidth();

			if (mHorizontalScrollBar == nullptr)
			{
				mHorizontalScrollBar = (INode*)NodeFactory::Instance().CreateRect( Rect2F(0, 0, 1, mHorizontalScrollBarHeight), mScrollBarColor);
				mHorizontalScrollBar->SetName(MEDUSA_PREFIX(HorizontalScrollBar));
				mHorizontalScrollBar->SetPosition(Point3F::Zero);
				mHorizontalScrollBar->EnableManaged();

				AddChild(mHorizontalScrollBar);
			}


			mHorizontalScrollBar->SetSize(1, mHorizontalScrollBarHeight);
			mHorizontalScrollBar->SetScaleX(scrollBarWidth);
			mHorizontalScrollBar->SetPositionX(offset);
			mHorizontalScrollBar->SetPositionY(0.f);

			if (mVerticalScrollBarVisibility == ScrollBarVisibility::Auto)
			{
				IScrollMathModel::ScrollState state = mScrollModel->State();

				switch (state)
				{
					case IScrollMathModel::ScrollState::None:
						mHorizontalScrollBar->SetOpacity(0.f);
						break;
					case IScrollMathModel::ScrollState::Begin:
						break;
					case IScrollMathModel::ScrollState::StaticScroll:
					case IScrollMathModel::ScrollState::Scrolling:
					case IScrollMathModel::ScrollState::Spring:
						if (Math::IsZero(mHorizontalScrollBar->Opacity()))
						{
							mHorizontalScrollBar->StopAllActions();
							mHorizontalScrollBar->RunAction(new FadeBySpeedAction(mScrollBarOpacityFadeSpeed));
						}
						break;
					case IScrollMathModel::ScrollState::End:
						mHorizontalScrollBar->StopAllActions();
						mHorizontalScrollBar->RunAction(new FadeBySpeedAction(-mScrollBarOpacityFadeSpeed));
						break;
					default:
						break;
				}
			}
		}
	}

	{
		//vertical
		bool isShowVertical = false;
		switch (mVerticalScrollBarVisibility)
		{
			case ScrollBarVisibility::Disabled:
				if (mVerticalScrollBar != nullptr)
				{
					DeleteChild(mVerticalScrollBar);
					mVerticalScrollBar = nullptr;
				}
				break;
			case ScrollBarVisibility::VisibleIfNeed:
			case ScrollBarVisibility::Auto:
				isShowVertical = mScrollModel->NeedVerticalScrollBar();
				if (!isShowVertical&&mVerticalScrollBar != nullptr&&mVerticalScrollBar->IsVisible())
				{
					mVerticalScrollBar->StopAllActions();
					mVerticalScrollBar->SetVisible(false);
				}
				break;
			case ScrollBarVisibility::AlwaysVisible:
				isShowVertical = true;
				break;
			default:
				break;
		}

		if (isShowVertical)
		{
			float offset = mScrollModel->VerticalScrollBarOffset();
			float scrollBarHeight = mScrollModel->VerticalScrollBarHeight();

			if (mVerticalScrollBar == nullptr)
			{
				mVerticalScrollBar = (INode*)NodeFactory::Instance().CreateRect(Rect2F(0, 0, mVerticalScrollBarWidth, 1), mScrollBarColor);
				mVerticalScrollBar->SetName(MEDUSA_PREFIX(VerticalScrollBar));
				mVerticalScrollBar->SetPosition(Point3F::Zero);
				mVerticalScrollBar->SetPositionX(mSize.Width - mVerticalScrollBarWidth);
				mVerticalScrollBar->EnableManaged();

				AddChild(mVerticalScrollBar);
			}


			mVerticalScrollBar->SetSize(mVerticalScrollBarWidth, 1);
			mVerticalScrollBar->SetScaleY(scrollBarHeight);
			mVerticalScrollBar->SetPositionX(mSize.Width - mVerticalScrollBarWidth);
			mVerticalScrollBar->SetPositionY(offset);

			if (mVerticalScrollBarVisibility == ScrollBarVisibility::Auto)
			{
				IScrollMathModel::ScrollState state = mScrollModel->State();

				switch (state)
				{
					case IScrollMathModel::ScrollState::None:
						mVerticalScrollBar->SetOpacity(0.f);
						break;
					case IScrollMathModel::ScrollState::Begin:
						break;
					case IScrollMathModel::ScrollState::StaticScroll:
					case IScrollMathModel::ScrollState::Scrolling:
					case IScrollMathModel::ScrollState::Spring:
						if (Math::IsZero(mVerticalScrollBar->Opacity()))
						{
							mVerticalScrollBar->StopAllActions();
							mVerticalScrollBar->RunAction(new FadeBySpeedAction(mScrollBarOpacityFadeSpeed));
						}
						break;
					case IScrollMathModel::ScrollState::End:
						mVerticalScrollBar->StopAllActions();
						mVerticalScrollBar->RunAction(new FadeBySpeedAction(-mScrollBarOpacityFadeSpeed));
						break;
					default:
						break;
				}
			}

		}

	}


}

void ScrollPanel::SetHorizontalScrollBarVisibility(ScrollBarVisibility val)
{
	RETURN_IF_EQUAL(mHorizontalScrollBarVisibility, val);
	mHorizontalScrollBarVisibility = val;
	OnUpdateScrollBar();
}

void ScrollPanel::SetVerticalScrollBarVisibility(ScrollBarVisibility val)
{
	RETURN_IF_EQUAL(mVerticalScrollBarVisibility, val);
	mVerticalScrollBarVisibility = val;
	OnUpdateScrollBar();
}

void ScrollPanel::SetHorizontalScrollBarHeight(float val)
{
	RETURN_IF_EQUAL(mHorizontalScrollBarHeight, val);
	mHorizontalScrollBarHeight = val;
	OnUpdateScrollBar();
}

void ScrollPanel::SetVerticalScrollBarWidth(float val)
{
	RETURN_IF_EQUAL(mVerticalScrollBarWidth, val);
	mVerticalScrollBarWidth = val;
	OnUpdateScrollBar();
}

bool ScrollPanel::Update(float dt, NodeUpdateFlags flag /*= NodeUpdateFlags::None*/)
{
	bool isMoved = mScrollModel->UpdateModel(dt);
	if (isMoved)
	{
		OnMoveChildren();
		UpdateScrollStatus();
	}

	return true;
}

void ScrollPanel::OnBeginMove()
{

}

void ScrollPanel::OnEndMove()
{
	UpdateScrollStatus();
}

bool ScrollPanel::IsSensitiveToChildLayoutChanged(const ILayoutable& sender, NodeLayoutChangedFlags changedFlag)
{
	INode* child = (INode*)&sender;
	return !mManagedNodes.Contains(child);
}



MEDUSA_IMPLEMENT_RTTI(ScrollPanel, IPanel);


MEDUSA_END;
