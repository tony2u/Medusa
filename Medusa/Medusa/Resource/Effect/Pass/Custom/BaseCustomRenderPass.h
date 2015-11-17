// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/Pass/IRenderPass.h"

MEDUSA_BEGIN;

class BaseCustomRenderPass:public IRenderPass
{
public:
	BaseCustomRenderPass(const FileIdRef& fileId,int index=0);
	virtual ~BaseCustomRenderPass();
	virtual bool IsCustom()const{return true;}

	void UpdateShaderVariables(RenderingStep step);
	void Validate();
	void Invalidate();
};

MEDUSA_END;