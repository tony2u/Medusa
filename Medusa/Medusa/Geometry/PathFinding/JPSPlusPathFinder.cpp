// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "JPSPlusPathFinder.h"
MEDUSA_BEGIN;





bool JPSPlusPathFinder::TraversalNeighbours(const Cell* currentCell, const Cell* goalCell)
{
	PathNode& pathNode = mPathNodes[currentCell->Id()];
	if (!pathNode.PrevCell)
	{
		bool nonblock[9];
		char direction;
		for (direction = 0; direction <= JPSPlusPathFinder::MaxDirection; direction += 2)
		{
			const Cell* nextCell = NextWalkableCell(currentCell, (Direction)direction);

			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell, goalCell, direction))
				nonblock[direction] = nextCell ? 1 : 0;
		}
		nonblock[8] = nonblock[0];
		for (direction = 1; direction <= JPSPlusPathFinder::MaxDirection && nonblock[direction - 1] && nonblock[direction + 1]; direction += 2)
		{
			const Cell* next_cell = NextWalkableCell(currentCell, (Direction)direction);
			RETURN_TRUE_IF(AddNeighbors(currentCell, next_cell, goalCell, direction));
		}
	}
	else
	{
		if (IsDirectionDiagonal(pathNode.PrevDirection)) /*diagonal*/
		{
			/* natural neighbor */
			const Cell* nextCell1 = NextWalkableCell(currentCell, pathNode.PrevDirection);
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell1, goalCell, pathNode.PrevDirection));
			const Cell* nextCell2 = NextWalkableCell(currentCell, (Direction)(pathNode.PrevDirection + 1));
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell2, goalCell, pathNode.PrevDirection + 1));
			const Cell* nextCell3 = NextWalkableCell(currentCell, pathNode.PrevDirection - 1);
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell3, goalCell, pathNode.PrevDirection - 1));
		}
		else/*straight*/
		{
			/* natural neighbor */
			const Cell* nextCell1 = NextWalkableCell(currentCell, pathNode.PrevDirection);
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell1, goalCell, pathNode.PrevDirection));
			/* forced neighbor */
			const Cell* nextCell2 = NextWalkableCell(currentCell, pathNode.PrevDirection + 3);
			const Cell* nextCell3 = nextCell2 ? nullptr : NextWalkableCell(currentCell, pathNode.PrevDirection + 2);

			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell3, goalCell, pathNode.PrevDirection + 2));
			const Cell* nextCell4 = !(nextCell3 && nextCell1) ? nullptr : NextWalkableCell(currentCell, pathNode.PrevDirection + 1);
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell4, goalCell, pathNode.PrevDirection + 1));
			/* forced neighbor */
			const Cell* nextCell5 = NextWalkableCell(currentCell, pathNode.PrevDirection + 5);
			const Cell* nextCell6 = nextCell5 ? nullptr : NextWalkableCell(currentCell, pathNode.PrevDirection + 6);
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell6, goalCell, pathNode.PrevDirection + 6));
			const Cell* nextCell7 = !(nextCell6 && nextCell1) ? nullptr : NextWalkableCell(currentCell, pathNode.PrevDirection + 7);
			RETURN_TRUE_IF(AddNeighbors(currentCell, nextCell7, goalCell, pathNode.PrevDirection + 7));
		}
	}
	return false;
}



bool JPSPlusPathFinder::Run(const Cell& startCell, const Cell& goalCell, List<const Cell*>* outPath)
{
	if (startCell.Capability()!=0 || goalCell.Capability()!=0)
		return false;

	mOpenList.Clear();
	mPathNodes.Clear();

	PathNode& pathNode = mPathNodes[startCell.Id()];
	pathNode.CurrentToGoalCost = HDistance(startCell, goalCell);
	mOpenList.Push(pathNode.CurrentToGoalCost, &startCell);

	while (!mOpenList.IsEmpty())
	{
		const Cell* currentCell = mOpenList.Top().Value;
		if (currentCell == &goalCell)
			break;
		mOpenList.Pop();

		mPathNodes[currentCell->Id()].IsClosed = 1;

		if (TraversalNeighbours(currentCell, &goalCell))
		{
			if (outPath!=nullptr)
			{
				return ResolvePath(&startCell, &goalCell,*outPath) > 0;
			}
			return true;
		}
	}

	if (outPath != nullptr)
	{
		ResolvePath(&startCell, &goalCell, *outPath);
	}

	return true;
}


const JPSPlusPathFinder::Cell* JPSPlusPathFinder::NextWalkableCell(const Cell* cell, Direction direction)
{
	Point2I vector = mDirectionVectors[(uint)direction&MaxDirection];
	vector += cell->Index();
	if (!mGraph->Contains(vector))
		return nullptr;

	cell = &mGraph->CellAt(vector);
	if (cell->Capability()!=0)
		return nullptr;

	return cell;
}

int JPSPlusPathFinder::ResolvePath(const Cell* startCell, const Cell* goalCell, List<const Cell*>& outPath)
{
	const Cell* currentCell = goalCell;

	if (mOnlySaveJumpPoints)
	{
		while (currentCell != startCell)
		{
			PathNode& pathNode = mPathNodes[currentCell->Id()];
			if (!pathNode.PrevCell)
				break;
			outPath.Add(currentCell);
			currentCell = pathNode.PrevCell;

		}
	}
	else
	{
		while (currentCell != startCell)
		{
			PathNode& pathNode = mPathNodes[currentCell->Id()];
			if (!pathNode.PrevCell)
				break;

			while (currentCell != pathNode.PrevCell)
			{
				outPath.Add(currentCell);
				Point2I vector = JPSPlusPathFinder::mDirectionVectors[(pathNode.PrevDirection + 4)&JPSPlusPathFinder::MaxDirection];  //anti direction
				vector += currentCell->Index();
				currentCell = &mGraph->CellAt(vector);
			}
		}
	}

	return (int)outPath.Count();
}

bool JPSPlusPathFinder::AddNeighbors(const Cell* currentCell, const Cell* nextCell, const Cell* goalCell, Direction direction)
{
	RETURN_FALSE_IF_NULL(nextCell);
	bool outIsCompleted = false;
	Direction outMarkedDirection;
	const Cell* nextNextCell = Jump(nextCell, goalCell, direction, outIsCompleted, outMarkedDirection);
	if (outIsCompleted)
	{
		LinkCell(currentCell, nextNextCell, (direction));
		LinkCell(nextNextCell, goalCell, outMarkedDirection);
		return true;
	}
	if (nextNextCell)
	{
		AddToOpenList(currentCell, nextNextCell, goalCell, direction);
	}
	return false;
}

int JPSPlusPathFinder::AddToOpenList(const Cell* currentCell, const Cell* nextCell, const Cell* goalCell, Direction direction)
{
	PathNode& nextPathNode = mPathNodes[nextCell->Id()];
	if (nextPathNode.IsClosed) return 0;

	PathNode& currentPathNode = mPathNodes[currentCell->Id()];
	intp index = mOpenList.IndexOfValue(nextCell);

	if (index < 0)	//outside 
	{
		nextPathNode.PrevCell = currentCell;
		nextPathNode.PrevDirection = direction;
		nextPathNode.StartToCurrentCost = currentPathNode.StartToCurrentCost + GDistance(*currentCell, *nextCell, direction);
		nextPathNode.CurrentToGoalCost = HDistance(*nextCell, *goalCell);
		int priority = nextPathNode.StartToCurrentCost + nextPathNode.CurrentToGoalCost;
		mOpenList.Push(priority, nextCell);
		return 1;
	}

	int newStartToCurrentCost = currentPathNode.StartToCurrentCost + GDistance(*currentCell, *nextCell, direction);
	if (newStartToCurrentCost < nextPathNode.StartToCurrentCost)
	{
		nextPathNode.PrevCell = currentCell;
		nextPathNode.PrevDirection = direction;
		nextPathNode.StartToCurrentCost = newStartToCurrentCost;
		int priority = newStartToCurrentCost + nextPathNode.CurrentToGoalCost;
		mOpenList.Update(index, priority);
		return 2;
	}

	return 0;
}

int JPSPlusPathFinder::LinkCell(const Cell* currentCell, const Cell* nextCell, Direction direction)
{
	if (currentCell == nextCell)
		return 0;
	PathNode& nextPathNode = mPathNodes[nextCell->Id()];
	nextPathNode.PrevCell = currentCell;
	nextPathNode.PrevDirection = direction;
	return 1;
}

const JPSPlusPathFinder::Cell* JPSPlusPathFinder::Jump(const Cell* nextCell, const Cell* goalCell, Direction direction, bool& outIsCompleted, Direction& outMarkedDirection)
{
	/* assert(next_cell != nullptr); */
	const Cell *nextNextCell1, *nextNextCell2, *nextNextCell3;

	if (nextCell == goalCell)
	{
		outIsCompleted = true;
		outMarkedDirection = direction;
		return nextCell;
	}

	if (!IsDirectionDiagonal(direction))
	{
		if (((!NextWalkableCell(nextCell, (direction)+3) && NextWalkableCell(nextCell, (direction)+2)) || (!NextWalkableCell(nextCell, (direction)+5) && NextWalkableCell(nextCell, (direction)+6))))
			return nextCell;
	}
	else
	{
		nextNextCell1 = NextWalkableCell(nextCell, direction + 1);
		if (nextNextCell1 && Jump(nextNextCell1, goalCell, direction + 1, outIsCompleted, outMarkedDirection))
			return nextCell;

		nextNextCell2 = NextWalkableCell(nextCell, direction - 1);
		if (nextNextCell2 && Jump(nextNextCell2, goalCell, direction - 1, outIsCompleted, outMarkedDirection))
			return nextCell;
		/* can't walk through DIAGONAL block */
		if (!nextNextCell1 || !nextNextCell2)
			return nullptr;
	}

	nextNextCell3 = NextWalkableCell(nextCell, direction);
	return nextNextCell3 ? Jump(nextNextCell3, goalCell, direction, outIsCompleted, outMarkedDirection) : nullptr;
}

/*Definition of global vector array from direction */
const Point2I JPSPlusPathFinder::mDirectionVectors[8] = {
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ -1, 1 },
	{ -1, 0 },
	{ -1, -1 },
	{ 0, -1 },
	{ 1, -1 }
};

MEDUSA_END;
