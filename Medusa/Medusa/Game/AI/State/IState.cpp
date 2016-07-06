// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IState.h"
#include "StateAutoConnector.h"
#include "StateEventConnector.h"

MEDUSA_BEGIN;

IState::IState()
{

}

IState::~IState(void)
{
	SAFE_DELETE_COLLECTION(mBeforeConnectors);
	SAFE_DELETE_COLLECTION(mAfterConnectors);
	SAFE_DELETE_COLLECTION(mEventConnectors);
}


void IState::AddBefore(StateAutoConnector* val)
{
	mBeforeConnectors.Add(val);
}

void IState::AddAfter(StateAutoConnector* val)
{
	mAfterConnectors.Add(val);
}

void IState::AddEvent(StateEventConnector* val)
{
	mEventConnectors.Add(val);
}

void IState::Enter(void* sender)
{

}

void IState::Exit(void* sender)
{

}



StateAutoConnector* IState::Update(void* sender, float dt)
{
	for (auto connector : mBeforeConnectors)
	{
		if (connector->Evaluate(sender))
		{
			return connector;
		}
	}

	RETURN_NULL_IF_TRUE(OnUpdate(sender, dt));

	for (auto connector : mAfterConnectors)
	{
		if (connector->Evaluate(sender))
		{
			return connector;
		}
	}

	return nullptr;
}


StateEventConnector* IState::ReceiveEvent(void* sender, IEventArg& e)
{
	OnBeforeEvent(sender, e);
	for (auto connector : mEventConnectors)
	{
		if (connector->IsFit(e) && connector->Evaluate(sender))
		{
			return connector;
		}
	}

	OnAfterEvent(sender, e);
	return nullptr;
}

MEDUSA_END;