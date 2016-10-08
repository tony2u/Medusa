// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "BaseFiniteRepeatableCountDownDelayAction.h"

MEDUSA_BEGIN;

bool BaseFiniteRepeatableCountDownDelayAction::Update(float dt, float blend /*= 1.f*/)
{
	RETURN_FALSE_IF_FALSE(IAction::Update(dt, blend));

	switch (mMode)
	{
		case RepeateModeStep::Before:	//before delay
			mBeforeDelayElapsed += dt;
			if (mBeforeDelayElapsed <= mBeforeDelay)
			{
				return true;
			}
			dt = mBeforeDelayElapsed - mBeforeDelay;
			mMode = RepeateModeStep::Repeat;
		case RepeateModeStep::Repeat:	//repeat
		{
			float prevElapsed = this->mElapsed;
			this->mElapsed += dt;
			if (this->mElapsed > this->mDuration)
			{
				float exceed = this->mElapsed - this->mDuration;
				this->mElapsed = this->mDuration;

				if (mCurrentCount == 0)
				{
					if (mHasAfterDelay)
					{
						mMode = RepeateModeStep::After;
						this->OnUpdate(prevElapsed, dt - exceed, blend);
						dt = exceed;
					}
					else
					{
						this->Stop();
						return OnUpdate(prevElapsed, dt - exceed, blend);
					}
				}
				else
				{
					if (mCurrentCount > 0)
					{
						--mCurrentCount;
					}

					this->OnUpdate(prevElapsed, dt - exceed, blend);
					this->Start();	//this->mElapsed will reset to 0.f in start
					this->OnUpdate(0.f, exceed, blend);
				}
			}
			else
			{
				this->OnUpdate(prevElapsed, dt, blend);
			}

			if (mMode == RepeateModeStep::Repeat)
			{
				if (mHasRepeatDuration)
				{
					mRepeatElapsed += dt;
					if (mRepeatElapsed > mRepeatDuration)
					{
						dt = mRepeatDuration - mRepeatElapsed;
						if (mHasAfterDelay)
						{
							mMode = RepeateModeStep::After;
						}
						else
						{
							this->Stop();
							return true;
						}
					}
					else
					{
						return true;
					}
				}
				else
				{
					return true;
				}
				
			}
		}
		case RepeateModeStep::After:	//after delay
			mAfterDelayElapsed += dt;
			if (mAfterDelayElapsed > mAfterDelay)
			{
				this->Stop();
				return true;
			}
			break;
	}

	return true;
}

float BaseFiniteRepeatableCountDownDelayAction::ElapsedExceed() const
{
	switch (mMode)
	{
		case RepeateModeStep::Before:
			break;
		case RepeateModeStep::Repeat:
			if (mHasRepeatDuration)
			{
				if (mRepeatElapsed > mRepeatDuration)
				{
					return mRepeatElapsed - mRepeatDuration;
				}
			}

			return Math::ClampAboveZero(mElapsed - mDuration);
		case RepeateModeStep::After:
			return Math::ClampAboveZero(mAfterDelayElapsed - mAfterDelay);
			break;
	}

	return 0.f;
}


void BaseFiniteRepeatableCountDownDelayAction::BuildClone(IAction& obj)
{
	BaseFiniteRepeatableAction::BuildClone(obj);
	auto& t = (BaseFiniteRepeatableCountDownDelayAction&)obj;
	t.mBeforeDelay = mBeforeDelay;
	t.mRepeatDuration = mRepeatDuration;
	t.mAfterDelay = mAfterDelay;

	t.mBeforeDelayElapsed = mBeforeDelayElapsed;
	t.mAfterDelayElapsed = mAfterDelayElapsed;
	t.mRepeatElapsed = mRepeatElapsed;

	t.mHasRepeatDuration = mHasRepeatDuration;
	t.mHasAfterDelay = mHasAfterDelay;
	t.mHasBeforeDelay = mHasBeforeDelay;

	t.mMode = mMode;
}

MEDUSA_END;
