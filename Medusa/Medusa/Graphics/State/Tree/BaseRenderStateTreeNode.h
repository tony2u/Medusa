// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/Dictionary.h"
#include "Graphics/State/RenderStateType.h"
#include "Graphics/State/IRenderState.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;


class BaseRenderStateTreeNode:public ISharableSingleThread
{
public:
	BaseRenderStateTreeNode(const Share<IRenderState>& state = nullptr, RenderStateTreeCompositeNode* parent = nullptr);
	virtual ~BaseRenderStateTreeNode(void);

	uint Id() const { return mId; }
	const Share<IRenderState>& State() const { return mState; }
	RenderStateTreeCompositeNode* Parent() const { return mParent; }

	void Apply();
	void Restore();

protected:
	RenderStateTreeCompositeNode* mParent;
	uint mId;
	Share<IRenderState> mState;	//null able
	
};

MEDUSA_END;
