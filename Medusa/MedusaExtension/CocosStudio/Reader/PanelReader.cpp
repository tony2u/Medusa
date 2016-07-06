#include "MedusaExtensionPreCompiled.h"
#include "ImageViewReader.h"
#include "PanelReader.h"
#include "Core/String/StringRef.h"
#include "Core/IO/FileId.h"
#include "Node/Panel/CanvasPanel.h"
#include "Node/NodeFactory.h"
#include "ReaderFactory.h"
#include "CocosStudio/CSParseBinary_generated.h"
#include "Rendering/RenderingObjectFactory.h"
#include "Rendering/RenderingObject.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Model/Mesh/Fixed/ShapeQuadMesh.h"
#include "Node/Shape/IShape.h"
#include "Core/IO/Path.h"
#include "Node/Sprite/NineGridSprite.h"

MEDUSA_COCOS_BEGIN;


INode* PanelReader::CreateNodeWithFlatBuffers(INodeEditor& editor, const flatbuffers::Table* nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::PanelOptions*)nodeTree;
	auto panel = (NodeFactory::Instance().CreatePanel(PanelType::Canvas));
	bool clipEnabled = options->clipEnabled() != 0;
	panel->EnableClipToBound(clipEnabled);

	StringRef fullName = options->backGroundImageData()->path()->c_str();
	auto fileId = FileId::ParseFrom(fullName);
	if (fileId.IsValid())
	{
		auto sprite = ImageViewReader::CreateNineGridSprite(options->backGroundScale9Enabled(), options->scale9Size(), options->widgetOptions()->size(), options->capInsets(), fileId);
		panel->AddChild(sprite);
	}

	switch (options->colorType())
	{
	case 0:
		break;
	case 1:
	{
		INode* rect = CreateSingleColorRect(options->bgColorOpacity(), *options->bgColor(), *options->widgetOptions()->size());
		panel->AddChild(rect);
	}
		break; 
	case 2:
	{
		INode* rect = CreateGradientRect(options->bgColorOpacity(), *options->bgColor(), *options->widgetOptions()->size(), *options->bgStartColor(), *options->bgEndColor(),*options->colorVector());
		panel->AddChild(rect);
	}
	break;
	default:
		Log::AssertFailed("PanelReader PanelBackGroundColorType  Error");
		break;
	}

	SetPropsWithFlatBuffers(panel, (flatbuffers::Table*) options->widgetOptions());
	return panel;
}

IShape* PanelReader::CreateGradientRect(byte opacity, const flatbuffers::Color& bgColor, const flatbuffers::FlatSize& flatSize, const flatbuffers::Color& start, const flatbuffers::Color& end, const flatbuffers::ColorVector& vec)
{
	auto shape = CreateSingleColorRect(opacity, bgColor, flatSize);
	SetGradientRectColor(shape,opacity,start,end,vec);
	return shape;
}

void PanelReader::SetGradientRectColor(IShape* rect, byte opacity, const flatbuffers::Color& start, const flatbuffers::Color& end, const flatbuffers::ColorVector& vec)
{
	Point2F u(vec.vectorX(), vec.vectorY());
	u.Normalize();
	float c = Math::Sqrt(2.0f);
	float h2 = 1 / (Math::Abs(u.X) + Math::Abs(u.Y));
	u = u * (h2 * (float)c);
	Color4F startColor(start.r(), start.g(), start.b(), opacity);
	Color4F endColor(end.r(), end.g(), end.b(), opacity);
	auto mesh = rect->Mesh().CastPtr<ShapeQuadMesh>();
	mesh->SetColor(0, endColor + (startColor - endColor)*((c + u.X + u.Y) / (2.0f * c)));
	mesh->SetColor(1, endColor + (startColor - endColor)*((c - u.X + u.Y) / (2.0f * c)));
	mesh->SetColor(2, endColor + (startColor - endColor)*((c - u.X - u.Y) / (2.0f * c)));
	mesh->SetColor(3, endColor + (startColor - endColor)*((c + u.X - u.Y) / (2.0f * c)));
}

IShape* PanelReader::CreateSingleColorRect(byte opacity, const flatbuffers::Color& bgColor, const flatbuffers::FlatSize& flatSize)
{
	return NodeFactory::Instance().CreateRect(Size2F(flatSize.width(), flatSize.height()), Color4F(bgColor.r(), bgColor.g(), bgColor.b(), opacity));
}

INode* PanelReader::CreateNodeWithJson(INodeEditor& editor, const rapidjson::Value& nodeTree, const StringRef& className /*= StringRef::Empty*/, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	return nullptr;
}


MEDUSA_COCOS_END;
