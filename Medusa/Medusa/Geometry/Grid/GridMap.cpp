// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "GridMap.h"
#include "Geometry/Navigation/DijkstraPathFinder.h"
#include "Geometry/Navigation/NavigationAlgorithm.h"
MEDUSA_BEGIN;

GridMap::~GridMap()
{
	for (CellRow* row : mCells)
	{
		SAFE_DELETE_COLLECTION(*row);
		delete row;
	}
}

Point2I GridMap::ToIndex(const Point2F& pos) const
{
	return NavigationAlgorithm::ToGridIndex(mGridSize, pos);
}

Point2F GridMap::ToPosition(Point2I index)
{
	return mpp(mGridSize*index.X, mGridSize*index.Y);
}

void GridMap::Alloc(const Size2F& size, float gridSize)
{
	mGridSize = gridSize;
	auto cellSize = NavigationAlgorithm::ToGridSize(size, gridSize);
	Alloc(cellSize);
}

void GridMap::Alloc(const Size2U& size)
{
	Expand(size, true);
}

bool GridMap::Add(GridCell* cell)
{
	CellRow* row = mCells[cell->Y()];
	RETURN_FALSE_IF_NULL(row);
	GridCell* prevCell = row->Get(cell->X());
	RETURN_FALSE_IF_NOT_NULL(prevCell);
	cell->SetMap(this);
	row->Set(cell->X(), cell);
	return true;
}

GridCell* GridMap::TryAddCell(const Point2I& index)
{
	GridCell* cell= MutableCellAt(index);
	RETURN_SELF_IF_NOT_NULL(cell);
	cell = new GridCell(index);
	Add(cell);
	return cell;
}

void GridMap::Expand(const Size2U& size, bool allocCell /*= false*/)
{
	Size2U newSize = size;
	newSize.Width = Math::Max(mSize.Width, newSize.Width);
	newSize.Height = Math::Max(mSize.Height, newSize.Height);

	RETURN_IF_EQUAL(mSize, newSize);
	mCells.ForceReserveCount(newSize.Height);
	FOR_EACH_SIZE(y, newSize.Height)
	{
		CellRow* row = mCells[y];
		if (row == nullptr)
		{
			row = new CellRow();
			mCells[y] = row;
		}

		row->ForceReserveCount(newSize.Width);
	}

	if (allocCell)
	{
		FOR_EACH_SIZE_BEGIN_END(y, mSize.Height, newSize.Height - 1)
		{
			CellRow* row = mCells[y];
			FOR_EACH_SIZE(x, newSize.Width)
			{
				GridCell* cell = new GridCell((int)x, (int)y);
				cell->SetMap(this);
				row->Set(cell->X(), cell);
			}
		}

		FOR_EACH_SIZE(y, mSize.Height)
		{
			CellRow* row = mCells[y];
			FOR_EACH_SIZE_BEGIN_END(x, mSize.Width, newSize.Width - 1)
			{
				GridCell* cell = new GridCell((int)x, (int)y);
				cell->SetMap(this);
				row->Set(cell->X(), cell);

			}
		}
	}
	mSize = size;
}

void GridMap::GetReachableCellsDiagonalCareObstacle(const GridCell& node, uint moveDistance, List<const GridCell*>& outNeighbors, uint agentCapability /*= Math::UIntMaxValue*/) const
{
	typedef DijkstraPathFinder< GridMap> PathExplorer;
	PathExplorer explorer;
	explorer.SetGraph(this);
	explorer.SetOptions(false);
	explorer.SetAgentCapablity(agentCapability);
	HashSet<typename PathExplorer::PathNode> outPath;
	explorer.Explore(node, moveDistance, outPath);
	for (auto& tNode : outPath)
	{
		outNeighbors.Add(tNode.Current);
	}
}

void GridMap::GetReachableCellsStraightCareObstacle(const GridCell& node, uint moveDistance, List<const GridCell*>& outNeighbors, uint agentCapability /*= Math::UIntMaxValue*/) const
{
	typedef DijkstraPathFinder<GridMap> PathExplorer;
	PathExplorer explorer;
	explorer.SetGraph(this);
	explorer.SetOptions(true);
	explorer.SetAgentCapablity(agentCapability);
	HashSet<typename PathExplorer::PathNode> outPath;
	explorer.Explore(node, moveDistance, outPath);
	for (auto& tNode : outPath)
	{
		outNeighbors.Add(tNode.Current);
	}
}

void GridMap::GetReachableCells(const GridCell& node, uint moveDistance, List<const GridCell*>& outNeighbors, bool allowDiagonalMove /*= false*/, bool ignoreObstacle /*= false*/, uint agentCapability /*= Math::UIntMaxValue*/) const
{
	if (ignoreObstacle)
	{
		Point2I index = node.Index();

		Rect2I mapRect(mOffset, mSize);
		List<Point2I> outSpaces;
		NavigationAlgorithm::FindGridsInRange(mapRect, index, outSpaces, moveDistance, allowDiagonalMove);
		for (Point2I pos : outSpaces)
		{
			const GridCell* cell = CellAt(pos);
			if (cell != nullptr)
			{
				outNeighbors.Add(cell);
			}
		}
	}
	else
	{
		if (allowDiagonalMove)
		{
			GetReachableCellsDiagonalCareObstacle(node, moveDistance, outNeighbors, agentCapability);
		}
		else
		{
			GetReachableCellsStraightCareObstacle(node, moveDistance, outNeighbors, agentCapability);
		}
	}
}


const GridCell* GridMap::CellAt(int x, int y) const
{
	RETURN_NULL_IF_FALSE(IsValidIndex(x, y));
	const CellRow* row = mCells[y];
	RETURN_NULL_IF_NULL(row);
	return row->Get(x);
}

GridCell* GridMap::MutableCellAt(int x, int y)
{
	RETURN_NULL_IF_FALSE(IsValidIndex(x, y));

	CellRow* row = mCells[y];
	RETURN_NULL_IF_NULL(row);
	return row->Get(x);
}

int GridMap::CalculateDistance(const GridCell& from, const GridCell& to, bool allowDiagonalMove /*= false*/) const
{
	return CalculateDistance(from.Index(), to.Index(), allowDiagonalMove);
}

int GridMap::CalculateDistance(const Point2I& from, const Point2I& to, bool allowDiagonalMove /*= false*/) const
{
	return allowDiagonalMove ? NavigationAlgorithm::DiagonalDistanceEqually(from, to) : NavigationAlgorithm::ManhattanDistance(from, to);
}

int GridMap::HeuristicCost(const GridCell& from, const GridCell& to, bool allowDiagonalMove) const
{
	return CalculateDistance(from, to, allowDiagonalMove);
}

int GridMap::RealCost(const GridCell& from, const GridCell& to, bool allowDiagonalMove) const
{
	return CalculateDistance(from, to, allowDiagonalMove);
}

void GridMap::GetNeighbors( const GridCell& node, List<const GridCell*>& outNeighbors, uint agentCapablity /*= Math::UIntMaxValue*/, bool allowDiagonalMove /*= false*/, const GridCell* ignore/*=nullptr*/) const
{
	Point2I index = node.Index();
	//left 
	const GridCell* nextCell = node.HasDirection(MoveDirection::Left) ? CellAt(index.X - 1, index.Y) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}
	//right
	nextCell = node.HasDirection(MoveDirection::Right) ? CellAt(index.X + 1, index.Y) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}
	//up
	nextCell = node.HasDirection(MoveDirection::Up) ? CellAt(index.X, index.Y + 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}
	//down
	nextCell = node.HasDirection(MoveDirection::Down) ? CellAt(index.X, index.Y - 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}

	RETURN_IF_FALSE(allowDiagonalMove);
	//left up
	nextCell = node.HasDirection(MoveDirection::LeftUp) ? CellAt(index.X - 1, index.Y + 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}

	//left down
	nextCell = node.HasDirection(MoveDirection::LeftDown) ? CellAt(index.X - 1, index.Y - 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}

	//right up
	nextCell = node.HasDirection(MoveDirection::RightUp) ? CellAt(index.X + 1, index.Y + 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}

	//right down
	nextCell = node.HasDirection(MoveDirection::RightDown) ? CellAt(index.X + 1, index.Y - 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		outNeighbors.Add(nextCell);
	}
}

List<MoveDirection> GridMap::GetAvailableDirections(const GridCell& node, uint agentCapablity /*= Math::UIntMaxValue*/, bool allowDiagonalMove /*= false*/, const GridCell* ignore /*= nullptr*/) const
{
	List<MoveDirection> directions;
	Point2I index = node.Index();
	//left 
	const GridCell* nextCell = node.HasDirection(MoveDirection::Left) ? CellAt(index.X - 1, index.Y) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::Left);
	}
	//right
	nextCell = node.HasDirection(MoveDirection::Right) ? CellAt(index.X + 1, index.Y) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::Right);
	}
	//up
	nextCell = node.HasDirection(MoveDirection::Up) ? CellAt(index.X, index.Y + 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::Up);
	}
	//down
	nextCell = node.HasDirection(MoveDirection::Down) ? CellAt(index.X, index.Y - 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::Down);
	}
	if (!allowDiagonalMove)
	{
		return directions;
	}

	//left up
	nextCell = node.HasDirection(MoveDirection::LeftUp) ? CellAt(index.X - 1, index.Y + 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::LeftUp);
	}

	//left down
	nextCell = node.HasDirection(MoveDirection::LeftDown) ? CellAt(index.X - 1, index.Y - 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::LeftDown);
	}

	//right up
	nextCell = node.HasDirection(MoveDirection::RightUp) ? CellAt(index.X + 1, index.Y + 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::RightUp);
	}

	//right down
	nextCell = node.HasDirection(MoveDirection::RightDown) ? CellAt(index.X + 1, index.Y - 1) : nullptr;
	if (nextCell != nullptr&&nextCell != ignore&&nextCell->IsWalkable(agentCapablity))
	{
		directions.Add(MoveDirection::RightDown);
	}

	return directions;

}



bool GridMap::IsForwardWalkable(const GridCell& start, MoveDirection direction, uint agentCapablity /*= Math::UIntMaxValue*/) const
{
	RETURN_FALSE_IF_FALSE(start.HasDirection(direction));
	Point2I index = start.Index();
	Point2I forward= NavigationAlgorithm::ToVector(direction);
	index += forward;
	const GridCell* nextCell = CellAt(index);
	RETURN_FALSE_IF_NULL(nextCell);
	return nextCell->IsWalkable(agentCapablity);
}

MEDUSA_END;