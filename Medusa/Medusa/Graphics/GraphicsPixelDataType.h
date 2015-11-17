// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_CUSTOM_7(GraphicsPixelDataType,Byte, GL_UNSIGNED_BYTE,UnsignedShort565, GL_UNSIGNED_SHORT_5_6_5,UnsignedShort4444, GL_UNSIGNED_SHORT_4_4_4_4,UnsignedShort5551, GL_UNSIGNED_SHORT_5_5_5_1,HalfFloatOES, GL_HALF_FLOAT_OES,FloatOES, GL_FLOAT,UInt, GL_UNSIGNED_INT);
class GraphicsPixelDataType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class GraphicsPixelDataTypeField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsPixelDataType;
public:
GraphicsPixelDataTypeField()
{
}
 bool operator==( GraphicsPixelDataType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsPixelDataType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsPixelDataType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsPixelDataType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsPixelDataType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsPixelDataType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( GraphicsPixelDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( GraphicsPixelDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( GraphicsPixelDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( GraphicsPixelDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( GraphicsPixelDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( GraphicsPixelDataTypeField<TValue2,TIndex2,TName2> rhs ) const
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
 GraphicsPixelDataType( const GraphicsPixelDataType& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsPixelDataType operator=( GraphicsPixelDataType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsPixelDataType(const GraphicsPixelDataTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 GraphicsPixelDataType operator=(const GraphicsPixelDataTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( GraphicsPixelDataType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsPixelDataType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsPixelDataType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsPixelDataType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsPixelDataType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsPixelDataType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( GraphicsPixelDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( GraphicsPixelDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( GraphicsPixelDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( GraphicsPixelDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( GraphicsPixelDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( GraphicsPixelDataTypeField<TValue,TIndex,TName> rhs ) const
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
return "Byte";
}
static StringRef OnName2()
{
return "UnsignedShort565";
}
static StringRef OnName3()
{
return "UnsignedShort4444";
}
static StringRef OnName4()
{
return "UnsignedShort5551";
}
static StringRef OnName5()
{
return "HalfFloatOES";
}
static StringRef OnName6()
{
return "FloatOES";
}
static StringRef OnName7()
{
return "UInt";
}
public:
explicit GraphicsPixelDataType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case GL_UNSIGNED_BYTE:return "Byte";
case GL_UNSIGNED_SHORT_5_6_5:return "UnsignedShort565";
case GL_UNSIGNED_SHORT_4_4_4_4:return "UnsignedShort4444";
case GL_UNSIGNED_SHORT_5_5_5_1:return "UnsignedShort5551";
case GL_HALF_FLOAT_OES:return "HalfFloatOES";
case GL_FLOAT:return "FloatOES";
case GL_UNSIGNED_INT:return "UInt";
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
static GraphicsPixelDataType Parse(int val)
{
if(IsDefined(val))
{
return GraphicsPixelDataType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return GraphicsPixelDataType::Byte;
}
static bool TryParse(int val,GraphicsPixelDataType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static GraphicsPixelDataType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return GraphicsPixelDataType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return GraphicsPixelDataType::Byte;
}
static bool TryParse(GraphicsPixelDataType& outEnum,StringRef name,bool ignoreCase=false)
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
static constexpr unsigned int Size=7;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsPixelDataTypeField<GL_UNSIGNED_BYTE,0,GraphicsPixelDataType::OnName1> Byte;
static const GraphicsPixelDataTypeField<GL_UNSIGNED_SHORT_5_6_5,1,GraphicsPixelDataType::OnName2> UnsignedShort565;
static const GraphicsPixelDataTypeField<GL_UNSIGNED_SHORT_4_4_4_4,2,GraphicsPixelDataType::OnName3> UnsignedShort4444;
static const GraphicsPixelDataTypeField<GL_UNSIGNED_SHORT_5_5_5_1,3,GraphicsPixelDataType::OnName4> UnsignedShort5551;
static const GraphicsPixelDataTypeField<GL_HALF_FLOAT_OES,4,GraphicsPixelDataType::OnName5> HalfFloatOES;
static const GraphicsPixelDataTypeField<GL_FLOAT,5,GraphicsPixelDataType::OnName6> FloatOES;
static const GraphicsPixelDataTypeField<GL_UNSIGNED_INT,6,GraphicsPixelDataType::OnName7> UInt;
GraphicsPixelDataType():mState(GL_UNSIGNED_BYTE)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsPixelDataType::Names[Size]=
{
"Byte","UnsignedShort565","UnsignedShort4444","UnsignedShort5551","HalfFloatOES","FloatOES","UInt"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsPixelDataType::Values[Size]=
{
GL_UNSIGNED_BYTE,GL_UNSIGNED_SHORT_5_6_5,GL_UNSIGNED_SHORT_4_4_4_4,GL_UNSIGNED_SHORT_5_5_5_1,GL_HALF_FLOAT_OES,GL_FLOAT,GL_UNSIGNED_INT
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_UNSIGNED_BYTE,0,GraphicsPixelDataType::OnName1> GraphicsPixelDataType::Byte;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_UNSIGNED_SHORT_5_6_5,1,GraphicsPixelDataType::OnName2> GraphicsPixelDataType::UnsignedShort565;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_UNSIGNED_SHORT_4_4_4_4,2,GraphicsPixelDataType::OnName3> GraphicsPixelDataType::UnsignedShort4444;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_UNSIGNED_SHORT_5_5_5_1,3,GraphicsPixelDataType::OnName4> GraphicsPixelDataType::UnsignedShort5551;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_HALF_FLOAT_OES,4,GraphicsPixelDataType::OnName5> GraphicsPixelDataType::HalfFloatOES;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_FLOAT,5,GraphicsPixelDataType::OnName6> GraphicsPixelDataType::FloatOES;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsPixelDataType::GraphicsPixelDataTypeField<GL_UNSIGNED_INT,6,GraphicsPixelDataType::OnName7> GraphicsPixelDataType::UInt;
MEDUSA_END;
