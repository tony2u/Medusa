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
//STRONG_FLAGS_2(NodeUpdateFlags, SuppressRunningAction, SuppressDispatchingInput);
class NodeUpdateFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class NodeUpdateFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class NodeUpdateFlags;
public:
 NodeUpdateFlagsField()
{
}
 bool operator==( NodeUpdateFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( NodeUpdateFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( NodeUpdateFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( NodeUpdateFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( NodeUpdateFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( NodeUpdateFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 NodeUpdateFlags operator|( NodeUpdateFlags rhs ) const
{
return NodeUpdateFlags( TValue | rhs.mState );
}
 NodeUpdateFlags operator&( NodeUpdateFlags rhs ) const
{
return NodeUpdateFlags( TValue & rhs.mState );
}
 NodeUpdateFlags operator^( NodeUpdateFlags rhs ) const
{
return NodeUpdateFlags( TValue ^ rhs.mState );
}
 NodeUpdateFlags operator~() const
{
return NodeUpdateFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 NodeUpdateFlags operator|( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return NodeUpdateFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeUpdateFlags operator&( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return NodeUpdateFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeUpdateFlags operator^( NodeUpdateFlagsField<TValue2,TName2> rhs ) const
{
return NodeUpdateFlags(TValue ^ TValue2);
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
 NodeUpdateFlags( const NodeUpdateFlags& rhs ) : mState( rhs.mState ) 
{
}
 NodeUpdateFlags operator=( NodeUpdateFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags(NodeUpdateFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator=( NodeUpdateFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( NodeUpdateFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( NodeUpdateFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( NodeUpdateFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( NodeUpdateFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( NodeUpdateFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( NodeUpdateFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 NodeUpdateFlags operator|( NodeUpdateFlags rhs ) const
{
return NodeUpdateFlags( mState | rhs.mState );
}
 NodeUpdateFlags operator&( NodeUpdateFlags rhs ) const
{
return NodeUpdateFlags( mState & rhs.mState );
}
 NodeUpdateFlags operator^( NodeUpdateFlags rhs ) const
{
return NodeUpdateFlags( mState ^ rhs.mState );
}
 NodeUpdateFlags operator~() const
{
return NodeUpdateFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator|( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return NodeUpdateFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator&( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return NodeUpdateFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator^( NodeUpdateFlagsField<TValue,TName> rhs ) const
{
return NodeUpdateFlags( mState ^ TValue );
}
 NodeUpdateFlags& operator|=( NodeUpdateFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 NodeUpdateFlags& operator&=( NodeUpdateFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 NodeUpdateFlags& operator^=( NodeUpdateFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator|=( NodeUpdateFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return NodeUpdateFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator&=( NodeUpdateFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return NodeUpdateFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeUpdateFlags operator^=( NodeUpdateFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return NodeUpdateFlags( *this );
}
 NodeUpdateFlags operator<<( unsigned int s )
{
return NodeUpdateFlags( mState << s );
}
 NodeUpdateFlags operator>>( unsigned int s )
{
return NodeUpdateFlags( mState >> s );
}
 NodeUpdateFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 NodeUpdateFlags& operator>>=( unsigned int s )
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
 bool Has(NodeUpdateFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(NodeUpdateFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(NodeUpdateFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(NodeUpdateFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(NodeUpdateFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(NodeUpdateFlags rhs,bool isSet)
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
 bool Has(NodeUpdateFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(NodeUpdateFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(NodeUpdateFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(NodeUpdateFlagsField<TValue,TName> field,bool isSet)
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
explicit NodeUpdateFlags(int state=0):mState(state)
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
static NodeUpdateFlags Parse(int val)
{
if(IsDefined(val))
{
return NodeUpdateFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return NodeUpdateFlags(val);
}
static bool TryParse(int val,NodeUpdateFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static NodeUpdateFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
NodeUpdateFlags result;
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
static bool TryParse(NodeUpdateFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const NodeUpdateFlagsField<0,NodeUpdateFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const NodeUpdateFlagsField<1|2,NodeUpdateFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const NodeUpdateFlagsField<1,NodeUpdateFlags::OnName0> SuppressRunningAction;
bool IsSuppressRunningAction()const 
{
 return (mState&SuppressRunningAction.IntValue) == SuppressRunningAction.IntValue;
 
}
static const NodeUpdateFlagsField<2,NodeUpdateFlags::OnName1> SuppressDispatchingInput;
bool IsSuppressDispatchingInput()const 
{
 return (mState&SuppressDispatchingInput.IntValue) == SuppressDispatchingInput.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeUpdateFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeUpdateFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeUpdateFlags::Names[Size]=
{
"SuppressRunningAction","SuppressDispatchingInput"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int NodeUpdateFlags::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeUpdateFlags::NodeUpdateFlagsField<0,NodeUpdateFlags::OnNameNone> NodeUpdateFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeUpdateFlags::NodeUpdateFlagsField<1|2,NodeUpdateFlags::OnNameAll> NodeUpdateFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeUpdateFlags::NodeUpdateFlagsField<1,NodeUpdateFlags::OnName0> NodeUpdateFlags::SuppressRunningAction;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeUpdateFlags::NodeUpdateFlagsField<2,NodeUpdateFlags::OnName1> NodeUpdateFlags::SuppressDispatchingInput;
MEDUSA_END;
