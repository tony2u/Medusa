// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "IProgressBar.h"

MEDUSA_BEGIN;


class ShapeProgressBar :public IProgressBar
{
	MEDUSA_DECLARE_RTTI;

public:
	ShapeProgressBar(StringRef name, ProgressType progressType, const Size2F& size, const Color4F& color, float percent=1.f);
	virtual ~ShapeProgressBar(void);
	virtual bool Initialize()override;
protected:
	virtual void OnUpdateMesh(bool isProgressTypeChanged=false)override;
protected:
	Array<Point3F,4> mVertices; //initial vertext

};

MEDUSA_END;
