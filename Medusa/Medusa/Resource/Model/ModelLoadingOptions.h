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
//STRONG_FLAGS_3(ModelLoadingOptions,NoCameraAnimation,NoSkeletonAnimation,NoLightAnimation);
class ModelLoadingOptions	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class ModelLoadingOptionsField	//[IGNORE_PRE_DECLARE]
{
friend class ModelLoadingOptions;
public:
 ModelLoadingOptionsField()
{
}
 bool operator==( ModelLoadingOptions rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( ModelLoadingOptions rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( ModelLoadingOptions rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( ModelLoadingOptions rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( ModelLoadingOptions rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( ModelLoadingOptions rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 ModelLoadingOptions operator|( ModelLoadingOptions rhs ) const
{
return ModelLoadingOptions( TValue | rhs.mState );
}
 ModelLoadingOptions operator&( ModelLoadingOptions rhs ) const
{
return ModelLoadingOptions( TValue & rhs.mState );
}
 ModelLoadingOptions operator^( ModelLoadingOptions rhs ) const
{
return ModelLoadingOptions( TValue ^ rhs.mState );
}
 ModelLoadingOptions operator~() const
{
return ModelLoadingOptions(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 ModelLoadingOptions operator|( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return ModelLoadingOptions(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ModelLoadingOptions operator&( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return ModelLoadingOptions(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 ModelLoadingOptions operator^( ModelLoadingOptionsField<TValue2,TName2> rhs ) const
{
return ModelLoadingOptions(TValue ^ TValue2);
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
 ModelLoadingOptions( const ModelLoadingOptions& rhs ) : mState( rhs.mState ) 
{
}
 ModelLoadingOptions operator=( ModelLoadingOptions rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions(ModelLoadingOptionsField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator=( ModelLoadingOptionsField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( ModelLoadingOptions rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( ModelLoadingOptions rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( ModelLoadingOptions rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( ModelLoadingOptions rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( ModelLoadingOptions rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( ModelLoadingOptions rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 ModelLoadingOptions operator|( ModelLoadingOptions rhs ) const
{
return ModelLoadingOptions( mState | rhs.mState );
}
 ModelLoadingOptions operator&( ModelLoadingOptions rhs ) const
{
return ModelLoadingOptions( mState & rhs.mState );
}
 ModelLoadingOptions operator^( ModelLoadingOptions rhs ) const
{
return ModelLoadingOptions( mState ^ rhs.mState );
}
 ModelLoadingOptions operator~() const
{
return ModelLoadingOptions( ~mState );
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator|( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return ModelLoadingOptions( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator&( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return ModelLoadingOptions( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator^( ModelLoadingOptionsField<TValue,TName> rhs ) const
{
return ModelLoadingOptions( mState ^ TValue );
}
 ModelLoadingOptions& operator|=( ModelLoadingOptions rhs )
{
mState |= rhs.mState;
return *this;
}
 ModelLoadingOptions& operator&=( ModelLoadingOptions rhs )
{
mState &= rhs.mState;
return *this;
}
 ModelLoadingOptions& operator^=( ModelLoadingOptions rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator|=( ModelLoadingOptionsField<TValue,TName> rhs )
{
mState |= TValue;
return ModelLoadingOptions( *this );
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator&=( ModelLoadingOptionsField<TValue,TName> rhs )
{
mState &= TValue;
return ModelLoadingOptions( *this );
}
 template<int TValue,const StringRef& TName()>
 ModelLoadingOptions operator^=( ModelLoadingOptionsField<TValue,TName> rhs )
{
mState ^= TValue;
return ModelLoadingOptions( *this );
}
 ModelLoadingOptions operator<<( unsigned int s )
{
return ModelLoadingOptions( mState << s );
}
 ModelLoadingOptions operator>>( unsigned int s )
{
return ModelLoadingOptions( mState >> s );
}
 ModelLoadingOptions& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 ModelLoadingOptions& operator>>=( unsigned int s )
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
 bool Has(ModelLoadingOptions rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(ModelLoadingOptions rhs)
{
mState|=rhs.ToInt();
}
 void Remove(ModelLoadingOptions rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(ModelLoadingOptions rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(ModelLoadingOptions rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(ModelLoadingOptions rhs,bool isSet)
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
 bool Has(ModelLoadingOptionsField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(ModelLoadingOptionsField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(ModelLoadingOptionsField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(ModelLoadingOptionsField<TValue,TName> field,bool isSet)
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
explicit ModelLoadingOptions(int state=0):mState(state)
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
static ModelLoadingOptions Parse(int val)
{
if(IsDefined(val))
{
return ModelLoadingOptions(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return ModelLoadingOptions(val);
}
static bool TryParse(int val,ModelLoadingOptions& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static ModelLoadingOptions Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
ModelLoadingOptions result;
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
static bool TryParse(ModelLoadingOptions& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const ModelLoadingOptionsField<0,ModelLoadingOptions::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const ModelLoadingOptionsField<1|2|4,ModelLoadingOptions::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const ModelLoadingOptionsField<1,ModelLoadingOptions::OnName0> NoCameraAnimation;
bool IsNoCameraAnimation()const 
{
 return (mState&NoCameraAnimation.IntValue) == NoCameraAnimation.IntValue;
 
}
static const ModelLoadingOptionsField<2,ModelLoadingOptions::OnName1> NoSkeletonAnimation;
bool IsNoSkeletonAnimation()const 
{
 return (mState&NoSkeletonAnimation.IntValue) == NoSkeletonAnimation.IntValue;
 
}
static const ModelLoadingOptionsField<4,ModelLoadingOptions::OnName2> NoLightAnimation;
bool IsNoLightAnimation()const 
{
 return (mState&NoLightAnimation.IntValue) == NoLightAnimation.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ModelLoadingOptions::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ModelLoadingOptions::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef ModelLoadingOptions::Names[Size]=
{
"NoCameraAnimation","NoSkeletonAnimation","NoLightAnimation"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int ModelLoadingOptions::Values[Size]=
{
1,2,4
};
MEDUSA_WEAK_MULTIPLE_DEFINE const ModelLoadingOptions::ModelLoadingOptionsField<0,ModelLoadingOptions::OnNameNone> ModelLoadingOptions::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const ModelLoadingOptions::ModelLoadingOptionsField<1|2|4,ModelLoadingOptions::OnNameAll> ModelLoadingOptions::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ModelLoadingOptions::ModelLoadingOptionsField<1,ModelLoadingOptions::OnName0> ModelLoadingOptions::NoCameraAnimation;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ModelLoadingOptions::ModelLoadingOptionsField<2,ModelLoadingOptions::OnName1> ModelLoadingOptions::NoSkeletonAnimation;
 MEDUSA_WEAK_MULTIPLE_DEFINE const ModelLoadingOptions::ModelLoadingOptionsField<4,ModelLoadingOptions::OnName2> ModelLoadingOptions::NoLightAnimation;
MEDUSA_END;
