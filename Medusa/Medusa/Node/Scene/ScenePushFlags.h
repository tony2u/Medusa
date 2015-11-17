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
//STRONG_FLAGS_4(ScenePushFlags,ShowPrevScene,SuppressUpdateLogic,DisableTouch,HideAllPrevScenes);
class ScenePushFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class ScenePushFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class ScenePushFlags;
public:
 ScenePushFlagsField()
{
}
 bool operator==( ScenePushFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( ScenePushFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( ScenePushFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( ScenePushFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( ScenePushFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( ScenePushFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 ScenePushFlags operator|( ScenePushFlags rhs ) const
{
return ScenePushFlags( TValue | rhs.mState );
}
 ScenePushFlags operator&( ScenePushFlags rhs ) const
{
return ScenePushFlags( TValue & rhs.mState );
}
 ScenePushFlags operator^( ScenePushFlags rhs ) const
{
return ScenePushFlags( TValue ^ rhs.mState );
}
 ScenePushFlags operator~() const
{
return ScenePushFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 ScenePushFlags operator|( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return ScenePushFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ScenePushFlags operator&( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return ScenePushFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ScenePushFlags operator^( ScenePushFlagsField<TValue2,TName2> rhs ) const
{
return ScenePushFlags(TValue ^ TValue2);
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
 ScenePushFlags( const ScenePushFlags& rhs ) : mState( rhs.mState ) 
{
}
 ScenePushFlags operator=( ScenePushFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags(ScenePushFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator=( ScenePushFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( ScenePushFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( ScenePushFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( ScenePushFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( ScenePushFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( ScenePushFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( ScenePushFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( ScenePushFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( ScenePushFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( ScenePushFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( ScenePushFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( ScenePushFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( ScenePushFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 ScenePushFlags operator|( ScenePushFlags rhs ) const
{
return ScenePushFlags( mState | rhs.mState );
}
 ScenePushFlags operator&( ScenePushFlags rhs ) const
{
return ScenePushFlags( mState & rhs.mState );
}
 ScenePushFlags operator^( ScenePushFlags rhs ) const
{
return ScenePushFlags( mState ^ rhs.mState );
}
 ScenePushFlags operator~() const
{
return ScenePushFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator|( ScenePushFlagsField<TValue,TName> rhs ) const
{
return ScenePushFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator&( ScenePushFlagsField<TValue,TName> rhs ) const
{
return ScenePushFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator^( ScenePushFlagsField<TValue,TName> rhs ) const
{
return ScenePushFlags( mState ^ TValue );
}
 ScenePushFlags& operator|=( ScenePushFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 ScenePushFlags& operator&=( ScenePushFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 ScenePushFlags& operator^=( ScenePushFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator|=( ScenePushFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return ScenePushFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator&=( ScenePushFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return ScenePushFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 ScenePushFlags operator^=( ScenePushFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return ScenePushFlags( *this );
}
 ScenePushFlags operator<<( unsigned int s )
{
return ScenePushFlags( mState << s );
}
 ScenePushFlags operator>>( unsigned int s )
{
return ScenePushFlags( mState >> s );
}
 ScenePushFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 ScenePushFlags& operator>>=( unsigned int s )
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
 bool Has(ScenePushFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(ScenePushFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(ScenePushFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(ScenePushFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(ScenePushFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(ScenePushFlags rhs,bool isSet)
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
 bool Has(ScenePushFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(ScenePushFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(ScenePushFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(ScenePushFlagsField<TValue,TName> field,bool isSet)
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
explicit ScenePushFlags(int state=0):mState(state)
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
static ScenePushFlags Parse(int val)
{
if(IsDefined(val))
{
return ScenePushFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return ScenePushFlags(val);
}
static bool TryParse(int val,ScenePushFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static ScenePushFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
ScenePushFlags result;
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
static bool TryParse(ScenePushFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const ScenePushFlagsField<0,ScenePushFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const ScenePushFlagsField<1|2|4|8,ScenePushFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const ScenePushFlagsField<1,ScenePushFlags::OnName0> ShowPrevScene;
bool IsShowPrevScene()const 
{
 return (mState&ShowPrevScene.IntValue) == ShowPrevScene.IntValue;
 
}
static const ScenePushFlagsField<2,ScenePushFlags::OnName1> SuppressUpdateLogic;
bool IsSuppressUpdateLogic()const 
{
 return (mState&SuppressUpdateLogic.IntValue) == SuppressUpdateLogic.IntValue;
 
}
static const ScenePushFlagsField<4,ScenePushFlags::OnName2> DisableTouch;
bool IsDisableTouch()const 
{
 return (mState&DisableTouch.IntValue) == DisableTouch.IntValue;
 
}
static const ScenePushFlagsField<8,ScenePushFlags::OnName3> HideAllPrevScenes;
bool IsHideAllPrevScenes()const 
{
 return (mState&HideAllPrevScenes.IntValue) == HideAllPrevScenes.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ScenePushFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ScenePushFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ScenePushFlags::Names[Size]=
{
"ShowPrevScene","SuppressUpdateLogic","DisableTouch","HideAllPrevScenes"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int ScenePushFlags::Values[Size]=
{
1,2,4,8
};
MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePushFlags::ScenePushFlagsField<0,ScenePushFlags::OnNameNone> ScenePushFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePushFlags::ScenePushFlagsField<1|2|4|8,ScenePushFlags::OnNameAll> ScenePushFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePushFlags::ScenePushFlagsField<1,ScenePushFlags::OnName0> ScenePushFlags::ShowPrevScene;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePushFlags::ScenePushFlagsField<2,ScenePushFlags::OnName1> ScenePushFlags::SuppressUpdateLogic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePushFlags::ScenePushFlagsField<4,ScenePushFlags::OnName2> ScenePushFlags::DisableTouch;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePushFlags::ScenePushFlagsField<8,ScenePushFlags::OnName3> ScenePushFlags::HideAllPrevScenes;
MEDUSA_END;
