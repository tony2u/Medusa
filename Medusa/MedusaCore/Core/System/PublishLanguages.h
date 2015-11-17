// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;
//STRONG_FLAGS_2(PublishLanguages,enus,zhcn);
class PublishLanguages	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class PublishLanguagesField	//[IGNORE_PRE_DECLARE]
{
friend class PublishLanguages;
public:
 PublishLanguagesField()
{
}
 bool operator==( PublishLanguages rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( PublishLanguages rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( PublishLanguages rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( PublishLanguages rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( PublishLanguages rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( PublishLanguages rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 PublishLanguages operator|( PublishLanguages rhs ) const
{
return PublishLanguages( TValue | rhs.mState );
}
 PublishLanguages operator&( PublishLanguages rhs ) const
{
return PublishLanguages( TValue & rhs.mState );
}
 PublishLanguages operator^( PublishLanguages rhs ) const
{
return PublishLanguages( TValue ^ rhs.mState );
}
 PublishLanguages operator~() const
{
return PublishLanguages(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 PublishLanguages operator|( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return PublishLanguages(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PublishLanguages operator&( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return PublishLanguages(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PublishLanguages operator^( PublishLanguagesField<TValue2,TName2> rhs ) const
{
return PublishLanguages(TValue ^ TValue2);
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
 PublishLanguages( const PublishLanguages& rhs ) : mState( rhs.mState ) 
{
}
 PublishLanguages operator=( PublishLanguages rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages(PublishLanguagesField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator=( PublishLanguagesField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( PublishLanguages rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( PublishLanguages rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( PublishLanguages rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( PublishLanguages rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( PublishLanguages rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( PublishLanguages rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( PublishLanguagesField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( PublishLanguagesField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( PublishLanguagesField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( PublishLanguagesField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( PublishLanguagesField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( PublishLanguagesField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 PublishLanguages operator|( PublishLanguages rhs ) const
{
return PublishLanguages( mState | rhs.mState );
}
 PublishLanguages operator&( PublishLanguages rhs ) const
{
return PublishLanguages( mState & rhs.mState );
}
 PublishLanguages operator^( PublishLanguages rhs ) const
{
return PublishLanguages( mState ^ rhs.mState );
}
 PublishLanguages operator~() const
{
return PublishLanguages( ~mState );
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator|( PublishLanguagesField<TValue,TName> rhs ) const
{
return PublishLanguages( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator&( PublishLanguagesField<TValue,TName> rhs ) const
{
return PublishLanguages( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator^( PublishLanguagesField<TValue,TName> rhs ) const
{
return PublishLanguages( mState ^ TValue );
}
 PublishLanguages& operator|=( PublishLanguages rhs )
{
mState |= rhs.mState;
return *this;
}
 PublishLanguages& operator&=( PublishLanguages rhs )
{
mState &= rhs.mState;
return *this;
}
 PublishLanguages& operator^=( PublishLanguages rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator|=( PublishLanguagesField<TValue,TName> rhs )
{
mState |= TValue;
return PublishLanguages( *this );
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator&=( PublishLanguagesField<TValue,TName> rhs )
{
mState &= TValue;
return PublishLanguages( *this );
}
 template<int TValue,const StringRef& TName()>
 PublishLanguages operator^=( PublishLanguagesField<TValue,TName> rhs )
{
mState ^= TValue;
return PublishLanguages( *this );
}
 PublishLanguages operator<<( unsigned int s )
{
return PublishLanguages( mState << s );
}
 PublishLanguages operator>>( unsigned int s )
{
return PublishLanguages( mState >> s );
}
 PublishLanguages& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 PublishLanguages& operator>>=( unsigned int s )
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
 bool Has(PublishLanguages rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(PublishLanguages rhs)
{
mState|=rhs.ToInt();
}
 void Remove(PublishLanguages rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(PublishLanguages rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(PublishLanguages rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(PublishLanguages rhs,bool isSet)
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
 bool Has(PublishLanguagesField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(PublishLanguagesField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(PublishLanguagesField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(PublishLanguagesField<TValue,TName> field,bool isSet)
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
explicit PublishLanguages(int state=0):mState(state)
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
static PublishLanguages Parse(int val)
{
if(IsDefined(val))
{
return PublishLanguages(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return PublishLanguages(val);
}
static bool TryParse(int val,PublishLanguages& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static PublishLanguages Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
PublishLanguages result;
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
static bool TryParse(PublishLanguages& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const PublishLanguagesField<0,PublishLanguages::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const PublishLanguagesField<1|2,PublishLanguages::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const PublishLanguagesField<1,PublishLanguages::OnName0> enus;
bool Isenus()const 
{
 return (mState&enus.IntValue) == enus.IntValue;
 
}
static const PublishLanguagesField<2,PublishLanguages::OnName1> zhcn;
bool Iszhcn()const 
{
 return (mState&zhcn.IntValue) == zhcn.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishLanguages::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishLanguages::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishLanguages::Names[Size]=
{
"enus","zhcn"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int PublishLanguages::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const PublishLanguages::PublishLanguagesField<0,PublishLanguages::OnNameNone> PublishLanguages::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const PublishLanguages::PublishLanguagesField<1|2,PublishLanguages::OnNameAll> PublishLanguages::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PublishLanguages::PublishLanguagesField<1,PublishLanguages::OnName0> PublishLanguages::enus;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PublishLanguages::PublishLanguagesField<2,PublishLanguages::OnName1> PublishLanguages::zhcn;
MEDUSA_END;
