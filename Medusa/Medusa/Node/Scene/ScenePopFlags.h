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
//STRONG_FLAGS_6(ScenePopFlags,ShowCurrentScene, SuppressUpdateLogic, DisableTouch, IgnorePrevScene, DeleteCurrentScene, DeleteCurrentSceneAsync);
class ScenePopFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class ScenePopFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class ScenePopFlags;
public:
 ScenePopFlagsField()
{
}
 bool operator==( ScenePopFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( ScenePopFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( ScenePopFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( ScenePopFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( ScenePopFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( ScenePopFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 ScenePopFlags operator|( ScenePopFlags rhs ) const
{
return ScenePopFlags( TValue | rhs.mState );
}
 ScenePopFlags operator&( ScenePopFlags rhs ) const
{
return ScenePopFlags( TValue & rhs.mState );
}
 ScenePopFlags operator^( ScenePopFlags rhs ) const
{
return ScenePopFlags( TValue ^ rhs.mState );
}
 ScenePopFlags operator~() const
{
return ScenePopFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 ScenePopFlags operator|( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return ScenePopFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ScenePopFlags operator&( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return ScenePopFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ScenePopFlags operator^( ScenePopFlagsField<TValue2,TName2> rhs ) const
{
return ScenePopFlags(TValue ^ TValue2);
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
 ScenePopFlags( const ScenePopFlags& rhs ) : mState( rhs.mState ) 
{
}
 ScenePopFlags operator=( ScenePopFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags(ScenePopFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator=( ScenePopFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( ScenePopFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( ScenePopFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( ScenePopFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( ScenePopFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( ScenePopFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( ScenePopFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( ScenePopFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( ScenePopFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( ScenePopFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( ScenePopFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( ScenePopFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( ScenePopFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 ScenePopFlags operator|( ScenePopFlags rhs ) const
{
return ScenePopFlags( mState | rhs.mState );
}
 ScenePopFlags operator&( ScenePopFlags rhs ) const
{
return ScenePopFlags( mState & rhs.mState );
}
 ScenePopFlags operator^( ScenePopFlags rhs ) const
{
return ScenePopFlags( mState ^ rhs.mState );
}
 ScenePopFlags operator~() const
{
return ScenePopFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator|( ScenePopFlagsField<TValue,TName> rhs ) const
{
return ScenePopFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator&( ScenePopFlagsField<TValue,TName> rhs ) const
{
return ScenePopFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator^( ScenePopFlagsField<TValue,TName> rhs ) const
{
return ScenePopFlags( mState ^ TValue );
}
 ScenePopFlags& operator|=( ScenePopFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 ScenePopFlags& operator&=( ScenePopFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 ScenePopFlags& operator^=( ScenePopFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator|=( ScenePopFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return ScenePopFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator&=( ScenePopFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return ScenePopFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 ScenePopFlags operator^=( ScenePopFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return ScenePopFlags( *this );
}
 ScenePopFlags operator<<( unsigned int s )
{
return ScenePopFlags( mState << s );
}
 ScenePopFlags operator>>( unsigned int s )
{
return ScenePopFlags( mState >> s );
}
 ScenePopFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 ScenePopFlags& operator>>=( unsigned int s )
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
 bool Has(ScenePopFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(ScenePopFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(ScenePopFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(ScenePopFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(ScenePopFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(ScenePopFlags rhs,bool isSet)
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
 bool Has(ScenePopFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(ScenePopFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(ScenePopFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(ScenePopFlagsField<TValue,TName> field,bool isSet)
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
explicit ScenePopFlags(int state=0):mState(state)
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
static ScenePopFlags Parse(int val)
{
if(IsDefined(val))
{
return ScenePopFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return ScenePopFlags(val);
}
static bool TryParse(int val,ScenePopFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static ScenePopFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
ScenePopFlags result;
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
static bool TryParse(ScenePopFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=6;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const ScenePopFlagsField<0,ScenePopFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const ScenePopFlagsField<1|2|4|8|16|32,ScenePopFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const ScenePopFlagsField<1,ScenePopFlags::OnName0> ShowCurrentScene;
bool IsShowCurrentScene()const 
{
 return (mState&ShowCurrentScene.IntValue) == ShowCurrentScene.IntValue;
 
}
static const ScenePopFlagsField<2,ScenePopFlags::OnName1> SuppressUpdateLogic;
bool IsSuppressUpdateLogic()const 
{
 return (mState&SuppressUpdateLogic.IntValue) == SuppressUpdateLogic.IntValue;
 
}
static const ScenePopFlagsField<4,ScenePopFlags::OnName2> DisableTouch;
bool IsDisableTouch()const 
{
 return (mState&DisableTouch.IntValue) == DisableTouch.IntValue;
 
}
static const ScenePopFlagsField<8,ScenePopFlags::OnName3> IgnorePrevScene;
bool IsIgnorePrevScene()const 
{
 return (mState&IgnorePrevScene.IntValue) == IgnorePrevScene.IntValue;
 
}
static const ScenePopFlagsField<16,ScenePopFlags::OnName4> DeleteCurrentScene;
bool IsDeleteCurrentScene()const 
{
 return (mState&DeleteCurrentScene.IntValue) == DeleteCurrentScene.IntValue;
 
}
static const ScenePopFlagsField<32,ScenePopFlags::OnName5> DeleteCurrentSceneAsync;
bool IsDeleteCurrentSceneAsync()const 
{
 return (mState&DeleteCurrentSceneAsync.IntValue) == DeleteCurrentSceneAsync.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ScenePopFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ScenePopFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ScenePopFlags::Names[Size]=
{
"ShowCurrentScene","SuppressUpdateLogic","DisableTouch","IgnorePrevScene","DeleteCurrentScene","DeleteCurrentSceneAsync"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int ScenePopFlags::Values[Size]=
{
1,2,4,8,16,32
};
MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<0,ScenePopFlags::OnNameNone> ScenePopFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<1|2|4|8|16|32,ScenePopFlags::OnNameAll> ScenePopFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<1,ScenePopFlags::OnName0> ScenePopFlags::ShowCurrentScene;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<2,ScenePopFlags::OnName1> ScenePopFlags::SuppressUpdateLogic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<4,ScenePopFlags::OnName2> ScenePopFlags::DisableTouch;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<8,ScenePopFlags::OnName3> ScenePopFlags::IgnorePrevScene;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<16,ScenePopFlags::OnName4> ScenePopFlags::DeleteCurrentScene;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ScenePopFlags::ScenePopFlagsField<32,ScenePopFlags::OnName5> ScenePopFlags::DeleteCurrentSceneAsync;
MEDUSA_END;
