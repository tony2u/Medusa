// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Effect/Shader/Vertex/BaseVertexShader.h"
#include "Rendering/RenderingContext.h"
#include "Resource/Camera/Camera.h"
#include "Resource/Effect/IEffect.h"
#include "Rendering/Batch/IRenderBatch.h"
#include "Resource/ResourceNames.h"

MEDUSA_BEGIN;

BaseVertexShader::BaseVertexShader(const FileIdRef& fileId):IShader(fileId)
{

}

BaseVertexShader::~BaseVertexShader()
{
}

bool BaseVertexShader::Compare( const IShader& shader ) const
{
	return true;
}


MEDUSA_END;