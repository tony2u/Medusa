// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseMultipleLineEditBox.h"

MEDUSA_BEGIN;

class MultipleLineEditBox :public BaseMultipleLineEditBox
{
	MEDUSA_NODE(MultipleLineEditBox,BaseMultipleLineEditBox);
public:
	MultipleLineEditBox(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	MultipleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	virtual ~MultipleLineEditBox(void);
};
MEDUSA_ENABLE_STATIC_CONSTRUCTOR(MultipleLineEditBox);

MEDUSA_END;
