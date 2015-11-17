// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledImageLayer.h"
#include "TiledImage.h"


MEDUSA_BEGIN;

TiledImageLayer::TiledImageLayer()
	:mImage(nullptr)
{
}

TiledImageLayer::~TiledImageLayer()
{
	SAFE_DELETE(mImage);
}


void TiledImageLayer::SetImage(TiledImage* val)
{
	SAFE_ASSIGN(mImage, val);
}

MEDUSA_END;

