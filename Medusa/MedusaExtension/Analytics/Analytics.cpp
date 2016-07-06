// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "Analytics.h"

#ifdef MEDUSA_ANALYTICS_TALKINGDATA
#include "TalkingDataAnalyzer.h"
#endif

#ifdef MEDUSA_ANALYTICS_UMENG
#include "UmengAnalyzer.h"
#endif

MEDUSA_BEGIN;

bool Analytics::Initialize()
{
	for(auto analyzer:mAnalyzers)
	{
		RETURN_FALSE_IF_FALSE(analyzer->Initialize());
	}

	return true;
}

bool Analytics::Uninitialize()
{
	SAFE_DELETE_COLLECTION(mAnalyzers);
	return true;
}

void Analytics::AddAnalyzer(IAnalyzer* analyzer )
{
	mAnalyzers.Append(analyzer);
}

void Analytics::AddTalkingDataAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy/*=AnalyticsReportPolicy::RealTime*/)
{
#ifdef MEDUSA_ANALYTICS_TALKINGDATA
	IAnalyzer* analyzer=new TalkingDataAnalyzer(appKey,channelId,policy);
	AddAnalyzer(analyzer);
#endif
}

void Analytics::AddUmengAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy/*=AnalyticsReportPolicy::RealTime*/)
{
#ifdef MEDUSA_ANALYTICS_UMENG
	IAnalyzer* analyzer=new UmengAnalyzer(appKey,channelId,policy);
	AddAnalyzer(analyzer);
#endif

}

void Analytics::EnableLog(bool val)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->EnableLog(val);
	}
}


void Analytics::EnableCrashReport(bool val)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->EnableCrashReport(val);
	}
}

#pragma region Account

void Analytics::InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level/*=1*/,int age/*=18*/,AnalyticsAccountType accountType/*=AnalyticsAccountType::Registered*/,AnalyticsAccountGender gender/*=AnalyticsAccountGender::Unknown*/)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->InitAccount(gameServerName,accountId,accountName,level,age,accountType,gender);
	}
}

void Analytics::UpdateAccountLevel(int level)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->UpdateAccountLevel(level);
	}
}

#pragma endregion Account

#pragma region Payment

void Analytics::RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->RequestPay(itemId,currencyAmount,currencyType,virtualCurrencyAmount,paymentType,orderId);
	}
}

void Analytics::SucceedPay(const StringRef& orderId)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->SucceedPay(orderId);
	}
}

void Analytics::RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->RequestAndSucceedPay(itemId,itemCount,currencyAmount,currencyType,virtualCurrencyAmount,paymentType,orderId);
	}
}



#pragma endregion Payment

#pragma region Reward
void Analytics::RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->RewardCurrency(virtualCurrencyAmount,reason);
	}
}

void Analytics::RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->RewardItem(itemName,itemCount,currencyAmount,currencyType,price,reason);
	}
}

#pragma endregion Reward

#pragma region Purchase
void Analytics::Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->Purchase(itemName,count,virtualCurrencyAmount);
	}
}

void Analytics::Use(const StringRef& itemName,int count/*=1*/,double price/*=0*/)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->Use(itemName,count,price);
	}
}


#pragma endregion Purchase


#pragma region Mission

void Analytics::BeginMission(const StringRef& missionId)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->BeginMission(missionId);
	}
}

void Analytics::CompeleteMission(const StringRef& missionId)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->CompeleteMission(missionId);
	}
}

void Analytics::FailedMission(const StringRef& missionId,const StringRef& reason/*=StringRef::Empty*/)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->FailedMission(missionId,reason);
	}
}

#pragma endregion Mission

#pragma region Event

void Analytics::LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEvent(eventId,attributes);
	}
}

void Analytics::LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEvent(eventId,attributes);
	}
}

void Analytics::LogEvent(const StringRef& eventId)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEvent(eventId);
	}
}

void Analytics::LogEvent(const StringRef& eventId,const StringRef& label)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEvent(eventId,label);
	}
}

void Analytics::LogEvent(const StringRef& eventId,int count)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEvent(eventId,count);
	}
}

void Analytics::LogEvent(const StringRef& eventId,const StringRef& label,int count)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEvent(eventId,label,count);
	}
}

void Analytics::BeginEvent(const StringRef& eventId)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->BeginEvent(eventId);
	}
}

void Analytics::BeginEvent(const StringRef& eventId,const StringRef& label)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->BeginEvent(eventId,label);
	}
}

void Analytics::EndEvent(const StringRef& eventId)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->EndEvent(eventId);
	}
}

void Analytics::EndEvent(const StringRef& eventId,const StringRef& label)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->EndEvent(eventId,label);
	}
}

void Analytics::BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->BeginEventWithName(eventId,primaryKey,attributes);
	}
}

void Analytics::EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->EndEventWithName(eventId,primaryKey);
	}
}

void Analytics::LogEventTime(const StringRef& eventId,int microseconds)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEventTime(eventId,microseconds);
	}
}

void Analytics::LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEventTime(eventId,label,microseconds);
	}
}

void Analytics::LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogEventTime(eventId,attributes,microseconds);
	}
}

void Analytics::LogPageStay(const StringRef& pageName,int seconds)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->LogPageStay(pageName,seconds);
	}
}

void Analytics::BeginPageStay(const StringRef& pageName)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->BeginPageStay(pageName);
	}
}

void Analytics::EndPageStay(const StringRef& pageName)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->EndPageStay(pageName);
	}
}


#pragma endregion Event

#pragma region Location

void Analytics::SetLocation(double latitude,double longitude)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->SetLocation(latitude,longitude);
	}
}

#pragma endregion Location

#pragma region OnlineConfig

void Analytics::SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->SetOnlineConfigDelegate(handler);
	}
}

void Analytics::UpdateConfig()
{
	for (auto analyzer : mAnalyzers)
	{
		analyzer->UpdateConfig();
	}
}

HeapString Analytics::GetConfigString(const StringRef& key)
{
	return HeapString::Empty;
}



#pragma endregion OnlineConfig

List<IAnalyzer*> Analytics::mAnalyzers;
bool Analytics::mEnabled=true;
MEDUSA_END;
