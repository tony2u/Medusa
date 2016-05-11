// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/EffectTechniqueGroup.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/EffectTechnique.h"
#include "Resource/Effect/IEffect.h"

MEDUSA_BEGIN;

EffectTechniqueGroup::EffectTechniqueGroup(StringRef name):mName(name)
{
	mEffect=nullptr;
	mCurrentTechnique=nullptr;
}

EffectTechniqueGroup::~EffectTechniqueGroup()
{
	Uninitialize();
	
}

void EffectTechniqueGroup::Apply()
{
	
}


void EffectTechniqueGroup::Restore()
{
	
}

bool EffectTechniqueGroup::Initialize()
{
	return true;
}

bool EffectTechniqueGroup::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mTechniques);
	mTechniqueDict.Clear();
	return true;
}

EffectTechnique* EffectTechniqueGroup::CreateDefaultTechnique(bool setCurrent/*=true*/)
{
	return CreateTechnique(mDefaultTechniqueName,setCurrent);
}

EffectTechnique* EffectTechniqueGroup::CreateTechnique( StringRef name ,bool setCurrent/*=true*/)
{
	EffectTechnique* result=GetTechniqueByName(name);
	if (result!=nullptr)
	{
		return result;
	}

	result=new EffectTechnique(name);
	mTechniqueDict.Add(name,result);
	mTechniques.Add(result);
	result->SetGroup(this);

	if (setCurrent)
	{
		mCurrentTechnique=result;
	}

	return result;
}

bool EffectTechniqueGroup::RemoveTechnique( StringRef name )
{
	EffectTechnique* result=GetTechniqueByName(name);
	if (result!=nullptr)
	{
		mTechniques.Remove(result);
		mTechniqueDict.RemoveKey(name);
		result->SetGroup(nullptr);
		if (result==mCurrentTechnique)
		{
			mCurrentTechnique=nullptr;
		}
		SAFE_DELETE(result);
		return true;
	}
	return false;
}

void EffectTechniqueGroup::SetCurrentTechnique( StringRef name )
{
	mCurrentTechnique=GetTechniqueByName(name);
}


EffectTechnique* EffectTechniqueGroup::GetTechniqueByIndex( uint index )
{
	return mTechniques[index];
}

EffectTechnique* EffectTechniqueGroup::GetTechniqueByName( StringRef name )
{
	return mTechniqueDict.GetOptional(name,nullptr);
}

void EffectTechniqueGroup::SetEffect( IEffect* val )
{
	
}


const StringRef EffectTechniqueGroup::mDefaultTechniqueName="Default";

MEDUSA_END;