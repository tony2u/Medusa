// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/NodeFactory.h"
#include "Node/Control/Label/FntLabel.h"
#include "Resource/Model/Font/BaseFontModel.h"
#include "Resource/Model/Font/SingleLineFontModel.h"
#include "Resource/Model/Font/MultipleLineFontModel.h"
#include "Resource/Font/FontFactory.h"
#include "Resource/Model/Basic/QuadModel.h"
#include "Resource/ResourceNames.h"
#include "Node/Sprite/Sprite.h"
#include "Node/Sprite/NineGridSprite.h"

#include "Resource/Material/MaterialFactory.h"
#include "Resource/Effect/EffectFactory.h"
#include "Resource/Model/ModelFactory.h"
#include "Resource/Model/Mesh/MeshFactory.h"
#include "Resource/Model/Mesh/Fixed/ShapeQuadMesh.h"
#include "Resource/Model/Mesh/Fixed/ShapeTriangleMesh.h"
#include "Resource/Model/Mesh/General/ShapeGeneralMesh.h"


#include "Resource/Model/Mesh/Fixed/TextureNineGridMesh.h"
#include "Resource/Model/Mesh/Fixed/TextureQuadMesh.h"


#include "Node/Shape/IShape.h"
#include "Node/Control/ListBox/ListBox.h"


#include "Node/Panel/PanelFactory.h"
#include "Node/DataSource/StringListDataSource.h"
#include "Node/Control/Button/TextureButton.h"
#include "Node/Control/Button/NodeButton.h"

#include "Node/Control/ProgressBar/ShapeProgressBar.h"
#include "Node/Control/ProgressBar/TextureProgressBar.h"

#include "Node/Control/EditBox/SingleLineEditBox.h"
#include "Node/Control/EditBox/MultipleLineEditBox.h"

#include "Node/Skeleton/SpineSkeleton.h"
#include "Resource/Skeleton/SkeletonModelFactory.h"

#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"
#include "Rendering/RenderingObjectFactory.h"


MEDUSA_BEGIN;

NodeFactory::NodeFactory()
{

}

NodeFactory::~NodeFactory()
{
	Clear();
}

void NodeFactory::Clear()
{
}

IShape* NodeFactory::CreateRect(const Size2F& rectSize, const Color4F& color)
{

	ShapeQuadMesh* mesh = MeshFactory::Instance().CreateShapeQuadMesh(rectSize, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	sprite->SetSize(rectSize);
	return sprite;
}

IShape* NodeFactory::CreateRect( const Rect2F& rect, const Color4F& color)
{
	ShapeQuadMesh* mesh = MeshFactory::Instance().CreateShapeQuadMesh(rect, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));

	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	sprite->SetSize(rect.Size);

	return sprite;
}

IShape* NodeFactory::CreateRectBorder(const Size2F& rectSize, const Color4F& color)
{
	ShapeQuadMesh* mesh = MeshFactory::Instance().CreateShapeQuadMesh(rectSize, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_WireFrame));

	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	sprite->SetSize(rectSize);
	return sprite;
}

IShape* NodeFactory::CreateRectBorder(const Rect2F& rect, const Color4F& color)
{
	ShapeQuadMesh* mesh = MeshFactory::Instance().CreateShapeQuadMesh(rect, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_WireFrame));

	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	sprite->SetSize(rect.Size);

	return sprite;
}

IShape* NodeFactory::CreateTriangle(const Point3F& p1, const Point3F& p2, const Point3F& p3, const Color4F& color)
{
	ShapeTriangleMesh* mesh = MeshFactory::Instance().CreateShapeTriangleMesh(p1, p2, p3, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	return sprite;

}

IShape* NodeFactory::CreateTriangle(float width, float height, const Color4F& color)
{
	ShapeTriangleMesh* mesh = MeshFactory::Instance().CreateShapeTriangleMesh(width, height, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	return sprite;
}

IShape* NodeFactory::CreateCircle(float radius, float precision, const Color4F& color)
{
	ShapeGeneralMesh* mesh = MeshFactory::Instance().CreateShapeCircleMesh(radius, precision, color);
	RETURN_NULL_IF_NULL(mesh);
	IMaterial* material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_TrianglesFan));
	material->SetDrawMode(GraphicsDrawMode::TriangleFan);
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);
	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	return sprite;
	
}



Sprite* NodeFactory::CreateEmptySprite()
{
	Sprite* sprite = new Sprite();
	sprite->Initialize();
	return sprite;
}


Sprite* NodeFactory::CreateQuadSprite(const FileIdRef& textureName, const Rect2F& textureRect/*=Rect2F::Zero*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(textureName, textureRect);
	RETURN_NULL_IF_NULL(renderingObject);

	Sprite* sprite = new Sprite();
	sprite->SetRenderingObject(renderingObject);
	sprite->SetSize(renderingObject.Mesh()->Size());
	sprite->Initialize();

	return sprite;
}

NineGridSprite* NodeFactory::CreateNineGridSprite(const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect/*=Rect2F::Zero*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateNineGridTexture(targetSize, textureName,padding,textureRect);
	RETURN_NULL_IF_NULL(renderingObject);

	NineGridSprite* sprite = new NineGridSprite();
	sprite->EnableLayout(false);	//suppress duplicate arrange after size changed
	sprite->SetRenderingObject(renderingObject);
	sprite->SetSize(renderingObject.Mesh()->Size());
	sprite->Initialize();
	sprite->EnableLayout(true);
	return sprite;

}

Sprite* NodeFactory::CreateSpriteFromAtlasRegion(TextureAtlasRegion* region)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTextureAtlasRegion(region);
	RETURN_NULL_IF_NULL(renderingObject);

	Sprite* sprite = new Sprite();
	sprite->SetRenderingObject(renderingObject);
	sprite->SetSize(renderingObject.Mesh()->Size());
	sprite->Initialize();

	return sprite;

}

Sprite* NodeFactory::CreateSpriteFromAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasFileFormat fileFormat /*= TextureAtlasFileFormat::Spine*/, uint atlasPageCount /*= 1*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTextureAtlasRegion(regionName, atlasFileId, fileFormat, atlasPageCount);
	RETURN_NULL_IF_NULL(renderingObject);

	Sprite* sprite = new Sprite();
	sprite->SetRenderingObject(renderingObject);
	sprite->SetSize(renderingObject.Mesh()->Size());
	sprite->Initialize();
	return sprite;
}


Sprite* NodeFactory::CreatePODSprite(const FileIdRef& modelName)
{
	IModel* model = ModelFactory::Instance().Create(modelName);
	RETURN_NULL_IF_NULL(model);
	return (Sprite*)model->CreateCloneInstance();
}


ILabel* NodeFactory::CreateMultipleLineLabel(const FontId& fontId, StringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	IFont* font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty,font, alignment, restrictSize, true, isStatic);
	label->Initialize();
	label->SetString(text);

	return label;
}

ILabel* NodeFactory::CreateMultipleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	IFont* font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, true, isStatic);
	label->Initialize();
	label->SetString(text);

	return label;
}

ILabel* NodeFactory::CreateSingleLineLabel(const FontId& fontId, StringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	IFont* font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, false, isStatic);
	label->Initialize();
	label->SetString(text);
	return label;
}

ILabel* NodeFactory::CreateSingleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	IFont* font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, false, isStatic);
	label->Initialize();
	label->SetString(text);
	return label;
}




IPanel* NodeFactory::CreatePanel(PanelType panelType)
{
	return PanelFactory::Instance().Create(panelType);
}

ListBox* NodeFactory::CreateStringListBox(const List<WHeapString>& strItems, bool isSingleLine/*=true*/)
{
	ListBox* listBox = new ListBox();
	listBox->SetDataSource(new StringListDataSource(strItems, isSingleLine));
	listBox->Initialize();
	return listBox;
}


ListBox* NodeFactory::CreateEmptyListBox()
{
	ListBox* listBox = new ListBox();
	listBox->Initialize();
	return listBox;
}

TextureButton* NodeFactory::CreateTextureButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName/*=FileId::Empty*/, const FileIdRef& disabledTextureName/*=FileId::Empty*/, const FileIdRef& disabledSelectedTextureName/*=FileId::Empty*/)
{
	TextureButton* button = new TextureButton(StringRef::Empty, normalTextureName, selectedTextureName, disabledTextureName, disabledSelectedTextureName);
	button->Initialize();
	return button;
}

NodeButton* NodeFactory::CreateNodeButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName /*= FileIdRef::Empty*/, const FileIdRef& disabledTextureName /*= FileIdRef::Empty*/, const FileIdRef& disabledSelectedTextureName /*= FileIdRef::Empty*/)
{
	Sprite* normalSprite = CreateQuadSprite(normalTextureName);
	Sprite* selectedSprite = CreateQuadSprite(selectedTextureName);
	Sprite* disabledSprite = CreateQuadSprite(disabledTextureName);
	Sprite* disabledSelectedSprite = CreateQuadSprite(disabledSelectedTextureName);

	NodeButton* button = new NodeButton(StringRef::Empty, normalSprite, selectedSprite, disabledSprite, disabledSelectedSprite);
	button->Initialize();
	return button;
}

TextureProgressBar* NodeFactory::CreateTextureProgressBar(ProgressType progressType, const FileIdRef& textureName, float percent /*= 1.f*/)
{
	TextureProgressBar* val = new TextureProgressBar(StringRef::Empty, progressType, textureName, percent);
	val->Initialize();
	return val;
}

TextureProgressBar* NodeFactory::CreateTextureProgressBar(ProgressType progressType, const FileIdRef& textureName, const FileIdRef& backgroundTextureName, float percent /*= 1.f*/)
{
	TextureProgressBar* val = CreateTextureProgressBar(progressType, textureName, percent);
	Sprite* sprite = CreateQuadSprite(backgroundTextureName);
	sprite->SetDepth(-1);
	val->AddChild(sprite);
	return val;
}

SingleLineEditBox* NodeFactory::CreateSingleLineEditBox(const Size2F& size, const FontId& fontId, WStringRef text /*= WStringRef::Empty*/, Alignment alignment /*= Alignment::LeftBottom*/)
{
	SingleLineEditBox* val = new SingleLineEditBox(StringRef::Empty, size, fontId, text, alignment);
	val->Initialize();
	return val;
}

MultipleLineEditBox* NodeFactory::CreateMultipleLineEditBox(const Size2F& size, const FontId& fontId, WStringRef text /*= WStringRef::Empty*/, Alignment alignment /*= Alignment::LeftBottom*/)
{
	MultipleLineEditBox* val = new MultipleLineEditBox(StringRef::Empty, size, fontId, text, alignment);
	val->Initialize();
	return val;
}

SpineSkeleton* NodeFactory::CreateSkeleton(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId, bool isPreCalculated /*= false*/)
{
	SpineSkeletonModel* model = SkeletonModelFactory::Instance().CreateSpineFromJson(skeletonfileId, atlasFileId, isPreCalculated);
	RETURN_NULL_IF_NULL(model);
	SpineSkeleton* skeleton = new SpineSkeleton(StringRef::Empty, model);
	skeleton->Initialize();
	return skeleton;
}

SpineSkeleton* NodeFactory::CreateSkeletonDefault(const FileIdRef& name, bool isPreCalculated /*= false*/)
{
	FileId skeletonfileId = name;
	FileId atlasFileId = name;
	skeletonfileId.Name += ".json";
	atlasFileId.Name += ".atlas";

	return CreateSkeleton(skeletonfileId.ToRef(), atlasFileId.ToRef(), isPreCalculated);

}




MEDUSA_END;