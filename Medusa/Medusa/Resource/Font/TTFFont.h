// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Font/IFont.h"
#include "Core/Memory/MemoryData.h"
#include "Graphics/GraphicsTypes.h"
#include "Graphics/PixelType.h"

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
	static TTFFont* CreateFromData(const FontId& fontId,const MemoryData& data);

public:
	TTFFont(const FontId& fontId);

	virtual ~TTFFont(void);
	virtual bool IsBitmap()const override { return false; }

	bool Initialize(const MemoryData& data);

	virtual uint Preload(const WStringRef& str);
	virtual bool IsFixed()const{ return false; }
protected:
	virtual const FontChar* OnLoadChar(wchar_t c);
	virtual const FontKerning* OnLoadKerning(int prev,int next);
	virtual bool OnUpdateFontId();

private:
	inline intp FontUnitToPixelSize(intp fontUnitSize)const;
	static intp FixedPointToPixelSize(intp val) { return val / 64; }
	static Rect2I BBoxToRect(const FT_BBox& val);

	TextureAtlasRegion* AddGlyphImage(wchar_t c, PixelType destPixelType, const Size2U& size, int pitch, const MemoryData& imageData, PixelType srcPixelType);
	FT_UInt32 GetGlyphLoadFlags(bool outline = false, bool hinting = false, bool lcdFiltering = false)const;
private:
	static FT_Library mLibrary;
	FT_Face mFace=nullptr;
	FT_Stroker mStroker=nullptr;
	FT_Encoding mEncoding=FT_ENCODING_UNICODE;

	bool mDistanceFieldEnabled = false;	//Not implemented

	MemoryData mFontData;	//should keep this as mFace ref to memory data

	Size2U mInitialImageSize;	//default image size
	Size2U mMaxImageSize;
	//3 type images to cache all ttf glyphs,in these case to make more chars into less draw calls
};

MEDUSA_END;