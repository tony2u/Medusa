// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Sprite.h"

MEDUSA_BEGIN;


Sprite::Sprite( StringRef name/*=StringRef::Empty*/ ) :INode(name)
{

}

Sprite::~Sprite( void )
{

}

bool Sprite::Initialize()
{
	return true;
}

MEDUSA_IMPLEMENT_RTTI(Sprite, INode);

MEDUSA_END;
