// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaExtensionPreCompiled.h"
#include "IAnalyzer.h"

MEDUSA_BEGIN;

class TalkingDataAnalyzer:public IAnalyzer
{
public:
	TalkingDataAnalyzer(const StringRef& appKey,const StringRef& channelId,AnalyticsReportPolicy policy=AnalyticsReportPolicy::RealTime):IAnalyzer(appKey,channelId){}
	virtual ~TalkingDataAnalyzer(){}

	virtual bool Initialize()override;
	virtual bool Uninitialize()override;
	virtual void EnableLog(bool val)override;
	virtual void EnableCrashReport(bool val)override;

#pragma region Account
public:
	//accountId < 64
	//accountName < 64
	//1<=level <=1000
	//0<=age <=120
	//gameServerName <16
	virtual void InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level=1,int age=18,AnalyticsAccountType accountType=AnalyticsAccountType::Registered,AnalyticsAccountGender gender=AnalyticsAccountGender::Unknown)override;
	//1<=level <=1000
	virtual void UpdateAccountLevel(int level)override;
#pragma endregion Account


#pragma region Payment
public:
	//orderId < 64
	//itemId < 32
	virtual void RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty)override;
	virtual void SucceedPay(const StringRef& orderId)override;

	virtual void RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId=StringRef::Empty)override;

#pragma endregion Payment

#pragma region Reward
public:
	//reason < 32, support <=100 different types
	virtual void RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)override;
	virtual void RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)override;

#pragma endregion Reward

#pragma region Purchase
public:
	//itemName <=32
	virtual void Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)override;
	virtual void Use(const StringRef& itemName,int count=1,double price=0)override;
#pragma endregion Purchase

#pragma region Mission
public:
	//missionId <=32, count <500
	virtual void BeginMission(const StringRef& missionId)override;
	virtual void CompeleteMission(const StringRef& missionId)override;
	virtual void FailedMission(const StringRef& missionId,const StringRef& reason=StringRef::Empty)override;
#pragma endregion Mission

#pragma region Event
public:
	virtual void LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)override;

	virtual void LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)override;
	virtual void LogEvent(const StringRef& eventId)override;


	virtual void LogEvent(const StringRef& eventId,const StringRef& label)override;
	virtual void LogEvent(const StringRef& eventId,int count)override;
	virtual void LogEvent(const StringRef& eventId,const StringRef& label,int count)override;


	virtual void BeginEvent(const StringRef& eventId)override;
	virtual void EndEvent(const StringRef& eventId)override;

	virtual void BeginEvent(const StringRef& eventId,const StringRef& label)override;
	virtual void EndEvent(const StringRef& eventId,const StringRef& label)override;

	virtual void BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)override;
	virtual void EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)override;


	virtual void LogEventTime(const StringRef& eventId,int microseconds)override;
	virtual void LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)override;
	virtual void LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)override;


	virtual void LogPageStay(const StringRef& pageName,int seconds)override;
	virtual void BeginPageStay(const StringRef& pageName)override;
	virtual void EndPageStay(const StringRef& pageName)override;
#pragma endregion Event

#pragma region Location
public:
	virtual void SetLocation(double latitude,double longitude)override;
#pragma endregion Location

#pragma region OnlineConfig
public:

	virtual void SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)override;
	virtual void UpdateConfig()override;

	virtual HeapString GetConfigString(const StringRef& key)override;
#pragma endregion OnlineConfig
protected:
    void* mAccount;
};


MEDUSA_END;