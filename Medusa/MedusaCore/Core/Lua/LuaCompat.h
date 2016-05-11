// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA


#if MEDUSA_SCRIPT == MEDUSA_SCRIPT_LUA_JIT
#include "CoreLib/Common/luajit/lua.hpp"
#elif MEDUSA_SCRIPT ==MEDUSA_SCRIPT_LUA
#include "CoreLib/Common/lua/lua.hpp"
#endif


/**
* Set MEDUSA_LUA_CHECK_TYPE to 1 if you want to check type match on member funciton calling
*
*/
#ifndef MEDUSA_LUA_CHECK_TYPE
#define MEDUSA_LUA_CHECK_TYPE 1
#endif


/**
* Set MEDUSA_LUA_UNSAFE_INT64 to 1 if you want to include partial int64_t support.
*
* This option applys to lua 5.2 or eailier version only, or with 32-bit configuration.
* This option has no effect to lua 5.3 or later version, which has native 64 bit int support.
*/
#ifndef MEDUSA_LUA_UNSAFE_INT64
#define MEDUSA_LUA_UNSAFE_INT64 1
#endif

/**
* Set MEDUSA_LUA_UNSAFE_INT64_CHECK to 1 if you want to make sure every pushed int64_t is safe,
* that is, it can be converted from/to lua_Number without loss.
*
* This check will throw Lua runtime error if the conversion is not safe.
* This check has no effect to lua 5.3 or later version, which has native 64 bit int support.
*/
#ifndef MEDUSA_LUA_UNSAFE_INT64_CHECK
#define MEDUSA_LUA_UNSAFE_INT64_CHECK 0
#endif


/**
* Set MEDUSA_EXTRA_LUA_FIELDS to 1 if you want to include support for adding extra lua fields
* for the exported C++ objects. Otherwise setting missing field will raise lua error.
*
* Note the extra fields is attached to Lua object, different Lua objects will have different
* set of extra fields even they refer to the same C++ object (in the pointer or reference case).
*/
#ifndef MEDUSA_LUA_EXTRA_LUA_FIELDS
#define MEDUSA_LUA_EXTRA_LUA_FIELDS 0
#endif


#if LUA_VERSION_NUM == 501

#include <stdint.h>
typedef uint32_t lua_Unsigned;

#define LUA_OK 0

#define LUA_OPEQ 0
#define LUA_OPLT 1
#define LUA_OPLE 2

#define lua_rawlen(L, i) \
    lua_objlen(L, i)

#define lua_pushglobaltable(L) \
    lua_pushvalue(L, LUA_GLOBALSINDEX)

#define lua_tounsigned(L, i) \
    lua_tounsignedx(L, i, NULL)

const lua_Number* lua_version(lua_State* L);

int lua_absindex(lua_State* L, int i);
void lua_copy(lua_State* L, int from, int to);

void lua_pushunsigned(lua_State* L, lua_Unsigned n);
lua_Number lua_tonumberx(lua_State* L, int i, int* isnum);
lua_Integer lua_tointegerx(lua_State* L, int i, int* isnum);
lua_Unsigned lua_tounsignedx(lua_State* L, int i, int* isnum);

int lua_compare(lua_State* L, int index1, int index2, int op);

void lua_len(lua_State* L, int i);
void lua_rawgetp(lua_State* L, int i, const void* p);
void lua_rawsetp(lua_State* L, int i, const void* p);

void lua_getuservalue(lua_State* L, int i);
void lua_setuservalue(lua_State* L, int i);

#define luaL_newlib(L, l) \
    (lua_newtable(L), luaL_setfuncs(L, l, 0))

void luaL_checkversion(lua_State* L);

lua_Unsigned luaL_checkunsigned(lua_State* L, int i);
lua_Unsigned luaL_optunsigned(lua_State* L, int i, lua_Unsigned def);
const char* luaL_tolstring(lua_State* L, int idx, size_t* len);

void* luaL_testudata(lua_State* L, int i, const char* tname);
void luaL_setfuncs(lua_State* L, const luaL_Reg* l, int nup);

int luaL_len(lua_State* L, int i);
void luaL_setmetatable(lua_State* L, const char* tname);
int luaL_getsubtable(lua_State* L, int i, const char* name);

//void luaL_traceback(lua_State* L, lua_State* L1, const char* msg, int level);
//int luaL_fileresult(lua_State* L, int stat, const char* fname);


//---------------------------------------------------------------------------

#elif LUA_VERSION_NUM >= 503

    #ifndef lua_pushunsigned
        #define lua_pushunsigned(L, n) \
            lua_pushinteger(L, static_cast<lua_Integer>(n))

        #define lua_tounsignedx(L, i, is) \
            static_cast<lua_Unsigned>(lua_tointegerx(L, i, is))

        #define lua_tounsigned(L, i) \
            lua_tounsignedx(L, (i), nullptr)
    #endif

    #ifndef luaL_checkunsigned
        #define luaL_checkunsigned(L, a) \
            static_cast<lua_Unsigned>(luaL_checkinteger(L, a))

        #define luaL_optunsigned(L, a, d) \
            static_cast<lua_Unsigned>(luaL_optinteger(L, a, static_cast<lua_Integer>(d)))
    #endif

#endif

#endif