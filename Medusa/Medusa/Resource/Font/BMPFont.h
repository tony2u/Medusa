// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Font/IFont.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class BMPFont :public IFont
{
public:
	virtual bool IsBitmap()const override { return true; }

	static Share<BMPFont> CreateFromPVR(const FontId& fontId);
	static Share<BMPFont> CreateFromBMPBinary(const FontId& fontId, const IStream& stream);
	static Share<BMPFont> CreateFromBMPText(const FontId& fontId, const IStream& stream);
	static Share<BMPFont> CreateFromSingleTexture(const FontId& fontId, wchar_t firstChar = L'0');

public:
	BMPFont(const FontId& fontId);
	virtual ~BMPFont(void);
private:
};

MEDUSA_END;