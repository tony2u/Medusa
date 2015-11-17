// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Graphics/State/IRenderState.h"


MEDUSA_BEGIN;

IRenderState::IRenderState()
{
}

IRenderState::~IRenderState()
{

}

bool IRenderState::Equals( const IRenderState& state ) const
{
	RETURN_FALSE_IF_FALSE(IsExactly(state.Class()));
	RETURN_FALSE_IF_NOT_EQUAL(HashCode(),state.HashCode());
	return true;
}


void IRenderState::OnStateChanged()
{
	OnChanged(*this);
}

MEDUSA_IMPLEMENT_RTTI_ROOT(IRenderState);

MEDUSA_END;