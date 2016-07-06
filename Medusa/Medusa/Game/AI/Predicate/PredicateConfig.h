// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Object/IdObjectCache.h"
#include "Core/IO/IFileLoadSavable.h"
#include "Game/AI/Predicate/IPredicate.h"


MEDUSA_BEGIN;


class PredicateConfig :public Singleton < PredicateConfig >, public IdObjectCache < uint, IPredicate*>, public IFileLoadSavable
{
	friend class Singleton < PredicateConfig > ;
	PredicateConfig() {}
	~PredicateConfig(void) {}
public:
	virtual bool LoadFromData(const FileIdRef& fileId, const MemoryData& data, uint format = 0);
	virtual void Unload();
private:
	void LoadPredicate(const pugi::xml_node& node, IPredicate* parent);

};

MEDUSA_END;
