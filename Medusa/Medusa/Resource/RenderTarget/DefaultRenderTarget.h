// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/GraphicsTypes.h"
#include "Resource/RenderTarget/IRenderTarget.h"

MEDUSA_BEGIN;
class DefaultRenderTarget:public IRenderTarget
{
public:
	DefaultRenderTarget(const FileIdRef& fileId);
	virtual ~DefaultRenderTarget();
	virtual int ZOrder() const{return 0;}
};


MEDUSA_END;