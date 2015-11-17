// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Effect/EffectTechniqueGroup.h"
#include "Resource/Effect/EffectTechnique.h"
#include "Core/Pattern/AutoIncreaseId.h"

MEDUSA_BEGIN;

IEffect::IEffect(const FileIdRef& fileId/*=FileId::Empty*/):IResource(fileId)
{
	mId = AutoIncreaseId<IEffect>::New();

	mCurrentTechniqueGroup=nullptr;
}

IEffect::~IEffect()
{
	Uninitialize();
}

void IEffect::Apply()
{
	
}


void IEffect::Restore()
{
	
}

bool IEffect::Initialize()
{
 return true;
}

bool IEffect::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mTechniqueGroups);
	mTechniqueGroupDict.Clear();
	return true;
}


EffectTechniqueGroup* IEffect::CreateDefaultGroup(bool setCurrent/*=true*/)
{
	return CreateGroup(mDefaultTechniqueGroupName,setCurrent);
}

EffectTechniqueGroup* IEffect::CreateGroup( StringRef name ,bool setCurrent/*=true*/)
{
	EffectTechniqueGroup* group=GetGroupByName(name);
	if (group!=nullptr)
	{
		return group;
	}

	group=new EffectTechniqueGroup(name);
	mTechniqueGroupDict.Add(name,group);
	mTechniqueGroups.Append(group);
	group->SetEffect(this);

	if (setCurrent)
	{
		mCurrentTechniqueGroup=group;
	}
	return group;
}


bool IEffect::RemoveGroup( StringRef name )
{
	EffectTechniqueGroup* group=GetGroupByName(name);
	if (group!=nullptr)
	{
		mTechniqueGroups.Remove(group);
		mTechniqueGroupDict.RemoveKey(name);
		group->SetEffect(nullptr);
		if (group==mCurrentTechniqueGroup)
		{
			mCurrentTechniqueGroup=nullptr;
		}
		SAFE_DELETE(group);
		return true;
	}

	return false;
}

void IEffect::SetCurrentTechniqueGroup( StringRef name )
{
	mCurrentTechniqueGroup=GetGroupByName(name);
}

EffectTechniqueGroup* IEffect::GetGroupByIndex( uint index )
{
	return mTechniqueGroups[index];
}

EffectTechniqueGroup* IEffect::GetGroupByName( StringRef name )
{
	return mTechniqueGroupDict.TryGetValueWithFailed(name,nullptr);
}

//
//ShaderConstant* IEffect::BindUniformBeforeLink( int index,StringRef name )
//{
//	MEDUSA_ASSERT_NOT_IMPLEMENT();
//	if (mIsLinked)
//	{
//		MEDUSA_ASSERT_FAILED("Cannot bind after link");
//	}
//
//	ShaderConstant** result=mUniforms.TryGetValue(name);
//	if (result==nullptr)
//	{
//		Render::Instance().BindUniformLocation(mEffect,index,name);
//		ShaderConstant* result2=new ShaderConstant(this,index,name);
//		mUniforms.Add(name,result2);
//		return result2;
//	}
//	return *result;
//}

const StringRef IEffect::mDefaultTechniqueGroupName="Default";

MEDUSA_END;