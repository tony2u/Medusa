// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Action/BaseInstantAction.h"
#include "Core/Pattern/Delegate.h"
#include "Core/Compile/TypeTraits.h"
MEDUSA_BEGIN;

template<typename TArg>
class ArgDelegateAction :public BaseInstantAction
{
public:
	typedef Delegate<void(void*, TArg)> DelegateType;
	typedef typename Compile::TypeTraits<TArg>::ParameterType TArgParameterType;
public:
	ArgDelegateAction(DelegateType func, TArgParameterType arg, const StringRef& name = StringRef::Empty) :BaseInstantAction(name), mDelegate(func), mArg(arg) {}
	virtual ~ArgDelegateAction(void) {}
	virtual ActionType Type()const { return ActionType::Instant; }
public:
	virtual ArgDelegateAction* Clone()const override { return new ArgDelegateAction(mDelegate, mArg); }
	virtual ArgDelegateAction* Reverse()const override { return new ArgDelegateAction(mDelegate, mArg); }
	static ArgDelegateAction* Create(DelegateType func, TArgParameterType arg) { return new ArgDelegateAction(func, arg); }
protected:
	virtual bool OnAction()
	{
		if (mDelegate.IsValid())
		{
			this->mDelegate(this->mTarget, mArg);
		}
		return true;
	}
protected:
	DelegateType mDelegate;
	TArg mArg;

};

MEDUSA_END;
