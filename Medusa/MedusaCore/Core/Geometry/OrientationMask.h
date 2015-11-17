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
//STRONG_FLAGS_CUSTOM_7(OrientationMask,Up, 1,Down, 2,Left, 4,Right, 8,UpAndDown, 3,LeftAndRight, 12,AllButDown, 13);
class OrientationMask	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class OrientationMaskField	//[IGNORE_PRE_DECLARE]
{
friend class OrientationMask;
public:
 OrientationMaskField()
{
}
 bool operator==( OrientationMask rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( OrientationMask rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( OrientationMask rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( OrientationMask rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( OrientationMask rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( OrientationMask rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( OrientationMaskField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( OrientationMaskField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( OrientationMaskField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( OrientationMaskField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( OrientationMaskField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( OrientationMaskField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 OrientationMask operator|( OrientationMask rhs ) const
{
return OrientationMask( TValue | rhs.mState );
}
 OrientationMask operator&( OrientationMask rhs ) const
{
return OrientationMask( TValue & rhs.mState );
}
 OrientationMask operator^( OrientationMask rhs ) const
{
return OrientationMask( TValue ^ rhs.mState );
}
 OrientationMask operator~() const
{
return OrientationMask(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 OrientationMask operator|( OrientationMaskField<TValue2,TName2> rhs ) const
{
return OrientationMask(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 OrientationMask operator&( OrientationMaskField<TValue2,TName2> rhs ) const
{
return OrientationMask(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 OrientationMask operator^( OrientationMaskField<TValue2,TName2> rhs ) const
{
return OrientationMask(TValue ^ TValue2);
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
 OrientationMask( const OrientationMask& rhs ) : mState( rhs.mState ) 
{
}
 OrientationMask operator=( OrientationMask rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 OrientationMask(OrientationMaskField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator=( OrientationMaskField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( OrientationMask rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( OrientationMask rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( OrientationMask rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( OrientationMask rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( OrientationMask rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( OrientationMask rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( OrientationMaskField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( OrientationMaskField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( OrientationMaskField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( OrientationMaskField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( OrientationMaskField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( OrientationMaskField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 OrientationMask operator|( OrientationMask rhs ) const
{
return OrientationMask( mState | rhs.mState );
}
 OrientationMask operator&( OrientationMask rhs ) const
{
return OrientationMask( mState & rhs.mState );
}
 OrientationMask operator^( OrientationMask rhs ) const
{
return OrientationMask( mState ^ rhs.mState );
}
 OrientationMask operator~() const
{
return OrientationMask( ~mState );
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator|( OrientationMaskField<TValue,TName> rhs ) const
{
return OrientationMask( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator&( OrientationMaskField<TValue,TName> rhs ) const
{
return OrientationMask( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator^( OrientationMaskField<TValue,TName> rhs ) const
{
return OrientationMask( mState ^ TValue );
}
 OrientationMask& operator|=( OrientationMask rhs )
{
mState |= rhs.mState;
return *this;
}
 OrientationMask& operator&=( OrientationMask rhs )
{
mState &= rhs.mState;
return *this;
}
 OrientationMask& operator^=( OrientationMask rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator|=( OrientationMaskField<TValue,TName> rhs )
{
mState |= TValue;
return OrientationMask( *this );
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator&=( OrientationMaskField<TValue,TName> rhs )
{
mState &= TValue;
return OrientationMask( *this );
}
 template<int TValue,const StringRef& TName()>
 OrientationMask operator^=( OrientationMaskField<TValue,TName> rhs )
{
mState ^= TValue;
return OrientationMask( *this );
}
 OrientationMask operator<<( unsigned int s )
{
return OrientationMask( mState << s );
}
 OrientationMask operator>>( unsigned int s )
{
return OrientationMask( mState >> s );
}
 OrientationMask& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 OrientationMask& operator>>=( unsigned int s )
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
 bool Has(OrientationMask rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(OrientationMask rhs)
{
mState|=rhs.ToInt();
}
 void Remove(OrientationMask rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(OrientationMask rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(OrientationMask rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(OrientationMask rhs,bool isSet)
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
 bool Has(OrientationMaskField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(OrientationMaskField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(OrientationMaskField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(OrientationMaskField<TValue,TName> field,bool isSet)
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
explicit OrientationMask(int state=0):mState(state)
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
static const StringRef& OnName4()
{
return Names[4];
}
static const StringRef& OnName5()
{
return Names[5];
}
static const StringRef& OnName6()
{
return Names[6];
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
static OrientationMask Parse(int val)
{
if(IsDefined(val))
{
return OrientationMask(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return OrientationMask(val);
}
static bool TryParse(int val,OrientationMask& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static OrientationMask Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
OrientationMask result;
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
static bool TryParse(OrientationMask& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=7;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const OrientationMaskField<0,OrientationMask::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const OrientationMaskField<1|2|4|8|3|12|13,OrientationMask::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const OrientationMaskField<1,OrientationMask::OnName0> Up;
bool IsUp()const 
{
 return (mState&Up.IntValue) == Up.IntValue;
 
}
static const OrientationMaskField<2,OrientationMask::OnName1> Down;
bool IsDown()const 
{
 return (mState&Down.IntValue) == Down.IntValue;
 
}
static const OrientationMaskField<4,OrientationMask::OnName2> Left;
bool IsLeft()const 
{
 return (mState&Left.IntValue) == Left.IntValue;
 
}
static const OrientationMaskField<8,OrientationMask::OnName3> Right;
bool IsRight()const 
{
 return (mState&Right.IntValue) == Right.IntValue;
 
}
static const OrientationMaskField<3,OrientationMask::OnName4> UpAndDown;
bool IsUpAndDown()const 
{
 return (mState&UpAndDown.IntValue) == UpAndDown.IntValue;
 
}
static const OrientationMaskField<12,OrientationMask::OnName5> LeftAndRight;
bool IsLeftAndRight()const 
{
 return (mState&LeftAndRight.IntValue) == LeftAndRight.IntValue;
 
}
static const OrientationMaskField<13,OrientationMask::OnName6> AllButDown;
bool IsAllButDown()const 
{
 return (mState&AllButDown.IntValue) == AllButDown.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef OrientationMask::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef OrientationMask::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef OrientationMask::Names[Size]=
{
"Up","Down","Left","Right","UpAndDown","LeftAndRight","AllButDown"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int OrientationMask::Values[Size]=
{
1,2,4,8,3,12,13
};
MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<0,OrientationMask::OnNameNone> OrientationMask::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<1|2|4|8|3|12|13,OrientationMask::OnNameAll> OrientationMask::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<1,OrientationMask::OnName0> OrientationMask::Up;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<2,OrientationMask::OnName1> OrientationMask::Down;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<4,OrientationMask::OnName2> OrientationMask::Left;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<8,OrientationMask::OnName3> OrientationMask::Right;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<3,OrientationMask::OnName4> OrientationMask::UpAndDown;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<12,OrientationMask::OnName5> OrientationMask::LeftAndRight;
 MEDUSA_WEAK_MULTIPLE_DEFINE const OrientationMask::OrientationMaskField<13,OrientationMask::OnName6> OrientationMask::AllButDown;
MEDUSA_END;
