// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IEditBox.h"
#include "Resource/Font/FontId.h"

MEDUSA_BEGIN;

class BaseSingleLineEditBox :public IEditBox
{
	MEDUSA_RTTI(BaseSingleLineEditBox,IEditBox);

public:
	BaseSingleLineEditBox(const StringRef& name = StringRef::Empty, const IEventArg& e = IEventArg::Empty);
	BaseSingleLineEditBox(StringRef name, const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	virtual ~BaseSingleLineEditBox(void);
public:
	virtual bool Initialize() override;
	void SetFontId(const FontId& val);
};

MEDUSA_END;
