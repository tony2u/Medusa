// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ITiledLayer.h"
#include "TiledMap.h"
#include "Node/Layer/NormalLayer.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"
#include "TiledDefines.h"

MEDUSA_BEGIN;

ITiledLayer::ITiledLayer()
	: mPosition(Point2I::Zero),
	mSize(Size2I::Zero),
	mOpacity(1.f),
	mIsVisible(true),
	mZOrder(0),
	mInstantiateMode(InstantiateMode::Sprite),
	mRunningState(RunningState::None)
{
	mInstantiateLayer = NormalLayer::ClassNameStatic();
}

ITiledLayer::~ITiledLayer()
{
}


bool ITiledLayer::Parse(const pugi::xml_node& node)
{
	StringRef name = node.attribute("name").as_string();
	SetName(name);

	Point2I pos;
	pos.X = node.attribute("offsetx").as_int(0);
	pos.Y = node.attribute("offsety").as_int(0);
	SetPosition(pos);

	Size2I size;
	size.Width = node.attribute("width").as_int(0);
	size.Height = node.attribute("height").as_int(0);
	SetSize(size);

	float opacity = node.attribute("opacity").as_float(1.f);
	SetOpacity(opacity);

	bool isVisible = node.attribute("visible").as_int(1) != 0;
	SetVisible(isVisible);

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		TiledMap::ParseProperties(propertiesNode, MutableProperties());
	}


	StringRef renderingModeStr = mProperties.GetString(TiledMapProperties::InstantiateMode);
	if (renderingModeStr == TiledMapPropertyValues::Mesh)
	{
		mInstantiateMode = InstantiateMode::Mesh;
	}
	else if (renderingModeStr == TiledMapPropertyValues::Sprite)
	{
		mInstantiateMode = InstantiateMode::Sprite;
	}

	StringRef runningModeStr = mProperties.GetString(TiledMapProperties::State);
	if (runningModeStr == TiledMapPropertyValues::Done)
	{
		mRunningState = RunningState::Done;
	}
	else if (runningModeStr == TiledMapPropertyValues::Running)
	{
		mRunningState = RunningState::Running;
	}
	else if (runningModeStr == TiledMapPropertyValues::Paused)
	{
		mRunningState = RunningState::Paused;
	}
	
	mInstantiateLayer = mProperties.GetString(TiledMapProperties::InstantiateLayer);
	mCollisionEnabled = mProperties.GetOptionalT(TiledMapProperties::EnableCollision, true);
	mInputEnabled = mProperties.GetOptionalT(TiledMapProperties::EnableInput, false);

	mScriptFile = mProperties.GetString(TiledMapProperties::ScriptFile);

	return true;
}

MEDUSA_END;