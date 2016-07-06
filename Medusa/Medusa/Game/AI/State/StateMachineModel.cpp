// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StateMachineModel.h"
#include "IState.h"
#include "StateFactory.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

StateMachineModel::StateMachineModel()
{
	mDefaultState = nullptr;
}

StateMachineModel::~StateMachineModel(void)
{
	SAFE_DELETE_COLLECTION(mStates);
}

void StateMachineModel::Initialize(uint size)
{
	mStates.ForceReserveCount(size);
	mStates.SetAll(nullptr);
}


IState* StateMachineModel::Register(IState* state)
{
	uint index= state->GetIndex();
	if (mStates[index]!=nullptr)
	{
		Log::AssertFailedFormat("Duplicate state index {}", index);
		return nullptr;
	}
	mStates[index] = state;
	return state;
}

IState* StateMachineModel::Register(StringRef name)
{
	IState* state = StateFactory::Instance().Create(name);
	Log::AssertNotNullFormat(state, "Cannot create state:{}", name.c_str());
	Register(state);
	return state;
}

IState* StateMachineModel::Find(StringRef name) const
{
	for (auto state : mStates)
	{
		if (state->ClassName() == name)
		{
			return state;
		}
	}

	return nullptr;
}



IState* StateMachineModel::SmartFind(StringRef name) const
{
	IState* state=Find(name);
	if (state==nullptr)
	{
		state = Find(name + "State");
	}
	return state;
}

MEDUSA_END;
