// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "ISceneGraph.h"

MEDUSA_BEGIN;


class UISceneGraph:public ISceneGraph
{
public:
	UISceneGraph(IScene* scene);
	virtual ~UISceneGraph(void);
protected:
	virtual bool OnUpdateQueue()override;

private:
	void AddNodeRecursivelyToRenderQueue(INode* node);
};

MEDUSA_END;
