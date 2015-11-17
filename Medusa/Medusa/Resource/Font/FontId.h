// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/Geometry/Matrix2.h"
#include "Core/Geometry/Color4.h"
#include "Core/IO/FileId.h"
#include "FontMarkupFlags.h"

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

enum class FontImageDepth
{
	MonoChrome=1,
	RGB=3,
	RGBA=4
};

class FontId:public FileId
{
public:
	const static byte LightLCDFilter[5];	// FT_LCD_FILTER_LIGHT   is (0x00, 0x55, 0x56, 0x55, 0x00)
	const static byte DefaultLCDFilter[5];	// FT_LCD_FILTER_DEFAULT is (0x10, 0x40, 0x70, 0x40, 0x10)
	const static FontId Default;
public:
	FontId(const FileIdRef& fileId=FileIdRef::Empty,uint size=12);
	FontId(const char* name, uint size = 12);

	FontId(const FontId& fontId);
	FontId& operator=(const FontId& fontId);

	intp HashCode()const;
	bool operator==(const FontId& val)const;
public:
	bool IsBitmap() const { return mIsBitmap; }

	bool HasOutline()const{return mOutlineType!=FontOutlineType::None;}
	bool HasHinting()const{return !mFlags.Has(FontMarkupFlags::DisableAutoHint);}
	bool HasLCDFiltering()const{return mLCDFilterType!=FontLCDFilterType::None;}
	bool HasKerning()const{return !mFlags.Has(FontMarkupFlags::DisableKerning);}

	FontImageDepth Depth() const { return mDepth; }
	void SetDepth(FontImageDepth val) { mDepth = val; }

	uint OriginalSize() const { return mOriginalSize; }
	void SetOriginalSize(uint val) { mOriginalSize = val; }

	uint Size() const { return mSize; }
	void SetSize(uint val){mSize=val;}

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

	static bool IsBitmapFont(const StringRef& name);
private:
	bool mIsBitmap;

	FontImageDepth mDepth= FontImageDepth::RGBA;
	uint mOriginalSize=0;
	
	uint mSize;

	float mRise=0.f;	//Vertical displacement from the baseline.
	float mSpacing=0.f;	//Spacing between letters.
	float mGamma=0.f;	//Gamma correction.
	FontMarkupFlags mFlags;

	FontOutlineType mOutlineType= FontOutlineType::None;
	uint mUnderlineTickness=0;
	uint mOutlineThickness=0;	//The outline thickness for the characters.
	
	Color4F mColor;	//text color
	Color4F mBackgroundColor;
	Color4F mOutlineColor;	
	Color4F mUnderlineColor;	
	Color4F mOverlineColor;		
	Color4F mStrikethroughColor;
	FontLCDFilterType mLCDFilterType= FontLCDFilterType::None;
	Matrix2 mMatrix;		

	
};


MEDUSA_END;