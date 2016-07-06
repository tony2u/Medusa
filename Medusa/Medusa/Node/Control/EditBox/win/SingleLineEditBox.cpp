// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Control/EditBox/SingleLineEditBox.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;


SingleLineEditBox::SingleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text /*= WStringRef::Empty*/, Alignment alignment /*= Alignment::LeftBottom*/)
	:BaseSingleLineEditBox(name,size, fontId, text, alignment)
{
}

SingleLineEditBox::SingleLineEditBox(const StringRef& name /*= StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	: BaseSingleLineEditBox(name, e)
{

}

SingleLineEditBox::~SingleLineEditBox(void)
{

}
MEDUSA_IMPLEMENT_NODE(SingleLineEditBox);

MEDUSA_END;
