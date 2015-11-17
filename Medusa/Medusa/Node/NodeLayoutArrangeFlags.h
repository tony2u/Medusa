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
//STRONG_FLAGS_2(NodeLayoutArrangeFlags, SuppressArrangeSelf, SuppressArrangeChildren);
class NodeLayoutArrangeFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class NodeLayoutArrangeFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class NodeLayoutArrangeFlags;
public:
 NodeLayoutArrangeFlagsField()
{
}
 bool operator==( NodeLayoutArrangeFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( NodeLayoutArrangeFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( NodeLayoutArrangeFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( NodeLayoutArrangeFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( NodeLayoutArrangeFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( NodeLayoutArrangeFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 NodeLayoutArrangeFlags operator|( NodeLayoutArrangeFlags rhs ) const
{
return NodeLayoutArrangeFlags( TValue | rhs.mState );
}
 NodeLayoutArrangeFlags operator&( NodeLayoutArrangeFlags rhs ) const
{
return NodeLayoutArrangeFlags( TValue & rhs.mState );
}
 NodeLayoutArrangeFlags operator^( NodeLayoutArrangeFlags rhs ) const
{
return NodeLayoutArrangeFlags( TValue ^ rhs.mState );
}
 NodeLayoutArrangeFlags operator~() const
{
return NodeLayoutArrangeFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 NodeLayoutArrangeFlags operator|( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return NodeLayoutArrangeFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeLayoutArrangeFlags operator&( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return NodeLayoutArrangeFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeLayoutArrangeFlags operator^( NodeLayoutArrangeFlagsField<TValue2,TName2> rhs ) const
{
return NodeLayoutArrangeFlags(TValue ^ TValue2);
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
 NodeLayoutArrangeFlags( const NodeLayoutArrangeFlags& rhs ) : mState( rhs.mState ) 
{
}
 NodeLayoutArrangeFlags operator=( NodeLayoutArrangeFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags(NodeLayoutArrangeFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator=( NodeLayoutArrangeFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( NodeLayoutArrangeFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( NodeLayoutArrangeFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( NodeLayoutArrangeFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( NodeLayoutArrangeFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( NodeLayoutArrangeFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( NodeLayoutArrangeFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 NodeLayoutArrangeFlags operator|( NodeLayoutArrangeFlags rhs ) const
{
return NodeLayoutArrangeFlags( mState | rhs.mState );
}
 NodeLayoutArrangeFlags operator&( NodeLayoutArrangeFlags rhs ) const
{
return NodeLayoutArrangeFlags( mState & rhs.mState );
}
 NodeLayoutArrangeFlags operator^( NodeLayoutArrangeFlags rhs ) const
{
return NodeLayoutArrangeFlags( mState ^ rhs.mState );
}
 NodeLayoutArrangeFlags operator~() const
{
return NodeLayoutArrangeFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator|( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return NodeLayoutArrangeFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator&( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return NodeLayoutArrangeFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator^( NodeLayoutArrangeFlagsField<TValue,TName> rhs ) const
{
return NodeLayoutArrangeFlags( mState ^ TValue );
}
 NodeLayoutArrangeFlags& operator|=( NodeLayoutArrangeFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 NodeLayoutArrangeFlags& operator&=( NodeLayoutArrangeFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 NodeLayoutArrangeFlags& operator^=( NodeLayoutArrangeFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator|=( NodeLayoutArrangeFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return NodeLayoutArrangeFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator&=( NodeLayoutArrangeFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return NodeLayoutArrangeFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeLayoutArrangeFlags operator^=( NodeLayoutArrangeFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return NodeLayoutArrangeFlags( *this );
}
 NodeLayoutArrangeFlags operator<<( unsigned int s )
{
return NodeLayoutArrangeFlags( mState << s );
}
 NodeLayoutArrangeFlags operator>>( unsigned int s )
{
return NodeLayoutArrangeFlags( mState >> s );
}
 NodeLayoutArrangeFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 NodeLayoutArrangeFlags& operator>>=( unsigned int s )
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
 bool Has(NodeLayoutArrangeFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(NodeLayoutArrangeFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(NodeLayoutArrangeFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(NodeLayoutArrangeFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(NodeLayoutArrangeFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(NodeLayoutArrangeFlags rhs,bool isSet)
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
 bool Has(NodeLayoutArrangeFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(NodeLayoutArrangeFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(NodeLayoutArrangeFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(NodeLayoutArrangeFlagsField<TValue,TName> field,bool isSet)
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
explicit NodeLayoutArrangeFlags(int state=0):mState(state)
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
static NodeLayoutArrangeFlags Parse(int val)
{
if(IsDefined(val))
{
return NodeLayoutArrangeFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return NodeLayoutArrangeFlags(val);
}
static bool TryParse(int val,NodeLayoutArrangeFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static NodeLayoutArrangeFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
NodeLayoutArrangeFlags result;
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
static bool TryParse(NodeLayoutArrangeFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=2;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const NodeLayoutArrangeFlagsField<0,NodeLayoutArrangeFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const NodeLayoutArrangeFlagsField<1|2,NodeLayoutArrangeFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const NodeLayoutArrangeFlagsField<1,NodeLayoutArrangeFlags::OnName0> SuppressArrangeSelf;
bool IsSuppressArrangeSelf()const 
{
 return (mState&SuppressArrangeSelf.IntValue) == SuppressArrangeSelf.IntValue;
 
}
static const NodeLayoutArrangeFlagsField<2,NodeLayoutArrangeFlags::OnName1> SuppressArrangeChildren;
bool IsSuppressArrangeChildren()const 
{
 return (mState&SuppressArrangeChildren.IntValue) == SuppressArrangeChildren.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeLayoutArrangeFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeLayoutArrangeFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeLayoutArrangeFlags::Names[Size]=
{
"SuppressArrangeSelf","SuppressArrangeChildren"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int NodeLayoutArrangeFlags::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutArrangeFlags::NodeLayoutArrangeFlagsField<0,NodeLayoutArrangeFlags::OnNameNone> NodeLayoutArrangeFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutArrangeFlags::NodeLayoutArrangeFlagsField<1|2,NodeLayoutArrangeFlags::OnNameAll> NodeLayoutArrangeFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutArrangeFlags::NodeLayoutArrangeFlagsField<1,NodeLayoutArrangeFlags::OnName0> NodeLayoutArrangeFlags::SuppressArrangeSelf;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeLayoutArrangeFlags::NodeLayoutArrangeFlagsField<2,NodeLayoutArrangeFlags::OnName1> NodeLayoutArrangeFlags::SuppressArrangeChildren;
MEDUSA_END;
