// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseSingleLineEditBox.h"

MEDUSA_BEGIN;

class SingleLineEditBox :public BaseSingleLineEditBox
{
	MEDUSA_NODE(SingleLineEditBox,BaseSingleLineEditBox);

public:
	SingleLineEditBox(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);

	SingleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	virtual ~SingleLineEditBox(void);
};

MEDUSA_END;
