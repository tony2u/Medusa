// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Light/ILight.h"

MEDUSA_BEGIN;

class DirectionalLight:public ILight
{
public:
	DirectionalLight(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~DirectionalLight(void){}

	virtual GraphicsLightType LightType()const{return GraphicsLightType::Directional;}
};

MEDUSA_END;
