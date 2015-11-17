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
	static TTFFont* CreateFromFile(const FontId& fontId);
	static TTFFont* CreateFromData(const FontId& fontId,const MemoryByteData& data);

public:
	TTFFont(const FontId& fontId);
	TTFFont(const FontId& fontId,const MemoryByteData& data);

	virtual ~TTFFont(void);
	virtual bool Initialize();
	virtual uint Preload(const WStringRef& str);
	virtual bool IsFixedMaterial()const{ return false; }
protected:
	virtual const FontChar* OnLoadChar(wchar_t c);
	virtual const FontKerning* OnLoadKerning(int prev,int next);
	virtual bool OnUpdateFontId();

private:
	inline intp FontUnitToPixelSize(intp fontUnitSize)const;
	inline intp FixedPointToPixelSize(intp val)const;
private:
	FT_Library mLibrary;
	FT_Face mFace;

	FT_UInt32 mGlyphLoadFlags=0;

	MemoryByteData mFontData;

};

MEDUSA_END;