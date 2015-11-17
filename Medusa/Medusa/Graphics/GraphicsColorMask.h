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
//STRONG_FLAGS_4(GraphicsColorMask, R, G, B, A);
class GraphicsColorMask	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class GraphicsColorMaskField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsColorMask;
public:
 GraphicsColorMaskField()
{
}
 bool operator==( GraphicsColorMask rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsColorMask rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsColorMask rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsColorMask rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsColorMask rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsColorMask rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 GraphicsColorMask operator|( GraphicsColorMask rhs ) const
{
return GraphicsColorMask( TValue | rhs.mState );
}
 GraphicsColorMask operator&( GraphicsColorMask rhs ) const
{
return GraphicsColorMask( TValue & rhs.mState );
}
 GraphicsColorMask operator^( GraphicsColorMask rhs ) const
{
return GraphicsColorMask( TValue ^ rhs.mState );
}
 GraphicsColorMask operator~() const
{
return GraphicsColorMask(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsColorMask operator|( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return GraphicsColorMask(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsColorMask operator&( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return GraphicsColorMask(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsColorMask operator^( GraphicsColorMaskField<TValue2,TName2> rhs ) const
{
return GraphicsColorMask(TValue ^ TValue2);
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
 GraphicsColorMask( const GraphicsColorMask& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsColorMask operator=( GraphicsColorMask rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask(GraphicsColorMaskField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator=( GraphicsColorMaskField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( GraphicsColorMask rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsColorMask rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsColorMask rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsColorMask rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsColorMask rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsColorMask rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 GraphicsColorMask operator|( GraphicsColorMask rhs ) const
{
return GraphicsColorMask( mState | rhs.mState );
}
 GraphicsColorMask operator&( GraphicsColorMask rhs ) const
{
return GraphicsColorMask( mState & rhs.mState );
}
 GraphicsColorMask operator^( GraphicsColorMask rhs ) const
{
return GraphicsColorMask( mState ^ rhs.mState );
}
 GraphicsColorMask operator~() const
{
return GraphicsColorMask( ~mState );
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator|( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return GraphicsColorMask( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator&( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return GraphicsColorMask( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator^( GraphicsColorMaskField<TValue,TName> rhs ) const
{
return GraphicsColorMask( mState ^ TValue );
}
 GraphicsColorMask& operator|=( GraphicsColorMask rhs )
{
mState |= rhs.mState;
return *this;
}
 GraphicsColorMask& operator&=( GraphicsColorMask rhs )
{
mState &= rhs.mState;
return *this;
}
 GraphicsColorMask& operator^=( GraphicsColorMask rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator|=( GraphicsColorMaskField<TValue,TName> rhs )
{
mState |= TValue;
return GraphicsColorMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator&=( GraphicsColorMaskField<TValue,TName> rhs )
{
mState &= TValue;
return GraphicsColorMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsColorMask operator^=( GraphicsColorMaskField<TValue,TName> rhs )
{
mState ^= TValue;
return GraphicsColorMask( *this );
}
 GraphicsColorMask operator<<( unsigned int s )
{
return GraphicsColorMask( mState << s );
}
 GraphicsColorMask operator>>( unsigned int s )
{
return GraphicsColorMask( mState >> s );
}
 GraphicsColorMask& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 GraphicsColorMask& operator>>=( unsigned int s )
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
 bool Has(GraphicsColorMask rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(GraphicsColorMask rhs)
{
mState|=rhs.ToInt();
}
 void Remove(GraphicsColorMask rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(GraphicsColorMask rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(GraphicsColorMask rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(GraphicsColorMask rhs,bool isSet)
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
 bool Has(GraphicsColorMaskField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(GraphicsColorMaskField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(GraphicsColorMaskField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(GraphicsColorMaskField<TValue,TName> field,bool isSet)
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
explicit GraphicsColorMask(int state=0):mState(state)
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
static GraphicsColorMask Parse(int val)
{
if(IsDefined(val))
{
return GraphicsColorMask(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return GraphicsColorMask(val);
}
static bool TryParse(int val,GraphicsColorMask& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static GraphicsColorMask Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
GraphicsColorMask result;
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
static bool TryParse(GraphicsColorMask& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=4;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsColorMaskField<0,GraphicsColorMask::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const GraphicsColorMaskField<1|2|4|8,GraphicsColorMask::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const GraphicsColorMaskField<1,GraphicsColorMask::OnName0> R;
bool IsR()const 
{
 return (mState&R.IntValue) == R.IntValue;
 
}
static const GraphicsColorMaskField<2,GraphicsColorMask::OnName1> G;
bool IsG()const 
{
 return (mState&G.IntValue) == G.IntValue;
 
}
static const GraphicsColorMaskField<4,GraphicsColorMask::OnName2> B;
bool IsB()const 
{
 return (mState&B.IntValue) == B.IntValue;
 
}
static const GraphicsColorMaskField<8,GraphicsColorMask::OnName3> A;
bool IsA()const 
{
 return (mState&A.IntValue) == A.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsColorMask::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsColorMask::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsColorMask::Names[Size]=
{
"R","G","B","A"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsColorMask::Values[Size]=
{
1,2,4,8
};
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsColorMask::GraphicsColorMaskField<0,GraphicsColorMask::OnNameNone> GraphicsColorMask::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsColorMask::GraphicsColorMaskField<1|2|4|8,GraphicsColorMask::OnNameAll> GraphicsColorMask::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsColorMask::GraphicsColorMaskField<1,GraphicsColorMask::OnName0> GraphicsColorMask::R;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsColorMask::GraphicsColorMaskField<2,GraphicsColorMask::OnName1> GraphicsColorMask::G;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsColorMask::GraphicsColorMaskField<4,GraphicsColorMask::OnName2> GraphicsColorMask::B;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsColorMask::GraphicsColorMaskField<8,GraphicsColorMask::OnName3> GraphicsColorMask::A;
MEDUSA_END;
