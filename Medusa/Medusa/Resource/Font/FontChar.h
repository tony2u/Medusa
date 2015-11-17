// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Geometry/Rect2.h"
#include "Core/Geometry/Point2.h"
#include "Core/Collection/Array.h"

MEDUSA_BEGIN;

#pragma pack(push, 4)		// Force 4byte alignment.
struct FontKerning
{
	union 
	{
		struct 
		{
			int First;
			int	Second;
		};
		uint64	Pair;				// OR'd pair for 32bit characters
	};
	int	Offset;			// Kerning offset (in pixels)

	FontKerning():Pair(0),Offset(0){}
	FontKerning(int first,int second,int offset)
		:First(first),Second(second),Offset(offset){}
	intp HashCode()const
	{
		int* p=(int*)Pair;
		return p[0]^p[1]^Offset;
	}

	bool operator==(const FontKerning& val)const
	{
		return Pair==val.Pair&&Offset==val.Offset;
	}
};
#pragma pack(pop)


class FontChar
{
public:
	FontChar(void);
	~FontChar(void);

	FontChar(const FontChar& fontChar);
	FontChar& operator=(const FontChar& fontChar);

	FontChar(wchar_t id);

	wchar_t Id=0;
	Rect2U TextureRect;
	Array<Point2F,4> TextureCoords;
	Point2I HBearing;
	ushort HAdvance=0;	//character width

	Point2I VBearing;
	ushort VAdvance=0;	//character height

	int Channel;	//The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).
	void SetMaterial(IMaterial* material);
	IMaterial* Material() const { return mMaterial; }

	intp HashCode()const
	{
		return TextureRect.HashCode();
	}

	bool operator==(const FontChar& val)const
	{
		return Id==val.Id;
	}

	void UpdateTextureCoords(const Size2U& textureSize);
	void UpdateTextureCoordsReverse(const Size2U& textureSize);

	void UpdateTextureCoords(const Rect2U textureRect,const Size2U& textureSize);


private:
	IMaterial* mMaterial;
};

MEDUSA_END;