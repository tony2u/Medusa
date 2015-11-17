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
//STRONG_FLAGS_3(ApplicationDebugInfoFlags, Performance, GPU, Touch);
class ApplicationDebugInfoFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class ApplicationDebugInfoFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class ApplicationDebugInfoFlags;
public:
 ApplicationDebugInfoFlagsField()
{
}
 bool operator==( ApplicationDebugInfoFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( ApplicationDebugInfoFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( ApplicationDebugInfoFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( ApplicationDebugInfoFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( ApplicationDebugInfoFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( ApplicationDebugInfoFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 ApplicationDebugInfoFlags operator|( ApplicationDebugInfoFlags rhs ) const
{
return ApplicationDebugInfoFlags( TValue | rhs.mState );
}
 ApplicationDebugInfoFlags operator&( ApplicationDebugInfoFlags rhs ) const
{
return ApplicationDebugInfoFlags( TValue & rhs.mState );
}
 ApplicationDebugInfoFlags operator^( ApplicationDebugInfoFlags rhs ) const
{
return ApplicationDebugInfoFlags( TValue ^ rhs.mState );
}
 ApplicationDebugInfoFlags operator~() const
{
return ApplicationDebugInfoFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 ApplicationDebugInfoFlags operator|( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return ApplicationDebugInfoFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ApplicationDebugInfoFlags operator&( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return ApplicationDebugInfoFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ApplicationDebugInfoFlags operator^( ApplicationDebugInfoFlagsField<TValue2,TName2> rhs ) const
{
return ApplicationDebugInfoFlags(TValue ^ TValue2);
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
 ApplicationDebugInfoFlags( const ApplicationDebugInfoFlags& rhs ) : mState( rhs.mState ) 
{
}
 ApplicationDebugInfoFlags operator=( ApplicationDebugInfoFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags(ApplicationDebugInfoFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator=( ApplicationDebugInfoFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( ApplicationDebugInfoFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( ApplicationDebugInfoFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( ApplicationDebugInfoFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( ApplicationDebugInfoFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( ApplicationDebugInfoFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( ApplicationDebugInfoFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 ApplicationDebugInfoFlags operator|( ApplicationDebugInfoFlags rhs ) const
{
return ApplicationDebugInfoFlags( mState | rhs.mState );
}
 ApplicationDebugInfoFlags operator&( ApplicationDebugInfoFlags rhs ) const
{
return ApplicationDebugInfoFlags( mState & rhs.mState );
}
 ApplicationDebugInfoFlags operator^( ApplicationDebugInfoFlags rhs ) const
{
return ApplicationDebugInfoFlags( mState ^ rhs.mState );
}
 ApplicationDebugInfoFlags operator~() const
{
return ApplicationDebugInfoFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator|( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return ApplicationDebugInfoFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator&( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return ApplicationDebugInfoFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator^( ApplicationDebugInfoFlagsField<TValue,TName> rhs ) const
{
return ApplicationDebugInfoFlags( mState ^ TValue );
}
 ApplicationDebugInfoFlags& operator|=( ApplicationDebugInfoFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 ApplicationDebugInfoFlags& operator&=( ApplicationDebugInfoFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 ApplicationDebugInfoFlags& operator^=( ApplicationDebugInfoFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator|=( ApplicationDebugInfoFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return ApplicationDebugInfoFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator&=( ApplicationDebugInfoFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return ApplicationDebugInfoFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 ApplicationDebugInfoFlags operator^=( ApplicationDebugInfoFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return ApplicationDebugInfoFlags( *this );
}
 ApplicationDebugInfoFlags operator<<( unsigned int s )
{
return ApplicationDebugInfoFlags( mState << s );
}
 ApplicationDebugInfoFlags operator>>( unsigned int s )
{
return ApplicationDebugInfoFlags( mState >> s );
}
 ApplicationDebugInfoFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 ApplicationDebugInfoFlags& operator>>=( unsigned int s )
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
 bool Has(ApplicationDebugInfoFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(ApplicationDebugInfoFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(ApplicationDebugInfoFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(ApplicationDebugInfoFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(ApplicationDebugInfoFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(ApplicationDebugInfoFlags rhs,bool isSet)
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
 bool Has(ApplicationDebugInfoFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(ApplicationDebugInfoFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(ApplicationDebugInfoFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(ApplicationDebugInfoFlagsField<TValue,TName> field,bool isSet)
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
explicit ApplicationDebugInfoFlags(int state=0):mState(state)
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
static ApplicationDebugInfoFlags Parse(int val)
{
if(IsDefined(val))
{
return ApplicationDebugInfoFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return ApplicationDebugInfoFlags(val);
}
static bool TryParse(int val,ApplicationDebugInfoFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static ApplicationDebugInfoFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
ApplicationDebugInfoFlags result;
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
static bool TryParse(ApplicationDebugInfoFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const ApplicationDebugInfoFlagsField<0,ApplicationDebugInfoFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const ApplicationDebugInfoFlagsField<1|2|4,ApplicationDebugInfoFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const ApplicationDebugInfoFlagsField<1,ApplicationDebugInfoFlags::OnName0> Performance;
bool IsPerformance()const 
{
 return (mState&Performance.IntValue) == Performance.IntValue;
 
}
static const ApplicationDebugInfoFlagsField<2,ApplicationDebugInfoFlags::OnName1> GPU;
bool IsGPU()const 
{
 return (mState&GPU.IntValue) == GPU.IntValue;
 
}
static const ApplicationDebugInfoFlagsField<4,ApplicationDebugInfoFlags::OnName2> Touch;
bool IsTouch()const 
{
 return (mState&Touch.IntValue) == Touch.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ApplicationDebugInfoFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ApplicationDebugInfoFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ApplicationDebugInfoFlags::Names[Size]=
{
"Performance","GPU","Touch"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int ApplicationDebugInfoFlags::Values[Size]=
{
1,2,4
};
MEDUSA_WEAK_MULTIPLE_DEFINE const ApplicationDebugInfoFlags::ApplicationDebugInfoFlagsField<0,ApplicationDebugInfoFlags::OnNameNone> ApplicationDebugInfoFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const ApplicationDebugInfoFlags::ApplicationDebugInfoFlagsField<1|2|4,ApplicationDebugInfoFlags::OnNameAll> ApplicationDebugInfoFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ApplicationDebugInfoFlags::ApplicationDebugInfoFlagsField<1,ApplicationDebugInfoFlags::OnName0> ApplicationDebugInfoFlags::Performance;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ApplicationDebugInfoFlags::ApplicationDebugInfoFlagsField<2,ApplicationDebugInfoFlags::OnName1> ApplicationDebugInfoFlags::GPU;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ApplicationDebugInfoFlags::ApplicationDebugInfoFlagsField<4,ApplicationDebugInfoFlags::OnName2> ApplicationDebugInfoFlags::Touch;
MEDUSA_END;
