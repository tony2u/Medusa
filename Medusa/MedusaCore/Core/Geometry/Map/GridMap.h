// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Geometry/Size2.h"
#include "Core/Collection/List.h"
#include "Core/Geometry/GeometryAlgorithm.h"
#include "Core/Algorithm/PathFinding/DijkstraPathFinder.h"

MEDUSA_BEGIN;

template<typename TCell, typename TCellCompare = EqualCompare<TCell>>
class GridMap
{
public:
	typedef GridMap<TCell, TCellCompare> SelfType;
	typedef TCell CellType;
	typedef List<TCell, TCellCompare> CellList;
public:
	void Alloc(const Size2U& size)
	{
		mSize = size;
		mCells.ForceReserveCount(mSize.Area());

		FOR_EACH_SIZE(x, mSize.Width)
		{
			FOR_EACH_SIZE(y, mSize.Height)
			{
				uint id = x + y*mSize.Width;
				TCell& cell = mCells[id];
				cell.SetId(id);
				cell.SetIndex((int)x, (int)y);
			}
		}

	}

	uint ToId(int x, int y)const { return x + y*mSize.Width; }
	uint ToId(const Point2I& index)const { return ToId(index.X, index.Y); }

	const CellList& Cells() const { return mCells; }
	CellList& MutableCells() { return mCells; }

	uint Width()const { return mSize.Width; }
	uint Height()const { return mSize.Height; }
	const Size2U& Size() const { return mSize; }

	bool Contains(int x, int y)const { return x >= 0 && (uint)x < mSize.Width&&y >= 0 && (uint)y < mSize.Height; }
	bool Contains(const Point2I& index)const { return Contains(index.X, index.Y); }
	intp CellCount()const { return mCells.Count(); }

	const TCell& CellAt(int x, int y)const { return mCells[x + y*mSize.Width]; }
	const TCell& CellAt(const Point2I& index) const { return CellAt(index.X, index.Y); }

	TCell& MutableCellAt(int x, int y) { return mCells[x + y*mSize.Width]; }
	TCell& MutableCellAt(const Point2I& index) { return MutableCellAt(index.X, index.Y); }

	const TCell& operator[](const Point2I& index)const { return CellAt(index); }
	TCell& operator[](const Point2I& index) { return MutableCellAt(index); }


	const TCell* TryGetCell(int x, int y)const { return Contains(x, y) ? mCells.Items() + x + y*mSize.Width : nullptr; }
	const TCell* TryGetCell(const Point2I& index) const { return TryGetCell(index.X, index.Y); }

	TCell* TryGetMutableCell(int x, int y) { return Contains(x, y) ? mCells.MutableItems() + x + y*mSize.Width : nullptr; }
	TCell* TryGetMutableCell(const Point2I& index) { return TryGetMutableCell(index.X, index.Y); }

	int CalculateDistance(const TCell& from, const TCell& to, bool allowDiagonalMove = false)const
	{
		return CalculateDistance(from.Index(), to.Index(), allowDiagonalMove);
	}
	int CalculateDistance(const Point2I& from, const Point2I& to, bool allowDiagonalMove = false)const
	{
		return allowDiagonalMove ? GeometryAlgorithm::DiagonalDistanceEqually(from, to) : GeometryAlgorithm::ManhattanDistance(from, to);
	}

	int HeuristicCost(const TCell& from, const TCell& to, bool userData)const
	{
		return CalculateDistance(from, to, userData);
	}
	int RealCost(const TCell& from, const TCell& to, bool userData)const
	{
		return CalculateDistance(from, to, userData);
	}

	void GetNeighbors(const TCell& start, const TCell* prev, const TCell& node, List<const TCell*>& outNeighbors, uint agentCapablity = Math::UIntMaxValue, bool allowDiagonalMove = false)const
	{
		Point2I index = node.Index();
		//left 
		const TCell* nextCell = TryGetCell(index.X - 1, index.Y);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}
		//right
		nextCell = TryGetCell(index.X + 1, index.Y);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}
		//up
		nextCell = TryGetCell(index.X, index.Y + 1);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}
		//down
		nextCell = TryGetCell(index.X, index.Y - 1);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}

		RETURN_IF_FALSE(allowDiagonalMove);
		//left up
		nextCell = TryGetCell(index.X - 1, index.Y + 1);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}

		//left down
		nextCell = TryGetCell(index.X - 1, index.Y - 1);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}

		//right up
		nextCell = TryGetCell(index.X + 1, index.Y + 1);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}

		//right down
		nextCell = TryGetCell(index.X + 1, index.Y - 1);
		if (nextCell != nullptr&&nextCell != prev&&nextCell->IsWalkable(agentCapablity))
		{
			outNeighbors.Add(nextCell);
		}
	}

	void GetReachableCells(const TCell& node, uint moveDistance, List<const TCell*>& outNeighbors, bool allowDiagonalMove = false, bool ignoreObstacle = false, uint agentCapability = Math::UIntMaxValue)const
	{
		if (ignoreObstacle)
		{
			Point2I index = node.Index();

			Rect2I mapRect(Point2I::Zero, mSize);
			List<Point2I> outSpaces;
			GeometryAlgorithm::FindGridsInRange(mapRect, index, outSpaces, moveDistance, allowDiagonalMove);
			for (Point2I pos : outSpaces)
			{
				const TCell* cell = TryGetCell(pos);
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

protected:
	void GetReachableCellsStraightCareObstacle(const TCell& node, uint moveDistance, List<const TCell*>& outNeighbors, uint agentCapability = Math::UIntMaxValue)const
	{
		typedef DijkstraPathFinder<SelfType, TCell, bool> PathExplorer;
		PathExplorer explorer;
		explorer.SetGraph(this);
		explorer.SetUserData(true);
		HashSet<typename PathExplorer::PathNode> outPath;
		explorer.Explore(node, moveDistance, outPath, agentCapability);
		for (auto& node : outPath)
		{
			outNeighbors.Add(node.Current);
		}

	}

	void GetReachableCellsDiagonalCareObstacle(const TCell& node, uint moveDistance, List<const TCell*>& outNeighbors, uint agentCapability = Math::UIntMaxValue)const
	{
		typedef DijkstraPathFinder<SelfType, TCell, bool> PathExplorer;
		PathExplorer explorer;
		explorer.SetGraph(this);
		explorer.SetUserData(false);
		HashSet<typename PathExplorer::PathNode> outPath;
		explorer.Explore(node, moveDistance, outPath, agentCapability);
		for (auto& node : outPath)
		{
			outNeighbors.Add(node.Current);
		}
	}



protected:
	CellList mCells;
	Size2U mSize;
};

MEDUSA_END;
