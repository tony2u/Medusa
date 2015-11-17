// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "Analytics/UmengAnalyzer.h"
MEDUSA_BEGIN;

#ifdef MEDUSA_WINDOWS

bool UmengAnalyzer::Initialize()
{
	return true;
}

bool UmengAnalyzer::Uninitialize()
{
	return true;
}

void UmengAnalyzer::EnableLog(bool val)
{

}

void UmengAnalyzer::EnableCrashReport(bool val)
{

}


#pragma region Account

void UmengAnalyzer::InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level/*=1*/,int age/*=18*/,AnalyticsAccountType accountType/*=AnalyticsAccountType::Registered*/,AnalyticsAccountGender gender/*=AnalyticsAccountGender::Unknown*/)
{
	
}

void UmengAnalyzer::UpdateAccountLevel(int level)
{

}

#pragma endregion Account

#pragma region Payment

void UmengAnalyzer::RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{

}

void UmengAnalyzer::SucceedPay(const StringRef& orderId)
{

}

void UmengAnalyzer::RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{

}



#pragma endregion Payment

#pragma region Reward
void UmengAnalyzer::RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)
{

}

void UmengAnalyzer::RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)
{

}

#pragma endregion Reward

#pragma region Purchase
void UmengAnalyzer::Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)
{

}

void UmengAnalyzer::Use(const StringRef& itemName,int count/*=1*/,double price/*=0*/)
{

}


#pragma endregion Purchase


#pragma region Mission

void UmengAnalyzer::BeginMission(const StringRef& missionId)
{

}

void UmengAnalyzer::CompeleteMission(const StringRef& missionId)
{

}

void UmengAnalyzer::FailedMission(const StringRef& missionId,const StringRef& reason/*=StringRef::Empty*/)
{

}

#pragma endregion Mission

#pragma region Event

void UmengAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)
{

}

void UmengAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)
{

}

void UmengAnalyzer::LogEvent(const StringRef& eventId)
{

}

void UmengAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label)
{

}

void UmengAnalyzer::LogEvent(const StringRef& eventId,int count)
{

}

void UmengAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label,int count)
{

}

void UmengAnalyzer::BeginEvent(const StringRef& eventId)
{

}

void UmengAnalyzer::BeginEvent(const StringRef& eventId,const StringRef& label)
{

}

void UmengAnalyzer::EndEvent(const StringRef& eventId)
{

}

void UmengAnalyzer::EndEvent(const StringRef& eventId,const StringRef& label)
{

}

void UmengAnalyzer::BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)
{

}

void UmengAnalyzer::EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)
{

}

void UmengAnalyzer::LogEventTime(const StringRef& eventId,int microseconds)
{

}

void UmengAnalyzer::LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)
{

}

void UmengAnalyzer::LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)
{

}

void UmengAnalyzer::LogPageStay(const StringRef& pageName,int seconds)
{

}

void UmengAnalyzer::BeginPageStay(const StringRef& pageName)
{

}

void UmengAnalyzer::EndPageStay(const StringRef& pageName)
{

}


#pragma endregion Event

#pragma region Location

void UmengAnalyzer::SetLocation(double latitude,double longitude)
{

}

#pragma endregion Location

#pragma region OnlineConfig

void UmengAnalyzer::SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)
{

}

void UmengAnalyzer::UpdateConfig()
{

}

HeapString UmengAnalyzer::GetConfigString(const StringRef& key)
{
	return HeapString::Empty;
}



#pragma endregion OnlineConfig

#endif
MEDUSA_END;
