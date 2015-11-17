// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "Analytics/TalkingDataAnalyzer.h"
#include "Core/Log/Log.h"


MEDUSA_BEGIN;

#ifdef MEDUSA_ANDROID

bool TalkingDataAnalyzer::Initialize()
{

	return true;
}

bool TalkingDataAnalyzer::Uninitialize()
{
	return true;
}

void TalkingDataAnalyzer::EnableLog(bool val)
{

}

void TalkingDataAnalyzer::EnableCrashReport(bool val)
{

}

#pragma region Account

void TalkingDataAnalyzer::InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level/*=1*/,int age/*=18*/,AnalyticsAccountType accountType/*=AnalyticsAccountType::Registered*/,AnalyticsAccountGender gender/*=AnalyticsAccountGender::Unknown*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(gameServerName,16);
	LOG_ASSERT_STRING_MAX_LENGTH(accountId,64);
	LOG_ASSERT_STRING_MAX_LENGTH(accountName,64);
	LOG_ASSERT_INT_RANGE(level,1,1000);
	LOG_ASSERT_INT_RANGE(age,1,120);
}

void TalkingDataAnalyzer::UpdateAccountLevel(int level)
{
	LOG_ASSERT_INT_RANGE(level,1,1000);

}

#pragma endregion Account

#pragma region Payment

void TalkingDataAnalyzer::RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(orderId,64);
	LOG_ASSERT_STRING_MAX_LENGTH(itemId,32);
	LOG_ASSERT_STRING_MAX_LENGTH(paymentType.ToString(),16);


}

void TalkingDataAnalyzer::SucceedPay(const StringRef& orderId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(orderId,64);

}

void TalkingDataAnalyzer::RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(orderId,64);
	LOG_ASSERT_STRING_MAX_LENGTH(itemId,32);
	LOG_ASSERT_STRING_MAX_LENGTH(paymentType.ToString(),16);
}



#pragma endregion Payment

#pragma region Reward
void TalkingDataAnalyzer::RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)
{
	LOG_ASSERT_STRING_MAX_LENGTH(reason,32);

}

void TalkingDataAnalyzer::RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)
{
	LOG_ASSERT_STRING_MAX_LENGTH(reason,32);
	//NOT SUPPORTED
}

#pragma endregion Reward

#pragma region Purchase
void TalkingDataAnalyzer::Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)
{
	LOG_ASSERT_STRING_MAX_LENGTH(itemName,32);

}

void TalkingDataAnalyzer::Use(const StringRef& itemName,int count/*=1*/,double price/*=0*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(itemName,32);

}


#pragma endregion Purchase


#pragma region Mission

void TalkingDataAnalyzer::BeginMission(const StringRef& missionId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,32);

}

void TalkingDataAnalyzer::CompeleteMission(const StringRef& missionId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,32);

}

void TalkingDataAnalyzer::FailedMission(const StringRef& missionId,const StringRef& reason/*=StringRef::Empty*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,32);
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,16);

}

#pragma endregion Mission

#pragma region Event

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	LOG_ASSERT_COLLECTION_MAX_COUNT(attributes,10);
	FOR_EACH_COLLECTION(i,attributes)
	{
		LOG_ASSERT_STRING_MAX_LENGTH(i->Key,32);
		LOG_ASSERT_STRING_MAX_LENGTH(i->Value,32);

	}



}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	FOR_EACH_COLLECTION(i,attributes)
	{
		LOG_ASSERT_STRING_MAX_LENGTH(i->Key,32);

	}
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,int count)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label,int count)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
}

void TalkingDataAnalyzer::BeginEvent(const StringRef& eventId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::BeginEvent(const StringRef& eventId,const StringRef& label)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::EndEvent(const StringRef& eventId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::EndEvent(const StringRef& eventId,const StringRef& label)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::LogEventTime(const StringRef& eventId,int microseconds)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::LogPageStay(const StringRef& pageName,int seconds)
{
	LOG_ASSERT_STRING_MAX_LENGTH(pageName,64);

}

void TalkingDataAnalyzer::BeginPageStay(const StringRef& pageName)
{
	LOG_ASSERT_STRING_MAX_LENGTH(pageName,64);

}

void TalkingDataAnalyzer::EndPageStay(const StringRef& pageName)
{
	LOG_ASSERT_STRING_MAX_LENGTH(pageName,64);

}


#pragma endregion Event

#pragma region Location

void TalkingDataAnalyzer::SetLocation(double latitude,double longitude)
{
	
}

#pragma endregion Location

#pragma region OnlineConfig

void TalkingDataAnalyzer::SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)
{
	//NOT SUPPORTED
}

void TalkingDataAnalyzer::UpdateConfig()
{
	//NOT SUPPORTED
}

HeapString TalkingDataAnalyzer::GetConfigString(const StringRef& key)
{
	//NOT SUPPORTED
	return HeapString::Empty;
}



#pragma endregion OnlineConfig

#endif
MEDUSA_END;
