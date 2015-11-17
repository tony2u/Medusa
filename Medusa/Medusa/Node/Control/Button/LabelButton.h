// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "IButton.h"

MEDUSA_BEGIN;

class LabelButton :public IButton
{
	MEDUSA_DECLARE_RTTI;
public:
	LabelButton(ILabel* label, StringRef name=StringRef::Empty);
	virtual ~LabelButton(void);
	virtual bool Initialize() override;

	ILabel* Label() const { return mLabel; }
	void SetLabel(ILabel* val) { mLabel = val; }
protected:
	ILabel* mLabel;
	
};

MEDUSA_END;
