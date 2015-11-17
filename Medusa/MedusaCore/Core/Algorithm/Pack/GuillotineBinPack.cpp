// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
/** @file GuillotineBinPack.cpp
@author Jukka Jyl?nki

@brief Implements different bin packer algorithms that use the GUILLOTINE data structure.

This work is released to Public Domain, do whatever you want with it.
*/
#include "MedusaCorePreCompiled.h"
#include "GuillotineBinPack.h"
#include "Core/Memory/Memory.h"
#include "Core/Math/Math.h"
MEDUSA_BEGIN;

GuillotineBinPack::GuillotineBinPack():mBinSize(Size2U::Zero)
{
}

GuillotineBinPack::GuillotineBinPack(const Size2U& size)
{
	Init(size);
}

void GuillotineBinPack::Init(const Size2U& size)
{
	mBinSize=size;

	// Clear any memory of previously packed rectangles.
	mUsedRects.Clear();

	// We start with a single big free rectangle that spans the whole bin.
	Rect2U n(Point2I::Zero,size);

	mFreeRects.Clear();
	mFreeRects.Add(n);
}

void GuillotineBinPack::Insert(List<Size2U> &sizes, bool isMerge, FreeRectChoiceHeuristic rectChoice, GuillotineSplitHeuristic splitMethod)
{
	// Remember variables about the best packing choice we have made so far during the iteration process.
	size_t bestFreeRectIndex = 0;
	size_t bestRectIndex = 0;

	// Pack rectangles one at a time until we have cleared the rects array of all rectangles.
	// rects will get destroyed in the process.
	while(!sizes.IsEmpty())
	{
		// Stores the penalty score of the best rectangle placement - bigger=worse, smaller=better.
		int bestScore = Math::IntMaxValue;
		size_t freeRectCount=mFreeRects.Count();
		size_t rectCount = sizes.Count();
		FOR_EACH_SIZE(i,freeRectCount)
		{
			FOR_EACH_SIZE(j,rectCount)
			{
				// If this rectangle is a perfect match, we pick it instantly.
				if (sizes[j] == mFreeRects[i].Size)
				{
					bestFreeRectIndex = i;
					bestRectIndex = j;
					bestScore = Math::IntMinValue;
					i = mFreeRects.Count(); // Force a jump out of the outer loop as well - we got an instant fit.
					break;
				}
				else if (sizes[j].Width <= mFreeRects[i].Size.Width && sizes[j].Height <= mFreeRects[i].Size.Height)
				{
					// Try if we can fit the rectangle upright.
					int score = ScoreByHeuristic(sizes[j], mFreeRects[i], rectChoice);
					if (score < bestScore)
					{
						bestFreeRectIndex = i;
						bestRectIndex = j;
						bestScore = score;
					}
				}
			}
		}

		// If we didn't manage to find any rectangle to pack, abort.
		if (bestScore == Math::IntMaxValue)
			return;

		// Otherwise, we're good to go and do the actual packing.
		Rect2U newRect(mFreeRects[bestFreeRectIndex].Origin,sizes[bestRectIndex]);

		// Remove the free space we lost in the bin.
		SplitFreeRectByHeuristic(mFreeRects[bestFreeRectIndex], newRect, splitMethod);
		mFreeRects.RemoveAt(bestFreeRectIndex);

		// Remove the rectangle we just packed from the input list.
		sizes.RemoveAt(bestRectIndex);

		// Perform a Rectangle Merge step if desired.
		if (isMerge)
			MergeFreeList();

		// Remember the new used rectangle.
		mUsedRects.Add(newRect);

	}

}

/*
// A helper function for GUILLOTINE-MAXFITTING. Counts how many rectangles fit into the given rectangle
// after it has been split.
void CountNumFitting(const Rect2U &freeRect, const Size2U& size, const List<Size2U> &rects, 
int usedRectIndex, bool splitHorizontal, int &score1, int &score2)
{
const int w = freeRect.Width - width;
const int h = freeRect.Height - height;

Rect2U bottom;
bottom.X = freeRect.X;
bottom.Y = freeRect.Y + height;
bottom.Height = h;

Rect2U right;
right.X = freeRect.X + width;
right.Y = freeRect.Y;
right.Width = w;

if (splitHorizontal)
{
bottom.Width = freeRect.Width;
right.Height = height;
}
else // Split vertically
{
bottom.Width = width;
right.Height = freeRect.Height;
}

int fitBottom = 0;
int fitRight = 0;
for(size_t i = 0; i < rects.Count(); ++i)
if (i != usedRectIndex)
{
if (FitsPerfectly(rects[i], bottom))
fitBottom |= 0x10000000;
if (FitsPerfectly(rects[i], right))
fitRight |= 0x10000000;

if (Fits(rects[i], bottom))
++fitBottom;
if (Fits(rects[i], right))
++fitRight;
}

score1 = min(fitBottom, fitRight);
score2 = max(fitBottom, fitRight);
}
*/
/*
// Implements GUILLOTINE-MAXFITTING, an experimental heuristic that's really cool but didn't quite work in practice.
void GuillotineBinPack::InsertMaxFitting(List<Size2U> &rects, List<Rect2U> &dst, bool merge, 
FreeRectChoiceHeuristic rectChoice, GuillotineSplitHeuristic splitMethod)
{
dst.Clear();
int bestRect = 0;
bool bestFlipped = false;
bool bestSplitHorizontal = false;

// Pick rectangles one at a time and pack the one that leaves the most choices still open.
while(rects.Count() > 0 && freeRectangles.Count() > 0)
{
int bestScore1 = -1;
int bestScore2 = -1;

///\todo Different sort predicates.
clb::sort::QuickSort(&freeRectangles[0], freeRectangles.Count(), CompareRectShortSide);

Rect2U &freeRect = freeRectangles[0];

for(size_t j = 0; j < rects.Count(); ++j)
{
int score1;
int score2;

if (rects[j].Width == freeRect.Width && rects[j].Height == freeRect.Height)
{
bestRect = j;
bestFlipped = false;
bestScore1 = bestScore2 = Math::IntMaxValue;
break;
}
else if (rects[j].Width <= freeRect.Width && rects[j].Height <= freeRect.Height)
{
CountNumFitting(freeRect, rects[j].Width, rects[j].Height, rects, j, false, score1, score2);

if (score1 > bestScore1 || (score1 == bestScore1 && score2 > bestScore2))
{
bestRect = j;
bestScore1 = score1;
bestScore2 = score2;
bestFlipped = false;
bestSplitHorizontal = false;
}

CountNumFitting(freeRect, rects[j].Width, rects[j].Height, rects, j, true, score1, score2);

if (score1 > bestScore1 || (score1 == bestScore1 && score2 > bestScore2))
{
bestRect = j;
bestScore1 = score1;
bestScore2 = score2;
bestFlipped = false;
bestSplitHorizontal = true;
}
}

if (rects[j].Height == freeRect.Width && rects[j].Width == freeRect.Height)
{
bestRect = j;
bestFlipped = true;
bestScore1 = bestScore2 = Math::IntMaxValue;
break;
}
else if (rects[j].Height <= freeRect.Width && rects[j].Width <= freeRect.Height)
{
CountNumFitting(freeRect, rects[j].Height, rects[j].Width, rects, j, false, score1, score2);

if (score1 > bestScore1 || (score1 == bestScore1 && score2 > bestScore2))
{
bestRect = j;
bestScore1 = score1;
bestScore2 = score2;
bestFlipped = true;
bestSplitHorizontal = false;
}

CountNumFitting(freeRect, rects[j].Height, rects[j].Width, rects, j, true, score1, score2);

if (score1 > bestScore1 || (score1 == bestScore1 && score2 > bestScore2))
{
bestRect = j;
bestScore1 = score1;
bestScore2 = score2;
bestFlipped = true;
bestSplitHorizontal = true;
}
}
}

if (bestScore1 >= 0)
{
Rect2U newNode;
newNode.X = freeRect.X;
newNode.Y = freeRect.Y;
newNode.Width = rects[bestRect].Width;
newNode.Height = rects[bestRect].Height;
if (bestFlipped)
std::swap(newNode.Width, newNode.Height);

SplitFreeRectAlongAxis(freeRect, newNode, bestSplitHorizontal);

rects.erase(rects.begin() + bestRect);

if (merge)
MergeFreeList();

usedRectangles.Add(newNode);

}

freeRectangles.erase(freeRectangles.begin());
}
}
*/

Rect2U GuillotineBinPack::Insert(const Size2U& size, bool isMerge, FreeRectChoiceHeuristic rectChoice, GuillotineSplitHeuristic splitMethod)
{
	// Find where to put the new rectangle.
	int outFreeNodeIndex = 0;
	Rect2U newRect = FindPositionForNewNode(size, rectChoice, outFreeNodeIndex);

	// Abort if we didn't have enough space in the bin.
	if (newRect.Size.Height == 0)
		return newRect;

	// Remove the space that was just consumed by the new rectangle.
	SplitFreeRectByHeuristic(mFreeRects[outFreeNodeIndex], newRect, splitMethod);
	mFreeRects.RemoveAt(outFreeNodeIndex);

	// Perform a Rectangle Merge step if desired.
	if (isMerge)
		MergeFreeList();

	// Remember the new used rectangle.
	mUsedRects.Add(newRect);


	return newRect;
}

/// Computes the ratio of used surface area to the total bin area.
float GuillotineBinPack::Occupancy() const
{
	///\todo The occupancy rate could be cached/tracked incrementally instead
	///      of looping through the list of packed rectangles here.
	unsigned long usedSurfaceArea = 0;
	size_t usedCount=mUsedRects.Count();
	FOR_EACH_SIZE(i,usedCount)
	{
		usedSurfaceArea += mUsedRects[i].Size.Width * mUsedRects[i].Size.Height;
	}

	return (float)usedSurfaceArea / (mBinSize.Area());
}

/// Returns the heuristic score value for placing a rectangle of size width*height into freeRect. Does not try to rotate.
int GuillotineBinPack::ScoreByHeuristic(const Size2U& size, const Rect2U &freeRect, FreeRectChoiceHeuristic rectChoice)
{
	switch(rectChoice)
	{
	case FreeRectChoiceHeuristic::RectBestAreaFit: return ScoreBestAreaFit(size, freeRect);
	case FreeRectChoiceHeuristic::RectBestShortSideFit: return ScoreBestShortSideFit(size, freeRect);
	case FreeRectChoiceHeuristic::RectBestLongSideFit: return ScoreBestLongSideFit(size, freeRect);
	case FreeRectChoiceHeuristic::RectWorstAreaFit: return ScoreWorstAreaFit(size, freeRect);
	case FreeRectChoiceHeuristic::RectWorstShortSideFit: return ScoreWorstShortSideFit(size, freeRect);
	case FreeRectChoiceHeuristic::RectWorstLongSideFit: return ScoreWorstLongSideFit(size, freeRect);
	default: assert(false); return Math::IntMaxValue;
	}
}

int GuillotineBinPack::ScoreBestAreaFit(const Size2U& size, const Rect2U &freeRect)
{
	return freeRect.Area() - size.Area();
}

int GuillotineBinPack::ScoreBestShortSideFit(const Size2U& size, const Rect2U &freeRect)
{
	int leftoverHoriz = Math::Abs((int)freeRect.Size.Width - (int)size.Width);
	int leftoverVert = Math::Abs((int)freeRect.Size.Height - (int)size.Height);
	int leftover = Math::Min(leftoverHoriz, leftoverVert);
	return leftover;
}

int GuillotineBinPack::ScoreBestLongSideFit(const Size2U& size, const Rect2U &freeRect)
{
	int leftoverHoriz = Math::Abs((int)freeRect.Size.Width - (int)size.Width);
	int leftoverVert = Math::Abs((int)freeRect.Size.Height - (int)size.Height);
	int leftover = Math::Min(leftoverHoriz, leftoverVert);
	return leftover;
}

int GuillotineBinPack::ScoreWorstAreaFit(const Size2U& size, const Rect2U &freeRect)
{
	return -ScoreBestAreaFit(size, freeRect);
}

int GuillotineBinPack::ScoreWorstShortSideFit(const Size2U& size, const Rect2U &freeRect)
{
	return -ScoreBestShortSideFit(size, freeRect);
}

int GuillotineBinPack::ScoreWorstLongSideFit(const Size2U& size, const Rect2U &freeRect)
{
	return -ScoreBestLongSideFit(size, freeRect);
}

Rect2U GuillotineBinPack::FindPositionForNewNode(const Size2U& size, FreeRectChoiceHeuristic rectChoice, int& outNodeIndex)
{
	Rect2U bestNode=Rect2U::Zero;
	bestNode.Size=size;
	int bestScore = Math::IntMaxValue;

	/// Try each free rectangle to find the best one for placement.
	size_t freeCount=mFreeRects.Count();
	FOR_EACH_SIZE(i,freeCount)
	{
		// If this is a perfect fit upright, choose it immediately.
		if (size==mFreeRects[i].Size)
		{
			
			outNodeIndex = (int)i;
			return mFreeRects[i];
		}
		else if (size<=mFreeRects[i].Size)
		{
			// Does the rectangle fit upright?
			int score = ScoreByHeuristic(size, mFreeRects[i], rectChoice);

			if (score < bestScore)
			{
				bestNode.Origin=mFreeRects[i].Origin;
				bestScore = score;
				outNodeIndex = (int)i;
			}
		}
	}
	return bestNode;
}

void GuillotineBinPack::SplitFreeRectByHeuristic(const Rect2U &freeRect, const Rect2U &placedRect, GuillotineSplitHeuristic method)
{
	// Compute the lengths of the leftover area.
	Size2U size=freeRect.Size-placedRect.Size;

	// Placing placedRect into freeRect results in an L-shaped free area, which must be split into
	// two disjoint rectangles. This can be achieved with by splitting the L-shape using a single line.
	// We have two choices: horizontal or vertical.	

	// Use the given heuristic to decide which choice to make.

	bool splitHorizontal;
	switch(method)
	{
	case GuillotineSplitHeuristic::SplitShorterLeftoverAxis:
		// Split along the shorter leftover axis.
		splitHorizontal = (size.Width <= size.Height);
		break;
	case GuillotineSplitHeuristic::SplitLongerLeftoverAxis:
		// Split along the longer leftover axis.
		splitHorizontal = (size.Width > size.Height);
		break;
	case GuillotineSplitHeuristic::SplitMinimizeArea:
		// Maximize the larger area == minimize the smaller area.
		// Tries to make the single bigger rectangle.
		splitHorizontal = (placedRect.Size.Width * size.Height > size.Width * placedRect.Size.Height);
		break;
	case GuillotineSplitHeuristic::SplitMaximizeArea:
		// Maximize the smaller area == minimize the larger area.
		// Tries to make the rectangles more even-sized.
		splitHorizontal = (placedRect.Size.Width * size.Height <= size.Width * placedRect.Size.Height);
		break;
	case GuillotineSplitHeuristic::SplitShorterAxis:
		// Split along the shorter total axis.
		splitHorizontal = (freeRect.Size.Width <= freeRect.Size.Height);
		break;
	case GuillotineSplitHeuristic::SplitLongerAxis:
		// Split along the longer total axis.
		splitHorizontal = (freeRect.Size.Width > freeRect.Size.Height);
		break;
	default:
		splitHorizontal = true;
		assert(false);
	}

	// Perform the actual split.
	SplitFreeRectAlongAxis(freeRect, placedRect, splitHorizontal);
}

/// This function will add the two generated rectangles into the freeRectangles array. The caller is expected to
/// remove the original rectangle from the freeRectangles array after that.
void GuillotineBinPack::SplitFreeRectAlongAxis(const Rect2U &freeRect, const Rect2U &placedRect, bool splitHorizontal)
{
	// Form the two new rectangles.
	Rect2U bottom;
	bottom.Origin.X = freeRect.Origin.X;
	bottom.Origin.Y = freeRect.Top();
	bottom.Size.Height = freeRect.Size.Height - placedRect.Size.Height;

	Rect2U right;
	right.Origin.X = freeRect.Right();
	right.Origin.Y = freeRect.Origin.Y;
	right.Size.Width = freeRect.Size.Width - placedRect.Size.Width;

	if (splitHorizontal)
	{
		bottom.Size.Width = freeRect.Size.Width;
		right.Size.Height = placedRect.Size.Height;
	}
	else // Split vertically
	{
		bottom.Size.Width = placedRect.Size.Width;
		right.Size.Height = freeRect.Size.Height;
	}

	// Add the new rectangles into the free rectangle pool if they weren't degenerate.
	if (bottom.Size.Width > 0 && bottom.Size.Height > 0)
	{
		mFreeRects.Add(bottom);
	}
	if (right.Size.Width > 0 && right.Size.Height > 0)
	{
		mFreeRects.Add(right);
	}

}

void GuillotineBinPack::MergeFreeList()
{
	// Do a Theta(n^2) loop to see if any pair of free rectangles could me merged into one.
	// Note that we miss any opportunities to merge three rectangles into one. (should call this function again to detect that)
	for(size_t i = 0; i < mFreeRects.Count(); ++i)
	{
		for(size_t j = i+1; j < mFreeRects.Count(); ++j)
		{
			if (mFreeRects[i].Size.Width == mFreeRects[j].Size.Width && mFreeRects[i].Origin.X == mFreeRects[j].Origin.X)
			{
				if (mFreeRects[i].Origin.Y == mFreeRects[j].Top())
				{
					mFreeRects[i].Origin.Y -= mFreeRects[j].Size.Height;
					mFreeRects[i].Size.Height += mFreeRects[j].Size.Height;
					mFreeRects.RemoveAt(j);
					--j;
				}
				else if (mFreeRects[i].Top() == mFreeRects[j].Origin.Y)
				{
					mFreeRects[i].Size.Height += mFreeRects[j].Size.Height;
					mFreeRects.RemoveAt(j);
					--j;
				}
			}
			else if (mFreeRects[i].Size.Height == mFreeRects[j].Size.Height && mFreeRects[i].Origin.Y == mFreeRects[j].Origin.Y)
			{
				if (mFreeRects[i].Origin.X == mFreeRects[j].Origin.X + mFreeRects[j].Size.Width)
				{
					mFreeRects[i].Origin.X -= mFreeRects[j].Size.Width;
					mFreeRects[i].Size.Width += mFreeRects[j].Size.Width;
					mFreeRects.RemoveAt(j);
					--j;
				}
				else if (mFreeRects[i].Right() == mFreeRects[j].Origin.X)
				{
					mFreeRects[i].Size.Width += mFreeRects[j].Size.Width;
					mFreeRects.RemoveAt(j);
					--j;
				}
			}
		}

	}
}

MEDUSA_END;
