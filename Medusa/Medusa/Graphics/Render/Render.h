// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Graphics/Render/IRender.h"

MEDUSA_BEGIN;

class Render
{
	Render();
	~Render();
public:
	static IRender& Instance()
	{
		return *mRender;
	}
	static bool SetupRender(GraphicsAPI api);
	static bool DestoryRender();
private:
	IRender& GetRender() { return *mRender; }
private:
	static IRender* mRender;
};

MEDUSA_END;