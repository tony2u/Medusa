// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaSelector.h"


MEDUSA_BEGIN;

LuaSelector::LuaSelector(lua_State* state, StringRef path)
	:mState(state), mPath(path)
{

}

LuaSelector::LuaSelector(LuaSelector&& val)
	:mState(val.mState),
	mPath(std::move(val.mPath)),
	mIsFunctorActive(val.mIsFunctorActive),
	mFunctorArguments(std::move(val.mFunctorArguments))
{
	val.mIsFunctorActive = false;
	val.mState = nullptr;
}

LuaSelector::LuaSelector(const LuaSelector& val)
	:mState(val.mState),
	mPath(val.mPath),
	mIsFunctorActive(val.mIsFunctorActive),
	mFunctorArguments(val.mFunctorArguments)
{

}
LuaSelector& LuaSelector::operator=(const LuaSelector& val)
{
	mState = val.mState;
	mPath = val.mPath;
	mIsFunctorActive = val.mIsFunctorActive;
	mFunctorArguments = val.mFunctorArguments;
	return *this;
}

LuaSelector& LuaSelector::operator=(LuaSelector&& val)
{
	mState = val.mState;
	mPath = std::move(val.mPath);
	mIsFunctorActive = val.mIsFunctorActive;
	mFunctorArguments = std::move(val.mFunctorArguments);

	val.mIsFunctorActive = false;
	val.mState = nullptr;

	return *this;
}

LuaSelector::~LuaSelector(void)
{
	RETURN_IF_FALSE(mIsFunctorActive);

	LuaStackAutoReset save(mState);	//reset stack after functor call, no matter how many ret returns

	Get().PushToStack();
	ExecuteFunctor(0);
}



void LuaSelector::Retrieve(uint retCount/*=0*/)const
{
	Get().PushToStack();
	ExecuteFunctor(retCount);
}

LuaRef LuaSelector::RetrieveGet(uint retCount/*=0*/)const
{
	LuaStackAutoReset save(mState);
	Retrieve(retCount);
	return LuaRef::PopFromStack(mState);
}


LuaRef LuaSelector::Get() const
{
	return LuaRef::EvaluateGet(mState, mPath);
}

bool LuaSelector::ExecuteFunctor(uint retCount)const
{
	RETURN_FALSE_IF_FALSE(mIsFunctorActive);
	mIsFunctorActive = false;

	LuaStack s(mState);

	int errorFunc = s.SetErrorHandler();	//func,err
	int funcIndex = errorFunc - 1;

	//swap error func and func
	s.Duplicate(funcIndex);
	s.Copy(errorFunc, funcIndex);
	s.Replace(errorFunc);
	//err,func
	errorFunc = errorFunc - 1;

	for (const auto& arg : mFunctorArguments)
	{
		s.Push(arg);
	}

	int statusCode = lua_pcall(mState, (int)mFunctorArguments.Count(), retCount, errorFunc);	//err,func,ret
	s.RemoveAt(errorFunc);	//func,ret
	s.RemoveAt(funcIndex - 1);	//ret


	return statusCode == LUA_OK;
}

MEDUSA_END;
#endif