// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/String/HeapString.h"
#include "Core/String/StringRef.h"
#include "Core/String/StringParser.h"


#define FLAGS_NAME_COMMON_OPERATOR(TFlags,TField)															   \
public:																									   \
	const static bool IsEnum = true;\
	TFlags( const TFlags& rhs ) : mState( rhs.mState ) {}															\
	TFlags operator=( TFlags rhs ){mState = rhs.mState;return *this;}											   \
	template<int TValue,const StringRef& TName()> TFlags(TField<TValue,TName> rhs ) : mState( TValue ) {}													   \
	template<int TValue,const StringRef& TName()> TFlags operator=( TField<TValue,TName> rhs ){mState = TValue;return *this;}										   \
	bool operator==( TFlags rhs ) const{return mState == rhs.mState;}										   \
	bool operator!=( TFlags rhs ) const{return mState != rhs.mState;}										   \
	bool operator<( TFlags rhs ) const{return mState < rhs.mState;}											   \
	bool operator>( TFlags rhs ) const{return mState > rhs.mState;}											   \
	bool operator<=( TFlags rhs ) const{return mState <= rhs.mState;}										   \
	bool operator>=( TFlags rhs ) const{return mState >= rhs.mState;}										   \
	template<int TValue,const StringRef& TName()> bool operator==( TField<TValue,TName> rhs ) const{return mState == TValue;}										   \
	template<int TValue,const StringRef& TName()> bool operator!=( TField<TValue,TName> rhs ) const{return mState != TValue;}										   \
	template<int TValue,const StringRef& TName()> bool operator<( TField<TValue,TName> rhs ) const{return mState < TValue;}											   \
	template<int TValue,const StringRef& TName()> bool operator>( TField<TValue,TName> rhs ) const{return mState > TValue;}											   \
	template<int TValue,const StringRef& TName()> bool operator<=( TField<TValue,TName> rhs ) const{return mState <= TValue;}										   \
	template<int TValue,const StringRef& TName()> bool operator>=( TField<TValue,TName> rhs ) const{return mState >= TValue;}										   \
	TFlags operator|( TFlags rhs ) const{return TFlags( mState | rhs.mState );}								   \
	TFlags operator&( TFlags rhs ) const{return TFlags( mState & rhs.mState );}								   \
	TFlags operator^( TFlags rhs ) const{return TFlags( mState ^ rhs.mState );}								   \
	TFlags operator~() const{return TFlags( ~mState );}														   \
	template<int TValue,const StringRef& TName()> TFlags operator|( TField<TValue,TName> rhs ) const{return TFlags( mState | TValue );}								   \
	template<int TValue,const StringRef& TName()> TFlags operator&( TField<TValue,TName> rhs ) const{return TFlags( mState & TValue );}								   \
	template<int TValue,const StringRef& TName()> TFlags operator^( TField<TValue,TName> rhs ) const{return TFlags( mState ^ TValue );}								   \
	TFlags& operator|=( TFlags rhs ){mState |= rhs.mState;return *this;}								   \
	TFlags& operator&=( TFlags rhs ){mState &= rhs.mState;return *this;}								   \
	TFlags& operator^=( TFlags rhs ){mState ^= rhs.mState;return *this;}								   \
	template<int TValue,const StringRef& TName()> TFlags operator|=( TField<TValue,TName> rhs ){mState |= TValue;return TFlags( *this );}								   \
	template<int TValue,const StringRef& TName()> TFlags operator&=( TField<TValue,TName> rhs ){mState &= TValue;return TFlags( *this );}								   \
	template<int TValue,const StringRef& TName()> TFlags operator^=( TField<TValue,TName> rhs ){mState ^= TValue;return TFlags( *this );}								   \
	TFlags operator<<( unsigned int s ){return TFlags( mState << s );}										   \
	TFlags operator>>( unsigned int s ){return TFlags( mState >> s );}										   \
	TFlags& operator<<=( unsigned int s ){mState <<= s;return *this;}											   \
	TFlags& operator>>=( unsigned int s ){mState >>= s;return *this;}											   \
	int ToInt()const{return mState;}																		\
	bool IsZero()const{return mState==0;}																		\
	bool HasValue()const{return mState!=0;}																		\
	bool Has(TFlags rhs)const{return (mState&rhs.ToInt())==rhs.ToInt();}									\
	void Set(TFlags rhs){mState|=rhs.ToInt();}									\
	void Remove(TFlags rhs){mState&=~rhs.ToInt();}									\
	void SetIf(TFlags rhs,bool isSet){if(isSet){mState|=rhs.ToInt();}}\
	void RemoveIf(TFlags rhs,bool isSet){if(isSet){mState&=~rhs.ToInt();}}\
	void SetOrRemoveIf(TFlags rhs,bool isSet){if(isSet){mState|=rhs.ToInt();}else{mState&=~rhs.ToInt();}}\
	template<int TValue,const StringRef& TName()> bool Has(TField<TValue,TName> field)const{return (mState&TValue)==TValue;}									\
	template<int TValue,const StringRef& TName()> void Set(TField<TValue,TName> field){mState|=TValue;}															\
	template<int TValue,const StringRef& TName()> void Remove(TField<TValue,TName> field){mState&=~TValue;}\
	template<int TValue,const StringRef& TName()> void SetOrRemoveIf(TField<TValue,TName> field,bool isSet){if(isSet){mState|=TValue;}else{mState&=~TValue;}}\
	bool ForceHasFlag(int flag)const{return (mState&flag)==flag;}									\
	void ForceSetOrRemoveFlagIf(int flag,bool isSet){if(isSet){mState|=flag;}else{mState&=~flag;}}\
	void ForceSetFlag(int flag){mState|=flag;}\
	void ForceRemoveFlag(int flag){mState&=~flag;}\
	void ForceSet(int state){mState=state;}																													   \
	int* ForceGetPointer(){return &mState;}																													   \
	int& ForceGetReference(){return mState;}																													   \
	unsigned int ToUInt()const{return (unsigned int)mState;}											\
	explicit operator unsigned int()const{return (unsigned int)mState;}\
	explicit operator int()const{return (int)mState;}\
	intp HashCode()const{return mState;}


#define FLAGS_FIELD_COMMON_OPERATOR(TFlags,TField)														   \
public:	TField(){}																								   \
	bool operator==( TFlags rhs ) const{return TValue == rhs.mState;}										   \
	bool operator!=( TFlags rhs ) const{return TValue != rhs.mState;}										   \
	bool operator<( TFlags rhs ) const{return TValue < rhs.mState;}											   \
	bool operator>( TFlags rhs ) const{return TValue > rhs.mState;}											   \
	bool operator<=( TFlags rhs ) const{return TValue <= rhs.mState;}										   \
	bool operator>=( TFlags rhs ) const{return TValue >= rhs.mState;}										   \
	template<int TValue2,const StringRef& TName2()> bool operator==( TField<TValue2,TName2> rhs ) const{return TValue == TValue2;}										   \
	template<int TValue2,const StringRef& TName2()> bool operator!=( TField<TValue2,TName2> rhs ) const{return TValue != TValue2;}										   \
	template<int TValue2,const StringRef& TName2()> bool operator<( TField<TValue2,TName2> rhs ) const{return TValue < TValue2;}											   \
	template<int TValue2,const StringRef& TName2()> bool operator>( TField<TValue2,TName2> rhs ) const{return TValue > TValue2;}											   \
	template<int TValue2,const StringRef& TName2()> bool operator<=( TField<TValue2,TName2> rhs ) const{return TValue <= TValue2;}										   \
	template<int TValue2,const StringRef& TName2()> bool operator>=( TField<TValue2,TName2> rhs ) const{return TValue >= TValue2;}										   \
	TFlags operator|( TFlags rhs ) const{return TFlags( TValue | rhs.mState );}								   \
	TFlags operator&( TFlags rhs ) const{return TFlags( TValue & rhs.mState );}								   \
	TFlags operator^( TFlags rhs ) const{return TFlags( TValue ^ rhs.mState );}								   \
	TFlags operator~() const{return TFlags(~TValue);}														   \
	template<int TValue2,const StringRef& TName2()> TFlags operator|( TField<TValue2,TName2> rhs ) const{return TFlags(TValue | TValue2);}								   \
	template<int TValue2,const StringRef& TName2()> TFlags operator&( TField<TValue2,TName2> rhs ) const{return TFlags(TValue & TValue2);}								   \
	template<int TValue2,const StringRef& TName2()> TFlags operator^( TField<TValue2,TName2> rhs ) const{return TFlags(TValue ^ TValue2);}								   \
	static constexpr int IntValue=TValue;																															   \
	constexpr int ToInt()const{return TValue;}																														   \
	StringRef ToString()const{return TName();}



#define FLAGS_CLASS_BEGIN(TFlags)																														\
class TFlags																																		   \
{																																					   \
	template<int TValue,const StringRef& TName()> \
class TFlags##Field{friend class TFlags;FLAGS_FIELD_COMMON_OPERATOR(TFlags,TFlags##Field);};	   \
protected:int mState;																																   \
	FLAGS_NAME_COMMON_OPERATOR(TFlags,TFlags##Field);																								   \
public:explicit TFlags(int state=0):mState(state){}

//BEGIN_AUTO_GENERATE_FLAGS_CLASS_END
#define FLAGS_CLASS_END_1(TFlags,T1,P1)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=1;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;

#define FLAGS_CLASS_END_2(TFlags,T1,P1,T2,P2)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=2;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;

#define FLAGS_CLASS_END_3(TFlags,T1,P1,T2,P2,T3,P3)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=3;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;

#define FLAGS_CLASS_END_4(TFlags,T1,P1,T2,P2,T3,P3,T4,P4)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=4;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;

#define FLAGS_CLASS_END_5(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
static const StringRef& OnName4(){return Names[4];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=5;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4|P5,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
static const TFlags##Field<P5,TFlags::OnName4> T5;\
bool Is##T5()const { return (mState&T5.IntValue) == T5.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName4> TFlags::T5;

#define FLAGS_CLASS_END_6(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
static const StringRef& OnName4(){return Names[4];}\
static const StringRef& OnName5(){return Names[5];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=6;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4|P5|P6,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
static const TFlags##Field<P5,TFlags::OnName4> T5;\
bool Is##T5()const { return (mState&T5.IntValue) == T5.IntValue; }\
static const TFlags##Field<P6,TFlags::OnName5> T6;\
bool Is##T6()const { return (mState&T6.IntValue) == T6.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName4> TFlags::T5;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName5> TFlags::T6;

#define FLAGS_CLASS_END_7(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
static const StringRef& OnName4(){return Names[4];}\
static const StringRef& OnName5(){return Names[5];}\
static const StringRef& OnName6(){return Names[6];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=7;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
static const TFlags##Field<P5,TFlags::OnName4> T5;\
bool Is##T5()const { return (mState&T5.IntValue) == T5.IntValue; }\
static const TFlags##Field<P6,TFlags::OnName5> T6;\
bool Is##T6()const { return (mState&T6.IntValue) == T6.IntValue; }\
static const TFlags##Field<P7,TFlags::OnName6> T7;\
bool Is##T7()const { return (mState&T7.IntValue) == T7.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName4> TFlags::T5;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName5> TFlags::T6;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName6> TFlags::T7;

#define FLAGS_CLASS_END_8(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
static const StringRef& OnName4(){return Names[4];}\
static const StringRef& OnName5(){return Names[5];}\
static const StringRef& OnName6(){return Names[6];}\
static const StringRef& OnName7(){return Names[7];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=8;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
static const TFlags##Field<P5,TFlags::OnName4> T5;\
bool Is##T5()const { return (mState&T5.IntValue) == T5.IntValue; }\
static const TFlags##Field<P6,TFlags::OnName5> T6;\
bool Is##T6()const { return (mState&T6.IntValue) == T6.IntValue; }\
static const TFlags##Field<P7,TFlags::OnName6> T7;\
bool Is##T7()const { return (mState&T7.IntValue) == T7.IntValue; }\
static const TFlags##Field<P8,TFlags::OnName7> T8;\
bool Is##T8()const { return (mState&T8.IntValue) == T8.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName4> TFlags::T5;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName5> TFlags::T6;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName6> TFlags::T7;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName7> TFlags::T8;

#define FLAGS_CLASS_END_9(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
static const StringRef& OnName4(){return Names[4];}\
static const StringRef& OnName5(){return Names[5];}\
static const StringRef& OnName6(){return Names[6];}\
static const StringRef& OnName7(){return Names[7];}\
static const StringRef& OnName8(){return Names[8];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=9;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
static const TFlags##Field<P5,TFlags::OnName4> T5;\
bool Is##T5()const { return (mState&T5.IntValue) == T5.IntValue; }\
static const TFlags##Field<P6,TFlags::OnName5> T6;\
bool Is##T6()const { return (mState&T6.IntValue) == T6.IntValue; }\
static const TFlags##Field<P7,TFlags::OnName6> T7;\
bool Is##T7()const { return (mState&T7.IntValue) == T7.IntValue; }\
static const TFlags##Field<P8,TFlags::OnName7> T8;\
bool Is##T8()const { return (mState&T8.IntValue) == T8.IntValue; }\
static const TFlags##Field<P9,TFlags::OnName8> T9;\
bool Is##T9()const { return (mState&T9.IntValue) == T9.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName4> TFlags::T5;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName5> TFlags::T6;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName6> TFlags::T7;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName7> TFlags::T8;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName8> TFlags::T9;

#define FLAGS_CLASS_END_10(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)\
private:\
static const StringRef& OnNameNone(){return NoneName;}\
static const StringRef& OnNameAll(){return AllName;}\
static const StringRef& OnName0(){return Names[0];}\
static const StringRef& OnName1(){return Names[1];}\
static const StringRef& OnName2(){return Names[2];}\
static const StringRef& OnName3(){return Names[3];}\
static const StringRef& OnName4(){return Names[4];}\
static const StringRef& OnName5(){return Names[5];}\
static const StringRef& OnName6(){return Names[6];}\
static const StringRef& OnName7(){return Names[7];}\
static const StringRef& OnName8(){return Names[8];}\
static const StringRef& OnName9(){return Names[9];}\
public:\
HeapString ToString()const{if (mState == None.IntValue) { return NoneName; }if (mState == All.IntValue) { return AllName; }HeapString result;for(uint i=0;i<Size;++i){if ((mState & Values[i]) == Values[i]) { if (!result.IsEmpty()) { result += '|'; }result += Names[i]; }}return result;}\
static bool IsDefined(int val){for(uint i=0;i<Size;++i){if(Values[i]==val) return true;}return false;}\
static bool HasField(const StringRef& name,bool ignoreCase=false){for(uint i=0;i<Size;++i){if(Names[i].Compare(name,ignoreCase)==0) return true;}return false;}\
static TFlags Parse(int val){if(IsDefined(val)){return TFlags(val);}MEDUSA_ASSERT_FAILED("Invalid flags val.");return TFlags(val);}\
static bool TryParse(int val,TFlags& outFlags){if(IsDefined(val)){outFlags.ForceSet(val);return true;}return false;}\
static TFlags Parse(const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { return None; } if (name.Compare(AllName, ignoreCase) == 0) { return All; }TFlags result;bool isSucceed=true;uint j=0;List<HeapString> names;bool splitResult=StringParser::Split<char>(name,"|",names);if(!splitResult){MEDUSA_ASSERT_FAILED("Invalid flags names.");}for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){result.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}if(!isSucceed){MEDUSA_ASSERT_FAILED("Invalid flags names.");}return result;}\
static bool TryParse(TFlags& outFlags,const StringRef& name,bool ignoreCase=false){if (name.Compare(NoneName, ignoreCase) == 0) { outFlags = None; return true; } if (name.Compare(AllName, ignoreCase) == 0) { outFlags = All; return true; }bool isSucceed=true;uint j=0;List<HeapString> names;RETURN_FALSE_IF_FALSE(StringParser::Split<char>(name,"|",names));for(const auto& str:names){if (isSucceed){for(j=0;j<Size;++j){if (str.Compare(Names[j],ignoreCase)==0){outFlags.ForceSetFlag(Values[j]);break;}}if(j==Size){isSucceed=false;}}}return isSucceed;}\
static constexpr unsigned int Size=10;\
static const StringRef NoneName;\
static const StringRef AllName;\
static const StringRef Names[Size];\
static const int Values[Size];\
static const TFlags##Field<0,TFlags::OnNameNone> None;\
bool IsNone()const { return mState == None.IntValue; }\
static const TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10,TFlags::OnNameAll> All;\
bool IsAll()const { return mState == All.IntValue; }\
static const TFlags##Field<P1,TFlags::OnName0> T1;\
bool Is##T1()const { return (mState&T1.IntValue) == T1.IntValue; }\
static const TFlags##Field<P2,TFlags::OnName1> T2;\
bool Is##T2()const { return (mState&T2.IntValue) == T2.IntValue; }\
static const TFlags##Field<P3,TFlags::OnName2> T3;\
bool Is##T3()const { return (mState&T3.IntValue) == T3.IntValue; }\
static const TFlags##Field<P4,TFlags::OnName3> T4;\
bool Is##T4()const { return (mState&T4.IntValue) == T4.IntValue; }\
static const TFlags##Field<P5,TFlags::OnName4> T5;\
bool Is##T5()const { return (mState&T5.IntValue) == T5.IntValue; }\
static const TFlags##Field<P6,TFlags::OnName5> T6;\
bool Is##T6()const { return (mState&T6.IntValue) == T6.IntValue; }\
static const TFlags##Field<P7,TFlags::OnName6> T7;\
bool Is##T7()const { return (mState&T7.IntValue) == T7.IntValue; }\
static const TFlags##Field<P8,TFlags::OnName7> T8;\
bool Is##T8()const { return (mState&T8.IntValue) == T8.IntValue; }\
static const TFlags##Field<P9,TFlags::OnName8> T9;\
bool Is##T9()const { return (mState&T9.IntValue) == T9.IntValue; }\
static const TFlags##Field<P10,TFlags::OnName9> T10;\
bool Is##T10()const { return (mState&T10.IntValue) == T10.IntValue; }\
};\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::NoneName = "None";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::AllName = "All";\
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef TFlags::Names[Size]={#T1,#T2,#T3,#T4,#T5,#T6,#T7,#T8,#T9,#T10};\
MEDUSA_WEAK_MULTIPLE_DEFINE const int TFlags::Values[Size]={P1,P2,P3,P4,P5,P6,P7,P8,P9,P10};\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<0,TFlags::OnNameNone> TFlags::None;\
MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1|P2|P3|P4|P5|P6|P7|P8|P9|P10,TFlags::OnNameAll> TFlags::All;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P1,TFlags::OnName0> TFlags::T1;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P2,TFlags::OnName1> TFlags::T2;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P3,TFlags::OnName2> TFlags::T3;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P4,TFlags::OnName3> TFlags::T4;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P5,TFlags::OnName4> TFlags::T5;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P6,TFlags::OnName5> TFlags::T6;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P7,TFlags::OnName6> TFlags::T7;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P8,TFlags::OnName7> TFlags::T8;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P9,TFlags::OnName8> TFlags::T9;\
	MEDUSA_WEAK_MULTIPLE_DEFINE const TFlags::TFlags##Field<P10,TFlags::OnName9> TFlags::T10;

//END_AUTO_GENERATE_FLAGS_CLASS_END

//BEGIN_AUTO_GENERATE_FLAGS_DEFINE
#define STRONG_FLAGS_CUSTOM_1(TFlags,T1,P1)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_1(TFlags,T1,P1)
#define STRONG_FLAGS_CUSTOM_2(TFlags,T1,P1,T2,P2)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_2(TFlags,T1,P1,T2,P2)
#define STRONG_FLAGS_CUSTOM_3(TFlags,T1,P1,T2,P2,T3,P3)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_3(TFlags,T1,P1,T2,P2,T3,P3)
#define STRONG_FLAGS_CUSTOM_4(TFlags,T1,P1,T2,P2,T3,P3,T4,P4)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_4(TFlags,T1,P1,T2,P2,T3,P3,T4,P4)
#define STRONG_FLAGS_CUSTOM_5(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_5(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5)
#define STRONG_FLAGS_CUSTOM_6(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_6(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6)
#define STRONG_FLAGS_CUSTOM_7(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_7(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7)
#define STRONG_FLAGS_CUSTOM_8(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_8(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8)
#define STRONG_FLAGS_CUSTOM_9(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_9(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9)
#define STRONG_FLAGS_CUSTOM_10(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)	FLAGS_CLASS_BEGIN(TFlags)	FLAGS_CLASS_END_10(TFlags,T1,P1,T2,P2,T3,P3,T4,P4,T5,P5,T6,P6,T7,P7,T8,P8,T9,P9,T10,P10)




#define STRONG_FLAGS_1(TEnum,T1)	STRONG_FLAGS_CUSTOM_1(TEnum,T1,1)
#define STRONG_FLAGS_2(TEnum,T1,T2)	STRONG_FLAGS_CUSTOM_2(TEnum,T1,1,T2,2)
#define STRONG_FLAGS_3(TEnum,T1,T2,T3)	STRONG_FLAGS_CUSTOM_3(TEnum,T1,1,T2,2,T3,4)
#define STRONG_FLAGS_4(TEnum,T1,T2,T3,T4)	STRONG_FLAGS_CUSTOM_4(TEnum,T1,1,T2,2,T3,4,T4,8)
#define STRONG_FLAGS_5(TEnum,T1,T2,T3,T4,T5)	STRONG_FLAGS_CUSTOM_5(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16)
#define STRONG_FLAGS_6(TEnum,T1,T2,T3,T4,T5,T6)	STRONG_FLAGS_CUSTOM_6(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32)
#define STRONG_FLAGS_7(TEnum,T1,T2,T3,T4,T5,T6,T7)	STRONG_FLAGS_CUSTOM_7(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64)
#define STRONG_FLAGS_8(TEnum,T1,T2,T3,T4,T5,T6,T7,T8)	STRONG_FLAGS_CUSTOM_8(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128)
#define STRONG_FLAGS_9(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9)	STRONG_FLAGS_CUSTOM_9(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256)
#define STRONG_FLAGS_10(TEnum,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)	STRONG_FLAGS_CUSTOM_10(TEnum,T1,1,T2,2,T3,4,T4,8,T5,16,T6,32,T7,64,T8,128,T9,256,T10,512)
//END_AUTO_GENERATE_FLAGS_DEFINE

