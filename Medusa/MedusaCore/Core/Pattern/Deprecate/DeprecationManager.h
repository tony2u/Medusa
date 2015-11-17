// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once

#include "MedusaCorePreDeclares.h"



MEDUSA_BEGIN;
class DeprecationManager
{
public:
	static DeprecationManager& Instance()
	{
		static DeprecationManager inst;
		return inst;
	}

	void AddDeprecateFunction(const char* funcName, const char* comment, const char* fileName, const char* lineName);

	~DeprecationManager();
private:
	DeprecationManager() {}
private:
	std::map<const char*, const char*> mDeprecatedFunction;
};


#ifdef MEDUSA_DEBUG
#define MEDUSA_DEPRECATE(funcName,comment) DeprecationManager::Instance().AddDeprecateFunction(funcName,comment,__FILE__,__LINE__);
#else
#define MEDUSA_DEPRECATE(funcName,comment)
#endif
MEDUSA_END;