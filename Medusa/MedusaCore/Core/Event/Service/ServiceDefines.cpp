// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "ServiceDefines.h"

MEDUSA_BEGIN;

namespace ServicePropertyNames
{
	const StringRef Host = "Host";
	const StringRef Port = "Port";
	const StringRef Poller = "Poller";
	const StringRef Connection = "Connection";
	const StringRef ReadHandlers = "ReadHandlers";
	const StringRef WriteHandlers = "WriteHandlers";
	const StringRef ThreadCount = "ThreadCount";
	const StringRef IdleMilliseconds = "IdleMilliseconds";	//after idle check to be idle to auto close 
	const StringRef HeartbeatMilliseconds = "HeartbeatMilliseconds";	//after idle check to be idle to auto close 


}

MEDUSA_END;
