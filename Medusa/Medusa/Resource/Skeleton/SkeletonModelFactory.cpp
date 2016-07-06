// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "SkeletonModelFactory.h"
#include "SpineSkeletonModel.h"
#include "Application/Application.h"

MEDUSA_BEGIN;

SkeletonModelFactory::SkeletonModelFactory()
{

}

SkeletonModelFactory::~SkeletonModelFactory()
{

}

bool SkeletonModelFactory::Initialize()
{
	return true;
}

bool SkeletonModelFactory::Uninitialize()
{
	Clear();
	return true;
}

Share<SpineSkeletonModel> SkeletonModelFactory::CreateSpineFromJson(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId, bool isPreCalculated/*=false*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	if (shareType!=ResourceShareType::None)
	{
		auto val = Find(skeletonfileId).CastPtr<SpineSkeletonModel>();
		RETURN_SELF_IF_NOT_NULL(val);
	}

	Share<SpineSkeletonModel> model = SpineSkeletonModel::CreateFromJsonFile(skeletonfileId, atlasFileId);
	RETURN_NULL_IF_NULL(model);
	if (isPreCalculated)
	{
		model->PreCalculate(Application::Instance().FPS());
	}

	Add(model, shareType);

	return model;
}

Share<SpineSkeletonModel> SkeletonModelFactory::CreateSpineFromJson(const FileIdRef& name, bool isPreCalculated /*= false*/, ResourceShareType shareType /*= ResourceShareType::Share*/)
{
	FileId skeletonfileId = name;
	FileId atlasFileId = name;
	skeletonfileId.Name += ".json";
	atlasFileId.Name += ".atlas";

	return CreateSpineFromJson(skeletonfileId.ToRef(), atlasFileId.ToRef(), isPreCalculated, shareType);
}



MEDUSA_END;