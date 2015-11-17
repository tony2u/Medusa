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
//STRONG_FLAGS_4(PackageFlags,Readonly,EncryptFileNames,WriteSaltData,WholeFileCoding);
class PackageFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class PackageFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class PackageFlags;
public:
 PackageFlagsField()
{
}
 bool operator==( PackageFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( PackageFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( PackageFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( PackageFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( PackageFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( PackageFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( PackageFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( PackageFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( PackageFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( PackageFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( PackageFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( PackageFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 PackageFlags operator|( PackageFlags rhs ) const
{
return PackageFlags( TValue | rhs.mState );
}
 PackageFlags operator&( PackageFlags rhs ) const
{
return PackageFlags( TValue & rhs.mState );
}
 PackageFlags operator^( PackageFlags rhs ) const
{
return PackageFlags( TValue ^ rhs.mState );
}
 PackageFlags operator~() const
{
return PackageFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 PackageFlags operator|( PackageFlagsField<TValue2,TName2> rhs ) const
{
return PackageFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PackageFlags operator&( PackageFlagsField<TValue2,TName2> rhs ) const
{
return PackageFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PackageFlags operator^( PackageFlagsField<TValue2,TName2> rhs ) const
{
return PackageFlags(TValue ^ TValue2);
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
 PackageFlags( const PackageFlags& rhs ) : mState( rhs.mState ) 
{
}
 PackageFlags operator=( PackageFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PackageFlags(PackageFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator=( PackageFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( PackageFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( PackageFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( PackageFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( PackageFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( PackageFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( PackageFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( PackageFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( PackageFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( PackageFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( PackageFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( PackageFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( PackageFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 PackageFlags operator|( PackageFlags rhs ) const
{
return PackageFlags( mState | rhs.mState );
}
 PackageFlags operator&( PackageFlags rhs ) const
{
return PackageFlags( mState & rhs.mState );
}
 PackageFlags operator^( PackageFlags rhs ) const
{
return PackageFlags( mState ^ rhs.mState );
}
 PackageFlags operator~() const
{
return PackageFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator|( PackageFlagsField<TValue,TName> rhs ) const
{
return PackageFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator&( PackageFlagsField<TValue,TName> rhs ) const
{
return PackageFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator^( PackageFlagsField<TValue,TName> rhs ) const
{
return PackageFlags( mState ^ TValue );
}
 PackageFlags& operator|=( PackageFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 PackageFlags& operator&=( PackageFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 PackageFlags& operator^=( PackageFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator|=( PackageFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return PackageFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator&=( PackageFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return PackageFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 PackageFlags operator^=( PackageFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return PackageFlags( *this );
}
 PackageFlags operator<<( unsigned int s )
{
return PackageFlags( mState << s );
}
 PackageFlags operator>>( unsigned int s )
{
return PackageFlags( mState >> s );
}
 PackageFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 PackageFlags& operator>>=( unsigned int s )
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
 bool Has(PackageFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(PackageFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(PackageFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(PackageFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(PackageFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(PackageFlags rhs,bool isSet)
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
 bool Has(PackageFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(PackageFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(PackageFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(PackageFlagsField<TValue,TName> field,bool isSet)
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
explicit PackageFlags(int state=0):mState(state)
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
static const StringRef& OnName2()
{
return Names[2];
}
static const StringRef& OnName3()
{
return Names[3];
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
static PackageFlags Parse(int val)
{
if(IsDefined(val))
{
return PackageFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return PackageFlags(val);
}
static bool TryParse(int val,PackageFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static PackageFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
PackageFlags result;
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
static bool TryParse(PackageFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=4;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const PackageFlagsField<0,PackageFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const PackageFlagsField<1|2|4|8,PackageFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const PackageFlagsField<1,PackageFlags::OnName0> Readonly;
bool IsReadonly()const 
{
 return (mState&Readonly.IntValue) == Readonly.IntValue;
 
}
static const PackageFlagsField<2,PackageFlags::OnName1> EncryptFileNames;
bool IsEncryptFileNames()const 
{
 return (mState&EncryptFileNames.IntValue) == EncryptFileNames.IntValue;
 
}
static const PackageFlagsField<4,PackageFlags::OnName2> WriteSaltData;
bool IsWriteSaltData()const 
{
 return (mState&WriteSaltData.IntValue) == WriteSaltData.IntValue;
 
}
static const PackageFlagsField<8,PackageFlags::OnName3> WholeFileCoding;
bool IsWholeFileCoding()const 
{
 return (mState&WholeFileCoding.IntValue) == WholeFileCoding.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PackageFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PackageFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PackageFlags::Names[Size]=
{
"Readonly","EncryptFileNames","WriteSaltData","WholeFileCoding"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int PackageFlags::Values[Size]=
{
1,2,4,8
};
MEDUSA_WEAK_MULTIPLE_DEFINE const PackageFlags::PackageFlagsField<0,PackageFlags::OnNameNone> PackageFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const PackageFlags::PackageFlagsField<1|2|4|8,PackageFlags::OnNameAll> PackageFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PackageFlags::PackageFlagsField<1,PackageFlags::OnName0> PackageFlags::Readonly;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PackageFlags::PackageFlagsField<2,PackageFlags::OnName1> PackageFlags::EncryptFileNames;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PackageFlags::PackageFlagsField<4,PackageFlags::OnName2> PackageFlags::WriteSaltData;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PackageFlags::PackageFlagsField<8,PackageFlags::OnName3> PackageFlags::WholeFileCoding;
MEDUSA_END;
