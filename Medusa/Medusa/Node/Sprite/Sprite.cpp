// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Sprite.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

Sprite::~Sprite( void )
{

}

bool Sprite::Initialize()
{
	return true;
}

MEDUSA_IMPLEMENT_NODE(Sprite);

MEDUSA_END;
