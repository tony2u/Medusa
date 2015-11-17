// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Math/Math.h"
#include "Core/Siren/SirenDefines.h"


MEDUSA_BEGIN;


#define MEDUSA_COLOR_BYTE_MULTIPLE(X,Y) ((byte)((((float)X/255)*((float)Y/255))*255))
#define MEDUSA_COLOR_BYTE_DIVIDE(X,Y) ((byte)((((float)X/255)*((float)Y/255))*255))
#define MEDUSA_COLOR_ARGB_TO_RGBA(x) ((x<<8)|(x>>24))



class Color4F;

class Color4B
{
public:
	const static uint32 Size=4;

	union
	{
		byte Buffer[Size];
		struct
		{
			byte R;	//lowest byte
			byte G;	
			byte B;
			byte A;
		};
		uint32 Data;
	};

	const static Color4B Zero;

	const static Color4B AliceBlue;
	const static Color4B AntiqueWhite;
	const static Color4B Aqua;
	const static Color4B Aquamarine;
	const static Color4B Azure;
	const static Color4B Beige;
	const static Color4B Bisque;
	const static Color4B Black;
	const static Color4B BlanchedAlmond;
	const static Color4B Blue;
	const static Color4B BlueViolet;
	const static Color4B Brown;
	const static Color4B BurlyWood;
	const static Color4B CadetBlue;
	const static Color4B Chartreuse;
	const static Color4B Chocolate;
	const static Color4B Coral;
	const static Color4B CornflowerBlue;
	const static Color4B Cornsilk;
	const static Color4B Crimson;
	const static Color4B Cyan;
	const static Color4B DarkBlue;
	const static Color4B DarkCyan;
	const static Color4B DarkGoldenrod;
	const static Color4B DarkGray;
	const static Color4B DarkGreen;
	const static Color4B DarkKhaki;
	const static Color4B DarkMagenta;
	const static Color4B DarkOliveGreen;
	const static Color4B DarkOrange;
	const static Color4B DarkOrchid;
	const static Color4B DarkRed;
	const static Color4B DarkSalmon;
	const static Color4B DarkSeaGreen;
	const static Color4B DarkSlateBlue;
	const static Color4B DarkSlateGray;
	const static Color4B DarkTurquoise;
	const static Color4B DarkViolet;
	const static Color4B DeepPink;
	const static Color4B DeepSkyBlue;
	const static Color4B DimGray;
	const static Color4B DodgerBlue;
	const static Color4B Firebrick;
	const static Color4B FloralWhite;
	const static Color4B ForestGreen;
	const static Color4B Fuchsia;
	const static Color4B Gainsboro;
	const static Color4B GhostWhite;
	const static Color4B Gold;
	const static Color4B Goldenrod;
	const static Color4B Gray;
	const static Color4B Green;
	const static Color4B GreenYellow;
	const static Color4B Honeydew;
	const static Color4B HotPink;
	const static Color4B IndianRed;
	const static Color4B Indigo;
	const static Color4B Ivory;
	const static Color4B Khaki;
	const static Color4B Lavender;
	const static Color4B LavenderBlush;
	const static Color4B LawnGreen;
	const static Color4B LemonChiffon;
	const static Color4B LightBlue;
	const static Color4B LightCoral;
	const static Color4B LightCyan;
	const static Color4B LightGoldenrodYellow;
	const static Color4B LightGray;
	const static Color4B LightGreen;
	const static Color4B LightPink;
	const static Color4B LightSalmon;
	const static Color4B LightSeaGreen;
	const static Color4B LightSkyBlue;
	const static Color4B LightSlateGray;
	const static Color4B LightSteelBlue;
	const static Color4B LightYellow;
	const static Color4B Lime;
	const static Color4B LimeGreen;
	const static Color4B Linen;
	const static Color4B Magenta;
	const static Color4B Maroon;
	const static Color4B MediumAquamarine;
	const static Color4B MediumBlue;
	const static Color4B MediumOrchid;
	const static Color4B MediumPurple;
	const static Color4B MediumSeaGreen;
	const static Color4B MediumSlateBlue;
	const static Color4B MediumSpringGreen;
	const static Color4B MediumTurquoise;
	const static Color4B MediumVioletRed;
	const static Color4B MidnightBlue;
	const static Color4B MintCream;
	const static Color4B MistyRose;
	const static Color4B Moccasin;
	const static Color4B NavajoWhite;
	const static Color4B Navy;
	const static Color4B OldLace;
	const static Color4B Olive;
	const static Color4B OliveDrab;
	const static Color4B Orange;
	const static Color4B OrangeRed;
	const static Color4B Orchid;
	const static Color4B PaleGoldenrod;
	const static Color4B PaleGreen;
	const static Color4B PaleTurquoise;
	const static Color4B PaleVioletRed;
	const static Color4B PapayaWhip;
	const static Color4B PeachPuff;
	const static Color4B Peru;
	const static Color4B Pink;
	const static Color4B Plum;
	const static Color4B PowderBlue;
	const static Color4B Purple;
	const static Color4B Red;
	const static Color4B RosyBrown;
	const static Color4B RoyalBlue;
	const static Color4B SaddleBrown;
	const static Color4B Salmon;
	const static Color4B SandyBrown;
	const static Color4B SeaGreen;
	const static Color4B SeaShell;
	const static Color4B Sienna;
	const static Color4B Silver;
	const static Color4B SkyBlue;
	const static Color4B SlateBlue;
	const static Color4B SlateGray;
	const static Color4B Snow;
	const static Color4B SpringGreen;
	const static Color4B SteelBlue;
	const static Color4B Tan;
	const static Color4B Teal;
	const static Color4B Thistle;
	const static Color4B Tomato;
	const static Color4B Transparent;
	const static Color4B Turquoise;
	const static Color4B Violet;
	const static Color4B Wheat;
	const static Color4B White;
	const static Color4B WhiteSmoke;
	const static Color4B Yellow;
	const static Color4B YellowGreen;
public:
	Color4B(const Color3B& color);
	Color4B& operator=(const Color3B& color);

	Color4B(void){}
	Color4B(byte r,byte g,byte b,byte a=255):R(r),G(g),B(b),A(a){}
	Color4B(const byte* rgba) :R(rgba[0]), G(rgba[1]), B(rgba[2]), A(rgba[3]){}

	Color4B(uint32 data):Data(data){}


	Color4B(const Color4B& color):Data(color.Data){}

	Color4B& operator=(const Color4B& color){Data=color.Data;return *this;}
	Color4B& operator=(uint32 val){Data=val;return *this;}

	
	bool operator==(const Color4B& color)const{return Math::IsEqual(Data,color.Data);}
	bool operator!=(const Color4B& color)const{return !operator==(color);}
	bool operator>(const Color4B& color)const{return Data>color.Data;}
	bool operator<(const Color4B& color)const{return Data<color.Data;}
	bool operator>=(const Color4B& color)const{return Data>=color.Data;}
	bool operator<=(const Color4B& color)const{return Data<=color.Data;}

	
	Color4B operator+(const Color4B& color)const{return Color4B(R+color.R,G+color.G,B+color.B,A+color.A);}
	Color4B operator-(const Color4B& color)const{return Color4B(R-color.R,G-color.G,B-color.B,A-color.A);}
	Color4B& operator+=(const Color4B& color){R+=color.R;G+=color.G;B+=color.B;A+=color.A;return *this;}
	Color4B& operator-=(const Color4B& color){R-=color.R;G-=color.G;B-=color.B;A-=color.A;return *this;}

	Color4B operator*(const Color4B& color)const{return Color4B(MEDUSA_COLOR_BYTE_MULTIPLE(R,color.R),MEDUSA_COLOR_BYTE_MULTIPLE(G,color.G),MEDUSA_COLOR_BYTE_MULTIPLE(B,color.B),MEDUSA_COLOR_BYTE_MULTIPLE(A,color.A));}
	Color4B operator/(const Color4B& color)const{return Color4B(MEDUSA_COLOR_BYTE_DIVIDE(R,color.R),MEDUSA_COLOR_BYTE_DIVIDE(G,color.G),MEDUSA_COLOR_BYTE_DIVIDE(B,color.B),MEDUSA_COLOR_BYTE_DIVIDE(A,color.A));}
	Color4B& operator*=(const Color4B& color){R=MEDUSA_COLOR_BYTE_MULTIPLE(R,color.R);G=MEDUSA_COLOR_BYTE_MULTIPLE(G,color.G);B=MEDUSA_COLOR_BYTE_MULTIPLE(B,color.B);A=MEDUSA_COLOR_BYTE_MULTIPLE(A,color.A);return *this;}
	Color4B& operator/=(const Color4B& color){R=MEDUSA_COLOR_BYTE_DIVIDE(R,color.R);G=MEDUSA_COLOR_BYTE_DIVIDE(G,color.G);B=MEDUSA_COLOR_BYTE_DIVIDE(B,color.B);A=MEDUSA_COLOR_BYTE_DIVIDE(A,color.A);return *this;}

	Color4B operator*(byte delta)const{return Color4B(MEDUSA_COLOR_BYTE_MULTIPLE(R,delta),MEDUSA_COLOR_BYTE_MULTIPLE(G,delta),MEDUSA_COLOR_BYTE_MULTIPLE(B,delta),MEDUSA_COLOR_BYTE_MULTIPLE(A,delta));}
	Color4B operator/(byte delta)const{return Color4B(MEDUSA_COLOR_BYTE_DIVIDE(R,delta),MEDUSA_COLOR_BYTE_DIVIDE(G,delta),MEDUSA_COLOR_BYTE_DIVIDE(B,delta),MEDUSA_COLOR_BYTE_DIVIDE(A,delta));}
	Color4B& operator*=(byte delta){R=MEDUSA_COLOR_BYTE_MULTIPLE(R,delta);G=MEDUSA_COLOR_BYTE_MULTIPLE(G,delta);B=MEDUSA_COLOR_BYTE_MULTIPLE(B,delta);A=MEDUSA_COLOR_BYTE_MULTIPLE(A,delta);return *this;}
	Color4B& operator/=(byte delta){R=MEDUSA_COLOR_BYTE_DIVIDE(R,delta);G=MEDUSA_COLOR_BYTE_DIVIDE(G,delta);B=MEDUSA_COLOR_BYTE_DIVIDE(B,delta);A=MEDUSA_COLOR_BYTE_DIVIDE(A,delta);return *this;}


	Color4B operator<<(uint32 delta)const{return Color4B(R<<delta,G<<delta,B<<delta,A<<delta);}
	Color4B operator>>(uint32 delta)const{return Color4B(R>>delta,G>>delta,B>>delta,A>>delta);}

	Color4B& operator<<=(uint32 delta){R<<=delta;G<<=delta;B<<=delta;A<<=delta;return *this;}
	Color4B& operator>>=(uint32 delta){R>>=delta;G>>=delta;B>>=delta;A>>=delta;return *this;}

	Color4B& operator++(){++R;++G;++B;++A;return *this;}
	Color4B& operator--(){--R;--G;--B;++A;return *this;}

	Color4B operator++(int){Color4B orign=*this;++R;++G;++B;++A;return orign;}
	Color4B operator--(int){Color4B orign=*this;--R;--G;--B;++A;return orign;}

    friend Color4B operator*(byte delta,const Color4B& color){return Color4B(delta*color.R,delta*color.G,delta*color.B,delta*color.A);}

	
	bool operator==(uint32 val)const{return Math::IsEqual(Data,val);}
	bool operator!=(uint32 val)const{return !operator==(val);}
	bool operator>(uint32 val)const{return Data>val;}
	bool operator<(uint32 val)const{return Data<val;}
	bool operator>=(uint32 val)const{return Data>=val;}
	bool operator<=(uint32 val)const{return Data<=val;}

	
	Color4F To4F()const;
	intp HashCode()const{return R^G^B^A;}

	static Color4B LinearInterpolate(const Color4B& begin,const Color4B& end,float blend)
	{
		return Color4B(Math::LinearInterpolate(begin.R,end.R,blend),Math::LinearInterpolate(begin.G,end.G,blend),Math::LinearInterpolate(begin.B,end.B,blend),Math::LinearInterpolate(begin.A,end.A,blend));
	}
};


class Color4F
{
public:
	const static uint32 Size=4;

	union
	{
		float Buffer[Size];
		struct
		{
			float R;
			float G;
			float B;
			float A;
		};
	};

	const static Color4F Zero;

	const static Color4F AliceBlue;
	const static Color4F AntiqueWhite;
	const static Color4F Aqua;
	const static Color4F Aquamarine;
	const static Color4F Azure;
	const static Color4F Beige;
	const static Color4F Bisque;
	const static Color4F Black;
	const static Color4F BlanchedAlmond;
	const static Color4F Blue;
	const static Color4F BlueViolet;
	const static Color4F Brown;
	const static Color4F BurlyWood;
	const static Color4F CadetBlue;
	const static Color4F Chartreuse;
	const static Color4F Chocolate;
	const static Color4F Coral;
	const static Color4F CornflowerBlue;
	const static Color4F Cornsilk;
	const static Color4F Crimson;
	const static Color4F Cyan;
	const static Color4F DarkBlue;
	const static Color4F DarkCyan;
	const static Color4F DarkGoldenrod;
	const static Color4F DarkGray;
	const static Color4F DarkGreen;
	const static Color4F DarkKhaki;
	const static Color4F DarkMagenta;
	const static Color4F DarkOliveGreen;
	const static Color4F DarkOrange;
	const static Color4F DarkOrchid;
	const static Color4F DarkRed;
	const static Color4F DarkSalmon;
	const static Color4F DarkSeaGreen;
	const static Color4F DarkSlateBlue;
	const static Color4F DarkSlateGray;
	const static Color4F DarkTurquoise;
	const static Color4F DarkViolet;
	const static Color4F DeepPink;
	const static Color4F DeepSkyBlue;
	const static Color4F DimGray;
	const static Color4F DodgerBlue;
	const static Color4F Firebrick;
	const static Color4F FloralWhite;
	const static Color4F ForestGreen;
	const static Color4F Fuchsia;
	const static Color4F Gainsboro;
	const static Color4F GhostWhite;
	const static Color4F Gold;
	const static Color4F Goldenrod;
	const static Color4F Gray;
	const static Color4F Green;
	const static Color4F GreenYellow;
	const static Color4F Honeydew;
	const static Color4F HotPink;
	const static Color4F IndianRed;
	const static Color4F Indigo;
	const static Color4F Ivory;
	const static Color4F Khaki;
	const static Color4F Lavender;
	const static Color4F LavenderBlush;
	const static Color4F LawnGreen;
	const static Color4F LemonChiffon;
	const static Color4F LightBlue;
	const static Color4F LightCoral;
	const static Color4F LightCyan;
	const static Color4F LightGoldenrodYellow;
	const static Color4F LightGray;
	const static Color4F LightGreen;
	const static Color4F LightPink;
	const static Color4F LightSalmon;
	const static Color4F LightSeaGreen;
	const static Color4F LightSkyBlue;
	const static Color4F LightSlateGray;
	const static Color4F LightSteelBlue;
	const static Color4F LightYellow;
	const static Color4F Lime;
	const static Color4F LimeGreen;
	const static Color4F Linen;
	const static Color4F Magenta;
	const static Color4F Maroon;
	const static Color4F MediumAquamarine;
	const static Color4F MediumBlue;
	const static Color4F MediumOrchid;
	const static Color4F MediumPurple;
	const static Color4F MediumSeaGreen;
	const static Color4F MediumSlateBlue;
	const static Color4F MediumSpringGreen;
	const static Color4F MediumTurquoise;
	const static Color4F MediumVioletRed;
	const static Color4F MidnightBlue;
	const static Color4F MintCream;
	const static Color4F MistyRose;
	const static Color4F Moccasin;
	const static Color4F NavajoWhite;
	const static Color4F Navy;
	const static Color4F OldLace;
	const static Color4F Olive;
	const static Color4F OliveDrab;
	const static Color4F Orange;
	const static Color4F OrangeRed;
	const static Color4F Orchid;
	const static Color4F PaleGoldenrod;
	const static Color4F PaleGreen;
	const static Color4F PaleTurquoise;
	const static Color4F PaleVioletRed;
	const static Color4F PapayaWhip;
	const static Color4F PeachPuff;
	const static Color4F Peru;
	const static Color4F Pink;
	const static Color4F Plum;
	const static Color4F PowderBlue;
	const static Color4F Purple;
	const static Color4F Red;
	const static Color4F RosyBrown;
	const static Color4F RoyalBlue;
	const static Color4F SaddleBrown;
	const static Color4F Salmon;
	const static Color4F SandyBrown;
	const static Color4F SeaGreen;
	const static Color4F SeaShell;
	const static Color4F Sienna;
	const static Color4F Silver;
	const static Color4F SkyBlue;
	const static Color4F SlateBlue;
	const static Color4F SlateGray;
	const static Color4F Snow;
	const static Color4F SpringGreen;
	const static Color4F SteelBlue;
	const static Color4F Tan;
	const static Color4F Teal;
	const static Color4F Thistle;
	const static Color4F Tomato;
	const static Color4F Transparent;
	const static Color4F Turquoise;
	const static Color4F Violet;
	const static Color4F Wheat;
	const static Color4F White;
	const static Color4F WhiteSmoke;
	const static Color4F Yellow;
	const static Color4F YellowGreen;
public:
	Color4F(const Color3F& color);
	Color4F& operator=(const Color3F& color);

	Color4F(void){}
	Color4F(float r,float g,float b,float a=1.f):R(r),G(g),B(b),A(a){}
	Color4F(const float* rgba) :R(rgba[0]), G(rgba[1]), B(rgba[2]), A(rgba[3]){}

	Color4F(const Color4F& color):R(color.R),G(color.G),B(color.B),A(color.A){}
	Color4F(uint32 data):R((float)Color4B(data).R/255.f),G((float)Color4B(data).G/255.f),B((float)Color4B(data).B/255.f),A((float)Color4B(data).A/255.f){}
	Color4F(byte r,byte g,byte b,byte a=255):R(r/255.f),G(g/255.f),B(b/255.f),A(a/255.f){}

	Color4F& operator=(const Color4F& color){R=color.R;G=color.G;B=color.B;A=color.A;return *this;}
	Color4F& operator=(float val){R=val;G=val;B=val;A=val;return *this;}


	bool operator==(const Color4F& color)const{return Math::IsEqual(R,color.R)&&Math::IsEqual(G,color.G)&&Math::IsEqual(B,color.B)&&Math::IsEqual(A,color.A);}
	bool operator!=(const Color4F& color)const{return !operator==(color);}
	bool operator>(const Color4F& color)const{return R>color.R&&G>color.G&&B>color.B&&A>color.A;}
	bool operator<(const Color4F& color)const{return R<color.R&&G<color.G&&B<color.B&&A<color.A;}
	bool operator>=(const Color4F& color)const{return R>=color.R&&G>=color.G&&B>=color.B&&A>=color.A;}
	bool operator<=(const Color4F& color)const{return R<=color.R&&G<=color.G&&B<=color.B&&A<=color.A;}


	Color4F operator+(const Color4F& color)const{return Color4F(R+color.R,G+color.G,B+color.B,A+color.A);}
	Color4F operator-(const Color4F& color)const{return Color4F(R-color.R,G-color.G,B-color.B,A-color.A);}
	Color4F& operator+=(const Color4F& color){R+=color.R;G+=color.G;B+=color.B;A+=color.A;return *this;}
	Color4F& operator-=(const Color4F& color){R-=color.R;G-=color.G;B-=color.B;A-=color.A;return *this;}

	Color4F operator*(const Color4F& color)const{return Color4F(R*color.R,G*color.G,B*color.B,A*color.A);}
	Color4F operator/(const Color4F& color)const{return Color4F(R/color.R,G/color.G,B/color.B,A/color.A);}
	Color4F& operator*=(const Color4F& color){R*=color.R;G*=color.G;B*=color.B;A*=color.A;return *this;}
	Color4F& operator/=(const Color4F& color){R/=color.R;G/=color.G;B/=color.B;A/=color.A;return *this;}


	Color4F operator*(float delta)const{return Color4F(R*delta,G*delta,B*delta,A*delta);}
	Color4F operator/(float delta)const{return Color4F(R/delta,G/delta,B/delta,A/delta);}


	Color4F& operator*=(float delta){R*=delta;G*=delta;B*=delta;A*=delta;return *this;}
	Color4F& operator/=(float delta){R/=delta;G/=delta;B/=delta;A/=delta;return *this;}

	Color4F& operator++(){++R;++G;++B;++A;return *this;}
	Color4F& operator--(){--R;--G;--B;++A;return *this;}

	Color4F operator++(int){Color4F orign=*this;++R;++G;++B;++A;return orign;}
	Color4F operator--(int){Color4F orign=*this;--R;--G;--B;++A;return orign;}

	friend Color4F operator*(float delta,const Color4F& color){return Color4F(delta*color.R,delta*color.G,delta*color.B,delta*color.A);}


	bool operator==(float val)const{return Math::IsEqual(R,val)&&Math::IsEqual(G,val)&&Math::IsEqual(B,val)&&Math::IsEqual(A,val);}
	bool operator!=(float val)const{return !operator==(val);}
	bool operator>(float val)const{return R>val&&G>val&&B>val&&A>val;}
	bool operator<(float val)const{return R<val&&G<val&&B<val&&A<val;}
	bool operator>=(float val)const{return R>=val&&G>=val&&B>=val&&A>=val;}
	bool operator<=(float val)const{return R<=val&&G<=val&&B<=val&&A<=val;}


	Color4B To4B()const{return Color4B((byte)R*255,(byte)G*255,(byte)B*255,(byte)A*255);}
	intp HashCode()const{return (uint32)R^(uint32)G^(uint32)B^(uint32)A;}

	static Color4F LinearInterpolate(const Color4F& begin,const Color4F& end,float blend)
	{
		return Color4F(Math::LinearInterpolate(begin.R,end.R,blend),Math::LinearInterpolate(begin.G,end.G,blend),Math::LinearInterpolate(begin.B,end.B,blend),Math::LinearInterpolate(begin.A,end.A,blend));
	}

};


namespace Siren
{
	template <>
	struct HasCustomSerialization<Color4F> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter>
	void Serialize(TWriter& writer, const Color4F& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<float, false>("R", 1, 0, obj.R);
		writer.template OnProperty<float, false>("G", 1, 1, obj.G);
		writer.template OnProperty<float, false>("B", 1, 2, obj.B);
		writer.template OnProperty<float, false>("A", 1, 3, obj.A);

		writer.OnStructEnd();
	}

	template <typename TReader>
	bool DeserializeTo(TReader& reader, Color4F& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<float, false>("R", 1, 0, outObj.R);
		reader.template OnProperty<float, false>("G", 1, 1, outObj.G);
		reader.template OnProperty<float, false>("B", 1, 2, outObj.B);
		reader.template OnProperty<float, false>("A", 1, 3, outObj.A);

		reader.OnStructEnd();

		return true;
	}

	template <>
	struct HasCustomSerialization<Color4B> : std::true_type{};	//[IGNORE_PRE_DECLARE]

	template <typename TWriter>
	void Serialize(TWriter& writer, const Color4B& obj)
	{
		writer.OnStructBegin();
		writer.template OnProperty<byte, false>("R", 1, 0, obj.R);
		writer.template OnProperty<byte, false>("G", 1, 1, obj.G);
		writer.template OnProperty<byte, false>("B", 1, 2, obj.B);
		writer.template OnProperty<byte, false>("A", 1, 3, obj.A);

		writer.OnStructEnd();
	}

	template <typename TReader>
	bool DeserializeTo(TReader& reader, Color4B& outObj)
	{
		reader.OnStructBegin();
		reader.template OnProperty<byte, false>("R", 1, 0, outObj.R);
		reader.template OnProperty<byte, false>("G", 1, 1, outObj.G);
		reader.template OnProperty<byte, false>("B", 1, 2, outObj.B);
		reader.template OnProperty<byte, false>("A", 1, 3, outObj.A);

		reader.OnStructEnd();

		return true;
	}
}


#define mrgba_b(r,g,b,a) Color4B(r,g,b,a)
#define mrgba(r,g,b,a) Color4F(r,g,b,a)

#undef MEDUSA_COLOR_BYTE_MULTIPLE
#undef MEDUSA_COLOR_BYTE_DIVIDE

MEDUSA_END;


#ifdef MEDUSA_SCRIPT
MEDUSA_SCRIPT_BEGIN;
void RegisterColor4F(asIScriptEngine* engine);
MEDUSA_SCRIPT_END;
#endif