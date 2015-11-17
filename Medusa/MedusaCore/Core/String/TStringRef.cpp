// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "TStringRef.h"
#include "TStringRef.inl"
#include "Core/String/THeapString.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

MEDUSA_SCRIPT_BEGIN;
#pragma region Native



static void Construct_StringRef(StringRef *thisPointer)
{
	new(thisPointer)StringRef();
}

static void CopyConstruct_StringRef(const StringRef& str, StringRef *thisPointer)
{
	new(thisPointer)StringRef(str);
}

static void Destruct_StringRef(StringRef *thisPointer)
{
	thisPointer->~StringRef();
}

void RegisterStringRefNative(asIScriptEngine* engine)
{
	int r;
	if (engine->GetObjectTypeByName("StringRef") == nullptr)
	{
		r = engine->RegisterObjectType("StringRef", sizeof(StringRef), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}

	if (engine->GetObjectTypeByName("HeapString") == nullptr)
	{
		r = engine->RegisterObjectType("HeapString", sizeof(HeapString), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}


	r = engine->RegisterObjectBehaviour("StringRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct_StringRef), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("StringRef", asBEHAVE_CONSTRUCT, "void f(const StringRef &in)", asFUNCTION(CopyConstruct_StringRef), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("StringRef", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct_StringRef), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "bool opEquals(const StringRef &in)const", asMETHODPR(StringRef, operator ==, (const StringRef&)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int opCmp(const StringRef &in) const", asMETHODPR(StringRef, Compare, (const StringRef&)const, int), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int Compare(const StringRef &in) const", asMETHODPR(StringRef, Compare, (const StringRef&)const, int), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int Compare(const StringRef &in,bool) const", asMETHODPR(StringRef, Compare, (const StringRef&, bool)const, int), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "StringRef& opAssign(const StringRef &in)", asMETHODPR(StringRef, operator =, (const StringRef&), StringRef&), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "HeapString opAdd(const StringRef &in)const", asMETHODPR(StringRef, operator+, (const StringRef&)const, HeapString), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "HeapString opAdd(int8)const", asMETHODPR(StringRef, operator+, (char)const, HeapString), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	

	r = engine->RegisterObjectMethod("StringRef", "int8 opIndex(uint)const", asMETHODPR(StringRef, operator[], (size_t)const, char), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "StringRef SubString(uint) const", asMETHODPR(StringRef, SubString, (size_t)const, StringRef), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	//base string
	r = engine->RegisterObjectMethod("StringRef", "int8 First()const", asMETHOD(StringRef, First), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int8 Last()const", asMETHOD(StringRef, Last), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool IsEmpty()const", asMETHOD(StringRef, IsEmpty), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "uint Length()const", asMETHOD(StringRef, Length), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint get_Length()const", asMETHOD(StringRef, Length), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "void ForceUpdateLength()", asMETHOD(StringRef, ForceUpdateLength), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "void ForceSetLength(uint)", asMETHOD(StringRef, ForceSetLength), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint HashCode()const", asMETHOD(StringRef, HashCode), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(int8)const", asMETHODPR(StringRef, IndexOf, (char)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(int8,int)const", asMETHODPR(StringRef, IndexOf, (char, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(const StringRef &in)const", asMETHODPR(StringRef, IndexOf, (const StringRef&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(const StringRef &in,int)const", asMETHODPR(StringRef, IndexOf, (const StringRef&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOfAny(const StringRef &in)const", asMETHODPR(StringRef, IndexOfAny, (const StringRef&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOfAny(const StringRef &in,int)const", asMETHODPR(StringRef, IndexOfAny, (const StringRef&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int PrevIndexOf(int8)const", asMETHODPR(StringRef, PrevIndexOf, (char)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int PrevIndexOf(int8,int)const", asMETHODPR(StringRef, PrevIndexOf, (char, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(int8)const", asMETHODPR(StringRef, LastIndexOf, (char)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(int8,int)const", asMETHODPR(StringRef, LastIndexOf, (char, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(const StringRef &in)const", asMETHODPR(StringRef, LastIndexOf, (const StringRef&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(const StringRef &in,int)const", asMETHODPR(StringRef, LastIndexOf, (const StringRef&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOfAny(const StringRef &in)const", asMETHODPR(StringRef, LastIndexOfAny, (const StringRef&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOfAny(const StringRef &in,int)const", asMETHODPR(StringRef, LastIndexOfAny, (const StringRef&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool Contains(int8)const", asMETHODPR(StringRef, Contains, (char)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool Contains(const StringRef &in)const", asMETHODPR(StringRef, Contains, (const StringRef &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool ContainsAny(const StringRef &in)const", asMETHODPR(StringRef, ContainsAny, (const StringRef &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool BeginWith(const StringRef &in)const", asMETHODPR(StringRef, BeginWith, (const StringRef &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool BeginWith(int8)const", asMETHODPR(StringRef, BeginWith, (char)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool EndWith(const StringRef &in)const", asMETHODPR(StringRef, EndWith, (const StringRef &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool EndWith(int8)const", asMETHODPR(StringRef, EndWith, (char)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int ToInt()const", asMETHODPR(StringRef, ToInt, (void)const, long), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int ToInt(int)const", asMETHODPR(StringRef, ToInt, (int radix)const, long), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool TryParseInt(int &out)const", asMETHODPR(StringRef, TryParseInt, (long&)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool TryParseInt(int &out,int)const", asMETHODPR(StringRef, TryParseInt, (long&, int)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "double ToDouble()const", asMETHODPR(StringRef, ToDouble, (void)const, double), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool TryParseDouble(double &out)const", asMETHODPR(StringRef, TryParseDouble, (double&)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint Count(int8)const", asMETHODPR(StringRef, Count, (char)const, size_t), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint Count(const StringRef &in)const", asMETHODPR(StringRef, Count, (const StringRef &)const, size_t), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);




}


#pragma endregion

#pragma region Generic

static void Construct_StringRefGeneric(asIScriptGeneric * gen)
{
	new(gen->GetObject())StringRef();
}

static void CopyConstruct_StringRefGeneric(asIScriptGeneric * gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetArgObject(0));
	new(gen->GetObject())StringRef(*str);
}

static void Destruct_StringRefGeneric(asIScriptGeneric * gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	str->~StringRef();
}

static HeapString PrependChar_StringRefGeneric(asIScriptGeneric * gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));

	HeapString result(c);
	result += *str;
	return result;
}

static void Equal_StringRefGeneric(asIScriptGeneric * gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));

	*(bool*)gen->GetAddressOfReturnLocation() = (*str == *str2);
}

static void Compare_StringRefGeneric(asIScriptGeneric * gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	gen->SetReturnDWord(str->Compare(*str2));
}

static void Assign_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	*str = *str2;
	gen->SetReturnAddress(str);
}

static void Add_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	HeapString result(*str);
	result += *str2;
	gen->SetReturnObject(&result);
}

static void AddChar_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	HeapString result(*str);
	result += c;
	gen->SetReturnObject(&result);
}

static void GetChar_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	gen->SetReturnByte(str->operator[](c));
}

static void SubString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	StringRef sub = str->SubString(c);
	gen->SetReturnObject(&sub);

}

static void First_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	gen->SetReturnByte(str->First());
}


static void Last_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	gen->SetReturnByte(str->Last());
}


static void IsEmpty_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->IsEmpty();
}


static void Length_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->Length());
}

static void ForceUpdateLength_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	str->ForceUpdateLength();
}

static void ForceSetLength_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	str->ForceSetLength(c);
}

static void HashCode_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->HashCode());
}

static void IndexOf_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->IndexOf(c));
}

static void IndexOfStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->IndexOf(c, begin));
}

static void IndexOfString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->IndexOf(*str2));
}

static void IndexOfStringStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->IndexOf(*str2, begin));
}

static void IndexOfAny_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->IndexOfAny(*str2));
}

static void IndexOfAnyStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->IndexOfAny(*str2, begin));
}

static void PrevIndexOf_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->PrevIndexOf(c));
}

static void PrevIndexOfStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->PrevIndexOf(c, begin));
}

static void LastIndexOf_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->LastIndexOf(c));
}

static void LastIndexOfStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->LastIndexOf(c, begin));
}

static void LastIndexOfString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->LastIndexOf(*str2));
}

static void LastIndexOfStringStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->LastIndexOf(*str2, begin));
}


static void LastIndexOfAny_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->LastIndexOfAny(*str2));
}

static void LastIndexOfAnyStart_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->LastIndexOfAny(*str2, begin));
}


static void Contains_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Contains(c);
}

static void ContainsString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Contains(*str2);
}

static void ContainsAny_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ContainsAny(*str2);
}

static void BeginWithString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->BeginWith(*str2);
}

static void BeginWith_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->BeginWith(c);
}

static void EndWithString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->EndWith(*str2);
}

static void EndWith_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->EndWith(c);
}

static void ToInt_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->ToInt());
}

static void ToIntRadix_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	int radix = static_cast<int>(gen->GetArgDWord(0));
	gen->SetReturnDWord((uint)str->ToInt(radix));
}

static void TryParseInt_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	long outResult=0;
	bool result = str->TryParseInt(outResult);
	*(long*)gen->GetArgAddress(0) = outResult;
	*(bool*)gen->GetAddressOfReturnLocation() = result;
}
static void TryParseIntRadix_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	int radix = static_cast<int>(gen->GetArgDWord(1));

	long outResult=0;
	bool result = str->TryParseInt(outResult, radix);
	*(long*)gen->GetArgAddress(0) = outResult;
	*(bool*)gen->GetAddressOfReturnLocation() = result;
}

static void ToDouble_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	gen->SetReturnDouble(str->ToDouble());
}
static void TryParseDouble_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	double outResult=0.0;
	bool result = str->TryParseDouble(outResult);
	*(double*)gen->GetArgAddress(0) = outResult;
	*(bool*)gen->GetAddressOfReturnLocation() = result;
}

static void Count_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->Count(c));
}

static void CountString_StringRefGeneric(asIScriptGeneric *gen)
{
	StringRef* str = static_cast<StringRef *>(gen->GetObject());
	StringRef* str2 = static_cast<StringRef *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->Count(*str2));
}



void RegisterStringRefGeneric(asIScriptEngine* engine)
{
	int r;
	if (engine->GetObjectTypeByName("StringRef") == nullptr)
	{
		r = engine->RegisterObjectType("StringRef", sizeof(StringRef), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}

	if (engine->GetObjectTypeByName("HeapString") == nullptr)
	{
		r = engine->RegisterObjectType("HeapString", sizeof(HeapString), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}


	r = engine->RegisterObjectBehaviour("StringRef", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("StringRef", asBEHAVE_CONSTRUCT, "void f(const StringRef &in)", asFUNCTION(CopyConstruct_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("StringRef", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "bool opEquals(const StringRef &in)const", asFUNCTION(Equal_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int opCmp(const StringRef &in) const", asFUNCTION(Compare_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int Compare(const StringRef &in) const", asFUNCTION(Compare_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "StringRef& opAssign(const StringRef &in)", asFUNCTION(Assign_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "HeapString opAdd(const StringRef &in)const", asFUNCTION(Add_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "HeapString opAdd(int8)const", asFUNCTION(AddChar_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	


	r = engine->RegisterObjectMethod("StringRef", "int8 opIndex(uint)const", asFUNCTION(GetChar_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "StringRef SubString(uint) const", asFUNCTION(SubString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	//base string
	r = engine->RegisterObjectMethod("StringRef", "int8 First()const", asFUNCTION(First_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int8 Last()const", asFUNCTION(Last_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool IsEmpty()const", asFUNCTION(IsEmpty_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("StringRef", "uint Length()const", asFUNCTION(Length_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint get_Length()const", asFUNCTION(Length_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "void ForceUpdateLength()", asFUNCTION(ForceUpdateLength_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "void ForceSetLength(uint)", asFUNCTION(ForceSetLength_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint HashCode()const", asFUNCTION(HashCode_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(int8)const", asFUNCTION(IndexOf_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(int8,int)const", asFUNCTION(IndexOfStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(const StringRef &in)const", asFUNCTION(IndexOfString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOf(const StringRef &in,int)const", asFUNCTION(IndexOfStringStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOfAny(const StringRef &in)const", asFUNCTION(IndexOfAny_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int IndexOfAny(const StringRef &in,int)const", asFUNCTION(IndexOfAnyStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int PrevIndexOf(int8)const", asFUNCTION(PrevIndexOf_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int PrevIndexOf(int8,int)const", asFUNCTION(PrevIndexOfStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(int8)const", asFUNCTION(LastIndexOf_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(int8,int)const", asFUNCTION(LastIndexOfStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(const StringRef &in)const", asFUNCTION(LastIndexOfString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOf(const StringRef &in,int)const", asFUNCTION(LastIndexOfStringStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOfAny(const StringRef &in)const", asFUNCTION(LastIndexOfAny_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int LastIndexOfAny(const StringRef &in,int)const", asFUNCTION(LastIndexOfAnyStart_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool Contains(int8)const", asFUNCTION(Contains_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool Contains(const StringRef &in)const", asFUNCTION(ContainsString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool ContainsAny(const StringRef &in)const", asFUNCTION(ContainsAny_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool BeginWith(const StringRef &in)const", asFUNCTION(BeginWithString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool BeginWith(int8)const", asFUNCTION(BeginWith_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool EndWith(const StringRef &in)const", asFUNCTION(EndWithString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool EndWith(int8)const", asFUNCTION(EndWith_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "int ToInt()const", asFUNCTION(ToInt_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "int ToInt(int)const", asFUNCTION(ToIntRadix_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("StringRef", "bool TryParseInt(int &out)const", asFUNCTION(TryParseInt_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool TryParseInt(int &out,int)const", asFUNCTION(TryParseIntRadix_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "double ToDouble()const", asFUNCTION(ToDouble_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "bool TryParseDouble(double &out)const", asFUNCTION(TryParseDouble_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint Count(int8)const", asFUNCTION(Count_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("StringRef", "uint Count(const StringRef &in)const", asFUNCTION(CountString_StringRefGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);




}

#pragma endregion
void RegisterStringRef(asIScriptEngine * engine)
{
	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
		RegisterStringRefGeneric(engine);
	else
		RegisterStringRefNative(engine);
}


MEDUSA_SCRIPT_END;

#endif

