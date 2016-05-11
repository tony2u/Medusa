// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Core/Collection/Dictionary.h"
#include "Core/String/HeapString.h"
#include "Core/Collection/SortedList.h"
#include "Graphics/GraphicsTypes.h"
#include "Graphics/State/RenderStateSet.h"
#include "Core/Pattern/Delegate.h"
#include "Resource/IResource.h"
#include "Rendering/RenderingTypes.h"
MEDUSA_BEGIN;


class IRenderPass:public RenderStateSet,public IResource
{
public:
	const static StringRef DefaultRenderPassName;
public:
	IRenderPass(const FileIdRef& fileId = FileIdRef::Empty, uint index = 0);
	virtual ~IRenderPass();
	virtual ResourceType Type()const{return ResourceType::RenderPass;}
	static ResourceType ClassGetResourceType(){return ResourceType::RenderPass;}

	bool operator<(const IRenderPass& pass)const{return mIndex<pass.GetIndex();}

	uint GetIndex() const { return mIndex; }

	EffectTechnique* Technique() { return mTechnique; }
	void SetTechnique(EffectTechnique* val) { mTechnique = val; }

	virtual void Apply();
	virtual void Restore();
	virtual bool IsCustom()const=0;

	virtual bool Initialize(){return true;}
	
	RenderPassFlags Flags() const { return mFlags; }

	virtual void UpdateShaderUniforms(RenderingStep step)=0;
	virtual void Validate()=0;
	virtual void Invalidate()=0;

	virtual bool Draw(IRenderQueue& renderQueue,RenderingFlags renderingFlags) { return true; }
protected:
	uint mIndex;
	EffectTechnique* mTechnique;
	RenderPassFlags mFlags;
};

MEDUSA_END;