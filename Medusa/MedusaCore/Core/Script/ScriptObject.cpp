// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_SCRIPT

#include "Core/IO/FileSystem.h"
#include "Core/IO/File.h"
#include "Core/Script/ScriptObject.h"
#include "Core/Script/ScriptEngine.h"
#include "Core/Log/Log.h"
#include "CoreLib/Common/angelscript.h"

MEDUSA_BEGIN;

ScriptObject::ScriptObject(asIScriptObject* scriptObject)
	:mScriptObject(scriptObject)
{
	Log::AssertNotNull(scriptObject, "scriptObject");
	mScriptObject->AddRef();
	CacheMemberAddresses();

}

ScriptObject::ScriptObject(const ScriptObject& obj)
{
	mScriptObject = obj.mScriptObject;
	if (mScriptObject != nullptr)
	{
		mScriptObject->AddRef();
	}
	CacheMemberAddresses();
}

ScriptObject& ScriptObject::operator=(const ScriptObject& obj)
{
	if (&obj != this)
	{
		mScriptObject = obj.mScriptObject;
		if (mScriptObject != nullptr)
		{
			mScriptObject->AddRef();
		}
	}

	return *this;
}


ScriptObject::~ScriptObject()
{
	SAFE_RELEASE(mScriptObject);
}

template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, asBYTE value)
{
	return context->SetArgByte(arg, value);
}
template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, asWORD value)
{
	return context->SetArgWord(arg, value);
}
template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, asDWORD value)
{
	return context->SetArgDWord(arg, value);
}
template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, asQWORD value)
{
	return context->SetArgQWord(arg, value);
}
template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, float value)
{
	return context->SetArgFloat(arg, value);
}
template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, double value)
{
	return context->SetArgDouble(arg, value);
}
template<>
inline int ScriptObject::SetArg(asIScriptContext* context, asUINT arg, void *value)
{
	return context->SetArgObject(arg, value);
}

template<>
inline asBYTE ScriptObject::GetReturn<asBYTE>(asIScriptContext* context)
{
	return context->GetReturnByte();
}
template<>
inline asWORD ScriptObject::GetReturn<asWORD>(asIScriptContext* context)
{
	return context->GetReturnWord();
}
template<>
inline asDWORD ScriptObject::GetReturn<asDWORD>(asIScriptContext* context)
{
	return context->GetReturnDWord();
}
template<>
inline asQWORD ScriptObject::GetReturn<asQWORD>(asIScriptContext* context)
{
	return context->GetReturnQWord();
}
template<>
inline float ScriptObject::GetReturn<float>(asIScriptContext* context)
{
	return context->GetReturnFloat();
}
template<>
inline double ScriptObject::GetReturn<double>(asIScriptContext* context)
{
	return context->GetReturnDouble();
}
template<>
inline void* ScriptObject::GetReturn<void*>(asIScriptContext* context)
{
	return context->GetReturnObject();
}

template<>
inline HeapString ScriptObject::GetReturn<HeapString>(asIScriptContext* context)
{
	return HeapString((*(HeapString*)context->GetReturnAddress()).c_str());
}

Medusa::StringRef ScriptObject::ClassName() const
{
	return mScriptObject->GetObjectType()->GetName();
}

template<typename... TArgs>
inline void ScriptObject::Invoke(const StringRef& funcName, TArgs&&... args)
{
	asIObjectType* scriptObjectType = mScriptObject->GetObjectType();
	asIScriptFunction* func = scriptObjectType->GetMethodByName(funcName.c_str());
	if (func == nullptr)
	{
		Log::AssertFailedFormat("Cannot find {}::{}", scriptObjectType->GetName(), funcName.c_str());
		return;
	}

	asIScriptContext* context = ScriptEngine::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	SetArgs(context, std::forward<TArgs>(args)...);
	context->Execute();

	asThreadCleanup();
}

template<typename R, typename... TArgs>
inline R ScriptObject::Invoke(const StringRef& funcName, TArgs&&... args)
{
	asIObjectType* scriptObjectType = mScriptObject->GetObjectType();
	asIScriptFunction* func = scriptObjectType->GetMethodByName(funcName.c_str());
	if (func == nullptr)
	{
		Log::AssertFailedFormat("Cannot find {}::{}", scriptObjectType->GetName(), funcName.c_str());
		return Compile::DefaultValue<R>();
	}

	asIScriptContext* context = ScriptEngine::Instance().GetScriptContext();
	context->Prepare(func);
	context->SetObject(mScriptObject);
	SetArgs(context, std::forward<TArgs>(args)...);
	context->Execute();

	R result = GetReturn<R>(context);
	asThreadCleanup();
	return result;
}

template<typename R>
inline R ScriptObject::GetProperty(const StringRef& propertyName)
{
	HeapString funcName("get_");
	funcName += propertyName;

	return Invoke<float>(funcName);
}



void* ScriptObject::GetMemberAddress(StringRef memberName)
{
	return mMemberAddresses.TryGetValueWithFailed(memberName, nullptr);
}



void ScriptObject::CacheMemberAddresses()
{
	mMemberAddresses.Clear();
	uint32 count = mScriptObject->GetPropertyCount();
	FOR_EACH_SIZE(i, count)
	{
		StringRef name = mScriptObject->GetPropertyName(static_cast<uint32>(i));
		void* result = mScriptObject->GetAddressOfProperty(static_cast<uint32>(i));
		mMemberAddresses.Add(name, result);
	}

}


MEDUSA_END;
#endif
