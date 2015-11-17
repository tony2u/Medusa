// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_3(GraphicsHintMode, Fastest, GL_FASTEST, Nicest, GL_NICEST, DontCare, GL_DONT_CARE);
class GraphicsHintMode	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsHintModeField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsHintMode;
public:
GraphicsHintModeField()
{
}
 bool operator==( GraphicsHintMode rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsHintMode rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsHintMode rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsHintMode rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsHintMode rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsHintMode rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsHintModeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsHintModeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsHintModeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsHintModeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsHintModeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsHintModeField<TValue2,TIndex2,TName2> rhs ) const
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
 GraphicsHintMode( const GraphicsHintMode& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsHintMode operator=( GraphicsHintMode rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsHintMode(const GraphicsHintModeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsHintMode operator=(const GraphicsHintModeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsHintMode rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsHintMode rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsHintMode rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsHintMode rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsHintMode rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsHintMode rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsHintModeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsHintModeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsHintModeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsHintModeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsHintModeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsHintModeField<TValue,TIndex,TName> rhs ) const
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
return "Fastest";
}
static StringRef OnName2()
{
return "Nicest";
}
static StringRef OnName3()
{
return "DontCare";
}
public:
explicit GraphicsHintMode(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_FASTEST:return "Fastest";
case GL_NICEST:return "Nicest";
case GL_DONT_CARE:return "DontCare";
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
static GraphicsHintMode Parse(int val)
{
if(IsDefined(val))
{
return GraphicsHintMode(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsHintMode::Fastest;
}
static bool TryParse(int val,GraphicsHintMode& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsHintMode Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsHintMode(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsHintMode::Fastest;
}
static bool TryParse(GraphicsHintMode& outEnum,StringRef name,bool ignoreCase=false)
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
static const GraphicsHintModeField<GL_FASTEST,0,GraphicsHintMode::OnName1> Fastest;
static const GraphicsHintModeField<GL_NICEST,1,GraphicsHintMode::OnName2> Nicest;
static const GraphicsHintModeField<GL_DONT_CARE,2,GraphicsHintMode::OnName3> DontCare;
GraphicsHintMode():mState(GL_FASTEST)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsHintMode::Names[Size]=
{
"Fastest","Nicest","DontCare"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsHintMode::Values[Size]=
{
GL_FASTEST,GL_NICEST,GL_DONT_CARE
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsHintMode::GraphicsHintModeField<GL_FASTEST,0,GraphicsHintMode::OnName1> GraphicsHintMode::Fastest;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsHintMode::GraphicsHintModeField<GL_NICEST,1,GraphicsHintMode::OnName2> GraphicsHintMode::Nicest;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsHintMode::GraphicsHintModeField<GL_DONT_CARE,2,GraphicsHintMode::OnName3> GraphicsHintMode::DontCare;
MEDUSA_END;
