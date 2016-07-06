// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/Font/BaseFontModel.h"

MEDUSA_BEGIN;



class MultipleLineFontModel:public BaseFontModel
{
public:
	MultipleLineFontModel(const Share<IFont>& font,Alignment alignment=Alignment::LeftBottom,Size2U restrictSize=Size2U::Zero);
	virtual ~MultipleLineFontModel(void);

	virtual void SetText(StringRef text);
	virtual void SetText(WStringRef text);

};

MEDUSA_END;