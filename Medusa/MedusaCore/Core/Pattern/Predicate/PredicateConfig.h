// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/IdObjectCache.h"
#include "Core/IO/IFileLoadable.h"
#include "Core/Pattern/Predicate/IPredicate.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"


MEDUSA_BEGIN;


class PredicateConfig :public Singleton < PredicateConfig >, public IdObjectCache < uint, IPredicate*>, public IFileLoadable
{
	friend class Singleton < PredicateConfig > ;
	PredicateConfig() {}
	~PredicateConfig(void) {}
public:
	virtual bool LoadFromData(StringRef path, const MemoryByteData& data, uint format = 0);
	virtual void Unload();
private:
	void LoadPredicate(pugi::xml_node node, IPredicate* parent);

};

MEDUSA_END;
