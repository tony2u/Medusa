// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "Resource/Effect/Shader/IShader.h"
MEDUSA_BEGIN;

class BaseVertexShader:public IShader
{
public:
	BaseVertexShader(const FileIdRef& fileId);
	virtual ~BaseVertexShader();
	virtual GraphicsShaderType ShaderType()const{return GraphicsShaderType::VertexShader;}

	virtual bool Compare(const IShader& shader)const;

};


MEDUSA_END;