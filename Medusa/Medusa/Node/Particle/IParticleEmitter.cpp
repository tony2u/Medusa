// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IParticleEmitter.h"

MEDUSA_BEGIN;

IParticleEmitter::IParticleEmitter(StringRef name/*=StringRef::Empty*/):INode(name)
{
}


IParticleEmitter::~IParticleEmitter(void)
{
}

bool IParticleEmitter::Initialize()
{
	return true;
}


MEDUSA_END;
