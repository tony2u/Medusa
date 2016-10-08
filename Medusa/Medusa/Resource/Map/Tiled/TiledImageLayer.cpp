// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "TiledImageLayer.h"
#include "TiledImage.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"


MEDUSA_BEGIN;

TiledImageLayer::TiledImageLayer()
{
}

TiledImageLayer::~TiledImageLayer()
{
	SAFE_DELETE(mImage);
}


bool TiledImageLayer::Parse(const pugi::xml_node& node)
{
	RETURN_FALSE_IF_FALSE(ITiledLayer::Parse(node));
	pugi::xml_node imageNode = node.child("image");
	if (!imageNode.empty())
	{
		TiledImage* image = new TiledImage();
		image->Parse(imageNode);
		SetImage(image);
	}
	return true;
}

void TiledImageLayer::SetImage(TiledImage* val)
{
	SAFE_ASSIGN(mImage, val);
	if (mImage!=nullptr)
	{
		mImage->SetLayer(this);
	}
}

MEDUSA_END;

