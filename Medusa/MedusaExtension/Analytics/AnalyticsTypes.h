// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "Core/Pattern/Delegate.h"



MEDUSA_BEGIN;

enum class AnalyticsReportPolicy
{
	RealTime = 0,       
	Batch = 1,          //report at run
	Daily = 4,      //report every day
	WifiOnly = 5,   //report only when WIFI
	Interval = 6,   //report on min interval
	OnExit = 7        //report after exit or background
};


enum class AnalyticsAccountType
{
	Anonymous = 0,      
	Registered = 1,     
	SinaWeibo = 2,      
	QQ = 3,             
	TencentWeibo = 4,   
	ND91 = 5,           
	Type1 = 11,         
	Type2 = 12,         
	Type3 = 13,         
	Type4 = 14,         
	Type5 = 15,         
	Type6 = 16,         
	Type7 = 17,         
	Type8 = 18,         
	Type9 = 19,         
	Type10 = 20         
};


enum class AnalyticsAccountGender
{
	Unknown = 0,    
	Male = 1,       
	Female = 2      
};

typedef Delegate<void()> AnalyticsOnlineConfigDelegate;

MEDUSA_END;