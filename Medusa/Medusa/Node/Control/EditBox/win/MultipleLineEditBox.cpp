// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Control/EditBox/MultipleLineEditBox.h"

MEDUSA_BEGIN;


MultipleLineEditBox::MultipleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text /*= WStringRef::Empty*/, Alignment alignment /*= Alignment::LeftBottom*/)
	:BaseMultipleLineEditBox(name,size, fontId, text, alignment)
{

}

MultipleLineEditBox::~MultipleLineEditBox( void )
{

}

MEDUSA_IMPLEMENT_RTTI(MultipleLineEditBox, BaseMultipleLineEditBox);

MEDUSA_END;
