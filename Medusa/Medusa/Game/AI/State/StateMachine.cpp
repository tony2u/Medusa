// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StateMachine.h"
#include "IState.h"
#include "StateFactory.h"
#include "Core/Log/Log.h"
#include "StateMachineModelConfig.h"
#include "StateAutoConnector.h"
#include "StateEventConnector.h"


MEDUSA_BEGIN;

StateMachine::StateMachine()
{

}

StateMachine::~StateMachine(void)
{
}

bool StateMachine::Initialize(StringRef modelName)
{
	mModel = StateMachineModelConfig::Instance().TryGetObjectWithFailed(modelName, nullptr);
	return mModel != nullptr;
}

void StateMachine::Reset(void* sender)
{
	while (!mCurrentStates.IsEmpty())
	{
		IState* state = mCurrentStates.PopCopy();
		state->Exit(sender);
	}
}


IState* StateMachine::Get(uint index) const
{
	return mModel->Get(index);
}

IState* StateMachine::Find(StringRef name) const
{
	return mModel->Find(name);
}


void StateMachine::Start(void* sender)
{
	IState* defaultState = mModel->DefaultState();
	defaultState->Enter(sender);
	mCurrentStates.Push(defaultState);
}


void StateMachine::Push(void* sender, StringRef name)
{
	IState* state = Find(name);
	Log::AssertNotNullFormat(state, "Cannot create state:{}", name.c_str());
	Push(sender, state);
}

void StateMachine::Push(void* sender, IState* val)
{
	if (!mCurrentStates.IsEmpty())
	{
#ifdef MEDUSA_SAFE_CHECK
		Log::AssertFormat(!mCurrentStates.Contains(val), "Duplicate push state:{}", val->ClassName().c_str());
#endif
		IState* currentState = mCurrentStates.Top();
		currentState->Exit(sender);
	}

	mCurrentStates.Push(val);
	val->Enter(sender);
}

void StateMachine::ReplaceTo(void* sender, IState* val)
{
	if (!mCurrentStates.IsEmpty())
	{
		IState* currentState = mCurrentStates.Top();
		if (currentState != val)
		{
			currentState->Exit(sender);
			currentState->Enter(sender);
			return;
		}
		else
		{
#ifdef MEDUSA_SAFE_CHECK
			Log::AssertFormat(!mCurrentStates.Contains(val), "Duplicate push state:{}", val->ClassName().c_str());
#endif
			currentState->Exit(sender);
			mCurrentStates.Pop();
		}
	}

	mCurrentStates.Push(val);
	val->Enter(sender);
}

void StateMachine::ReplaceTo(void* sender, StringRef name)
{
	IState* state = Find(name);
	Log::AssertNotNullFormat(state, "Cannot create state:{}", name.c_str());
	ReplaceTo(sender, state);
}

bool StateMachine::IsActive(IState* val) const
{
	return Current() == val;
}

bool StateMachine::IsActive(StringRef name) const
{
	return Current()->ClassName() == name;
}

bool StateMachine::IsActive(uint index) const
{
	return Current()->GetIndex() == index;
}

void StateMachine::Update(void* sender, float dt)
{
	StateAutoConnector* connector = mCurrentStates.Top()->Update(sender, dt);
	RETURN_IF_NULL(connector);
	switch (connector->TransitionMode())
	{
		case StateTransitionMode::Push:
			Push(sender, connector->State());
			break;
		case StateTransitionMode::Replace:
			ReplaceTo(sender, connector->State());
			break;
	}

}



void StateMachine::ReceiveEvent(void* sender, IEventArg& e)
{
	StateEventConnector* connector = mCurrentStates.Top()->ReceiveEvent(sender, e);
	RETURN_IF_NULL(connector);
	switch (connector->TransitionMode())
	{
		case StateTransitionMode::Push:
			Push(sender, connector->State());
			break;
		case StateTransitionMode::Replace:
			ReplaceTo(sender, connector->State());
			break;
	}
}

MEDUSA_END;
