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
//STRONG_FLAGS_2(NodeVisitFlags, ForceUpdateWorldMatrix, ForceUpdateWorldColor);
class NodeVisitFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class NodeVisitFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class NodeVisitFlags;
public:
 NodeVisitFlagsField()
{
}
 bool operator==( NodeVisitFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( NodeVisitFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( NodeVisitFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( NodeVisitFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( NodeVisitFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( NodeVisitFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 NodeVisitFlags operator|( NodeVisitFlags rhs ) const
{
return NodeVisitFlags( TValue | rhs.mState );
}
 NodeVisitFlags operator&( NodeVisitFlags rhs ) const
{
return NodeVisitFlags( TValue & rhs.mState );
}
 NodeVisitFlags operator^( NodeVisitFlags rhs ) const
{
return NodeVisitFlags( TValue ^ rhs.mState );
}
 NodeVisitFlags operator~() const
{
return NodeVisitFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 NodeVisitFlags operator|( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return NodeVisitFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeVisitFlags operator&( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return NodeVisitFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 NodeVisitFlags operator^( NodeVisitFlagsField<TValue2,TName2> rhs ) const
{
return NodeVisitFlags(TValue ^ TValue2);
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
 NodeVisitFlags( const NodeVisitFlags& rhs ) : mState( rhs.mState ) 
{
}
 NodeVisitFlags operator=( NodeVisitFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags(NodeVisitFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator=( NodeVisitFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( NodeVisitFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( NodeVisitFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( NodeVisitFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( NodeVisitFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( NodeVisitFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( NodeVisitFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 NodeVisitFlags operator|( NodeVisitFlags rhs ) const
{
return NodeVisitFlags( mState | rhs.mState );
}
 NodeVisitFlags operator&( NodeVisitFlags rhs ) const
{
return NodeVisitFlags( mState & rhs.mState );
}
 NodeVisitFlags operator^( NodeVisitFlags rhs ) const
{
return NodeVisitFlags( mState ^ rhs.mState );
}
 NodeVisitFlags operator~() const
{
return NodeVisitFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator|( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return NodeVisitFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator&( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return NodeVisitFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator^( NodeVisitFlagsField<TValue,TName> rhs ) const
{
return NodeVisitFlags( mState ^ TValue );
}
 NodeVisitFlags& operator|=( NodeVisitFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 NodeVisitFlags& operator&=( NodeVisitFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 NodeVisitFlags& operator^=( NodeVisitFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator|=( NodeVisitFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return NodeVisitFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator&=( NodeVisitFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return NodeVisitFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 NodeVisitFlags operator^=( NodeVisitFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return NodeVisitFlags( *this );
}
 NodeVisitFlags operator<<( unsigned int s )
{
return NodeVisitFlags( mState << s );
}
 NodeVisitFlags operator>>( unsigned int s )
{
return NodeVisitFlags( mState >> s );
}
 NodeVisitFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 NodeVisitFlags& operator>>=( unsigned int s )
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
 bool Has(NodeVisitFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(NodeVisitFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(NodeVisitFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(NodeVisitFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(NodeVisitFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(NodeVisitFlags rhs,bool isSet)
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
 bool Has(NodeVisitFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(NodeVisitFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(NodeVisitFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(NodeVisitFlagsField<TValue,TName> field,bool isSet)
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
explicit NodeVisitFlags(int state=0):mState(state)
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
static NodeVisitFlags Parse(int val)
{
if(IsDefined(val))
{
return NodeVisitFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return NodeVisitFlags(val);
}
static bool TryParse(int val,NodeVisitFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static NodeVisitFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
NodeVisitFlags result;
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
static bool TryParse(NodeVisitFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const NodeVisitFlagsField<0,NodeVisitFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const NodeVisitFlagsField<1|2,NodeVisitFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const NodeVisitFlagsField<1,NodeVisitFlags::OnName0> ForceUpdateWorldMatrix;
bool IsForceUpdateWorldMatrix()const 
{
 return (mState&ForceUpdateWorldMatrix.IntValue) == ForceUpdateWorldMatrix.IntValue;
 
}
static const NodeVisitFlagsField<2,NodeVisitFlags::OnName1> ForceUpdateWorldColor;
bool IsForceUpdateWorldColor()const 
{
 return (mState&ForceUpdateWorldColor.IntValue) == ForceUpdateWorldColor.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeVisitFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeVisitFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef NodeVisitFlags::Names[Size]=
{
"ForceUpdateWorldMatrix","ForceUpdateWorldColor"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int NodeVisitFlags::Values[Size]=
{
1,2
};
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeVisitFlags::NodeVisitFlagsField<0,NodeVisitFlags::OnNameNone> NodeVisitFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const NodeVisitFlags::NodeVisitFlagsField<1|2,NodeVisitFlags::OnNameAll> NodeVisitFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeVisitFlags::NodeVisitFlagsField<1,NodeVisitFlags::OnName0> NodeVisitFlags::ForceUpdateWorldMatrix;
 MEDUSA_WEAK_MULTIPLE_DEFINE const NodeVisitFlags::NodeVisitFlagsField<2,NodeVisitFlags::OnName1> NodeVisitFlags::ForceUpdateWorldColor;
MEDUSA_END;
