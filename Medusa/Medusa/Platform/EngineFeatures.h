// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;
//EngineFeatures, MultipleThreadUpdating,MultipleThreadRendering);
class EngineFeatures	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class EngineFeaturesField	//[IGNORE_PRE_DECLARE]
{
friend class EngineFeatures;
public:
 EngineFeaturesField()
{
}
 bool operator==( EngineFeatures rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( EngineFeatures rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( EngineFeatures rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( EngineFeatures rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( EngineFeatures rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( EngineFeatures rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 EngineFeatures operator|( EngineFeatures rhs ) const
{
return EngineFeatures( TValue | rhs.mState );
}
 EngineFeatures operator&( EngineFeatures rhs ) const
{
return EngineFeatures( TValue & rhs.mState );
}
 EngineFeatures operator^( EngineFeatures rhs ) const
{
return EngineFeatures( TValue ^ rhs.mState );
}
 EngineFeatures operator~() const
{
return EngineFeatures(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 EngineFeatures operator|( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return EngineFeatures(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 EngineFeatures operator&( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return EngineFeatures(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 EngineFeatures operator^( EngineFeaturesField<TValue2,TName2> rhs ) const
{
return EngineFeatures(TValue ^ TValue2);
}
 static constexpr int IntValue=TValue;
 constexpr int ToInt()const
{
return TValue;
}
 StringRef ToString()const
{
return TName();
};
};
 protected:
int mState;
 public:
 const static bool IsEnum = true;
 EngineFeatures( const EngineFeatures& rhs ) : mState( rhs.mState ) 
{
}
 EngineFeatures operator=( EngineFeatures rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures(EngineFeaturesField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator=( EngineFeaturesField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( EngineFeatures rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( EngineFeatures rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( EngineFeatures rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( EngineFeatures rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( EngineFeatures rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( EngineFeatures rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( EngineFeaturesField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( EngineFeaturesField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( EngineFeaturesField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( EngineFeaturesField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( EngineFeaturesField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( EngineFeaturesField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 EngineFeatures operator|( EngineFeatures rhs ) const
{
return EngineFeatures( mState | rhs.mState );
}
 EngineFeatures operator&( EngineFeatures rhs ) const
{
return EngineFeatures( mState & rhs.mState );
}
 EngineFeatures operator^( EngineFeatures rhs ) const
{
return EngineFeatures( mState ^ rhs.mState );
}
 EngineFeatures operator~() const
{
return EngineFeatures( ~mState );
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator|( EngineFeaturesField<TValue,TName> rhs ) const
{
return EngineFeatures( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator&( EngineFeaturesField<TValue,TName> rhs ) const
{
return EngineFeatures( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator^( EngineFeaturesField<TValue,TName> rhs ) const
{
return EngineFeatures( mState ^ TValue );
}
 EngineFeatures& operator|=( EngineFeatures rhs )
{
mState |= rhs.mState;
return *this;
}
 EngineFeatures& operator&=( EngineFeatures rhs )
{
mState &= rhs.mState;
return *this;
}
 EngineFeatures& operator^=( EngineFeatures rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator|=( EngineFeaturesField<TValue,TName> rhs )
{
mState |= TValue;
return EngineFeatures( *this );
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator&=( EngineFeaturesField<TValue,TName> rhs )
{
mState &= TValue;
return EngineFeatures( *this );
}
 template<int TValue,const StringRef& TName()>
 EngineFeatures operator^=( EngineFeaturesField<TValue,TName> rhs )
{
mState ^= TValue;
return EngineFeatures( *this );
}
 EngineFeatures operator<<( unsigned int s )
{
return EngineFeatures( mState << s );
}
 EngineFeatures operator>>( unsigned int s )
{
return EngineFeatures( mState >> s );
}
 EngineFeatures& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 EngineFeatures& operator>>=( unsigned int s )
{
mState >>= s;
return *this;
}
 int ToInt()const
{
return mState;
}
 bool IsZero()const
{
return mState==0;
}
 bool HasValue()const
{
return mState!=0;
}
 bool Has(EngineFeatures rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(EngineFeatures rhs)
{
mState|=rhs.ToInt();
}
 void Remove(EngineFeatures rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(EngineFeatures rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(EngineFeatures rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(EngineFeatures rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
else
{
mState&=~rhs.ToInt();
}
}
 template<int TValue,const StringRef& TName()>
 bool Has(EngineFeaturesField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(EngineFeaturesField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(EngineFeaturesField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(EngineFeaturesField<TValue,TName> field,bool isSet)
{
if(isSet)
{
mState|=TValue;
}
else
{
mState&=~TValue;
}
}
 bool ForceHasFlag(int flag)const
{
return (mState&flag)==flag;
}
 void ForceSetOrRemoveFlagIf(int flag,bool isSet)
{
if(isSet)
{
mState|=flag;
}
else
{
mState&=~flag;
}
}
 void ForceSetFlag(int flag)
{
mState|=flag;
}
 void ForceRemoveFlag(int flag)
{
mState&=~flag;
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
explicit EngineFeatures(int state=0):mState(state)
{
}
 private:
static const StringRef& OnNameNone()
{
return NoneName;
}
static const StringRef& OnNameAll()
{
return AllName;
}
static const StringRef& OnName0()
{
return Names[0];
}
static const StringRef& OnName1()
{
return Names[1];
}
public:
HeapString ToString()const
{
if (mState == None.IntValue) 
{
 return NoneName;
 
}
if (mState == All.IntValue) 
{
 return AllName;
 
}
HeapString result;
for(uint i=0;i<Size;++i)
{
if ((mState & Values[i]) == Values[i]) 
{
 if (!result.IsEmpty()) 
{
 result += '|';
 
}
result += Names[i];
 
}
}
return result;
}
static bool IsDefined(int val)
{
for(uint i=0;i<Size;++i)
{
if(Values[i]==val) return true;
}
return false;
}
static bool HasField(const StringRef& name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0) return true;
}
return false;
}
static EngineFeatures Parse(int val)
{
if(IsDefined(val))
{
return EngineFeatures(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return EngineFeatures(val);
}
static bool TryParse(int val,EngineFeatures& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static EngineFeatures Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
EngineFeatures result;
bool isSucceed=true;
uint j=0;
List<HeapString> names;
bool splitResult=StringParser::Split<char>(name,"|",names);
if(!splitResult)
{
MEDUSA_ASSERT_FAILED("Invalid flags names");
}
for(auto i = (names).GetEnumerator();i.MoveNext();)
{
const HeapString& str=*i;
if (isSucceed)
{
for(j=0;j<Size;++j)
{
if (str.Compare(Names[j],ignoreCase)==0)
{
result.ForceSetFlag(Values[j]);
break;
}
}
if(j==Size)
{
isSucceed=false;
}
}
}
if(!isSucceed)
{
MEDUSA_ASSERT_FAILED("Invalid flags names");
}
return result;
}
static bool TryParse(EngineFeatures& outFlags,const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 outFlags = None;
 return true;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 outFlags = All;
 return true;
 
}
bool isSucceed=true;
uint j=0;
List<HeapString> names;
if ((StringParser::Split<char>(name,"|",names))==false)
{
return false;
};
for(auto i = (names).GetEnumerator();i.MoveNext();)
{
const HeapString& str=*i;
if (isSucceed)
{
for(j=0;j<Size;++j)
{
if (str.Compare(Names[j],ignoreCase)==0)
{
outFlags.ForceSetFlag(Values[j]);
break;
}
}
if(j==Size)
{
isSucceed=false;
}
}
}
return isSucceed;
}
static constexpr unsigned int Size=2;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const EngineFeaturesField<0,EngineFeatures::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const EngineFeaturesField<1|2,EngineFeatures::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const EngineFeaturesField<1,EngineFeatures::OnName0> MultipleThreadUpdating;
bool IsMultipleThreadUpdating()const 
{
 return (mState&MultipleThreadUpdating.IntValue) == MultipleThreadUpdating.IntValue;
 
}
static const EngineFeaturesField<2,EngineFeatures::OnName1> MultipleThreadRendering;
bool IsMultipleThreadRendering()const 
{
 return (mState&MultipleThreadRendering.IntValue) == MultipleThreadRendering.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef EngineFeatures::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef EngineFeatures::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef EngineFeatures::Names[Size]=
{
"MultipleThreadUpdating","MultipleThreadRendering"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int EngineFeatures::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const EngineFeatures::EngineFeaturesField<0,EngineFeatures::OnNameNone> EngineFeatures::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const EngineFeatures::EngineFeaturesField<1|2,EngineFeatures::OnNameAll> EngineFeatures::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const EngineFeatures::EngineFeaturesField<1,EngineFeatures::OnName0> EngineFeatures::MultipleThreadUpdating;
 MEDUSA_WEAK_MULTIPLE_DEFINE const EngineFeatures::EngineFeaturesField<2,EngineFeatures::OnName1> EngineFeatures::MultipleThreadRendering;
MEDUSA_END;
