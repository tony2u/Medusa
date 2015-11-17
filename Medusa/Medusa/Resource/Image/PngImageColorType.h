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
//STRONG_FLAGS_CUSTOM_5(PngImageColorType,Grey,0,RGB,2,Palette,3,GreyWithAlpha,4,RGBA,6);
class PngImageColorType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class PngImageColorTypeField	//[IGNORE_PRE_DECLARE]
{
friend class PngImageColorType;
public:
 PngImageColorTypeField()
{
}
 bool operator==( PngImageColorType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( PngImageColorType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( PngImageColorType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( PngImageColorType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( PngImageColorType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( PngImageColorType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 PngImageColorType operator|( PngImageColorType rhs ) const
{
return PngImageColorType( TValue | rhs.mState );
}
 PngImageColorType operator&( PngImageColorType rhs ) const
{
return PngImageColorType( TValue & rhs.mState );
}
 PngImageColorType operator^( PngImageColorType rhs ) const
{
return PngImageColorType( TValue ^ rhs.mState );
}
 PngImageColorType operator~() const
{
return PngImageColorType(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 PngImageColorType operator|( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return PngImageColorType(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PngImageColorType operator&( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return PngImageColorType(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 PngImageColorType operator^( PngImageColorTypeField<TValue2,TName2> rhs ) const
{
return PngImageColorType(TValue ^ TValue2);
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
 PngImageColorType( const PngImageColorType& rhs ) : mState( rhs.mState ) 
{
}
 PngImageColorType operator=( PngImageColorType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType(PngImageColorTypeField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator=( PngImageColorTypeField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( PngImageColorType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( PngImageColorType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( PngImageColorType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( PngImageColorType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( PngImageColorType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( PngImageColorType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( PngImageColorTypeField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( PngImageColorTypeField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( PngImageColorTypeField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( PngImageColorTypeField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( PngImageColorTypeField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( PngImageColorTypeField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 PngImageColorType operator|( PngImageColorType rhs ) const
{
return PngImageColorType( mState | rhs.mState );
}
 PngImageColorType operator&( PngImageColorType rhs ) const
{
return PngImageColorType( mState & rhs.mState );
}
 PngImageColorType operator^( PngImageColorType rhs ) const
{
return PngImageColorType( mState ^ rhs.mState );
}
 PngImageColorType operator~() const
{
return PngImageColorType( ~mState );
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator|( PngImageColorTypeField<TValue,TName> rhs ) const
{
return PngImageColorType( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator&( PngImageColorTypeField<TValue,TName> rhs ) const
{
return PngImageColorType( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator^( PngImageColorTypeField<TValue,TName> rhs ) const
{
return PngImageColorType( mState ^ TValue );
}
 PngImageColorType& operator|=( PngImageColorType rhs )
{
mState |= rhs.mState;
return *this;
}
 PngImageColorType& operator&=( PngImageColorType rhs )
{
mState &= rhs.mState;
return *this;
}
 PngImageColorType& operator^=( PngImageColorType rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator|=( PngImageColorTypeField<TValue,TName> rhs )
{
mState |= TValue;
return PngImageColorType( *this );
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator&=( PngImageColorTypeField<TValue,TName> rhs )
{
mState &= TValue;
return PngImageColorType( *this );
}
 template<int TValue,const StringRef& TName()>
 PngImageColorType operator^=( PngImageColorTypeField<TValue,TName> rhs )
{
mState ^= TValue;
return PngImageColorType( *this );
}
 PngImageColorType operator<<( unsigned int s )
{
return PngImageColorType( mState << s );
}
 PngImageColorType operator>>( unsigned int s )
{
return PngImageColorType( mState >> s );
}
 PngImageColorType& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 PngImageColorType& operator>>=( unsigned int s )
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
 bool Has(PngImageColorType rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(PngImageColorType rhs)
{
mState|=rhs.ToInt();
}
 void Remove(PngImageColorType rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(PngImageColorType rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(PngImageColorType rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(PngImageColorType rhs,bool isSet)
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
 bool Has(PngImageColorTypeField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(PngImageColorTypeField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(PngImageColorTypeField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(PngImageColorTypeField<TValue,TName> field,bool isSet)
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
explicit PngImageColorType(int state=0):mState(state)
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
static PngImageColorType Parse(int val)
{
if(IsDefined(val))
{
return PngImageColorType(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return PngImageColorType(val);
}
static bool TryParse(int val,PngImageColorType& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static PngImageColorType Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
PngImageColorType result;
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
static bool TryParse(PngImageColorType& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=5;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const PngImageColorTypeField<0,PngImageColorType::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const PngImageColorTypeField<0|2|3|4|6,PngImageColorType::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const PngImageColorTypeField<0,PngImageColorType::OnName0> Grey;
bool IsGrey()const 
{
 return (mState&Grey.IntValue) == Grey.IntValue;
 
}
static const PngImageColorTypeField<2,PngImageColorType::OnName1> RGB;
bool IsRGB()const 
{
 return (mState&RGB.IntValue) == RGB.IntValue;
 
}
static const PngImageColorTypeField<3,PngImageColorType::OnName2> Palette;
bool IsPalette()const 
{
 return (mState&Palette.IntValue) == Palette.IntValue;
 
}
static const PngImageColorTypeField<4,PngImageColorType::OnName3> GreyWithAlpha;
bool IsGreyWithAlpha()const 
{
 return (mState&GreyWithAlpha.IntValue) == GreyWithAlpha.IntValue;
 
}
static const PngImageColorTypeField<6,PngImageColorType::OnName4> RGBA;
bool IsRGBA()const 
{
 return (mState&RGBA.IntValue) == RGBA.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PngImageColorType::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PngImageColorType::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef PngImageColorType::Names[Size]=
{
"Grey","RGB","Palette","GreyWithAlpha","RGBA"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int PngImageColorType::Values[Size]=
{
0,2,3,4,6
};
MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<0,PngImageColorType::OnNameNone> PngImageColorType::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<0|2|3|4|6,PngImageColorType::OnNameAll> PngImageColorType::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<0,PngImageColorType::OnName0> PngImageColorType::Grey;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<2,PngImageColorType::OnName1> PngImageColorType::RGB;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<3,PngImageColorType::OnName2> PngImageColorType::Palette;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<4,PngImageColorType::OnName3> PngImageColorType::GreyWithAlpha;
 MEDUSA_WEAK_MULTIPLE_DEFINE const PngImageColorType::PngImageColorTypeField<6,PngImageColorType::OnName4> PngImageColorType::RGBA;
MEDUSA_END;
