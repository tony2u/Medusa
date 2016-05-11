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
	FOR_EACH_COLLECTION(i, mBeforeConnectors)
	{
		StateAutoConnector* connector = *i;
		if (connector->Evaluate(sender))
		{
			return connector;
		}
	}

	RETURN_NULL_IF_TRUE(OnUpdate(sender, dt));

	FOR_EACH_COLLECTION(i, mAfterConnectors)
	{
		StateAutoConnector* connector = *i;
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
	FOR_EACH_COLLECTION(i, mEventConnectors)
	{
		StateEventConnector* connector = *i;
		if (connector->IsFit(e) && connector->Evaluate(sender))
		{
			return connector;
		}
	}

	OnAfterEvent(sender, e);
	return nullptr;
}

MEDUSA_IMPLEMENT_RTTI_ROOT(IState);
MEDUSA_END;