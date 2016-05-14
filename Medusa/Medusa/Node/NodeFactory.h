// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Pattern/Singleton.h"
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Size2.h"
#include "Node/NodeDefines.h"
#include "Core/IO/FileIdRef.h"
#include "Geometry/Rect2.h"
#include "Resource/TextureAtlas/TextureAtlasDefines.h"
#include "Geometry/GeometryDefines.h"
#include "Geometry/Thickness.h"

MEDUSA_BEGIN;

class NodeFactory :public Singleton < NodeFactory >
{
	friend class Singleton < NodeFactory > ;
private:
	NodeFactory();
	~NodeFactory();
public:
	void Clear();
public:

	IShape* CreateRectBorder(const Size2F& rectSize, const Color4F& color);
	IShape* CreateRectBorder(const Rect2F& rect, const Color4F& color);

	IShape* CreateRect(const Size2F& rectSize, const Color4F& color);
	IShape* CreateRect(const Rect2F& rect, const Color4F& color);
	IShape* CreateTriangle(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color);
	IShape* CreateTriangle(float width, float height, const Color4F& color);

	IShape* CreateCircle(float radius, float precision,const Color4F& color);

	Sprite* CreateEmptySprite();

	Sprite* CreateSprite(const FileIdRef& textureName, const Rect2F& textureRect = Rect2F::Zero);
	Sprite* CreateSprite(ITexture* texture, const Rect2F& textureRect = Rect2F::Zero);

	NineGridSprite* CreateNineGridSprite( const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect = Rect2F::Zero);
	Sprite* CreatePODSprite(const FileIdRef& modelName);

	Sprite* CreateSpriteFromAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasType fileFormat = TextureAtlasType::None);
	Sprite* CreateSpriteFromAtlasRegion(TextureAtlasRegion* region);



	ILabel* CreateMultipleLineLabel(const FontId& fontId, StringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);
	ILabel* CreateMultipleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);

	ILabel* CreateSingleLineLabel(const FontId& fontId, StringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);
	ILabel* CreateSingleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);

	ListBox* CreateStringListBox(const List<WHeapString>& strItems, bool isSingleLine = true);
	ListBox* CreateEmptyListBox();

	IPanel* CreatePanel(PanelType panelType);

	TextureButton* CreateTextureButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName = FileIdRef::Empty, const FileIdRef& disabledTextureName = FileIdRef::Empty, const FileIdRef& disabledSelectedTextureName = FileIdRef::Empty);
	NodeButton* CreateNodeButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName = FileIdRef::Empty, const FileIdRef& disabledTextureName = FileIdRef::Empty, const FileIdRef& disabledSelectedTextureName = FileIdRef::Empty);

	TextureProgressBar* CreateTextureProgressBar(ProgressType progressType, const FileIdRef& textureName, float percent = 1.f);
	TextureProgressBar* CreateTextureProgressBar(ProgressType progressType, const FileIdRef& textureName, const FileIdRef& backgroundTextureName, float percent = 1.f);


	SingleLineEditBox* CreateSingleLineEditBox(const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	MultipleLineEditBox* CreateMultipleLineEditBox(const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);

	SpineSkeleton* CreateSkeleton(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId, bool isPreCalculated = false);
	SpineSkeleton* CreateSkeletonDefault(const FileIdRef& name, bool isPreCalculated = false);

};

MEDUSA_END;