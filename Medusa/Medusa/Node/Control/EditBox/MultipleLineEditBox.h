// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "BaseMultipleLineEditBox.h"

MEDUSA_BEGIN;

class MultipleLineEditBox :public BaseMultipleLineEditBox
{
	MEDUSA_DECLARE_RTTI;

public:
	MultipleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	virtual ~MultipleLineEditBox(void);
};

MEDUSA_END;
