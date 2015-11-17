// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "Resource/Effect/Shader/IShader.h"
MEDUSA_BEGIN;

class BasePixelShader:public IShader
{
public:
	BasePixelShader(const FileIdRef& fileId);
	virtual ~BasePixelShader();
	virtual GraphicsShaderType ShaderType()const{return GraphicsShaderType::PixelShader;}

	virtual bool Compare(const IShader& shader)const;

};


MEDUSA_END;