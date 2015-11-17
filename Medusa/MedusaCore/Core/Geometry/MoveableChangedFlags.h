// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaCorePreDeclares.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"
#include "Core/String/HeapString.h"
MEDUSA_BEGIN;
//STRONG_FLAGS_9(MoveableChangedFlags, SizeChanged, PositionChanged, RotationChanged, ScaleChanged, AnchorChanged, FlipChanged, MatrixChanged, WorldMatrixChanged,InheritChanged);
class MoveableChangedFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class MoveableChangedFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class MoveableChangedFlags;
public:
 MoveableChangedFlagsField()
{
}
 bool operator==( MoveableChangedFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( MoveableChangedFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( MoveableChangedFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( MoveableChangedFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( MoveableChangedFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( MoveableChangedFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 MoveableChangedFlags operator|( MoveableChangedFlags rhs ) const
{
return MoveableChangedFlags( TValue | rhs.mState );
}
 MoveableChangedFlags operator&( MoveableChangedFlags rhs ) const
{
return MoveableChangedFlags( TValue & rhs.mState );
}
 MoveableChangedFlags operator^( MoveableChangedFlags rhs ) const
{
return MoveableChangedFlags( TValue ^ rhs.mState );
}
 MoveableChangedFlags operator~() const
{
return MoveableChangedFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 MoveableChangedFlags operator|( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return MoveableChangedFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 MoveableChangedFlags operator&( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return MoveableChangedFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 MoveableChangedFlags operator^( MoveableChangedFlagsField<TValue2,TName2> rhs ) const
{
return MoveableChangedFlags(TValue ^ TValue2);
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
 MoveableChangedFlags( const MoveableChangedFlags& rhs ) : mState( rhs.mState ) 
{
}
 MoveableChangedFlags operator=( MoveableChangedFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags(MoveableChangedFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator=( MoveableChangedFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( MoveableChangedFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( MoveableChangedFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( MoveableChangedFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( MoveableChangedFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( MoveableChangedFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( MoveableChangedFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 MoveableChangedFlags operator|( MoveableChangedFlags rhs ) const
{
return MoveableChangedFlags( mState | rhs.mState );
}
 MoveableChangedFlags operator&( MoveableChangedFlags rhs ) const
{
return MoveableChangedFlags( mState & rhs.mState );
}
 MoveableChangedFlags operator^( MoveableChangedFlags rhs ) const
{
return MoveableChangedFlags( mState ^ rhs.mState );
}
 MoveableChangedFlags operator~() const
{
return MoveableChangedFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator|( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return MoveableChangedFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator&( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return MoveableChangedFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator^( MoveableChangedFlagsField<TValue,TName> rhs ) const
{
return MoveableChangedFlags( mState ^ TValue );
}
 MoveableChangedFlags& operator|=( MoveableChangedFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 MoveableChangedFlags& operator&=( MoveableChangedFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 MoveableChangedFlags& operator^=( MoveableChangedFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator|=( MoveableChangedFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return MoveableChangedFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator&=( MoveableChangedFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return MoveableChangedFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 MoveableChangedFlags operator^=( MoveableChangedFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return MoveableChangedFlags( *this );
}
 MoveableChangedFlags operator<<( unsigned int s )
{
return MoveableChangedFlags( mState << s );
}
 MoveableChangedFlags operator>>( unsigned int s )
{
return MoveableChangedFlags( mState >> s );
}
 MoveableChangedFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 MoveableChangedFlags& operator>>=( unsigned int s )
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
 bool Has(MoveableChangedFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(MoveableChangedFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(MoveableChangedFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(MoveableChangedFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(MoveableChangedFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(MoveableChangedFlags rhs,bool isSet)
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
 bool Has(MoveableChangedFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(MoveableChangedFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(MoveableChangedFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(MoveableChangedFlagsField<TValue,TName> field,bool isSet)
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
explicit MoveableChangedFlags(int state=0):mState(state)
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
static const StringRef& OnName8()
{
return Names[8];
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
static MoveableChangedFlags Parse(int val)
{
if(IsDefined(val))
{
return MoveableChangedFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return MoveableChangedFlags(val);
}
static bool TryParse(int val,MoveableChangedFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static MoveableChangedFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
MoveableChangedFlags result;
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
static bool TryParse(MoveableChangedFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=9;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const MoveableChangedFlagsField<0,MoveableChangedFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const MoveableChangedFlagsField<1|2|4|8|16|32|64|128|256,MoveableChangedFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const MoveableChangedFlagsField<1,MoveableChangedFlags::OnName0> SizeChanged;
bool IsSizeChanged()const 
{
 return (mState&SizeChanged.IntValue) == SizeChanged.IntValue;
 
}
static const MoveableChangedFlagsField<2,MoveableChangedFlags::OnName1> PositionChanged;
bool IsPositionChanged()const 
{
 return (mState&PositionChanged.IntValue) == PositionChanged.IntValue;
 
}
static const MoveableChangedFlagsField<4,MoveableChangedFlags::OnName2> RotationChanged;
bool IsRotationChanged()const 
{
 return (mState&RotationChanged.IntValue) == RotationChanged.IntValue;
 
}
static const MoveableChangedFlagsField<8,MoveableChangedFlags::OnName3> ScaleChanged;
bool IsScaleChanged()const 
{
 return (mState&ScaleChanged.IntValue) == ScaleChanged.IntValue;
 
}
static const MoveableChangedFlagsField<16,MoveableChangedFlags::OnName4> AnchorChanged;
bool IsAnchorChanged()const 
{
 return (mState&AnchorChanged.IntValue) == AnchorChanged.IntValue;
 
}
static const MoveableChangedFlagsField<32,MoveableChangedFlags::OnName5> FlipChanged;
bool IsFlipChanged()const 
{
 return (mState&FlipChanged.IntValue) == FlipChanged.IntValue;
 
}
static const MoveableChangedFlagsField<64,MoveableChangedFlags::OnName6> MatrixChanged;
bool IsMatrixChanged()const 
{
 return (mState&MatrixChanged.IntValue) == MatrixChanged.IntValue;
 
}
static const MoveableChangedFlagsField<128,MoveableChangedFlags::OnName7> WorldMatrixChanged;
bool IsWorldMatrixChanged()const 
{
 return (mState&WorldMatrixChanged.IntValue) == WorldMatrixChanged.IntValue;
 
}
static const MoveableChangedFlagsField<256,MoveableChangedFlags::OnName8> InheritChanged;
bool IsInheritChanged()const 
{
 return (mState&InheritChanged.IntValue) == InheritChanged.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MoveableChangedFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MoveableChangedFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MoveableChangedFlags::Names[Size]=
{
"SizeChanged","PositionChanged","RotationChanged","ScaleChanged","AnchorChanged","FlipChanged","MatrixChanged","WorldMatrixChanged","InheritChanged"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int MoveableChangedFlags::Values[Size]=
{
1,2,4,8,16,32,64,128,256
};
MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<0,MoveableChangedFlags::OnNameNone> MoveableChangedFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<1|2|4|8|16|32|64|128|256,MoveableChangedFlags::OnNameAll> MoveableChangedFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<1,MoveableChangedFlags::OnName0> MoveableChangedFlags::SizeChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<2,MoveableChangedFlags::OnName1> MoveableChangedFlags::PositionChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<4,MoveableChangedFlags::OnName2> MoveableChangedFlags::RotationChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<8,MoveableChangedFlags::OnName3> MoveableChangedFlags::ScaleChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<16,MoveableChangedFlags::OnName4> MoveableChangedFlags::AnchorChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<32,MoveableChangedFlags::OnName5> MoveableChangedFlags::FlipChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<64,MoveableChangedFlags::OnName6> MoveableChangedFlags::MatrixChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<128,MoveableChangedFlags::OnName7> MoveableChangedFlags::WorldMatrixChanged;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MoveableChangedFlags::MoveableChangedFlagsField<256,MoveableChangedFlags::OnName8> MoveableChangedFlags::InheritChanged;
MEDUSA_END;
