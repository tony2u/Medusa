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
//STRONG_FLAGS_8(RenderableChangedFlags, RenderQueueChanged,BatchChanged,DataTotalChanged, NewVertex, NewNormal, NewTexCoord, NewColor, NewIndex);
class RenderableChangedFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class RenderableChangedFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class RenderableChangedFlags;
public:
 RenderableChangedFlagsField()
{
}
 bool operator==( RenderableChangedFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( RenderableChangedFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( RenderableChangedFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( RenderableChangedFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( RenderableChangedFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( RenderableChangedFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 RenderableChangedFlags operator|( RenderableChangedFlags rhs ) const
{
return RenderableChangedFlags( TValue | rhs.mState );
}
 RenderableChangedFlags operator&( RenderableChangedFlags rhs ) const
{
return RenderableChangedFlags( TValue & rhs.mState );
}
 RenderableChangedFlags operator^( RenderableChangedFlags rhs ) const
{
return RenderableChangedFlags( TValue ^ rhs.mState );
}
 RenderableChangedFlags operator~() const
{
return RenderableChangedFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 RenderableChangedFlags operator|( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return RenderableChangedFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 RenderableChangedFlags operator&( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return RenderableChangedFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 RenderableChangedFlags operator^( RenderableChangedFlagsField<TValue2,TName2> rhs ) const
{
return RenderableChangedFlags(TValue ^ TValue2);
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
 RenderableChangedFlags( const RenderableChangedFlags& rhs ) : mState( rhs.mState ) 
{
}
 RenderableChangedFlags operator=( RenderableChangedFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags(RenderableChangedFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator=( RenderableChangedFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( RenderableChangedFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( RenderableChangedFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( RenderableChangedFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( RenderableChangedFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( RenderableChangedFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( RenderableChangedFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 RenderableChangedFlags operator|( RenderableChangedFlags rhs ) const
{
return RenderableChangedFlags( mState | rhs.mState );
}
 RenderableChangedFlags operator&( RenderableChangedFlags rhs ) const
{
return RenderableChangedFlags( mState & rhs.mState );
}
 RenderableChangedFlags operator^( RenderableChangedFlags rhs ) const
{
return RenderableChangedFlags( mState ^ rhs.mState );
}
 RenderableChangedFlags operator~() const
{
return RenderableChangedFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator|( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return RenderableChangedFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator&( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return RenderableChangedFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator^( RenderableChangedFlagsField<TValue,TName> rhs ) const
{
return RenderableChangedFlags( mState ^ TValue );
}
 RenderableChangedFlags& operator|=( RenderableChangedFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 RenderableChangedFlags& operator&=( RenderableChangedFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 RenderableChangedFlags& operator^=( RenderableChangedFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator|=( RenderableChangedFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return RenderableChangedFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator&=( RenderableChangedFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return RenderableChangedFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 RenderableChangedFlags operator^=( RenderableChangedFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return RenderableChangedFlags( *this );
}
 RenderableChangedFlags operator<<( unsigned int s )
{
return RenderableChangedFlags( mState << s );
}
 RenderableChangedFlags operator>>( unsigned int s )
{
return RenderableChangedFlags( mState >> s );
}
 RenderableChangedFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 RenderableChangedFlags& operator>>=( unsigned int s )
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
 bool Has(RenderableChangedFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(RenderableChangedFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(RenderableChangedFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(RenderableChangedFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(RenderableChangedFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(RenderableChangedFlags rhs,bool isSet)
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
 bool Has(RenderableChangedFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(RenderableChangedFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(RenderableChangedFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(RenderableChangedFlagsField<TValue,TName> field,bool isSet)
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
explicit RenderableChangedFlags(int state=0):mState(state)
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
static const StringRef& OnName7()
{
return Names[7];
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
static RenderableChangedFlags Parse(int val)
{
if(IsDefined(val))
{
return RenderableChangedFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return RenderableChangedFlags(val);
}
static bool TryParse(int val,RenderableChangedFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static RenderableChangedFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
RenderableChangedFlags result;
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
static bool TryParse(RenderableChangedFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=8;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const RenderableChangedFlagsField<0,RenderableChangedFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const RenderableChangedFlagsField<1|2|4|8|16|32|64|128,RenderableChangedFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const RenderableChangedFlagsField<1,RenderableChangedFlags::OnName0> RenderQueueChanged;
bool IsRenderQueueChanged()const 
{
 return (mState&RenderQueueChanged.IntValue) == RenderQueueChanged.IntValue;
 
}
static const RenderableChangedFlagsField<2,RenderableChangedFlags::OnName1> BatchChanged;
bool IsBatchChanged()const 
{
 return (mState&BatchChanged.IntValue) == BatchChanged.IntValue;
 
}
static const RenderableChangedFlagsField<4,RenderableChangedFlags::OnName2> DataTotalChanged;
bool IsDataTotalChanged()const 
{
 return (mState&DataTotalChanged.IntValue) == DataTotalChanged.IntValue;
 
}
static const RenderableChangedFlagsField<8,RenderableChangedFlags::OnName3> NewVertex;
bool IsNewVertex()const 
{
 return (mState&NewVertex.IntValue) == NewVertex.IntValue;
 
}
static const RenderableChangedFlagsField<16,RenderableChangedFlags::OnName4> NewNormal;
bool IsNewNormal()const 
{
 return (mState&NewNormal.IntValue) == NewNormal.IntValue;
 
}
static const RenderableChangedFlagsField<32,RenderableChangedFlags::OnName5> NewTexCoord;
bool IsNewTexCoord()const 
{
 return (mState&NewTexCoord.IntValue) == NewTexCoord.IntValue;
 
}
static const RenderableChangedFlagsField<64,RenderableChangedFlags::OnName6> NewColor;
bool IsNewColor()const 
{
 return (mState&NewColor.IntValue) == NewColor.IntValue;
 
}
static const RenderableChangedFlagsField<128,RenderableChangedFlags::OnName7> NewIndex;
bool IsNewIndex()const 
{
 return (mState&NewIndex.IntValue) == NewIndex.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef RenderableChangedFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef RenderableChangedFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef RenderableChangedFlags::Names[Size]=
{
"RenderQueueChanged","BatchChanged","DataTotalChanged","NewVertex","NewNormal","NewTexCoord","NewColor","NewIndex"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int RenderableChangedFlags::Values[Size]=
{
1,2,4,8,16,32,64,128
};
MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<0,RenderableChangedFlags::OnNameNone> RenderableChangedFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<1|2|4|8|16|32|64|128,RenderableChangedFlags::OnNameAll> RenderableChangedFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<1,RenderableChangedFlags::OnName0> RenderableChangedFlags::RenderQueueChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<2,RenderableChangedFlags::OnName1> RenderableChangedFlags::BatchChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<4,RenderableChangedFlags::OnName2> RenderableChangedFlags::DataTotalChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<8,RenderableChangedFlags::OnName3> RenderableChangedFlags::NewVertex;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<16,RenderableChangedFlags::OnName4> RenderableChangedFlags::NewNormal;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<32,RenderableChangedFlags::OnName5> RenderableChangedFlags::NewTexCoord;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<64,RenderableChangedFlags::OnName6> RenderableChangedFlags::NewColor;
 MEDUSA_WEAK_MULTIPLE_DEFINE const RenderableChangedFlags::RenderableChangedFlagsField<128,RenderableChangedFlags::OnName7> RenderableChangedFlags::NewIndex;
MEDUSA_END;
