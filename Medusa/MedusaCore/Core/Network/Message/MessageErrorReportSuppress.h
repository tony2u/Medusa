#pragma once
#include "MedusaCorePreDeclares.h"
MEDUSA_BEGIN;

enum class MessageErrorReportSuppress
{
	None=0,
	ConnectFail=1,
	AuthFailed=2,
	ServerFailed=4, 
	SwitchUI=8,
	UpdateLogic=16, 
	HideActivityIndicator=32
};

MEDUSA_END;
