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
#include "Core/Pattern/Object/MapObjectFactory.h"
#include "Core/Pattern/TuplePattern.h"
#include "Core/Event/EventArg/IEventArg.h"

MEDUSA_BEGIN;

class NodeFactory :public MapObjectFactory<StringRef, INode*(const StringRef&, const IEventArg&)>,public Singleton < NodeFactory >
{
	MEDUSA_TUPLE_3(NodeInfo, StringRef, ClassName, FileIdRef, EditorFile, FileIdRef, ScriptFile);

	NodeFactory();
	~NodeFactory();
	friend class Singleton < NodeFactory > ;
public:
	using BaseType = MapObjectFactory<StringRef, INode*(const StringRef&, const IEventArg&)>;
	template<typename T>
	void Register(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile)
	{
		BaseType::Register<T>(className);
		RegisterHelper(className, editorFile, scriptFile);
	}

	template<typename T>
	T* Create(const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None) { return (T*)Create(T::ClassNameStatic(), T::EditorFileNameStatic(), T::ScriptFileNameStatic(), e, flags); }

	INode* Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::All);
	INode* Create(const FileIdRef& smartName, const IEventArg& e = IEventArg::Empty, NodeCreateFlags flags = NodeCreateFlags::None);
private:
	void RegisterHelper(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile);
public:
	IShape* CreateRectBorder(const Size2F& rectSize, const Color4F& color);
	IShape* CreateRectBorder(const Rect2F& rect, const Color4F& color);

	IShape* CreateRect(const Size2F& rectSize, const Color4F& color);
	IShape* CreateRect(const Rect2F& rect, const Color4F& color);
	IShape* CreateTriangle(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color);
	IShape* CreateTriangle(float width, float height, const Color4F& color);

	IShape* CreateCircle(float radius, float precision,const Color4F& color);
	LinesShape* CreateLine(const Point3F& from, const Point3F& to, const Color4F& color);


	Sprite* CreateEmptySprite();

	Sprite* CreateSprite(const FileIdRef& textureName, const Rect2F& textureRect = Rect2F::Zero);
	Sprite* CreateSprite(const Share<ITexture>& texture, const Rect2F& textureRect = Rect2F::Zero);
	Sprite* CreateSprite(const RenderingObject& renderingObject);

	NineGridSprite* CreateNineGridSprite( const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect = Rect2F::Zero);
	Sprite* CreatePODSprite(const FileIdRef& modelName);

	Sprite* CreateSpriteFromAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasType fileFormat = TextureAtlasType::None);
	Sprite* CreateSpriteFromAtlasRegion(TextureAtlasRegion* region);



	ILabel* CreateMultipleLineLabel(const FontId& fontId, StringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);
	ILabel* CreateMultipleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);

	ILabel* CreateSingleLineBMPNumberLabel(const FontId& fontId, StringRef text, wchar_t firstChar = L'.', Alignment alignment = Alignment::MiddleCenter, Size2F restrictSize = Size2F::Zero, bool isStatic = false);
	ILabel* CreateSingleLineLabel(const FontId& fontId, StringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);
	ILabel* CreateSingleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);

	ListBox* CreateListBox();
	TableBox* CreateTableBox();


	IPanel* CreatePanel(PanelType panelType);

	TextureButton* CreateTextureButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName = FileIdRef::Empty, const FileIdRef& disabledTextureName = FileIdRef::Empty, const FileIdRef& disabledSelectedTextureName = FileIdRef::Empty);
	NodeButton* CreateNodeButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName = FileIdRef::Empty, const FileIdRef& disabledTextureName = FileIdRef::Empty, const FileIdRef& disabledSelectedTextureName = FileIdRef::Empty);
	LabelButton* CreateLabelButton(const FontId& fontId, StringRef text, Alignment alignment = Alignment::LeftBottom, Size2F restrictSize = Size2F::Zero, bool isStatic = false);



	TextureProgressBar* CreateTextureProgressBar(ProgressType progressType, const FileIdRef& textureName, float percent = 1.f);
	TextureProgressBar* CreateTextureProgressBar(ProgressType progressType, const FileIdRef& textureName, const FileIdRef& backgroundTextureName, float percent = 1.f);


	SingleLineEditBox* CreateSingleLineEditBox(const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);
	MultipleLineEditBox* CreateMultipleLineEditBox(const Size2F& size, const FontId& fontId, WStringRef text = WStringRef::Empty, Alignment alignment = Alignment::LeftBottom);

	SpineSkeleton* CreateSkeleton(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId, bool isPrecomputed = false);
	SpineSkeleton* CreateSkeletonDefault(const FileIdRef& name, bool isPrecomputed = false);
private:
	Dictionary<StringRef, NodeInfo*> mClassDict;
	Dictionary<FileIdRef, NodeInfo*> mEditorDict;
	Dictionary<StringRef, NodeInfo*> mEditorWithoutExtensionDict;

	Dictionary<FileIdRef, NodeInfo*> mScriptDict;
	Dictionary<StringRef, NodeInfo*> mScriptWithoutExtensionDict;
};

MEDUSA_END;