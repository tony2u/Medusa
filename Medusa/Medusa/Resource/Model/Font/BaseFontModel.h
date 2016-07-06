// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/BaseMultipleModel.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Font/IFont.h"
#include "Geometry/Color4.h"
#include "Resource/Model/Mesh/Font/FntTextMesh.h"

MEDUSA_BEGIN;



class BaseFontModel:public BaseMultipleModel<IMaterial>
{
public:
	BaseFontModel(const Share<IFont>& font,Alignment alignment=Alignment::LeftBottom,Size2U restrictSize=Size2U::Zero);
	virtual ~BaseFontModel(void);
public:
	virtual bool Initialize(ModelLoadingOptions loadingOptions=ModelLoadingOptions::None);
	const Share<IFont>& Font() const { return mFont; }
	Alignment GetAlignment() const { return mAlignment; }
	const Color4F& Color() const { return mColor; }
	const Size2U& RestrictSize() const { return mRestrictSize; }
	WStringRef Text() const { return mText; }

	virtual void SetText(StringRef text)=0;
	virtual void SetText(WStringRef text)=0;

protected:
	void ResetCachedMeshes();
protected:
	Share<IFont> mFont;
	WHeapString mText;
	Alignment mAlignment;
	Color4F mColor;
	Size2U mRestrictSize;
	//cache font char mesh
	Dictionary<Share<IMaterial>,Share<FntTextMesh>> mCachesMeshes;

	//cache material
};

MEDUSA_END;