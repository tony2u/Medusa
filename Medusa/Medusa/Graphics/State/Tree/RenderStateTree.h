// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Pattern/IInitializable.h"
#include "Core/Pattern/Share.h"

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
	Share<RenderStateTreeLeafNode> FindUniqueNode(const RenderStateSet& state);
	void Release(const Share<RenderStateTreeLeafNode>& node);
	uint MinId()const;
	uint CalcuateId(const RenderStateTreeLeafNode& node)const;
	const Share<RenderStateTreeLeafNode>& EmptyNode() const { return mEmptyNode; }

public:
	Share<RenderStateTreeCompositeNode> mRoot;
	Share<RenderStateTreeLeafNode> mEmptyNode;
};

MEDUSA_END;
