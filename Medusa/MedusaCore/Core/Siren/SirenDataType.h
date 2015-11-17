// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_17(SirenDataType, StructEnd,Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String, List,Blob, Dictionary, Struct));
class SirenDataType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class SirenDataTypeField	//[IGNORE_PRE_DECLARE]
{
friend class SirenDataType;
public:
SirenDataTypeField()
{
}
 bool operator==( SirenDataType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( SirenDataType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( SirenDataType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( SirenDataType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( SirenDataType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( SirenDataType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( SirenDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( SirenDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( SirenDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( SirenDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( SirenDataTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( SirenDataTypeField<TValue2,TIndex2,TName2> rhs ) const
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
 SirenDataType( const SirenDataType& rhs ) : mState( rhs.mState ) 
{
}
 SirenDataType operator=( SirenDataType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 SirenDataType(const SirenDataTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 SirenDataType operator=(const SirenDataTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( SirenDataType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( SirenDataType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( SirenDataType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( SirenDataType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( SirenDataType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( SirenDataType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( SirenDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( SirenDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( SirenDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( SirenDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( SirenDataTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( SirenDataTypeField<TValue,TIndex,TName> rhs ) const
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
return "StructEnd";
}
static StringRef OnName2()
{
return "Bool";
}
static StringRef OnName3()
{
return "Int8";
}
static StringRef OnName4()
{
return "UInt8";
}
static StringRef OnName5()
{
return "Int16";
}
static StringRef OnName6()
{
return "UInt16";
}
static StringRef OnName7()
{
return "Int32";
}
static StringRef OnName8()
{
return "UInt32";
}
static StringRef OnName9()
{
return "Int64";
}
static StringRef OnName10()
{
return "UInt64";
}
static StringRef OnName11()
{
return "Float";
}
static StringRef OnName12()
{
return "Double";
}
static StringRef OnName13()
{
return "String";
}
static StringRef OnName14()
{
return "Blob";
}
static StringRef OnName15()
{
return "List";
}
static StringRef OnName16()
{
return "Dictionary";
}
static StringRef OnName17()
{
return "Struct";
}
public:
explicit SirenDataType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case 0:return "StructEnd";
case 1:return "Bool";
case 2:return "Int8";
case 3:return "UInt8";
case 4:return "Int16";
case 5:return "UInt16";
case 6:return "Int32";
case 7:return "UInt32";
case 8:return "Int64";
case 9:return "UInt64";
case 10:return "Float";
case 11:return "Double";
case 12:return "String";
case 13:return "Blob";
case 14:return "List";
case 15:return "Dictionary";
case 16:return "Struct";
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
static SirenDataType Parse(int val)
{
if(IsDefined(val))
{
return SirenDataType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return SirenDataType::StructEnd;
}
static bool TryParse(int val,SirenDataType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static SirenDataType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return SirenDataType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return SirenDataType::StructEnd;
}
static bool TryParse(SirenDataType& outEnum,StringRef name,bool ignoreCase=false)
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
static constexpr unsigned int Size=17;
static const StringRef Names[Size];
static const int Values[Size];
static const SirenDataTypeField<0,0,SirenDataType::OnName1> StructEnd;
static const SirenDataTypeField<1,1,SirenDataType::OnName2> Bool;
static const SirenDataTypeField<2,2,SirenDataType::OnName3> Int8;
static const SirenDataTypeField<3,3,SirenDataType::OnName4> UInt8;
static const SirenDataTypeField<4,4,SirenDataType::OnName5> Int16;
static const SirenDataTypeField<5,5,SirenDataType::OnName6> UInt16;
static const SirenDataTypeField<6,6,SirenDataType::OnName7> Int32;
static const SirenDataTypeField<7,7,SirenDataType::OnName8> UInt32;
static const SirenDataTypeField<8,8,SirenDataType::OnName9> Int64;
static const SirenDataTypeField<9,9,SirenDataType::OnName10> UInt64;
static const SirenDataTypeField<10,10,SirenDataType::OnName11> Float;
static const SirenDataTypeField<11,11,SirenDataType::OnName12> Double;
static const SirenDataTypeField<12,12,SirenDataType::OnName13> String;
static const SirenDataTypeField<13,13,SirenDataType::OnName14> Blob;
static const SirenDataTypeField<14,14,SirenDataType::OnName15> List;
static const SirenDataTypeField<15,15,SirenDataType::OnName16> Dictionary;
static const SirenDataTypeField<16,16,SirenDataType::OnName17> Struct;
SirenDataType():mState(0)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef SirenDataType::Names[Size]=
{
"StructEnd","Bool","Int8","UInt8","Int16","UInt16","Int32","UInt32","Int64","UInt64","Float","Double","String","Blob","List","Dictionary","Struct"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int SirenDataType::Values[Size]=
{
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<0,0,SirenDataType::OnName1> SirenDataType::StructEnd;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<1,1,SirenDataType::OnName2> SirenDataType::Bool;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<2,2,SirenDataType::OnName3> SirenDataType::Int8;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<3,3,SirenDataType::OnName4> SirenDataType::UInt8;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<4,4,SirenDataType::OnName5> SirenDataType::Int16;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<5,5,SirenDataType::OnName6> SirenDataType::UInt16;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<6,6,SirenDataType::OnName7> SirenDataType::Int32;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<7,7,SirenDataType::OnName8> SirenDataType::UInt32;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<8,8,SirenDataType::OnName9> SirenDataType::Int64;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<9,9,SirenDataType::OnName10> SirenDataType::UInt64;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<10,10,SirenDataType::OnName11> SirenDataType::Float;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<11,11,SirenDataType::OnName12> SirenDataType::Double;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<12,12,SirenDataType::OnName13> SirenDataType::String;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<13,13,SirenDataType::OnName14> SirenDataType::Blob;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<14,14,SirenDataType::OnName15> SirenDataType::List;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<15,15,SirenDataType::OnName16> SirenDataType::Dictionary;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenDataType::SirenDataTypeField<16,16,SirenDataType::OnName17> SirenDataType::Struct;
MEDUSA_END;
