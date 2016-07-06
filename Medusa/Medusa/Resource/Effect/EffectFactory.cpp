// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "EffectFactory.h"

#include "Resource/Effect/PFXEffect.h"
#include "Resource/Effect/EffectTechniqueGroup.h"
#include "Resource/Effect/EffectTechnique.h"
#include "Resource/Effect/IEffect.h"
#include "Resource/Effect/Pass/Custom/RenderToTextureRenderPass.h"
#include "Resource/Effect/Pass/RenderPassFactory.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/FileInfo.h"
#include "Resource/ResourceNames.h"

MEDUSA_BEGIN;

EffectFactory::EffectFactory()
{

}

EffectFactory::~EffectFactory()
{
}
bool EffectFactory::Initialize()
{
	return true;
}

bool EffectFactory::Uninitialize()
{
	Clear();
	return true;
}


Share<IEffect> EffectFactory::CreateFromFile( const FileIdRef& fileId ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IEffect> effect;
	if (shareType != ResourceShareType::None)
	{
		effect = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(effect);
	}
	

	switch(FileInfo::ExtractType(fileId.Name))
	{
	case FileType::pfx:
		effect=PFXEffect::CreateFromFile(fileId.Name);	//TODO:
		break;
	default:
		return nullptr;
	}

	RETURN_NULL_IF_NULL(effect);
	if (effect->Initialize())
	{
		Add(effect, shareType);
		return effect;
	}
	
	return nullptr;
}

Share<IEffect> EffectFactory::CreateEmpty( const FileIdRef& fileId ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	
	Share<IEffect> effect;
	if (shareType != ResourceShareType::None)
	{
		effect = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(effect);
	}


	effect=new IEffect(fileId);
	if(effect->Initialize())
	{
		effect->CreateDefaultGroup()->CreateDefaultTechnique();
		Add(effect, shareType);
		return effect;
	}
	
	return nullptr;
}



Share<IEffect> EffectFactory::CreateSinglePassDefault( const FileIdRef& fileId ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	return CreateSinglePass(fileId,fileId,shareType);
}

Share<IEffect> EffectFactory::CreateSinglePass( const FileIdRef& fileId,const FileIdRef& passFileId ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IEffect> effect;
	if (shareType != ResourceShareType::None)
	{
		effect = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(effect);
	}

	auto pass=RenderPassFactory::Instance().CreateRenderPass(fileId);
	if (pass!=nullptr)
	{
		return CreateSinglePass(fileId,pass,shareType);
	}
	return nullptr;
}



Share<IEffect> EffectFactory::CreateSinglePass(const FileIdRef& fileId, const Share<IRenderPass>& renderPass,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IEffect> effect;
	if (shareType != ResourceShareType::None)
	{
		effect = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(effect);
	}

	effect= CreateEmpty(fileId,shareType);
	RETURN_NULL_IF_NULL(effect);

	effect->GetGroupByIndex(0)->GetTechniqueByIndex(0)->AddPass(renderPass);
	return effect;
}

Share<IEffect> EffectFactory::CreateMultiplePasses( const FileIdRef& fileId,const List<FileIdRef>& renderPasses ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IEffect> effect;
	if (shareType != ResourceShareType::None)
	{
		effect = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(effect);
	}

	List<Share<IRenderPass>> passes;
	for(auto passFileId:renderPasses)
	{
		auto pass=RenderPassFactory::Instance().CreateRenderPass(passFileId);
		passes.Add(pass);
	}

	effect=CreateMultiplePasses(fileId,passes,shareType);
	RETURN_SELF_IF_NOT_NULL(effect);
	return nullptr;
}


Share<IEffect> EffectFactory::CreateMultiplePasses( const FileIdRef& fileId,List<Share<IRenderPass>>& renderPasses ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	Share<IEffect> effect;
	if (shareType != ResourceShareType::None)
	{
		effect = Find(fileId);
		RETURN_SELF_IF_NOT_NULL(effect);
	}


	effect= CreateEmpty(fileId,shareType);
	RETURN_NULL_IF_NULL(effect);
	EffectTechnique* technique=effect->GetGroupByIndex(0)->GetTechniqueByIndex(0);
	for(auto i:renderPasses)
	{
		technique->AddPass(i);
	}

	return effect;
}


MEDUSA_END;