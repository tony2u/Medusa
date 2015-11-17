// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/SortedList.h"
#include "Core/String/HeapString.h"
#include "Resource/Effect/Pass/IRenderPass.h"
#include "Core/Pattern/IInitializable.h"


MEDUSA_BEGIN;

class EffectTechnique:public IInitializable
{
public:
	typedef SortedList<IRenderPass*,DefaultCompare<IRenderPass*>,DefaultCompareForPointer<IRenderPass> > PassCollectionType;
	EffectTechnique(StringRef name);
	virtual ~EffectTechnique();
	virtual void Apply();
	virtual void Restore();

	StringRef Name() const { return mName; }

	virtual bool Initialize();
	virtual bool Uninitialize();
	
	void AddPass(IRenderPass* pass);
	IRenderPass* RemovePass(StringRef name);
	IRenderPass* GetPassByIndex(uint index);
	IRenderPass* GetPassByName(StringRef name);
	IRenderPass* GetFirstPass()const;

	PassCollectionType& RenderPasses() { return mRenderPasses; }
	const PassCollectionType& RenderPasses() const{ return mRenderPasses; }


	EffectTechniqueGroup* Group() { return mGroup; }
	void SetGroup(EffectTechniqueGroup* val) { mGroup = val; }
	RenderPassFlags Flags() const { return mFlags; }

private:
	void UpdateFlags();
protected:
	HeapString mName;

	SortedList<IRenderPass*,DefaultCompare<IRenderPass*>,DefaultCompareForPointer<IRenderPass> > mRenderPasses;
	Dictionary<HeapString,IRenderPass*> mRenderPassDict;
	EffectTechniqueGroup* mGroup;
	RenderPassFlags mFlags;
};

MEDUSA_END;