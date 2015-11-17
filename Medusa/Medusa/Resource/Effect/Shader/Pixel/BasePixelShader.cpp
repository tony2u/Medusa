// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"

#include "Resource/Effect/Shader/Pixel/BasePixelShader.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Effect/Shader/Pixel/BasePixelShader.h"
#include "Resource/Effect/IEffect.h"

MEDUSA_BEGIN;

BasePixelShader::BasePixelShader(const FileIdRef& fileId):IShader(fileId)
{

}

BasePixelShader::~BasePixelShader()
{
}


bool BasePixelShader::Compare( const IShader& shader ) const
{
	return true;
}



MEDUSA_END;