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
//STRONG_FLAGS_CUSTOM_6(GraphicsMapBufferMask, Read, GL_MAP_READ_BIT, Write, GL_MAP_WRITE_BIT, InvalidateRange, GL_MAP_INVALIDATE_RANGE_BIT, InvalidateBuffer, GL_MAP_INVALIDATE_BUFFER_BIT, FlushExplicit, GL_MAP_FLUSH_EXPLICIT_BIT, Unsynchronized, GL_MAP_UNSYNCHRONIZED_BIT);
class GraphicsMapBufferMask	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class GraphicsMapBufferMaskField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsMapBufferMask;
public:
 GraphicsMapBufferMaskField()
{
}
 bool operator==( GraphicsMapBufferMask rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsMapBufferMask rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsMapBufferMask rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsMapBufferMask rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsMapBufferMask rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsMapBufferMask rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 GraphicsMapBufferMask operator|( GraphicsMapBufferMask rhs ) const
{
return GraphicsMapBufferMask( TValue | rhs.mState );
}
 GraphicsMapBufferMask operator&( GraphicsMapBufferMask rhs ) const
{
return GraphicsMapBufferMask( TValue & rhs.mState );
}
 GraphicsMapBufferMask operator^( GraphicsMapBufferMask rhs ) const
{
return GraphicsMapBufferMask( TValue ^ rhs.mState );
}
 GraphicsMapBufferMask operator~() const
{
return GraphicsMapBufferMask(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsMapBufferMask operator|( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return GraphicsMapBufferMask(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsMapBufferMask operator&( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return GraphicsMapBufferMask(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsMapBufferMask operator^( GraphicsMapBufferMaskField<TValue2,TName2> rhs ) const
{
return GraphicsMapBufferMask(TValue ^ TValue2);
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
 GraphicsMapBufferMask( const GraphicsMapBufferMask& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsMapBufferMask operator=( GraphicsMapBufferMask rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask(GraphicsMapBufferMaskField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator=( GraphicsMapBufferMaskField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( GraphicsMapBufferMask rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsMapBufferMask rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsMapBufferMask rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsMapBufferMask rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsMapBufferMask rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsMapBufferMask rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 GraphicsMapBufferMask operator|( GraphicsMapBufferMask rhs ) const
{
return GraphicsMapBufferMask( mState | rhs.mState );
}
 GraphicsMapBufferMask operator&( GraphicsMapBufferMask rhs ) const
{
return GraphicsMapBufferMask( mState & rhs.mState );
}
 GraphicsMapBufferMask operator^( GraphicsMapBufferMask rhs ) const
{
return GraphicsMapBufferMask( mState ^ rhs.mState );
}
 GraphicsMapBufferMask operator~() const
{
return GraphicsMapBufferMask( ~mState );
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator|( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return GraphicsMapBufferMask( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator&( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return GraphicsMapBufferMask( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator^( GraphicsMapBufferMaskField<TValue,TName> rhs ) const
{
return GraphicsMapBufferMask( mState ^ TValue );
}
 GraphicsMapBufferMask& operator|=( GraphicsMapBufferMask rhs )
{
mState |= rhs.mState;
return *this;
}
 GraphicsMapBufferMask& operator&=( GraphicsMapBufferMask rhs )
{
mState &= rhs.mState;
return *this;
}
 GraphicsMapBufferMask& operator^=( GraphicsMapBufferMask rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator|=( GraphicsMapBufferMaskField<TValue,TName> rhs )
{
mState |= TValue;
return GraphicsMapBufferMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator&=( GraphicsMapBufferMaskField<TValue,TName> rhs )
{
mState &= TValue;
return GraphicsMapBufferMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsMapBufferMask operator^=( GraphicsMapBufferMaskField<TValue,TName> rhs )
{
mState ^= TValue;
return GraphicsMapBufferMask( *this );
}
 GraphicsMapBufferMask operator<<( unsigned int s )
{
return GraphicsMapBufferMask( mState << s );
}
 GraphicsMapBufferMask operator>>( unsigned int s )
{
return GraphicsMapBufferMask( mState >> s );
}
 GraphicsMapBufferMask& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 GraphicsMapBufferMask& operator>>=( unsigned int s )
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
 bool Has(GraphicsMapBufferMask rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(GraphicsMapBufferMask rhs)
{
mState|=rhs.ToInt();
}
 void Remove(GraphicsMapBufferMask rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(GraphicsMapBufferMask rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(GraphicsMapBufferMask rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(GraphicsMapBufferMask rhs,bool isSet)
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
 bool Has(GraphicsMapBufferMaskField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(GraphicsMapBufferMaskField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(GraphicsMapBufferMaskField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(GraphicsMapBufferMaskField<TValue,TName> field,bool isSet)
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
explicit GraphicsMapBufferMask(int state=0):mState(state)
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
static GraphicsMapBufferMask Parse(int val)
{
if(IsDefined(val))
{
return GraphicsMapBufferMask(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return GraphicsMapBufferMask(val);
}
static bool TryParse(int val,GraphicsMapBufferMask& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static GraphicsMapBufferMask Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
GraphicsMapBufferMask result;
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
static bool TryParse(GraphicsMapBufferMask& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const GraphicsMapBufferMaskField<0,GraphicsMapBufferMask::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_READ_BIT|GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_RANGE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT|GL_MAP_FLUSH_EXPLICIT_BIT|GL_MAP_UNSYNCHRONIZED_BIT,GraphicsMapBufferMask::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_READ_BIT,GraphicsMapBufferMask::OnName0> Read;
bool IsRead()const 
{
 return (mState&Read.IntValue) == Read.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_WRITE_BIT,GraphicsMapBufferMask::OnName1> Write;
bool IsWrite()const 
{
 return (mState&Write.IntValue) == Write.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_INVALIDATE_RANGE_BIT,GraphicsMapBufferMask::OnName2> InvalidateRange;
bool IsInvalidateRange()const 
{
 return (mState&InvalidateRange.IntValue) == InvalidateRange.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_INVALIDATE_BUFFER_BIT,GraphicsMapBufferMask::OnName3> InvalidateBuffer;
bool IsInvalidateBuffer()const 
{
 return (mState&InvalidateBuffer.IntValue) == InvalidateBuffer.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_FLUSH_EXPLICIT_BIT,GraphicsMapBufferMask::OnName4> FlushExplicit;
bool IsFlushExplicit()const 
{
 return (mState&FlushExplicit.IntValue) == FlushExplicit.IntValue;
 
}
static const GraphicsMapBufferMaskField<GL_MAP_UNSYNCHRONIZED_BIT,GraphicsMapBufferMask::OnName5> Unsynchronized;
bool IsUnsynchronized()const 
{
 return (mState&Unsynchronized.IntValue) == Unsynchronized.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsMapBufferMask::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsMapBufferMask::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsMapBufferMask::Names[Size]=
{
"Read","Write","InvalidateRange","InvalidateBuffer","FlushExplicit","Unsynchronized"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsMapBufferMask::Values[Size]=
{
GL_MAP_READ_BIT,GL_MAP_WRITE_BIT,GL_MAP_INVALIDATE_RANGE_BIT,GL_MAP_INVALIDATE_BUFFER_BIT,GL_MAP_FLUSH_EXPLICIT_BIT,GL_MAP_UNSYNCHRONIZED_BIT
};
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<0,GraphicsMapBufferMask::OnNameNone> GraphicsMapBufferMask::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_READ_BIT|GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_RANGE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT|GL_MAP_FLUSH_EXPLICIT_BIT|GL_MAP_UNSYNCHRONIZED_BIT,GraphicsMapBufferMask::OnNameAll> GraphicsMapBufferMask::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_READ_BIT,GraphicsMapBufferMask::OnName0> GraphicsMapBufferMask::Read;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_WRITE_BIT,GraphicsMapBufferMask::OnName1> GraphicsMapBufferMask::Write;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_INVALIDATE_RANGE_BIT,GraphicsMapBufferMask::OnName2> GraphicsMapBufferMask::InvalidateRange;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_INVALIDATE_BUFFER_BIT,GraphicsMapBufferMask::OnName3> GraphicsMapBufferMask::InvalidateBuffer;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_FLUSH_EXPLICIT_BIT,GraphicsMapBufferMask::OnName4> GraphicsMapBufferMask::FlushExplicit;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsMapBufferMask::GraphicsMapBufferMaskField<GL_MAP_UNSYNCHRONIZED_BIT,GraphicsMapBufferMask::OnName5> GraphicsMapBufferMask::Unsynchronized;
MEDUSA_END;
