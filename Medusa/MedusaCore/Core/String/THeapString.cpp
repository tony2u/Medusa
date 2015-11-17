// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "THeapString.h"

#ifdef MEDUSA_SCRIPT
#include "CoreLib/Common/angelscript.h"

#if AS_USE_STRINGPOOL==1
#include "Core/String/Pool/StringPool.h"
#endif

MEDUSA_SCRIPT_BEGIN;

#pragma region Native



static void Construct_HeapString(HeapString *thisPointer)
{
	new(thisPointer)HeapString();
}

static void ConstructWithStringRef_HeapString(const StringRef& str, HeapString *thisPointer)
{
	new(thisPointer)HeapString(str);
}


static void ConstructWithSize_HeapString(uint size, HeapString *thisPointer)
{
	new(thisPointer)HeapString(size,false);
}


static void CopyConstruct_HeapString(const HeapString& str, HeapString *thisPointer)
{
	new(thisPointer)HeapString(str);
}

static void Destruct_HeapString(HeapString *thisPointer)
{
	thisPointer->~HeapString();
}


#if AS_USE_STRINGPOOL==1

static const HeapString& HeapStringFactory(asUINT length, const char *str)
{
	return StringPool::Instance().Create(str, length);
}

static void CleanupEngineStringPool(asIScriptEngine *engine)
{
	StringPool::Instance().Uninitialize();
}
#else
static HeapString HeapStringFactory(asUINT length, const char *str)
{
	return HeapString(str, length);
}

#endif


void RegisterHeapStringNative(asIScriptEngine* engine)
{
	int r;

	if (engine->GetObjectTypeByName("HeapString") == nullptr)
	{
		r = engine->RegisterObjectType("HeapString", sizeof(HeapString), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}

	if (engine->GetObjectTypeByName("StringRef") == nullptr)
	{
		r = engine->RegisterObjectType("StringRef", sizeof(StringRef), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}

#if AS_USE_STRINGPOOL==1
	r = engine->RegisterStringFactory("const HeapString&", asFUNCTION(HeapStringFactory), asCALL_CDECL); MEDUSA_ASSERT_SILENT(r >= 0);
	engine->SetEngineUserDataCleanupCallback(CleanupEngineStringPool, 1001);
#else
	r = engine->RegisterStringFactory("HeapString", asFUNCTION(HeapStringFactory), asCALL_CDECL); MEDUSA_ASSERT_SILENT(r >= 0);
#endif

	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct_HeapString), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f(const StringRef &in)", asFUNCTION(Construct_HeapString), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructWithSize_HeapString), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f(const HeapString &in)", asFUNCTION(CopyConstruct_HeapString), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct_HeapString), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "StringRef ToString() const", asMETHODPR(HeapString, ToString, ()const, StringRef), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool opEquals(const HeapString &in)const", asMETHODPR(HeapString, operator ==, (const HeapString&)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int opCmp(const HeapString &in) const", asMETHODPR(HeapString, Compare, (const HeapString&)const, int), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int Compare(const HeapString &in) const", asMETHODPR(HeapString, Compare, (const HeapString&)const, int), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int Compare(const HeapString &in,bool) const", asMETHODPR(HeapString, Compare, (const HeapString&, bool)const, int), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "HeapString& opAssign(const HeapString &in)", asMETHODPR(HeapString, operator =, (const HeapString&), HeapString&), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString& opAddAssign(const HeapString &in)", asMETHODPR(HeapString, operator+=, (const HeapString&), HeapString&), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString& opAddAssign(int8)", asMETHODPR(HeapString, operator+=, (char), HeapString&), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "HeapString opAdd(const HeapString &in)const", asMETHODPR(HeapString, operator+, (const HeapString&)const, HeapString), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString opAdd(int8)const", asMETHODPR(HeapString, operator+, (char)const, HeapString), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	


	r = engine->RegisterObjectMethod("HeapString", "int8& opIndex(uint)", asMETHODPR(HeapString, operator[], (size_t), char&), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int8 opIndex(uint)const", asMETHODPR(HeapString, operator[], (size_t)const, char), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "HeapString SubString(uint) const", asMETHODPR(HeapString, SubString, (size_t)const, HeapString), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString SubString(uint,uint) const", asMETHODPR(HeapString, SubString, (size_t,size_t)const, HeapString), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool ReserveSize(uint)", asMETHOD(HeapString, ReserveSize), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReserveLength(uint)", asMETHOD(HeapString, ReserveLength), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ReleaseExtraSize()", asMETHOD(HeapString, ReleaseExtraSize), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	//base string
	r = engine->RegisterObjectMethod("HeapString", "void Clear()", asMETHOD(HeapString, Clear), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int8 First()const", asMETHOD(HeapString, First), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int8 Last()const", asMETHOD(HeapString, Last), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool IsEmpty()const", asMETHOD(HeapString, IsEmpty), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "uint Size()const", asMETHOD(HeapString, Size), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint get_Size()const", asMETHOD(HeapString, Size), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "uint Length()const", asMETHOD(HeapString, Length), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint get_Length()const", asMETHOD(HeapString, Length), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ForceUpdateLength()", asMETHOD(HeapString, ForceUpdateLength), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ForceSetLength(uint)", asMETHOD(HeapString, ForceSetLength), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint HashCode()const", asMETHOD(HeapString, HashCode), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(int8)const", asMETHODPR(HeapString, IndexOf,(char)const,intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(int8,int)const", asMETHODPR(HeapString, IndexOf, (char,intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(const HeapString &in)const", asMETHODPR(HeapString, IndexOf, (const HeapString&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(const HeapString &in,int)const", asMETHODPR(HeapString, IndexOf, (const HeapString&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOfAny(const HeapString &in)const", asMETHODPR(HeapString, IndexOfAny, (const HeapString&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOfAny(const HeapString &in,int)const", asMETHODPR(HeapString, IndexOfAny, (const HeapString&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int PrevIndexOf(int8)const", asMETHODPR(HeapString, PrevIndexOf, (char)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int PrevIndexOf(int8,int)const", asMETHODPR(HeapString, PrevIndexOf, (char, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(int8)const", asMETHODPR(HeapString, LastIndexOf, (char)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(int8,int)const", asMETHODPR(HeapString, LastIndexOf, (char, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(const HeapString &in)const", asMETHODPR(HeapString, LastIndexOf, (const HeapString&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(const HeapString &in,int)const", asMETHODPR(HeapString, LastIndexOf, (const HeapString&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOfAny(const HeapString &in)const", asMETHODPR(HeapString, LastIndexOfAny, (const HeapString&)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOfAny(const HeapString &in,int)const", asMETHODPR(HeapString, LastIndexOfAny, (const HeapString&, intp)const, intp), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool Contains(int8)const", asMETHODPR(HeapString, Contains,(char)const,bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Contains(const HeapString &in)const", asMETHODPR(HeapString, Contains, (const HeapString &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ContainsAny(const HeapString &in)const", asMETHODPR(HeapString, ContainsAny, (const HeapString &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool BeginWith(const HeapString &in)const", asMETHODPR(HeapString, BeginWith, (const HeapString &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool BeginWith(int8)const", asMETHODPR(HeapString, BeginWith, (char)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool EndWith(const HeapString &in)const", asMETHODPR(HeapString, EndWith, (const HeapString &)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool EndWith(int8)const", asMETHODPR(HeapString, EndWith, (char)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int ToInt()const", asMETHODPR(HeapString, ToInt, (void)const, long), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int ToInt(int)const", asMETHODPR(HeapString, ToInt, (int radix)const, long), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool TryParseInt(int &out)const", asMETHODPR(HeapString, TryParseInt, (long&)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TryParseInt(int &out,int)const", asMETHODPR(HeapString, TryParseInt, (long&, int)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "double ToDouble()const", asMETHODPR(HeapString, ToDouble, (void)const, double), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TryParseDouble(double &out)const", asMETHODPR(HeapString, TryParseDouble, (double&)const, bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint Count(int8)const", asMETHODPR(HeapString, Count, (char)const, size_t), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint Count(const HeapString &in)const", asMETHODPR(HeapString, Count, (const HeapString &)const, size_t), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "void CopyTo(HeapString &out)const", asMETHODPR(HeapString, CopyTo, (HeapString &)const, void), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "void ToCase(bool)", asMETHOD(HeapString, ToCase), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ToUpper()", asMETHOD(HeapString, ToUpper), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ToLower()", asMETHOD(HeapString, ToLower), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void Reverse()", asMETHOD(HeapString, Reverse), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceAllTo(int8)", asMETHOD(HeapString, ReplaceAllTo), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceTo(int8,uint)", asMETHOD(HeapString, ReplaceTo), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceAll(int8,int8)", asMETHODPR(HeapString, ReplaceAll, (char, char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceFirst(int8,int8)", asMETHODPR(HeapString, ReplaceFirst, (char, char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceLast(int8,int8)", asMETHODPR(HeapString, ReplaceLast, (char, char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceAll(const HeapString &in,const HeapString &in)", asMETHODPR(HeapString, ReplaceAll,(const HeapString&,const HeapString&),bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceFirst(const HeapString &in,const HeapString &in)", asMETHODPR(HeapString, ReplaceFirst, (const HeapString&, const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceLast(const HeapString &in,const HeapString &in)", asMETHODPR(HeapString, ReplaceLast, (const HeapString&, const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBeginAny(const HeapString &in)", asMETHODPR(HeapString, RemoveBeginAny, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBeginAnyExclude(const HeapString &in)", asMETHODPR(HeapString, RemoveBeginAnyExclude, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBegin(int8)", asMETHOD(HeapString, RemoveBegin), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBeginExclude(int8)", asMETHOD(HeapString, RemoveBeginExclude), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEnd(int8)", asMETHOD(HeapString, RemoveEnd), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEndExclude(int8)", asMETHOD(HeapString, RemoveEndExclude), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEndAny(const HeapString &in)", asMETHODPR(HeapString, RemoveEndAny, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEndAnyExclude(const HeapString &in)", asMETHODPR(HeapString, RemoveEndAnyExclude, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool Append(int8)", asMETHODPR(HeapString, Append,(char),bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Append(int8,uint)", asMETHODPR(HeapString, Append, (char,size_t), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Append(const HeapString &in)", asMETHODPR(HeapString, Append, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine()", asMETHODPR(HeapString, AppendLine, (), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine(int8)", asMETHODPR(HeapString, AppendLine, (char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine(int8,uint)", asMETHODPR(HeapString, AppendLine, (char,size_t), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine(const HeapString &in)", asMETHODPR(HeapString, AppendLine, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool Push(int8)", asMETHODPR(HeapString, Push, (char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Push(int8,uint)", asMETHODPR(HeapString, Push, (char, size_t), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Push(const HeapString &in)", asMETHODPR(HeapString, Push, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool Insert(uint,int8)", asMETHODPR(HeapString, Insert, (size_t,char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Insert(uint,int8,uint)", asMETHODPR(HeapString, Insert, (size_t, char,size_t), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Insert(uint,const HeapString &in)", asMETHODPR(HeapString, Insert, (uintp,const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAll(int8)", asMETHODPR(HeapString, RemoveAll, (char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFirst()", asMETHODPR(HeapString, RemoveFirst, (), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFirst(int8)", asMETHODPR(HeapString, RemoveFirst, (char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveLast(int8)", asMETHODPR(HeapString, RemoveLast, (char), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveLast()", asMETHODPR(HeapString, RemoveLast, (), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAt(uint)", asMETHODPR(HeapString, RemoveAt, (uintp), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAt(uint,uint)", asMETHODPR(HeapString, RemoveAt, (uintp,uintp), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFrom(uint)", asMETHODPR(HeapString, RemoveFrom, (uintp), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAll(const HeapString &in)", asMETHODPR(HeapString, RemoveAll, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFirst(const HeapString &in)", asMETHODPR(HeapString, RemoveFirst, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveLast(const HeapString &in)", asMETHODPR(HeapString, RemoveLast, (const HeapString&), bool), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool TrimAll()", asMETHOD(HeapString, TrimAll), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TrimBegin()", asMETHOD(HeapString, TrimBegin), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TrimEnd()", asMETHOD(HeapString, TrimEnd), asCALL_THISCALL); MEDUSA_ASSERT_SILENT(r >= 0);

}


#pragma endregion

#pragma region Generic

#if AS_USE_STRINGPOOL==1

static void HeapStringFactory_Generic(asIScriptGeneric * gen)
{
	asUINT length = gen->GetArgDWord(0);
	const char *str = (const char*)gen->GetArgAddress(1);

	const HeapString& obj= StringPool::Instance().Create(str, length);
    gen->SetReturnAddress((void*)&obj);
    
}

#else
static void HeapStringFactory_Generic(asIScriptGeneric * gen)
{
	asUINT length = gen->GetArgDWord(0);
	const char *str = (const char*)gen->GetArgAddress(1);
    new(gen->GetAddressOfReturnLocation()) HeapString(str, length);
}

#endif

static void Construct_HeapStringGeneric(asIScriptGeneric * gen)
{
	new(gen->GetObject())HeapString();
}

static void ConstructWithSize_HeapStringGeneric(asIScriptGeneric * gen)
{
    size_t c = static_cast<size_t>(gen->GetArgDWord(0));
    new(gen->GetObject())HeapString(c,false);
}

static void CopyConstruct_HeapStringGeneric(asIScriptGeneric * gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetArgObject(0));
	new(gen->GetObject())HeapString(*str);
}

static void Destruct_HeapStringGeneric(asIScriptGeneric * gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->~HeapString();
}


static void ToStringRef_HeapStringGeneric(asIScriptGeneric * gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	StringRef ref = str->ToString();
	gen->SetReturnObject(&ref);
}


static void Equal_HeapStringGeneric(asIScriptGeneric * gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));

	*(bool*)gen->GetAddressOfReturnLocation() = (*str == *str2);
}

static void Compare_HeapStringGeneric(asIScriptGeneric * gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	gen->SetReturnDWord(str->Compare(*str2));
}

static void CompareCase_HeapStringGeneric(asIScriptGeneric * gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	bool b=*(bool*)gen->GetArgAddress(1);
	gen->SetReturnDWord(str->Compare(*str2,b));
}


static void Assign_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	*str = *str2;
	gen->SetReturnAddress(str);
}

static void AddAssign_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	*str += *str2;
	gen->SetReturnAddress(str);
}

static void AddAssignChar_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*str += c;
	gen->SetReturnAddress(str);
}


static void Add_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	HeapString result(*str);
	result += *str2;
	gen->SetReturnObject(&result);
}

static void AddChar_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	HeapString result(*str);
	result += c;
	gen->SetReturnObject(&result);
}

static void GetChar_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	gen->SetReturnByte(str->operator[](c));
}

static void MutableChar_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	gen->SetReturnAddress(str->MutableBuffer()+c);
}


static void SubString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	HeapString sub = str->SubString(c);
	gen->SetReturnObject(&sub);
}

static void SubStringWithLength_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	uint c2 = static_cast<uint>(gen->GetArgDWord(1));
	HeapString sub = str->SubString(c,c2);
	gen->SetReturnObject(&sub);
}

static void First_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnByte(str->First());
}


static void Last_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnByte(str->Last());
}


static void IsEmpty_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->IsEmpty();
}



static void Length_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->Length());
}

static void ForceUpdateLength_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->ForceUpdateLength();
}

static void ForceSetLength_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	str->ForceSetLength(c);
}

static void HashCode_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->HashCode());
}

static void IndexOf_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->IndexOf(c));
}

static void IndexOfStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->IndexOf(c, begin));
}

static void IndexOfString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->IndexOf(*str2));
}

static void IndexOfStringStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->IndexOf(*str2, begin));
}

static void IndexOfAny_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->IndexOfAny(*str2));
}

static void IndexOfAnyStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->IndexOfAny(*str2, begin));
}

static void PrevIndexOf_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->PrevIndexOf(c));
}

static void PrevIndexOfStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->PrevIndexOf(c, begin));
}

static void LastIndexOf_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->LastIndexOf(c));
}

static void LastIndexOfStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->LastIndexOf(c, begin));
}

static void LastIndexOfString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->LastIndexOf(*str2));
}

static void LastIndexOfStringStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->LastIndexOf(*str2, begin));
}


static void LastIndexOfAny_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->LastIndexOfAny(*str2));
}

static void LastIndexOfAnyStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	int begin = static_cast<int>(gen->GetArgDWord(1));

	gen->SetReturnDWord((uint)str->LastIndexOfAny(*str2, begin));
}


static void Contains_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Contains(c);
}

static void ContainsString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Contains(*str2);
}

static void ContainsAny_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ContainsAny(*str2);
}

static void BeginWithString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->BeginWith(*str2);
}

static void BeginWith_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->BeginWith(c);
}

static void EndWithString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->EndWith(*str2);
}

static void EndWith_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->EndWith(c);
}

static void ToInt_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->ToInt());
}

static void ToIntRadix_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	int radix = static_cast<int>(gen->GetArgDWord(0));
	gen->SetReturnDWord((uint)str->ToInt(radix));
}

static void TryParseInt_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	long outResult=0;
	bool result = str->TryParseInt(outResult);
	*(long*)gen->GetArgAddress(0) = outResult;
	*(bool*)gen->GetAddressOfReturnLocation() = result;
}
static void TryParseIntRadix_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	int radix = static_cast<int>(gen->GetArgDWord(1));

	long outResult=0;
	bool result = str->TryParseInt(outResult, radix);
	*(long*)gen->GetArgAddress(0) = outResult;
	*(bool*)gen->GetAddressOfReturnLocation() = result;
}

static void ToDouble_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnDouble(str->ToDouble());
}
static void TryParseDouble_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	double outResult=0;
	bool result = str->TryParseDouble(outResult);
	*(double*)gen->GetArgAddress(0) = outResult;
	*(bool*)gen->GetAddressOfReturnLocation() = result;
}

static void Count_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	gen->SetReturnDWord((uint)str->Count(c));
}

static void CountString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgObject(0));
	gen->SetReturnDWord((uint)str->Count(*str2));
}

static void Size_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	gen->SetReturnDWord((uint)str->Size());
}

static void Clear_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->Clear();
}

static void ReserveSize_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReserveSize(c);
}


static void ReserveLength_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint c = static_cast<uint>(gen->GetArgDWord(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReserveLength(c);
}

static void ReleaseExtraSize_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->ReleaseExtraSize();
}

static void CopyTo_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str2= static_cast<HeapString *>(gen->GetArgAddress(0));
	str->CopyTo(*str2);
}

static void ToCase_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	bool* toCase = static_cast<bool *>(gen->GetArgAddress(0));
	str->ToCase(*toCase);
}


static void ToUpper_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->ToUpper();
}

static void ToLower_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->ToLower();
}

static void Reverse_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	str->Reverse();
}

static void ReplaceAllTo_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceAllTo(c);
}
static void ReplaceToStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	uint s = static_cast<uint>(gen->GetArgDWord(1));

	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceTo(c,s);
}

static void ReplaceAll_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	char c2 = static_cast<char>(gen->GetArgByte(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceAll(c,c2);
}

static void ReplaceFirst_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	char c2 = static_cast<char>(gen->GetArgByte(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceFirst(c, c2);
}

static void ReplaceLast_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	char c2 = static_cast<char>(gen->GetArgByte(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceLast(c, c2);
}

static void ReplaceAllString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgAddress(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceAll(*str1, *str2);
}

static void ReplaceFirstString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgAddress(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceFirst(*str1, *str2);
}
static void ReplaceLastString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	HeapString* str2 = static_cast<HeapString *>(gen->GetArgAddress(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->ReplaceLast(*str1, *str2);
}

static void RemoveBeginAny_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveBeginAny(*str1);
}
static void RemoveBeginAnyExclude_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveBeginAnyExclude(*str1);
}

static void RemoveEndAny_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveEndAny(*str1);
}
static void RemoveEndAnyExclude_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveEndAnyExclude(*str1);
}

static void RemoveBegin_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveBegin(c);
}

static void RemoveBeginExclude_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveBeginExclude(c);
}

static void RemoveEnd_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveEnd(c);
}

static void RemoveEndExclude_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveEndExclude(c);
}

static void Append_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Append(c);
}

static void AppendStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	uint i = static_cast<uint>(gen->GetArgDWord(1));

	*(bool*)gen->GetAddressOfReturnLocation() = str->Append(c,i);
}

static void AppendString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Append(*str1);
}

static void AppendLineEmpty_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->AppendLine();
}

static void AppendLine_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->AppendLine(c);
}

static void AppendLineStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	uint i = static_cast<uint>(gen->GetArgDWord(1));

	*(bool*)gen->GetAddressOfReturnLocation() = str->AppendLine(c, i);
}

static void AppendLineString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->AppendLine(*str1);
}


static void Push_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Push(c);
}

static void PushStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	uint i = static_cast<uint>(gen->GetArgDWord(1));

	*(bool*)gen->GetAddressOfReturnLocation() = str->Push(c, i);
}

static void PushString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Push(*str1);
}

static void Insert_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	size_t i = static_cast<size_t>(gen->GetArgDWord(0));
	char c = static_cast<char>(gen->GetArgByte(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Insert(i,c);
}

static void InsertStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint i = static_cast<uint>(gen->GetArgDWord(0));
	char c = static_cast<char>(gen->GetArgByte(1));
	uint count = static_cast<uint>(gen->GetArgDWord(2));

	*(bool*)gen->GetAddressOfReturnLocation() = str->Insert(i,c, count);
}

static void InsertString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint i = static_cast<uint>(gen->GetArgDWord(0));
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->Insert(i,*str1);
}

static void RemoveAll_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveAll(c);
}

static void RemoveFirst_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveFirst();
}

static void RemoveFirstChar_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveFirst(c);
}

static void RemoveLast_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveLast();
}

static void RemoveLastChar_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	char c = static_cast<char>(gen->GetArgByte(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveLast(c);
}

static void RemoveAt_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint i = static_cast<uint>(gen->GetArgDWord(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveAt(i);
}

static void RemoveAtStart_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint i = static_cast<uint>(gen->GetArgDWord(0));
	uint count = static_cast<uint>(gen->GetArgDWord(1));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveAt(i,count);
}

static void RemoveFrom_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	uint i = static_cast<uint>(gen->GetArgDWord(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveFrom(i);
}

static void RemoveAllString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveAll(*str1);
}

static void RemoveFirstString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveFirst(*str1);
}

static void RemoveLastString_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	HeapString* str1 = static_cast<HeapString *>(gen->GetArgAddress(0));
	*(bool*)gen->GetAddressOfReturnLocation() = str->RemoveLast(*str1);
}

static void TrimAll_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->TrimAll();
}

static void TrimBegin_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->TrimBegin();
}

static void TrimEnd_HeapStringGeneric(asIScriptGeneric *gen)
{
	HeapString* str = static_cast<HeapString *>(gen->GetObject());
	*(bool*)gen->GetAddressOfReturnLocation() = str->TrimEnd();
}

void RegisterHeapStringGeneric(asIScriptEngine* engine)
{
	int r;

	if (engine->GetObjectTypeByName("HeapString") == nullptr)
	{
		r = engine->RegisterObjectType("HeapString", sizeof(HeapString), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}

	if (engine->GetObjectTypeByName("StringRef") == nullptr)
	{
		r = engine->RegisterObjectType("StringRef", sizeof(StringRef), asOBJ_VALUE | asOBJ_APP_CLASS_CDAK); MEDUSA_ASSERT_SILENT(r >= 0);
	}

#if AS_USE_STRINGPOOL==1
	r = engine->RegisterStringFactory("const HeapString&", asFUNCTION(HeapStringFactory_Generic), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	engine->SetEngineUserDataCleanupCallback(CleanupEngineStringPool, 1001);
#else
	r = engine->RegisterStringFactory("HeapString", asFUNCTION(HeapStringFactory_Generic), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
#endif

	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(Construct_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f(const StringRef &in)", asFUNCTION(Construct_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(ConstructWithSize_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_CONSTRUCT, "void f(const HeapString &in)", asFUNCTION(CopyConstruct_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectBehaviour("HeapString", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(Destruct_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "StringRef ToString() const", asFUNCTION(ToStringRef_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool opEquals(const HeapString &in)const", asFUNCTION(Equal_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int opCmp(const HeapString &in) const", asFUNCTION(Compare_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int Compare(const HeapString &in) const", asFUNCTION(Compare_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int Compare(const HeapString &in,bool) const", asFUNCTION(CompareCase_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "HeapString& opAssign(const HeapString &in)", asFUNCTION(Assign_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString& opAddAssign(const HeapString &in)", asFUNCTION(AddAssign_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString& opAddAssign(int8)", asFUNCTION(AddAssignChar_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "HeapString opAdd(const HeapString &in)const", asFUNCTION(Add_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString opAdd(int8)const", asFUNCTION(AddChar_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	
	r = engine->RegisterObjectMethod("HeapString", "int8& opIndex(uint)", asFUNCTION(MutableChar_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int8 opIndex(uint)const", asFUNCTION(GetChar_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "HeapString SubString(uint) const", asFUNCTION(SubString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "HeapString SubString(uint,uint) const", asFUNCTION(SubStringWithLength_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	

	//base string
	
	r = engine->RegisterObjectMethod("HeapString", "int8 First()const", asFUNCTION(First_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int8 Last()const", asFUNCTION(Last_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool IsEmpty()const", asFUNCTION(IsEmpty_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	

	r = engine->RegisterObjectMethod("HeapString", "uint Length()const", asFUNCTION(Length_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint get_Length()const", asFUNCTION(Length_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ForceUpdateLength()", asFUNCTION(ForceUpdateLength_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ForceSetLength(uint)", asFUNCTION(ForceSetLength_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint HashCode()const", asFUNCTION(HashCode_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(int8)const", asFUNCTION(IndexOf_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(int8,int)const", asFUNCTION(IndexOfStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(const HeapString &in)const", asFUNCTION(IndexOfString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOf(const HeapString &in,int)const", asFUNCTION(IndexOfStringStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOfAny(const HeapString &in)const", asFUNCTION(IndexOfAny_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int IndexOfAny(const HeapString &in,int)const", asFUNCTION(IndexOfAnyStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int PrevIndexOf(int8)const", asFUNCTION(PrevIndexOf_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int PrevIndexOf(int8,int)const", asFUNCTION(PrevIndexOfStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(int8)const", asFUNCTION(LastIndexOf_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(int8,int)const", asFUNCTION(LastIndexOfStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(const HeapString &in)const", asFUNCTION(LastIndexOfString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOf(const HeapString &in,int)const", asFUNCTION(LastIndexOfStringStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOfAny(const HeapString &in)const", asFUNCTION(LastIndexOfAny_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int LastIndexOfAny(const HeapString &in,int)const", asFUNCTION(LastIndexOfAnyStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool Contains(int8)const", asFUNCTION(Contains_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Contains(const HeapString &in)const", asFUNCTION(ContainsString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ContainsAny(const HeapString &in)const", asFUNCTION(ContainsAny_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool BeginWith(const HeapString &in)const", asFUNCTION(BeginWithString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool BeginWith(int8)const", asFUNCTION(BeginWith_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool EndWith(const HeapString &in)const", asFUNCTION(EndWithString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool EndWith(int8)const", asFUNCTION(EndWith_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "int ToInt()const", asFUNCTION(ToInt_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "int ToInt(int)const", asFUNCTION(ToIntRadix_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool TryParseInt(int &out)const", asFUNCTION(TryParseInt_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TryParseInt(int &out,int)const", asFUNCTION(TryParseIntRadix_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "double ToDouble()const", asFUNCTION(ToDouble_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TryParseDouble(double &out)const", asFUNCTION(TryParseDouble_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint Count(int8)const", asFUNCTION(Count_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint Count(const HeapString &in)const", asFUNCTION(CountString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	
	r = engine->RegisterObjectMethod("HeapString", "uint Size()const", asFUNCTION(Size_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "uint get_Size()const", asFUNCTION(Size_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void Clear()", asFUNCTION(Clear_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReserveSize(uint)", asFUNCTION(ReserveSize_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReserveLength(uint)", asFUNCTION(ReserveLength_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ReleaseExtraSize()", asFUNCTION(ReleaseExtraSize_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "void CopyTo(HeapString &out)const", asFUNCTION(CopyTo_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "void ToCase(bool)", asFUNCTION(ToCase_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ToUpper()", asFUNCTION(ToUpper_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void ToLower()", asFUNCTION(ToLower_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "void Reverse()", asFUNCTION(Reverse_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceAllTo(int8)", asFUNCTION(ReplaceAllTo_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceTo(int8,uint)", asFUNCTION(ReplaceToStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceAll(int8,int8)", asFUNCTION(ReplaceAll_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceFirst(int8,int8)", asFUNCTION(ReplaceFirst_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceLast(int8,int8)", asFUNCTION(ReplaceLast_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceAll(const HeapString &in,const HeapString &in)", asFUNCTION(ReplaceAllString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceFirst(const HeapString &in,const HeapString &in)", asFUNCTION(ReplaceFirstString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool ReplaceLast(const HeapString &in,const HeapString &in)", asFUNCTION(ReplaceLastString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBeginAny(const HeapString &in)", asFUNCTION(RemoveBeginAny_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBeginAnyExclude(const HeapString &in)", asFUNCTION(RemoveBeginAnyExclude_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBegin(int8)", asFUNCTION(RemoveBegin_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveBeginExclude(int8)", asFUNCTION(RemoveBeginExclude_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEnd(int8)", asFUNCTION(RemoveEnd_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEndExclude(int8)", asFUNCTION(RemoveEndExclude_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEndAny(const HeapString &in)", asFUNCTION(RemoveEndAny_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveEndAnyExclude(const HeapString &in)", asFUNCTION(RemoveEndAnyExclude_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool Append(int8)", asFUNCTION(Append_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Append(int8,uint)", asFUNCTION(AppendStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Append(const HeapString &in)", asFUNCTION(AppendString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine()", asFUNCTION(AppendLineEmpty_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine(int8)", asFUNCTION(AppendLine_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine(int8,uint)", asFUNCTION(AppendLineStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool AppendLine(const HeapString &in)", asFUNCTION(AppendLineString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool Push(int8)", asFUNCTION(Push_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Push(int8,uint)", asFUNCTION(PushStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Push(const HeapString &in)", asFUNCTION(PushString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool Insert(uint,int8)", asFUNCTION(Insert_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Insert(uint,int8,uint)", asFUNCTION(InsertStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool Insert(uint,const HeapString &in)", asFUNCTION(InsertString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAll(int8)", asFUNCTION(RemoveAll_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFirst()", asFUNCTION(RemoveFirst_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFirst(int8)", asFUNCTION(RemoveFirstChar_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveLast(int8)", asFUNCTION(RemoveLast_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveLast()", asFUNCTION(RemoveLastChar_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAt(uint)", asFUNCTION(RemoveAt_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAt(uint,uint)", asFUNCTION(RemoveAtStart_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFrom(uint)", asFUNCTION(RemoveFrom_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveAll(const HeapString &in)", asFUNCTION(RemoveAllString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveFirst(const HeapString &in)", asFUNCTION(RemoveFirstString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool RemoveLast(const HeapString &in)", asFUNCTION(RemoveLastString_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);


	r = engine->RegisterObjectMethod("HeapString", "bool TrimAll()", asFUNCTION(TrimAll_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TrimBegin()", asFUNCTION(TrimBegin_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);
	r = engine->RegisterObjectMethod("HeapString", "bool TrimEnd()", asFUNCTION(TrimEnd_HeapStringGeneric), asCALL_GENERIC); MEDUSA_ASSERT_SILENT(r >= 0);

}

#pragma endregion

void RegisterHeapString(asIScriptEngine * engine)
{
	if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
		RegisterHeapStringGeneric(engine);
	else
		RegisterHeapStringNative(engine);
}


MEDUSA_SCRIPT_END;

#endif

