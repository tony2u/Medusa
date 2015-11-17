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
//STRONG_FLAGS_CUSTOM_1(GraphicsSyncMask, FlushCommands, GL_SYNC_FLUSH_COMMANDS_BIT);
class GraphicsSyncMask	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class GraphicsSyncMaskField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsSyncMask;
public:
 GraphicsSyncMaskField()
{
}
 bool operator==( GraphicsSyncMask rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsSyncMask rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsSyncMask rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsSyncMask rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsSyncMask rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsSyncMask rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 GraphicsSyncMask operator|( GraphicsSyncMask rhs ) const
{
return GraphicsSyncMask( TValue | rhs.mState );
}
 GraphicsSyncMask operator&( GraphicsSyncMask rhs ) const
{
return GraphicsSyncMask( TValue & rhs.mState );
}
 GraphicsSyncMask operator^( GraphicsSyncMask rhs ) const
{
return GraphicsSyncMask( TValue ^ rhs.mState );
}
 GraphicsSyncMask operator~() const
{
return GraphicsSyncMask(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsSyncMask operator|( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return GraphicsSyncMask(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsSyncMask operator&( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return GraphicsSyncMask(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsSyncMask operator^( GraphicsSyncMaskField<TValue2,TName2> rhs ) const
{
return GraphicsSyncMask(TValue ^ TValue2);
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
 GraphicsSyncMask( const GraphicsSyncMask& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsSyncMask operator=( GraphicsSyncMask rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask(GraphicsSyncMaskField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator=( GraphicsSyncMaskField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( GraphicsSyncMask rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsSyncMask rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsSyncMask rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsSyncMask rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsSyncMask rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsSyncMask rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 GraphicsSyncMask operator|( GraphicsSyncMask rhs ) const
{
return GraphicsSyncMask( mState | rhs.mState );
}
 GraphicsSyncMask operator&( GraphicsSyncMask rhs ) const
{
return GraphicsSyncMask( mState & rhs.mState );
}
 GraphicsSyncMask operator^( GraphicsSyncMask rhs ) const
{
return GraphicsSyncMask( mState ^ rhs.mState );
}
 GraphicsSyncMask operator~() const
{
return GraphicsSyncMask( ~mState );
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator|( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return GraphicsSyncMask( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator&( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return GraphicsSyncMask( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator^( GraphicsSyncMaskField<TValue,TName> rhs ) const
{
return GraphicsSyncMask( mState ^ TValue );
}
 GraphicsSyncMask& operator|=( GraphicsSyncMask rhs )
{
mState |= rhs.mState;
return *this;
}
 GraphicsSyncMask& operator&=( GraphicsSyncMask rhs )
{
mState &= rhs.mState;
return *this;
}
 GraphicsSyncMask& operator^=( GraphicsSyncMask rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator|=( GraphicsSyncMaskField<TValue,TName> rhs )
{
mState |= TValue;
return GraphicsSyncMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator&=( GraphicsSyncMaskField<TValue,TName> rhs )
{
mState &= TValue;
return GraphicsSyncMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsSyncMask operator^=( GraphicsSyncMaskField<TValue,TName> rhs )
{
mState ^= TValue;
return GraphicsSyncMask( *this );
}
 GraphicsSyncMask operator<<( unsigned int s )
{
return GraphicsSyncMask( mState << s );
}
 GraphicsSyncMask operator>>( unsigned int s )
{
return GraphicsSyncMask( mState >> s );
}
 GraphicsSyncMask& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 GraphicsSyncMask& operator>>=( unsigned int s )
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
 bool Has(GraphicsSyncMask rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(GraphicsSyncMask rhs)
{
mState|=rhs.ToInt();
}
 void Remove(GraphicsSyncMask rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(GraphicsSyncMask rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(GraphicsSyncMask rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(GraphicsSyncMask rhs,bool isSet)
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
 bool Has(GraphicsSyncMaskField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(GraphicsSyncMaskField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(GraphicsSyncMaskField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(GraphicsSyncMaskField<TValue,TName> field,bool isSet)
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
explicit GraphicsSyncMask(int state=0):mState(state)
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
static GraphicsSyncMask Parse(int val)
{
if(IsDefined(val))
{
return GraphicsSyncMask(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return GraphicsSyncMask(val);
}
static bool TryParse(int val,GraphicsSyncMask& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static GraphicsSyncMask Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
GraphicsSyncMask result;
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
static bool TryParse(GraphicsSyncMask& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=1;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsSyncMaskField<0,GraphicsSyncMask::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const GraphicsSyncMaskField<GL_SYNC_FLUSH_COMMANDS_BIT,GraphicsSyncMask::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const GraphicsSyncMaskField<GL_SYNC_FLUSH_COMMANDS_BIT,GraphicsSyncMask::OnName0> FlushCommands;
bool IsFlushCommands()const 
{
 return (mState&FlushCommands.IntValue) == FlushCommands.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsSyncMask::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsSyncMask::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsSyncMask::Names[Size]=
{
"FlushCommands"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsSyncMask::Values[Size]=
{
GL_SYNC_FLUSH_COMMANDS_BIT
};
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsSyncMask::GraphicsSyncMaskField<0,GraphicsSyncMask::OnNameNone> GraphicsSyncMask::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsSyncMask::GraphicsSyncMaskField<GL_SYNC_FLUSH_COMMANDS_BIT,GraphicsSyncMask::OnNameAll> GraphicsSyncMask::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsSyncMask::GraphicsSyncMaskField<GL_SYNC_FLUSH_COMMANDS_BIT,GraphicsSyncMask::OnName0> GraphicsSyncMask::FlushCommands;
MEDUSA_END;
