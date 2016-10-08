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
class DijkstraPathFinder :public IPathFinder < TGraph >
{
public:
	typedef typename IPathFinder < TGraph >::PathNode PathNodeType;
	DijkstraPathFinder(const TGraph* graph = nullptr) :IPathFinder <TGraph >(graph) {}
	virtual ~DijkstraPathFinder(void) {}


	virtual bool Run(const NodeType& start, const NodeType& goal, List<const NodeType*>* outPath)
	{
		this->mOpenList.Clear();
		mCloseList.Clear();

		PathNodeType first(&start, &start, 0);
		this->mOpenList.Push(first);

		List<const NodeType*> neighbors;
		while (!this->mOpenList.IsEmpty())
		{
			PathNodeType currentNode = this->mOpenList.Top();
			this->mOpenList.Pop();


			if (currentNode.Current == &goal)
			{
				//extract path
				if (outPath != nullptr)
				{
					PathNodeType* node = &currentNode;	//search by goal
					do
					{
						outPath->Append(node->Current);
						node = mCloseList.TryGetByOther(node->Prev, (intp)node->Prev);
					} while (node->Current != node->Prev);
					outPath->Reverse();
				}

				return true;
			}
			mCloseList.Add(currentNode);

			neighbors.Clear();
			this->mGraph->GetNeighbors(*currentNode.Current, neighbors, this->mAgentCapablity, this->mOptions, currentNode.Prev);
			for (auto neighbor : neighbors)
			{
				CONTINUE_IF(mCloseList.ContainsOther(neighbor, (intp)neighbor));

				intp index = this->mOpenList.IndexOfOther(neighbor);
				if (index >= 0)
				{
					//update weight
					PathNodeType& prev = this->mOpenList[index];	//prev is neighbor
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mOptions);
					int newPathCost = currentNode.StartToCurrentCost + currentToNeighborCost;
					if (prev.StartToCurrentCost > newPathCost)
					{
						//there's another shorter path
						prev.StartToCurrentCost = newPathCost;
						prev.Prev = currentNode.Current;
						this->mOpenList.HeapifyUp(index);
					}
				}
				else
				{
					//add to open list
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mOptions);
					PathNodeType newNode(neighbor, currentNode.Current, currentNode.StartToCurrentCost + currentToNeighborCost);
					this->mOpenList.Push(newNode);
				}
			}

		}
		return false;
	}

	virtual bool Explore(const NodeType& start, int maxCost, HashSet<PathNodeType>& outValidNodes)
	{
		this->mOpenList.Clear();
		PathNodeType first(&start, &start, 0);
		mOpenList.Push(first);

		List<const NodeType*> neighbors;
		while (!mOpenList.IsEmpty())
		{
			PathNodeType currentNode = mOpenList.Top();
			mOpenList.Pop();

			if (currentNode.StartToCurrentCost == maxCost)
			{
				outValidNodes.Add(currentNode);
				
			}
			else if (currentNode.StartToCurrentCost > maxCost)
			{
				continue;
			}
			else
			{
				if (currentNode.Current != &start)
				{
					outValidNodes.Add(currentNode);
				}
			}

			neighbors.Clear();
			this->mGraph->GetNeighbors(*currentNode.Current, neighbors, this->mAgentCapablity, this->mOptions, currentNode.Prev);
			for (auto neighbor : neighbors)
			{
				CONTINUE_IF(outValidNodes.ContainsOther(neighbor, (intp)neighbor));

				intp index = mOpenList.IndexOfOther(neighbor);
				if (index >= 0)
				{
					//update weight
					PathNodeType& prev = mOpenList[index];	//prev is neighbor
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
					if (currentNode.StartToCurrentCost + currentToNeighborCost <= maxCost)
					{
						PathNodeType newNode(neighbor, currentNode.Current, currentNode.StartToCurrentCost + currentToNeighborCost);
						mOpenList.Push(newNode);
					}

				}
			}

		}


		return !outValidNodes.IsEmpty();
	}

protected:
	PriorityQueue < PathNodeType, EqualCompare, CustomCompare > mOpenList;
	HashSet<PathNodeType> mCloseList;
};

MEDUSA_END;
