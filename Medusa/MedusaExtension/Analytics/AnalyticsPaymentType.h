// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaExtensionPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_8(AnalyticsPaymentType, AppStore, AliPay, WebBank, QQPay, ChinaMobile, Unicom, Telecom, Paypal);
class AnalyticsPaymentType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class AnalyticsPaymentTypeField	//[IGNORE_PRE_DECLARE]
{
friend class AnalyticsPaymentType;
public:
AnalyticsPaymentTypeField()
{
}
 bool operator==( AnalyticsPaymentType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( AnalyticsPaymentType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( AnalyticsPaymentType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( AnalyticsPaymentType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( AnalyticsPaymentType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( AnalyticsPaymentType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( AnalyticsPaymentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( AnalyticsPaymentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( AnalyticsPaymentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( AnalyticsPaymentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( AnalyticsPaymentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( AnalyticsPaymentTypeField<TValue2,TIndex2,TName2> rhs ) const
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
 AnalyticsPaymentType( const AnalyticsPaymentType& rhs ) : mState( rhs.mState ) 
{
}
 AnalyticsPaymentType operator=( AnalyticsPaymentType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 AnalyticsPaymentType(const AnalyticsPaymentTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 AnalyticsPaymentType operator=(const AnalyticsPaymentTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( AnalyticsPaymentType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( AnalyticsPaymentType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( AnalyticsPaymentType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( AnalyticsPaymentType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( AnalyticsPaymentType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( AnalyticsPaymentType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( AnalyticsPaymentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( AnalyticsPaymentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( AnalyticsPaymentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( AnalyticsPaymentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( AnalyticsPaymentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( AnalyticsPaymentTypeField<TValue,TIndex,TName> rhs ) const
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
return "AppStore";
}
static StringRef OnName2()
{
return "AliPay";
}
static StringRef OnName3()
{
return "WebBank";
}
static StringRef OnName4()
{
return "QQPay";
}
static StringRef OnName5()
{
return "ChinaMobile";
}
static StringRef OnName6()
{
return "Unicom";
}
static StringRef OnName7()
{
return "Telecom";
}
static StringRef OnName8()
{
return "Paypal";
}
public:
explicit AnalyticsPaymentType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case 0:return "AppStore";
case 1:return "AliPay";
case 2:return "WebBank";
case 3:return "QQPay";
case 4:return "ChinaMobile";
case 5:return "Unicom";
case 6:return "Telecom";
case 7:return "Paypal";
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
static AnalyticsPaymentType Parse(int val)
{
if(IsDefined(val))
{
return AnalyticsPaymentType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return AnalyticsPaymentType::AppStore;
}
static bool TryParse(int val,AnalyticsPaymentType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static AnalyticsPaymentType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return AnalyticsPaymentType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return AnalyticsPaymentType::AppStore;
}
static bool TryParse(AnalyticsPaymentType& outEnum,StringRef name,bool ignoreCase=false)
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
static const AnalyticsPaymentTypeField<0,0,AnalyticsPaymentType::OnName1> AppStore;
static const AnalyticsPaymentTypeField<1,1,AnalyticsPaymentType::OnName2> AliPay;
static const AnalyticsPaymentTypeField<2,2,AnalyticsPaymentType::OnName3> WebBank;
static const AnalyticsPaymentTypeField<3,3,AnalyticsPaymentType::OnName4> QQPay;
static const AnalyticsPaymentTypeField<4,4,AnalyticsPaymentType::OnName5> ChinaMobile;
static const AnalyticsPaymentTypeField<5,5,AnalyticsPaymentType::OnName6> Unicom;
static const AnalyticsPaymentTypeField<6,6,AnalyticsPaymentType::OnName7> Telecom;
static const AnalyticsPaymentTypeField<7,7,AnalyticsPaymentType::OnName8> Paypal;
AnalyticsPaymentType():mState(0)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef AnalyticsPaymentType::Names[Size]=
{
"AppStore","AliPay","WebBank","QQPay","ChinaMobile","Unicom","Telecom","Paypal"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int AnalyticsPaymentType::Values[Size]=
{
0,1,2,3,4,5,6,7
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<0,0,AnalyticsPaymentType::OnName1> AnalyticsPaymentType::AppStore;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<1,1,AnalyticsPaymentType::OnName2> AnalyticsPaymentType::AliPay;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<2,2,AnalyticsPaymentType::OnName3> AnalyticsPaymentType::WebBank;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<3,3,AnalyticsPaymentType::OnName4> AnalyticsPaymentType::QQPay;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<4,4,AnalyticsPaymentType::OnName5> AnalyticsPaymentType::ChinaMobile;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<5,5,AnalyticsPaymentType::OnName6> AnalyticsPaymentType::Unicom;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<6,6,AnalyticsPaymentType::OnName7> AnalyticsPaymentType::Telecom;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsPaymentType::AnalyticsPaymentTypeField<7,7,AnalyticsPaymentType::OnName8> AnalyticsPaymentType::Paypal;
MEDUSA_END;
