// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Model/Font/BaseFontModel.h"

MEDUSA_BEGIN;



class SingleLineFontModel:public BaseFontModel
{
public:
	SingleLineFontModel(const Share<IFont>& font,Alignment alignment=Alignment::LeftBottom,Size2U restrictSize=Size2U::Zero);
	virtual ~SingleLineFontModel(void);


	virtual void SetText(StringRef text);
	virtual void SetText(WStringRef text);

};

MEDUSA_END;