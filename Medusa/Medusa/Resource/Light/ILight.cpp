// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ILight.h"
#include "Graphics/Render/Render.h"

MEDUSA_BEGIN;


ILight::ILight( const FileIdRef& fileId/*=FileId::Empty*/ ) :
	IResource(fileId),
	mAmbientColor(Color3F::Black),
	mDiffuseColor(Color3F::Black),
	mSpecularColor(Color3F::Black)
{
	
}


MEDUSA_END;
