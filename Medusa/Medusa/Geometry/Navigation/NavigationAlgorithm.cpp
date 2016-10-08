// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "NavigationAlgorithm.h"

MEDUSA_BEGIN;


Point2I NavigationAlgorithm::ToGridIndex(float gridSize, const Point2F& pos)
{
	return Point2I((int)Math::Floor(pos.X / gridSize), (int)Math::Floor(pos.Y / gridSize));
}

Size2U NavigationAlgorithm::ToGridSize(Size2F size, float gridSize)
{
	return Size2U((uint)Math::Floor(size.Width / gridSize), (uint)Math::Floor(size.Height / gridSize));
}

Point2I NavigationAlgorithm::ToVector(MoveDirection direction)
{
	switch (direction)
	{
	case MoveDirection::Left:
		return Point2I(-1, 0);
	case MoveDirection::Right:
		return Point2I(1, 0);
	case MoveDirection::Down:
		return Point2I(0, -1);
	case MoveDirection::Up:
		return Point2I(0, 1);
	case MoveDirection::LeftUp:
		return Point2I(-1, 1);
	case MoveDirection::RightUp:
		return Point2I(1, 1);
	case MoveDirection::LeftDown:
		return Point2I(-1, -1);
	case MoveDirection::RightDown:
		return Point2I(1, -1);
	}
	return Point2I::Zero;
}

MoveDirection NavigationAlgorithm::Reverse(MoveDirection direction)
{
	switch (direction)
	{
	case MoveDirection::Left:
		return MoveDirection::Right;
	case MoveDirection::Right:
		return MoveDirection::Left;
	case MoveDirection::Down:
		return MoveDirection::Up;
	case MoveDirection::Up:
		return MoveDirection::Down;
	case MoveDirection::LeftUp:
		return MoveDirection::RightDown;
	case MoveDirection::RightUp:
		return MoveDirection::LeftDown;
	case MoveDirection::LeftDown:
		return MoveDirection::RightUp;
	case MoveDirection::RightDown:
		return MoveDirection::LeftUp;
	}
	return MoveDirection::None;
}

void NavigationAlgorithm::FindGridsInRange(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, int maxDistance, bool allowDiagnoal)
{
	FOR_EACH_INT32_BEGIN_END(d, 1, (int)maxDistance)
	{
		FindGridsWithDistance(rect, cur, outSpaces, d, allowDiagnoal);
	}
}

void NavigationAlgorithm::FindGridsWithDistance(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, int distance, bool allowDiagnoal)
{
	Point2I pos;

	if (allowDiagnoal)
	{
		//top
		pos.Y = cur.Y + distance;
		FOR_EACH_INT32_BEGIN_END(dx, -distance, distance)
		{
			pos.X = cur.X + dx;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
		//bottom
		pos.Y = cur.Y - distance;
		FOR_EACH_INT32_BEGIN_END(dx, -distance, distance)
		{
			pos.X = cur.X + dx;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//left
		pos.X = cur.X - distance;
		FOR_EACH_INT32_BEGIN_END(dy, -distance + 1, distance - 1)
		{
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//right
		pos.X = cur.X + distance;
		FOR_EACH_INT32_BEGIN_END(dy, -distance + 1, distance - 1)
		{
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
	}
	else
	{
		//right top
		FOR_EACH_INT32_END_BEGIN(dx, distance, 0)
		{
			int dy = distance - dx;
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
		//right bottom
		FOR_EACH_INT32_END_BEGIN(dx, distance, 0)
		{
			int dy = -(distance - dx);
			CONTINUE_IF_ZERO(dy);	//ignore duplicate 0
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//left top
		FOR_EACH_INT32_BEGIN_END(dx, -distance, -1)
		{
			int dy = distance + dx;
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}

		//left bottom
		FOR_EACH_INT32_BEGIN_END(dx, -distance, -1)
		{
			int dy = -(distance + dx);
			CONTINUE_IF_ZERO(dy);	//ignore duplicate 0
			pos.X = cur.X + dx;
			pos.Y = cur.Y + dy;
			if (rect.Contains(pos))
			{
				outSpaces.Add(pos);
			}
		}
	}

}

void NavigationAlgorithm::FindGridsNear(const Rect2I& rect, const Point2I& cur, List<Point2I>& outSpaces, bool allowDiagnoal)
{
	/*
	-1,1	0,1		1,1
	-1,0	(0,0)	1,0
	-1,-1	0,-1	1,-1
	*/

	Point2I pos = cur;

	//right center
	pos.X = cur.X + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//top center
	pos.X = cur.X;
	pos.Y = cur.Y + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//bottom center
	pos.Y = cur.Y - 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//left center
	pos.X = cur.X - 1;
	pos.Y = cur.Y;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}

	RETURN_IF_FALSE(allowDiagnoal);

	//right top
	pos = cur + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}

	//right bottom
	pos.Y = cur.Y - 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//left top
	pos.X = cur.X - 1;
	pos.Y = cur.Y + 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
	//left bottom
	pos = cur - 1;
	if (rect.Contains(pos))
	{
		outSpaces.Add(pos);
	}
}

void NavigationAlgorithm::BresenhamLine(Point2I from, Point2I to, List<Point2I>& outPoints, bool allowDiagonalMove/*=true*/)
{
	int x1 = from.X;
	int y1 = from.Y;

	int x2 = to.X;
	int y2 = to.Y;

	int dx = x2 - x1;
	int dy = y2 - y1;
	int ux = (dx > 0) ? 1 : -1;//x的增量方向，取或-1
	int uy = (dy > 0) ? 1 : -1;//y的增量方向，取或-1
	int x = x1;
	int y = y1;
	int  eps = 0;//eps为累加误差

	dx = Math::Abs(dx);
	dy = Math::Abs(dy);
	if (dx > dy)
	{
		for (x = x1; ; x += ux)
		{
			outPoints.Emplace(x, y);

			if (x == x2)
			{
				//last point
				break;
			}
			eps += dy;
			if ((eps << 1) >= dx)
			{
				if (!allowDiagonalMove)
				{
					outPoints.Emplace(x + ux, y);
				}
				y += uy;
				eps -= dx;
			}


		}

	}
	else
	{
		for (y = y1; ; y += uy)
		{
			outPoints.Emplace(x, y);
			if (y == y2)
			{
				break;
			}
			eps += dx;
			if ((eps << 1) >= dy)
			{
				if (!allowDiagonalMove)
				{
					outPoints.Emplace(x, y + uy);
				}

				x += ux;
				eps -= dy;
			}
		}
	}
}

Point2F NavigationAlgorithm::LinearMove(Point2F from, Point2F to, float distance)
{
	Point2F delta = to - from;
	Point2F move = Point2F::Zero;
	if (Math::IsZero(delta.X))
	{
		move.X = 0.f;
		move.Y = distance*Math::Sign(delta.Y);
	}
	else
	{
		float k = Math::Atan2(delta.Y, delta.X);
		move.X = distance* Math::Cos(k);
		move.Y = distance* Math::Sin(k);

		if (delta.X >= 0.f)
		{
			move.X = Math::Min(move.X, delta.X);
		}
		else
		{
			move.X = Math::Max(move.X, delta.X);
		}
	}

	if (delta.Y >= 0.f)
	{
		move.Y = Math::Min(move.Y, delta.Y);
	}
	else
	{
		move.Y = Math::Max(move.Y, delta.Y);
	}

	return move;
}

float NavigationAlgorithm::MoveAlongPath(const List<Point2F>& path, uint& refNextIndex, Point2F& refCurrentPosition, float distance)
{
	uint count = path.Count();
	if (refNextIndex >= count)	//reach end
	{
		refNextIndex = count;
		refCurrentPosition = path.Last();
		return 0.f;
	}

	float leftDistance = distance;
	while (leftDistance >= 0.f&&refNextIndex < count)
	{
		const Point2F& target = path[refNextIndex];
		auto targetDistance = Point2F::Distance(refCurrentPosition, target);
		if (targetDistance > leftDistance)
		{
			//still in current node
			auto move = LinearMove(refCurrentPosition, target, leftDistance);
			refCurrentPosition += move;
			return distance;
		}
		else
		{
			//cross next node
			leftDistance -= targetDistance;
			refCurrentPosition = target;
			++refNextIndex;
		}
	}

	return distance - leftDistance;

}

MEDUSA_END;


