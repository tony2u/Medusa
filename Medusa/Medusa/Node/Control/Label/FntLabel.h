// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "ILabel.h"

MEDUSA_BEGIN;

class FntLabel :public ILabel
{
	MEDUSA_DECLARE_RTTI;
public:
	FntLabel(StringRef name, IFont* font, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isMultipleLine = true, bool isStatic = false);
	virtual ~FntLabel(void);

	virtual BaseFontMesh* CreateFontMesh(IMaterial* material, bool isStatic = false)override;

	virtual Point2F GetCharPosition(uint charIndex)const override;
	virtual Point2F GetCursorPosition(uint charIndex)const override;
	virtual uint FindCharIndex(const Point2F& touchPosition, Point2F& outCharPosition)const override;
	virtual void UpdateMesh()override;

protected:
	virtual void OnUpdateFont() override;

	void CreateMesh();

protected:
	List<BaseFontMesh*> mInternalMeshes;
	List<IMaterial*> mInternalMaterials;

};

MEDUSA_END;
