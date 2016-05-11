#pragma once
#include "MedusaPreDeclares.h"
MEDUSA_BEGIN;

enum class FontOutlineType
{
	None,
	Line,
	Inner,
	Outer
};

enum class FontLCDFilterType
{
	None,
	Default,
	Light
};


enum class FontMarkupFlags
{
	None = 0,
	IsItalic = 1,
	IsBold = 2,
	HasUnderLine = 4,
	HasOverline = 8,
	HasStrikethrough = 16,
	DisableAutoHint = 32,
	DisableKerning = 64,

};


enum class FontFlags
{
	None = 0,
	HasHorizontal = 1,
	HasVertical = 2,
	HasKerning = 4,
	IsScalable = 8,
	IsItalic = 16,
	IsBold = 32,

};


MEDUSA_END;
