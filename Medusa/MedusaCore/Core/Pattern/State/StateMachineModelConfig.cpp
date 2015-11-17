// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "StateMachineModelConfig.h"
#include "Core/Pattern/State/StateFactory.h"
#include "Core/Pattern/State/StateMachineModel.h"
#include "Core/Log/Log.h"
#include "Core/Pattern/State/StateAutoConnector.h"
#include "Core/Pattern/State/StateEventConnector.h"
#include "Core/Pattern/Predicate/PredicateConfig.h"
MEDUSA_BEGIN;

bool StateMachineModelConfig::LoadFromData(StringRef path, const MemoryByteData& data, uint format /*= 0*/)
{
	RETURN_FALSE_IF(data.IsNull());

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", path.c_str(), result.description());
		return false;
	}

	List<IState*> states;
	FOR_EACH_COLLECTION_STL(i, doc.first_child().children())
	{
		pugi::xml_node child = *i;
		StringRef typeName = child.name();
		StringRef defaultStateStr = child.attribute("Default").value();

		StateMachineModel* model = new StateMachineModel();
		model->SetName(typeName);
		Add(typeName, model);

		//load states
		uint maxIndex = 0;
		states.Clear();
		FOR_EACH_COLLECTION_STL(j, child.children())
		{
			pugi::xml_node stateChild = *j;
			StringRef stateTypeName = stateChild.name();
			IState* state = StateFactory::Instance().SmartCreate(stateTypeName);
			states.Add(state);
			maxIndex = Math::Max(maxIndex, state->GetIndex());
		}

		model->Initialize(maxIndex + 1);
		FOR_EACH_COLLECTION(j, states)
		{
			IState* state = *j;
			model->Register(state);
		}

		if (!defaultStateStr.IsEmpty())
		{
			IState* defaultState = model->SmartFind(defaultStateStr);
			Log::AssertNotNullFormat(defaultState, "Cannot find StateMachineModel Default State:{}", defaultStateStr.c_str());
			model->SetDefaultState(defaultState);
		}



		//load connectors
		uint index = 0;
		FOR_EACH_COLLECTION_STL(j, child.children())
		{
			pugi::xml_node stateChild = *j;
			IState* state = states[index++];

			//load connector
			FOR_EACH_COLLECTION_STL(k, stateChild.children())
			{
				pugi::xml_node connectorChild = *k;
				StringRef connectorTypeName = connectorChild.name();
				IStateConnector* connector = nullptr;
				if (connectorTypeName == "Before")
				{
					StateAutoConnector* autoConnector = new StateAutoConnector();
					state->AddBefore(autoConnector);
					connector = autoConnector;
				}
				else if(connectorTypeName == "After")
				{
					StateAutoConnector* autoConnector = new StateAutoConnector();
					state->AddAfter(autoConnector);
					connector = autoConnector;
				}
				else if (connectorTypeName == "Event")
				{
					StateEventConnector* eventConnector = new StateEventConnector();
					state->AddEvent(eventConnector);
					connector = eventConnector;

					StringRef stateEventTypeStr = connectorChild.attribute("Type").value();
					if (!stateEventTypeStr.IsEmpty())
					{
						eventConnector->SetEventType(stateEventTypeStr);
					}

				}
				else
				{
					Log::AssertFailedFormat("Invalid state connector type:{}", connectorTypeName.c_str());
					return false;
				}

				StringRef stateModeStr = connectorChild.attribute("Mode").value();
				if (!stateModeStr.IsEmpty())
				{
					if (stateModeStr == "Push")
					{
						connector->SetTransitionMode(StateTransitionMode::Push);
					}
					else if (stateModeStr == "Replace")
					{
						connector->SetTransitionMode(StateTransitionMode::Replace);
					}
					else
					{
						Log::AssertFailedFormat("Invalid StateTransitionMode:{}", stateModeStr.c_str());
						return false;
					}
				}

				uint predicateId = connectorChild.attribute("Predicate").as_uint(0);
				if (predicateId!=0)
				{
					IPredicate* predicate = PredicateConfig::Instance().TryGetObjectWithFailed(predicateId, nullptr);
					Log::AssertNotNullFormat(predicate, "Cannot find predicate id:{}", predicateId);
					connector->SetPredicate(predicate);
				}

				StringRef stateStr = connectorChild.attribute("State").value();
				IState* targetState = model->SmartFind(stateStr);
				Log::AssertNotNullFormat(targetState, "Cannot find Connector State:{}", stateStr.c_str());
				connector->SetState(targetState);

			}
		}
	}


	return true;
}

void StateMachineModelConfig::Unload()
{
	Clear();
}


MEDUSA_END;