// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
//[IGNORE_PRE_DECLARE_FILE]
#include "MedusaPreDeclares.h"
#include "Core/String/StringRef.h"
MEDUSA_BEGIN;
//STRONG_ENUM_4(SkeletonAttachmentType, Region, Mesh, SkinnedMesh, BoundingBox);
class SkeletonAttachmentType	//[IGNORE_PRE_DECLARE] 
{
 template<int TValue,unsigned int TIndex,StringRef TName()>
 class SkeletonAttachmentTypeField	//[IGNORE_PRE_DECLARE]
{
friend class SkeletonAttachmentType;
public:
SkeletonAttachmentTypeField()
{
}
 bool operator==( SkeletonAttachmentType rhs ) const
{
return TValue == rhs.mState;
}
 bool operator!=( SkeletonAttachmentType rhs ) const
{
return TValue != rhs.mState;
}
 bool operator<( SkeletonAttachmentType rhs ) const
{
return TValue < rhs.mState;
}
 bool operator>( SkeletonAttachmentType rhs ) const
{
return TValue > rhs.mState;
}
 bool operator<=( SkeletonAttachmentType rhs ) const
{
return TValue <= rhs.mState;
}
 bool operator>=( SkeletonAttachmentType rhs ) const
{
return TValue >= rhs.mState;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator==( SkeletonAttachmentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue == TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator!=( SkeletonAttachmentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue != TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<( SkeletonAttachmentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue < TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>( SkeletonAttachmentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue > TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator<=( SkeletonAttachmentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue <= TValue2;
}
 template<int TValue2,int TIndex2,StringRef TName2()>
 bool operator>=( SkeletonAttachmentTypeField<TValue2,TIndex2,TName2> rhs ) const
{
return TValue >= TValue2;
}
 constexpr static int IntValue=TValue;
 constexpr static unsigned int Index=TIndex;
 constexpr int ToInt()const
{
return TValue;
}
 constexpr unsigned int ToUInt()const
{
return (unsigned int)TValue;
}
 constexpr unsigned int ToIndex()const
{
return TIndex;
}
 StringRef ToString()const
{
return TName();
}
 constexpr intp HashCode()const
{
return TValue;
};
};
 protected:
int mState;
 public:
 const static bool IsEnum = true;
 SkeletonAttachmentType( const SkeletonAttachmentType& rhs ) : mState( rhs.mState ) 
{
}
 SkeletonAttachmentType operator=( SkeletonAttachmentType rhs )
{
mState = rhs.mState;
return *this;
}
 template<int TValue,uint TIndex,StringRef TName()>
 SkeletonAttachmentType(const SkeletonAttachmentTypeField<TValue,TIndex,TName>& rhs ) : mState( TValue ) 
{
}
 template<int TValue,uint TIndex,StringRef TName()>
 SkeletonAttachmentType operator=(const SkeletonAttachmentTypeField<TValue,TIndex,TName>& rhs )
{
mState =TValue;
return *this;
}
 bool operator==( SkeletonAttachmentType rhs ) const
{
return mState == rhs.mState;
}
 bool operator!=( SkeletonAttachmentType rhs ) const
{
return mState != rhs.mState;
}
 bool operator<( SkeletonAttachmentType rhs ) const
{
return mState < rhs.mState;
}
 bool operator>( SkeletonAttachmentType rhs ) const
{
return mState > rhs.mState;
}
 bool operator<=( SkeletonAttachmentType rhs ) const
{
return mState <= rhs.mState;
}
 bool operator>=( SkeletonAttachmentType rhs ) const
{
return mState >= rhs.mState;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator==( SkeletonAttachmentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState == TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator!=( SkeletonAttachmentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState != TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<( SkeletonAttachmentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState < TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>( SkeletonAttachmentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState > TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator<=( SkeletonAttachmentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState <= TValue;
}
 template<int TValue,int TIndex,StringRef TName()>
 bool operator>=( SkeletonAttachmentTypeField<TValue,TIndex,TName> rhs ) const
{
return mState >= TValue;
}
 int ToInt()const
{
return mState;
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
 private:
static StringRef OnName1()
{
return "Region";
}
static StringRef OnName2()
{
return "Mesh";
}
static StringRef OnName3()
{
return "SkinnedMesh";
}
static StringRef OnName4()
{
return "BoundingBox";
}
public:
explicit SkeletonAttachmentType(int val):mState(val)
{
}
StringRef ToString()const
{
switch(mState)
{
case 0:return "Region";
case 1:return "Mesh";
case 2:return "SkinnedMesh";
case 3:return "BoundingBox";
default:
return nullptr;
}
}
uint ToIndex()const
{
for(uint i=0;i<Size;++i)
{
if(Values[i]==mState) return i;
}
return (uint)0xFFFFFFFF;
}
static bool IsDefined(int val)
{
for(uint i=0;i<Size;++i)
{
if(Values[i]==val) return true;
}
return false;
}
static bool HasField(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0) return true;
}
return false;
}
static SkeletonAttachmentType Parse(int val)
{
if(IsDefined(val))
{
return SkeletonAttachmentType(val);
}
MEDUSA_ASSERT_FAILED("Invalid enum val.");
return SkeletonAttachmentType::Region;
}
static bool TryParse(int val,SkeletonAttachmentType& outEnum)
{
if(IsDefined(val))
{
outEnum.ForceSet(val);
return true;
}
return false;
}
static SkeletonAttachmentType Parse(StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
return SkeletonAttachmentType(Values[i]);
}
}
MEDUSA_ASSERT_FAILED("Invalid enum name.");
return SkeletonAttachmentType::Region;
}
static bool TryParse(SkeletonAttachmentType& outEnum,StringRef name,bool ignoreCase=false)
{
for(uint i=0;i<Size;++i)
{
if(Names[i].Compare(name,ignoreCase)==0)
{
outEnum.ForceSet(Values[i]);
 return true;
}
}
return false;
}
public:
static constexpr unsigned int Size=4;
static const StringRef Names[Size];
static const int Values[Size];
static const SkeletonAttachmentTypeField<0,0,SkeletonAttachmentType::OnName1> Region;
static const SkeletonAttachmentTypeField<1,1,SkeletonAttachmentType::OnName2> Mesh;
static const SkeletonAttachmentTypeField<2,2,SkeletonAttachmentType::OnName3> SkinnedMesh;
static const SkeletonAttachmentTypeField<3,3,SkeletonAttachmentType::OnName4> BoundingBox;
SkeletonAttachmentType():mState(0)
{
}
};
MEDUSA_WEAK_MULTIPLE_DEFINE const StringRef SkeletonAttachmentType::Names[Size]=
{
"Region","Mesh","SkinnedMesh","BoundingBox"
};
MEDUSA_WEAK_MULTIPLE_DEFINE const int SkeletonAttachmentType::Values[Size]=
{
0,1,2,3
};
 MEDUSA_WEAK_MULTIPLE_DEFINE const SkeletonAttachmentType::SkeletonAttachmentTypeField<0,0,SkeletonAttachmentType::OnName1> SkeletonAttachmentType::Region;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SkeletonAttachmentType::SkeletonAttachmentTypeField<1,1,SkeletonAttachmentType::OnName2> SkeletonAttachmentType::Mesh;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SkeletonAttachmentType::SkeletonAttachmentTypeField<2,2,SkeletonAttachmentType::OnName3> SkeletonAttachmentType::SkinnedMesh;
 MEDUSA_WEAK_MULTIPLE_DEFINE const SkeletonAttachmentType::SkeletonAttachmentTypeField<3,3,SkeletonAttachmentType::OnName4> SkeletonAttachmentType::BoundingBox;
MEDUSA_END;
