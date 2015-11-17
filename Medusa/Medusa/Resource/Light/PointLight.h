// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Light/ILight.h"

MEDUSA_BEGIN;

class PointLight:public ILight
{
public:
	PointLight(const FileIdRef& fileId=FileIdRef::Empty);
	virtual ~PointLight(void){}

	virtual GraphicsLightType LightType()const{return GraphicsLightType::Point;}
};

MEDUSA_END;
