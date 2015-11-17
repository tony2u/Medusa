// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_8(GraphicsStencilOperation,Keep, GL_KEEP,Zero, GL_ZERO,ReplaceToRef, GL_REPLACE,Increase, GL_INCR,IncreaseWrap, GL_INCR_WRAP,Decrease, GL_DECR,DecreaseWrap, GL_DECR_WRAP,Invert, GL_INVERT);
class GraphicsStencilOperation	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsStencilOperationField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsStencilOperation;
public:
GraphicsStencilOperationField()
{
}
 bool operator==( GraphicsStencilOperation rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsStencilOperation rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsStencilOperation rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsStencilOperation rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsStencilOperation rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsStencilOperation rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsStencilOperationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsStencilOperationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsStencilOperationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsStencilOperationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsStencilOperationField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsStencilOperationField<TValue2,TIndex2,TName2> rhs ) const
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
 GraphicsStencilOperation( const GraphicsStencilOperation& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsStencilOperation operator=( GraphicsStencilOperation rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsStencilOperation(const GraphicsStencilOperationField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsStencilOperation operator=(const GraphicsStencilOperationField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsStencilOperation rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsStencilOperation rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsStencilOperation rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsStencilOperation rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsStencilOperation rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsStencilOperation rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsStencilOperationField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsStencilOperationField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsStencilOperationField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsStencilOperationField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsStencilOperationField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsStencilOperationField<TValue,TIndex,TName> rhs ) const
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
return "Keep";
}
static StringRef OnName2()
{
return "Zero";
}
static StringRef OnName3()
{
return "ReplaceToRef";
}
static StringRef OnName4()
{
return "Increase";
}
static StringRef OnName5()
{
return "IncreaseWrap";
}
static StringRef OnName6()
{
return "Decrease";
}
static StringRef OnName7()
{
return "DecreaseWrap";
}
static StringRef OnName8()
{
return "Invert";
}
public:
explicit GraphicsStencilOperation(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_KEEP:return "Keep";
case GL_ZERO:return "Zero";
case GL_REPLACE:return "ReplaceToRef";
case GL_INCR:return "Increase";
case GL_INCR_WRAP:return "IncreaseWrap";
case GL_DECR:return "Decrease";
case GL_DECR_WRAP:return "DecreaseWrap";
case GL_INVERT:return "Invert";
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
static GraphicsStencilOperation Parse(int val)
{
if(IsDefined(val))
{
return GraphicsStencilOperation(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsStencilOperation::Keep;
}
static bool TryParse(int val,GraphicsStencilOperation& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsStencilOperation Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsStencilOperation(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsStencilOperation::Keep;
}
static bool TryParse(GraphicsStencilOperation& outEnum,StringRef name,bool ignoreCase=false)
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
static const GraphicsStencilOperationField<GL_KEEP,0,GraphicsStencilOperation::OnName1> Keep;
static const GraphicsStencilOperationField<GL_ZERO,1,GraphicsStencilOperation::OnName2> Zero;
static const GraphicsStencilOperationField<GL_REPLACE,2,GraphicsStencilOperation::OnName3> ReplaceToRef;
static const GraphicsStencilOperationField<GL_INCR,3,GraphicsStencilOperation::OnName4> Increase;
static const GraphicsStencilOperationField<GL_INCR_WRAP,4,GraphicsStencilOperation::OnName5> IncreaseWrap;
static const GraphicsStencilOperationField<GL_DECR,5,GraphicsStencilOperation::OnName6> Decrease;
static const GraphicsStencilOperationField<GL_DECR_WRAP,6,GraphicsStencilOperation::OnName7> DecreaseWrap;
static const GraphicsStencilOperationField<GL_INVERT,7,GraphicsStencilOperation::OnName8> Invert;
GraphicsStencilOperation():mState(GL_KEEP)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsStencilOperation::Names[Size]=
{
"Keep","Zero","ReplaceToRef","Increase","IncreaseWrap","Decrease","DecreaseWrap","Invert"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsStencilOperation::Values[Size]=
{
GL_KEEP,GL_ZERO,GL_REPLACE,GL_INCR,GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP,GL_INVERT
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_KEEP,0,GraphicsStencilOperation::OnName1> GraphicsStencilOperation::Keep;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_ZERO,1,GraphicsStencilOperation::OnName2> GraphicsStencilOperation::Zero;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_REPLACE,2,GraphicsStencilOperation::OnName3> GraphicsStencilOperation::ReplaceToRef;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_INCR,3,GraphicsStencilOperation::OnName4> GraphicsStencilOperation::Increase;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_INCR_WRAP,4,GraphicsStencilOperation::OnName5> GraphicsStencilOperation::IncreaseWrap;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_DECR,5,GraphicsStencilOperation::OnName6> GraphicsStencilOperation::Decrease;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_DECR_WRAP,6,GraphicsStencilOperation::OnName7> GraphicsStencilOperation::DecreaseWrap;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsStencilOperation::GraphicsStencilOperationField<GL_INVERT,7,GraphicsStencilOperation::OnName8> GraphicsStencilOperation::Invert;
MEDUSA_END;
