// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "ITiledLayer.h"

MEDUSA_BEGIN;

class TiledImageLayer : public ITiledLayer
{
public:
	TiledImageLayer();
	~TiledImageLayer();
	virtual TiledLayerType Type()const override { return TiledLayerType::Image; }
	bool Parse(const pugi::xml_node& node);

	TiledImage* Image() const { return mImage; }
	void SetImage(TiledImage* val);
private:
	TiledImage* mImage=nullptr;
	
};

MEDUSA_END;
