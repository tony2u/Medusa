// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ITiledLayer.h"
#include "TmxTiledMap.h"
#include "Node/Layer/NormalLayer.h"
#include "CoreLib/Common/pugixml/pugixml.hpp"

MEDUSA_BEGIN;

ITiledLayer::ITiledLayer()
	: mPosition(Point2I::Zero),
	mSize(Size2I::Zero),
	mOpacity(1.f),
	mIsVisible(true),
	mZOrder(0),
	mInstantiateMode(InstantiateMode::Sprite),
	mRunningState(RunningState::Running)
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

	bool isVisible = node.attribute("visible").as_int(1)!=0;
	SetVisible(isVisible);

	pugi::xml_node propertiesNode = node.child("properties");
	if (!propertiesNode.empty())
	{
		TmxTiledMap::ParseProperties(propertiesNode, MutableProperties());
	}

	const StringRef str1 = "Instantiate";
	HeapString* renderingModeStr=mProperties.TryGetByOtherKey(str1, str1.HashCode());
	if (renderingModeStr!=nullptr)
	{
		if (*renderingModeStr=="Mesh")
		{
			mInstantiateMode = InstantiateMode::Mesh;
		}
		else if (*renderingModeStr == "Sprite")
		{
			mInstantiateMode = InstantiateMode::Sprite;
		}
	}

	const StringRef str2 = "Running";
	HeapString* runningModeStr = mProperties.TryGetByOtherKey(str2, str2.HashCode());
	if (runningModeStr != nullptr)
	{
		if (*runningModeStr == "Done")
		{
			mRunningState = RunningState::Done;
		}
		else if (*runningModeStr == "Running")
		{
			mRunningState = RunningState::Running;
		}
		else if (*runningModeStr == "Paused")
		{
			mRunningState = RunningState::Paused;
		}
	}

	const StringRef str3 = "InstantiateLayer";
	HeapString* instantiateLayerStr = mProperties.TryGetByOtherKey(str3, str3.HashCode());
	if (instantiateLayerStr != nullptr&&!instantiateLayerStr->IsEmpty())
	{
		mInstantiateLayer = *instantiateLayerStr;
	}

	const StringRef str4 = "EnableCollision";
	HeapString* enableCollisionStr = mProperties.TryGetByOtherKey(str4, str4.HashCode());
	if (enableCollisionStr != nullptr&&!enableCollisionStr->IsEmpty())
	{
		mCollisionEnabled = StringParser::StringTo<bool>(*enableCollisionStr);
	}

	const StringRef str5 = "ScriptFile";
	HeapString* scriptFileStr = mProperties.TryGetByOtherKey(str5, str5.HashCode());
	if (scriptFileStr != nullptr && !scriptFileStr->IsEmpty())
	{
		mScriptFile = *scriptFileStr;
	}

	return true;
}

MEDUSA_END;