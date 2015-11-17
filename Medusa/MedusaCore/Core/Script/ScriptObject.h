// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#ifdef MEDUSA_SCRIPT

#include "Core/String/HeapString.h"
#include "Core/Collection/Dictionary.h"

MEDUSA_BEGIN;

class ScriptObject
{
public:
	ScriptObject(asIScriptObject* scriptObject);
	~ScriptObject();
	ScriptObject(const ScriptObject& obj);
	ScriptObject& operator=(const ScriptObject& obj);
public:
	StringRef ClassName()const;

	template<typename... TArgs>
	void Invoke(const StringRef& funcName, TArgs&&... args);

	template<typename R, typename... TArgs>
	R Invoke(const StringRef& funcName, TArgs&&... args);


	template<typename... TArgs>
	void operator()(const StringRef& funcName, TArgs&&... args)
	{
		Invoke(funcName, std::forward<TArgs>(args)...);
	}

	template<typename R, typename... TArgs>
	R operator()(const StringRef& funcName, TArgs&&... args)
	{
		return Invoke<R>(funcName, std::forward<TArgs>(args)...);
	}

	template<typename R>
	R GetProperty(const StringRef& propertyName);

	asIScriptObject* Data() const { return mScriptObject; }

public:
	void* GetMemberAddress(StringRef memberName);


	template<typename T>
	T Member(StringRef memberName)
	{
		return *(T*)GetMemberAddress(memberName);
	}

	
	template<typename T>
	T MemberOrDefault(StringRef memberName, T defaultVal)
	{
		T* p = (T*)GetMemberAddress(memberName);
		if (p != nullptr)
		{
			return *p;
		}
		return defaultVal;
	}

	template<typename T>
	bool SetMember(StringRef memberName, T val)
	{
		T* p = (T*)GetMemberAddress(memberName);
		if (p != nullptr)
		{
			*p = val;
			return true;
		}
		return false;
	}
private:
	void CacheMemberAddresses();

	template<typename... TArgs>
	static inline int SetArgs(asIScriptContext* context, TArgs&&... args)
	{
		return DoSetArgs(context, 0, std::forward<TArgs>(args)...);
	}

	template<typename T1, typename... TArgs>
	static inline int DoSetArgs(asIScriptContext* context, uint index, T1&& arg1, TArgs&&... args)
	{
		return SetArg(context, index, std::forward<T1>(arg1)) | DoSetArgs(context, index + 1, std::forward<TArgs>(args)...);
	}

	template<typename T1>
	static inline int DoSetArgs(asIScriptContext* context, uint index, T1&& arg1)
	{
		return SetArg(context, index, std::forward<T1>(arg1));
	}

	static inline int DoSetArgs(asIScriptContext* context, uint index)
	{
		return 0;
	}

	template<typename T>
	static int SetArg(asIScriptContext* context, uint arg, T value);
	template<typename R>
	static R GetReturn(asIScriptContext* context);
	
private:
	asIScriptObject* mScriptObject;
	Dictionary<StringRef, void*> mMemberAddresses;	//cache member address to improve performance!
};

template<>
inline StringRef ScriptObject::Member<StringRef>(StringRef memberName)
{
	HeapString* p = (HeapString*)GetMemberAddress(memberName);
	if (p != nullptr)
	{
		return p->c_str();
	}
	return StringRef::Empty;
}

template<>
inline bool ScriptObject::SetMember(StringRef memberName, StringRef val)
{
	HeapString* p = (HeapString*)GetMemberAddress(memberName);
	if (p != nullptr)
	{
		*p = val.c_str();
		return true;
	}
	return false;
}


template<>
inline StringRef ScriptObject::MemberOrDefault(StringRef memberName, StringRef defaultVal)
{
	HeapString* p = (HeapString*)GetMemberAddress(memberName);
	if (p != nullptr)
	{
		return p->c_str();
	}
	return defaultVal;
}

MEDUSA_END;
#endif
