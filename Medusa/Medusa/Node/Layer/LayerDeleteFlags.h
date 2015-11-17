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
//STRONG_FLAGS_1(LayerDeleteFlags,Async);
class LayerDeleteFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class LayerDeleteFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class LayerDeleteFlags;
public:
 LayerDeleteFlagsField()
{
}
 bool operator==( LayerDeleteFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( LayerDeleteFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( LayerDeleteFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( LayerDeleteFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( LayerDeleteFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( LayerDeleteFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 LayerDeleteFlags operator|( LayerDeleteFlags rhs ) const
{
return LayerDeleteFlags( TValue | rhs.mState );
}
 LayerDeleteFlags operator&( LayerDeleteFlags rhs ) const
{
return LayerDeleteFlags( TValue & rhs.mState );
}
 LayerDeleteFlags operator^( LayerDeleteFlags rhs ) const
{
return LayerDeleteFlags( TValue ^ rhs.mState );
}
 LayerDeleteFlags operator~() const
{
return LayerDeleteFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 LayerDeleteFlags operator|( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return LayerDeleteFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 LayerDeleteFlags operator&( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return LayerDeleteFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 LayerDeleteFlags operator^( LayerDeleteFlagsField<TValue2,TName2> rhs ) const
{
return LayerDeleteFlags(TValue ^ TValue2);
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
 LayerDeleteFlags( const LayerDeleteFlags& rhs ) : mState( rhs.mState ) 
{
}
 LayerDeleteFlags operator=( LayerDeleteFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags(LayerDeleteFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator=( LayerDeleteFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( LayerDeleteFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( LayerDeleteFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( LayerDeleteFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( LayerDeleteFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( LayerDeleteFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( LayerDeleteFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 LayerDeleteFlags operator|( LayerDeleteFlags rhs ) const
{
return LayerDeleteFlags( mState | rhs.mState );
}
 LayerDeleteFlags operator&( LayerDeleteFlags rhs ) const
{
return LayerDeleteFlags( mState & rhs.mState );
}
 LayerDeleteFlags operator^( LayerDeleteFlags rhs ) const
{
return LayerDeleteFlags( mState ^ rhs.mState );
}
 LayerDeleteFlags operator~() const
{
return LayerDeleteFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator|( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return LayerDeleteFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator&( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return LayerDeleteFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator^( LayerDeleteFlagsField<TValue,TName> rhs ) const
{
return LayerDeleteFlags( mState ^ TValue );
}
 LayerDeleteFlags& operator|=( LayerDeleteFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 LayerDeleteFlags& operator&=( LayerDeleteFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 LayerDeleteFlags& operator^=( LayerDeleteFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator|=( LayerDeleteFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return LayerDeleteFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator&=( LayerDeleteFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return LayerDeleteFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 LayerDeleteFlags operator^=( LayerDeleteFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return LayerDeleteFlags( *this );
}
 LayerDeleteFlags operator<<( unsigned int s )
{
return LayerDeleteFlags( mState << s );
}
 LayerDeleteFlags operator>>( unsigned int s )
{
return LayerDeleteFlags( mState >> s );
}
 LayerDeleteFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 LayerDeleteFlags& operator>>=( unsigned int s )
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
 bool Has(LayerDeleteFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(LayerDeleteFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(LayerDeleteFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(LayerDeleteFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(LayerDeleteFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(LayerDeleteFlags rhs,bool isSet)
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
 bool Has(LayerDeleteFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(LayerDeleteFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(LayerDeleteFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(LayerDeleteFlagsField<TValue,TName> field,bool isSet)
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
explicit LayerDeleteFlags(int state=0):mState(state)
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
static LayerDeleteFlags Parse(int val)
{
if(IsDefined(val))
{
return LayerDeleteFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return LayerDeleteFlags(val);
}
static bool TryParse(int val,LayerDeleteFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static LayerDeleteFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
LayerDeleteFlags result;
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
static bool TryParse(LayerDeleteFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=1;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const LayerDeleteFlagsField<0,LayerDeleteFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const LayerDeleteFlagsField<1,LayerDeleteFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const LayerDeleteFlagsField<1,LayerDeleteFlags::OnName0> Async;
bool IsAsync()const 
{
 return (mState&Async.IntValue) == Async.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerDeleteFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerDeleteFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerDeleteFlags::Names[Size]=
{
"Async"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int LayerDeleteFlags::Values[Size]=
{
1
};
MEDUSA_WEAK_MULTIPLE_DEFINE const LayerDeleteFlags::LayerDeleteFlagsField<0,LayerDeleteFlags::OnNameNone> LayerDeleteFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const LayerDeleteFlags::LayerDeleteFlagsField<1,LayerDeleteFlags::OnNameAll> LayerDeleteFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerDeleteFlags::LayerDeleteFlagsField<1,LayerDeleteFlags::OnName0> LayerDeleteFlags::Async;
MEDUSA_END;
