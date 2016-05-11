// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaRef.h"
#include "Core/Log/Log.h"
#include "LuaDefines.h"
#include "LuaState.h"
#include "Core/Collection/Stack.h"

MEDUSA_BEGIN;

LuaRef::LuaRef(lua_State* state)
	:mState(state)
{

}

LuaRef::LuaRef(const LuaRef& other)
	: mState(other.mState)
{
	if (mState)
	{
		//generate another ref to value
		lua_rawgeti(mState, LUA_REGISTRYINDEX, other.mRef);
		mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
	}
	else
	{
		mRef = LUA_NOREF;
	}
}

LuaRef::LuaRef(lua_State* state, int index)
	:mState(state)
{
	lua_pushvalue(mState, index);
	mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
}


LuaRef::LuaRef(lua_State* state, StringRef name)
	:mState(state)
{
	*this = std::move(LuaRef::EvaluateGet(state,name));
}

LuaRef& LuaRef::operator=(std::nullptr_t)
{
	if (mState)
	{
		luaL_unref(mState, LUA_REGISTRYINDEX, mRef);
		mRef = LUA_REFNIL;
	}
	return *this;
}

LuaRef& LuaRef::operator=(const LuaRef& other)
{
	if (&other == this)
		return *this;

	if (mState)
	{
		luaL_unref(mState, LUA_REGISTRYINDEX, mRef);
	}
	mState = other.mState;
	if (mState)
	{
		lua_rawgeti(mState, LUA_REGISTRYINDEX, other.mRef);
		mRef = luaL_ref(mState, LUA_REGISTRYINDEX);
	}
	else
	{
		mRef = LUA_NOREF;
	}
	return *this;
}

LuaRef::LuaRef(LuaRef&& other)
	: mState(other.mState),
	mRef(other.mRef)
{
	other.mState = nullptr;
	other.mRef = LUA_NOREF;
}


LuaRef& LuaRef::operator=(LuaRef&& other)
{
	if (&other == this)
		return *this;
	mState = other.mState;
	mRef = other.mRef;

	other.mState = nullptr;
	other.mRef = LUA_NOREF;
	return *this;
}

LuaRef::~LuaRef(void)
{
	if (mState)
	{
		luaL_unref(mState, LUA_REGISTRYINDEX, mRef);
		mRef = LUA_NOREF;
	}
}

void LuaRef::PushToStack() const
{
	if (!this->IsValid())
	{
		Log::AssertFailedFormat("Failed to push lua ref:{}", mRef);
		return;
	}
	lua_rawgeti(mState, LUA_REGISTRYINDEX, mRef);
}

int LuaRef::Type() const
{
	PushToStack();
	int t = lua_type(mState, -1);
	lua_pop(mState, 1);
	return t;
}

const LuaRef& LuaRef::CheckType(int type) const
{
	PushToStack();
	luaL_checktype(mState, -1, static_cast<int>(type));
	lua_pop(mState, 1);
	return *this;
}



bool LuaRef::IsReferenceEqual(const LuaRef& other) const
{
	PushToStack();
	other.PushToStack();
	bool r = lua_rawequal(mState, -2, -1) != 0;
	lua_pop(mState, 2);
	return r;
}

int LuaRef::Compare(const LuaRef& other) const
{
	PushToStack();
	other.PushToStack();
	int r = lua_compare(mState, -2, -1, LUA_OPEQ)
		? 0
		: (lua_compare(mState, -2, -1, LUA_OPLT) ? -1 : 1);
	lua_pop(mState, 2);
	return r;
}

bool LuaRef::operator==(const LuaRef& other) const
{
	PushToStack();
	other.PushToStack();
	bool r = lua_compare(mState, -2, -1, LUA_OPEQ) != 0;
	lua_pop(mState, 2);
	return r;
}

bool LuaRef::operator!=(const LuaRef& other) const
{
	return !this->operator==(other);
}

bool LuaRef::operator<(const LuaRef& other) const
{
	PushToStack();
	other.PushToStack();
	bool r = lua_compare(mState, -2, -1, LUA_OPLT) != 0;
	lua_pop(mState, 2);
	return r;
}

bool LuaRef::operator<=(const LuaRef& other) const
{
	PushToStack();
	other.PushToStack();
	bool r = lua_compare(mState, -2, -1, LUA_OPLE) != 0;
	lua_pop(mState, 2);
	return r;
}

bool LuaRef::operator>(const LuaRef& other) const
{
	return !this->operator<=(other);
}

bool LuaRef::operator>=(const LuaRef& other) const
{
	return !this->operator<(other);
}

LuaRef LuaRef::PopFromStack(lua_State* state)
{
	LuaRef ref(state);
	ref.mRef = luaL_ref(state, LUA_REGISTRYINDEX);
	return ref;
}

LuaRef LuaRef::RefToTop(lua_State* state)
{
	lua_pushvalue(state, -1);
	return PopFromStack(state);
}

LuaRef LuaRef::NewUserData(lua_State* state, size_t size, void** outUserData /*= nullptr*/)
{
	void* userData = lua_newuserdata(state, size);
	if (outUserData)
	{
		*outUserData = userData;
	}
	return PopFromStack(state);
}



LuaRef LuaRef::Registry(lua_State* state)
{
	return LuaRef(state, LUA_REGISTRYINDEX);
}

LuaRef LuaRef::ClassTable(lua_State* state)
{
	LuaRef registry(state, LUA_REGISTRYINDEX);
	LuaRef classes = registry.Rawget(LuaNames::ClassesTable);
	if (classes == nullptr)
	{
		classes = LuaRef::NewTable(state);
		registry.Rawset(LuaNames::ClassesTable, classes);
	}

	return classes;
}

LuaRef LuaRef::NewTable(lua_State* state, int arraySize/*=0*/, int recordCount/*=0*/)
{
	lua_createtable(state, arraySize, recordCount);
	return PopFromStack(state);
}

LuaRef LuaRef::NewTableWithMeta(lua_State* state, StringRef name)
{
	lua_newtable(state);
	LuaStack s(state);
	LuaRef::EvaluateGet(state, name).PushToStack();

	lua_setmetatable(state, -2);
	return PopFromStack(state);
}

LuaRef LuaRef::Global(lua_State* state)
{
	lua_pushglobaltable(state);
	return PopFromStack(state);
}

void LuaRef::SetMetaTable(const LuaRef& meta)
{
	PushToStack();
	meta.PushToStack();
	lua_setmetatable(mState, -2);
	lua_pop(mState, 1);
}

int LuaRef::RawLength() const
{
	PushToStack();
	int n = int(lua_rawlen(mState, -1));
	lua_pop(mState, 1);
	return n;
}

int LuaRef::Length() const
{
	PushToStack();
	int n = int(luaL_len(mState, -1));
	lua_pop(mState, 1);
	return n;
}

//"a.b["e"][d[3]].c"
LuaRef LuaRef::EvaluateGet(StringRef path) const
{
	if (path.IsEmpty())
	{
		return *this;
	}

	LuaStackAutoReset save(mState);
	PushToStack();

	size_t length = path.Length();
	uintp prevIndex = 0;
	char prevMatchChar = 0;

	FOR_EACH_SIZE(i, length)
	{
		char c = path[i];
		switch (c)
		{
		case '.':
		{
			if (prevMatchChar != 0)
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return nullptr;
			}
			//prev is a var
			StringRef varName = path.SubString(prevIndex, i - prevIndex);
			prevIndex = i + 1;	//+1 to skip cur

			if (varName.IsEmpty())
			{
				//maybe  [].
			}
			else
			{
				lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
				lua_gettable(mState, -2);                    // parent,value
				lua_remove(mState, -2);	 // value

				if (lua_isnoneornil(mState, -1))
				{
					Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
					return nullptr;
				}
			}

		}
		break;
		case '[':
		{
			if (prevMatchChar != 0)
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return nullptr;
			}

			StringRef varName = path.SubString(prevIndex, i - prevIndex);
			prevIndex = i + 1;	//+1 to skip cur
			if (!varName.IsEmpty())
			{
				//prev is a var : a[]
				lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
				lua_gettable(mState, -2);                    // parent,value
				lua_remove(mState, -2);	 // value

				if (lua_isnoneornil(mState, -1))
				{
					Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
					return nullptr;
				}
			}
			else
			{
				//or a connect a[][]
				//do nothing as parent is already in stack
			}

			char nextChar = *(path.c_str() + i + 1);
			if (StdString::IsDigit(nextChar))
			{
				//number index
			}
			else if (StdString::IsAlpha(nextChar) || nextChar == '_')
			{
				//name
				//push global
				lua_pushglobaltable(mState);// parent
			}
			else if (nextChar != '\''&&nextChar != '\"')
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return nullptr;
			}

		}
		break;
		case ']':
		{
			if (prevMatchChar != 0)
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return nullptr;
			}

			StringRef varName = path.SubString(prevIndex, i - prevIndex);
			prevIndex = i + 1;

			//var name could be a number or string or value
			if (varName.IsEmpty())	//prevIndex have already be skipped at '' or ""
			{
				//str or inner [[]]
				lua_gettable(mState, -2);                    // parent,value
				lua_remove(mState, -2);	 // value

				if (lua_isnoneornil(mState, -1))
				{
					Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
					return nullptr;
				}
			}
			else
			{
				char firstChar = varName[0];
				if (StdString::IsDigit(firstChar))
				{
					//number index
					intp arrayIndex = varName.ToInt();
					lua_pushinteger(mState, (lua_Integer)arrayIndex); // <table> <key>
					lua_gettable(mState, -2);                // <table> <table_value>
					lua_remove(mState, -2);                  // <table_value>
					if (lua_isnoneornil(mState, -1))
					{
						Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
						return nullptr;
					}
				}
				else
				{
					//var index
					lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
					lua_gettable(mState, -2);                    // parent,value
					lua_remove(mState, -2);	 // value

					if (lua_isnoneornil(mState, -1))
					{
						Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
						return nullptr;
					}

					//use cur value as key to get parent's value
					lua_gettable(mState, -2);                    // parent,value
					lua_remove(mState, -2);	 // value

					if (lua_isnoneornil(mState, -1))
					{
						Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
						return nullptr;
					}
				}

			}
		}
		break;
		case '\'':
		case '\"':
		{
			if (prevMatchChar == 0)
			{
				//require a match ' later
				prevMatchChar = c;
			}
			else if (c == prevMatchChar)
			{
				StringRef varName = path.SubString(prevIndex, i - prevIndex);
				prevMatchChar = 0;
				lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
			}
			else
			{
				Log::AssertFailedFormat("Invalid path:{}.{} not match", path, c);
				return nullptr;
			}

			prevIndex = i + 1;
		}
		break;
		default:
			break;
		}
	}

	if (prevIndex != length)
	{
		//still have last part
		StringRef varName = path.SubString(prevIndex);
		lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
		lua_gettable(mState, -2);                    // parent,value
		lua_remove(mState, -2);	 // value

		if (lua_isnoneornil(mState, -1))
		{
			Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
			return nullptr;
		}
	}


	return LuaRef::PopFromStack(mState);
}

LuaRef LuaRef::EvaluateGet(lua_State* state, StringRef name)
{
	return LuaRef::Global(state).EvaluateGet(name);
}

//"a.b["e"][d[3]].c"=123
bool LuaRef::EvaluateSetHelper(StringRef path, const LuaRef& val) const
{
	if (path.IsEmpty())
	{
		return false;
	}

	LuaStackAutoReset save(mState);
	PushToStack();

	size_t length = path.Length();
	uintp prevIndex = 0;
	char prevMatchChar = 0;

	FOR_EACH_SIZE(i, length)
	{
		char c = path[i];
		switch (c)
		{
		case '.':
		{
			if (prevMatchChar != 0)
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return false;
			}
			//prev is a var
			StringRef varName = path.SubString(prevIndex, i - prevIndex);
			prevIndex = i + 1;	//+1 to skip cur

			if (varName.IsEmpty())
			{
				//maybe  [].
			}
			else
			{
				lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
				lua_gettable(mState, -2);                    // parent,value
				lua_remove(mState, -2);	 // value

				if (lua_isnoneornil(mState, -1))
				{
					Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
					return false;
				}
			}

		}
		break;
		case '[':
		{
			if (prevMatchChar != 0)
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return false;
			}

			StringRef varName = path.SubString(prevIndex, i - prevIndex);
			prevIndex = i + 1;	//+1 to skip cur
			if (!varName.IsEmpty())
			{
				//prev is a var : a[]
				lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
				lua_gettable(mState, -2);                    // parent,value
				lua_remove(mState, -2);	 // value

				if (lua_isnoneornil(mState, -1))
				{
					Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
					return false;
				}
			}
			else
			{
				//or a connect a[][]
				//do nothing as parent is already in stack
			}

			char nextChar = *(path.c_str() + i + 1);
			if (StdString::IsDigit(nextChar))
			{
				//number index
			}
			else if (StdString::IsAlpha(nextChar) || nextChar == '_')
			{
				//name
				//push global
				lua_pushglobaltable(mState);// parent
			}
			else if (nextChar != '\''&&nextChar != '\"')
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return false;
			}

		}
		break;
		case ']':
		{
			if (prevMatchChar != 0)
			{
				Log::AssertFailedFormat("Invalid path:{}", path);
				return false;
			}

			StringRef varName = path.SubString(prevIndex, i - prevIndex);
			prevIndex = i + 1;

			if (i == length - 1)
			{
				//last char means have to set

				//var name could be a number or string or value
				if (varName.IsEmpty())	//prevIndex have already be skipped at '' or ""
				{
					//str or inner [[]]
					val.PushToStack();
					lua_settable(mState, -3);                    // parent,key,value
					return true;
				}
				else
				{
					char firstChar = varName[0];
					if (StdString::IsDigit(firstChar))
					{
						//number index
						intp arrayIndex = varName.ToInt();
						lua_pushinteger(mState, (lua_Integer)arrayIndex); // <table> <key>
						val.PushToStack();
						lua_settable(mState, -3);                // <table> <table_value>
					}
					else
					{
						//var index
						lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
						lua_gettable(mState, -2);                    // parent,value
						lua_remove(mState, -2);	 // value

						if (lua_isnoneornil(mState, -1))
						{
							Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
							return false;
						}

						//use cur value as key to get parent's value
						lua_settable(mState, -3);                    // parent,value
					}
				}
			}
			else
			{
				//get

				//var name could be a number or string or value
				if (varName.IsEmpty())	//prevIndex have already be skipped at '' or ""
				{
					//str or inner [[]]
					lua_gettable(mState, -2);                    // parent,value
					lua_remove(mState, -2);	 // value

					if (lua_isnoneornil(mState, -1))
					{
						Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
						return false;
					}
				}
				else
				{
					char firstChar = varName[0];
					if (StdString::IsDigit(firstChar))
					{
						//number index
						intp arrayIndex = varName.ToInt();
						lua_pushinteger(mState, (lua_Integer)arrayIndex); // <table> <key>
						lua_gettable(mState, -2);                // <table> <table_value>
						lua_remove(mState, -2);                  // <table_value>
						if (lua_isnoneornil(mState, -1))
						{
							Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
							return false;
						}
					}
					else
					{
						//var index
						lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
						lua_gettable(mState, -2);                    // parent,value
						lua_remove(mState, -2);	 // value

						if (lua_isnoneornil(mState, -1))
						{
							Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
							return false;
						}

						//use cur value as key to get parent's value
						lua_gettable(mState, -2);                    // parent,value
						lua_remove(mState, -2);	 // value

						if (lua_isnoneornil(mState, -1))
						{
							Log::AssertFailedFormat("Invalid path:{}. Cannot get {}", path, varName);
							return false;
						}
					}
				}

			}
		}
		break;
		case '\'':
		case '\"':
		{
			if (prevMatchChar == 0)
			{
				//require a match ' later
				prevMatchChar = c;
			}
			else if (c == prevMatchChar)
			{
				StringRef varName = path.SubString(prevIndex, i - prevIndex);
				prevMatchChar = 0;
				lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
			}
			else
			{
				Log::AssertFailedFormat("Invalid path:{}.{} not match", path, c);
				return false;
			}

			prevIndex = i + 1;
		}
		break;
		default:
			break;
		}
	}

	if (prevIndex != length)
	{
		//still have last part
		StringRef varName = path.SubString(prevIndex);
		lua_pushlstring(mState, varName.c_str(), varName.Length()); //parent,key
		val.PushToStack();
		lua_settable(mState, -3);                    // parent,value
	}

	return true;
}

LuaRef LuaRef::GetMetaTable() const
{
	LuaRef meta;
	PushToStack();
	if (lua_getmetatable(mState, -1))
	{
		meta = PopFromStack(mState);
	}
	lua_pop(mState, 1);
	return meta;
}

const LuaRef LuaRef::Empty;

MEDUSA_END;
#endif