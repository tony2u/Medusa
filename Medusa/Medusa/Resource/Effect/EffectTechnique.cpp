// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/EffectTechnique.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/Pass/Program/BaseProgramRenderPass.h"

MEDUSA_BEGIN;

EffectTechnique::EffectTechnique(StringRef name):mName(name)
{
	mGroup=nullptr;
}

EffectTechnique::~EffectTechnique()
{
	Uninitialize();
}

void EffectTechnique::Apply()
{
	
}


void EffectTechnique::Restore()
{
	
}

bool EffectTechnique::Initialize()
{
	return true;	
}

bool EffectTechnique::Uninitialize()
{
	SAFE_RELEASE_COLLECTION(mRenderPasses);
	return true;
}


void EffectTechnique::AddPass( IRenderPass* pass )
{
	IRenderPass* result=GetPassByName(pass->Name());
	if (result!=nullptr)
	{
		MEDUSA_ASSERT_FAILED("Duplicate add pass");
	}

	if (!pass->Name().IsEmpty())
	{
		mRenderPassDict.Add(pass->Name(),pass);
	}
	mRenderPasses.Add(pass);
	pass->Retain();
	pass->SetTechnique(this);

	UpdateFlags();
}

IRenderPass* EffectTechnique::RemovePass( StringRef name )
{
	IRenderPass* result=GetPassByName(name);
	if (result!=nullptr)
	{
		mRenderPasses.Remove(result);
		mRenderPassDict.RemoveKey(name);
		result->SetTechnique(nullptr);
		bool isValid=result->Release();
		UpdateFlags();
        return isValid?result:nullptr;
	}
	return result;
}



IRenderPass* EffectTechnique::GetPassByIndex( uint index )
{
	FOR_EACH_COLLECTION(i,mRenderPasses)
	{
		IRenderPass* pass=*i;
		if (pass->GetIndex()==index)
		{
			return pass;
		}
	}

	return nullptr;
}

IRenderPass* EffectTechnique::GetPassByName( StringRef name )
{
	return mRenderPassDict.GetOptional(name,nullptr);
}

void EffectTechnique::UpdateFlags()
{
	mFlags=RenderPassFlags::None;
	FOR_EACH_COLLECTION(i,mRenderPasses)
	{
		const IRenderPass* pass=*i;
		MEDUSA_FLAG_ADD(mFlags,pass->Flags());
	}
}

IRenderPass* EffectTechnique::GetFirstPass() const
{
	return mRenderPasses.First();
}


MEDUSA_END;