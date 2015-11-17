// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/IVisitor.h"
#include "Core/Collection/List.h"

MEDUSA_BEGIN;


class ChangedNodeCollector :public IVisitor < INode* >
{
public:
	ChangedNodeCollector();
	~ChangedNodeCollector(void);

	virtual bool Visit(INode* node);

	void Clear();
protected:
	List<INode*> mNodes;
};

MEDUSA_END;
