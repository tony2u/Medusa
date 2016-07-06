// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "ViewPanel.h"
#include "Node/NodeFactory.h"
MEDUSA_BEGIN;

ViewPanel::ViewPanel(StringRef name/*=StringRef::Empty*/, const IEventArg& e /*= IEventArg::Empty*/)
	:IPanel(name,e),mChildStretch(Stretch::Uniform)
{
	EnableClipToBound(true);
}

ViewPanel::~ViewPanel(void)
{

}

bool ViewPanel::ArrangeChildren(const Rect2F& limitRect/*=Rect2F::Zero*/,NodeLayoutArrangeFlags arrangeFlags/*=NodeLayoutArrangeFlags::None*/)
{
	switch (mChildStretch)
	{
	case Stretch::None:
		{
			for (auto child : mNodes)
			{
				child->ArrangeRecursively(Rect2F::Zero);
			}
		}
		break;

	case Stretch::Fill:
		{
			Scale3F resultScale=Scale3F::One;
			Rect2F resultRect=Rect2F::Zero;

			for (auto child : mNodes)
			{
				const Size3F& childSize=child->Size();

				resultScale.X=limitRect.Size.Width/childSize.Width;
				resultScale.Y=limitRect.Size.Height/childSize.Height;

				child->SetAnchor(Point3F::Half);
				child->SetPosition(limitRect.MiddleCenter());
				child->SetScale(resultScale);

				resultRect.Size=limitRect.Size;
				child->ArrangeRecursively(resultRect,NodeLayoutArrangeFlags::SuppressArrangeSelf);
			}

		}
		break;
	case Stretch::FillWidth:
		{
			Scale3F resultScale=Scale3F::One;
			Rect2F resultRect=Rect2F::Zero;

			for (auto child : mNodes)
			{
				const Size3F& childSize=child->Size();

				resultScale.X=limitRect.Size.Width/childSize.Width;
				resultScale.Y=resultScale.X;

				child->SetAnchor(Point3F::Half);
				child->SetPosition(limitRect.MiddleCenter());
				child->SetScale(resultScale);

				resultRect.Size.Width=limitRect.Size.Width;
				resultRect.Size.Height=resultScale.Y*childSize.Height;

				child->ArrangeRecursively(resultRect,NodeLayoutArrangeFlags::SuppressArrangeSelf);
			}

		}
		break;
	case Stretch::FillHeight:
		{
			Scale3F resultScale=Scale3F::One;
			Rect2F resultRect=Rect2F::Zero;

			for (auto child : mNodes)
			{
				const Size3F& childSize=child->Size();

				resultScale.Y=limitRect.Size.Height/childSize.Height;
				resultScale.X=resultScale.Y;

				child->SetAnchor(Point3F::Half);
				child->SetPosition(limitRect.MiddleCenter());
				child->SetScale(resultScale);

				resultRect.Size.Height=limitRect.Size.Height;
				resultRect.Size.Width=resultScale.X*childSize.Width;

				child->ArrangeRecursively(resultRect,NodeLayoutArrangeFlags::SuppressArrangeSelf);
			}

		}
		break;
	case Stretch::Uniform:
		{
			Scale3F resultScale=Scale3F::One;
			Rect2F resultRect=Rect2F::Zero;
			for (auto child : mNodes)
			{
				const Size3F& childSize=child->Size();

				resultScale.X=limitRect.Size.Width/childSize.Width;
				resultScale.Y=limitRect.Size.Height/childSize.Height;

				resultScale.X=resultScale.Y=Math::Min(resultScale.X,resultScale.Y);

				child->SetAnchor(Point3F::Half);
				child->SetPosition(limitRect.MiddleCenter());
				child->SetScale(resultScale);

				resultRect.Size.Width=resultScale.X*childSize.Width;
				resultRect.Size.Height=resultScale.X*childSize.Height;

				child->ArrangeRecursively(resultRect,NodeLayoutArrangeFlags::SuppressArrangeSelf);
			}
		}

		break;
	case Stretch::UniformToFill:
		{
			Scale3F resultScale=Scale3F::One;
			Rect2F resultRect=Rect2F::Zero;

			for (auto child : mNodes)
			{
				const Size3F& childSize=child->Size();

				resultScale.X=limitRect.Size.Width/childSize.Width;
				resultScale.Y=limitRect.Size.Height/childSize.Height;

				resultScale.X=resultScale.Y=Math::Max(resultScale.X,resultScale.Y);

				child->SetAnchor(Point3F::Half);
				child->SetPosition(limitRect.MiddleCenter());
				child->SetScale(resultScale);

				resultRect.Size.Width=resultScale.X*childSize.Width;
				resultRect.Size.Height=resultScale.X*childSize.Height;

				child->ArrangeRecursively(resultRect,NodeLayoutArrangeFlags::SuppressArrangeSelf);
			}
		}
		break;
	default:
		break;
	}

	return true;
}

MEDUSA_IMPLEMENT_NODE(ViewPanel);

MEDUSA_END;
