#include "MedusaExtensionPreCompiled.h"
#include "CocosStudio/Reader/INodeReader.h"
#include "Geometry/Color4.h"
#include "Geometry/Size3.h"
#include "Node/INode.h"
#include "Application/Settings/ApplicationSettings.h"
#include "CocosStudio/CSParseBinary_generated.h"

MEDUSA_COCOS_BEGIN;

void INodeReader::SetPropsWithFlatBuffers(INode* node, const flatbuffers::Table* nodeOptions, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	auto options = (flatbuffers::WidgetOptions*)(nodeOptions);
	const flatbuffers::LayoutComponentTable* layoutComponent = options->layoutComponent();
	StringRef name = options->name()->c_str();

	float scalex = options->scale()->scaleX();
	float scaley = options->scale()->scaleY();
	float rotationSkewX = options->rotationSkew()->rotationSkewX();
	float rotationSkewY = options->rotationSkew()->rotationSkewY();
	float anchorx = options->anchorPoint()->scaleX();
	float anchory = options->anchorPoint()->scaleY();
	int zorder = options->zOrder();
	int tag = options->tag();
	//	int actionTag = options->actionTag();
	bool visible = options->visible() != 0;
	float w = options->size()->width();
	float h = options->size()->height();
	byte alpha = options->alpha();
	Color4F color(options->color()->r(), options->color()->g(), options->color()->b(), alpha);
	bool flipX = options->flipX() != 0;
	bool flipY = options->flipY() != 0;

	node->SetName(name);
	node->SetScaleX(scalex);
	node->SetScaleY(scaley);
	node->SetAnchor(anchorx, anchory);
	node->SetDepth(zorder);
	node->SetVisible(visible);
	node->SetSize(Size3F(w, h, 0));
	node->SetOpacity(alpha / 255.f);
	node->SetColor(color);
	node->SetTag(tag);
	node->SetFlipX(flipX);
	node->SetFlipY(flipY);

	node->SetPositionX(options->position()->x());
	node->SetPositionY(options->position()->y());


	if (layoutComponent != nullptr)
	{
		if (layoutComponent->positionXPercentEnabled() || layoutComponent->positionYPercentEnabled())
		{
			node->SetDock(DockPoint::Percent);
			node->SetRelativePosition(Point2F(layoutComponent->positionXPercent(), layoutComponent->positionYPercent()));

		}

		if (layoutComponent->stretchHorizontalEnabled())
		{
			if (layoutComponent->stretchVerticalEnabled())
			{
				node->SetStretch(Stretch::Uniform);
			}
			else
			{
				node->SetStretch(Stretch::ExpandWidth);
			}
		}
		else
		{
			if (layoutComponent->stretchVerticalEnabled())
			{
				node->SetStretch(Stretch::ExpandHeight);
			}
		}

		if (layoutComponent->sizeXPercentEnable() || layoutComponent->sizeYPercentEnable())
		{
			node->SetStretch(Stretch::Percent);
			node->SetStretchPercent(Scale2F(layoutComponent->sizeXPercent(), layoutComponent->sizeYPercent()));
		}


		StringRef hEdge = layoutComponent->horizontalEdge()->c_str();
		StringRef vEdge = layoutComponent->verticalEdge()->c_str();
		MarginEdges marginEdges = MarginEdges::None;
		auto hMargin = GetHorizontalMarginEdge(hEdge);
		MEDUSA_FLAG_ADD(marginEdges, hMargin);
		auto vMargin = GetVerticalMarginEdge(vEdge);
		MEDUSA_FLAG_ADD(marginEdges, vMargin);

		ThicknessF margin = ThicknessF::Zero;
		margin.Left = layoutComponent->leftMargin();
		margin.Right = -layoutComponent->rightMargin();	//fix direction,we use self edge-parent edge 
		margin.Bottom = layoutComponent->bottomMargin();
		margin.Top = -layoutComponent->topMargin();	//fix direction,we use self edge-parent edge 
		node->SetMargin(margin);
		node->SetMarginEdge(marginEdges);
	}


	SetRotatioSkewXY(node, rotationSkewX, rotationSkewY);

	StringRef frameEvent = options->frameEvent()->c_str();
	StringRef customProperty = options->customProperty()->c_str();
	if (!frameEvent.IsEmpty())
	{
		node->MutableProperties().Add(NodeProperties::FrameEvent, frameEvent);
	}

	node->MutableProperties().Parse(customProperty);

	TryBindScript(node, flags);
}

void INodeReader::SetPropsWithJson(INode* node, const rapidjson::Value& nodeTree, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
	StringRef name = nodeTree.GetMember("Name", nullptr);
	node->SetName(name);

	int tag = nodeTree.GetMember("Tag", 0);
	node->SetTag(tag);

	bool isVisible = nodeTree.GetMember("VisibleForFrame", true);
	node->SetVisible(isVisible);

	//int actionTag = jsonNode.Get("ActionTag", 0);

	const rapidjson::Value* blendNode = nodeTree.GetMemberValue("BlendFunc");
	if (blendNode != nullptr)
	{
		GraphicsBlendSrcFunc srcFunc = (GraphicsBlendSrcFunc)blendNode->GetMember("Src", (int)GraphicsBlendSrcFunc::SrcAlpha);
		GraphicsBlendDestFunc destFunc = (GraphicsBlendDestFunc)blendNode->GetMember("Dst", (int)GraphicsBlendDestFunc::OneMinusSrcAlpha);
		if (srcFunc != GraphicsBlendSrcFunc::SrcAlpha&&destFunc != GraphicsBlendDestFunc::OneMinusSrcAlpha)
		{
			//not default
			node->MutableRenderState().SetBlendFunc(srcFunc, destFunc);
		}
	}
	const rapidjson::Value* sizeNode = nodeTree.GetMemberValue("Size");
	if (sizeNode != nullptr)
	{
		Size2F size;
		size.Width = sizeNode->GetMember("X", 0.f);
		size.Height = sizeNode->GetMember("Y", 0.f);
		node->SetSize(size);
	}

	const rapidjson::Value* anchorPointNode = nodeTree.GetMemberValue("AnchorPoint");
	if (anchorPointNode != nullptr)
	{
		Point2F anchorPoint;
		anchorPoint.X = anchorPointNode->GetMember("ScaleX", 0.f);
		anchorPoint.Y = anchorPointNode->GetMember("ScaleY", 0.f);
		node->SetAnchor(anchorPoint);
	}

	const rapidjson::Value* positionNode = nodeTree.GetMemberValue("Position");
	if (positionNode != nullptr)
	{
		Point2F pos;
		pos.X = positionNode->GetMember("X", 0.f);
		pos.Y = positionNode->GetMember("Y", 0.f);
		node->SetPosition(pos);
	}

	const rapidjson::Value* scaleNode = nodeTree.GetMemberValue("Scale");
	if (scaleNode != nullptr)
	{
		Scale2F scale;
		scale.X = scaleNode->GetMember("ScaleX", 0.f);
		scale.Y = scaleNode->GetMember("ScaleY", 0.f);
		node->SetScale(scale);
	}

	float rotationSkewX = nodeTree.GetMember("RotationSkewX", 0.f);
	float rotationSkewY = nodeTree.GetMember("RotationSkewY", 0.f);
	SetRotatioSkewXY(node, rotationSkewX, rotationSkewY);

	bool flipX = nodeTree.GetMember("FlipX", false);
	bool flipY = nodeTree.GetMember("FlipY", false);
	node->SetFlipX(flipX);
	node->SetFlipY(flipY);

	Color4F color = ToColor(nodeTree.GetMemberValue("CColor"));
	node->SetColor(color);
	float opacity = nodeTree.GetMember("Alpha", 255) / 255.f;
	node->SetOpacity(opacity);

	bool positionPercentXEnabled = nodeTree.GetMember("PositionPercentXEnabled", false);
	bool positionPercentYEnabled = nodeTree.GetMember("PositionPercentYEnabled", false);
	if (positionPercentXEnabled || positionPercentYEnabled)
	{
		node->SetDock(DockPoint::Percent);
		const rapidjson::Value* prePositionNode = nodeTree.GetMemberValue("PrePosition");
		if (prePositionNode != nullptr)
		{
			Point2F pos;
			pos.X = prePositionNode->GetMember("X", 0.f);
			pos.Y = prePositionNode->GetMember("Y", 0.f);
			node->SetRelativePosition(pos);
		}
	}
	bool stretchWidthEnable = nodeTree.GetMember("StretchWidthEnable", false);
	bool stretchHeightEnable = nodeTree.GetMember("StretchHeightEnable", false);
	if (stretchWidthEnable)
	{
		if (stretchHeightEnable)
		{
			node->SetStretch(Stretch::Uniform);
		}
		else
		{
			node->SetStretch(Stretch::ExpandWidth);
		}
	}
	else
	{
		if (stretchHeightEnable)
		{
			node->SetStretch(Stretch::ExpandHeight);
		}
	}

	bool percentWidthEnable = nodeTree.GetMember("PercentWidthEnable", false) || nodeTree.GetMember("PercentWidthEnabled", false);
	bool percentHeightEnable = nodeTree.GetMember("PercentHeightEnable", false) || nodeTree.GetMember("PercentHeightEnabled", false);
	if (percentWidthEnable || percentHeightEnable)
	{
		node->SetStretch(Stretch::Percent);
		const rapidjson::Value* preSizeNode = nodeTree.GetMemberValue("PreSize");
		if (preSizeNode != nullptr)
		{
			Scale2F sizePercent;
			sizePercent.X = preSizeNode->GetMember("X", 0.f);
			sizePercent.Y = preSizeNode->GetMember("Y", 0.f);
			node->SetStretchPercent(sizePercent);
		}
	}

	StringRef hEdge = nodeTree.GetMember("HorizontalEdge", nullptr);
	StringRef vEdge = nodeTree.GetMember("VerticalEdge", nullptr);
	MarginEdges marginEdges = MarginEdges::None;
	auto hMargin = GetHorizontalMarginEdge(hEdge);
	MEDUSA_FLAG_ADD(marginEdges, hMargin);
	auto vMargin = GetVerticalMarginEdge(vEdge);
	MEDUSA_FLAG_ADD(marginEdges, vMargin);

	ThicknessF margin = ThicknessF::Zero;
	margin.Left = nodeTree.GetMember("LeftMargin", 0.f);
	margin.Right = -nodeTree.GetMember("RightMargin", 0.f);
	margin.Bottom = nodeTree.GetMember("BottomMargin", 0.f);
	margin.Top = -nodeTree.GetMember("TopMargin", 0.f);
	node->SetMargin(margin);
	node->SetMarginEdge(marginEdges);

	StringRef userData = nodeTree.GetMember("UserData", nullptr);
	if (!userData.IsEmpty())
	{
		node->MutableProperties().Parse(userData);
	}

	StringRef frameEvent = nodeTree.GetMember("FrameEvent", nullptr);
	if (!frameEvent.IsEmpty())
	{
		node->MutableProperties().Add(NodeProperties::FrameEvent, frameEvent);
	}

	TryBindScript(node, flags);
}

MarginEdges INodeReader::GetHorizontalMarginEdge(StringRef val)
{
	MarginEdges marginEdges = MarginEdges::None;
	if (val == "LeftEdge")
	{
		MEDUSA_FLAG_ADD(marginEdges, MarginEdges::Left);
	}
	else if (val == "RightEdge")
	{
		MEDUSA_FLAG_ADD(marginEdges, MarginEdges::Right);
	}
	else if (val == "BothEdge")
	{
		MEDUSA_FLAG_ADD(marginEdges, MarginEdges::Horizontal);
	}

	return marginEdges;
}

MarginEdges INodeReader::GetVerticalMarginEdge(StringRef val)
{
	MarginEdges marginEdges = MarginEdges::None;
	if (val == "BottomEdge")
	{
		MEDUSA_FLAG_ADD(marginEdges, MarginEdges::Bottom);
	}
	else if (val == "TopEdge")
	{
		MEDUSA_FLAG_ADD(marginEdges, MarginEdges::Top);
	}
	else if (val == "BothEdge")
	{
		MEDUSA_FLAG_ADD(marginEdges, MarginEdges::Vertical);
	}
	return marginEdges;

}

void INodeReader::SetRotatioSkewXY(INode* node, float x, float y)
{
	x = Math::ToRadian(x);	//x is right
	y = -Math::ToRadian(y);	//y is down in cocos

	if (Math::IsEqual(x, y))
	{
		node->SetRotationZ(x);
	}
	else
	{
		/*
		//in cocos,rotation skew matrix like this
		cosY,sinY,
		-sinX,cosX

		regular skew matrix is
		1,tanY
		tanX,1

		so we have to scale back
		cosY,0
		0,cosX

		so we got
		cosy,tanY*cosY
		cosx*tanX,cosx
		*/
		float cosX = Math::Cos(x);
		float cosY = Math::Cos(y);

		node->SetSkewXY(x, y);
		node->SetScale(node->ScaleX()*cosY, node->ScaleY()*cosX);	//so we have to scale to apply to cocos's style rotation skew
	}

}

Color4F INodeReader::ToColor(const rapidjson::Value* jsonNode)
{
	if (jsonNode != nullptr)
	{
		Color4B color;
		color.R = (byte)jsonNode->GetMember("R", 255);
		color.G = (byte)jsonNode->GetMember("G", 255);
		color.B = (byte)jsonNode->GetMember("B", 255);
		color.A = (byte)jsonNode->GetMember("A", 255);
		return color.To4F();
	}

	return Color4F::White;	//default color
}

void INodeReader::TryBindScript(INode* node, NodeCreateFlags flags /*= NodeCreateFlags::None*/)
{
#ifdef MEDUSA_SCRIPT

	if (ApplicationSettings::Instance().HasScriptBinding())
	{
		if (MEDUSA_FLAG_HAS(flags, NodeCreateFlags::BindScriptSelf))
		{
			StringRef customScript;
			//re check if editor disable the script
			if (node->Properties().Has(NodeProperties::Script))
			{
				customScript = node->Properties().Get(NodeProperties::Script);	//may be empty
				if (customScript.Compare("false", true) == 0)
				{
					return;
				}
				else if (customScript.Compare("true", true) == 0)
				{
					customScript = StringRef::Empty;
				}
			}

			if (customScript.IsEmpty())
			{
				customScript = node->ScriptFileName().Name;
			}

			node->TryAttachScriptObject(customScript);
		}
		
	}

#endif
}


MEDUSA_COCOS_END;
