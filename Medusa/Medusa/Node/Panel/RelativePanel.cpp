// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "RelativePanel.h"

MEDUSA_BEGIN;

RelativePanel::RelativePanel(StringRef name/*=StringRef::Empty*/):IPanel(name)
{
}

RelativePanel::~RelativePanel(void)
{

}

MEDUSA_IMPLEMENT_RTTI(RelativePanel, IPanel);


MEDUSA_END;
