// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/Sweeper.h"

MEDUSA_BEGIN;


class NodeSweeper :public Sweeper<INode*>, public Singleton < NodeSweeper >
{
	friend class Singleton < NodeSweeper > ;
protected:
#ifdef MEDUSA_SAFE_CHECK
	virtual void OnAddFailed(INode* item)const override;
#endif
	virtual void OnRelease(INode* item)const override;

};

MEDUSA_END;
