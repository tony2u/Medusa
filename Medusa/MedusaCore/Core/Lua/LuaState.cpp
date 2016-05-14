// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "LuaState.h"
#include "Core/Log/Log.h"
#include "Core/String/StringParser.h"
#include "Core/IO/FileSystem.h"
#include "Core/IO/Path.h"


MEDUSA_BEGIN;


LuaState::LuaState(bool openDefaultLibs /*= true*/)
{
	mState = luaL_newstate();
	Log::AssertNotNull(mState, "Cannot create lua state");
	mIsOwner = true;

	if (openDefaultLibs)
	{
		luaL_openlibs(mState);
	}

	lua_pushglobaltable(mState);
	lua_pushcfunction(mState, OnPrint);
	lua_setfield(mState, -2, "print");
	lua_pop(mState, 1);

	AddPackageLoader(OnPackageLoader);
}

LuaState::LuaState(lua_State* state, bool isOwner/*=false*/)
	:mState(state), mIsOwner(isOwner)
{

}

LuaState::~LuaState(void)
{
	if (mState != nullptr && mIsOwner)
	{
		ForceGC();
		lua_close(mState);
	}
	mState = nullptr;
}

void LuaState::ForceGC()
{
	lua_gc(mState, LUA_GCCOLLECT, 0);
}

LuaModule LuaState::BeginModule(StringRef name)
{
	if (name.IsEmpty())
	{
		Log::AssertFailed("Cannot have empty name lua module");
	}

	LuaRef parent = LuaRef::Global(mState);
	auto ref = parent.Rawget(name);
	if (ref != nullptr)
	{
		return LuaModule(mState, ref, name);
	}
	else
	{
		LuaModule mod(mState, name);
		parent.Rawset(name, mod.Ref());
		return mod;
	}
}

LuaTable LuaState::BeginTable(StringRef name)
{
	if (name.IsEmpty())
	{
		Log::AssertFailed("Cannot have empty name lua table");
	}

	LuaRef parent = LuaRef::Global(mState);
	auto ref = parent.Rawget(name);
	if (ref != nullptr)
	{
		return LuaTable(mState, ref, name);
	}
	else
	{
		LuaTable mod(mState, name);
		parent.Rawset(name, mod.Ref());
		return mod;
	}
}


void LuaState::AddPackagePath(const StringRef& path)
{
	lua_getglobal(mState, "package");
	lua_getfield(mState, -1, "path");
	const char* curPath = lua_tostring(mState, -1);

	lua_pushfstring(mState, "%s%s/?.lua", curPath, path.c_str());
	lua_setfield(mState, -3, "path");
	lua_pop(mState, 2);
}

void LuaState::SetPackagePath(const StringRef& path)
{
	lua_getglobal(mState, "package");
	lua_pushfstring(mState, "?.lua;%s/?.lua", path.c_str());
	lua_setfield(mState, -2, "path");
	lua_pop(mState, 1);
}

void LuaState::AddPackageLoader(lua_CFunction loader)
{
#if LUA_VERSION_NUM>501
	constexpr static char* searchersName = "searchers";
#else
	constexpr static char* searchersName = "loaders";

#endif
	RETURN_IF_NULL(loader);
	lua_getglobal(mState, "package");	 /* L: package */
	lua_getfield(mState, -1, searchersName);		/* L: package, searchers */

	//insert loader into index 2
	lua_pushvalue(mState, -2);
	lua_pushcclosure(mState, loader, 1);	//set package as loader up value

	//lua_pushcfunction(mState, loader);	 /* L: package, searchers, func */

	/*
	static const lua_CFunction searchers[] =
	{searcher_preload, searcher_Lua, searcher_C, searcher_Croot, NULL};
	*/
	//move back searchers >=2

	//for (int i = luaL_len(mState, -2); i >= 2; --i)
	//{
	//	lua_rawgeti(mState, -2, i);		/* L: package, searchers, func, function */
	//	lua_rawseti(mState, -3, i + 1);		/* L: package, searchers, func */
	//}

	lua_rawseti(mState, -2, 2);			 /* L: package, searchers */
	lua_setfield(mState, -2, searchersName);	/* L: package */

	lua_pop(mState, 1);

}


int LuaState::OnPackageLoader(lua_State* state)
{
	const char* fileName = luaL_checkstring(state, 1);
	lua_getfield(state, lua_upvalueindex(1), "path");
	const char* packagePath = lua_tostring(state, -1);

	HeapString path(fileName);
	path.ReplaceAll('.', '/');
	HeapString searchPaths(packagePath);
	searchPaths.ReplaceAll("?", path);

	List<StringRef> outPaths;
	StringParser::Split(searchPaths.ToString(), ";", outPaths);
	for (auto tryPath : outPaths)
	{
		HeapString realPath = FileSystem::Instance().GetRealPath(tryPath);
		if (!realPath.IsEmpty())
		{
			//real file on disk
			int result = luaL_loadfile(state, realPath.c_str());
			if (result != LUA_OK)
			{
				luaL_error(state, "Error loading module %s from file %s :\n\t%s", lua_tostring(state, 1), tryPath.c_str(), lua_tostring(state, -1));
				return 0;
			}
			return 1;
		}
		else
		{
			MemoryData data = FileSystem::Instance().ReadAllData(tryPath);
			if (data.IsValid())
			{
				if (luaL_loadbuffer(state, (const char*)data.Data(), data.Size(), fileName) != 0)
				{
					luaL_error(state, "Error loading module %s from file %s :\n\t%s", lua_tostring(state, 1), tryPath.c_str(), lua_tostring(state, -1));
					return 0;
				}
				return 1;
			}
		}

	}
	Log::FormatError("Cannot load file:{}", path);
	return 0;
}

void LuaState::RegisterExtension(const StringRef& name, lua_CFunction loader)
{
	RETURN_IF_NULL(loader);
	lua_getglobal(mState, "package");
	lua_getfield(mState, -1, "preload");

	lua_pushcfunction(mState, loader);
	lua_setfield(mState, -2, name.c_str());
	lua_pop(mState, 2);
}

bool LuaState::DoFile(const FileIdRef& file, int resultCount/*=0*/)
{
	HeapString realPath = FileSystem::Instance().GetRealPath(file);
	if (!realPath.IsEmpty())
	{
		//we can find a file on disk and has no coding. use loadfile to enable lua debugging

		LuaStack s(mState);
		
		int errorFunc = s.SetErrorHandler();
		int result = luaL_loadfile(mState, realPath.c_str());
		if (result == LUA_OK)
		{
			HeapString pureName = Path::GetFileNameWithoutExtension(file.Name);
			s.Push(pureName);

			//push file name as arg
			result = lua_pcall(mState, 1, resultCount, errorFunc);
		}

		if (result != LUA_OK)
		{
			lua_remove(mState, -2);
			Log::FormatError("Failed to do file:{} because of {}:{}", realPath, result, lua_tostring(mState, -1));
			return false;
		}

		lua_remove(mState, -(resultCount + 1));		//remove error func

		return true;
	}
	else
	{
		HeapString data = FileSystem::Instance().ReadAllText(file);
		if (data.IsEmpty())
		{
			Log::FormatError("Cannot find file:{}", file.Name);
			return false;
		}
		return DoBuffer(data, resultCount, file.Name);
	}

}

bool LuaState::DoBuffer(StringRef buffer, int resultCount/*=0*/, StringRef fileName /*= StringRef::Empty*/)
{
	LuaStack s(mState);
	int errorFunc = s.SetErrorHandler();

	int result = luaL_loadbuffer(mState, buffer.c_str(), buffer.Length(), fileName.c_str());
	if (result == LUA_OK)
	{
		//push name as arg
		HeapString pureName = Path::GetFileNameWithoutExtension(fileName);
		s.Push(pureName);

		result = lua_pcall(mState, 1, resultCount, errorFunc);
	}

	if (result != LUA_OK)
	{
		lua_remove(mState, -2);
		Log::FormatError("Failed to do buffer:{} because of {}:{}", buffer, result, lua_tostring(mState, -1));
		return false;
	}

	lua_remove(mState, -(resultCount + 1));		//remove error func
	return true;
}



LuaRef LuaState::DoFileWithReturn(const FileIdRef& file)
{
	if (DoFile(file, 1))
	{
		return LuaRef::PopFromStack(mState);
	}
	return nullptr;
}

LuaRef LuaState::DoBufferWithReturn(StringRef buffer, StringRef fileName /*= StringRef::Empty*/)
{
	if (DoBuffer(buffer, 1, fileName))
	{
		return LuaRef::PopFromStack(mState);
	}
	return nullptr;
}


void LuaState::DumpGlobals()
{
	const static char* luaStr = "local function print_all(t,prefix) for k,v in pairs(t) do if type(v) == \"string\" then print(string.format(\"%s => %s\", prefix .. \".\" .. k,v)) else print(prefix .. \".\" .. k) end if type(v) == \"table\" and k ~= \"_G\" and k ~= \"_G._G\" and not v.package then print_all(v, \"  \" .. prefix .. \".\" .. k)	end end end print_all(_G, \"_G\")";
	DoBuffer(luaStr, 0, "DumpGlobals");
}

int LuaState::OnPrint(lua_State* state)
{
	int count = lua_gettop(state);
	for (int i = 1; i <= count; ++i)
	{
		int type = lua_type(state, i);
		switch (type)
		{
		case LUA_TNIL:
			Log::Info("nil");
			break;
		case LUA_TBOOLEAN:
			Log::Info(StringParser::ToString(lua_toboolean(state, i) != 0));
			break;
		case LUA_TLIGHTUSERDATA:
			Log::FormatInfo("{}", lua_topointer(state, i));
			break;
		case LUA_TNUMBER:
			Log::FormatInfo("{:f}", lua_tonumber(state, i));
			break;
		case LUA_TSTRING:
			Log::Info(lua_tostring(state, i));
			break;
		case LUA_TTABLE:
		case LUA_TFUNCTION:
		case LUA_TUSERDATA:
		case LUA_TTHREAD:
			Log::FormatInfo("{}", lua_topointer(state, i));	//\t0x%08p
			break;
		default:
			Log::Info(lua_typename(state, type));
			break;
		}
	}

	return 0;
}

MEDUSA_END;

#endif