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
//STRONG_FLAGS_7(FontMarkupFlags,IsItalic,IsBold,HasUnderLine,HasOverline,HasStrikethrough,DisableAutoHint,DisableKerning);
class FontMarkupFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class FontMarkupFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class FontMarkupFlags;
public:
 FontMarkupFlagsField()
{
}
 bool operator==( FontMarkupFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( FontMarkupFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( FontMarkupFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( FontMarkupFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( FontMarkupFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( FontMarkupFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 FontMarkupFlags operator|( FontMarkupFlags rhs ) const
{
return FontMarkupFlags( TValue | rhs.mState );
}
 FontMarkupFlags operator&( FontMarkupFlags rhs ) const
{
return FontMarkupFlags( TValue & rhs.mState );
}
 FontMarkupFlags operator^( FontMarkupFlags rhs ) const
{
return FontMarkupFlags( TValue ^ rhs.mState );
}
 FontMarkupFlags operator~() const
{
return FontMarkupFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 FontMarkupFlags operator|( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return FontMarkupFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 FontMarkupFlags operator&( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return FontMarkupFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 FontMarkupFlags operator^( FontMarkupFlagsField<TValue2,TName2> rhs ) const
{
return FontMarkupFlags(TValue ^ TValue2);
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
 FontMarkupFlags( const FontMarkupFlags& rhs ) : mState( rhs.mState ) 
{
}
 FontMarkupFlags operator=( FontMarkupFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags(FontMarkupFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator=( FontMarkupFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( FontMarkupFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( FontMarkupFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( FontMarkupFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( FontMarkupFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( FontMarkupFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( FontMarkupFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 FontMarkupFlags operator|( FontMarkupFlags rhs ) const
{
return FontMarkupFlags( mState | rhs.mState );
}
 FontMarkupFlags operator&( FontMarkupFlags rhs ) const
{
return FontMarkupFlags( mState & rhs.mState );
}
 FontMarkupFlags operator^( FontMarkupFlags rhs ) const
{
return FontMarkupFlags( mState ^ rhs.mState );
}
 FontMarkupFlags operator~() const
{
return FontMarkupFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator|( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return FontMarkupFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator&( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return FontMarkupFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator^( FontMarkupFlagsField<TValue,TName> rhs ) const
{
return FontMarkupFlags( mState ^ TValue );
}
 FontMarkupFlags& operator|=( FontMarkupFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 FontMarkupFlags& operator&=( FontMarkupFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 FontMarkupFlags& operator^=( FontMarkupFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator|=( FontMarkupFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return FontMarkupFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator&=( FontMarkupFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return FontMarkupFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 FontMarkupFlags operator^=( FontMarkupFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return FontMarkupFlags( *this );
}
 FontMarkupFlags operator<<( unsigned int s )
{
return FontMarkupFlags( mState << s );
}
 FontMarkupFlags operator>>( unsigned int s )
{
return FontMarkupFlags( mState >> s );
}
 FontMarkupFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 FontMarkupFlags& operator>>=( unsigned int s )
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
 bool Has(FontMarkupFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(FontMarkupFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(FontMarkupFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(FontMarkupFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(FontMarkupFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(FontMarkupFlags rhs,bool isSet)
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
 bool Has(FontMarkupFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(FontMarkupFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(FontMarkupFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(FontMarkupFlagsField<TValue,TName> field,bool isSet)
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
explicit FontMarkupFlags(int state=0):mState(state)
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
static FontMarkupFlags Parse(int val)
{
if(IsDefined(val))
{
return FontMarkupFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return FontMarkupFlags(val);
}
static bool TryParse(int val,FontMarkupFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static FontMarkupFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
FontMarkupFlags result;
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
static bool TryParse(FontMarkupFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static constexpr unsigned int Size=7;
static const StringRef NoneName;
static const StringRef AllName;
static const StringRef Names[Size];
static const int Values[Size];
static const FontMarkupFlagsField<0,FontMarkupFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const FontMarkupFlagsField<1|2|4|8|16|32|64,FontMarkupFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const FontMarkupFlagsField<1,FontMarkupFlags::OnName0> IsItalic;
bool IsIsItalic()const 
{
 return (mState&IsItalic.IntValue) == IsItalic.IntValue;
 
}
static const FontMarkupFlagsField<2,FontMarkupFlags::OnName1> IsBold;
bool IsIsBold()const 
{
 return (mState&IsBold.IntValue) == IsBold.IntValue;
 
}
static const FontMarkupFlagsField<4,FontMarkupFlags::OnName2> HasUnderLine;
bool IsHasUnderLine()const 
{
 return (mState&HasUnderLine.IntValue) == HasUnderLine.IntValue;
 
}
static const FontMarkupFlagsField<8,FontMarkupFlags::OnName3> HasOverline;
bool IsHasOverline()const 
{
 return (mState&HasOverline.IntValue) == HasOverline.IntValue;
 
}
static const FontMarkupFlagsField<16,FontMarkupFlags::OnName4> HasStrikethrough;
bool IsHasStrikethrough()const 
{
 return (mState&HasStrikethrough.IntValue) == HasStrikethrough.IntValue;
 
}
static const FontMarkupFlagsField<32,FontMarkupFlags::OnName5> DisableAutoHint;
bool IsDisableAutoHint()const 
{
 return (mState&DisableAutoHint.IntValue) == DisableAutoHint.IntValue;
 
}
static const FontMarkupFlagsField<64,FontMarkupFlags::OnName6> DisableKerning;
bool IsDisableKerning()const 
{
 return (mState&DisableKerning.IntValue) == DisableKerning.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FontMarkupFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FontMarkupFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FontMarkupFlags::Names[Size]=
{
"IsItalic","IsBold","HasUnderLine","HasOverline","HasStrikethrough","DisableAutoHint","DisableKerning"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int FontMarkupFlags::Values[Size]=
{
1,2,4,8,16,32,64
};
MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<0,FontMarkupFlags::OnNameNone> FontMarkupFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<1|2|4|8|16|32|64,FontMarkupFlags::OnNameAll> FontMarkupFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<1,FontMarkupFlags::OnName0> FontMarkupFlags::IsItalic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<2,FontMarkupFlags::OnName1> FontMarkupFlags::IsBold;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<4,FontMarkupFlags::OnName2> FontMarkupFlags::HasUnderLine;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<8,FontMarkupFlags::OnName3> FontMarkupFlags::HasOverline;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<16,FontMarkupFlags::OnName4> FontMarkupFlags::HasStrikethrough;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<32,FontMarkupFlags::OnName5> FontMarkupFlags::DisableAutoHint;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontMarkupFlags::FontMarkupFlagsField<64,FontMarkupFlags::OnName6> FontMarkupFlags::DisableKerning;
MEDUSA_END;
