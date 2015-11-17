// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#include "Core/Collection/List.h"
#include "Core/Collection/HashSet.h"


MEDUSA_BEGIN;

/*
template<typename TNode>
class SearchTrait
{
public:
void GetNeighbors(const TNode* prev,const TNode& node, List<TNode>& outNeighbors,void* searchOptions);	//prev may be null
int HeuristicCost(const TNode& from, const TNode& to,void* searchOptions);
int RealCost(const TNode& from, const TNode& to,void* searchOptions);
};
*/

template<typename TGraph, typename TNode,typename TUserData>
class IPathFinder
{
public:
	typedef TGraph GraphType;
	typedef TNode NodeType;

	class PathNode	//[IGNORE_PRE_DECLARE_FILE]
	{
	public:
		PathNode() {}
		PathNode(const TNode* node, const TNode* prev, int startToCurrentCost = 0)
			:Current(node), Prev(prev), StartToCurrentCost(startToCurrentCost)
		{
		}
		PathNode(const TNode* current) :Current(current) {}

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
		const TNode* Current;
		const TNode* Prev;
	};
public:
	IPathFinder(const TGraph* graph = nullptr) :mGraph(graph) {}

	virtual ~IPathFinder(void) {}
	const TGraph* Graph() const { return mGraph; }
	void SetGraph(const TGraph* val) { mGraph = val; }
	TUserData UserData() const { return mUserData; }
	void SetUserData(TUserData val) { mUserData = val; }
public:
	virtual bool Run(const TNode& start, const TNode& goal, List<const TNode*>* outPath) { return false; }	//outPath null means no need path
	virtual bool Explore(const TNode& start, int cost, HashSet<PathNode>& outValidNodes) { return false; }
protected:
	const TGraph* mGraph;
	TUserData mUserData;

};

MEDUSA_END;
