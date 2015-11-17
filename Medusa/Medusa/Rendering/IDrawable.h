// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "Graphics/Render/Render.h"

MEDUSA_BEGIN;

/*

nodes->get model->get meshes->pack to batch mesh
*/
struct IDrawable
{
public:
	IDrawable(){}
	virtual ~IDrawable(){}
public:
	virtual void Draw()=0;
};


MEDUSA_END;