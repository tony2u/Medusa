// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IShape.h"

MEDUSA_BEGIN;


IShape::IShape( StringRef name/*=StringRef::Empty*/ ) :INode(name)
{

}

IShape::~IShape( void )
{

}

bool IShape::Initialize()
{
	return true;
}

MEDUSA_IMPLEMENT_RTTI(IShape, INode);
MEDUSA_END;
