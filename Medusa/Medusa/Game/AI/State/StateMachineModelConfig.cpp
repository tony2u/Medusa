// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "StateMachineModelConfig.h"
#include "Game/AI/State/StateFactory.h"
#include "Game/AI/State/StateMachineModel.h"
#include "Core/Log/Log.h"
#include "Game/AI/State/StateAutoConnector.h"
#include "Game/AI/State/StateEventConnector.h"
#include "Game/AI/Predicate/PredicateConfig.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;

bool StateMachineModelConfig::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format /*= 0*/)
{
	RETURN_FALSE_IF(data.IsNull());

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", fileId, result.description());
		return false;
	}

	List<IState*> states;
	for(const auto& child:doc.first_child().children())
	{
		StringRef typeName = child.name();
		StringRef defaultStateStr = child.attribute("Default").value();

		StateMachineModel* model = new StateMachineModel();
		model->SetName(typeName);
		Add(typeName, model);

		//load states
		uint maxIndex = 0;
		states.Clear();
		for (const auto& stateChild : child.children())
		{
			StringRef stateTypeName = stateChild.name();
			IState* state = StateFactory::Instance().SmartCreate(stateTypeName);
			states.Add(state);
			maxIndex = Math::Max(maxIndex, state->GetIndex());
		}

		model->Initialize(maxIndex + 1);
		for (auto state : states)
		{
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
		for (const auto& stateChild : child.children())
		{
			IState* state = states[index++];

			//load connector
			for (const auto& connectorChild : stateChild.children())
			{
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