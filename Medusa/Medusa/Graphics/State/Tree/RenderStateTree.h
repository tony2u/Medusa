// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

class RenderStateTree:public Singleton<RenderStateTree>,public IInitializable
{
	friend class Singleton<RenderStateTree>;
	RenderStateTree();
	~RenderStateTree();
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override;
public:
	RenderStateTreeLeafNode* FindUniqueNode(const RenderStateSet& state);
	void Release(RenderStateTreeLeafNode* node);
	uint MinId()const;
	uint CalcuateId(const RenderStateTreeLeafNode& node)const;
	RenderStateTreeLeafNode* EmptyNode() const { return mEmptyNode; }

public:
	RenderStateTreeCompositeNode* mRoot;
	RenderStateTreeLeafNode* mEmptyNode;
};

MEDUSA_END;
