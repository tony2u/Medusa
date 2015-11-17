// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_3(GraphicsBlendEquation,Add, GL_FUNC_ADD,Subtract, GL_FUNC_SUBTRACT,ReverserSubtract, GL_FUNC_REVERSE_SUBTRACT);
class GraphicsBlendEquation	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsBlendEquationField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsBlendEquation;
public:
GraphicsBlendEquationField()
{
}
 bool operator==( GraphicsBlendEquation rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsBlendEquation rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsBlendEquation rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsBlendEquation rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsBlendEquation rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsBlendEquation rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsBlendEquationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsBlendEquationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsBlendEquationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsBlendEquationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsBlendEquationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsBlendEquationField<TValue2,TIndex2,TName2> rhs ) const
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
 GraphicsBlendEquation( const GraphicsBlendEquation& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsBlendEquation operator=( GraphicsBlendEquation rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsBlendEquation(const GraphicsBlendEquationField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsBlendEquation operator=(const GraphicsBlendEquationField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsBlendEquation rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsBlendEquation rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsBlendEquation rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsBlendEquation rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsBlendEquation rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsBlendEquation rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsBlendEquationField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsBlendEquationField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsBlendEquationField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsBlendEquationField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsBlendEquationField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsBlendEquationField<TValue,TIndex,TName> rhs ) const
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
return "Add";
}
static StringRef OnName2()
{
return "Subtract";
}
static StringRef OnName3()
{
return "ReverserSubtract";
}
public:
explicit GraphicsBlendEquation(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_FUNC_ADD:return "Add";
case GL_FUNC_SUBTRACT:return "Subtract";
case GL_FUNC_REVERSE_SUBTRACT:return "ReverserSubtract";
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
static GraphicsBlendEquation Parse(int val)
{
if(IsDefined(val))
{
return GraphicsBlendEquation(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsBlendEquation::Add;
}
static bool TryParse(int val,GraphicsBlendEquation& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsBlendEquation Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsBlendEquation(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsBlendEquation::Add;
}
static bool TryParse(GraphicsBlendEquation& outEnum,StringRef name,bool ignoreCase=false)
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
static const GraphicsBlendEquationField<GL_FUNC_ADD,0,GraphicsBlendEquation::OnName1> Add;
static const GraphicsBlendEquationField<GL_FUNC_SUBTRACT,1,GraphicsBlendEquation::OnName2> Subtract;
static const GraphicsBlendEquationField<GL_FUNC_REVERSE_SUBTRACT,2,GraphicsBlendEquation::OnName3> ReverserSubtract;
GraphicsBlendEquation():mState(GL_FUNC_ADD)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsBlendEquation::Names[Size]=
{
"Add","Subtract","ReverserSubtract"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsBlendEquation::Values[Size]=
{
GL_FUNC_ADD,GL_FUNC_SUBTRACT,GL_FUNC_REVERSE_SUBTRACT
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBlendEquation::GraphicsBlendEquationField<GL_FUNC_ADD,0,GraphicsBlendEquation::OnName1> GraphicsBlendEquation::Add;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBlendEquation::GraphicsBlendEquationField<GL_FUNC_SUBTRACT,1,GraphicsBlendEquation::OnName2> GraphicsBlendEquation::Subtract;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBlendEquation::GraphicsBlendEquationField<GL_FUNC_REVERSE_SUBTRACT,2,GraphicsBlendEquation::OnName3> GraphicsBlendEquation::ReverserSubtract;
MEDUSA_END;
