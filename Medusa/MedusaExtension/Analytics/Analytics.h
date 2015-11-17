// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "AnalyticsTypes.h"
#include "Core/String/StringParser.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Collection/List.h"

#include "AnalyticsCurrencyType.h"
#include "AnalyticsPaymentType.h"
#include "AnalyticsRewardType.h"

MEDUSA_BEGIN;

class Analytics
{

public:
	static bool Uninitialize();

	static bool IsEnabled() { return mEnabled; }
	static void Enable(bool val) { mEnabled = val; }

	//1. add analyzers
	static void AddAnalyzer(IAnalyzer* analyzer);
	static void AddTalkingDataAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy=AnalyticsReportPolicy::RealTime);
	static void AddUmengAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy=AnalyticsReportPolicy::RealTime);

	//2.set  options
	static void EnableLog(bool val);
	static void EnableCrashReport(bool val);

	//3.init
	static bool Initialize();


#pragma region Account
public:
	//accountId < 64
	//accountName < 64
	//1<=level <=1000
	//0<=age <=120
	//gameServerName <16
	static void InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level=1,int age=18,AnalyticsAccountType accountType=AnalyticsAccountType::Registered,AnalyticsAccountGender gender=AnalyticsAccountGender::Unknown);
	//1<=level <=1000
	static void UpdateAccountLevel(int level);
#pragma endregion Account


#pragma region Payment
public:
	//orderId < 64
	//itemId < 32
	static void RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty);
	static void SucceedPay(const StringRef& orderId);

	static void RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty);

#pragma endregion Payment

#pragma region Reward
public:
	//reason < 32, support <=100 different types
	static void RewardCurrency(double virtualCurrencyAmount,const StringRef& reason);
	static void RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason);

#pragma endregion Reward

#pragma region Purchase
public:
	//itemName <=32
	static void Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount);
	static void Use(const StringRef& itemName,int count=1,double price=0);
#pragma endregion Purchase

#pragma region Mission
public:
	//missionId <=32, count <500
	static void BeginMission(const StringRef& missionId);
	static void CompeleteMission(const StringRef& missionId);
	static void FailedMission(const StringRef& missionId,const StringRef& reason=StringRef::Empty);
#pragma endregion Mission

#pragma region Event
public:
	
	static void LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes);

	static void LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes);
	static void LogEvent(const StringRef& eventId);


	static void LogEvent(const StringRef& eventId,const StringRef& label);
	static void LogEvent(const StringRef& eventId,int count);
	static void LogEvent(const StringRef& eventId,const StringRef& label,int count);


	static void BeginEvent(const StringRef& eventId);
	static void EndEvent(const StringRef& eventId);

	static void BeginEvent(const StringRef& eventId,const StringRef& label);
	static void EndEvent(const StringRef& eventId,const StringRef& label);

	
	static void BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes);
	static void EndEventWithName(const StringRef& eventId,const StringRef& primaryKey);


	static void LogEventTime(const StringRef& eventId,int microseconds);
	static void LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds);
	static void LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds);


	static void LogPageStay(const StringRef& pageName,int seconds);
	static void BeginPageStay(const StringRef& pageName);
	static void EndPageStay(const StringRef& pageName);
#pragma endregion Event

#pragma region Location
public:
	static void SetLocation(double latitude,double longitude);
#pragma endregion Location

#pragma region OnlineConfig
public:

	static void SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler);
	static void UpdateConfig();

	static HeapString GetConfigString(const StringRef& key);
	static bool TryGetConfigInt(const StringRef& key,int& outResult)
	{
		outResult=0;
		HeapString result=GetConfigString(key);
		RETURN_FALSE_IF_EMPTY(result);
		outResult=StringParser::StringTo<int>(result);
		return true;
	}


	static bool GetConfigBool(const StringRef& key,bool& outResult)
	{
		outResult=false;
		HeapString result=GetConfigString(key);
		RETURN_FALSE_IF_EMPTY(result);
		outResult=StringParser::StringTo<bool>(result);
		return true;
	}
#pragma endregion OnlineConfig


private:
	static List<IAnalyzer*> mAnalyzers;
	static bool mEnabled;
};


MEDUSA_END;