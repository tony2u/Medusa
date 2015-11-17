// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_3(GraphicsFace, Front, GL_FRONT, Back, GL_BACK, FrontAndBack, GL_FRONT_AND_BACK);
class GraphicsFace	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsFaceField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsFace;
public:
GraphicsFaceField()
{
}
 bool operator==( GraphicsFace rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsFace rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsFace rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsFace rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsFace rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsFace rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 constexpr static int IntValue=TValue;
 constexpr static unsigned int Index=TIndex;
 constexpr int ToInt()const
{
return TValue;
}
 constexpr unsigned int ToUInt()const
{
return (unsigned int)TValue;
}
 constexpr unsigned int ToIndex()const
{
return TIndex;
}
 StringRef ToString()const
{
return TName();
}
 constexpr intp HashCode()const
{
return TValue;
};
};
 protected:
int mState;
 public:
 const static bool IsEnum = true;
 GraphicsFace( const GraphicsFace& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsFace operator=( GraphicsFace rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsFace(const GraphicsFaceField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsFace operator=(const GraphicsFaceField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsFace rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsFace rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsFace rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsFace rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsFace rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsFace rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsFaceField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsFaceField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsFaceField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsFaceField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsFaceField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsFaceField<TValue,TIndex,TName> rhs ) const
{
return mState >= TValue;
}
 int ToInt()const
{
return mState;
}
 void ForceSet(int state)
{
mState=state;
}
 int* ForceGetPointer()
{
return &mState;
}
 int& ForceGetReference()
{
return mState;
}
 unsigned int ToUInt()const
{
return (unsigned int)mState;
}
 explicit operator unsigned int()const
{
return (unsigned int)mState;
}
 explicit operator int()const
{
return (int)mState;
}
 intp HashCode()const
{
return mState;
};
 public:
 private:
static StringRef OnName1()
{
return "Front";
}
static StringRef OnName2()
{
return "Back";
}
static StringRef OnName3()
{
return "FrontAndBack";
}
public:
explicit GraphicsFace(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_FRONT:return "Front";
case GL_BACK:return "Back";
case GL_FRONT_AND_BACK:return "FrontAndBack";
default:
return nullptr;
}
}
uint ToIndex()const
{
for(uint i=0;i<Size;++i)
{
if(Values[i]==mState) return i;
}
return (uint)0xFFFFFFFF;
}
static bool IsDefined(int val)
{
for(uint i=0;i<Size;++i)
{
if(Values[i]==val) return true;
}
return false;
}
static bool HasField(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0) return true;
}
return false;
}
static GraphicsFace Parse(int val)
{
if(IsDefined(val))
{
return GraphicsFace(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsFace::Front;
}
static bool TryParse(int val,GraphicsFace& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsFace Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsFace(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsFace::Front;
}
static bool TryParse(GraphicsFace& outEnum,StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
outEnum.ForceSet(Values[i]);
 return true;
}
}
return false;
}
public:
static constexpr unsigned int Size=3;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsFaceField<GL_FRONT,0,GraphicsFace::OnName1> Front;
static const GraphicsFaceField<GL_BACK,1,GraphicsFace::OnName2> Back;
static const GraphicsFaceField<GL_FRONT_AND_BACK,2,GraphicsFace::OnName3> FrontAndBack;
GraphicsFace():mState(GL_FRONT)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsFace::Names[Size]=
{
"Front","Back","FrontAndBack"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsFace::Values[Size]=
{
GL_FRONT,GL_BACK,GL_FRONT_AND_BACK
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFace::GraphicsFaceField<GL_FRONT,0,GraphicsFace::OnName1> GraphicsFace::Front;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFace::GraphicsFaceField<GL_BACK,1,GraphicsFace::OnName2> GraphicsFace::Back;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFace::GraphicsFaceField<GL_FRONT_AND_BACK,2,GraphicsFace::OnName3> GraphicsFace::FrontAndBack;
MEDUSA_END;
