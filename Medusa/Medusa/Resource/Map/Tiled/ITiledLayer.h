// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/String/HeapString.h"
#include "Geometry/Size2.h"
#include "Geometry/Point2.h"
#include "Core/Pattern/Property/VariantPropertySet.h"
#include "TiledDefines.h"
#include "Rendering/RenderingTypes.h"
#include "Core/Pattern/Runnable/IRunnable.h"
#include "Resource/ResourceType.h"
#include "Resource/Map/Tiled/TiledMap.h"

/*
Features:
custom properties:
RunningState:
	RunningState::Done(default): disable update
	RunningState::Running: enable update
Instantiate
	Instantiate::Mesh	use static mesh to render tiles
	Instantiate::Sprite(default) use sprites to render tiles
InstantiateLayer: the layer class to instantiate
EnableCollision: a bool indicate enable collision or not
*/
MEDUSA_BEGIN;

class ITiledLayer
{
public:
	ITiledLayer();
	virtual ~ITiledLayer();
	virtual TiledLayerType Type()const = 0;

	bool Parse(const pugi::xml_node& node);

	StringRef Name() const { return mName; }
	void SetName(const StringRef& val) { mName = val; }

	Point2I Position() const { return mPosition; }
	void SetPosition(Point2I val) { mPosition = val; }

	Size2I Size() const { return mSize; }
	void SetSize(Size2I val) { mSize = val; }
	float Opacity() const { return mOpacity; }
	void SetOpacity(float val) { mOpacity = val; }

	int ZOrder() const { return mZOrder; }
	void SetZOrder(int z) { mZOrder = z; }
	bool IsVisible() const { return mIsVisible; }
	void SetVisible(bool val) { mIsVisible = val; }

	const VariantPropertySet& Properties() const { return mProperties; }
	VariantPropertySet& MutableProperties() { return mProperties; }
	void SetProperties(const VariantPropertySet& val) { mProperties = val; }

	TiledMap* Map() const { return mMap; }
	void SetMap(TiledMap* val) { mMap = val; }
	bool IsCollisionEnabled() const { return mCollisionEnabled; }
	void EnableCollision(bool val) { mCollisionEnabled = val; }

	bool IsInputEnabled() const { return mInputEnabled; }
	void EnableInput(bool val) { mInputEnabled = val; }

	virtual INode* Instantiate(NodeInstantiateInfo* instantiateInfo = nullptr)const { return nullptr; }

protected:
	int AdjustY(int y)const { return mSize.Height - y - 1; }
protected:
	HeapString mName;
	Point2I mPosition;
	Size2I mSize;
	float mOpacity;
	bool mIsVisible;

	VariantPropertySet mProperties;
	int mZOrder;

	TiledMap* mMap = nullptr;	//weak ptr
	InstantiateMode mInstantiateMode;
	RunningState mRunningState;
	HeapString mInstantiateLayer;
	bool mCollisionEnabled = false;
	bool mInputEnabled = false;

	HeapString mScriptFile;

	bool mHasSingleTexture = true;
};

MEDUSA_END;
