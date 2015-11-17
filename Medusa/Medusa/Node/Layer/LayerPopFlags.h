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
//STRONG_FLAGS_7(LayerPopFlags,ShowCurrentLayer,SuppressUpdateLogic,DisableTouch,IgnorePrevLayer,DeleteCurrentLayer,DeleteCurrentLayerAsync,RestoreStatusAfterPop);
class LayerPopFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class LayerPopFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class LayerPopFlags;
public:
 LayerPopFlagsField()
{
}
 bool operator==( LayerPopFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( LayerPopFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( LayerPopFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( LayerPopFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( LayerPopFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( LayerPopFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 LayerPopFlags operator|( LayerPopFlags rhs ) const
{
return LayerPopFlags( TValue | rhs.mState );
}
 LayerPopFlags operator&( LayerPopFlags rhs ) const
{
return LayerPopFlags( TValue & rhs.mState );
}
 LayerPopFlags operator^( LayerPopFlags rhs ) const
{
return LayerPopFlags( TValue ^ rhs.mState );
}
 LayerPopFlags operator~() const
{
return LayerPopFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 LayerPopFlags operator|( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return LayerPopFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 LayerPopFlags operator&( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return LayerPopFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 LayerPopFlags operator^( LayerPopFlagsField<TValue2,TName2> rhs ) const
{
return LayerPopFlags(TValue ^ TValue2);
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
 LayerPopFlags( const LayerPopFlags& rhs ) : mState( rhs.mState ) 
{
}
 LayerPopFlags operator=( LayerPopFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags(LayerPopFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator=( LayerPopFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( LayerPopFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( LayerPopFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( LayerPopFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( LayerPopFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( LayerPopFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( LayerPopFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( LayerPopFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( LayerPopFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( LayerPopFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( LayerPopFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( LayerPopFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( LayerPopFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 LayerPopFlags operator|( LayerPopFlags rhs ) const
{
return LayerPopFlags( mState | rhs.mState );
}
 LayerPopFlags operator&( LayerPopFlags rhs ) const
{
return LayerPopFlags( mState & rhs.mState );
}
 LayerPopFlags operator^( LayerPopFlags rhs ) const
{
return LayerPopFlags( mState ^ rhs.mState );
}
 LayerPopFlags operator~() const
{
return LayerPopFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator|( LayerPopFlagsField<TValue,TName> rhs ) const
{
return LayerPopFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator&( LayerPopFlagsField<TValue,TName> rhs ) const
{
return LayerPopFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator^( LayerPopFlagsField<TValue,TName> rhs ) const
{
return LayerPopFlags( mState ^ TValue );
}
 LayerPopFlags& operator|=( LayerPopFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 LayerPopFlags& operator&=( LayerPopFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 LayerPopFlags& operator^=( LayerPopFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator|=( LayerPopFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return LayerPopFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator&=( LayerPopFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return LayerPopFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 LayerPopFlags operator^=( LayerPopFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return LayerPopFlags( *this );
}
 LayerPopFlags operator<<( unsigned int s )
{
return LayerPopFlags( mState << s );
}
 LayerPopFlags operator>>( unsigned int s )
{
return LayerPopFlags( mState >> s );
}
 LayerPopFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 LayerPopFlags& operator>>=( unsigned int s )
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
 bool Has(LayerPopFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(LayerPopFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(LayerPopFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(LayerPopFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(LayerPopFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(LayerPopFlags rhs,bool isSet)
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
 bool Has(LayerPopFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(LayerPopFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(LayerPopFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(LayerPopFlagsField<TValue,TName> field,bool isSet)
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
explicit LayerPopFlags(int state=0):mState(state)
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
static LayerPopFlags Parse(int val)
{
if(IsDefined(val))
{
return LayerPopFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return LayerPopFlags(val);
}
static bool TryParse(int val,LayerPopFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static LayerPopFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
LayerPopFlags result;
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
static bool TryParse(LayerPopFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const LayerPopFlagsField<0,LayerPopFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const LayerPopFlagsField<1|2|4|8|16|32|64,LayerPopFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const LayerPopFlagsField<1,LayerPopFlags::OnName0> ShowCurrentLayer;
bool IsShowCurrentLayer()const 
{
 return (mState&ShowCurrentLayer.IntValue) == ShowCurrentLayer.IntValue;
 
}
static const LayerPopFlagsField<2,LayerPopFlags::OnName1> SuppressUpdateLogic;
bool IsSuppressUpdateLogic()const 
{
 return (mState&SuppressUpdateLogic.IntValue) == SuppressUpdateLogic.IntValue;
 
}
static const LayerPopFlagsField<4,LayerPopFlags::OnName2> DisableTouch;
bool IsDisableTouch()const 
{
 return (mState&DisableTouch.IntValue) == DisableTouch.IntValue;
 
}
static const LayerPopFlagsField<8,LayerPopFlags::OnName3> IgnorePrevLayer;
bool IsIgnorePrevLayer()const 
{
 return (mState&IgnorePrevLayer.IntValue) == IgnorePrevLayer.IntValue;
 
}
static const LayerPopFlagsField<16,LayerPopFlags::OnName4> DeleteCurrentLayer;
bool IsDeleteCurrentLayer()const 
{
 return (mState&DeleteCurrentLayer.IntValue) == DeleteCurrentLayer.IntValue;
 
}
static const LayerPopFlagsField<32,LayerPopFlags::OnName5> DeleteCurrentLayerAsync;
bool IsDeleteCurrentLayerAsync()const 
{
 return (mState&DeleteCurrentLayerAsync.IntValue) == DeleteCurrentLayerAsync.IntValue;
 
}
static const LayerPopFlagsField<64,LayerPopFlags::OnName6> RestoreStatusAfterPop;
bool IsRestoreStatusAfterPop()const 
{
 return (mState&RestoreStatusAfterPop.IntValue) == RestoreStatusAfterPop.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerPopFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerPopFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef LayerPopFlags::Names[Size]=
{
"ShowCurrentLayer","SuppressUpdateLogic","DisableTouch","IgnorePrevLayer","DeleteCurrentLayer","DeleteCurrentLayerAsync","RestoreStatusAfterPop"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int LayerPopFlags::Values[Size]=
{
1,2,4,8,16,32,64
};
MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<0,LayerPopFlags::OnNameNone> LayerPopFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<1|2|4|8|16|32|64,LayerPopFlags::OnNameAll> LayerPopFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<1,LayerPopFlags::OnName0> LayerPopFlags::ShowCurrentLayer;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<2,LayerPopFlags::OnName1> LayerPopFlags::SuppressUpdateLogic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<4,LayerPopFlags::OnName2> LayerPopFlags::DisableTouch;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<8,LayerPopFlags::OnName3> LayerPopFlags::IgnorePrevLayer;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<16,LayerPopFlags::OnName4> LayerPopFlags::DeleteCurrentLayer;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<32,LayerPopFlags::OnName5> LayerPopFlags::DeleteCurrentLayerAsync;
 MEDUSA_WEAK_MULTIPLE_DEFINE const LayerPopFlags::LayerPopFlagsField<64,LayerPopFlags::OnName6> LayerPopFlags::RestoreStatusAfterPop;
MEDUSA_END;
