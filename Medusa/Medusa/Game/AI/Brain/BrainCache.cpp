// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BrainCache.h"
#include "Game/AI/Behavior/BehaviorConfig.h"
#include "Game/AI/Brain/BrainFactory.h"
#include "Core/Log/Log.h"
#include "Game/AI/Behavior/BehaviorFactory.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "Core/IO/FileIdRef.h"

MEDUSA_BEGIN;



bool BrainCache::LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format /*= 0*/)
{
	Unload();
	RETURN_FALSE_IF(data.IsNull());

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", fileId, result.description());
		return false;
	}

	for(const auto& child: doc.first_child().children())
	{
		StringRef typeName = child.name();
		StringRef id = child.attribute("Id").value();
		if (id.IsEmpty())
		{
			id = typeName;
		}

#ifdef MEDUSA_SAFE_CHECK
		if (ContainsId(id))
		{
			Log::AssertFailedFormat("Duplicate id:{} in {}", id.c_str(), typeName.c_str());
		}
#endif
		auto brain = BrainFactory::Instance().SmartCreate(typeName);
		StringRef paramter = child.attribute("Paramter").value();
		brain->SetParamter(paramter);
		brain->Initialize();

		if (id.EndWith("Brain"))
		{
			Add(id, brain);
		}
		else
		{
			Add(id + "Brain", brain);
		}


		//root behavior
		StringRef rootBehaviorName = child.attribute("Behavior").value();
		if (!rootBehaviorName.IsEmpty())
		{
			IBehavior* behavior = BehaviorConfig::Instance().SmartCreate(rootBehaviorName);
			brain->SetRootBehavior(behavior);
		}

		//event handler
		for (const auto& eventChild : child.children())
		{
			StringRef eventName = eventChild.name();
			StringRef behaviorName = eventChild.attribute("Behavior").value();
			if (!behaviorName.IsEmpty())
			{
				auto behavior = BehaviorConfig::Instance().SmartCreate(behaviorName);
				brain->RegisterEventBehavior(eventName, behavior);
			}
		}
	}


	return true;
}

void BrainCache::Unload()
{
	Clear();
}



IBrain* BrainCache::SmartCreate(StringRef name)
{
	IBrain* brain = TryGetObjectWithFailed(name, nullptr);
	if (brain == nullptr)
	{
		brain = TryGetObjectWithFailed(name + "Brain", nullptr);
	}


	return brain;
}


MEDUSA_END;