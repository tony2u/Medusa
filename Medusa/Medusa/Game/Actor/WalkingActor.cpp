// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "WalkingActor.h"
#include "Node/NodeFactory.h"
#include "Node/Component/Movement/LinearMovementComponent.h"

MEDUSA_BEGIN;

WalkingActor::~WalkingActor( void )
{

}

bool WalkingActor::Initialize()
{
	mMovementComponent = AddComponent<LinearMovementComponent>();


	return true;
}

MEDUSA_IMPLEMENT_NODE(WalkingActor);
MEDUSA_END;
