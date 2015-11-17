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
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
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
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->EnableLog(val);
	}
}


void Analytics::EnableCrashReport(bool val)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->EnableCrashReport(val);
	}
}

#pragma region Account

void Analytics::InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level/*=1*/,int age/*=18*/,AnalyticsAccountType accountType/*=AnalyticsAccountType::Registered*/,AnalyticsAccountGender gender/*=AnalyticsAccountGender::Unknown*/)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->InitAccount(gameServerName,accountId,accountName,level,age,accountType,gender);
	}
}

void Analytics::UpdateAccountLevel(int level)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->UpdateAccountLevel(level);
	}
}

#pragma endregion Account

#pragma region Payment

void Analytics::RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->RequestPay(itemId,currencyAmount,currencyType,virtualCurrencyAmount,paymentType,orderId);
	}
}

void Analytics::SucceedPay(const StringRef& orderId)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->SucceedPay(orderId);
	}
}

void Analytics::RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->RequestAndSucceedPay(itemId,itemCount,currencyAmount,currencyType,virtualCurrencyAmount,paymentType,orderId);
	}
}



#pragma endregion Payment

#pragma region Reward
void Analytics::RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->RewardCurrency(virtualCurrencyAmount,reason);
	}
}

void Analytics::RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->RewardItem(itemName,itemCount,currencyAmount,currencyType,price,reason);
	}
}

#pragma endregion Reward

#pragma region Purchase
void Analytics::Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->Purchase(itemName,count,virtualCurrencyAmount);
	}
}

void Analytics::Use(const StringRef& itemName,int count/*=1*/,double price/*=0*/)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->Use(itemName,count,price);
	}
}


#pragma endregion Purchase


#pragma region Mission

void Analytics::BeginMission(const StringRef& missionId)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->BeginMission(missionId);
	}
}

void Analytics::CompeleteMission(const StringRef& missionId)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->CompeleteMission(missionId);
	}
}

void Analytics::FailedMission(const StringRef& missionId,const StringRef& reason/*=StringRef::Empty*/)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->FailedMission(missionId,reason);
	}
}

#pragma endregion Mission

#pragma region Event

void Analytics::LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEvent(eventId,attributes);
	}
}

void Analytics::LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEvent(eventId,attributes);
	}
}

void Analytics::LogEvent(const StringRef& eventId)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEvent(eventId);
	}
}

void Analytics::LogEvent(const StringRef& eventId,const StringRef& label)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEvent(eventId,label);
	}
}

void Analytics::LogEvent(const StringRef& eventId,int count)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEvent(eventId,count);
	}
}

void Analytics::LogEvent(const StringRef& eventId,const StringRef& label,int count)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEvent(eventId,label,count);
	}
}

void Analytics::BeginEvent(const StringRef& eventId)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->BeginEvent(eventId);
	}
}

void Analytics::BeginEvent(const StringRef& eventId,const StringRef& label)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->BeginEvent(eventId,label);
	}
}

void Analytics::EndEvent(const StringRef& eventId)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->EndEvent(eventId);
	}
}

void Analytics::EndEvent(const StringRef& eventId,const StringRef& label)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->EndEvent(eventId,label);
	}
}

void Analytics::BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->BeginEventWithName(eventId,primaryKey,attributes);
	}
}

void Analytics::EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->EndEventWithName(eventId,primaryKey);
	}
}

void Analytics::LogEventTime(const StringRef& eventId,int microseconds)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEventTime(eventId,microseconds);
	}
}

void Analytics::LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEventTime(eventId,label,microseconds);
	}
}

void Analytics::LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogEventTime(eventId,attributes,microseconds);
	}
}

void Analytics::LogPageStay(const StringRef& pageName,int seconds)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->LogPageStay(pageName,seconds);
	}
}

void Analytics::BeginPageStay(const StringRef& pageName)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->BeginPageStay(pageName);
	}
}

void Analytics::EndPageStay(const StringRef& pageName)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->EndPageStay(pageName);
	}
}


#pragma endregion Event

#pragma region Location

void Analytics::SetLocation(double latitude,double longitude)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->SetLocation(latitude,longitude);
	}
}

#pragma endregion Location

#pragma region OnlineConfig

void Analytics::SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
		analyzer->SetOnlineConfigDelegate(handler);
	}
}

void Analytics::UpdateConfig()
{
	FOR_EACH_COLLECTION(i,mAnalyzers)
	{
		IAnalyzer* analyzer=*i;
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
