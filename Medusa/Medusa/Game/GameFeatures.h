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
//STRONG_FLAGS_5(GameFeatures, SupportThreadEvent, SupportMessage,SupportScript, SupportFileUpdating,SupportSceneEditor);
class GameFeatures	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class GameFeaturesField	//[IGNORE_PRE_DECLARE]
{
friend class GameFeatures;
public:
 GameFeaturesField()
{
}
 bool operator==( GameFeatures rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GameFeatures rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GameFeatures rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GameFeatures rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GameFeatures rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GameFeatures rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( GameFeaturesField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( GameFeaturesField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( GameFeaturesField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( GameFeaturesField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( GameFeaturesField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( GameFeaturesField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 GameFeatures operator|( GameFeatures rhs ) const
{
return GameFeatures( TValue | rhs.mState );
}
 GameFeatures operator&( GameFeatures rhs ) const
{
return GameFeatures( TValue & rhs.mState );
}
 GameFeatures operator^( GameFeatures rhs ) const
{
return GameFeatures( TValue ^ rhs.mState );
}
 GameFeatures operator~() const
{
return GameFeatures(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 GameFeatures operator|( GameFeaturesField<TValue2,TName2> rhs ) const
{
return GameFeatures(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GameFeatures operator&( GameFeaturesField<TValue2,TName2> rhs ) const
{
return GameFeatures(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GameFeatures operator^( GameFeaturesField<TValue2,TName2> rhs ) const
{
return GameFeatures(TValue ^ TValue2);
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
 GameFeatures( const GameFeatures& rhs ) : mState( rhs.mState ) 
{
}
 GameFeatures operator=( GameFeatures rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GameFeatures(GameFeaturesField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator=( GameFeaturesField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( GameFeatures rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GameFeatures rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GameFeatures rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GameFeatures rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GameFeatures rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GameFeatures rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( GameFeaturesField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( GameFeaturesField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( GameFeaturesField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( GameFeaturesField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( GameFeaturesField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( GameFeaturesField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 GameFeatures operator|( GameFeatures rhs ) const
{
return GameFeatures( mState | rhs.mState );
}
 GameFeatures operator&( GameFeatures rhs ) const
{
return GameFeatures( mState & rhs.mState );
}
 GameFeatures operator^( GameFeatures rhs ) const
{
return GameFeatures( mState ^ rhs.mState );
}
 GameFeatures operator~() const
{
return GameFeatures( ~mState );
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator|( GameFeaturesField<TValue,TName> rhs ) const
{
return GameFeatures( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator&( GameFeaturesField<TValue,TName> rhs ) const
{
return GameFeatures( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator^( GameFeaturesField<TValue,TName> rhs ) const
{
return GameFeatures( mState ^ TValue );
}
 GameFeatures& operator|=( GameFeatures rhs )
{
mState |= rhs.mState;
return *this;
}
 GameFeatures& operator&=( GameFeatures rhs )
{
mState &= rhs.mState;
return *this;
}
 GameFeatures& operator^=( GameFeatures rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator|=( GameFeaturesField<TValue,TName> rhs )
{
mState |= TValue;
return GameFeatures( *this );
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator&=( GameFeaturesField<TValue,TName> rhs )
{
mState &= TValue;
return GameFeatures( *this );
}
 template<int TValue,const StringRef& TName()>
 GameFeatures operator^=( GameFeaturesField<TValue,TName> rhs )
{
mState ^= TValue;
return GameFeatures( *this );
}
 GameFeatures operator<<( unsigned int s )
{
return GameFeatures( mState << s );
}
 GameFeatures operator>>( unsigned int s )
{
return GameFeatures( mState >> s );
}
 GameFeatures& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 GameFeatures& operator>>=( unsigned int s )
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
 bool Has(GameFeatures rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(GameFeatures rhs)
{
mState|=rhs.ToInt();
}
 void Remove(GameFeatures rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(GameFeatures rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(GameFeatures rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(GameFeatures rhs,bool isSet)
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
 bool Has(GameFeaturesField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(GameFeaturesField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(GameFeaturesField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(GameFeaturesField<TValue,TName> field,bool isSet)
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
explicit GameFeatures(int state=0):mState(state)
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
static GameFeatures Parse(int val)
{
if(IsDefined(val))
{
return GameFeatures(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return GameFeatures(val);
}
static bool TryParse(int val,GameFeatures& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static GameFeatures Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
GameFeatures result;
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
static bool TryParse(GameFeatures& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=5;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const GameFeaturesField<0,GameFeatures::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const GameFeaturesField<1|2|4|8|16,GameFeatures::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const GameFeaturesField<1,GameFeatures::OnName0> SupportThreadEvent;
bool IsSupportThreadEvent()const 
{
 return (mState&SupportThreadEvent.IntValue) == SupportThreadEvent.IntValue;
 
}
static const GameFeaturesField<2,GameFeatures::OnName1> SupportMessage;
bool IsSupportMessage()const 
{
 return (mState&SupportMessage.IntValue) == SupportMessage.IntValue;
 
}
static const GameFeaturesField<4,GameFeatures::OnName2> SupportScript;
bool IsSupportScript()const 
{
 return (mState&SupportScript.IntValue) == SupportScript.IntValue;
 
}
static const GameFeaturesField<8,GameFeatures::OnName3> SupportFileUpdating;
bool IsSupportFileUpdating()const 
{
 return (mState&SupportFileUpdating.IntValue) == SupportFileUpdating.IntValue;
 
}
static const GameFeaturesField<16,GameFeatures::OnName4> SupportSceneEditor;
bool IsSupportSceneEditor()const 
{
 return (mState&SupportSceneEditor.IntValue) == SupportSceneEditor.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GameFeatures::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GameFeatures::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GameFeatures::Names[Size]=
{
"SupportThreadEvent","SupportMessage","SupportScript","SupportFileUpdating","SupportSceneEditor"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GameFeatures::Values[Size]=
{
1,2,4,8,16
};
MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<0,GameFeatures::OnNameNone> GameFeatures::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<1|2|4|8|16,GameFeatures::OnNameAll> GameFeatures::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<1,GameFeatures::OnName0> GameFeatures::SupportThreadEvent;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<2,GameFeatures::OnName1> GameFeatures::SupportMessage;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<4,GameFeatures::OnName2> GameFeatures::SupportScript;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<8,GameFeatures::OnName3> GameFeatures::SupportFileUpdating;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GameFeatures::GameFeaturesField<16,GameFeatures::OnName4> GameFeatures::SupportSceneEditor;
MEDUSA_END;
