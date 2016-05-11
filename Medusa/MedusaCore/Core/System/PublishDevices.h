#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;
//STRONG_FLAGS_2(PublishDevices,sd,hd);
class PublishDevices	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class PublishDevicesField	//[IGNORE_PRE_DECLARE]
{
friend class PublishDevices;
public:
 PublishDevicesField()
{
}
 bool operator==( PublishDevices rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( PublishDevices rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( PublishDevices rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( PublishDevices rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( PublishDevices rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( PublishDevices rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( PublishDevicesField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( PublishDevicesField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( PublishDevicesField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( PublishDevicesField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( PublishDevicesField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( PublishDevicesField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 PublishDevices operator|( PublishDevices rhs ) const
{
return PublishDevices( TValue | rhs.mState );
}
 PublishDevices operator&( PublishDevices rhs ) const
{
return PublishDevices( TValue & rhs.mState );
}
 PublishDevices operator^( PublishDevices rhs ) const
{
return PublishDevices( TValue ^ rhs.mState );
}
 PublishDevices operator~() const
{
return PublishDevices(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 PublishDevices operator|( PublishDevicesField<TValue2,TName2> rhs ) const
{
return PublishDevices(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PublishDevices operator&( PublishDevicesField<TValue2,TName2> rhs ) const
{
return PublishDevices(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PublishDevices operator^( PublishDevicesField<TValue2,TName2> rhs ) const
{
return PublishDevices(TValue ^ TValue2);
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
 PublishDevices( const PublishDevices& rhs ) : mState( rhs.mState ) 
{
}
 PublishDevices operator=( PublishDevices rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PublishDevices(PublishDevicesField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator=( PublishDevicesField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( PublishDevices rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( PublishDevices rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( PublishDevices rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( PublishDevices rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( PublishDevices rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( PublishDevices rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( PublishDevicesField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( PublishDevicesField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( PublishDevicesField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( PublishDevicesField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( PublishDevicesField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( PublishDevicesField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 PublishDevices operator|( PublishDevices rhs ) const
{
return PublishDevices( mState | rhs.mState );
}
 PublishDevices operator&( PublishDevices rhs ) const
{
return PublishDevices( mState & rhs.mState );
}
 PublishDevices operator^( PublishDevices rhs ) const
{
return PublishDevices( mState ^ rhs.mState );
}
 PublishDevices operator~() const
{
return PublishDevices( ~mState );
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator|( PublishDevicesField<TValue,TName> rhs ) const
{
return PublishDevices( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator&( PublishDevicesField<TValue,TName> rhs ) const
{
return PublishDevices( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator^( PublishDevicesField<TValue,TName> rhs ) const
{
return PublishDevices( mState ^ TValue );
}
 PublishDevices& operator|=( PublishDevices rhs )
{
mState |= rhs.mState;
return *this;
}
 PublishDevices& operator&=( PublishDevices rhs )
{
mState &= rhs.mState;
return *this;
}
 PublishDevices& operator^=( PublishDevices rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator|=( PublishDevicesField<TValue,TName> rhs )
{
mState |= TValue;
return PublishDevices( *this );
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator&=( PublishDevicesField<TValue,TName> rhs )
{
mState &= TValue;
return PublishDevices( *this );
}
 template<int TValue,const StringRef& TName()>
 PublishDevices operator^=( PublishDevicesField<TValue,TName> rhs )
{
mState ^= TValue;
return PublishDevices( *this );
}
 PublishDevices operator<<( unsigned int s )
{
return PublishDevices( mState << s );
}
 PublishDevices operator>>( unsigned int s )
{
return PublishDevices( mState >> s );
}
 PublishDevices& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 PublishDevices& operator>>=( unsigned int s )
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
 bool Has(PublishDevices rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(PublishDevices rhs)
{
mState|=rhs.ToInt();
}
 void Remove(PublishDevices rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(PublishDevices rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(PublishDevices rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(PublishDevices rhs,bool isSet)
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
 bool Has(PublishDevicesField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(PublishDevicesField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(PublishDevicesField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(PublishDevicesField<TValue,TName> field,bool isSet)
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
explicit PublishDevices(int state=0):mState(state)
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
static PublishDevices Parse(int val)
{
if(IsDefined(val))
{
return PublishDevices(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return PublishDevices(val);
}
static bool TryParse(int val,PublishDevices& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static PublishDevices Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
PublishDevices result;
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
static bool TryParse(PublishDevices& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const PublishDevicesField<0,PublishDevices::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const PublishDevicesField<1|2,PublishDevices::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const PublishDevicesField<1,PublishDevices::OnName0> sd;
bool Issd()const 
{
 return (mState&sd.IntValue) == sd.IntValue;
 
}
static const PublishDevicesField<2,PublishDevices::OnName1> hd;
bool Ishd()const 
{
 return (mState&hd.IntValue) == hd.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishDevices::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishDevices::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PublishDevices::Names[Size]=
{
"sd","hd"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int PublishDevices::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const PublishDevices::PublishDevicesField<0,PublishDevices::OnNameNone> PublishDevices::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const PublishDevices::PublishDevicesField<1|2,PublishDevices::OnNameAll> PublishDevices::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PublishDevices::PublishDevicesField<1,PublishDevices::OnName0> PublishDevices::sd;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PublishDevices::PublishDevicesField<2,PublishDevices::OnName1> PublishDevices::hd;
MEDUSA_END;
