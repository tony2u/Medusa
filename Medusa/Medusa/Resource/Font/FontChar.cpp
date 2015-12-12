// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FontChar.h"

MEDUSA_BEGIN;

FontChar::FontChar(void) 
	:HBearing(Point2I::Zero)
{
	VBearing=Point2I::Zero;
	VAdvance=0;
	Channel=0;
}

FontChar::FontChar(wchar_t id) 
	:Id(id), HBearing(Point2I::Zero)
{
	VBearing=Point2I::Zero;
	VAdvance=0;
	Channel=0;
}

FontChar::FontChar( const FontChar& fontChar )
	:Id(fontChar.Id),
	HBearing(fontChar.HBearing),
	HAdvance(fontChar.HAdvance),
	VBearing(fontChar.VBearing),
	VAdvance(fontChar.VAdvance),
	Channel(fontChar.Channel)
{
	mRegion = fontChar.mRegion;
}

FontChar& FontChar::operator=( const FontChar& fontChar )
{
	Id=fontChar.Id;
	HBearing=fontChar.HBearing;
	HAdvance=fontChar.HAdvance;
	VBearing=fontChar.VBearing;
	VAdvance=fontChar.VAdvance;
	Channel=fontChar.Channel;
	mRegion = fontChar.mRegion;


	return *this;
}

FontChar::~FontChar(void)
{
}




MEDUSA_END;