#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;
//STRONG_FLAGS_2(PublishVersions,main,free);
class PublishVersions	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class PublishVersionsField	//[IGNORE_PRE_DECLARE]
{
friend class PublishVersions;
public:
 PublishVersionsField()
{
}
 bool operator==( PublishVersions rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( PublishVersions rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( PublishVersions rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( PublishVersions rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( PublishVersions rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( PublishVersions rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( PublishVersionsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( PublishVersionsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( PublishVersionsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( PublishVersionsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( PublishVersionsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( PublishVersionsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 PublishVersions operator|( PublishVersions rhs ) const
{
return PublishVersions( TValue | rhs.mState );
}
 PublishVersions operator&( PublishVersions rhs ) const
{
return PublishVersions( TValue & rhs.mState );
}
 PublishVersions operator^( PublishVersions rhs ) const
{
return PublishVersions( TValue ^ rhs.mState );
}
 PublishVersions operator~() const
{
return PublishVersions(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 PublishVersions operator|( PublishVersionsField<TValue2,TName2> rhs ) const
{
return PublishVersions(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PublishVersions operator&( PublishVersionsField<TValue2,TName2> rhs ) const
{
return PublishVersions(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PublishVersions operator^( PublishVersionsField<TValue2,TName2> rhs ) const
{
return PublishVersions(TValue ^ TValue2);
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
 PublishVersions( const PublishVersions& rhs ) : mState( rhs.mState ) 
{
}
 PublishVersions operator=( PublishVersions rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PublishVersions(PublishVersionsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator=( PublishVersionsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( PublishVersions rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( PublishVersions rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( PublishVersions rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( PublishVersions rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( PublishVersions rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( PublishVersions rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( PublishVersionsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( PublishVersionsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( PublishVersionsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( PublishVersionsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( PublishVersionsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( PublishVersionsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 PublishVersions operator|( PublishVersions rhs ) const
{
return PublishVersions( mState | rhs.mState );
}
 PublishVersions operator&( PublishVersions rhs ) const
{
return PublishVersions( mState & rhs.mState );
}
 PublishVersions operator^( PublishVersions rhs ) const
{
return PublishVersions( mState ^ rhs.mState );
}
 PublishVersions operator~() const
{
return PublishVersions( ~mState );
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator|( PublishVersionsField<TValue,TName> rhs ) const
{
return PublishVersions( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator&( PublishVersionsField<TValue,TName> rhs ) const
{
return PublishVersions( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator^( PublishVersionsField<TValue,TName> rhs ) const
{
return PublishVersions( mState ^ TValue );
}
 PublishVersions& operator|=( PublishVersions rhs )
{
mState |= rhs.mState;
return *this;
}
 PublishVersions& operator&=( PublishVersions rhs )
{
mState &= rhs.mState;
return *this;
}
 PublishVersions& operator^=( PublishVersions rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator|=( PublishVersionsField<TValue,TName> rhs )
{
mState |= TValue;
return PublishVersions( *this );
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator&=( PublishVersionsField<TValue,TName> rhs )
{
mState &= TValue;
return PublishVersions( *this );
}
 template<int TValue,const StringRef& TName()>
 PublishVersions operator^=( PublishVersionsField<TValue,TName> rhs )
{
mState ^= TValue;
return PublishVersions( *this );
}
 PublishVersions operator<<( unsigned int s )
{
return PublishVersions( mState << s );
}
 PublishVersions operator>>( unsigned int s )
{
return PublishVersions( mState >> s );
}
 PublishVersions& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 PublishVersions& operator>>=( unsigned int s )
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
 bool Has(PublishVersions rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(PublishVersions rhs)
{
mState|=rhs.ToInt();
}
 void Remove(PublishVersions rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(PublishVersions rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(PublishVersions rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(PublishVersions rhs,bool isSet)
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
 bool Has(PublishVersionsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(PublishVersionsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(PublishVersionsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(PublishVersionsField<TValue,TName> field,bool isSet)
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
explicit PublishVersions(int state=0):mState(state)
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
static PublishVersions Parse(int val)
{
if(IsDefined(val))
{
return PublishVersions(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return PublishVersions(val);
}
static bool TryParse(int val,PublishVersions& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static PublishVersions Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
PublishVersions result;
bool isSucceed=true;
uint j=0;
List<HeapString> names;
bool splitResult=StringParser::Split<char>(name,"|",names);
if(!splitResult)
{
MEDUSA_ASSERT_FAILED("Invalid flags names");
}
for(const auto& str:names)
{
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
static bool TryParse(PublishVersions& outFlags,const StringRef& name,bool ignoreCase=false)
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
for(const auto& str:names)
{
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
static const PublishVersionsField<0,PublishVersions::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const PublishVersionsField<1|2,PublishVersions::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const PublishVersionsField<1,PublishVersions::OnName0> main;
bool Ismain()const 
{
 return (mState&main.IntValue) == main.IntValue;
 
}
static const PublishVersionsField<2,PublishVersions::OnName1> free;
bool Isfree()const 
{
 return (mState&free.IntValue) == free.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishVersions::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishVersions::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishVersions::Names[Size]=
{
"main","free"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int PublishVersions::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const PublishVersions::PublishVersionsField<0,PublishVersions::OnNameNone> PublishVersions::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const PublishVersions::PublishVersionsField<1|2,PublishVersions::OnNameAll> PublishVersions::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PublishVersions::PublishVersionsField<1,PublishVersions::OnName0> PublishVersions::main;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PublishVersions::PublishVersionsField<2,PublishVersions::OnName1> PublishVersions::free;
MEDUSA_END;
