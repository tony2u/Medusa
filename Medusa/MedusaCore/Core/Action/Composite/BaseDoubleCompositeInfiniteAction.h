// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInfiniteAction.h"

MEDUSA_BEGIN;
class BaseDoubleCompositeInfiniteAction :public BaseInfiniteAction
{
public:
	BaseDoubleCompositeInfiniteAction(IAction* from, IAction* to) :mFrom(from), mTo(to) {}
	virtual ~BaseDoubleCompositeInfiniteAction(void)
	{
		SAFE_DELETE(mFrom);
		SAFE_DELETE(mTo);
	}
public:
	virtual bool IsRunning()const override { return BaseInfiniteAction::IsRunning() &&(mFrom != nullptr && mFrom->IsRunning()) && (mTo != nullptr && mTo->IsRunning()); }
	virtual bool IsDone()const override { return BaseInfiniteAction::IsDone()||(mFrom == nullptr || mFrom->IsDone()) && (mTo == nullptr || mTo->IsDone()); }

	virtual bool Reset()override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Reset());

		mFrom->Reset();
		mTo->Reset();

		return true;
	}

	virtual bool Initialize(void* target)override
	{
		RETURN_FALSE_IF_FALSE(BaseInfiniteAction::Initialize(target));

		RETURN_FALSE_IF_FALSE(mFrom->Initialize(target));
		RETURN_FALSE_IF_FALSE(mTo->Initialize(target));

		return true;
	}

	virtual IAction* FindActionByTagRecursively(int tag)const override
	{
		if (mFrom->Tag() == tag)
		{
			return mFrom;
		}

		if (mTo->Tag() == tag)
		{
			return mTo;
		}
		IAction* result = mFrom->FindActionByTagRecursively(tag);
		RETURN_SELF_IF_NOT_NULL(result);
		return mTo->FindActionByTagRecursively(tag);
	}

	virtual IAction* FindActionByNameRecursively(const StringRef& name) const override
	{
		if (mFrom->Name() == name)
		{
			return mFrom;
		}

		if (mTo->Name() == name)
		{
			return mTo;
		}
		IAction* result = mFrom->FindActionByNameRecursively(name);
		RETURN_SELF_IF_NOT_NULL(result);
		return mTo->FindActionByNameRecursively(name);
	}
public:
	IAction* From() const { return mFrom; }
	IAction* To() const { return mTo; }

protected:
	IAction* mFrom=nullptr;
	IAction* mTo=nullptr;
};
MEDUSA_END;
