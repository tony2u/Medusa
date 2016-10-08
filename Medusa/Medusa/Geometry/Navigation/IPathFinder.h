// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Collection/HashSet.h"
//[IGNORE_PRE_DECLARE_FILE]

MEDUSA_BEGIN;

/*
template<typename NodeType>
class SearchTrait
{
public:
void GetNeighbors(const NodeType* prev,const NodeType& node, List<NodeType>& outNeighbors,void* searchOptions);	//prev may be null
int HeuristicCost(const NodeType& from, const NodeType& to,void* searchOptions);
int RealCost(const NodeType& from, const NodeType& to,void* searchOptions);
};
*/

template<typename TGraph>
class IPathFinder
{
public:
	typedef TGraph GraphType;
	using NodeType=typename GraphType::NodeType;
	using OptionsType = typename GraphType::MovementOptionsType;


	class PathNode
	{
	public:
		PathNode() {}
		PathNode(const NodeType* node, const NodeType* prev, int startToCurrentCost = 0)
			:Current(node), Prev(prev), StartToCurrentCost(startToCurrentCost)
		{
		}
		PathNode(const NodeType* current) :Current(current) {}

		bool operator==(const PathNode& other)const { return Current == other.Current; }
		int Compare(const PathNode& other)const
		{
			if (Math::IsEqual(StartToCurrentCost, other.StartToCurrentCost))
			{
				return (StartToCurrentCost > other.StartToCurrentCost) ? -1 : 1;	//less first
			}
			return 0;
		}
		intp HashCode()const
		{
			return (intp)Current;
		}

		int StartToCurrentCost;
		const NodeType* Current;
		const NodeType* Prev;
	};
public:
	IPathFinder(const TGraph* graph = nullptr) :mGraph(graph) {}

	virtual ~IPathFinder(void) {}
	const TGraph* Graph() const { return mGraph; }
	void SetGraph(const TGraph* val) { mGraph = val; }

	OptionsType Options() const { return mOptions; }
	void SetOptions(OptionsType val) { mOptions = val; }

	uint AgentCapablity() const { return mAgentCapablity; }
	void SetAgentCapablity(uint val) { mAgentCapablity = val; }
public:
	virtual bool Run(const NodeType& start, const NodeType& goal, List<const NodeType*>* outPath) { return false; }	//outPath null means no need path
	virtual bool Explore(const NodeType& start, int cost, HashSet<PathNode>& outValidNodes) { return false; }
protected:
	const TGraph* mGraph=nullptr;
	OptionsType mOptions;	//used to pass it back to cost functions
	uint mAgentCapablity = Math::UIntMaxValue;	//default can walk anywhere
	
};

MEDUSA_END;
