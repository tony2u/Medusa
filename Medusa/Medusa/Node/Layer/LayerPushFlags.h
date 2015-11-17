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
//STRONG_FLAGS_6(LayerPushFlags,ShowPrevLayer,SuppressUpdateLogic,AlwaysCreate,DisableTouch,HideAllPrevLayers,SaveStatusBeforePush);
class LayerPushFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class LayerPushFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class LayerPushFlags;
public:
 LayerPushFlagsField()
{
}
 bool operator==( LayerPushFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( LayerPushFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( LayerPushFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( LayerPushFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( LayerPushFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( LayerPushFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 LayerPushFlags operator|( LayerPushFlags rhs ) const
{
return LayerPushFlags( TValue | rhs.mState );
}
 LayerPushFlags operator&( LayerPushFlags rhs ) const
{
return LayerPushFlags( TValue & rhs.mState );
}
 LayerPushFlags operator^( LayerPushFlags rhs ) const
{
return LayerPushFlags( TValue ^ rhs.mState );
}
 LayerPushFlags operator~() const
{
return LayerPushFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 LayerPushFlags operator|( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return LayerPushFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 LayerPushFlags operator&( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return LayerPushFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 LayerPushFlags operator^( LayerPushFlagsField<TValue2,TName2> rhs ) const
{
return LayerPushFlags(TValue ^ TValue2);
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
 LayerPushFlags( const LayerPushFlags& rhs ) : mState( rhs.mState ) 
{
}
 LayerPushFlags operator=( LayerPushFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags(LayerPushFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator=( LayerPushFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( LayerPushFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( LayerPushFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( LayerPushFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( LayerPushFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( LayerPushFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( LayerPushFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( LayerPushFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( LayerPushFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( LayerPushFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( LayerPushFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( LayerPushFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( LayerPushFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 LayerPushFlags operator|( LayerPushFlags rhs ) const
{
return LayerPushFlags( mState | rhs.mState );
}
 LayerPushFlags operator&( LayerPushFlags rhs ) const
{
return LayerPushFlags( mState & rhs.mState );
}
 LayerPushFlags operator^( LayerPushFlags rhs ) const
{
return LayerPushFlags( mState ^ rhs.mState );
}
 LayerPushFlags operator~() const
{
return LayerPushFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator|( LayerPushFlagsField<TValue,TName> rhs ) const
{
return LayerPushFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator&( LayerPushFlagsField<TValue,TName> rhs ) const
{
return LayerPushFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator^( LayerPushFlagsField<TValue,TName> rhs ) const
{
return LayerPushFlags( mState ^ TValue );
}
 LayerPushFlags& operator|=( LayerPushFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 LayerPushFlags& operator&=( LayerPushFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 LayerPushFlags& operator^=( LayerPushFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator|=( LayerPushFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return LayerPushFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator&=( LayerPushFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return LayerPushFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 LayerPushFlags operator^=( LayerPushFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return LayerPushFlags( *this );
}
 LayerPushFlags operator<<( unsigned int s )
{
return LayerPushFlags( mState << s );
}
 LayerPushFlags operator>>( unsigned int s )
{
return LayerPushFlags( mState >> s );
}
 LayerPushFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 LayerPushFlags& operator>>=( unsigned int s )
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
 bool Has(LayerPushFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(LayerPushFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(LayerPushFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(LayerPushFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(LayerPushFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(LayerPushFlags rhs,bool isSet)
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
 bool Has(LayerPushFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(LayerPushFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(LayerPushFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(LayerPushFlagsField<TValue,TName> field,bool isSet)
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
explicit LayerPushFlags(int state=0):mState(state)
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
static LayerPushFlags Parse(int val)
{
if(IsDefined(val))
{
return LayerPushFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return LayerPushFlags(val);
}
static bool TryParse(int val,LayerPushFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static LayerPushFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
LayerPushFlags result;
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
static bool TryParse(LayerPushFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const LayerPushFlagsField<0,LayerPushFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const LayerPushFlagsField<1|2|4|8|16|32,LayerPushFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const LayerPushFlagsField<1,LayerPushFlags::OnName0> ShowPrevLayer;
bool IsShowPrevLayer()const 
{
 return (mState&ShowPrevLayer.IntValue) == ShowPrevLayer.IntValue;
 
}
static const LayerPushFlagsField<2,LayerPushFlags::OnName1> SuppressUpdateLogic;
bool IsSuppressUpdateLogic()const 
{
 return (mState&SuppressUpdateLogic.IntValue) == SuppressUpdateLogic.IntValue;
 
}
static const LayerPushFlagsField<4,LayerPushFlags::OnName2> AlwaysCreate;
bool IsAlwaysCreate()const 
{
 return (mState&AlwaysCreate.IntValue) == AlwaysCreate.IntValue;
 
}
static const LayerPushFlagsField<8,LayerPushFlags::OnName3> DisableTouch;
bool IsDisableTouch()const 
{
 return (mState&DisableTouch.IntValue) == DisableTouch.IntValue;
 
}
static const LayerPushFlagsField<16,LayerPushFlags::OnName4> HideAllPrevLayers;
bool IsHideAllPrevLayers()const 
{
 return (mState&HideAllPrevLayers.IntValue) == HideAllPrevLayers.IntValue;
 
}
static const LayerPushFlagsField<32,LayerPushFlags::OnName5> SaveStatusBeforePush;
bool IsSaveStatusBeforePush()const 
{
 return (mState&SaveStatusBeforePush.IntValue) == SaveStatusBeforePush.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerPushFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerPushFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerPushFlags::Names[Size]=
{
"ShowPrevLayer","SuppressUpdateLogic","AlwaysCreate","DisableTouch","HideAllPrevLayers","SaveStatusBeforePush"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int LayerPushFlags::Values[Size]=
{
1,2,4,8,16,32
};
MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<0,LayerPushFlags::OnNameNone> LayerPushFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<1|2|4|8|16|32,LayerPushFlags::OnNameAll> LayerPushFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<1,LayerPushFlags::OnName0> LayerPushFlags::ShowPrevLayer;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<2,LayerPushFlags::OnName1> LayerPushFlags::SuppressUpdateLogic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<4,LayerPushFlags::OnName2> LayerPushFlags::AlwaysCreate;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<8,LayerPushFlags::OnName3> LayerPushFlags::DisableTouch;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<16,LayerPushFlags::OnName4> LayerPushFlags::HideAllPrevLayers;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPushFlags::LayerPushFlagsField<32,LayerPushFlags::OnName5> LayerPushFlags::SaveStatusBeforePush;
MEDUSA_END;
