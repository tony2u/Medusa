// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Skeleton/ISkeletonModel.h"
#include "Resource/Skeleton/SpineSkeletonModel.h"

MEDUSA_BEGIN;

class SkeletonModelFactory :public Singleton<SkeletonModelFactory>, public BaseResourceFactory < ISkeletonModel >
{
	friend class Singleton < SkeletonModelFactory > ;
public:
	SkeletonModelFactory();
	~SkeletonModelFactory();
public:
	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
public:
	Share<SpineSkeletonModel> CreateSpineFromJson(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId, bool isPreCalculated = false, ResourceShareType shareType = ResourceShareType::Share);
	Share<SpineSkeletonModel> CreateSpineFromJson(const FileIdRef& name, bool isPreCalculated = false, ResourceShareType shareType = ResourceShareType::Share);

};

MEDUSA_END;