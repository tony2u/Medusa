// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaPreDeclares.h"
#include "Core/Math/Math.h"


MEDUSA_BEGIN;

#define MEDUSA_COLOR_BYTE_MULTIPLE(X,Y) ((byte)((((float)X/255)*((float)Y/255))*255))
#define MEDUSA_COLOR_BYTE_DIVIDE(X,Y) ((byte)((((float)X/255)*((float)Y/255))*255))

class Color3F;

class Color3B
{
public:
	union
	{
		byte Buffer[3];
		struct
		{
			byte R;
			byte G;
			byte B;
		};
		uint Data;
	};

	

	const static Color3B Black;
	const static Color3B White;
	const static Color3B Red;
	const static Color3B Green;
	const static Color3B Blue;
public:
	Color3B(const Color4B& color);
	Color3B& operator=(const Color4B& color);


	Color3B(void){}
	Color3B(byte r,byte g,byte b,byte a=255):R(r),G(g),B(b){}
	Color3B(uint data):Data(data){}

	Color3B(const Color3B& color):Data(color.Data){}

	Color3B& operator=(const Color3B& color){Data=color.Data;return *this;}
	Color3B& operator=(uint val){Data=val;return *this;}

	
	bool operator==(const Color3B& color)const{return Math::IsEqual(Data,color.Data);}
	bool operator!=(const Color3B& color)const{return !operator==(color);}
	bool operator>(const Color3B& color)const{return Data>color.Data;}
	bool operator<(const Color3B& color)const{return Data<color.Data;}
	bool operator>=(const Color3B& color)const{return Data>=color.Data;}
	bool operator<=(const Color3B& color)const{return Data<=color.Data;}

	
	Color3B operator+(const Color3B& color)const{return Color3B(R+color.R,G+color.G,B+color.B);}
	Color3B operator-(const Color3B& color)const{return Color3B(R-color.R,G-color.G,B-color.B);}
	Color3B& operator+=(const Color3B& color){R+=color.R;G+=color.G;B+=color.B;return *this;}
	Color3B& operator-=(const Color3B& color){R-=color.R;G-=color.G;B-=color.B;return *this;}

	Color3B operator*(const Color3B& color)const{return Color3B(MEDUSA_COLOR_BYTE_MULTIPLE(R,color.R),MEDUSA_COLOR_BYTE_MULTIPLE(G,color.G),MEDUSA_COLOR_BYTE_MULTIPLE(B,color.B));}
	Color3B operator/(const Color3B& color)const{return Color3B(MEDUSA_COLOR_BYTE_DIVIDE(R,color.R),MEDUSA_COLOR_BYTE_DIVIDE(G,color.G),MEDUSA_COLOR_BYTE_DIVIDE(B,color.B));}
	Color3B& operator*=(const Color3B& color){R=MEDUSA_COLOR_BYTE_MULTIPLE(R,color.R);G=MEDUSA_COLOR_BYTE_MULTIPLE(G,color.G);B=MEDUSA_COLOR_BYTE_MULTIPLE(B,color.B);return *this;}
	Color3B& operator/=(const Color3B& color){R=MEDUSA_COLOR_BYTE_DIVIDE(R,color.R);G=MEDUSA_COLOR_BYTE_DIVIDE(G,color.G);B=MEDUSA_COLOR_BYTE_DIVIDE(B,color.B);return *this;}

	Color3B operator*(byte delta)const{return Color3B(MEDUSA_COLOR_BYTE_MULTIPLE(R,delta),MEDUSA_COLOR_BYTE_MULTIPLE(G,delta),MEDUSA_COLOR_BYTE_MULTIPLE(B,delta));}
	Color3B operator/(byte delta)const{return Color3B(MEDUSA_COLOR_BYTE_DIVIDE(R,delta),MEDUSA_COLOR_BYTE_DIVIDE(G,delta),MEDUSA_COLOR_BYTE_DIVIDE(B,delta));}
	Color3B& operator*=(byte delta){R=MEDUSA_COLOR_BYTE_MULTIPLE(R,delta);G=MEDUSA_COLOR_BYTE_MULTIPLE(G,delta);B=MEDUSA_COLOR_BYTE_MULTIPLE(B,delta);return *this;}
	Color3B& operator/=(byte delta){R=MEDUSA_COLOR_BYTE_DIVIDE(R,delta);G=MEDUSA_COLOR_BYTE_DIVIDE(G,delta);B=MEDUSA_COLOR_BYTE_DIVIDE(B,delta);return *this;}


	Color3B operator<<(uint delta)const{return Color3B(R<<delta,G<<delta,B<<delta);}
	Color3B operator>>(uint delta)const{return Color3B(R>>delta,G>>delta,B>>delta);}
	Color3B& operator<<=(uint delta){R<<=delta;G<<=delta;B<<=delta;return *this;}
	Color3B& operator>>=(uint delta){R>>=delta;G>>=delta;B>>=delta;return *this;}

	Color3B& operator++(){++R;++G;++B;return *this;}
	Color3B& operator--(){--R;--G;--B;return *this;}

	Color3B operator++(int){Color3B orign=*this;++R;++G;++B;return orign;}
	Color3B operator--(int){Color3B orign=*this;--R;--G;--B;return orign;}

    friend Color3B operator*(byte delta,const Color3B& color){return Color3B(delta*color.R,delta*color.G,delta*color.B);}

	
	bool operator==(uint val)const{return Math::IsEqual(Data,val);}
	bool operator!=(uint val)const{return !operator==(val);}
	bool operator>(uint val)const{return Data>val;}
	bool operator<(uint val)const{return Data<val;}
	bool operator>=(uint val)const{return Data>=val;}
	bool operator<=(uint val)const{return Data<=val;}

	
	Color3F To3F()const;
	intp HashCode()const{return R^G^B;}

	static Color3B LinearInterpolate(const Color3B& begin,const Color3B& end,float blend)
	{
		return Color3B(Math::LinearInterpolate(begin.R,end.R,blend),Math::LinearInterpolate(begin.G,end.G,blend),Math::LinearInterpolate(begin.B,end.B,blend));
	}
};


class Color3F
{
public:
	union
	{
		float Buffer[3];
		struct
		{
			float R;
			float G;
			float B;
		};
	};

	const static Color3F Black;
	const static Color3F White;
	const static Color3F Red;
	const static Color3F Green;
	const static Color3F Blue;
public:
	Color3F(const Color4F& color);
	Color3F& operator=(const Color4F& color);

	Color3F(void){}
	Color3F(float r,float g,float b,float a=1.f):R(r),G(g),B(b){}
	Color3F(const Color3F& color):R(color.R),G(color.G),B(color.B){}

	Color3F& operator=(const Color3F& color){R=color.R;G=color.G;B=color.B;return *this;}
	Color3F& operator=(float val){R=val;G=val;B=val;return *this;}


	bool operator==(const Color3F& color)const{return Math::IsEqual(R,color.R)&&Math::IsEqual(G,color.G)&&Math::IsEqual(B,color.B);}
	bool operator!=(const Color3F& color)const{return !operator==(color);}
	bool operator>(const Color3F& color)const{return R>color.R&&G>color.G&&B>color.B;}
	bool operator<(const Color3F& color)const{return R<color.R&&G<color.G&&B<color.B;}
	bool operator>=(const Color3F& color)const{return R>=color.R&&G>=color.G&&B>=color.B;}
	bool operator<=(const Color3F& color)const{return R<=color.R&&G<=color.G&&B<=color.B;}


	Color3F operator+(const Color3F& color)const{return Color3F(R+color.R,G+color.G,B+color.B);}
	Color3F operator-(const Color3F& color)const{return Color3F(R-color.R,G-color.G,B-color.B);}
	Color3F& operator+=(const Color3F& color){R+=color.R;G+=color.G;B+=color.B;return *this;}
	Color3F& operator-=(const Color3F& color){R-=color.R;G-=color.G;B-=color.B;return *this;}

	Color3F operator*(const Color3F& color)const{return Color3F(R*color.R,G*color.G,B*color.B);}
	Color3F operator/(const Color3F& color)const{return Color3F(R/color.R,G/color.G,B/color.B);}
	Color3F& operator*=(const Color3F& color){R*=color.R;G*=color.G;B*=color.B;return *this;}
	Color3F& operator/=(const Color3F& color){R/=color.R;G/=color.G;B/=color.B;return *this;}

	Color3F operator*(float delta)const{return Color3F(R*delta,G*delta,B*delta);}
	Color3F operator/(float delta)const{return Color3F(R/delta,G/delta,B/delta);}


	Color3F& operator*=(float delta){R*=delta;G*=delta;B*=delta;return *this;}
	Color3F& operator/=(float delta){R/=delta;G/=delta;B/=delta;return *this;}

	Color3F& operator++(){++R;++G;++B;return *this;}
	Color3F& operator--(){--R;--G;--B;return *this;}

	Color3F operator++(int){Color3F orign=*this;++R;++G;++B;return orign;}
	Color3F operator--(int){Color3F orign=*this;--R;--G;--B;return orign;}

	friend Color3F operator*(float delta,const Color3F& color){return Color3F(delta*color.R,delta*color.G,delta*color.B);}


	bool operator==(float val)const{return Math::IsEqual(R,val)&&Math::IsEqual(G,val)&&Math::IsEqual(B,val);}
	bool operator!=(float val)const{return !operator==(val);}
	bool operator>(float val)const{return R>val&&G>val&&B>val;}
	bool operator<(float val)const{return R<val&&G<val&&B<val;}
	bool operator>=(float val)const{return R>=val&&G>=val&&B>=val;}
	bool operator<=(float val)const{return R<=val&&G<=val&&B<=val;}

	Color3B To3B()const{return Color3B((byte)R*255,(byte)G*255,(byte)B*255);}
	intp HashCode()const{return (uint)R^(uint)G^(uint)B;}

	static Color3F LinearInterpolate(const Color3F& begin,const Color3F& end,float blend)
	{
		return Color3F(Math::LinearInterpolate(begin.R,end.R,blend),Math::LinearInterpolate(begin.G,end.G,blend),Math::LinearInterpolate(begin.B,end.B,blend));
	}
};

#define mrgb_b(r,g,b) Color3B(r,g,b)
#define mrgb(r,g,b) Color3F(r,g,b)

#undef MEDUSA_COLOR_BYTE_MULTIPLE
#undef MEDUSA_COLOR_BYTE_DIVIDE
MEDUSA_END;


#ifdef MEDUSA_LUA
#include "Core/Lua/LuaState.h"
MEDUSA_BEGIN;

template <>
struct LuaTypeMapping <Color3B>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const Color3B& val)
	{
		LuaStack s(L);
		s.NewTable(0, 3);
		s.Rawset("R", val.R);
		s.Rawset("G", val.G);
		s.Rawset("B", val.B);
	}

	static Color3B Get(lua_State* L, int index)
	{
		Color3B result;
		LuaStack s(L);
		result.R = s.Get<byte>("R", index);
		result.G = s.Get<byte>("G", index);
		result.B = s.Get<byte>("B", index);
		return result;
	}

	static Color3B Optional(lua_State* L, int index, const Color3B& def)
	{
		return lua_isnoneornil(L, index) ? Color3B::Black : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, Color3B& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};


template <>
struct LuaTypeMapping <Color3F>//[IGNORE_PRE_DECLARE]
{
	static void Push(lua_State* L, const Color3F& val)
	{
		LuaStack s(L);
		s.NewTable(0, 3);
		s.Rawset("R", val.R);
		s.Rawset("G", val.G);
		s.Rawset("B", val.B);
	}

	static Color3F Get(lua_State* L, int index)
	{
		Color3F result;
		LuaStack s(L);
		result.R = s.Get<float>("R", index);
		result.G = s.Get<float>("G", index);
		result.B = s.Get<float>("B", index);
		return result;
	}

	static Color3F Optional(lua_State* L, int index, const Color3F& def)
	{
		return lua_isnoneornil(L, index) ? Color3F::Black : Get(L, index);
	}

	static bool TryGet(lua_State* L, int index, Color3F& outValue)
	{
		RETURN_FALSE_IF(lua_isnoneornil(L, index));
		outValue = Get(L, index);
		return true;
	}
};

MEDUSA_END;
#endif
