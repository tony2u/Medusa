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
//STRONG_FLAGS_8(NodeLayoutChangedFlags, SizeChanged, ChildAdded, ChildRemoved, ChildCleard, ChildOrderChanged,PositionChanged,ArrangeChanged,CollapseChanged);
class NodeLayoutChangedFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class NodeLayoutChangedFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class NodeLayoutChangedFlags;
public:
 NodeLayoutChangedFlagsField()
{
}
 bool operator==( NodeLayoutChangedFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( NodeLayoutChangedFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( NodeLayoutChangedFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( NodeLayoutChangedFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( NodeLayoutChangedFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( NodeLayoutChangedFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 NodeLayoutChangedFlags operator|( NodeLayoutChangedFlags rhs ) const
{
return NodeLayoutChangedFlags( TValue | rhs.mState );
}
 NodeLayoutChangedFlags operator&( NodeLayoutChangedFlags rhs ) const
{
return NodeLayoutChangedFlags( TValue & rhs.mState );
}
 NodeLayoutChangedFlags operator^( NodeLayoutChangedFlags rhs ) const
{
return NodeLayoutChangedFlags( TValue ^ rhs.mState );
}
 NodeLayoutChangedFlags operator~() const
{
return NodeLayoutChangedFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 NodeLayoutChangedFlags operator|( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return NodeLayoutChangedFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeLayoutChangedFlags operator&( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return NodeLayoutChangedFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeLayoutChangedFlags operator^( NodeLayoutChangedFlagsField<TValue2,TName2> rhs ) const
{
return NodeLayoutChangedFlags(TValue ^ TValue2);
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
 NodeLayoutChangedFlags( const NodeLayoutChangedFlags& rhs ) : mState( rhs.mState ) 
{
}
 NodeLayoutChangedFlags operator=( NodeLayoutChangedFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags(NodeLayoutChangedFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator=( NodeLayoutChangedFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( NodeLayoutChangedFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( NodeLayoutChangedFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( NodeLayoutChangedFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( NodeLayoutChangedFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( NodeLayoutChangedFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( NodeLayoutChangedFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 NodeLayoutChangedFlags operator|( NodeLayoutChangedFlags rhs ) const
{
return NodeLayoutChangedFlags( mState | rhs.mState );
}
 NodeLayoutChangedFlags operator&( NodeLayoutChangedFlags rhs ) const
{
return NodeLayoutChangedFlags( mState & rhs.mState );
}
 NodeLayoutChangedFlags operator^( NodeLayoutChangedFlags rhs ) const
{
return NodeLayoutChangedFlags( mState ^ rhs.mState );
}
 NodeLayoutChangedFlags operator~() const
{
return NodeLayoutChangedFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator|( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return NodeLayoutChangedFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator&( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return NodeLayoutChangedFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator^( NodeLayoutChangedFlagsField<TValue,TName> rhs ) const
{
return NodeLayoutChangedFlags( mState ^ TValue );
}
 NodeLayoutChangedFlags& operator|=( NodeLayoutChangedFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 NodeLayoutChangedFlags& operator&=( NodeLayoutChangedFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 NodeLayoutChangedFlags& operator^=( NodeLayoutChangedFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator|=( NodeLayoutChangedFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return NodeLayoutChangedFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator&=( NodeLayoutChangedFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return NodeLayoutChangedFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutChangedFlags operator^=( NodeLayoutChangedFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return NodeLayoutChangedFlags( *this );
}
 NodeLayoutChangedFlags operator<<( unsigned int s )
{
return NodeLayoutChangedFlags( mState << s );
}
 NodeLayoutChangedFlags operator>>( unsigned int s )
{
return NodeLayoutChangedFlags( mState >> s );
}
 NodeLayoutChangedFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 NodeLayoutChangedFlags& operator>>=( unsigned int s )
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
 bool Has(NodeLayoutChangedFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(NodeLayoutChangedFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(NodeLayoutChangedFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(NodeLayoutChangedFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(NodeLayoutChangedFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(NodeLayoutChangedFlags rhs,bool isSet)
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
 bool Has(NodeLayoutChangedFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(NodeLayoutChangedFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(NodeLayoutChangedFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(NodeLayoutChangedFlagsField<TValue,TName> field,bool isSet)
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
explicit NodeLayoutChangedFlags(int state=0):mState(state)
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
static NodeLayoutChangedFlags Parse(int val)
{
if(IsDefined(val))
{
return NodeLayoutChangedFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return NodeLayoutChangedFlags(val);
}
static bool TryParse(int val,NodeLayoutChangedFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static NodeLayoutChangedFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
NodeLayoutChangedFlags result;
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
static bool TryParse(NodeLayoutChangedFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const NodeLayoutChangedFlagsField<0,NodeLayoutChangedFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const NodeLayoutChangedFlagsField<1|2|4|8|16|32|64|128,NodeLayoutChangedFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const NodeLayoutChangedFlagsField<1,NodeLayoutChangedFlags::OnName0> SizeChanged;
bool IsSizeChanged()const 
{
 return (mState&SizeChanged.IntValue) == SizeChanged.IntValue;
 
}
static const NodeLayoutChangedFlagsField<2,NodeLayoutChangedFlags::OnName1> ChildAdded;
bool IsChildAdded()const 
{
 return (mState&ChildAdded.IntValue) == ChildAdded.IntValue;
 
}
static const NodeLayoutChangedFlagsField<4,NodeLayoutChangedFlags::OnName2> ChildRemoved;
bool IsChildRemoved()const 
{
 return (mState&ChildRemoved.IntValue) == ChildRemoved.IntValue;
 
}
static const NodeLayoutChangedFlagsField<8,NodeLayoutChangedFlags::OnName3> ChildCleard;
bool IsChildCleard()const 
{
 return (mState&ChildCleard.IntValue) == ChildCleard.IntValue;
 
}
static const NodeLayoutChangedFlagsField<16,NodeLayoutChangedFlags::OnName4> ChildOrderChanged;
bool IsChildOrderChanged()const 
{
 return (mState&ChildOrderChanged.IntValue) == ChildOrderChanged.IntValue;
 
}
static const NodeLayoutChangedFlagsField<32,NodeLayoutChangedFlags::OnName5> PositionChanged;
bool IsPositionChanged()const 
{
 return (mState&PositionChanged.IntValue) == PositionChanged.IntValue;
 
}
static const NodeLayoutChangedFlagsField<64,NodeLayoutChangedFlags::OnName6> ArrangeChanged;
bool IsArrangeChanged()const 
{
 return (mState&ArrangeChanged.IntValue) == ArrangeChanged.IntValue;
 
}
static const NodeLayoutChangedFlagsField<128,NodeLayoutChangedFlags::OnName7> CollapseChanged;
bool IsCollapseChanged()const 
{
 return (mState&CollapseChanged.IntValue) == CollapseChanged.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeLayoutChangedFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeLayoutChangedFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeLayoutChangedFlags::Names[Size]=
{
"SizeChanged","ChildAdded","ChildRemoved","ChildCleard","ChildOrderChanged","PositionChanged","ArrangeChanged","CollapseChanged"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int NodeLayoutChangedFlags::Values[Size]=
{
1,2,4,8,16,32,64,128
};
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<0,NodeLayoutChangedFlags::OnNameNone> NodeLayoutChangedFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<1|2|4|8|16|32|64|128,NodeLayoutChangedFlags::OnNameAll> NodeLayoutChangedFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<1,NodeLayoutChangedFlags::OnName0> NodeLayoutChangedFlags::SizeChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<2,NodeLayoutChangedFlags::OnName1> NodeLayoutChangedFlags::ChildAdded;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<4,NodeLayoutChangedFlags::OnName2> NodeLayoutChangedFlags::ChildRemoved;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<8,NodeLayoutChangedFlags::OnName3> NodeLayoutChangedFlags::ChildCleard;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<16,NodeLayoutChangedFlags::OnName4> NodeLayoutChangedFlags::ChildOrderChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<32,NodeLayoutChangedFlags::OnName5> NodeLayoutChangedFlags::PositionChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<64,NodeLayoutChangedFlags::OnName6> NodeLayoutChangedFlags::ArrangeChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutChangedFlags::NodeLayoutChangedFlagsField<128,NodeLayoutChangedFlags::OnName7> NodeLayoutChangedFlags::CollapseChanged;
MEDUSA_END;
