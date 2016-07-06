// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
/** @file SkylineBinPack.h
	@author Jukka Jyl?nki

	@brief Implements different bin packer algorithms that use the SKYLINE data structure.

	This work is released to Public Domain, do whatever you want with it.
*/
#pragma once
#include "MedusaPreDeclares.h"
#include "GuillotineBinPack.h"
#include "Geometry/Rect2.h"
#include "Geometry/Point2.h"
MEDUSA_BEGIN;



/** Implements bin packing algorithms that use the SKYLINE data structure to store the bin contents. Uses
	GuillotineBinPack as the waste map. */
class SkylineBinPack
{
	/// Represents a single level (a horizontal line) of the skyline/horizon/envelope.
	struct Skyline
	{
		Point2U Origin;

		/// The line width. The ending coordinate (inclusive) will be x+width-1.
		uint Width;

		uint Right()const{return Origin.X+Width;}
	};
public:
	/// Defines the different heuristic rules that can be used to decide how to make the rectangle placements.
	enum class LevelChoiceHeuristic
	{
		LevelBottomLeft,
		LevelMinWasteFit
	};
public:
	/// Instantiates a bin of size (0,0). Call Init to create a new bin.
	SkylineBinPack();

	/// Instantiates a bin of the given size.
	SkylineBinPack(const Size2U& size,bool useWasteMap=false);

	/// (Re)initializes the packer to an empty bin of width x height units. Call whenever
	/// you need to restart with a new bin.
	void Init(const Size2U& size, bool useWasteMap);

	/// Inserts the given list of rectangles in an offline/batch mode, possibly rotated.
	/// @param rects The list of rectangles to insert. This vector will be destroyed in the process.
	/// @param dst [out] This list will contain the packed rectangles. The indices will not correspond to that of rects.
	/// @param method The rectangle placement rule to use when packing.
	void Insert(List<Size2U> &sizes, List<Rect2U>& outRects, LevelChoiceHeuristic method);

	/// Inserts a single rectangle into the bin, possibly rotated.
	Rect2U Insert(const Size2U& size, LevelChoiceHeuristic method);

	/// Computes the ratio of used surface area to the total bin area.
	float Occupancy() const;
	const List<Rect2U>& UsedRects() const { return mUsedRects; }

	void GrowSize(const Size2U& newSize);
private:
	Rect2U InsertBottomLeft(const Size2U& size);
	Rect2U InsertMinWaste(const Size2U& size);

	Rect2U FindPositionForNewNodeMinWaste(const Size2U& size, uint &outBestHeight, uint &outBestWastedArea, int &outBestIndex) const;
	Rect2U FindPositionForNewNodeBottomLeft(const Size2U& size, Size2U& outBestSize, int &outBestIndex) const;

	bool RectangleFits(int skylineNodeIndex, const Size2U& size, uint &outY) const;
	bool RectangleFits(int skylineNodeIndex, const Size2U& size, uint &outY, uint &outWastedArea) const;
	uint ComputeWastedArea(int skylineNodeIndex, const Size2U& size, uint y) const;

	void AddWasteMapArea(int skylineNodeIndex, const Size2U& size, uint y);

	void AddSkylineLevel(int skylineNodeIndex, const Rect2U &rect);

	/// Merges all skyline nodes that are at the same level.
	void MergeSkylines();

private:
	Size2U mBinSize;

	List<Skyline,NoCompare > mLines;

	uint mUsedSurfaceArea;

	/// If true, we use the GuillotineBinPack structure to recover wasted areas into a waste map.
	bool mIsUseWasteMap;
	GuillotineBinPack mWasteMap;
	List<Rect2U> mUsedRects;
};

MEDUSA_END;