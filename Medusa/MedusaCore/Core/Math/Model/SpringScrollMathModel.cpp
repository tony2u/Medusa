// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "SpringScrollMathModel.h"

MEDUSA_BEGIN;


SpringScrollMathModel::SpringScrollMathModel(ScrollDirection direction /*= ScrollDirection::FreeFromCurrent*/)
	:IScrollMathModel(direction),
	mSpringLimitX(0),
	mSpringLimitY(0),
	mSpringSizePercent(mpp(0.2f, 0.2f)),
	mSpringFactor(100.f),
	mDampingStartFactor(100.f),
	mDampingFactor(0.8f)
{
	mInitialVelocityFactor = 0.8f;
}

SpringScrollMathModel::~SpringScrollMathModel(void)
{

}


void SpringScrollMathModel::ScrollTo(Point2F offset)
{
	IScrollMathModel::ScrollTo(offset);
	mCurrentWindow.Origin.X = Math::Clamp(mCurrentWindow.Origin.X, mSpringLimitX.Min, mSpringLimitX.Max);
	mCurrentWindow.Origin.Y = Math::Clamp(mCurrentWindow.Origin.Y, mSpringLimitY.Min, mSpringLimitY.Max);
}

void SpringScrollMathModel::ScrollBy(Point2F movement)
{
	IScrollMathModel::ScrollBy(movement);
	mCurrentWindow.Origin.X = Math::Clamp(mCurrentWindow.Origin.X, mSpringLimitX.Min, mSpringLimitX.Max);
	mCurrentWindow.Origin.Y = Math::Clamp(mCurrentWindow.Origin.Y, mSpringLimitY.Min, mSpringLimitY.Max);
}

bool SpringScrollMathModel::NeedSpringOnScrolling() const
{
	//horizontal
	if (mDirection.IsHorizontal())
	{
		float left = mCurrentWindow.Left();
		if (Math::IsEqual(mStaticLimitX.Min, mStaticLimitX.Max))
		{
			return true;
		}

		return !mStaticLimitX.Contains(left);
	}

	//vertical
	if (mDirection.IsVertical())
	{
		float bottom = mCurrentWindow.Bottom();
		if (Math::IsEqual(mStaticLimitY.Min, mStaticLimitY.Max))
		{
			return true;
		}
		return !mStaticLimitY.Contains(bottom);
	}

	return false;

}

bool SpringScrollMathModel::NeedSpringOnSpring() const
{
	//horizontal
	if (mDirection.IsHorizontal())
	{
		float left = mCurrentWindow.Left();
		if (Math::IsEqual(mStaticLimitX.Min, mStaticLimitX.Max))
		{
			return false;
		}

		return !mStaticLimitX.Contains(left);
	}

	//vertical
	if (mDirection.IsVertical())
	{
		float bottom = mCurrentWindow.Bottom();
		if (Math::IsEqual(mStaticLimitY.Min, mStaticLimitY.Max))
		{
			return false;
		}
		return !mStaticLimitY.Contains(bottom);
	}

	return false;
}

void SpringScrollMathModel::Release()
{
	mCurrentVelocity = Point2F::Zero;
	if (NeedSpringOnScrolling())
	{
		mState = ScrollState::Spring;
	}
	else
	{
		mState = ScrollState::End;
	}

}
bool SpringScrollMathModel::UpdateModel(float dt)
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
			Point2F a = CalculateScrollAccelerate();

			Point2F deltaVelocity = a*dt;
			mCurrentVelocity += a*dt;
			bool isStopX = Math::IsSameSign(mCurrentVelocity.X, deltaVelocity.X);
			bool isStopY = Math::IsSameSign(mCurrentVelocity.Y, deltaVelocity.Y);
			if (isStopX)
			{
				mCurrentVelocity.X = 0.f;
			}
			if (isStopY)
			{
				mCurrentVelocity.Y = 0.f;
			}

			Point2F movement = mCurrentVelocity*dt;
			if (movement == Point2F::Zero)
			{
				mState = ScrollState::End;
			}
			else
			{
				ScrollBy(movement);
			}

			if (NeedSpringOnScrolling())
			{
				mCurrentVelocity = Point2F::Zero;
				mState = ScrollState::Spring;
			}
		}

		break;
		case IScrollMathModel::ScrollState::Spring:
		{
			Point2F a = CalculateSpringAccelerate();

			mCurrentVelocity += a*dt;
			Point2F movement = mCurrentVelocity*dt;
			ScrollBy(movement);

			if (!NeedSpringOnSpring())
			{
				OnScrollingEnd();
				mState = ScrollState::End;
			}
		}
		break;
		default:
			break;
	}

	return true;
}


Point2F SpringScrollMathModel::CalculateScrollAccelerate() const
{
	Point2F a = Point2F::Zero;
	//horizontal
	if (mDirection.IsHorizontal())
	{
		a.X = Math::InverseSign(mCurrentVelocity.X)*mDampingStartFactor - mDampingFactor*mCurrentVelocity.X;
	}

	//vertical
	if (mDirection.IsVertical())
	{
		a.Y = Math::InverseSign(mCurrentVelocity.Y)*mDampingStartFactor - mDampingFactor*mCurrentVelocity.Y;
	}

	return a;
}


Point2F SpringScrollMathModel::CalculateSpringAccelerate() const
{
	Point2F a = Point2F::Zero;
	//horizontal
	if (mDirection.IsHorizontal())
	{
		float left = mCurrentWindow.Left();
		if (left < mStaticLimitX.Min)
		{
			a.X = mSpringFactor*(mStaticLimitX.Min - left);
		}
		else if (left > mStaticLimitX.Max)
		{
			a.X = mSpringFactor*(mSpringLimitX.Max - left);
		}
		else
		{
			a.X = -mDampingStartFactor - mDampingFactor*mCurrentVelocity.X;
		}
	}

	//vertical
	if (mDirection.IsVertical())
	{
		float bottom = mCurrentWindow.Bottom();
		if (bottom < mStaticLimitY.Min)
		{
			a.Y = mSpringFactor*(mStaticLimitY.Min - bottom);
		}
		else if (bottom > mStaticLimitY.Max)
		{
			a.Y = mSpringFactor*(mStaticLimitY.Max - bottom);
		}
		else
		{
			a.Y = -mDampingStartFactor - mDampingFactor*mCurrentVelocity.Y;
		}
	}

	return a;
}

void SpringScrollMathModel::OnUpdate()
{
	IScrollMathModel::OnUpdate();

	//update spring limit

	Point2F springOffset = mpp(mContainer.Size.Width*mSpringSizePercent.X, mContainer.Size.Height*mSpringSizePercent.Y);

	mSpringLimitX.Min = mStaticLimitX.Min - springOffset.X;
	mSpringLimitX.Max = mStaticLimitX.Max + springOffset.X;

	mSpringLimitY.Min = mStaticLimitY.Min - springOffset.Y;
	mSpringLimitY.Max = mStaticLimitY.Max + springOffset.Y;
}

void SpringScrollMathModel::OnRestrictScroll()
{
	//limit current window
	mCurrentWindow.Origin.X = mSpringLimitX.Clamp(mCurrentWindow.Origin.X);
	mCurrentWindow.Origin.Y = mSpringLimitY.Clamp(mCurrentWindow.Origin.Y);
}


void SpringScrollMathModel::OnScrollingEnd()
{
	//limit current window
	switch (mState)
	{
		case IScrollMathModel::ScrollState::Scrolling:
		case IScrollMathModel::ScrollState::Spring:
			mCurrentWindow.Origin.X = mSpringLimitX.Clamp(mCurrentWindow.Origin.X);
			mCurrentWindow.Origin.Y = mSpringLimitY.Clamp(mCurrentWindow.Origin.Y);
			break;
		case IScrollMathModel::ScrollState::None:
		case IScrollMathModel::ScrollState::Begin:
		case IScrollMathModel::ScrollState::StaticScroll:
		case IScrollMathModel::ScrollState::End:
		default:
			mCurrentWindow.Origin.X = mStaticLimitX.Clamp(mCurrentWindow.Origin.X);
			mCurrentWindow.Origin.Y = mStaticLimitY.Clamp(mCurrentWindow.Origin.Y);
			break;

	}

}

void SpringScrollMathModel::StartScrolling(Point2F initialVelocity)
{
	mCurrentVelocity = initialVelocity*mInitialVelocityFactor;
	mState = ScrollState::Scrolling;
}

MEDUSA_END;
