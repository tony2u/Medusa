// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Geometry/Geometry.h"
#include "Point2.h"
#include "Rect2.h"

MEDUSA_BEGIN;



Point2F Geometry::DockToRect(const Rect2F& rect, DockPoint dock, const Point2F& relativePosition /*= Point2F::Zero*/)
{
	Point2F pos;
	switch (dock)
	{
		case DockPoint::None:
			pos = Point2F::Zero;
			break;
		case DockPoint::LeftBottom:
			pos = rect.LeftBottom();
			pos += relativePosition;
			break;
		case DockPoint::LeftCenter:
			pos = rect.LeftCenter();
			pos += relativePosition;
			break;
		case DockPoint::LeftTop:
			pos = rect.LeftTop();
			pos += relativePosition;
			break;
		case DockPoint::MiddleBottom:
			pos = rect.MiddleBottom();
			pos += relativePosition;
			break;
		case DockPoint::MiddleCenter:
			pos = rect.MiddleCenter();
			pos += relativePosition;
			break;
		case DockPoint::MiddleTop:
			pos = rect.MiddleTop();
			pos += relativePosition;
			break;
		case DockPoint::RightBottom:
			pos = rect.RightBottom();
			pos += relativePosition;
			break;
		case DockPoint::RightCenter:
			pos = rect.RightCenter();
			pos += relativePosition;
			break;
		case DockPoint::RightTop:
			pos = rect.RightTop();
			pos += relativePosition;
			break;
		case DockPoint::Percent:
			pos.X = relativePosition.X*rect.Size.Width;
			pos.Y = relativePosition.Y*rect.Size.Height;
			break;
		default:
			break;
	}

	return pos;
}


void Geometry::StretchToRect(const Size2F& selfSize, const Rect2F& rect, Stretch stretch, const Scale2F& strecthPercent, Scale2F& outScale, Size2F& outSize)
{
	switch (stretch)
	{
		case Stretch::Fill:
			outScale.X = Math::IsZero(selfSize.Width) ? 0.f : rect.Size.Width / selfSize.Width;
			outScale.Y = Math::IsZero(selfSize.Height) ? 0.f : rect.Size.Height / selfSize.Height;
			outSize = rect.Size;
			break;
		case Stretch::FillWidth:
			outScale.X = Math::IsZero(selfSize.Width) ? 0.f : rect.Size.Width / selfSize.Width;
			outScale.Y = outScale.X;
			outSize.Width = rect.Size.Width;
			outSize.Height = selfSize.Height*outScale.Y;
			break;
		case Stretch::FillHeight:
			outScale.Y = Math::IsZero(selfSize.Height) ? 0.f : rect.Size.Height / selfSize.Height;
			outScale.X = outScale.Y;
			outSize.Height = rect.Size.Height;
			outSize.Width = selfSize.Width*outScale.X;

			break;
		case Stretch::Uniform:
		{
			float scaleX = Math::IsZero(selfSize.Width) ? 0.f : rect.Size.Width / selfSize.Width;
			float scaleY = Math::IsZero(selfSize.Height) ? 0.f : rect.Size.Height / selfSize.Height;
			float scale = Math::Min(scaleX, scaleY);
			outScale.X = scale;
			outScale.Y = scale;
			outSize.Height = selfSize.Height*outScale.Y;
			outSize.Width = selfSize.Width*outScale.X;

		}
		break;
		case Stretch::UniformToFill:
		{
			float scaleX = Math::IsZero(selfSize.Width) ? 0.f : rect.Size.Width / selfSize.Width;
			float scaleY = Math::IsZero(selfSize.Height) ? 0.f : rect.Size.Height / selfSize.Height;
			float scale = Math::Max(scaleX, scaleY);
			outScale.X = scale;
			outScale.Y = scale;
			outSize.Height = selfSize.Height*outScale.Y;
			outSize.Width = selfSize.Width*outScale.X;

		}
		break;
		case Stretch::Percent:
			outSize.Width = rect.Size.Width*strecthPercent.X;
			outSize.Height = rect.Size.Height*strecthPercent.Y;

			outScale.X = Math::IsZero(selfSize.Width) ? 0.f : outSize.Width / selfSize.Width;
			outScale.Y = Math::IsZero(selfSize.Width) ? 0.f : outSize.Height / selfSize.Height;
			break;
		case Stretch::None:
			outScale = Scale2F::One;
			outSize = selfSize;
			break;
		case Stretch::ExpandWidth:
			if (rect.Size.Width > selfSize.Width)
			{
				outScale.X = Math::IsZero(selfSize.Width) ? 0.f : rect.Size.Width / selfSize.Width;
				outScale.Y = outScale.X;
				outSize.Width = rect.Size.Width;
				outSize.Height = selfSize.Height*outScale.Y;
			}
			else
			{
				outScale = Scale2F::One;
				outSize = selfSize;
			}

			break;
		case Stretch::ExpandHeight:
			if (rect.Size.Height > selfSize.Height)
			{
				outScale.Y = Math::IsZero(selfSize.Height) ? 0.f : rect.Size.Height / selfSize.Height;
				outScale.X = outScale.Y;
				outSize.Height = rect.Size.Height;
				outSize.Width = selfSize.Width*outScale.X;
			}
			else
			{
				outScale = Scale2F::One;
				outSize = selfSize;
			}
			break;
		default:
			break;
	}

}


MEDUSA_END;
