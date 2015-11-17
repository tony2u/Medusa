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
//STRONG_FLAGS_4(PODAnimiationFlags,HasPosition,HasRotation,HasScale,HasMatrix);
class PODAnimiationFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class PODAnimiationFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class PODAnimiationFlags;
public:
 PODAnimiationFlagsField()
{
}
 bool operator==( PODAnimiationFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( PODAnimiationFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( PODAnimiationFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( PODAnimiationFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( PODAnimiationFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( PODAnimiationFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 PODAnimiationFlags operator|( PODAnimiationFlags rhs ) const
{
return PODAnimiationFlags( TValue | rhs.mState );
}
 PODAnimiationFlags operator&( PODAnimiationFlags rhs ) const
{
return PODAnimiationFlags( TValue & rhs.mState );
}
 PODAnimiationFlags operator^( PODAnimiationFlags rhs ) const
{
return PODAnimiationFlags( TValue ^ rhs.mState );
}
 PODAnimiationFlags operator~() const
{
return PODAnimiationFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 PODAnimiationFlags operator|( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return PODAnimiationFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PODAnimiationFlags operator&( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return PODAnimiationFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PODAnimiationFlags operator^( PODAnimiationFlagsField<TValue2,TName2> rhs ) const
{
return PODAnimiationFlags(TValue ^ TValue2);
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
 PODAnimiationFlags( const PODAnimiationFlags& rhs ) : mState( rhs.mState ) 
{
}
 PODAnimiationFlags operator=( PODAnimiationFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags(PODAnimiationFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator=( PODAnimiationFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( PODAnimiationFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( PODAnimiationFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( PODAnimiationFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( PODAnimiationFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( PODAnimiationFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( PODAnimiationFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 PODAnimiationFlags operator|( PODAnimiationFlags rhs ) const
{
return PODAnimiationFlags( mState | rhs.mState );
}
 PODAnimiationFlags operator&( PODAnimiationFlags rhs ) const
{
return PODAnimiationFlags( mState & rhs.mState );
}
 PODAnimiationFlags operator^( PODAnimiationFlags rhs ) const
{
return PODAnimiationFlags( mState ^ rhs.mState );
}
 PODAnimiationFlags operator~() const
{
return PODAnimiationFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator|( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return PODAnimiationFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator&( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return PODAnimiationFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator^( PODAnimiationFlagsField<TValue,TName> rhs ) const
{
return PODAnimiationFlags( mState ^ TValue );
}
 PODAnimiationFlags& operator|=( PODAnimiationFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 PODAnimiationFlags& operator&=( PODAnimiationFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 PODAnimiationFlags& operator^=( PODAnimiationFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator|=( PODAnimiationFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return PODAnimiationFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator&=( PODAnimiationFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return PODAnimiationFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 PODAnimiationFlags operator^=( PODAnimiationFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return PODAnimiationFlags( *this );
}
 PODAnimiationFlags operator<<( unsigned int s )
{
return PODAnimiationFlags( mState << s );
}
 PODAnimiationFlags operator>>( unsigned int s )
{
return PODAnimiationFlags( mState >> s );
}
 PODAnimiationFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 PODAnimiationFlags& operator>>=( unsigned int s )
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
 bool Has(PODAnimiationFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(PODAnimiationFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(PODAnimiationFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(PODAnimiationFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(PODAnimiationFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(PODAnimiationFlags rhs,bool isSet)
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
 bool Has(PODAnimiationFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(PODAnimiationFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(PODAnimiationFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(PODAnimiationFlagsField<TValue,TName> field,bool isSet)
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
explicit PODAnimiationFlags(int state=0):mState(state)
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
static PODAnimiationFlags Parse(int val)
{
if(IsDefined(val))
{
return PODAnimiationFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return PODAnimiationFlags(val);
}
static bool TryParse(int val,PODAnimiationFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static PODAnimiationFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
PODAnimiationFlags result;
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
static bool TryParse(PODAnimiationFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const PODAnimiationFlagsField<0,PODAnimiationFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const PODAnimiationFlagsField<1|2|4|8,PODAnimiationFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const PODAnimiationFlagsField<1,PODAnimiationFlags::OnName0> HasPosition;
bool IsHasPosition()const 
{
 return (mState&HasPosition.IntValue) == HasPosition.IntValue;
 
}
static const PODAnimiationFlagsField<2,PODAnimiationFlags::OnName1> HasRotation;
bool IsHasRotation()const 
{
 return (mState&HasRotation.IntValue) == HasRotation.IntValue;
 
}
static const PODAnimiationFlagsField<4,PODAnimiationFlags::OnName2> HasScale;
bool IsHasScale()const 
{
 return (mState&HasScale.IntValue) == HasScale.IntValue;
 
}
static const PODAnimiationFlagsField<8,PODAnimiationFlags::OnName3> HasMatrix;
bool IsHasMatrix()const 
{
 return (mState&HasMatrix.IntValue) == HasMatrix.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PODAnimiationFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PODAnimiationFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PODAnimiationFlags::Names[Size]=
{
"HasPosition","HasRotation","HasScale","HasMatrix"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int PODAnimiationFlags::Values[Size]=
{
1,2,4,8
};
MEDUSA_WEAK_MULTIPLE_DEFINE const PODAnimiationFlags::PODAnimiationFlagsField<0,PODAnimiationFlags::OnNameNone> PODAnimiationFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const PODAnimiationFlags::PODAnimiationFlagsField<1|2|4|8,PODAnimiationFlags::OnNameAll> PODAnimiationFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PODAnimiationFlags::PODAnimiationFlagsField<1,PODAnimiationFlags::OnName0> PODAnimiationFlags::HasPosition;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PODAnimiationFlags::PODAnimiationFlagsField<2,PODAnimiationFlags::OnName1> PODAnimiationFlags::HasRotation;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PODAnimiationFlags::PODAnimiationFlagsField<4,PODAnimiationFlags::OnName2> PODAnimiationFlags::HasScale;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PODAnimiationFlags::PODAnimiationFlagsField<8,PODAnimiationFlags::OnName3> PODAnimiationFlags::HasMatrix;
MEDUSA_END;
