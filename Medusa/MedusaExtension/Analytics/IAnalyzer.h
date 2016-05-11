// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/IInitializable.h"
#include "AnalyticsTypes.h"

#include "AnalyticsCurrencyType.h"
#include "AnalyticsPaymentType.h"
#include "AnalyticsRewardType.h"

#include "Core/String/HeapString.h"

MEDUSA_BEGIN;

class IAnalyzer:public IInitializable
{
public:
	IAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy=AnalyticsReportPolicy::RealTime):mAppKey(appKey),mChannelId(channelId),mPolicy(policy){}
	virtual ~IAnalyzer(){}

	virtual void EnableLog(bool val)=0;
	virtual void EnableCrashReport(bool val)=0;
#pragma region Account
public:
	//accountId < 64
	//accountName < 64
	//1<=level <=1000
	//0<=age <=120
	//gameServerName <16
	virtual void InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level=1,int age=18,AnalyticsAccountType accountType=AnalyticsAccountType::Registered,AnalyticsAccountGender gender=AnalyticsAccountGender::Unknown)=0;
	//1<=level <=1000
	virtual void UpdateAccountLevel(int level)=0;
#pragma endregion Account


#pragma region Payment
public:
	//orderId < 64
	//itemId < 32
	virtual void RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty)=0;
	virtual void SucceedPay(const StringRef& orderId)=0;

	virtual void RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty)=0;

#pragma endregion Payment

#pragma region Reward
public:
	//reason < 32, support <=100 different types
	virtual void RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)=0;
	virtual void RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)=0;

#pragma endregion Reward

#pragma region Purchase
public:
	//itemName <=32
	virtual void Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)=0;
	virtual void Use(const StringRef& itemName,int count=1,double price=0)=0;
#pragma endregion Purchase

#pragma region Mission
public:
	//missionId <=32, count <500
	virtual void BeginMission(const StringRef& missionId)=0;
	virtual void CompeleteMission(const StringRef& missionId)=0;
	virtual void FailedMission(const StringRef& missionId,const StringRef& reason=StringRef::Empty)=0;
#pragma endregion Mission

#pragma region Event
public:
	

	virtual void LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)=0;

	virtual void LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)=0;
	virtual void LogEvent(const StringRef& eventId)=0;


	virtual void LogEvent(const StringRef& eventId,const StringRef& label)=0;
	virtual void LogEvent(const StringRef& eventId,int count)=0;
	virtual void LogEvent(const StringRef& eventId,const StringRef& label,int count)=0;


	virtual void BeginEvent(const StringRef& eventId)=0;
	virtual void EndEvent(const StringRef& eventId)=0;

	virtual void BeginEvent(const StringRef& eventId,const StringRef& label)=0;
	virtual void EndEvent(const StringRef& eventId,const StringRef& label)=0;

	
	virtual void BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)=0;
	virtual void EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)=0;


	virtual void LogEventTime(const StringRef& eventId,int microseconds)=0;
	virtual void LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)=0;
	virtual void LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)=0;


	virtual void LogPageStay(const StringRef& pageName,int seconds)=0;
	virtual void BeginPageStay(const StringRef& pageName)=0;
	virtual void EndPageStay(const StringRef& pageName)=0;
#pragma endregion Event

#pragma region Location
public:
	virtual void SetLocation(double latitude,double longitude)=0;
#pragma endregion Location

#pragma region OnlineConfig
public:

	virtual void SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)=0;
	virtual void UpdateConfig()=0;

	virtual HeapString GetConfigString(const StringRef& key)=0;
#pragma endregion OnlineConfig

protected:
	HeapString mAppKey;
	HeapString mChannelId;
	AnalyticsReportPolicy mPolicy;
};


MEDUSA_END;