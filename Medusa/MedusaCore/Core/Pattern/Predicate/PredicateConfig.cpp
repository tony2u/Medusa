// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "PredicateConfig.h"
#include "Core/Pattern/Predicate/PredicateFactory.h"
#include "Core/Pattern/Predicate/IPredicate.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

bool PredicateConfig::LoadFromData(StringRef path, const MemoryByteData& data, uint format /*= 0*/)
{
	Unload();
	RETURN_FALSE_IF(data.IsNull());

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_buffer(data.Data(), data.Size());
	if (!result)
	{
		Log::AssertFailedFormat("Cannot parse xml:{} because {}", path.c_str(), result.description());
		return false;
	}

	FOR_EACH_COLLECTION_STL(i, doc.first_child().children())
	{
		pugi::xml_node child = *i;
		StringRef typeName = child.name();
		uint id = child.attribute("Id").as_uint(0);
		StringRef parameter = child.attribute("Parameter").value();

#ifdef MEDUSA_SAFE_CHECK
		if (ContainsId(id))
		{
			Log::AssertFailedFormat("Duplicate id:{} in {}", id, typeName.c_str());
		}
#endif
		IPredicate* predicate = PredicateFactory::Instance().SmartCreate(typeName);
		predicate->SetId(id);
		predicate->SetParamter(parameter);
		predicate->Initialize();
		Add(id, predicate);

		predicate->Retain();
		LoadPredicate(child, predicate);
	}


	return true;
}

void PredicateConfig::LoadPredicate(pugi::xml_node node, IPredicate* parent)
{
	FOR_EACH_COLLECTION_STL(i, node.children())
	{
		pugi::xml_node child = *i;
		StringRef typeName = child.name();
		StringRef paramter = child.attribute("Paramter").value();
		IPredicate* predicate = PredicateFactory::Instance().SmartCreate(typeName);
		predicate->SetParamter(paramter);
		predicate->Initialize();
		LoadPredicate(child, predicate);
		parent->Add(predicate);

	}
}

void PredicateConfig::Unload()
{
	Clear();
}



MEDUSA_END;