// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaExtensionPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_3(AnalyticsRewardType, FromPlayer, FromCompany, FromGame);
class AnalyticsRewardType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class AnalyticsRewardTypeField	//[IGNORE_PRE_DECLARE]
{
friend class AnalyticsRewardType;
public:
AnalyticsRewardTypeField()
{
}
 bool operator==( AnalyticsRewardType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( AnalyticsRewardType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( AnalyticsRewardType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( AnalyticsRewardType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( AnalyticsRewardType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( AnalyticsRewardType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( AnalyticsRewardTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( AnalyticsRewardTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( AnalyticsRewardTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( AnalyticsRewardTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( AnalyticsRewardTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( AnalyticsRewardTypeField<TValue2,TIndex2,TName2> rhs ) const
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
 AnalyticsRewardType( const AnalyticsRewardType& rhs ) : mState( rhs.mState ) 
{
}
 AnalyticsRewardType operator=( AnalyticsRewardType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 AnalyticsRewardType(const AnalyticsRewardTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 AnalyticsRewardType operator=(const AnalyticsRewardTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( AnalyticsRewardType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( AnalyticsRewardType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( AnalyticsRewardType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( AnalyticsRewardType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( AnalyticsRewardType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( AnalyticsRewardType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( AnalyticsRewardTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( AnalyticsRewardTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( AnalyticsRewardTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( AnalyticsRewardTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( AnalyticsRewardTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( AnalyticsRewardTypeField<TValue,TIndex,TName> rhs ) const
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
return "FromPlayer";
}
static StringRef OnName2()
{
return "FromCompany";
}
static StringRef OnName3()
{
return "FromGame";
}
public:
explicit AnalyticsRewardType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case 0:return "FromPlayer";
case 1:return "FromCompany";
case 2:return "FromGame";
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
static AnalyticsRewardType Parse(int val)
{
if(IsDefined(val))
{
return AnalyticsRewardType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return AnalyticsRewardType::FromPlayer;
}
static bool TryParse(int val,AnalyticsRewardType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static AnalyticsRewardType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return AnalyticsRewardType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return AnalyticsRewardType::FromPlayer;
}
static bool TryParse(AnalyticsRewardType& outEnum,StringRef name,bool ignoreCase=false)
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
static const AnalyticsRewardTypeField<0,0,AnalyticsRewardType::OnName1> FromPlayer;
static const AnalyticsRewardTypeField<1,1,AnalyticsRewardType::OnName2> FromCompany;
static const AnalyticsRewardTypeField<2,2,AnalyticsRewardType::OnName3> FromGame;
AnalyticsRewardType():mState(0)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef AnalyticsRewardType::Names[Size]=
{
"FromPlayer","FromCompany","FromGame"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int AnalyticsRewardType::Values[Size]=
{
0,1,2
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsRewardType::AnalyticsRewardTypeField<0,0,AnalyticsRewardType::OnName1> AnalyticsRewardType::FromPlayer;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsRewardType::AnalyticsRewardTypeField<1,1,AnalyticsRewardType::OnName2> AnalyticsRewardType::FromCompany;
 MEDUSA_WEAK_MULTIPLE_DEFINE const AnalyticsRewardType::AnalyticsRewardTypeField<2,2,AnalyticsRewardType::OnName3> AnalyticsRewardType::FromGame;
MEDUSA_END;
