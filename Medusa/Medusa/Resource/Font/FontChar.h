// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"
#include "Core/Geometry/Point2.h"

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
	Point2I HBearing;
	ushort HAdvance=0;	//character width

	Point2I VBearing;
	ushort VAdvance=0;	//character height

	int Channel;	//The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).

	TextureAtlasRegion* Region() const { return mRegion; }
	void SetRegion(TextureAtlasRegion* val) { mRegion = val; }

	bool operator==(const FontChar& val)const
	{
		return Id==val.Id;
	}

private:
	TextureAtlasRegion* mRegion=nullptr;
	
};

MEDUSA_END;