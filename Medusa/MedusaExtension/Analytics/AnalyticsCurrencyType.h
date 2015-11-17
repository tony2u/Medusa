// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaExtensionPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_3(AnalyticsCurrencyType, CNY, USD, EUR);
class AnalyticsCurrencyType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class AnalyticsCurrencyTypeField	//[IGNORE_PRE_DECLARE]
{
friend class AnalyticsCurrencyType;
public:
AnalyticsCurrencyTypeField()
{
}
 bool operator==( AnalyticsCurrencyType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( AnalyticsCurrencyType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( AnalyticsCurrencyType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( AnalyticsCurrencyType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( AnalyticsCurrencyType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( AnalyticsCurrencyType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( AnalyticsCurrencyTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( AnalyticsCurrencyTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( AnalyticsCurrencyTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( AnalyticsCurrencyTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( AnalyticsCurrencyTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( AnalyticsCurrencyTypeField<TValue2,TIndex2,TName2> rhs ) const
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
 AnalyticsCurrencyType( const AnalyticsCurrencyType& rhs ) : mState( rhs.mState ) 
{
}
 AnalyticsCurrencyType operator=( AnalyticsCurrencyType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 AnalyticsCurrencyType(const AnalyticsCurrencyTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 AnalyticsCurrencyType operator=(const AnalyticsCurrencyTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( AnalyticsCurrencyType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( AnalyticsCurrencyType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( AnalyticsCurrencyType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( AnalyticsCurrencyType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( AnalyticsCurrencyType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( AnalyticsCurrencyType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( AnalyticsCurrencyTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( AnalyticsCurrencyTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( AnalyticsCurrencyTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( AnalyticsCurrencyTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( AnalyticsCurrencyTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( AnalyticsCurrencyTypeField<TValue,TIndex,TName> rhs ) const
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
return "CNY";
}
static StringRef OnName2()
{
return "USD";
}
static StringRef OnName3()
{
return "EUR";
}
public:
explicit AnalyticsCurrencyType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case 0:return "CNY";
case 1:return "USD";
case 2:return "EUR";
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
static AnalyticsCurrencyType Parse(int val)
{
if(IsDefined(val))
{
return AnalyticsCurrencyType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return AnalyticsCurrencyType::CNY;
}
static bool TryParse(int val,AnalyticsCurrencyType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static AnalyticsCurrencyType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return AnalyticsCurrencyType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return AnalyticsCurrencyType::CNY;
}
static bool TryParse(AnalyticsCurrencyType& outEnum,StringRef name,bool ignoreCase=false)
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
static const AnalyticsCurrencyTypeField<0,0,AnalyticsCurrencyType::OnName1> CNY;
static const AnalyticsCurrencyTypeField<1,1,AnalyticsCurrencyType::OnName2> USD;
static const AnalyticsCurrencyTypeField<2,2,AnalyticsCurrencyType::OnName3> EUR;
AnalyticsCurrencyType():mState(0)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef AnalyticsCurrencyType::Names[Size]=
{
"CNY","USD","EUR"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int AnalyticsCurrencyType::Values[Size]=
{
0,1,2
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsCurrencyType::AnalyticsCurrencyTypeField<0,0,AnalyticsCurrencyType::OnName1> AnalyticsCurrencyType::CNY;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsCurrencyType::AnalyticsCurrencyTypeField<1,1,AnalyticsCurrencyType::OnName2> AnalyticsCurrencyType::USD;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsCurrencyType::AnalyticsCurrencyTypeField<2,2,AnalyticsCurrencyType::OnName3> AnalyticsCurrencyType::EUR;
MEDUSA_END;
