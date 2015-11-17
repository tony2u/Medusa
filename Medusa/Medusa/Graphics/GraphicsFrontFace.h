// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_2(GraphicsFrontFace, ClockWise, GL_CW, CounterClockWise, GL_CCW);
class GraphicsFrontFace	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsFrontFaceField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsFrontFace;
public:
GraphicsFrontFaceField()
{
}
 bool operator==( GraphicsFrontFace rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsFrontFace rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsFrontFace rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsFrontFace rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsFrontFace rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsFrontFace rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsFrontFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsFrontFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsFrontFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsFrontFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsFrontFaceField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsFrontFaceField<TValue2,TIndex2,TName2> rhs ) const
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
 GraphicsFrontFace( const GraphicsFrontFace& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsFrontFace operator=( GraphicsFrontFace rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsFrontFace(const GraphicsFrontFaceField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsFrontFace operator=(const GraphicsFrontFaceField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsFrontFace rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsFrontFace rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsFrontFace rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsFrontFace rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsFrontFace rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsFrontFace rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsFrontFaceField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsFrontFaceField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsFrontFaceField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsFrontFaceField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsFrontFaceField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsFrontFaceField<TValue,TIndex,TName> rhs ) const
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
return "ClockWise";
}
static StringRef OnName2()
{
return "CounterClockWise";
}
public:
explicit GraphicsFrontFace(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_CW:return "ClockWise";
case GL_CCW:return "CounterClockWise";
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
static GraphicsFrontFace Parse(int val)
{
if(IsDefined(val))
{
return GraphicsFrontFace(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsFrontFace::ClockWise;
}
static bool TryParse(int val,GraphicsFrontFace& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsFrontFace Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsFrontFace(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsFrontFace::ClockWise;
}
static bool TryParse(GraphicsFrontFace& outEnum,StringRef name,bool ignoreCase=false)
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
static constexpr unsigned int Size=2;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsFrontFaceField<GL_CW,0,GraphicsFrontFace::OnName1> ClockWise;
static const GraphicsFrontFaceField<GL_CCW,1,GraphicsFrontFace::OnName2> CounterClockWise;
GraphicsFrontFace():mState(GL_CW)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsFrontFace::Names[Size]=
{
"ClockWise","CounterClockWise"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsFrontFace::Values[Size]=
{
GL_CW,GL_CCW
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFrontFace::GraphicsFrontFaceField<GL_CW,0,GraphicsFrontFace::OnName1> GraphicsFrontFace::ClockWise;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFrontFace::GraphicsFrontFaceField<GL_CCW,1,GraphicsFrontFace::OnName2> GraphicsFrontFace::CounterClockWise;
MEDUSA_END;
