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
//STRONG_FLAGS_6(FontFlags,HasHorizontal,HasVertical,HasKerning,IsScalable,IsItalic,IsBold);
class FontFlags	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class FontFlagsField	//[IGNORE_PRE_DECLARE]
{
friend class FontFlags;
public:
 FontFlagsField()
{
}
 bool operator==( FontFlags rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( FontFlags rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( FontFlags rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( FontFlags rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( FontFlags rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( FontFlags rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( FontFlagsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( FontFlagsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( FontFlagsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( FontFlagsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( FontFlagsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( FontFlagsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 FontFlags operator|( FontFlags rhs ) const
{
return FontFlags( TValue | rhs.mState );
}
 FontFlags operator&( FontFlags rhs ) const
{
return FontFlags( TValue & rhs.mState );
}
 FontFlags operator^( FontFlags rhs ) const
{
return FontFlags( TValue ^ rhs.mState );
}
 FontFlags operator~() const
{
return FontFlags(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 FontFlags operator|( FontFlagsField<TValue2,TName2> rhs ) const
{
return FontFlags(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 FontFlags operator&( FontFlagsField<TValue2,TName2> rhs ) const
{
return FontFlags(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 FontFlags operator^( FontFlagsField<TValue2,TName2> rhs ) const
{
return FontFlags(TValue ^ TValue2);
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
 FontFlags( const FontFlags& rhs ) : mState( rhs.mState ) 
{
}
 FontFlags operator=( FontFlags rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 FontFlags(FontFlagsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator=( FontFlagsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( FontFlags rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( FontFlags rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( FontFlags rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( FontFlags rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( FontFlags rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( FontFlags rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( FontFlagsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( FontFlagsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( FontFlagsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( FontFlagsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( FontFlagsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( FontFlagsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 FontFlags operator|( FontFlags rhs ) const
{
return FontFlags( mState | rhs.mState );
}
 FontFlags operator&( FontFlags rhs ) const
{
return FontFlags( mState & rhs.mState );
}
 FontFlags operator^( FontFlags rhs ) const
{
return FontFlags( mState ^ rhs.mState );
}
 FontFlags operator~() const
{
return FontFlags( ~mState );
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator|( FontFlagsField<TValue,TName> rhs ) const
{
return FontFlags( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator&( FontFlagsField<TValue,TName> rhs ) const
{
return FontFlags( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator^( FontFlagsField<TValue,TName> rhs ) const
{
return FontFlags( mState ^ TValue );
}
 FontFlags& operator|=( FontFlags rhs )
{
mState |= rhs.mState;
return *this;
}
 FontFlags& operator&=( FontFlags rhs )
{
mState &= rhs.mState;
return *this;
}
 FontFlags& operator^=( FontFlags rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator|=( FontFlagsField<TValue,TName> rhs )
{
mState |= TValue;
return FontFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator&=( FontFlagsField<TValue,TName> rhs )
{
mState &= TValue;
return FontFlags( *this );
}
 template<int TValue,const StringRef& TName()>
 FontFlags operator^=( FontFlagsField<TValue,TName> rhs )
{
mState ^= TValue;
return FontFlags( *this );
}
 FontFlags operator<<( unsigned int s )
{
return FontFlags( mState << s );
}
 FontFlags operator>>( unsigned int s )
{
return FontFlags( mState >> s );
}
 FontFlags& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 FontFlags& operator>>=( unsigned int s )
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
 bool Has(FontFlags rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(FontFlags rhs)
{
mState|=rhs.ToInt();
}
 void Remove(FontFlags rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(FontFlags rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(FontFlags rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(FontFlags rhs,bool isSet)
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
 bool Has(FontFlagsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(FontFlagsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(FontFlagsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(FontFlagsField<TValue,TName> field,bool isSet)
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
explicit FontFlags(int state=0):mState(state)
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
static FontFlags Parse(int val)
{
if(IsDefined(val))
{
return FontFlags(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return FontFlags(val);
}
static bool TryParse(int val,FontFlags& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static FontFlags Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
FontFlags result;
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
static bool TryParse(FontFlags& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const FontFlagsField<0,FontFlags::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const FontFlagsField<1|2|4|8|16|32,FontFlags::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const FontFlagsField<1,FontFlags::OnName0> HasHorizontal;
bool IsHasHorizontal()const 
{
 return (mState&HasHorizontal.IntValue) == HasHorizontal.IntValue;
 
}
static const FontFlagsField<2,FontFlags::OnName1> HasVertical;
bool IsHasVertical()const 
{
 return (mState&HasVertical.IntValue) == HasVertical.IntValue;
 
}
static const FontFlagsField<4,FontFlags::OnName2> HasKerning;
bool IsHasKerning()const 
{
 return (mState&HasKerning.IntValue) == HasKerning.IntValue;
 
}
static const FontFlagsField<8,FontFlags::OnName3> IsScalable;
bool IsIsScalable()const 
{
 return (mState&IsScalable.IntValue) == IsScalable.IntValue;
 
}
static const FontFlagsField<16,FontFlags::OnName4> IsItalic;
bool IsIsItalic()const 
{
 return (mState&IsItalic.IntValue) == IsItalic.IntValue;
 
}
static const FontFlagsField<32,FontFlags::OnName5> IsBold;
bool IsIsBold()const 
{
 return (mState&IsBold.IntValue) == IsBold.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FontFlags::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FontFlags::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef FontFlags::Names[Size]=
{
"HasHorizontal","HasVertical","HasKerning","IsScalable","IsItalic","IsBold"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int FontFlags::Values[Size]=
{
1,2,4,8,16,32
};
MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<0,FontFlags::OnNameNone> FontFlags::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<1|2|4|8|16|32,FontFlags::OnNameAll> FontFlags::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<1,FontFlags::OnName0> FontFlags::HasHorizontal;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<2,FontFlags::OnName1> FontFlags::HasVertical;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<4,FontFlags::OnName2> FontFlags::HasKerning;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<8,FontFlags::OnName3> FontFlags::IsScalable;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<16,FontFlags::OnName4> FontFlags::IsItalic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const FontFlags::FontFlagsField<32,FontFlags::OnName5> FontFlags::IsBold;
MEDUSA_END;
