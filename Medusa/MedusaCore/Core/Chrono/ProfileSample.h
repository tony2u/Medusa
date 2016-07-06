// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include "MedusaCorePreDeclares.h"
#include "Core/Chrono/ProfileManager.h"



MEDUSA_BEGIN;

class ProfileSample
{
public:
	ProfileSample(const StringRef& name,size_t count=1 ,size_t logCount=0)
	{ 
		ProfileManager::Instance().Begin(name,count,logCount);
	}

	~ProfileSample( void )					
	{ 
		ProfileManager::Instance().End();
	}
};

#if defined(MEDUSA_DEBUG)&&defined(MEDUSA_PROFILE_FEATURE)

#define	MEDUSA_PROFILE( name )			ProfileSample MACRO_CONCAT(__profile,__COUNTER__)(name)
#define	MEDUSA_PROFILE_COUNT( name,count )			ProfileSample MACRO_CONCAT(__profile,__COUNTER__)(name,count)
#define	MEDUSA_PROFILE_COUNT_LOG( name,count,logCount )			ProfileSample MACRO_CONCAT(__profile,__COUNTER__)(name,count,logCount)
#define	MEDUSA_PROFILE_LOG( name,logCount )			ProfileSample MACRO_CONCAT(__profile,__COUNTER__)(name,1,logCount)
#define MEDUSA_PROFILE_PRINT()			ProfileManager::Instance().StopAll();
#else
#define	MEDUSA_PROFILE( name )
#define	MEDUSA_PROFILE_COUNT( name,count )			
#define	MEDUSA_PROFILE_COUNT_LOG( name,count,logCount )			
#define	MEDUSA_PROFILE_LOG( name,logCount )			
#define MEDUSA_PROFILE_PRINT()			
#endif

MEDUSA_END;