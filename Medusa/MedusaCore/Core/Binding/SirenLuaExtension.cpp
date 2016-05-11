// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_LUA
#include "SirenLuaExtension.h"

MEDUSA_BEGIN;

SirenLuaExtension::SirenLuaExtension()
{
	
}

SirenLuaExtension::~SirenLuaExtension(void)
{
}

//static void
//pushfunction_withbuffer(lua_State *L, const char * name, lua_CFunction func) {
//	lua_newuserdata(L, ENCODE_BUFFERSIZE);
//	lua_pushinteger(L, ENCODE_BUFFERSIZE);
//	lua_pushcclosure(L, func, 2);
//	lua_setfield(L, -2, name);
//}


int SirenLuaExtension::Open(lua_State *L)
{
//#ifdef luaL_checkversion
//	luaL_checkversion(L);
//#endif
//	luaL_Reg l[] = {
//		{ "newproto", lnewproto },
//		{ "deleteproto", ldeleteproto },
//		{ "dumpproto", ldumpproto },
//		{ "querytype", lquerytype },
//		{ "decode", ldecode },
//		{ "protocol", lprotocol },
//		{ "loadproto", lloadproto },
//		{ "saveproto", lsaveproto },
//		{ "default", ldefault },
//		{ NULL, NULL },
//	};
//
//	pushfunction_withbuffer(L, "encode", lencode);
//	pushfunction_withbuffer(L, "pack", lpack);
//	pushfunction_withbuffer(L, "unpack", lunpack);
//	luaL_newlib(L, l);

	return 1;
}

MEDUSA_END;

#endif