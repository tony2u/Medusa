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
#include "Node/Shape/LinesShape.h"

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
#include "Node/Control/Table/TableBox.h"



#include "Node/Panel/PanelFactory.h"
#include "Node/Control/Button/TextureButton.h"
#include "Node/Control/Button/NodeButton.h"
#include "Node/Control/Button/LabelButton.h"


#include "Node/Control/ProgressBar/ShapeProgressBar.h"
#include "Node/Control/ProgressBar/TextureProgressBar.h"

#include "Node/Control/EditBox/SingleLineEditBox.h"
#include "Node/Control/EditBox/MultipleLineEditBox.h"

#include "Node/Skeleton/SpineSkeleton.h"
#include "Resource/Skeleton/SkeletonModelFactory.h"

#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Resource/TextureAtlas/TextureAtlasFactory.h"
#include "Rendering/RenderingObjectFactory.h"

#include "Node/Editor/NodeEditorFactory.h"
#include "Core/IO/Path.h"
#include "Core/IO/FileInfo.h"
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;

NodeFactory::NodeFactory()
{

}

NodeFactory::~NodeFactory()
{
	SAFE_DELETE_DICTIONARY_VALUE(mClassDict);
}


void NodeFactory::RegisterHelper(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile)
{
	NodeInfo* info = new NodeInfo(className, editorFile, scriptFile);
	mClassDict.Add(className, info);
	if (!editorFile.Name.IsEmpty())
	{
		mEditorDict.Add(editorFile, info);
		auto pureName = Path::GetFileNameWithoutExtension(editorFile.Name);
		mEditorWithoutExtensionDict.Add(pureName, info);
	}

	if (!scriptFile.Name.IsEmpty())
	{
		mScriptDict.Add(scriptFile, info);
		auto pureName = Path::GetFileNameWithoutExtension(scriptFile.Name);
		mScriptWithoutExtensionDict.Add(pureName, info);
	}

}

INode* NodeFactory::Create(const StringRef& className, const FileIdRef& editorFile, const FileIdRef& scriptFile, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= LayerCreateFlags::All*/)
{
	INode* node = nullptr;
	if (editorFile.IsValid())
	{
		node = NodeEditorFactory::Instance().Create(className, editorFile, scriptFile, e, flags);
		RETURN_SELF_IF_NOT_NULL(node);
	}

	if (className.IsEmpty())
	{
		Log::AssertFailed("Cannot create layer without name");
		return nullptr;
	}
	else
	{
		node = BaseType::Create(className, StringRef::Empty, e);	//create layer only use name
	}

	if (node == nullptr)
	{
		Log::AssertFailedFormat("Cannot create layer by name:{}", className);
		return nullptr;
	}
#ifdef MEDUSA_SCRIPT
	node->TryAddScriptFile(scriptFile);
#endif
	node->Initialize();

	return node;
}


INode* NodeFactory::Create(const FileIdRef& smartName, const IEventArg& e /*= IEventArg::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	if (Path::HasExtension(smartName.Name))	//editor file or script file
	{
		FileType fileType = FileInfo::ExtractType(smartName.Name);
		if (FileInfo::IsScriptFile(fileType))
		{
			//script file
			NodeInfo* nodeInfo = mScriptDict.GetOptional(smartName, nullptr);
			if (nodeInfo != nullptr)
			{
				return Create(nodeInfo->ClassName, nodeInfo->EditorFile, nodeInfo->ScriptFile, e, flags);
			}
			//unknown class name, use default
			return Create(StringRef::Empty, FileIdRef::Empty, smartName, e, flags);
		}
		else
		{
			//editor file
			NodeInfo* nodeInfo = mEditorDict.GetOptional(smartName, nullptr);
			if (nodeInfo != nullptr)
			{
				return Create(nodeInfo->ClassName, nodeInfo->EditorFile, nodeInfo->ScriptFile, e, flags);
			}
			//unknown class name, use default
			return Create(StringRef::Empty, smartName, FileIdRef::Empty, e, flags);
		}
	}
	else
	{
		//try to find a match in layer infos
		//first try to find in class name
		NodeInfo* nodeInfo = mClassDict.GetOptional(smartName.Name, nullptr);
		if (nodeInfo != nullptr)
		{
			return Create(nodeInfo->ClassName, nodeInfo->EditorFile, nodeInfo->ScriptFile, e, flags);
		}

		nodeInfo = mEditorWithoutExtensionDict.GetOptional(smartName.Name, nullptr);
		if (nodeInfo != nullptr)
		{
			return Create(nodeInfo->ClassName, nodeInfo->EditorFile, nodeInfo->ScriptFile, e, flags);
		}

		nodeInfo = mScriptWithoutExtensionDict.GetOptional(smartName.Name, nullptr);
		if (nodeInfo != nullptr)
		{
			return Create(nodeInfo->ClassName, nodeInfo->EditorFile, nodeInfo->ScriptFile, e, flags);
		}

		//try to to find editor file in file system
		const auto& editors = NodeEditorFactory::Instance().Editors();
		for (const auto& editor : editors)
		{
			if (editor.Value->IsEnabled())
			{
				auto testFileName = smartName.Name + editor.Value->ExtensionString();
				if (FileSystem::Instance().Exists(testFileName))
				{
					return Create(StringRef::Empty, testFileName, FileIdRef::Empty, e, flags);
				}
			}
		}

		return nullptr;
	}

}


IShape* NodeFactory::CreateRect(const Size2F& rectSize, const Color4F& color)
{

	auto mesh = MeshFactory::Instance().CreateShapeQuadMesh(rectSize, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	sprite->SetSize(rectSize);
	return sprite;
}

IShape* NodeFactory::CreateRect(const Rect2F& rect, const Color4F& color)
{
	auto mesh = MeshFactory::Instance().CreateShapeQuadMesh(rect, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));

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
	auto mesh = MeshFactory::Instance().CreateShapeQuadMesh(rectSize, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_WireFrame));
	material->SetDrawMode(GraphicsDrawMode::LineStrip);

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
	auto mesh = MeshFactory::Instance().CreateShapeQuadMesh(rect, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_WireFrame));
	material->SetDrawMode(GraphicsDrawMode::LineStrip);

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
	auto mesh = MeshFactory::Instance().CreateShapeTriangleMesh(p1, p2, p3, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	return sprite;

}

IShape* NodeFactory::CreateTriangle(float width, float height, const Color4F& color)
{
	auto mesh = MeshFactory::Instance().CreateShapeTriangleMesh(width, height, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape));
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	return sprite;
}

IShape* NodeFactory::CreateCircle(float radius, float precision, const Color4F& color)
{
	auto mesh = MeshFactory::Instance().CreateShapeCircleMesh(radius, precision, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_TrianglesFan));
	material->SetDrawMode(GraphicsDrawMode::TriangleFan);
	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);
	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	return sprite;

}



LinesShape* NodeFactory::CreateLine(const Point3F& from, const Point3F& to, const Color4F& color)
{
	auto mesh = MeshFactory::Instance().CreateLineMesh(from, to, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_Lines));
	material->SetDrawMode(GraphicsDrawMode::Lines);
	LinesShape* sprite = new LinesShape();
	sprite->Initialize();

	sprite->SetSize(Math::Abs(to.X - from.X), Math::Abs(to.Y - from.Y));
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


Sprite* NodeFactory::CreateSprite(const FileIdRef& textureName, const Rect2F& textureRect/*=Rect2F::Zero*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(textureName, textureRect);
	RETURN_NULL_IF_NULL(renderingObject);

	return CreateSprite(renderingObject);
}

Sprite* NodeFactory::CreateSprite(const Share<ITexture>& texture, const Rect2F& textureRect /*= Rect2F::Zero*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTexture(texture, textureRect);
	RETURN_NULL_IF_NULL(renderingObject);

	return CreateSprite(renderingObject);
}

Sprite* NodeFactory::CreateSprite(const RenderingObject& renderingObject)
{
	Sprite* sprite = new Sprite();
	sprite->SetRenderingObject(renderingObject);
	sprite->SetSize(renderingObject.Mesh()->Size());
	sprite->Initialize();

	return sprite;
}

NineGridSprite* NodeFactory::CreateNineGridSprite(const Size2F& targetSize, const FileIdRef& textureName, const ThicknessF& padding, const Rect2F& textureRect/*=Rect2F::Zero*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateNineGridTexture(targetSize, textureName, padding, textureRect);
	RETURN_NULL_IF_NULL(renderingObject);

	NineGridSprite* sprite = new NineGridSprite();
	sprite->EnableLayout(false);	//suppress duplicate arrange after size changed
	sprite->SetRenderingObject(renderingObject);
	sprite->SetTexturePadding(padding);
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

Sprite* NodeFactory::CreateSpriteFromAtlasRegion(StringRef regionName, const FileIdRef& atlasFileId, TextureAtlasType fileFormat /*= TextureAtlasType::None*/)
{
	auto renderingObject = RenderingObjectFactory::Instance().CreateFromTextureAtlasRegion(regionName, atlasFileId, fileFormat);
	RETURN_NULL_IF_NULL(renderingObject);

	Sprite* sprite = new Sprite();
	sprite->SetRenderingObject(renderingObject);
	sprite->SetSize(renderingObject.Mesh()->Size());
	sprite->Initialize();
	return sprite;
}



Sprite* NodeFactory::CreatePODSprite(const FileIdRef& modelName)
{
	auto model = ModelFactory::Instance().Create(modelName);
	RETURN_NULL_IF_NULL(model);
	return (Sprite*)model->Instantiate();
}


ILabel* NodeFactory::CreateMultipleLineLabel(const FontId& fontId, StringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	auto font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, true, isStatic);
	label->Initialize();
	label->SetString(text);

	return label;
}

ILabel* NodeFactory::CreateMultipleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	auto font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, true, isStatic);
	label->Initialize();
	label->SetString(text);

	return label;
}

ILabel* NodeFactory::CreateSingleLineBMPNumberLabel(const FontId& fontId, StringRef text, wchar_t firstChar /*= L'.'*/, Alignment alignment /*= Alignment::MiddleCenter*/, Size2F restrictSize /*= Size2F::Zero*/, bool isStatic /*= false*/)
{
	auto font = FontFactory::Instance().CreateFromSingleTexture(fontId, firstChar);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, true, isStatic);
	label->Initialize();
	label->SetString(text);
	return label;
}

ILabel* NodeFactory::CreateSingleLineLabel(const FontId& fontId, StringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	auto font = FontFactory::Instance().Create(fontId);
	RETURN_NULL_IF_NULL(font);
	FntLabel* label = new FntLabel(StringRef::Empty, font, alignment, restrictSize, false, isStatic);
	label->Initialize();
	label->SetString(text);
	return label;
}

ILabel* NodeFactory::CreateSingleLineLabel(const FontId& fontId, WStringRef text, Alignment alignment/*=Alignment::LeftBottom*/, Size2F restrictSize/*=Size2F::Zero*/, bool isStatic/*=false*/)
{
	auto font = FontFactory::Instance().Create(fontId);
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



ListBox* NodeFactory::CreateListBox()
{
	ListBox* listBox = new ListBox(StringRef::Empty, ScrollDirection::VerticalFromTop);
	listBox->Initialize();
	return listBox;
}

TableBox* NodeFactory::CreateTableBox()
{
	TableBox* box = new TableBox(StringRef::Empty, ScrollDirection::VerticalFromTop);
	box->Initialize();
	return box;
}

TextureButton* NodeFactory::CreateTextureButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName /*= FileIdRef::Empty*/, const FileIdRef& disabledTextureName /*= FileIdRef::Empty*/, const FileIdRef& disabledSelectedTextureName /*= FileIdRef::Empty*/)
{
	TextureButton* button = new TextureButton(StringRef::Empty, normalTextureName, selectedTextureName, disabledTextureName, disabledSelectedTextureName);
	button->Initialize();
	return button;
}

NodeButton* NodeFactory::CreateNodeButton(const FileIdRef& normalTextureName, const FileIdRef& selectedTextureName /*= FileIdRef::Empty*/, const FileIdRef& disabledTextureName /*= FileIdRef::Empty*/, const FileIdRef& disabledSelectedTextureName /*= FileIdRef::Empty*/)
{
	Sprite* normalSprite = CreateSprite(normalTextureName);
	Sprite* selectedSprite = CreateSprite(selectedTextureName);
	Sprite* disabledSprite = CreateSprite(disabledTextureName);
	Sprite* disabledSelectedSprite = CreateSprite(disabledSelectedTextureName);

	NodeButton* button = new NodeButton(StringRef::Empty, normalSprite, selectedSprite, disabledSprite, disabledSelectedSprite);
	button->Initialize();
	return button;
}

LabelButton* NodeFactory::CreateLabelButton(const FontId& fontId, StringRef text, Alignment alignment /*= Alignment::LeftBottom*/, Size2F restrictSize /*= Size2F::Zero*/, bool isStatic /*= false*/)
{
	auto label = CreateSingleLineLabel(fontId, text, alignment, restrictSize, isStatic);
	if (label==nullptr)
	{
		Log::AssertFailedFormat("Cannot find font:{}", fontId);
	}
	LabelButton* button = new LabelButton(label);
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
	Sprite* sprite = CreateSprite(backgroundTextureName);
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

SpineSkeleton* NodeFactory::CreateSkeleton(const FileIdRef& skeletonfileId, const FileIdRef& atlasFileId, bool isPrecomputed /*= false*/)
{
	auto model = SkeletonModelFactory::Instance().CreateSpineFromJson(skeletonfileId, atlasFileId, isPrecomputed);
	RETURN_NULL_IF_NULL(model);
	SpineSkeleton* skeleton = new SpineSkeleton(StringRef::Empty, model);
	skeleton->Initialize();
	return skeleton;
}

SpineSkeleton* NodeFactory::CreateSkeletonDefault(const FileIdRef& name, bool isPrecomputed /*= false*/)
{
	FileId skeletonfileId = name;
	FileId atlasFileId = name;
	skeletonfileId.Name += ".json";
	atlasFileId.Name += ".atlas";

	return CreateSkeleton(skeletonfileId.ToRef(), atlasFileId.ToRef(), isPrecomputed);

}




MEDUSA_END;