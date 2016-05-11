// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IScrollMathModel.h"
#ifdef MEDUSA_SAFE_CHECK
#include "Core/Log/Log.h"
#endif

MEDUSA_BEGIN;


IScrollMathModel::IScrollMathModel(ScrollDirection direction /*= ScrollDirection::FreeFromCurrent*/)
	:mDirection(direction),
	mState(ScrollState::None),
	mContainer(Rect2F::Zero),
	mCurrentWindow(Rect2F::Zero),
	mPrevWindow(Rect2F::Zero),
	mInitialOffset(Point2F::Zero),
	mStaticLimitX(0.f),
	mStaticLimitY(0.f),
	mCurrentVelocity(Point2F::Zero)

{

}

IScrollMathModel::~IScrollMathModel(void)
{

}

void IScrollMathModel::SetDirection(ScrollDirection val)
{
	RETURN_IF_EQUAL(mDirection, val);
	mDirection = val;
	OnUpdate();
}

bool IScrollMathModel::IsVertical() const
{
	return mDirection.IsVertical();
}

bool IScrollMathModel::IsHorizontal() const
{
	return mDirection.IsHorizontal();
}



void IScrollMathModel::Initialize(const Size2F& containerSize, const Size2F& windowSize)
{
	Initialize(Rect2F(Point2F::Zero, containerSize), Rect2F(Point2F::Zero, windowSize));
}

void IScrollMathModel::Initialize(const Size2F& containerSize, const Rect2F& window)
{
	Initialize(Rect2F(Point2F::Zero, containerSize), window);
}

void IScrollMathModel::Initialize(const Rect2F& container, const Rect2F& window)
{
	mContainer = container;
	mCurrentWindow = window;
	mPrevWindow = mCurrentWindow;
	OnUpdate();
}


void IScrollMathModel::OnUpdate()
{
	//update initial offset
	ScrollDirectionHorizontal h = mDirection.ToHorizontal();
	switch (h)
	{
		case ScrollDirectionHorizontal::Left:
			mInitialOffset.X = mContainer.Origin.X;
			break;
		case ScrollDirectionHorizontal::Right:
			mInitialOffset.X = mContainer.Right() - mCurrentWindow.Size.Width;
			break;
		default:
			mInitialOffset.X = mCurrentWindow.Origin.X;
			break;
	}

	ScrollDirectionVertical v = mDirection.ToVertical();
	switch (v)
	{
		case ScrollDirectionVertical::Bottom:
			mInitialOffset.Y = mContainer.Origin.Y;
			break;
		case ScrollDirectionVertical::Top:
			mInitialOffset.Y = mContainer.Top() - mCurrentWindow.Size.Height;
			break;
		default:
			mInitialOffset.Y = mCurrentWindow.Origin.Y;
			break;
	}

	//update static limit
	if (mContainer.Size.Width > mCurrentWindow.Size.Width)
	{
		mStaticLimitX.Min = mContainer.Origin.X;
		mStaticLimitX.Max = mContainer.Right() - mCurrentWindow.Size.Width;
	}
	else
	{
		mStaticLimitX.Min = mContainer.Origin.X + mContainer.Size.Width - mCurrentWindow.Size.Width;
		mStaticLimitX.Max = mContainer.Origin.X + mCurrentWindow.Size.Width;
	}

	if (mContainer.Size.Height > mCurrentWindow.Size.Height)
	{
		mStaticLimitY.Min = mContainer.Origin.Y;
		mStaticLimitY.Max = mContainer.Top() - mCurrentWindow.Size.Height;
	}
	else
	{
		mStaticLimitY.Min = mContainer.Origin.Y + mContainer.Size.Height - mCurrentWindow.Size.Height;
		mStaticLimitY.Max = mContainer.Origin.Y;
	}


}

void IScrollMathModel::OnRestrictScroll()
{
	//limit current window
	mCurrentWindow.Origin.X = mStaticLimitX.Clamp(mCurrentWindow.Origin.X);
	mCurrentWindow.Origin.Y = mStaticLimitY.Clamp(mCurrentWindow.Origin.Y);
}

void IScrollMathModel::UpdateWindow(const Size2F& sizeChanged, bool isApplyToLast/*=true*/)
{
	if (mDirection.IsHorizontal())
	{
		mCurrentWindow.Size.Width += sizeChanged.Width;
		bool isAppendToRight = (mDirection == ScrollDirection::HorizontalFromLeft&&isApplyToLast) || (mDirection == ScrollDirection::HorizontalFromRight&&!isApplyToLast);
		if (!isAppendToRight)
		{
			mCurrentWindow.Origin.X -= sizeChanged.Width;
		}
	}
	else if (mDirection.IsVertical())
	{
		mCurrentWindow.Size.Height += sizeChanged.Height;
		bool isAppendTop = (mDirection == ScrollDirection::VerticalFromBottom&&isApplyToLast) || (mDirection == ScrollDirection::VerticalFromTop&&!isApplyToLast);
		if (!isAppendTop)
		{
			mCurrentWindow.Origin.Y -= sizeChanged.Height;
		}
	}
	else
	{
		mCurrentWindow.Size += sizeChanged;
		if (!isApplyToLast)
		{
			mCurrentWindow.Origin.X -= sizeChanged.Width;
			mCurrentWindow.Origin.Y -= sizeChanged.Height;
		}
	}

	mPrevWindow = mCurrentWindow;

	OnUpdate();
}

void IScrollMathModel::UpdateContainer(const Size2F& sizeChanged, bool isApplyToLast /*= true*/)
{
	if (mDirection.IsHorizontal())
	{
		mContainer.Size.Width += sizeChanged.Width;
		bool isAppendToRight = (mDirection == ScrollDirection::HorizontalFromLeft&&isApplyToLast) || (mDirection == ScrollDirection::HorizontalFromRight&&!isApplyToLast);
		if (!isAppendToRight)
		{
			mContainer.Origin.X -= sizeChanged.Width;
		}
	}
	else if (mDirection.IsVertical())
	{
		mContainer.Size.Height += sizeChanged.Height;
		bool isAppendTop = (mDirection == ScrollDirection::VerticalFromBottom&&isApplyToLast) || (mDirection == ScrollDirection::VerticalFromTop&&!isApplyToLast);
		if (!isAppendTop)
		{
			mContainer.Origin.Y -= sizeChanged.Height;
		}
	}
	else
	{
		mContainer.Size += sizeChanged;
		if (!isApplyToLast)
		{
			mContainer.Origin.X -= sizeChanged.Width;
			mContainer.Origin.Y -= sizeChanged.Height;
		}
	}

	OnUpdate();
}

float IScrollMathModel::HorizontalScrollBarOffset() const
{
	if (mCurrentWindow.Size.Width < mContainer.Size.Width)
	{
		return mCurrentWindow.Origin.X;
	}
	else
	{
		//scroll bar always show on container
		return mCurrentWindow.Origin.X* mContainer.Size.Width / mCurrentWindow.Size.Width;
	}
}

float IScrollMathModel::VerticalScrollBarOffset() const
{
	if (mCurrentWindow.Size.Height < mContainer.Size.Height)
	{
		return mCurrentWindow.Origin.X;
	}
	else
	{
		//scroll bar always show on container
		return mCurrentWindow.Origin.Y* mContainer.Size.Height / mCurrentWindow.Size.Height;
	}
}

Point2F IScrollMathModel::ScrollBarOffset() const
{
	return mpp(HorizontalScrollBarOffset(), VerticalScrollBarOffset());
}

float IScrollMathModel::HorizontalScrollBarWidth() const
{
	if (mCurrentWindow.Size.Width < mContainer.Size.Width)
	{
		return mCurrentWindow.Size.Width;
	}
	else
	{
		//scroll bar always show on container
		//percent in container
		return mContainer.Size.Width*mContainer.Size.Width / mCurrentWindow.Size.Width;
	}
}

float IScrollMathModel::VerticalScrollBarHeight() const
{
	if (mCurrentWindow.Size.Height<mContainer.Size.Height)
	{
		return mCurrentWindow.Size.Height;
	}
	else
	{
		//scroll bar always show on container
		//percent in container
		return mContainer.Size.Height*mContainer.Size.Height / mCurrentWindow.Size.Height;
	}

}

bool IScrollMathModel::NeedHorizontalScrollBar() const
{
	return mCurrentWindow.Size.Width > mContainer.Size.Width;
}

bool IScrollMathModel::NeedVerticalScrollBar() const
{
	return mCurrentWindow.Size.Height > mContainer.Size.Height;
}


Point2F IScrollMathModel::Offset() const
{
	return mCurrentWindow.Origin - mInitialOffset;
}

float IScrollMathModel::OffsetX() const
{
	return mCurrentWindow.Origin.X - mInitialOffset.X;

}

float IScrollMathModel::OffsetY() const
{
	return mCurrentWindow.Origin.Y - mInitialOffset.Y;
}

Point2F IScrollMathModel::MovementToEnd() const
{
	Point2F leftMovement = Point2F::Zero;
	ScrollDirectionHorizontal h = mDirection.ToHorizontal();
	switch (h)
	{
		case ScrollDirectionHorizontal::Left:
			leftMovement.X = mStaticLimitX.MovementToMax(mCurrentWindow.Origin.X);
			break;
		case ScrollDirectionHorizontal::Right:
			leftMovement.X = mStaticLimitX.MovementFromMin(mCurrentWindow.Origin.X);
			break;
		default:
			break;
	}

	ScrollDirectionVertical v = mDirection.ToVertical();
	switch (v)
	{
		case ScrollDirectionVertical::Bottom:
			leftMovement.Y = mStaticLimitY.MovementToMax(mCurrentWindow.Origin.Y);
			break;
		case ScrollDirectionVertical::Top:
			leftMovement.Y = mStaticLimitY.MovementFromMin(mCurrentWindow.Origin.Y);
			break;
		default:
			break;
	}
	return leftMovement;


}

Point2F IScrollMathModel::MovementToStart() const
{
	return mInitialOffset - mCurrentWindow.Origin;

}

Point2F IScrollMathModel::ConvertToWindowSpace(Point2F pos)
{
	Point2F totalMovement = Offset();
	return pos - totalMovement;
}


bool IScrollMathModel::IsRectVisible(const Rect2F& rect) const
{
	//in container
	Point2F totalMovement = Offset();

	if (mDirection.IsVertical())
	{
		float bottom = rect.Bottom() + totalMovement.Y;
		float top = rect.Top() + totalMovement.Y;

		return (mContainer.Bottom() <= bottom&& mContainer.Top() >= bottom) || (mContainer.Bottom() <= top && mContainer.Top() >= top);
	}
	else if (mDirection.IsHorizontal())
	{
		float left = rect.Left() + totalMovement.X;
		float right = rect.Right() + totalMovement.X;
		return (mContainer.Left() <= left&& mContainer.Right() >= left) || (mContainer.Left() <= right && mContainer.Right() >= right);
	}
	else
	{
		Rect2F copy = rect;
		copy.Origin += totalMovement;
		return mContainer.IsIntersect(rect);
	}
}


void IScrollMathModel::StartScrolling(Point2F initialVelocity)
{
	mCurrentVelocity = initialVelocity;
	mState = ScrollState::Scrolling;

}

void IScrollMathModel::Focus()
{
	mState = ScrollState::Begin;
	mCurrentVelocity = Point2F::Zero;
}

void IScrollMathModel::Release()
{
	mCurrentVelocity = Point2F::Zero;
	mState = ScrollState::End;

}

void IScrollMathModel::StaticScroll(Point2F movement)
{
	mState = ScrollState::StaticScroll;
	ScrollBy(movement);
}

void IScrollMathModel::ScrollTo(Point2F offset)
{
	mCurrentWindow.Origin = mInitialOffset + offset;
	OnRestrictScroll();
	OnScroll();
}

void IScrollMathModel::ScrollBy(Point2F movement)
{
	mCurrentWindow.Origin += movement;
	OnRestrictScroll();
	OnScroll();

}

void IScrollMathModel::ScrollToStart()
{
	Point2F movement = MovementToStart();
	ScrollBy(movement);
}

void IScrollMathModel::ScrollToEnd()
{
	Point2F movement = MovementToEnd();
	ScrollBy(movement);
}


Point2F IScrollMathModel::PageCount() const
{
	return mpp(mContainer.Width() / mCurrentWindow.Width(), mContainer.Height() / mCurrentWindow.Height());
}

Point2F IScrollMathModel::Page() const
{
	Point2F offset = Offset();
	return mpp(offset.X / mCurrentWindow.Width(), offset.Y / mCurrentWindow.Height());
}

float IScrollMathModel::PageX() const
{
	return OffsetX() / mCurrentWindow.Width();
}

float IScrollMathModel::PageY() const
{
	return OffsetY() / mCurrentWindow.Height();
}

void IScrollMathModel::ScrollByPageX(float page)
{
	Point2F movement(page*mCurrentWindow.Size.Width, 0.f);
	ScrollBy(movement);
}

void IScrollMathModel::ScrollByPageY(float page)
{
	Point2F movement(0.f, page*mCurrentWindow.Size.Height);
	ScrollBy(movement);
}


void IScrollMathModel::ScrollByPage(Point2F page)
{
	Point2F movement(page.X*mCurrentWindow.Size.Width, page.Y*mCurrentWindow.Size.Height);
	ScrollBy(movement);
}

void IScrollMathModel::ScrollToPageX(float page)
{
	Point2F movement(page*mCurrentWindow.Size.Width, 0.f);
	movement += mInitialOffset;
	ScrollTo(movement);
}

void IScrollMathModel::ScrollToPageY(float page)
{
	Point2F movement(0.f, page*mCurrentWindow.Size.Height);
	movement += mInitialOffset;
	ScrollTo(movement);
}


void IScrollMathModel::ScrollToPage(Point2F page)
{
	Point2F movement(page.X*mCurrentWindow.Size.Width, page.Y*mCurrentWindow.Size.Height);
	movement += mInitialOffset;
	ScrollTo(movement);
}

void IScrollMathModel::OnScrollingEnd()
{
	if (mDirection.IsHorizontal())
	{
		float left = mCurrentWindow.Left();
		float movement = mStaticLimitX.CalculateMinDockMovement(left);
		ScrollBy(mpp(-movement, 0.f));
	}
	else if (mDirection.IsVertical())
	{
		float bottom = mCurrentWindow.Bottom();
		float movement = mStaticLimitY.CalculateMinDockMovement(bottom);
		ScrollBy(mpp(0.f, -movement));
	}
	else
	{
		float left = mCurrentWindow.Left();
		float movementx = mStaticLimitX.CalculateMinDockMovement(left);

		float bottom = mCurrentWindow.Bottom();
		float movementy = mStaticLimitY.CalculateMinDockMovement(bottom);
		ScrollBy(mpp(-movementx, -movementy));
	}
}



bool IScrollMathModel::UpdateModel(float dt)
{
	switch (mState)
	{
		case IScrollMathModel::ScrollState::None:
		case IScrollMathModel::ScrollState::Begin:
		case IScrollMathModel::ScrollState::StaticScroll:
		case IScrollMathModel::ScrollState::End:
			return false;
		case IScrollMathModel::ScrollState::Scrolling:
		{
			Point2F movement = mCurrentVelocity*dt;
			ScrollBy(movement);
		}

		break;
		default:
			break;
	}

	return true;
}





MEDUSA_END;
