// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"

MEDUSA_BEGIN;
namespace Dynamic
{
	template<typename TBase,typename TWin32,typename TIOS,typename TAndroid,typename... TArgs>
	inline TBase* CreatePlatformType(TArgs&&... args)
	{
#ifdef MEDUSA_WINDOWS
		return new TWin32(std::forward<TArgs>(args)...);
#elif defined(MEDUSA_IOS)
		return new TIOS(std::forward<TArgs>(args)...);
#elif defined(MEDUSA_ANDROID)
		return new TAndroid(std::forward<TArgs>(args)...);
#endif
	}

}

MEDUSA_END;