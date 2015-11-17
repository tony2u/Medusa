// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ISkeletonModel.h"

MEDUSA_BEGIN;

class SpineSkeletonModel :public ISkeletonModel
{
public:
	static SpineSkeletonModel* CreateFromJsonFile(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId);
	static SpineSkeletonModel* CreateFromJsonData(const FileIdRef& fileId, const MemoryByteData& skeletonFileData, TextureAtlas* atlas);

	static void ParseCurve(const rapidjson::Value &frame, Math::TweenType& outTweenType, List<float>& outTweenArgs);

public:
	SpineSkeletonModel(const FileIdRef& fileId);

	virtual ~SpineSkeletonModel(void);

	virtual bool Initialize()override;

	size_t GetAtlasPagesCount()const;
	bool HasSingleAtlasPage()const;
	TextureGeneralMesh* CreateMesh(size_t atlasPageIndex = 0);

	bool CheckBlendFunc(bool& outIsAdditiveBlending)const;
};

MEDUSA_END;
