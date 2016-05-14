// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaCorePreDeclares.h"
#ifdef MEDUSA_SCRIPT
#include "Core/Pattern/Singleton.h"
#include "Core/Module/IModule.h"
#include "ScriptDefines.h"

MEDUSA_BEGIN;

class ScriptEngine :public Singleton<ScriptEngine>, public IModule
{
	friend class Singleton<ScriptEngine>;
	ScriptEngine();
	~ScriptEngine(void);
public:
	virtual bool Initialize() override;
	virtual bool Uninitialize()override;

	ScriptMachine* NewMachine(bool setCurrent = true);

	ScriptMachine* Current() const { return mCurrent; }
	void SetCurrent(ScriptMachine* val) { mCurrent = val; }
	StringRef Path() const { return mPath; }
	void SetPath(StringRef val) { mPath = val; }

	static ScriptState* State();

	static bool ExistsScriptFile(StringRef name);
protected:
	virtual bool OnLoad(IEventArg& e = IEventArg::Empty) override;
	virtual bool OnUnload(IEventArg& e = IEventArg::Empty) override;

	virtual bool OnChildLoad(IModule& child, IEventArg& e = IEventArg::Empty) override;
	virtual bool OnChildUnload(IModule& child, IEventArg& e = IEventArg::Empty) override;
	virtual bool OnChildReload(IModule& child, IEventArg& e = IEventArg::Empty) override;
private:
	ScriptMachine* mCurrent = nullptr;
	HeapString mPath;

};


MEDUSA_END;

#endif