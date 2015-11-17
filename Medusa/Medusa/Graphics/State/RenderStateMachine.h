// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Singleton.h"
#include "Core/Collection/Stack.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/RTTI/RTTIClass.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

/*
????????Render?????????????,???????????????,
????????????????????????,??????????????
*/
class RenderStateMachine:public Singleton<RenderStateMachine>,public IInitializable
{
	friend class Singleton<RenderStateMachine>;
	typedef Stack<IRenderState*> RenderStateStack;
private:
	RenderStateMachine();
	~RenderStateMachine();
public:
	void Push(IRenderState* state);
	void Pop(const IRenderState* state=nullptr);

public:
	virtual bool Initialize();
	
private:
	Dictionary<uint,RenderStateStack*>  mRenderStates;

};

MEDUSA_END;
