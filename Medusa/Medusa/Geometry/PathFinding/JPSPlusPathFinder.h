// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Geometry/Point2.h"
#include "Geometry/Size2.h"
#include "Core/Collection/PriorityDictionary.h"
#include "Geometry/Map/GridCell.h"
#include "Geometry/Map/GridMap.h"
#include "IPathFinder.h"

MEDUSA_BEGIN;




/**********************************************
Y > 0
3    2    1
*  *  *
* * *
X < 0<--   4 ******* 0    -->X > 0
* * *
*  *  *
5    6    7
Y < 0
**********************************************/






struct JPSPlusPathFinder :public IPathFinder<GridMap<GridCell>,GridCell,void*>
{
	typedef GridCell Cell;
	typedef GridMap<Cell> Map;

	/*enum direction_t:char
	{
	Right = 0,
	RightUp = 1,
	Up = 2,
	LeftUp = 3,
	Left = 4,
	LeftDown = 5,
	Down = 6,
	RightDown = 7
	};*/

	typedef char Direction;

	struct PathNode	//[IGNORE_PRE_DECLARE_FILE]
	{
		int CurrentToGoalCost;         /* estimating cost from current cell to target */
		int StartToCurrentCost;         /* cost from current cell to start */
		const Cell* PrevCell;          /* previous cell */
		Direction PrevDirection; /* direction from pre_cell to current cell */
		bool IsClosed;                /* Whether this cell has been put to be closed */
	};

	JPSPlusPathFinder(const GraphType* map=nullptr)
		:IPathFinder<GridMap<GridCell>, GridCell,void*>(map)
	{
		mOpenList.ReserveSize(mGraph->Size().Width + mGraph->Size().Height);
		mPathNodes.ReserveSize(mGraph->CellCount());
		mPathNodes.ForceReserveCount(mGraph->CellCount());
		mOnlySaveJumpPoints = false;
	}

	~JPSPlusPathFinder()
	{

	}

	bool mOnlySaveJumpPoints;
	PriorityDictionary<int, const Cell*> mOpenList;
	List<PathNode, NoCompare> mPathNodes;

	const static uint MaxDirection = 7;
	const static Point2I mDirectionVectors[8];
	int HDistance(const Cell& from, const Cell& to)const
	{
		return Math::Max(Math::Abs(from.Index().X - to.Index().X), Math::Abs(from.Index().Y - to.Index().Y));
	}

	int GDistance(const Cell& from, const Cell& to, Direction direction)const
	{
		if (IsDirectionDiagonal(direction))
		{
			return 14 * Math::Abs(from.Index().X - to.Index().X);
		}
		if (IsDirectionVertical(direction))
		{
			return 10 * Math::Abs(from.Index().X - to.Index().X);
		}
		return  10 * Math::Abs(from.Index().Y - to.Index().Y);
	}

	static bool IsDirectionDiagonal(Direction direction)
	{
		return (uint)direction & 1;
	}
	static bool IsDirectionVertical(Direction direction)
	{
		return !((uint)direction & 3);
	}


	/**
	* Returns true if jps+ has been triggered where we have searched the path
	* and should return directly.
	*/
	bool TraversalNeighbours(const Cell* currentCell, const Cell* goalCell);


	const Cell* Jump(const Cell* nextCell, const Cell* goalCell, Direction direction, bool& outIsCompleted, Direction& outMarkedDirection);
	int LinkCell(const Cell* currentCell, const Cell* nextCell, Direction direction);
	int AddToOpenList(const Cell* currentCell, const Cell* nextCell, const Cell* goalCell, Direction direction);
	bool AddNeighbors(const Cell* currentCell, const Cell* nextCell, const Cell* goalCell, Direction direction);
	int ResolvePath(const Cell* startCell, const Cell* goalCell, List<const Cell*>& outPath);
	virtual bool Run(const Cell& startCell, const Cell& goalCell, List<const Cell*>* outPath);
	const Cell* NextWalkableCell(const Cell* cell, Direction direction);
};



MEDUSA_END;
