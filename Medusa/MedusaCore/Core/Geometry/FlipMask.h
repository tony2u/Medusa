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
//STRONG_FLAGS_3(FlipMask, X, Y, Z);
class FlipMask	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class FlipMaskField	//[IGNORE_PRE_DECLARE]
{
friend class FlipMask;
public:
 FlipMaskField()
{
}
 bool operator==( FlipMask rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( FlipMask rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( FlipMask rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( FlipMask rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( FlipMask rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( FlipMask rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( FlipMaskField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( FlipMaskField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( FlipMaskField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( FlipMaskField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( FlipMaskField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( FlipMaskField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 FlipMask operator|( FlipMask rhs ) const
{
return FlipMask( TValue | rhs.mState );
}
 FlipMask operator&( FlipMask rhs ) const
{
return FlipMask( TValue & rhs.mState );
}
 FlipMask operator^( FlipMask rhs ) const
{
return FlipMask( TValue ^ rhs.mState );
}
 FlipMask operator~() const
{
return FlipMask(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 FlipMask operator|( FlipMaskField<TValue2,TName2> rhs ) const
{
return FlipMask(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 FlipMask operator&( FlipMaskField<TValue2,TName2> rhs ) const
{
return FlipMask(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 FlipMask operator^( FlipMaskField<TValue2,TName2> rhs ) const
{
return FlipMask(TValue ^ TValue2);
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
 FlipMask( const FlipMask& rhs ) : mState( rhs.mState ) 
{
}
 FlipMask operator=( FlipMask rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 FlipMask(FlipMaskField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator=( FlipMaskField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( FlipMask rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( FlipMask rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( FlipMask rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( FlipMask rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( FlipMask rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( FlipMask rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( FlipMaskField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( FlipMaskField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( FlipMaskField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( FlipMaskField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( FlipMaskField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( FlipMaskField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 FlipMask operator|( FlipMask rhs ) const
{
return FlipMask( mState | rhs.mState );
}
 FlipMask operator&( FlipMask rhs ) const
{
return FlipMask( mState & rhs.mState );
}
 FlipMask operator^( FlipMask rhs ) const
{
return FlipMask( mState ^ rhs.mState );
}
 FlipMask operator~() const
{
return FlipMask( ~mState );
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator|( FlipMaskField<TValue,TName> rhs ) const
{
return FlipMask( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator&( FlipMaskField<TValue,TName> rhs ) const
{
return FlipMask( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator^( FlipMaskField<TValue,TName> rhs ) const
{
return FlipMask( mState ^ TValue );
}
 FlipMask& operator|=( FlipMask rhs )
{
mState |= rhs.mState;
return *this;
}
 FlipMask& operator&=( FlipMask rhs )
{
mState &= rhs.mState;
return *this;
}
 FlipMask& operator^=( FlipMask rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator|=( FlipMaskField<TValue,TName> rhs )
{
mState |= TValue;
return FlipMask( *this );
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator&=( FlipMaskField<TValue,TName> rhs )
{
mState &= TValue;
return FlipMask( *this );
}
 template<int TValue,const StringRef& TName()>
 FlipMask operator^=( FlipMaskField<TValue,TName> rhs )
{
mState ^= TValue;
return FlipMask( *this );
}
 FlipMask operator<<( unsigned int s )
{
return FlipMask( mState << s );
}
 FlipMask operator>>( unsigned int s )
{
return FlipMask( mState >> s );
}
 FlipMask& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 FlipMask& operator>>=( unsigned int s )
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
 bool Has(FlipMask rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(FlipMask rhs)
{
mState|=rhs.ToInt();
}
 void Remove(FlipMask rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(FlipMask rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(FlipMask rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(FlipMask rhs,bool isSet)
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
 bool Has(FlipMaskField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(FlipMaskField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(FlipMaskField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(FlipMaskField<TValue,TName> field,bool isSet)
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
explicit FlipMask(int state=0):mState(state)
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
static FlipMask Parse(int val)
{
if(IsDefined(val))
{
return FlipMask(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return FlipMask(val);
}
static bool TryParse(int val,FlipMask& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static FlipMask Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
FlipMask result;
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
static bool TryParse(FlipMask& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const FlipMaskField<0,FlipMask::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const FlipMaskField<1|2|4,FlipMask::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const FlipMaskField<1,FlipMask::OnName0> X;
bool IsX()const 
{
 return (mState&X.IntValue) == X.IntValue;
 
}
static const FlipMaskField<2,FlipMask::OnName1> Y;
bool IsY()const 
{
 return (mState&Y.IntValue) == Y.IntValue;
 
}
static const FlipMaskField<4,FlipMask::OnName2> Z;
bool IsZ()const 
{
 return (mState&Z.IntValue) == Z.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FlipMask::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FlipMask::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FlipMask::Names[Size]=
{
"X","Y","Z"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int FlipMask::Values[Size]=
{
1,2,4
};
MEDUSA_WEAK_MULTIPLE_DEFINE const FlipMask::FlipMaskField<0,FlipMask::OnNameNone> FlipMask::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const FlipMask::FlipMaskField<1|2|4,FlipMask::OnNameAll> FlipMask::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FlipMask::FlipMaskField<1,FlipMask::OnName0> FlipMask::X;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FlipMask::FlipMaskField<2,FlipMask::OnName1> FlipMask::Y;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FlipMask::FlipMaskField<4,FlipMask::OnName2> FlipMask::Z;
MEDUSA_END;
