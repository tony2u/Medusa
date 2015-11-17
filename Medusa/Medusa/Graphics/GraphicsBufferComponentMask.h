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
//STRONG_FLAGS_CUSTOM_3(GraphicsBufferComponentMask, Depth, GL_DEPTH_BUFFER_BIT, Stencil, GL_STENCIL_BUFFER_BIT, Color, GL_COLOR_BUFFER_BIT);
class GraphicsBufferComponentMask	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class GraphicsBufferComponentMaskField	//[IGNORE_PRE_DECLARE]
{
friend class GraphicsBufferComponentMask;
public:
 GraphicsBufferComponentMaskField()
{
}
 bool operator==( GraphicsBufferComponentMask rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( GraphicsBufferComponentMask rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( GraphicsBufferComponentMask rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( GraphicsBufferComponentMask rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( GraphicsBufferComponentMask rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( GraphicsBufferComponentMask rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 GraphicsBufferComponentMask operator|( GraphicsBufferComponentMask rhs ) const
{
return GraphicsBufferComponentMask( TValue | rhs.mState );
}
 GraphicsBufferComponentMask operator&( GraphicsBufferComponentMask rhs ) const
{
return GraphicsBufferComponentMask( TValue & rhs.mState );
}
 GraphicsBufferComponentMask operator^( GraphicsBufferComponentMask rhs ) const
{
return GraphicsBufferComponentMask( TValue ^ rhs.mState );
}
 GraphicsBufferComponentMask operator~() const
{
return GraphicsBufferComponentMask(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsBufferComponentMask operator|( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return GraphicsBufferComponentMask(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsBufferComponentMask operator&( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return GraphicsBufferComponentMask(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 GraphicsBufferComponentMask operator^( GraphicsBufferComponentMaskField<TValue2,TName2> rhs ) const
{
return GraphicsBufferComponentMask(TValue ^ TValue2);
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
 GraphicsBufferComponentMask( const GraphicsBufferComponentMask& rhs ) : mState( rhs.mState ) 
{
}
 GraphicsBufferComponentMask operator=( GraphicsBufferComponentMask rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask(GraphicsBufferComponentMaskField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator=( GraphicsBufferComponentMaskField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( GraphicsBufferComponentMask rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( GraphicsBufferComponentMask rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( GraphicsBufferComponentMask rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( GraphicsBufferComponentMask rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( GraphicsBufferComponentMask rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( GraphicsBufferComponentMask rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 GraphicsBufferComponentMask operator|( GraphicsBufferComponentMask rhs ) const
{
return GraphicsBufferComponentMask( mState | rhs.mState );
}
 GraphicsBufferComponentMask operator&( GraphicsBufferComponentMask rhs ) const
{
return GraphicsBufferComponentMask( mState & rhs.mState );
}
 GraphicsBufferComponentMask operator^( GraphicsBufferComponentMask rhs ) const
{
return GraphicsBufferComponentMask( mState ^ rhs.mState );
}
 GraphicsBufferComponentMask operator~() const
{
return GraphicsBufferComponentMask( ~mState );
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator|( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return GraphicsBufferComponentMask( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator&( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return GraphicsBufferComponentMask( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator^( GraphicsBufferComponentMaskField<TValue,TName> rhs ) const
{
return GraphicsBufferComponentMask( mState ^ TValue );
}
 GraphicsBufferComponentMask& operator|=( GraphicsBufferComponentMask rhs )
{
mState |= rhs.mState;
return *this;
}
 GraphicsBufferComponentMask& operator&=( GraphicsBufferComponentMask rhs )
{
mState &= rhs.mState;
return *this;
}
 GraphicsBufferComponentMask& operator^=( GraphicsBufferComponentMask rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator|=( GraphicsBufferComponentMaskField<TValue,TName> rhs )
{
mState |= TValue;
return GraphicsBufferComponentMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator&=( GraphicsBufferComponentMaskField<TValue,TName> rhs )
{
mState &= TValue;
return GraphicsBufferComponentMask( *this );
}
 template<int TValue,const StringRef& TName()>
 GraphicsBufferComponentMask operator^=( GraphicsBufferComponentMaskField<TValue,TName> rhs )
{
mState ^= TValue;
return GraphicsBufferComponentMask( *this );
}
 GraphicsBufferComponentMask operator<<( unsigned int s )
{
return GraphicsBufferComponentMask( mState << s );
}
 GraphicsBufferComponentMask operator>>( unsigned int s )
{
return GraphicsBufferComponentMask( mState >> s );
}
 GraphicsBufferComponentMask& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 GraphicsBufferComponentMask& operator>>=( unsigned int s )
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
 bool Has(GraphicsBufferComponentMask rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(GraphicsBufferComponentMask rhs)
{
mState|=rhs.ToInt();
}
 void Remove(GraphicsBufferComponentMask rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(GraphicsBufferComponentMask rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(GraphicsBufferComponentMask rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(GraphicsBufferComponentMask rhs,bool isSet)
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
 bool Has(GraphicsBufferComponentMaskField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(GraphicsBufferComponentMaskField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(GraphicsBufferComponentMaskField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(GraphicsBufferComponentMaskField<TValue,TName> field,bool isSet)
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
explicit GraphicsBufferComponentMask(int state=0):mState(state)
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
static GraphicsBufferComponentMask Parse(int val)
{
if(IsDefined(val))
{
return GraphicsBufferComponentMask(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return GraphicsBufferComponentMask(val);
}
static bool TryParse(int val,GraphicsBufferComponentMask& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static GraphicsBufferComponentMask Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
GraphicsBufferComponentMask result;
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
static bool TryParse(GraphicsBufferComponentMask& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=3;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const GraphicsBufferComponentMaskField<0,GraphicsBufferComponentMask::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const GraphicsBufferComponentMaskField<GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_COLOR_BUFFER_BIT,GraphicsBufferComponentMask::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const GraphicsBufferComponentMaskField<GL_DEPTH_BUFFER_BIT,GraphicsBufferComponentMask::OnName0> Depth;
bool IsDepth()const 
{
 return (mState&Depth.IntValue) == Depth.IntValue;
 
}
static const GraphicsBufferComponentMaskField<GL_STENCIL_BUFFER_BIT,GraphicsBufferComponentMask::OnName1> Stencil;
bool IsStencil()const 
{
 return (mState&Stencil.IntValue) == Stencil.IntValue;
 
}
static const GraphicsBufferComponentMaskField<GL_COLOR_BUFFER_BIT,GraphicsBufferComponentMask::OnName2> Color;
bool IsColor()const 
{
 return (mState&Color.IntValue) == Color.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsBufferComponentMask::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsBufferComponentMask::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef GraphicsBufferComponentMask::Names[Size]=
{
"Depth","Stencil","Color"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int GraphicsBufferComponentMask::Values[Size]=
{
GL_DEPTH_BUFFER_BIT,GL_STENCIL_BUFFER_BIT,GL_COLOR_BUFFER_BIT
};
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBufferComponentMask::GraphicsBufferComponentMaskField<0,GraphicsBufferComponentMask::OnNameNone> GraphicsBufferComponentMask::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBufferComponentMask::GraphicsBufferComponentMaskField<GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_COLOR_BUFFER_BIT,GraphicsBufferComponentMask::OnNameAll> GraphicsBufferComponentMask::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBufferComponentMask::GraphicsBufferComponentMaskField<GL_DEPTH_BUFFER_BIT,GraphicsBufferComponentMask::OnName0> GraphicsBufferComponentMask::Depth;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBufferComponentMask::GraphicsBufferComponentMaskField<GL_STENCIL_BUFFER_BIT,GraphicsBufferComponentMask::OnName1> GraphicsBufferComponentMask::Stencil;
 MEDUSA_WEAK_MULTIPLE_DEFINE const GraphicsBufferComponentMask::GraphicsBufferComponentMaskField<GL_COLOR_BUFFER_BIT,GraphicsBufferComponentMask::OnName2> GraphicsBufferComponentMask::Color;
MEDUSA_END;
