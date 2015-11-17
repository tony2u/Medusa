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
//STRONG_FLAGS_3(MoveableInheritFlags, IgnoreScale, IgnoreRotation, IgnoreFlip);
class MoveableInheritFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class MoveableInheritFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class MoveableInheritFlags;
public:
 MoveableInheritFlagsField()
{
}
 bool operator==( MoveableInheritFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( MoveableInheritFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( MoveableInheritFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( MoveableInheritFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( MoveableInheritFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( MoveableInheritFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 MoveableInheritFlags operator|( MoveableInheritFlags rhs ) const
{
return MoveableInheritFlags( TValue | rhs.mState );
}
 MoveableInheritFlags operator&( MoveableInheritFlags rhs ) const
{
return MoveableInheritFlags( TValue & rhs.mState );
}
 MoveableInheritFlags operator^( MoveableInheritFlags rhs ) const
{
return MoveableInheritFlags( TValue ^ rhs.mState );
}
 MoveableInheritFlags operator~() const
{
return MoveableInheritFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 MoveableInheritFlags operator|( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return MoveableInheritFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 MoveableInheritFlags operator&( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return MoveableInheritFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 MoveableInheritFlags operator^( MoveableInheritFlagsField<TValue2,TName2> rhs ) const
{
return MoveableInheritFlags(TValue ^ TValue2);
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
 MoveableInheritFlags( const MoveableInheritFlags& rhs ) : mState( rhs.mState ) 
{
}
 MoveableInheritFlags operator=( MoveableInheritFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags(MoveableInheritFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator=( MoveableInheritFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( MoveableInheritFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( MoveableInheritFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( MoveableInheritFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( MoveableInheritFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( MoveableInheritFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( MoveableInheritFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 MoveableInheritFlags operator|( MoveableInheritFlags rhs ) const
{
return MoveableInheritFlags( mState | rhs.mState );
}
 MoveableInheritFlags operator&( MoveableInheritFlags rhs ) const
{
return MoveableInheritFlags( mState & rhs.mState );
}
 MoveableInheritFlags operator^( MoveableInheritFlags rhs ) const
{
return MoveableInheritFlags( mState ^ rhs.mState );
}
 MoveableInheritFlags operator~() const
{
return MoveableInheritFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator|( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return MoveableInheritFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator&( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return MoveableInheritFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator^( MoveableInheritFlagsField<TValue,TName> rhs ) const
{
return MoveableInheritFlags( mState ^ TValue );
}
 MoveableInheritFlags& operator|=( MoveableInheritFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 MoveableInheritFlags& operator&=( MoveableInheritFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 MoveableInheritFlags& operator^=( MoveableInheritFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator|=( MoveableInheritFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return MoveableInheritFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator&=( MoveableInheritFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return MoveableInheritFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 MoveableInheritFlags operator^=( MoveableInheritFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return MoveableInheritFlags( *this );
}
 MoveableInheritFlags operator<<( unsigned int s )
{
return MoveableInheritFlags( mState << s );
}
 MoveableInheritFlags operator>>( unsigned int s )
{
return MoveableInheritFlags( mState >> s );
}
 MoveableInheritFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 MoveableInheritFlags& operator>>=( unsigned int s )
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
 bool Has(MoveableInheritFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(MoveableInheritFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(MoveableInheritFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(MoveableInheritFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(MoveableInheritFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(MoveableInheritFlags rhs,bool isSet)
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
 bool Has(MoveableInheritFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(MoveableInheritFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(MoveableInheritFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(MoveableInheritFlagsField<TValue,TName> field,bool isSet)
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
explicit MoveableInheritFlags(int state=0):mState(state)
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
static MoveableInheritFlags Parse(int val)
{
if(IsDefined(val))
{
return MoveableInheritFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return MoveableInheritFlags(val);
}
static bool TryParse(int val,MoveableInheritFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static MoveableInheritFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
MoveableInheritFlags result;
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
static bool TryParse(MoveableInheritFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=3;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const MoveableInheritFlagsField<0,MoveableInheritFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const MoveableInheritFlagsField<1|2|4,MoveableInheritFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const MoveableInheritFlagsField<1,MoveableInheritFlags::OnName0> IgnoreScale;
bool IsIgnoreScale()const 
{
 return (mState&IgnoreScale.IntValue) == IgnoreScale.IntValue;
 
}
static const MoveableInheritFlagsField<2,MoveableInheritFlags::OnName1> IgnoreRotation;
bool IsIgnoreRotation()const 
{
 return (mState&IgnoreRotation.IntValue) == IgnoreRotation.IntValue;
 
}
static const MoveableInheritFlagsField<4,MoveableInheritFlags::OnName2> IgnoreFlip;
bool IsIgnoreFlip()const 
{
 return (mState&IgnoreFlip.IntValue) == IgnoreFlip.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MoveableInheritFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MoveableInheritFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MoveableInheritFlags::Names[Size]=
{
"IgnoreScale","IgnoreRotation","IgnoreFlip"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int MoveableInheritFlags::Values[Size]=
{
1,2,4
};
MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableInheritFlags::MoveableInheritFlagsField<0,MoveableInheritFlags::OnNameNone> MoveableInheritFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableInheritFlags::MoveableInheritFlagsField<1|2|4,MoveableInheritFlags::OnNameAll> MoveableInheritFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableInheritFlags::MoveableInheritFlagsField<1,MoveableInheritFlags::OnName0> MoveableInheritFlags::IgnoreScale;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableInheritFlags::MoveableInheritFlagsField<2,MoveableInheritFlags::OnName1> MoveableInheritFlags::IgnoreRotation;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableInheritFlags::MoveableInheritFlagsField<4,MoveableInheritFlags::OnName2> MoveableInheritFlags::IgnoreFlip;
MEDUSA_END;
