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
//STRONG_FLAGS_4(BufferObjectChangeFlags,Vertex,TexCoord,Color,Indices);
class BufferObjectChangeFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class BufferObjectChangeFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class BufferObjectChangeFlags;
public:
 BufferObjectChangeFlagsField()
{
}
 bool operator==( BufferObjectChangeFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( BufferObjectChangeFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( BufferObjectChangeFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( BufferObjectChangeFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( BufferObjectChangeFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( BufferObjectChangeFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 BufferObjectChangeFlags operator|( BufferObjectChangeFlags rhs ) const
{
return BufferObjectChangeFlags( TValue | rhs.mState );
}
 BufferObjectChangeFlags operator&( BufferObjectChangeFlags rhs ) const
{
return BufferObjectChangeFlags( TValue & rhs.mState );
}
 BufferObjectChangeFlags operator^( BufferObjectChangeFlags rhs ) const
{
return BufferObjectChangeFlags( TValue ^ rhs.mState );
}
 BufferObjectChangeFlags operator~() const
{
return BufferObjectChangeFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 BufferObjectChangeFlags operator|( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return BufferObjectChangeFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 BufferObjectChangeFlags operator&( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return BufferObjectChangeFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 BufferObjectChangeFlags operator^( BufferObjectChangeFlagsField<TValue2,TName2> rhs ) const
{
return BufferObjectChangeFlags(TValue ^ TValue2);
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
 BufferObjectChangeFlags( const BufferObjectChangeFlags& rhs ) : mState( rhs.mState ) 
{
}
 BufferObjectChangeFlags operator=( BufferObjectChangeFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags(BufferObjectChangeFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator=( BufferObjectChangeFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( BufferObjectChangeFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( BufferObjectChangeFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( BufferObjectChangeFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( BufferObjectChangeFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( BufferObjectChangeFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( BufferObjectChangeFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 BufferObjectChangeFlags operator|( BufferObjectChangeFlags rhs ) const
{
return BufferObjectChangeFlags( mState | rhs.mState );
}
 BufferObjectChangeFlags operator&( BufferObjectChangeFlags rhs ) const
{
return BufferObjectChangeFlags( mState & rhs.mState );
}
 BufferObjectChangeFlags operator^( BufferObjectChangeFlags rhs ) const
{
return BufferObjectChangeFlags( mState ^ rhs.mState );
}
 BufferObjectChangeFlags operator~() const
{
return BufferObjectChangeFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator|( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return BufferObjectChangeFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator&( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return BufferObjectChangeFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator^( BufferObjectChangeFlagsField<TValue,TName> rhs ) const
{
return BufferObjectChangeFlags( mState ^ TValue );
}
 BufferObjectChangeFlags& operator|=( BufferObjectChangeFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 BufferObjectChangeFlags& operator&=( BufferObjectChangeFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 BufferObjectChangeFlags& operator^=( BufferObjectChangeFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator|=( BufferObjectChangeFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return BufferObjectChangeFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator&=( BufferObjectChangeFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return BufferObjectChangeFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 BufferObjectChangeFlags operator^=( BufferObjectChangeFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return BufferObjectChangeFlags( *this );
}
 BufferObjectChangeFlags operator<<( unsigned int s )
{
return BufferObjectChangeFlags( mState << s );
}
 BufferObjectChangeFlags operator>>( unsigned int s )
{
return BufferObjectChangeFlags( mState >> s );
}
 BufferObjectChangeFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 BufferObjectChangeFlags& operator>>=( unsigned int s )
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
 bool Has(BufferObjectChangeFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(BufferObjectChangeFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(BufferObjectChangeFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(BufferObjectChangeFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(BufferObjectChangeFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(BufferObjectChangeFlags rhs,bool isSet)
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
 bool Has(BufferObjectChangeFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(BufferObjectChangeFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(BufferObjectChangeFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(BufferObjectChangeFlagsField<TValue,TName> field,bool isSet)
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
explicit BufferObjectChangeFlags(int state=0):mState(state)
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
static BufferObjectChangeFlags Parse(int val)
{
if(IsDefined(val))
{
return BufferObjectChangeFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return BufferObjectChangeFlags(val);
}
static bool TryParse(int val,BufferObjectChangeFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static BufferObjectChangeFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
BufferObjectChangeFlags result;
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
static bool TryParse(BufferObjectChangeFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const BufferObjectChangeFlagsField<0,BufferObjectChangeFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const BufferObjectChangeFlagsField<1|2|4|8,BufferObjectChangeFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const BufferObjectChangeFlagsField<1,BufferObjectChangeFlags::OnName0> Vertex;
bool IsVertex()const 
{
 return (mState&Vertex.IntValue) == Vertex.IntValue;
 
}
static const BufferObjectChangeFlagsField<2,BufferObjectChangeFlags::OnName1> TexCoord;
bool IsTexCoord()const 
{
 return (mState&TexCoord.IntValue) == TexCoord.IntValue;
 
}
static const BufferObjectChangeFlagsField<4,BufferObjectChangeFlags::OnName2> Color;
bool IsColor()const 
{
 return (mState&Color.IntValue) == Color.IntValue;
 
}
static const BufferObjectChangeFlagsField<8,BufferObjectChangeFlags::OnName3> Indices;
bool IsIndices()const 
{
 return (mState&Indices.IntValue) == Indices.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef BufferObjectChangeFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef BufferObjectChangeFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef BufferObjectChangeFlags::Names[Size]=
{
"Vertex","TexCoord","Color","Indices"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int BufferObjectChangeFlags::Values[Size]=
{
1,2,4,8
};
MEDUSA_WEAK_MULTIPLE_DEFINE const BufferObjectChangeFlags::BufferObjectChangeFlagsField<0,BufferObjectChangeFlags::OnNameNone> BufferObjectChangeFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const BufferObjectChangeFlags::BufferObjectChangeFlagsField<1|2|4|8,BufferObjectChangeFlags::OnNameAll> BufferObjectChangeFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const BufferObjectChangeFlags::BufferObjectChangeFlagsField<1,BufferObjectChangeFlags::OnName0> BufferObjectChangeFlags::Vertex;
 MEDUSA_WEAK_MULTIPLE_DEFINE const BufferObjectChangeFlags::BufferObjectChangeFlagsField<2,BufferObjectChangeFlags::OnName1> BufferObjectChangeFlags::TexCoord;
 MEDUSA_WEAK_MULTIPLE_DEFINE const BufferObjectChangeFlags::BufferObjectChangeFlagsField<4,BufferObjectChangeFlags::OnName2> BufferObjectChangeFlags::Color;
 MEDUSA_WEAK_MULTIPLE_DEFINE const BufferObjectChangeFlags::BufferObjectChangeFlagsField<8,BufferObjectChangeFlags::OnName3> BufferObjectChangeFlags::Indices;
MEDUSA_END;
