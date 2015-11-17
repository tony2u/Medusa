// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/String/StringRef.h"
#include "Graphics/GraphicsTypes.h"
MEDUSA_BEGIN;

class ViewFactory
{
public:
	static BaseRenderView* CreateGLView(StringRef name = StringRef::Empty);

};

MEDUSA_END;

