// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Geometry/Size2.h"
#include "Core/Collection/List.h"
#include "GridCell.h"

MEDUSA_BEGIN;

class GridMap
{
public:
	typedef GridCell NodeType;
	typedef bool MovementOptionsType;

	typedef GridCell CellType;
	typedef List<GridCell*> CellRow;
	typedef List<CellRow*> CellTable;

	~GridMap();
public:
	bool AllowDiagonalMove()const { return mAllowDiagonalMove; }
	void EnableAllowDiagonalMove(bool val) { mAllowDiagonalMove = val; }

	float GridSize() const { return mGridSize; }
	void SetGridSize(float val) { mGridSize = val; }
	Point2I ToIndex(const Point2F& pos)const;
	Point2F ToPosition(Point2I index);

	void Alloc(const Size2F& size,float gridSize);
	void Alloc(const Size2U& size);
	bool Add(GridCell* cell);
	GridCell* TryAddCell(const Point2I& index);

	void Expand(const Size2U& size,bool allocCell=false);


	uint ToId(int x, int y)const { return x + y*mSize.Width; }
	uint ToId(const Point2I& index)const { return ToId(index.X, index.Y); }

	const CellTable& Cells() const { return mCells; }
	CellTable& MutableCells() { return mCells; }

	uint Width()const { return mSize.Width; }
	uint Height()const { return mSize.Height; }
	const Size2U& Size() const { return mSize; }

	bool IsValidIndex(int x, int y)const { return x >= 0 && (uint)x < mSize.Width&&y >= 0 && (uint)y < mSize.Height; }
	bool IsValidIndex(const Point2I& index)const { return IsValidIndex(index.X, index.Y); }
	intp CellCount()const { return mCells.Count(); }

	const GridCell* CellAt(int x, int y)const;
	const GridCell* CellAt(const Point2I& index) const { return CellAt(index.X, index.Y); }

	GridCell* MutableCellAt(int x, int y);
	GridCell* MutableCellAt(const Point2I& index) { return MutableCellAt(index.X, index.Y); }

	const GridCell* operator[](const Point2I& index)const { return CellAt(index); }
	GridCell* operator[](const Point2I& index) { return MutableCellAt(index); }

	int CalculateDistance(const GridCell& from, const GridCell& to, bool allowDiagonalMove = false)const;
	int CalculateDistance(const Point2I& from, const Point2I& to, bool allowDiagonalMove = false)const;

	int HeuristicCost(const GridCell& from, const GridCell& to, bool allowDiagonalMove)const;
	int RealCost(const GridCell& from, const GridCell& to, bool allowDiagonalMove)const;

	void GetNeighbors(const GridCell& node, List<const GridCell*>& outNeighbors, uint agentCapablity = Math::UIntMaxValue, bool allowDiagonalMove = false, const GridCell* ignore=nullptr)const;
	void GetReachableCells(const GridCell& node, uint moveDistance, List<const GridCell*>& outNeighbors, bool allowDiagonalMove = false, bool ignoreObstacle = false, uint agentCapability = Math::UIntMaxValue)const;

	List<MoveDirection> GetAvailableDirections(const GridCell& node, uint agentCapablity = Math::UIntMaxValue, bool allowDiagonalMove = false, const GridCell* ignore = nullptr)const;
	bool IsForwardWalkable(const GridCell& start, MoveDirection direction, uint agentCapablity = Math::UIntMaxValue)const;
protected:
	void GetReachableCellsStraightCareObstacle(const GridCell& node, uint moveDistance, List<const GridCell*>& outNeighbors, uint agentCapability = Math::UIntMaxValue)const;
	void GetReachableCellsDiagonalCareObstacle(const GridCell& node, uint moveDistance, List<const GridCell*>& outNeighbors, uint agentCapability = Math::UIntMaxValue)const;
protected:
	float mGridSize=0.f;
	bool mAllowDiagonalMove=false;
	
	CellTable mCells;
	Point2I mOffset{ 0,0 };
	Size2U mSize{ 0,0 };

	GridMap* mParentMap = nullptr;
};

MEDUSA_END;
