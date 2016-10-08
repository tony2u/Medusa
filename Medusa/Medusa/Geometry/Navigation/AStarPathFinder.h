// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IPathFinder.h"
#include "Core/Collection/PriorityQueue.h"
//[IGNORE_PRE_DECLARE_FILE]
MEDUSA_BEGIN;

template<typename TGraph>
class AStarPathFinder :public IPathFinder < TGraph >
{
	typedef typename IPathFinder < TGraph >::PathNode PathNodeType;
	class AStarPathNode :public PathNodeType	 
	{
	public:
		AStarPathNode() {}
		AStarPathNode(const NodeType* node, const NodeType* prev, int startToCurrentCost = 0, int currentToGoalCost = 0)
			:PathNodeType(node, prev, startToCurrentCost), CurrentToGoalCost(currentToGoalCost)
		{
		}
		AStarPathNode(const NodeType* current) :PathNodeType(current) {}

		bool operator==(const AStarPathNode& other)const { return this->Current == other.Current; }
		int Compare(const AStarPathNode& other)const
		{
			if (Math::IsEqual(this->CurrentToGoalCost, other.CurrentToGoalCost))
			{
				if (Math::IsEqual(this->StartToCurrentCost, other.StartToCurrentCost))
				{
					return 0;
				}
				return (this->StartToCurrentCost > other.StartToCurrentCost) ? -1 : 1;	//less first

			}
			return (CurrentToGoalCost > other.CurrentToGoalCost) ? 1 : -1;
		}
		int CurrentToGoalCost;
	};

public:
	AStarPathFinder(const TGraph* graph = nullptr) :IPathFinder < TGraph >(graph) {}
	virtual ~AStarPathFinder(void) {}

	virtual bool Run(const NodeType& start, const NodeType& goal, List<const NodeType*>* outPath)
	{
		mOpenList.Clear();
		mCloseList.Clear();

		AStarPathNode first(&start, &start, 0, 0);
		mOpenList.Push(first);

		List<const NodeType*> neighbors;
		while (!mOpenList.IsEmpty())
		{
			AStarPathNode currentNode = mOpenList.Top();
			mOpenList.Pop();

			if (currentNode.Current == &goal)
			{
				//extract path
				if (outPath != nullptr)
				{
					AStarPathNode* node = &currentNode;	//search by goal
					do
					{
						outPath->Append(node->Current);
						node = mCloseList.TryGetByOther(node->Prev, (intp)node->Prev);
					} while (node!=nullptr&&node->Current != node->Prev);
					outPath->Reverse();
				}

				return true;
			}
			mCloseList.Add(currentNode);

			neighbors.Clear();
			this->mGraph->GetNeighbors( *currentNode.Current, neighbors, this->mAgentCapablity,mOptions, currentNode.Prev);
			for (auto neighbor : neighbors)
			{
				CONTINUE_IF(mCloseList.ContainsOther(neighbor, (intp)neighbor));

				intp index = mOpenList.IndexOfOther(neighbor);
				if (index >= 0)
				{
					//update weight
					AStarPathNode& prev = mOpenList[index];	//prev is neighbor
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mOptions);
					int newPathCost = currentNode.StartToCurrentCost + currentToNeighborCost;
					if (prev.StartToCurrentCost > newPathCost)
					{
						//there's another shorter path
						prev.StartToCurrentCost = newPathCost;
						prev.Prev = currentNode.Current;
						mOpenList.HeapifyUp(index);
					}
				}
				else
				{
					//add to open list
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mOptions);
					int neighborToGoalCost = this->mGraph->HeuristicCost(*neighbor, goal, this->mOptions);
					AStarPathNode newNode(neighbor, currentNode.Current, currentNode.StartToCurrentCost + currentToNeighborCost, currentNode.StartToCurrentCost + currentToNeighborCost + neighborToGoalCost);
					mOpenList.Push(newNode);
				}
			}

		}
		return false;
	}

protected:
	PriorityQueue < AStarPathNode, EqualCompare, CustomCompare > mOpenList;
	HashSet<AStarPathNode> mCloseList;
};

MEDUSA_END;
