// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Resource/Effect/Pass/Custom/BaseCustomRenderPass.h"

MEDUSA_BEGIN;

class RenderToTextureRenderPass:public BaseCustomRenderPass
{
public:
	RenderToTextureRenderPass(const FileIdRef& fileId);
	virtual ~RenderToTextureRenderPass();
	virtual void Apply();
	virtual void Restore();
	virtual bool Initialize();
	virtual bool Uninitialize();

};

MEDUSA_END;