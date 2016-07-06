// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Rendering/IRenderGroup.h"
#include "Core/Collection/List.h"
#include "Resource/Effect/IEffect.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class EffectRenderGroup:public IRenderGroup
{
public:
	EffectRenderGroup();
	virtual ~EffectRenderGroup();

	const Share<IEffect>& Effect() const { return mEffect; }
	void SetEffect(const Share<IEffect>& val) { mEffect = val; }
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;

	virtual bool Add(IRenderBatch* batch)override;
	virtual void Draw(IRenderQueue& renderQueue, RenderingFlags renderingFlags = RenderingFlags::None)override;
	virtual void Print(HeapString& ioStr, uint level)override;

private:
	Share<IEffect> mEffect;
	
	List<MaterialRenderGroup*> mGroups;
};


MEDUSA_END;