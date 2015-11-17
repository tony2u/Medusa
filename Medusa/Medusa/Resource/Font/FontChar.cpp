// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "FontChar.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;

FontChar::FontChar(void) 
	:TextureRect(Rect2U::Zero), HBearing(Point2I::Zero)
{
	mMaterial=nullptr;
	VBearing=Point2I::Zero;
	VAdvance=0;
	Channel=0;
}

FontChar::FontChar(wchar_t id) 
	:Id(id), TextureRect(Rect2U::Zero), HBearing(Point2I::Zero)
{
	mMaterial=nullptr;
	VBearing=Point2I::Zero;
	VAdvance=0;
	Channel=0;
}

FontChar::FontChar( const FontChar& fontChar )
	:Id(fontChar.Id),TextureRect(fontChar.TextureRect),
	TextureCoords(fontChar.TextureCoords),
	HBearing(fontChar.HBearing),
	HAdvance(fontChar.HAdvance),
	VBearing(fontChar.VBearing),
	VAdvance(fontChar.VAdvance),
	Channel(fontChar.Channel)
{
	SAFE_ASSIGN_REF(mMaterial,fontChar.Material());
}

FontChar& FontChar::operator=( const FontChar& fontChar )
{
	TextureRect=fontChar.TextureRect;
	Id=fontChar.Id;
	HBearing=fontChar.HBearing;
	HAdvance=fontChar.HAdvance;
	TextureCoords=fontChar.TextureCoords;
	VBearing=fontChar.VBearing;
	VAdvance=fontChar.VAdvance;
	Channel=fontChar.Channel;
	SAFE_ASSIGN_REF(mMaterial,fontChar.Material());

	return *this;
}

FontChar::~FontChar(void)
{
	SAFE_RELEASE(mMaterial);
}

void FontChar::SetMaterial( IMaterial* material )
{
	SAFE_ASSIGN_REF(mMaterial,material);
}

void FontChar::UpdateTextureCoords(const Rect2U textureRect,const Size2U& textureSize)
{
	TextureRect=textureRect;
	UpdateTextureCoords(textureSize);
}

void FontChar::UpdateTextureCoords(const Size2U& textureSize)
{
	Point2F textureCoord;

	textureCoord.X=(float)TextureRect.Origin.X/textureSize.Width;
	textureCoord.Y=(float)TextureRect.Origin.Y/textureSize.Height;
	TextureCoords[0]=textureCoord;

	textureCoord.X+=(float)TextureRect.Size.Width/textureSize.Width;
	TextureCoords[1]=textureCoord;

	textureCoord.Y+=(float)TextureRect.Size.Height/textureSize.Height;
	TextureCoords[2]=textureCoord;

	TextureCoords[3].X=TextureCoords[0].X;
	TextureCoords[3].Y=textureCoord.Y;
}

void FontChar::UpdateTextureCoordsReverse(const Size2U& textureSize)
{
	Point2F textureCoord;

	textureCoord.X=(float)TextureRect.Origin.X/textureSize.Width;
	textureCoord.Y=1.f-((float)TextureRect.Origin.Y+(float)TextureRect.Size.Height)/textureSize.Height;
	TextureCoords[0]=textureCoord;

	textureCoord.X+=(float)TextureRect.Size.Width/textureSize.Width;
	TextureCoords[1]=textureCoord;

	textureCoord.Y+=(float)TextureRect.Size.Height/textureSize.Height;
	TextureCoords[2]=textureCoord;

	TextureCoords[3]=TextureCoords[0];
	TextureCoords[3].Y=textureCoord.Y;
}




MEDUSA_END;