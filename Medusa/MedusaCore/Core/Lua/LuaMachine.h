// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_LUA

#include "Core/String/StringRef.h"
#include "Core/Collection/List.h"
#include "LuaCompat.h"
#include "Core/Pattern/IInitializable.h"

MEDUSA_BEGIN;

class LuaMachine :public IInitializable
{
public:
	LuaMachine(void);
	~LuaMachine(void);
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize() override;

	LuaState* OpenNew(bool setCurrent = true);
	void Close(LuaState* state);

	LuaState& Current() { return *mCurrentState; }

	LuaState* CurrentState() const { return mCurrentState; }
	void SetCurrent(LuaState* val) { mCurrentState = val; }

	void AddPackagePath(const StringRef& path);
	void SetPackagePath(const StringRef& path);

	void AddPackageLoader(lua_CFunction loader);
private:
	List<LuaState*> mStates;
	LuaState* mCurrentState=nullptr;

};

MEDUSA_END;
#endif