// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Font/IFont.h"
#include "Core/Memory/MemoryData.h"

#include "Lib/Common/freetype/ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_STROKER_H
#include FT_LCD_FILTER_H

MEDUSA_BEGIN;

class TTFFont:public IFont
{
public:
	static bool InitializeLibrary();
	static bool UninitializeLibrary();

	static TTFFont* CreateFromFile(const FontId& fontId);
	static TTFFont* CreateFromData(const FontId& fontId,const MemoryByteData& data);

public:
	TTFFont(const FontId& fontId);
	TTFFont(const FontId& fontId,const MemoryByteData& data);

	virtual ~TTFFont(void);
	virtual bool Initialize();
	virtual uint Preload(const WStringRef& str);
	virtual bool IsFixed()const{ return false; }
protected:
	virtual const FontChar* OnLoadChar(wchar_t c);
	virtual const FontKerning* OnLoadKerning(int prev,int next);
	virtual bool OnUpdateFontId();

private:
	inline intp FontUnitToPixelSize(intp fontUnitSize)const;
	inline intp FixedPointToPixelSize(intp val)const;

	TextureAtlasRegion* AddGlyphImage(wchar_t c,FontImageDepth destDepth, const Size2U& size, int pitch, const MemoryByteData& imageData, FontImageDepth srcDepth);

private:
	static FT_Library mLibrary;
	FT_Face mFace;

	FT_UInt32 mGlyphLoadFlags=0;

	MemoryByteData mFontData;

	Size2U mInitialImageSize;	//default image size
	Size2U mMaxImageSize;
	//3 type images to cache all ttf glyphs,in these case to make more chars into less draw calls
};

MEDUSA_END;