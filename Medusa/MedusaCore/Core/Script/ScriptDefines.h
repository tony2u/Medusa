// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;

#ifdef MEDUSA_SCRIPT

#define MEDUSA_SCRIPT_DECLARE(name)	namespace Script{void Register##name(asIScriptEngine* engine);}
#define MEDUSA_SCRIPT_REGISTER_BEGIN(name)	namespace Script{void Register##name(asIScriptEngine* engine){
#define MEDUSA_SCRIPT_REGISTER_END	}}

#else

#define MEDUSA_SCRIPT_DECLARE(name)	
#define MEDUSA_SCRIPT_REGISTER_BEGIN(name)	
#define MEDUSA_SCRIPT_REGISTER_END	}}

#endif
MEDUSA_END;

#ifdef MEDUSA_SCRIPT

MEDUSA_SCRIPT_BEGIN;

template<class TFrom, class TTo>
TTo* CastFromTo(TFrom* p)
{
	RETURN_NULL_IF_NULL(p);
	return dynamic_cast<TTo*>(p);
}


template<class TFrom, class TTo>
TTo* RefCastFromTo(TFrom* p)
{
	RETURN_NULL_IF_NULL(p);
	TTo* q = dynamic_cast<TTo*>(p);
	if (q != nullptr)
	{
		// Since the cast was made, we need to increase the ref counter for the returned handle
		q->AddRef();
		return q;
	}
	return nullptr;
}


#define MEDUSA_SCRIPT_REGISTER_CAST_BASE_DERIVED(engine,TBase,TDerived)\
{\
	int r = engine->RegisterObjectBehaviour(MACRO_TO_STRING(TBase), asBEHAVE_FACTORY, MACRO_TO_STRING(TDerived)"@ f()", asFUNCTION((CastFromTo<TBase, TDerived>)), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);\
	r = engine->RegisterObjectBehaviour(MACRO_TO_STRING(TDerived), asBEHAVE_FACTORY, MACRO_TO_STRING(TBase)"@ f()", asFUNCTION((CastFromTo<TDerived, TBase>)), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);\
}

#define MEDUSA_SCRIPT_REGISTER_NODE_NEW_DELETE(engine,TNode)\
{\
int r = engine->RegisterObjectBehaviour(MACRO_TO_STRING(TNode), asBEHAVE_FACTORY,  MACRO_TO_STRING(TNode)"@ f()", asFUNCTION(DefaultNewer<TNode*>::New), asCALL_CDECL); MEDUSA_ASSERT_SILENT(r >= 0);\
r = engine->RegisterObjectBehaviour(MACRO_TO_STRING(TNode), asBEHAVE_FACTORY,  MACRO_TO_STRING(TNode)"@ f(const StringRef &in)", asFUNCTIONPR((DefaultNewerById<const StringRef&, TNode*>::New), (const StringRef&), TNode*), asCALL_CDECL); MEDUSA_ASSERT_SILENT(r >= 0);\
r = engine->RegisterObjectBehaviour(MACRO_TO_STRING(TNode), asBEHAVE_FACTORY,  MACRO_TO_STRING(TNode)"@ f(const HeapString &in)", asFUNCTIONPR((DefaultNewerById<const HeapString&, TNode*>::New), (const HeapString&), TNode*), asCALL_CDECL); MEDUSA_ASSERT_SILENT(r >= 0);\
r = engine->RegisterObjectMethod(MACRO_TO_STRING(TNode), "void Delete()", asFUNCTIONPR(DefaultDeleter<TNode*>::Delete, (TNode*), void), asCALL_CDECL_OBJLAST); MEDUSA_ASSERT_SILENT(r >= 0);\
}


MEDUSA_SCRIPT_END;

#endif
