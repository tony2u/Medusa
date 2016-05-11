#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_18(SirenTypeId, Null,Bool, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String,Blob, Enum,List, Dictionary, Struct));
class SirenTypeId	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class SirenTypeIdField	//[IGNORE_PRE_DECLARE]
{
friend class SirenTypeId;
public:
SirenTypeIdField()
{
}
 bool operator==( SirenTypeId rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( SirenTypeId rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( SirenTypeId rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( SirenTypeId rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( SirenTypeId rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( SirenTypeId rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( SirenTypeIdField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( SirenTypeIdField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( SirenTypeIdField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( SirenTypeIdField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( SirenTypeIdField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( SirenTypeIdField<TValue2,TIndex2,TName2> rhs ) const
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
 SirenTypeId( const SirenTypeId& rhs ) : mState( rhs.mState ) 
{
}
 SirenTypeId operator=( SirenTypeId rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 SirenTypeId(const SirenTypeIdField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 SirenTypeId operator=(const SirenTypeIdField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( SirenTypeId rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( SirenTypeId rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( SirenTypeId rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( SirenTypeId rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( SirenTypeId rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( SirenTypeId rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( SirenTypeIdField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( SirenTypeIdField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( SirenTypeIdField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( SirenTypeIdField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( SirenTypeIdField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( SirenTypeIdField<TValue,TIndex,TName> rhs ) const
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
return "Null";
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
return "Enum";
}
static StringRef OnName16()
{
return "List";
}
static StringRef OnName17()
{
return "Dictionary";
}
static StringRef OnName18()
{
return "Struct";
}
public:
explicit SirenTypeId(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case 0:return "Null";
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
case 14:return "Enum";
case 15:return "List";
case 16:return "Dictionary";
case 17:return "Struct";
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
static SirenTypeId Parse(int val)
{
if(IsDefined(val))
{
return SirenTypeId(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return SirenTypeId::Null;
}
static bool TryParse(int val,SirenTypeId& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static SirenTypeId Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return SirenTypeId(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return SirenTypeId::Null;
}
static bool TryParse(SirenTypeId& outEnum,StringRef name,bool ignoreCase=false)
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
static constexpr unsigned int Size=18;
static const StringRef Names[Size];
static const int Values[Size];
static const SirenTypeIdField<0,0,SirenTypeId::OnName1> Null;
static const SirenTypeIdField<1,1,SirenTypeId::OnName2> Bool;
static const SirenTypeIdField<2,2,SirenTypeId::OnName3> Int8;
static const SirenTypeIdField<3,3,SirenTypeId::OnName4> UInt8;
static const SirenTypeIdField<4,4,SirenTypeId::OnName5> Int16;
static const SirenTypeIdField<5,5,SirenTypeId::OnName6> UInt16;
static const SirenTypeIdField<6,6,SirenTypeId::OnName7> Int32;
static const SirenTypeIdField<7,7,SirenTypeId::OnName8> UInt32;
static const SirenTypeIdField<8,8,SirenTypeId::OnName9> Int64;
static const SirenTypeIdField<9,9,SirenTypeId::OnName10> UInt64;
static const SirenTypeIdField<10,10,SirenTypeId::OnName11> Float;
static const SirenTypeIdField<11,11,SirenTypeId::OnName12> Double;
static const SirenTypeIdField<12,12,SirenTypeId::OnName13> String;
static const SirenTypeIdField<13,13,SirenTypeId::OnName14> Blob;
static const SirenTypeIdField<14,14,SirenTypeId::OnName15> Enum;
static const SirenTypeIdField<15,15,SirenTypeId::OnName16> List;
static const SirenTypeIdField<16,16,SirenTypeId::OnName17> Dictionary;
static const SirenTypeIdField<17,17,SirenTypeId::OnName18> Struct;
SirenTypeId():mState(0)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef SirenTypeId::Names[Size]=
{
"Null","Bool","Int8","UInt8","Int16","UInt16","Int32","UInt32","Int64","UInt64","Float","Double","String","Blob","Enum","List","Dictionary","Struct"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int SirenTypeId::Values[Size]=
{
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<0,0,SirenTypeId::OnName1> SirenTypeId::Null;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<1,1,SirenTypeId::OnName2> SirenTypeId::Bool;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<2,2,SirenTypeId::OnName3> SirenTypeId::Int8;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<3,3,SirenTypeId::OnName4> SirenTypeId::UInt8;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<4,4,SirenTypeId::OnName5> SirenTypeId::Int16;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<5,5,SirenTypeId::OnName6> SirenTypeId::UInt16;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<6,6,SirenTypeId::OnName7> SirenTypeId::Int32;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<7,7,SirenTypeId::OnName8> SirenTypeId::UInt32;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<8,8,SirenTypeId::OnName9> SirenTypeId::Int64;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<9,9,SirenTypeId::OnName10> SirenTypeId::UInt64;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<10,10,SirenTypeId::OnName11> SirenTypeId::Float;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<11,11,SirenTypeId::OnName12> SirenTypeId::Double;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<12,12,SirenTypeId::OnName13> SirenTypeId::String;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<13,13,SirenTypeId::OnName14> SirenTypeId::Blob;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<14,14,SirenTypeId::OnName15> SirenTypeId::Enum;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<15,15,SirenTypeId::OnName16> SirenTypeId::List;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<16,16,SirenTypeId::OnName17> SirenTypeId::Dictionary;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SirenTypeId::SirenTypeIdField<17,17,SirenTypeId::OnName18> SirenTypeId::Struct;
MEDUSA_END;
