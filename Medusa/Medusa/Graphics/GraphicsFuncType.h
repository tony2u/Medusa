// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_8(GraphicsFuncType,Never, GL_NEVER,Less, GL_LESS,Equal, GL_EQUAL,LessOrEqual, GL_LEQUAL,Greater, GL_GREATER,NotEqual, GL_NOTEQUAL,GreaterOrEqual, GL_GEQUAL,Always, GL_ALWAYS);
class GraphicsFuncType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsFuncTypeField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsFuncType;
public:
GraphicsFuncTypeField()
{
}
 bool operator==( GraphicsFuncType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsFuncType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsFuncType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsFuncType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsFuncType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsFuncType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsFuncTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsFuncTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsFuncTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsFuncTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsFuncTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsFuncTypeField<TValue2,TIndex2,TName2> rhs ) const
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
 GraphicsFuncType( const GraphicsFuncType& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsFuncType operator=( GraphicsFuncType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsFuncType(const GraphicsFuncTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsFuncType operator=(const GraphicsFuncTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsFuncType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsFuncType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsFuncType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsFuncType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsFuncType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsFuncType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsFuncTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsFuncTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsFuncTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsFuncTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsFuncTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsFuncTypeField<TValue,TIndex,TName> rhs ) const
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
return "Never";
}
static StringRef OnName2()
{
return "Less";
}
static StringRef OnName3()
{
return "Equal";
}
static StringRef OnName4()
{
return "LessOrEqual";
}
static StringRef OnName5()
{
return "Greater";
}
static StringRef OnName6()
{
return "NotEqual";
}
static StringRef OnName7()
{
return "GreaterOrEqual";
}
static StringRef OnName8()
{
return "Always";
}
public:
explicit GraphicsFuncType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_NEVER:return "Never";
case GL_LESS:return "Less";
case GL_EQUAL:return "Equal";
case GL_LEQUAL:return "LessOrEqual";
case GL_GREATER:return "Greater";
case GL_NOTEQUAL:return "NotEqual";
case GL_GEQUAL:return "GreaterOrEqual";
case GL_ALWAYS:return "Always";
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
static GraphicsFuncType Parse(int val)
{
if(IsDefined(val))
{
return GraphicsFuncType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsFuncType::Never;
}
static bool TryParse(int val,GraphicsFuncType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsFuncType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsFuncType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsFuncType::Never;
}
static bool TryParse(GraphicsFuncType& outEnum,StringRef name,bool ignoreCase=false)
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
static constexpr unsigned int Size=8;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsFuncTypeField<GL_NEVER,0,GraphicsFuncType::OnName1> Never;
static const GraphicsFuncTypeField<GL_LESS,1,GraphicsFuncType::OnName2> Less;
static const GraphicsFuncTypeField<GL_EQUAL,2,GraphicsFuncType::OnName3> Equal;
static const GraphicsFuncTypeField<GL_LEQUAL,3,GraphicsFuncType::OnName4> LessOrEqual;
static const GraphicsFuncTypeField<GL_GREATER,4,GraphicsFuncType::OnName5> Greater;
static const GraphicsFuncTypeField<GL_NOTEQUAL,5,GraphicsFuncType::OnName6> NotEqual;
static const GraphicsFuncTypeField<GL_GEQUAL,6,GraphicsFuncType::OnName7> GreaterOrEqual;
static const GraphicsFuncTypeField<GL_ALWAYS,7,GraphicsFuncType::OnName8> Always;
GraphicsFuncType():mState(GL_NEVER)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsFuncType::Names[Size]=
{
"Never","Less","Equal","LessOrEqual","Greater","NotEqual","GreaterOrEqual","Always"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsFuncType::Values[Size]=
{
GL_NEVER,GL_LESS,GL_EQUAL,GL_LEQUAL,GL_GREATER,GL_NOTEQUAL,GL_GEQUAL,GL_ALWAYS
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_NEVER,0,GraphicsFuncType::OnName1> GraphicsFuncType::Never;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_LESS,1,GraphicsFuncType::OnName2> GraphicsFuncType::Less;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_EQUAL,2,GraphicsFuncType::OnName3> GraphicsFuncType::Equal;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_LEQUAL,3,GraphicsFuncType::OnName4> GraphicsFuncType::LessOrEqual;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_GREATER,4,GraphicsFuncType::OnName5> GraphicsFuncType::Greater;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_NOTEQUAL,5,GraphicsFuncType::OnName6> GraphicsFuncType::NotEqual;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_GEQUAL,6,GraphicsFuncType::OnName7> GraphicsFuncType::GreaterOrEqual;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsFuncType::GraphicsFuncTypeField<GL_ALWAYS,7,GraphicsFuncType::OnName8> GraphicsFuncType::Always;
MEDUSA_END;
