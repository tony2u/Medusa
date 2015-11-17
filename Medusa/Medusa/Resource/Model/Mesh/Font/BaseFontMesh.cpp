// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "BaseFontMesh.h"

MEDUSA_BEGIN;


BaseFontMesh::BaseFontMesh( IEffect* effect/*=nullptr*/,IMaterial* material/*=nullptr*/,bool isStatic/*=false*/ ):IMesh(effect,material,isStatic)
{

}


BaseFontMesh::~BaseFontMesh(void)
{
}



MEDUSA_END;