// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "IView.h"

MEDUSA_BEGIN;

IView::IView(StringRef name/*=StringRef::Empty*/) :mName(name), mParent(nullptr), mSize(Size2F::Zero)
{
}

IView::~IView(void)
{
}



MEDUSA_END;
