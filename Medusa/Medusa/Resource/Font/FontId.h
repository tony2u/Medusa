// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Geometry/Matrix2.h"
#include "Geometry/Color4.h"
#include "Core/IO/FileId.h"
#include "FontDefines.h"
MEDUSA_BEGIN;

class FontId :public FileId
{
public:
	const static byte LightLCDFilter[5];	// FT_LCD_FILTER_LIGHT   is (0x00, 0x55, 0x56, 0x55, 0x00)
	const static byte DefaultLCDFilter[5];	// FT_LCD_FILTER_DEFAULT is (0x10, 0x40, 0x70, 0x40, 0x10)
	const static FontId Empty;

public:
	FontId(const FileIdRef& fileId = FileIdRef::Empty, uint size = 0);
	FontId(const char* name, uint size = 0);

	FontId(const FontId& fontId);
	FontId& operator=(const FontId& fontId);

	intp HashCode()const;
	bool operator==(const FontId& val)const;
public:
	bool IsBitmap() const { return mIsBitmap; }

	bool HasOutline()const { return mOutlineType != FontOutlineType::None&&mOutlineThickness > 0 && mOutlineColor.A > 0.f; }
	bool HasHinting()const { return !MEDUSA_FLAG_HAS(mFlags,FontMarkupFlags::DisableAutoHint); }
	bool HasLCDFiltering()const { return mLCDFilterType != FontLCDFilterType::None; }
	bool HasKerning()const { return !MEDUSA_FLAG_HAS(mFlags, FontMarkupFlags::DisableKerning); }


	uint Size() const { return mSize; }
	void SetSize(uint val) { mSize = val; }

	const Matrix2& Matrix() const { return mMatrix; }
	void SetMatrix(const Matrix2& val) { mMatrix = val; }

	FontMarkupFlags Flags() const { return mFlags; }
	void SetFlags(FontMarkupFlags val) { mFlags = val; }

	FontOutlineType OutlineType() const { return mOutlineType; }
	void SetOutlineType(FontOutlineType val) { mOutlineType = val; }

	FontLCDFilterType LCDFilterType() const { return mLCDFilterType; }
	void SetLCDFilterType(FontLCDFilterType val) { mLCDFilterType = val; }

	uint OutlineThickness() const { return mOutlineThickness; }
	void SetOutlineThickness(uint val) { mOutlineThickness = val; }

	Color4F OutlineColor() const { return mOutlineColor; }
	void SetOutlineColor(Color4F color) { mOutlineColor = color; }

	Color4F Color() const { return mColor; }
	void SetColor(Color4F val) { mColor = val; }

	Color4F BackgroundColor() const { return mBackgroundColor; }
	void SetBackgroundColor(Color4F val) { mBackgroundColor = val; }

	Color4F UnderlineColor() const { return mUnderlineColor; }
	void SetUnderlineColor(Color4F val) { mUnderlineColor = val; }

	Color4F OverlineColor() const { return mOverlineColor; }
	void SetOverlineColor(Color4F val) { mOverlineColor = val; }

	Color4F StrikethroughColor() const { return mStrikethroughColor; }
	void SetStrikethroughColor(Color4F val) { mStrikethroughColor = val; }

	static bool IsBitmapFont(const StringRef& name);
private:
	bool mIsBitmap;


	uint mSize;	//0 means not specified

	float mRise = 0.f;	//Vertical displacement from the baseline.
	float mSpacing = 0.f;	//Spacing between letters.
	float mGamma = 0.f;	//Gamma correction.
	FontMarkupFlags mFlags;

	FontOutlineType mOutlineType = FontOutlineType::None;
	uint mUnderlineTickness = 0;
	uint mOutlineThickness = 0;	//The outline thickness for the characters.

	Color4F mColor;	//text color
	Color4F mBackgroundColor;
	Color4F mOutlineColor;
	Color4F mUnderlineColor;
	Color4F mOverlineColor;
	Color4F mStrikethroughColor;
	
	FontLCDFilterType mLCDFilterType = FontLCDFilterType::Default;
	Matrix2 mMatrix;


};


MEDUSA_END;