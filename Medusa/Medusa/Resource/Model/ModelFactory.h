// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Core/Pattern/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include "Resource/Model/IModel.h"
#include "Resource/BaseResourceFactory.h"
MEDUSA_BEGIN;

class ModelFactory:public Singleton<ModelFactory>,public BaseResourceFactory<IModel>
{
	friend class Singleton<ModelFactory>;
public:
	ModelFactory();
	~ModelFactory();
public:
	virtual StringRef Name()const override { return "ModelFactory"; }

	virtual bool Initialize();
	virtual bool Uninitialize();
public:
	Share<QuadModel> CreateQuad(const FileIdRef& fileId,ResourceShareType shareType = ResourceShareType::Share);
	Share<SingleLineFontModel> CreateSingleLineFontModel(const FontId& fontId,StringRef text,Alignment alignment=Alignment::LeftBottom,Size2U restrictSize=Size2U::Zero);
	Share<MultipleLineFontModel> CreateMultipleLineFontModel(const FontId& fontId,StringRef text,Alignment alignment=Alignment::LeftBottom,Size2U restrictSize=Size2U::Zero);

	Share<IModel> Create(const FileIdRef& fileId,ModelLoadingOptions loadingOptions=ModelLoadingOptions::None,ResourceShareType shareType = ResourceShareType::Share);
};

MEDUSA_END;