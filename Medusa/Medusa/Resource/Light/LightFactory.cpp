// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "LightFactory.h"
#include "Resource/Light/DirectionalLight.h"
#include "Resource/Light/SpotLight.h"
#include "Resource/Model/ModelFactory.h"
#include "Resource/Model/Scene/BaseSceneModel.h"
#include "Core/Log/Log.h"

MEDUSA_BEGIN;

LightFactory::LightFactory()
{

}

LightFactory::~LightFactory()
{
	
}

bool LightFactory::Initialize()
{
	return true;
}

bool LightFactory::Uninitialize()
{
	Clear();
	return true;
}



ILight* LightFactory::CreateLightFromModel( const FileIdRef& fileId,const FileIdRef& modelFileId,bool setDefault/*=true*/,bool enabled/*=true*/ ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	ILight* light= Find(fileId);
	RETURN_SELF_IF_NOT_NULL(light);

	BaseSceneModel* model=(BaseSceneModel*)ModelFactory::Instance().Create(modelFileId);
	if (model!=nullptr)
	{
		light=model->CreateLight(fileId);
		Add(light, shareType);
	}


	if (light!=nullptr)
	{
		light->SetIsEnabled(enabled);
	}

	if(setDefault)
	{
		mCurrentLight=light;
	}
	return light;
}


DirectionalLight* LightFactory::CreateDirectionalLight( const FileIdRef& fileId,bool setDefault/*=true*/,bool enabled/*=true*/ ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	DirectionalLight* light= (DirectionalLight*)Find(fileId);
	RETURN_SELF_IF_NOT_NULL(light);

	if (light!=nullptr&&light->LightType()!=GraphicsLightType::Directional)
	{
		Log::FormatError("Error light type by {}",fileId.Name.c_str());
		return nullptr;
	}


	if (light==nullptr)
	{
		light=new DirectionalLight(fileId);
		Add(light, shareType);
	}

	if (light!=nullptr)
	{
		light->SetIsEnabled(enabled);
	}

	if(setDefault)
	{
		mCurrentLight=light;
	}
	return (DirectionalLight*)light;
}

SpotLight* LightFactory::CreateSpotLight( const FileIdRef& fileId,bool setDefault/*=true*/,bool enabled/*=true*/ ,ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	SpotLight* light=(SpotLight*)Find(fileId);
	RETURN_SELF_IF_NOT_NULL(light);

	if (light!=nullptr&&light->LightType()!=GraphicsLightType::Spot)
	{
		Log::FormatError("Error light type by {}",fileId.Name.c_str());
		return nullptr;
	}


	if (light==nullptr)
	{
		light=new SpotLight(fileId);
		Add(light, shareType);
	}

	if (light!=nullptr)
	{
		light->SetIsEnabled(enabled);
	}

	if(setDefault)
	{
		mCurrentLight=light;
	}
	return (SpotLight*)light;
}


ILight* LightFactory::SetCurrentLight( const FileIdRef& fileId )
{
	ILight* light= Find(fileId);
	if (light!=nullptr)
	{
		mCurrentLight=light;
	}

	return light;
}


MEDUSA_END;