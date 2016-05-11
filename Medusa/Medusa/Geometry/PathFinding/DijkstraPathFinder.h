// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "IPathFinder.h"
#include "Core/Collection/PriorityQueue.h"

MEDUSA_BEGIN;

template<typename TGraph, typename TNode, typename TUserData>
class DijkstraPathFinder :public IPathFinder < TGraph, TNode, TUserData >
{
public:
	typedef typename IPathFinder < TGraph, TNode, TUserData >::PathNode PathNodeType;
	DijkstraPathFinder(const TGraph* graph = nullptr) :IPathFinder <TGraph, TNode, TUserData >(graph) {}
	virtual ~DijkstraPathFinder(void) {}


	virtual bool Run(const TNode& start, const TNode& goal, List<const TNode*>* outPath, uint agentCapablity = Math::UIntMaxValue)
	{
		this->mOpenList.Clear();
		mCloseList.Clear();

		PathNodeType first(&start, &start, 0);
		this->mOpenList.Push(first);

		List<const TNode*> neighbors;
		while (!this->mOpenList.IsEmpty())
		{
			PathNodeType currentNode = this->mOpenList.Pop();

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
			this->mGraph->GetNeighbors(start, currentNode.Prev, *currentNode.Current, neighbors, agentCapablity, this->mUserData);
			for (auto neighbor : neighbors)
			{
				CONTINUE_IF(mCloseList.ContainsOther(neighbor, (intp)neighbor));

				intp index = this->mOpenList.IndexOfOther(neighbor);
				if (index >= 0)
				{
					//update weight
					PathNodeType& prev = this->mOpenList[index];	//prev is neighbor
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mUserData);
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
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mUserData);
					PathNodeType newNode(neighbor, currentNode.Current, currentNode.StartToCurrentCost + currentToNeighborCost);
					this->mOpenList.Push(newNode);
				}
			}

		}
		return false;
	}

	virtual bool Explore(const TNode& start, int cost, HashSet<PathNodeType>& outValidNodes, uint agentCapablity = Math::UIntMaxValue)
	{
		this->mOpenList.Clear();
		PathNodeType first(&start, &start, 0);
		mOpenList.Push(first);

		List<const TNode*> neighbors;
		while (!mOpenList.IsEmpty())
		{
			PathNodeType currentNode = mOpenList.Pop();
			if (currentNode.StartToCurrentCost == cost)
			{
				outValidNodes.Add(currentNode);
				
			}
			else if (currentNode.StartToCurrentCost > cost)
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
			this->mGraph->GetNeighbors(start, currentNode.Prev, *currentNode.Current, neighbors, agentCapablity, this->mUserData);
			for (auto neighbor : neighbors)
			{
				CONTINUE_IF(outValidNodes.ContainsOther(neighbor, (intp)neighbor));

				intp index = mOpenList.IndexOfOther(neighbor);
				if (index >= 0)
				{
					//update weight
					PathNodeType& prev = mOpenList[index];	//prev is neighbor
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mUserData);
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
					int currentToNeighborCost = this->mGraph->RealCost(*currentNode.Current, *neighbor, this->mUserData);
					if (currentNode.StartToCurrentCost + currentToNeighborCost <= cost)
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
	PriorityQueue < PathNodeType, EqualCompare<PathNodeType>, CustomCompare<PathNodeType> > mOpenList;
	HashSet<PathNodeType> mCloseList;
};

MEDUSA_END;
