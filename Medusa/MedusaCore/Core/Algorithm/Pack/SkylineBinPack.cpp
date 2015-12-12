// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
/** @file SkylineBinPack.cpp
	@author Jukka Jyl?nki

	@brief Implements different bin packer algorithms that use the SKYLINE data structure.

	This work is released to Public Domain, do whatever you want with it.
*/
#include "MedusaCorePreCompiled.h"
#include "SkylineBinPack.h"
MEDUSA_BEGIN;

SkylineBinPack::SkylineBinPack()
	:mBinSize(Size2U::Zero)
{
}

SkylineBinPack::SkylineBinPack(const Size2U& size, bool useWasteMap/*=false*/)
{
	Init(size, useWasteMap);
}

void SkylineBinPack::Init(const Size2U& size, bool useWasteMap)
{
	mBinSize = size;

	mIsUseWasteMap = useWasteMap;
	mUsedSurfaceArea = 0;
	mLines.Clear();
	mUsedRects.Clear();

	Skyline line;
	line.Origin = 0;
	line.Width = mBinSize.Width;
	mLines.Add(line);

	if (mIsUseWasteMap)
	{
		mWasteMap.Init(size);
		mWasteMap.MutableFreeRects().Clear();
	}
}


void SkylineBinPack::GrowSize(const Size2U& newSize)
{
	RETURN_IF(mBinSize >= newSize);
	//add next line
	Skyline line;
	line.Origin.X = mBinSize.Width;
	line.Origin.Y = 0;
	line.Width = newSize.Width - mBinSize.Width;
	mLines.Add(line);
	mBinSize = newSize;

}



void SkylineBinPack::Insert(List<Size2U> &sizes, List<Rect2U> &outRects, LevelChoiceHeuristic method)
{
	while (sizes.Count() > 0)
	{
		Rect2U bestRect;
		Size2U bestSize(Math::IntMaxValue, Math::IntMaxValue);
		int bestSkylineIndex = -1;
		int bestRectIndex = -1;
		for (size_t i = 0; i < sizes.Count(); ++i)
		{
			Rect2U newRect;
			Size2U outBestSize;
			int outBestIndex = 0;
			switch (method)
			{
			case LevelChoiceHeuristic::LevelBottomLeft:
				newRect = FindPositionForNewNodeBottomLeft(sizes[i], outBestSize, outBestIndex);
				break;
			case LevelChoiceHeuristic::LevelMinWasteFit:
				newRect = FindPositionForNewNodeMinWaste(sizes[i], outBestSize.Height, outBestSize.Width, outBestIndex);
				break;
			default: assert(false); break;
			}

			if (newRect.Size.Height != 0)
			{
				if (outBestSize.Width < bestSize.Width || (outBestSize.Width == bestSize.Width && outBestSize.Height < bestSize.Height))
				{
					bestRect = newRect;
					bestSize = outBestSize;
					bestSkylineIndex = outBestIndex;
					bestRectIndex = (int)i;
				}
			}
		}

		if (bestRectIndex == -1)
			return;

		// Perform the actual packing.

		AddSkylineLevel(bestSkylineIndex, bestRect);
		mUsedSurfaceArea += (sizes[bestRectIndex]).Area();
		sizes.RemoveAt(bestRectIndex);
		outRects.Add(bestRect);
	}
}

Rect2U SkylineBinPack::Insert(const Size2U& size, LevelChoiceHeuristic method)
{
	if (mIsUseWasteMap)
	{
		// First try to pack this rectangle into the waste map, if it fits.
		Rect2U rect = mWasteMap.Insert(size, true, GuillotineBinPack::FreeRectChoiceHeuristic::RectBestShortSideFit,
			GuillotineBinPack::GuillotineSplitHeuristic::SplitMaximizeArea);

		if (rect.Size.Height != 0)
		{
			mUsedSurfaceArea += size.Area();
			return rect;
		}
	}


	switch (method)
	{
	case LevelChoiceHeuristic::LevelBottomLeft: return InsertBottomLeft(size);
	case LevelChoiceHeuristic::LevelMinWasteFit: return InsertMinWaste(size);
	default: assert(false); return Rect2U::Zero;
	}
}

bool SkylineBinPack::RectangleFits(int skylineNodeIndex, const Size2U& size, uint &outY) const
{
	RETURN_FALSE_IF(mLines[skylineNodeIndex].Origin.X + size.Width > mBinSize.Width);
	outY = mLines[skylineNodeIndex].Origin.Y;

	int widthLeft = size.Width;
	while (widthLeft > 0)
	{
		outY = Math::Max(outY, mLines[skylineNodeIndex].Origin.Y);
		RETURN_FALSE_IF(outY + size.Height > mBinSize.Height);

		widthLeft -= mLines[skylineNodeIndex].Width;
		++skylineNodeIndex;
		assert(skylineNodeIndex < (int)mLines.Count() || widthLeft <= 0);
	}
	return true;
}

bool SkylineBinPack::RectangleFits(int skylineNodeIndex, const Size2U& size, uint &outY, uint &outWastedArea) const
{
	bool fits = RectangleFits(skylineNodeIndex, size, outY);
	if (fits)
		outWastedArea = ComputeWastedArea(skylineNodeIndex, size, outY);

	return fits;
}

uint SkylineBinPack::ComputeWastedArea(int skylineNodeIndex, const Size2U& size, uint y) const
{
	uint wastedArea = 0;
	const uint rectLeft = mLines[skylineNodeIndex].Origin.X;
	const uint rectRight = rectLeft + size.Width;

	for (; skylineNodeIndex < (int)mLines.Count() && mLines[skylineNodeIndex].Origin.X < rectRight; ++skylineNodeIndex)
	{
		if (mLines[skylineNodeIndex].Origin.X >= rectRight || mLines[skylineNodeIndex].Right() <= rectLeft)
			break;

		int leftSide = mLines[skylineNodeIndex].Origin.X;
		int rightSide = Math::Min(rectRight, leftSide + mLines[skylineNodeIndex].Width);
		assert(y >= mLines[skylineNodeIndex].Origin.Y);
		wastedArea += (rightSide - leftSide) * (y - mLines[skylineNodeIndex].Origin.Y);
	}
	return wastedArea;
}

void SkylineBinPack::AddWasteMapArea(int skylineNodeIndex, const Size2U& size, uint y)
{
	// int wastedArea = 0; // unused
	const uint rectLeft = mLines[skylineNodeIndex].Origin.X;
	const uint rectRight = rectLeft + size.Width;

	for (; skylineNodeIndex < (int)mLines.Count() && mLines[skylineNodeIndex].Origin.X < rectRight; ++skylineNodeIndex)
	{
		if (mLines[skylineNodeIndex].Origin.X >= rectRight || mLines[skylineNodeIndex].Right() <= rectLeft)
			break;

		uint leftSide = mLines[skylineNodeIndex].Origin.X;
		uint rightSide = Math::Min(rectRight, leftSide + mLines[skylineNodeIndex].Width);
		assert(y >= mLines[skylineNodeIndex].Origin.Y);

		Rect2U waste;
		waste.Origin.X = leftSide;
		waste.Origin.Y = mLines[skylineNodeIndex].Origin.Y;
		waste.Size.Width = rightSide - leftSide;
		waste.Size.Height = y - mLines[skylineNodeIndex].Origin.Y;

		mWasteMap.MutableFreeRects().Add(waste);
	}
}

void SkylineBinPack::AddSkylineLevel(int skylineNodeIndex, const Rect2U &rect)
{
	// First track all wasted areas and mark them into the waste map if we're using one.
	if (mIsUseWasteMap)
	{
		AddWasteMapArea(skylineNodeIndex, rect.Size, rect.Origin.Y);
	}

	mUsedRects.Add(rect);

	Skyline newLine;
	newLine.Origin.X = rect.Origin.X;
	newLine.Origin.Y = rect.Top();
	newLine.Width = rect.Size.Width;
	mLines.Insert(skylineNodeIndex, newLine);

	assert(newLine.Right() <= mBinSize.Width);
	assert(newLine.Origin.Y <= mBinSize.Height);

	//remove occupied lines
	for (size_t i = skylineNodeIndex + 1; i < mLines.Count(); ++i)
	{
		assert(newLine.Origin.X <= mLines[i].Origin.X);

		if (mLines[i].Right() <= newLine.Right())
		{
			mLines.RemoveAt(i);
			--i;
		}
		else
		{
			int shrink = newLine.Right() - mLines[i].Origin.X;
			if (shrink>0)
			{
				mLines[i].Origin.X += shrink;
				mLines[i].Width -= shrink;
			}
			break;
		}
	}
	MergeSkylines();
}

void SkylineBinPack::MergeSkylines()
{
	for (size_t i = 0; i < mLines.Count() - 1; ++i)
	{
		if (mLines[i].Origin.Y == mLines[i + 1].Origin.Y)
		{
			mLines[i].Width += mLines[i + 1].Width;
			mLines.RemoveAt(i + 1);
			--i;
		}
	}
}

Rect2U SkylineBinPack::InsertBottomLeft(const Size2U& size)
{
	int outBestIndex;
	Size2U outBestSize;
	Rect2U newRect = FindPositionForNewNodeBottomLeft(size, outBestSize, outBestIndex);

	if (outBestIndex != -1)
	{
		// Perform the actual packing.
		AddSkylineLevel(outBestIndex, newRect);
		mUsedSurfaceArea += size.Area();
	}


	return newRect;
}

Rect2U SkylineBinPack::FindPositionForNewNodeBottomLeft(const Size2U& size, Size2U& outBestSize, int &outBestIndex) const
{
	outBestSize = Math::IntMaxValue;
	outBestIndex = -1;
	// Used to break ties if there are nodes at the same level. Then pick the narrowest one.
	Rect2U newRect = Rect2U::Zero;

	size_t lineCount = mLines.Count();
	uint minY = mBinSize.Height;

	for (size_t i = 0; i < lineCount; ++i)
	{
		uint outY;
		if (RectangleFits((int)i, size, outY)&&outY<minY)
		{
			minY = outY;	//find most bottom line
			if (outY + size.Height < outBestSize.Height || (outY + size.Height == outBestSize.Height && mLines[i].Width < outBestSize.Width))
			{
				outBestIndex = (int)i;

				outBestSize.Width = mLines[i].Width;
				outBestSize.Height = outY + size.Height;

				newRect.Origin.X = mLines[i].Origin.X;
				newRect.Origin.Y = outY;
				newRect.Size = size;
			}
		}
	}

	return newRect;
}

Rect2U SkylineBinPack::InsertMinWaste(const Size2U& size)
{
	uint bestHeight;
	uint bestWastedArea;
	int outBestIndex;
	Rect2U newRect = FindPositionForNewNodeMinWaste(size, bestHeight, bestWastedArea, outBestIndex);

	if (outBestIndex != -1)
	{
		// Perform the actual packing.
		AddSkylineLevel(outBestIndex, newRect);
		mUsedSurfaceArea += size.Area();

	}

	return newRect;
}

Rect2U SkylineBinPack::FindPositionForNewNodeMinWaste(const Size2U& size, uint &outBestHeight, uint &outBestWastedArea, int &outBestIndex) const
{
	outBestHeight = Math::UIntMaxValue;
	outBestWastedArea = Math::UIntMaxValue;
	outBestIndex = -1;
	Rect2U newNode = Rect2U::Zero;

	for (size_t i = 0; i < mLines.Count(); ++i)
	{
		uint outY;
		uint outWastedArea;

		if (RectangleFits((int)i, size, outY, outWastedArea))
		{
			if (outWastedArea < outBestWastedArea || (outWastedArea == outBestWastedArea && outY + size.Height < outBestHeight))
			{
				outBestHeight = outY + size.Height;
				outBestWastedArea = outWastedArea;
				outBestIndex = (int)i;

				newNode.Origin.X = mLines[i].Origin.X;
				newNode.Origin.Y = outY;
				newNode.Size = size;
			}
		}

	}

	return newNode;
}

/// Computes the ratio of used surface area.
float SkylineBinPack::Occupancy() const
{
	return (float)mUsedSurfaceArea / (mBinSize.Area());
}




MEDUSA_END;