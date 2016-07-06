// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IEditBox.h"

MEDUSA_BEGIN;

class BaseMultipleLineEditBox :public IEditBox
{
	MEDUSA_RTTI(BaseMultipleLineEditBox,IEditBox);
public:
	BaseMultipleLineEditBox(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	BaseMultipleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	virtual ~BaseMultipleLineEditBox(void);
};

MEDUSA_END;
