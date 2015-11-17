// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/BaseResourceFactory.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

class MaterialFactory :public Singleton<MaterialFactory>, public BaseResourceFactory<IMaterial>
{
	friend class Singleton<MaterialFactory>;
public:
	MaterialFactory();
	~MaterialFactory();
public:
	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	IMaterial* Create(const FileIdRef& fileId, ITexture* texture, ResourceShareType shareType = ResourceShareType::Share);
	IMaterial* Create(const FileIdRef& fileId, StringRef samplerName = StringRef::Empty, ResourceShareType shareType = ResourceShareType::Share);
	IMaterial* Create(const FileIdRef& fileId, const FileMapOrderItem& orderItem,StringRef samplerName = StringRef::Empty, ResourceShareType shareType = ResourceShareType::Share);


	IMaterial* Create(const FileIdRef& fileId, IImage* image, StringRef samplerName = StringRef::Empty, GraphicsTextureUnits unit = GraphicsTextureUnits::Texture0, ResourceShareType shareType = ResourceShareType::Share);

	IMaterial* CreateEmpty(const FileIdRef& fileId, ResourceShareType shareType = ResourceShareType::Share);
};

MEDUSA_END;