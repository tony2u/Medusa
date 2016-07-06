// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "CorePlatform/CorePlatformDefines.h"

namespace Medusa
{
	template<typename T>
	class Share;

	namespace Private
	{
		template < typename T >
		inline T* ToPtr(Share<T>& val)
		{
			return val.Ptr();
		}

		template < typename T >
		inline T* ToPtr(T& val)
		{
			return &val;
		}

		template < typename T >
		inline T* ToPtr(T* val)
		{
			return val;
		}
	}
}

#define UN_USED(p) (void)p

#define MEDUSA_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define MEDUSA_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define MEDUSA_CLAMP(x, l, h)      (MEDUSA_MIN((h), MEDUSA_MAX((x), (l))))


#define IS_NULL_OR_EMPTY(cond) ((cond)==nullptr||(cond)->IsEmpty())
#define IS_NOT_NULL_OR_EMPTY(cond) ((cond)!=nullptr&&!(cond)->IsEmpty())


//return
#define RETURN_IF(cond) if ((cond)){return;}
#define RETURN_IF_TRUE(cond) if ((cond)==true){return;}
#define RETURN_IF_FALSE(cond) if ((cond)==false){return;}
#define RETURN_IF_NULL(cond) if ((cond)==nullptr){return;}
#define RETURN_IF_NOT_NULL(cond) if ((cond)!=nullptr){return;}
#define RETURN_IF_EMPTY(cond) {if((cond).IsEmpty()){return;}}
#define RETURN_IF_NOT_EMPTY(cond) {if(!(cond).IsEmpty()){return;}}
#define RETURN_IF_ZERO(cond) if ((cond)==0){return;}
#define RETURN_IF_NOT_ZERO(cond) if ((cond)!=0){return;}
#define RETURN_IF_EQUAL(first,second) if ((first)==(second)){return;}
#define RETURN_IF_NOT_EQUAL(first,second) if ((first)!=(second)){return;}



#define RETURN_TRUE_IF(cond) if ((cond)){return true;}
#define RETURN_TRUE_IF_TRUE(cond) if ((cond)==true){return true;}
#define RETURN_TRUE_IF_FALSE(cond) if ((cond)==false){return true;}
#define RETURN_TRUE_IF_NULL(cond) if ((cond)==nullptr){return true;}
#define RETURN_TRUE_IF_NOT_NULL(cond) if ((cond)!=nullptr){return true;}
#define RETURN_TRUE_IF_EMPTY(cond) {if((cond).IsEmpty()){return true;}}
#define RETURN_TRUE_IF_NOT_EMPTY(cond) {if(!(cond).IsEmpty()){return true;}}
#define RETURN_TRUE_IF_ZERO(cond) if ((cond)==0){return true;}
#define RETURN_TRUE_IF_NOT_ZERO(cond) if ((cond)!=0){return true;}
#define RETURN_TRUE_IF_EQUAL(first,second) if ((first)==(second)){return true;}
#define RETURN_TRUE_IF_NOT_EQUAL(first,second) if ((first)!=(second)){return true;}

#define RETURN_FALSE_IF(cond) if ((cond)){return false;}
#define RETURN_FALSE_IF_TRUE(cond) if ((cond)==true){return false;}
#define RETURN_FALSE_IF_FALSE(cond) if ((cond)==false){return false;}
#define RETURN_FALSE_IF_NULL(cond) if ((cond)==nullptr){return false;}
#define RETURN_FALSE_IF_NOT_NULL(cond) if ((cond)!=nullptr){return false;}
#define RETURN_FALSE_IF_EMPTY(cond) {if((cond).IsEmpty()){return false;}}
#define RETURN_FALSE_IF_NOT_EMPTY(cond) {if(!(cond).IsEmpty()){return false;}}
#define RETURN_FALSE_IF_ZERO(cond) if ((cond)==0){return false;}
#define RETURN_FALSE_IF_NOT_ZERO(cond) if ((cond)!=0){return false;}
#define RETURN_FALSE_IF_EQUAL(first,second) if ((first)==(second)){return false;}
#define RETURN_FALSE_IF_NOT_EQUAL(first,second) if ((first)!=(second)){return false;}

#define RETURN_NULL_IF(cond) if ((cond)){return nullptr;}
#define RETURN_NULL_IF_TRUE(cond) if ((cond)==true){return nullptr;}
#define RETURN_NULL_IF_FALSE(cond) if ((cond)==false){return nullptr;}
#define RETURN_NULL_IF_NULL(cond) if ((cond)==nullptr){return nullptr;}
#define RETURN_NULL_IF_NOT_NULL(cond) if ((cond)!=nullptr){return nullptr;}
#define RETURN_NULL_IF_EMPTY(cond) {if((cond).IsEmpty()){return nullptr;}}
#define RETURN_NULL_IF_NOT_EMPTY(cond) {if(!(cond).IsEmpty()){return nullptr;}}
#define RETURN_NULL_IF_ZERO(cond) if ((cond)==0){return nullptr;}
#define RETURN_NULL_IF_NOT_ZERO(cond) if ((cond)!=0){return nullptr;}
#define RETURN_NULL_IF_EQUAL(first,second) if ((first)==(second)){return nullptr;}
#define RETURN_NULL_IF_NOT_EQUAL(first,second) if ((first)!=(second)){return nullptr;}

#define RETURN_ZERO_IF(cond) if ((cond)){return 0;}
#define RETURN_ZERO_IF_TRUE(cond) if ((cond)==true){return 0;}
#define RETURN_ZERO_IF_FALSE(cond) if ((cond)==false){return 0;}
#define RETURN_ZERO_IF_NULL(cond) if ((cond)==nullptr){return 0;}
#define RETURN_ZERO_IF_NOT_NULL(cond) if ((cond)!=nullptr){return 0;}
#define RETURN_ZERO_IF_EMPTY(cond) {if((cond).IsEmpty()){return 0;}}
#define RETURN_ZERO_IF_NOT_EMPTY(cond) {if(!(cond).IsEmpty()){return 0;}}
#define RETURN_ZERO_IF_ZERO(cond) if ((cond)==0){return 0;}
#define RETURN_ZERO_IF_NOT_ZERO(cond) if ((cond)!=0){return 0;}
#define RETURN_ZERO_IF_EQUAL(first,second) if ((first)==(second)){return 0;}
#define RETURN_ZERO_IF_NOT_EQUAL(first,second) if ((first)!=(second)){return 0;}

#define RETURN_OBJECT_IF(cond,inObject) if ((cond)){return inObject;}
#define RETURN_OBJECT_IF_TRUE(cond,inObject) if ((cond)==true){return inObject;}
#define RETURN_OBJECT_IF_FALSE(cond,inObject) if ((cond)==false){return inObject;}
#define RETURN_OBJECT_IF_NULL(cond,inObject) if ((cond)==nullptr){return inObject;}
#define RETURN_OBJECT_IF_NOT_NULL(cond,inObject) if ((cond)!=nullptr){return inObject;}
#define RETURN_OBJECT_IF_EMPTY(cond,inObject) {if((cond).IsEmpty()){return inObject;}}
#define RETURN_OBJECT_IF_NOT_EMPTY(cond,inObject) {if(!(cond).IsEmpty()){return inObject;}}
#define RETURN_OBJECT_IF_ZERO(cond,inObject) if ((cond)==0){return inObject;}
#define RETURN_OBJECT_IF_NOT_ZERO(cond,inObject) if ((cond)!=0){return inObject;}
#define RETURN_OBJECT_IF_EQUAL(first,second,inObject) if ((first)==(second)){return inObject;}
#define RETURN_OBJECT_IF_NOT_EQUAL(first,second,inObject) if ((first)!=(second)){return inObject;}

#define RETURN_SELF_IF(inObject) if ((inObject)){return inObject;}
#define RETURN_SELF_IF_TRUE(inObject) if ((inObject)==true){return inObject;}
#define RETURN_SELF_IF_FALSE(inObject) if ((inObject)==false){return inObject;}
#define RETURN_SELF_IF_NULL(inObject) if ((inObject)==nullptr){return inObject;}
#define RETURN_SELF_IF_NOT_NULL(inObject) if ((inObject)!=nullptr){return inObject;}
#define RETURN_SELF_IF_EMPTY(inObject) {if((inObject).IsEmpty()){return inObject;}}
#define RETURN_SELF_IF_NOT_EMPTY(inObject) {if(!(inObject).IsEmpty()){return inObject;}}
#define RETURN_SELF_IF_ZERO(inObject) if ((inObject)==0){return inObject;}
#define RETURN_SELF_IF_NOT_ZERO(inObject) if ((inObject)!=0){return inObject;}
#define RETURN_SELF_IF_EQUAL(inObject,val) if ((inObject)==(val)){return inObject;}
#define RETURN_SELF_IF_NOT_EQUAL(inObject,val) if ((inObject)!=(val)){return inObject;}



//SET return 
#define SET_RETURN_IF(cond,ret) if ((cond)){ret=cond;return ret;}
#define SET_RETURN_TRUE_IF(cond,ret) if ((cond)){ret=true;return ret;}
#define SET_RETURN_FALSE_IF(cond,ret) if ((cond)){ret=false;return ret;}

#define SET_RETURN_TRUE_IF_TRUE(cond,ret) if ((cond)==true){ret=true;return ret;}
#define SET_RETURN_FALSE_IF_TRUE(cond,ret) if ((cond)==true){ret=false;return ret;}

#define SET_RETURN_TRUE_IF_FALSE(cond,ret) if ((cond)==false){ret=true;return ret;}
#define SET_RETURN_FALSE_IF_FALSE(cond,ret) if ((cond)==false){ret=false;return ret;}

#define SET_RETURN_TRUE_IF_NULL(cond,ret) if ((cond)==nullptr){ret=true;return ret;}
#define SET_RETURN_FALSE_IF_NULL(cond,ret) if ((cond)==nullptr){ret=false;return ret;}

#define SET_RETURN_IF_EMPTY(cond,ret) if ((cond).IsEmpty()){ret=cond;return ret;}
#define SET_RETURN_TRUE_IF_EMPTY(cond,ret) if ((cond).IsEmpty()){ret=true;return ret;}
#define SET_RETURN_FALSE_IF_EMPTY(cond,ret) if ((cond).IsEmpty()){ret=false;return ret;}

#define SET_RETURN_TRUE_IF_EQUAL(first,second) if ((first)==(second)){ret=true;return ret;}
#define SET_RETURN_FALSE_IF_NOT_EQUAL(first,second) if ((first)!=(second)){ret=false;return ret;}

//Break
#define BREAK_IF(cond) if ((cond)){break;}
#define BREAK_IF_TRUE(cond) if ((cond)==true){break;}
#define BREAK_IF_FALSE(cond) if ((cond)==false){break;}
#define BREAK_IF_NULL(cond) if ((cond)==nullptr){break;}
#define BREAK_IF_NOT_NULL(cond) if ((cond)!=nullptr){break;}
#define BREAK_IF_EMPTY(cond) if ((cond).IsEmpty()){break;}
#define BREAK_IF_NOT_EMPTY(cond) if (!(cond).IsEmpty()){break;}
#define BREAK_IF_ZERO(cond) if ((cond)==0){break;}
#define BREAK_IF_NOT_ZERO(cond) if ((cond)!=0){break;}
#define BREAK_IF_EQUAL(first,second) if ((first)==(second)){break;}
#define BREAK_IF_NOT_EQUAL(first,second) if ((first)!=(second)){break;}



#define CONTINUE_IF(cond) if ((cond)){continue;}
#define CONTINUE_IF_TRUE(cond) if ((cond)==true){continue;}
#define CONTINUE_IF_FALSE(cond) if ((cond)==false){continue;}
#define CONTINUE_IF_NULL(cond) if ((cond)==nullptr){continue;}
#define CONTINUE_IF_NOT_NULL(cond) if ((cond)!=nullptr){continue;}
#define CONTINUE_IF_EMPTY(cond) if ((cond).IsEmpty()){continue;}
#define CONTINUE_IF_NOT_EMPTY(cond) if (!(cond).IsEmpty()){continue;}
#define CONTINUE_IF_ZERO(cond) if ((cond)==0){continue;}
#define CONTINUE_IF_NOT_ZERO(cond) if ((cond)!=0){continue;}
#define CONTINUE_IF_EQUAL(first,second) if ((first)==(second)){continue;}
#define CONTINUE_IF_NOT_EQUAL(first,second) if ((first)!=(second)){continue;}


#define SAFE_FREE(p)			if(p!=nullptr) {free(p); p = nullptr; }
#define SAFE_DELETE(p)			if(p!=nullptr) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p)    if(p!=nullptr) { delete[] p; p = nullptr; }


#define SAFE_ASSIGN(dest,src)	{if(dest!=src){SAFE_DELETE(dest);dest=src;}}
#define SAFE_CONSTRUCT_PTR(type,dest,src)	{dest=src?new type(*src):nullptr;}
#define SAFE_COPY_PTR(type,dest,src)	{if(src!=nullptr){if(dest==nullptr){dest=new type(*src);}else{*dest=*src;}}else{SAFE_DELETE(dest);}}


#define SAFE_RELEASE(p)			if(p!=nullptr) { p->Release(); p = nullptr; }
#define SAFE_RETAIN(p)			if(p!=nullptr) { p->Retain(); }
#define SAFE_ASSIGN_REF(dest,src)	{if(dest!=src){SAFE_RETAIN(src);SAFE_RELEASE(dest);dest=src;}}
#define SAFE_MOVE_REF(dest,src)	{if(dest!=src){SAFE_RETAIN(src);SAFE_RELEASE(dest);dest=src;src=nullptr;}}



#define SAFE_DELETE_ARRAY_EACH(p)    if(p!=nullptr) {	for (size_t z=0;z<sizeof(p)/sizeof(p[0]);++z){SAFE_DELETE(p[z]);}}
#define SAFE_DELETE_ARRAY_EACH_WITH_SIZE(p,arraySize)   if(p!=nullptr) { for (size_t z=0;z<arraySize;++z){SAFE_DELETE(p[z]);}}

#define SAFE_DELETE_COLLECTION(items) {for(auto z:items) {SAFE_DELETE(z);}(items).Clear();}


#define SAFE_DELETE_DICTIONARY_KEY(items) {for(auto z:items) {SAFE_DELETE(z.Key);}(items).Clear();}
#define SAFE_DELETE_DICTIONARY_VALUE(items) {for(auto z:items) {SAFE_DELETE(z.Value);}(items).Clear();}
#define SAFE_DELETE_DICTIONARY_BOTH(items) {for(auto z:items) {SAFE_DELETE(z.Key);SAFE_DELETE(z.Value);}(items).Clear();}


#define FOR_EACH_ARRAY(i,items) for(size_t i=0;i<sizeof((items))/sizeof((items)[0]);++i)
#define FOR_EACH_SIZE(i,size) for(size_t i=0;i<size;++i)
#define FOR_EACH_INT32(i,size) for(int i=0;i<size;++i)
#define FOR_EACH_UINT32(i,size) for(uint i=0;i<size;++i)
#define FOR_EACH_AUTO(i,size) for(decltype(size) i=0;i<size;++i)

#define FOR_EACH_COLLECTION_VIRTUAL(i,items) for(auto i = (items).GetEnumeratorVirtual();i.MoveNext();) 


#define FOR_EACH_COLLECTION_BEGIN_END(i,begin,end) for(auto i = begin;i!=end;++i) 
#define FOR_EACH_COLLECTION_END_BEGIN(i,end,begin) for(auto i = end;i!=begin;--i) 

#define FOR_EACH_CHAR_BEGIN_END(i,begin,end) for(char i = begin;i<=end;++i) 
#define FOR_EACH_CHAR_END_BEGIN(i,end,begin) for(char i = end;i>=begin;--i) 

#define FOR_EACH_BYTE_BEGIN_END(i,begin,end) for(byte i = begin;i<=end;++i) 
#define FOR_EACH_BYTE_END_BEGIN(i,end,begin) for(byte i = end;i>=begin;--i) 

#define FOR_EACH_SHORT_BEGIN_END(i,begin,end) for(short i = begin;i<=end;++i) 
#define FOR_EACH_SHORT_END_BEGIN(i,end,begin) for(short i = end;i>=begin;--i) 

#define FOR_EACH_USHORT_BEGIN_END(i,begin,end) for(ushort i = begin;i<=end;++i) 
#define FOR_EACH_USHORT_END_BEGIN(i,end,begin) for(ushort i = end;i>=begin;--i) 

#define FOR_EACH_INT_BEGIN_END(i,begin,end) for(intp i = begin;i<=end;++i) 
#define FOR_EACH_INT_END_BEGIN(i,end,begin) for(intp i = end;i>=begin;--i) 

#define FOR_EACH_INT32_BEGIN_END(i,begin,end) for(int i = begin;i<=end;++i)
#define FOR_EACH_INT32_END_BEGIN(i,end,begin) for(int i = end;i>=begin;--i)

#define FOR_EACH_UINT_BEGIN_END(i,begin,end) for(uintp i = begin;i<=end;++i) 
#define FOR_EACH_UINT_END_BEGIN(i,end,begin) for(uintp i = end;i>=begin;--i) 

#define FOR_EACH_UINT32_BEGIN_END(i,begin,end) for(uint i = begin;i<=end;++i)
#define FOR_EACH_UINT32_END_BEGIN(i,end,begin) for(uint i = end;i>=begin;--i)

#define FOR_EACH_SIZE_BEGIN_END(i,begin,end) for(size_t i = begin;i<=end;++i)
#define FOR_EACH_SIZE_END_BEGIN(i,end,begin) for(size_t i = end;i>=begin;--i)

#define FOR_EACH_AUTO_BEGIN_END(i,begin,end) for(auto i = begin;i<=end;++i) 
#define FOR_EACH_AUTO_END_BEGIN(i,end,begin) for(auto i = end;i>=begin;--i) 

#define FOR_EACH_CUSTOM_BEGIN_END(T,i,begin,end) for(T i = begin;i<=end;++i) 
#define FOR_EACH_CUSTOM_END_BEGIN(T,i,end,begin) for(T i = end;i>=begin;--i) 


#define FOR_EACH_APPLY(items,func) {for(auto z:items){func(z);}}
#define FOR_EACH_TO(items,func) {for(auto z:items){Medusa::Private::ToPtr(z)->func;}}

#define FOR_EACH_ITEM_CLEAR(items,func) {for(auto z:items){func(z);}(items).Clear();}
#define FOR_EACH_TO_CLEAR(items,func) {for(auto z:items){Medusa::Private::ToPtr(z)->func;}(items).Clear();}


#define FOR_EACH_DICTIONARY_KEY(items,func) {for(auto z:items) {func(z.Key);}}
#define FOR_EACH_DICTIONARY_KEY_TO(items,func) {for(auto z:items){Medusa::Private::ToPtr(z.Key)->func;}}
#define FOR_EACH_DICTIONARY_KEY_CLEAR(items,func) {for(auto z:items) {func(z.Key);}(items).Clear();}
#define FOR_EACH_DICTIONARY_KEY_TO_CLEAR(items,func) {for(auto z:items){Medusa::Private::ToPtr(z.Key)->func;}(items).Clear();}

#define FOR_EACH_DICTIONARY_VALUE(items,func) {for(auto z:items) {func(z.Value);}}
#define FOR_EACH_DICTIONARY_VALUE_TO(items,func) {for(auto z:items){Medusa::Private::ToPtr(z.Value)->func;}}
#define FOR_EACH_DICTIONARY_VALUE_CLEAR(items,func) {for(auto z:items) {func(z.Value);}(items).Clear();}
#define FOR_EACH_DICTIONARY_VALUE_TO_CLEAR(items,func) {for(auto z:items){Medusa::Private::ToPtr(z.Value)->func;}(items).Clear();}


#define MEDUSA_LOW_SHORT(x)     ((int16)(((int32)(x)) & 0xffff))
#define MEDUSA_HIGH_SHORT(x)     ((int16)((((int32)(x)) >> 16) & 0xffff))
#define MEDUSA_LOW_INT(x)    ((int32)(x))
#define MEDUSA_HIGH_INT(x)    ((int32)(((x) >> 32) & 0xffffffff))

#define MEDUSA_LOW_USHORT(x)     ((uint16)(((uint32)(x)) & 0xffff))
#define MEDUSA_HIGH_USHORT(x)     ((uint16)((((uint32)(x)) >> 16) & 0xffff))
#define MEDUSA_LOW_UINT(x)    ((uint32)(x))
#define MEDUSA_HIGH_UINT(x)    ((uint32)(((x) >> 32) & 0xffffffff))


#define MEDUSA_INT_LOW(x)     ((((int32)(x)) & 0xffff))
#define MEDUSA_INT_HIGH(x)     ((((int32)(x)) & 0xffff0000))
#define MEDUSA_INT64_LOW(x)    ((((int64)(x)) & 0xffffffff))
#define MEDUSA_INT64_HIGH(x)    ((((int64)(x)) & 0xffffffff00000000))

#define MEDUSA_UINT_LOW(x)     ((((uint32)(x)) & 0xffff))
#define MEDUSA_UINT_HIGH(x)     ((((uint32)(x)) & 0xffff0000))
#define MEDUSA_UINT64_LOW(x)    ((((uint64)(x)) & 0xffffffffull))
#define MEDUSA_UINT64_HIGH(x)    ((((uint64)(x)) & 0xffffffff00000000ull))

#define MEDUSA_FLAG_HAS(flags,val) (((uint)flags&(uint)val)==(uint)val)
#define MEDUSA_FLAG_AND(flags,val) static_cast<decltype(flags)>((uint)flags & (uint)val)
#define MEDUSA_FLAG_OR(flags,val) static_cast<decltype(flags)>((uint)flags | (uint)val)
#define MEDUSA_FLAG_AND_NOT(flags,val) static_cast<decltype(flags)>((uint)flags & ~(uint)val)

#define MEDUSA_FLAG_RETURN_ENABLE(flags,val,cond) (cond)?(MEDUSA_FLAG_AND(flags,val)):(MEDUSA_FLAG_AND_NOT(flags,val))

#define MEDUSA_FLAG_ADD(flags,val) ((uint&)flags |= (uint)val)
#define MEDUSA_FLAG_REMOVE(flags,val) ((uint&)flags &= ~(uint)val)
#define MEDUSA_FLAG_ENABLE(flags,val,cond) if(cond){MEDUSA_FLAG_ADD(flags,val);}else{MEDUSA_FLAG_REMOVE(flags,val);}



#define MEDUSA_BEGIN namespace Medusa{
#define MEDUSA_END }
#define MEDUSA_PRIVATE_BEGIN namespace Medusa{namespace Private{
#define MEDUSA_PRIVATE_END }}

#define MEDUSA_CONTENT_BEGIN namespace Medusa{namespace Content{
#define MEDUSA_CONTENT_END }}

#define MEDUSA_SCRIPT_BINDING_BEGIN namespace Medusa{namespace ScriptBinding{
#define MEDUSA_SCRIPT_BINDING_END }}

#define USING_MEDUSA using namespace Medusa

//define a empty namespace to disable warning
//MEDUSA_BEGIN;
//MEDUSA_END;

