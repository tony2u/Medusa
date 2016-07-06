// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Delegate.h"


MEDUSA_BEGIN;

template<typename TFunc>
class ScopeGuard
{
public:
	ScopeGuard(const TFunc& func)
		:mFunc(func)
	{
	}

	ScopeGuard(TFunc&& func)
		:mFunc(func)
	{
	}

	~ScopeGuard()
	{
		if (!mDismissed)
		{
			mFunc();
		}
	}

	void Dismiss() { mDismissed = true; }
	void* operator new(std::size_t) = delete;	//only alloc on stack
protected:
	TFunc mFunc;
	bool mDismissed = false;
};

enum class ScopeGuardOnExit {};

template <typename FunctionType>
ScopeGuard<typename std::decay<FunctionType>::type> operator+(detail::ScopeGuardOnExit, FunctionType&& fn)
{
	return ScopeGuard<typename std::decay<FunctionType>::type>(std::forward<FunctionType>(fn));
}

#define SCOPE_EXIT \
  auto MEDUSA_ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) \
  = ::Medusa::ScopeGuardOnExit() + [&]() noexcept


MEDUSA_END;