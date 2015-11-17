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
//STRONG_FLAGS_6(MessageErrorReportSuppress,ConnectFail,AuthFailed,ServerFailed,SwitchUI,UpdateLogic,HideActivityIndicator);
class MessageErrorReportSuppress	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,const StringRef& TName()>
 class MessageErrorReportSuppressField	//[IGNORE_PRE_DECLARE]
{
friend class MessageErrorReportSuppress;
public:
 MessageErrorReportSuppressField()
{
}
 bool operator==( MessageErrorReportSuppress rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( MessageErrorReportSuppress rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( MessageErrorReportSuppress rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( MessageErrorReportSuppress rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( MessageErrorReportSuppress rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( MessageErrorReportSuppress rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator==( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator!=( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator<=( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,const StringRef& TName2()>
 bool operator>=( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 MessageErrorReportSuppress operator|( MessageErrorReportSuppress rhs ) const
{
return MessageErrorReportSuppress( TValue | rhs.mState );
}
 MessageErrorReportSuppress operator&( MessageErrorReportSuppress rhs ) const
{
return MessageErrorReportSuppress( TValue & rhs.mState );
}
 MessageErrorReportSuppress operator^( MessageErrorReportSuppress rhs ) const
{
return MessageErrorReportSuppress( TValue ^ rhs.mState );
}
 MessageErrorReportSuppress operator~() const
{
return MessageErrorReportSuppress(~TValue);
}
 template<int TValue2,const StringRef& TName2()>
 MessageErrorReportSuppress operator|( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return MessageErrorReportSuppress(TValue | TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 MessageErrorReportSuppress operator&( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return MessageErrorReportSuppress(TValue & TValue2);
}
 template<int TValue2,const StringRef& TName2()>
 MessageErrorReportSuppress operator^( MessageErrorReportSuppressField<TValue2,TName2> rhs ) const
{
return MessageErrorReportSuppress(TValue ^ TValue2);
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
 MessageErrorReportSuppress( const MessageErrorReportSuppress& rhs ) : mState( rhs.mState ) 
{
}
 MessageErrorReportSuppress operator=( MessageErrorReportSuppress rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress(MessageErrorReportSuppressField<TValue,TName> rhs ) : mState( TValue ) 
{
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator=( MessageErrorReportSuppressField<TValue,TName> rhs )
{
mState = TValue;
return *this;
}
 bool operator==( MessageErrorReportSuppress rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( MessageErrorReportSuppress rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( MessageErrorReportSuppress rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( MessageErrorReportSuppress rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( MessageErrorReportSuppress rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( MessageErrorReportSuppress rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,const StringRef& TName()>
 bool operator==( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator!=( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator<=( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,const StringRef& TName()>
 bool operator>=( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return mState >= TValue;
}
 MessageErrorReportSuppress operator|( MessageErrorReportSuppress rhs ) const
{
return MessageErrorReportSuppress( mState | rhs.mState );
}
 MessageErrorReportSuppress operator&( MessageErrorReportSuppress rhs ) const
{
return MessageErrorReportSuppress( mState & rhs.mState );
}
 MessageErrorReportSuppress operator^( MessageErrorReportSuppress rhs ) const
{
return MessageErrorReportSuppress( mState ^ rhs.mState );
}
 MessageErrorReportSuppress operator~() const
{
return MessageErrorReportSuppress( ~mState );
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator|( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return MessageErrorReportSuppress( mState | TValue );
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator&( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return MessageErrorReportSuppress( mState & TValue );
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator^( MessageErrorReportSuppressField<TValue,TName> rhs ) const
{
return MessageErrorReportSuppress( mState ^ TValue );
}
 MessageErrorReportSuppress& operator|=( MessageErrorReportSuppress rhs )
{
mState |= rhs.mState;
return *this;
}
 MessageErrorReportSuppress& operator&=( MessageErrorReportSuppress rhs )
{
mState &= rhs.mState;
return *this;
}
 MessageErrorReportSuppress& operator^=( MessageErrorReportSuppress rhs )
{
mState ^= rhs.mState;
return *this;
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator|=( MessageErrorReportSuppressField<TValue,TName> rhs )
{
mState |= TValue;
return MessageErrorReportSuppress( *this );
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator&=( MessageErrorReportSuppressField<TValue,TName> rhs )
{
mState &= TValue;
return MessageErrorReportSuppress( *this );
}
 template<int TValue,const StringRef& TName()>
 MessageErrorReportSuppress operator^=( MessageErrorReportSuppressField<TValue,TName> rhs )
{
mState ^= TValue;
return MessageErrorReportSuppress( *this );
}
 MessageErrorReportSuppress operator<<( unsigned int s )
{
return MessageErrorReportSuppress( mState << s );
}
 MessageErrorReportSuppress operator>>( unsigned int s )
{
return MessageErrorReportSuppress( mState >> s );
}
 MessageErrorReportSuppress& operator<<=( unsigned int s )
{
mState <<= s;
return *this;
}
 MessageErrorReportSuppress& operator>>=( unsigned int s )
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
 bool Has(MessageErrorReportSuppress rhs)const
{
return (mState&rhs.ToInt())==rhs.ToInt();
}
 void Set(MessageErrorReportSuppress rhs)
{
mState|=rhs.ToInt();
}
 void Remove(MessageErrorReportSuppress rhs)
{
mState&=~rhs.ToInt();
}
 void SetIf(MessageErrorReportSuppress rhs,bool isSet)
{
if(isSet)
{
mState|=rhs.ToInt();
}
}
 void RemoveIf(MessageErrorReportSuppress rhs,bool isSet)
{
if(isSet)
{
mState&=~rhs.ToInt();
}
}
 void SetOrRemoveIf(MessageErrorReportSuppress rhs,bool isSet)
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
 bool Has(MessageErrorReportSuppressField<TValue,TName> field)const
{
return (mState&TValue)==TValue;
}
 template<int TValue,const StringRef& TName()>
 void Set(MessageErrorReportSuppressField<TValue,TName> field)
{
mState|=TValue;
}
 template<int TValue,const StringRef& TName()>
 void Remove(MessageErrorReportSuppressField<TValue,TName> field)
{
mState&=~TValue;
}
 template<int TValue,const StringRef& TName()>
 void SetOrRemoveIf(MessageErrorReportSuppressField<TValue,TName> field,bool isSet)
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
explicit MessageErrorReportSuppress(int state=0):mState(state)
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
static MessageErrorReportSuppress Parse(int val)
{
if(IsDefined(val))
{
return MessageErrorReportSuppress(val);
}
MEDUSA_ASSERT_FAILED("Invalid flags val.");
return MessageErrorReportSuppress(val);
}
static bool TryParse(int val,MessageErrorReportSuppress& outFlags)
{
if(IsDefined(val))
{
outFlags.ForceSet(val);
return true;
}
return false;
}
static MessageErrorReportSuppress Parse(const StringRef& name,bool ignoreCase=false)
{
if (name.Compare(NoneName, ignoreCase) == 0) 
{
 return None;
 
}
 if (name.Compare(AllName, ignoreCase) == 0) 
{
 return All;
 
}
MessageErrorReportSuppress result;
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
static bool TryParse(MessageErrorReportSuppress& outFlags,const StringRef& name,bool ignoreCase=false)
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
static const MessageErrorReportSuppressField<0,MessageErrorReportSuppress::OnNameNone> None;
bool IsNone()const 
{
 return mState == None.IntValue;
 
}
static const MessageErrorReportSuppressField<1|2|4|8|16|32,MessageErrorReportSuppress::OnNameAll> All;
bool IsAll()const 
{
 return mState == All.IntValue;
 
}
static const MessageErrorReportSuppressField<1,MessageErrorReportSuppress::OnName0> ConnectFail;
bool IsConnectFail()const 
{
 return (mState&ConnectFail.IntValue) == ConnectFail.IntValue;
 
}
static const MessageErrorReportSuppressField<2,MessageErrorReportSuppress::OnName1> AuthFailed;
bool IsAuthFailed()const 
{
 return (mState&AuthFailed.IntValue) == AuthFailed.IntValue;
 
}
static const MessageErrorReportSuppressField<4,MessageErrorReportSuppress::OnName2> ServerFailed;
bool IsServerFailed()const 
{
 return (mState&ServerFailed.IntValue) == ServerFailed.IntValue;
 
}
static const MessageErrorReportSuppressField<8,MessageErrorReportSuppress::OnName3> SwitchUI;
bool IsSwitchUI()const 
{
 return (mState&SwitchUI.IntValue) == SwitchUI.IntValue;
 
}
static const MessageErrorReportSuppressField<16,MessageErrorReportSuppress::OnName4> UpdateLogic;
bool IsUpdateLogic()const 
{
 return (mState&UpdateLogic.IntValue) == UpdateLogic.IntValue;
 
}
static const MessageErrorReportSuppressField<32,MessageErrorReportSuppress::OnName5> HideActivityIndicator;
bool IsHideActivityIndicator()const 
{
 return (mState&HideActivityIndicator.IntValue) == HideActivityIndicator.IntValue;
 
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MessageErrorReportSuppress::NoneName = "None";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MessageErrorReportSuppress::AllName = "All";
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef MessageErrorReportSuppress::Names[Size]=
{
"ConnectFail","AuthFailed","ServerFailed","SwitchUI","UpdateLogic","HideActivityIndicator"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int MessageErrorReportSuppress::Values[Size]=
{
1,2,4,8,16,32
};
MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<0,MessageErrorReportSuppress::OnNameNone> MessageErrorReportSuppress::None;
MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<1|2|4|8|16|32,MessageErrorReportSuppress::OnNameAll> MessageErrorReportSuppress::All;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<1,MessageErrorReportSuppress::OnName0> MessageErrorReportSuppress::ConnectFail;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<2,MessageErrorReportSuppress::OnName1> MessageErrorReportSuppress::AuthFailed;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<4,MessageErrorReportSuppress::OnName2> MessageErrorReportSuppress::ServerFailed;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<8,MessageErrorReportSuppress::OnName3> MessageErrorReportSuppress::SwitchUI;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<16,MessageErrorReportSuppress::OnName4> MessageErrorReportSuppress::UpdateLogic;
 MEDUSA_WEAK_MULTIPLE_DEFINE const MessageErrorReportSuppress::MessageErrorReportSuppressField<32,MessageErrorReportSuppress::OnName5> MessageErrorReportSuppress::HideActivityIndicator;
MEDUSA_END;
