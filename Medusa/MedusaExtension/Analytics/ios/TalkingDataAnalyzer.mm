// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "Analytics/TalkingDataAnalyzer.h"
#include "Core/Log/Log.h"
#ifdef MEDUSA_ANALYTICS

#ifdef MEDUSA_ANALYTICS_TALKINGDATA
#include "ExtensionLib/ios/TalkingData/TalkingDataGA.h"
#endif

#endif

MEDUSA_BEGIN;

bool TalkingDataAnalyzer::Initialize()
{
    NSString* appKey=[NSString stringWithUTF8String:mAppKey.c_str()];
    NSString* channelId=[NSString stringWithUTF8String:mAppKey.c_str()];
    
    [TalkingDataGA onStart:appKey withChannelId:channelId];
    
	return true;
}

bool TalkingDataAnalyzer::Uninitialize()
{
	return true;
}

void TalkingDataAnalyzer::EnableLog(bool val)
{
    if (!val) {
        [TalkingDataGA setVerboseLogDisabled];
    }
    
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
    
    NSString* accountIdStr=[NSString stringWithUTF8String:accountId.c_str()];
    NSString* accountNameStr=[NSString stringWithUTF8String:accountName.c_str()];
    NSString* gameServerStr=[NSString stringWithUTF8String:gameServerName.c_str()];
    
    TDGAAccount* account=[TDGAAccount setAccount:accountIdStr];
    [account setAccountType:(TDGAAccountType)accountType];
    [account setAccountName:accountNameStr];
    [account setLevel:level];
    [account setGender:(TDGAGender)gender];
    [account setAge:age];
    [account setGameServer:gameServerStr];
    mAccount=(__bridge void*)account;
    
}

void TalkingDataAnalyzer::UpdateAccountLevel(int level)
{
	LOG_ASSERT_INT_RANGE(level,1,1000);
    TDGAAccount* account=(__bridge TDGAAccount*)mAccount;
    [account setLevel:level];
}

#pragma endregion Account

#pragma region Payment

void TalkingDataAnalyzer::RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(orderId,64);
	LOG_ASSERT_STRING_MAX_LENGTH(itemId,32);
	LOG_ASSERT_STRING_MAX_LENGTH(paymentType.ToString(),16);
    
    NSString* orderIdStr=[NSString stringWithUTF8String:orderId.c_str()];
    NSString* itemIdStr=[NSString stringWithUTF8String:itemId.c_str()];
    NSString* currencyTypeStr=[NSString stringWithUTF8String:currencyType.ToString().c_str()];
    NSString* paymentTypeStr=[NSString stringWithUTF8String:paymentType.ToString().c_str()];
    
    [TDGAVirtualCurrency onChargeRequst:orderIdStr iapId:itemIdStr currencyAmount:currencyAmount currencyType:currencyTypeStr virtualCurrencyAmount:virtualCurrencyAmount paymentType:paymentTypeStr];
    

}

void TalkingDataAnalyzer::SucceedPay(const StringRef& orderId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(orderId,64);
    NSString* orderIdStr=[NSString stringWithUTF8String:orderId.c_str()];
    
    [TDGAVirtualCurrency onChargeSuccess:orderIdStr];
}

void TalkingDataAnalyzer::RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(orderId,64);
	LOG_ASSERT_STRING_MAX_LENGTH(itemId,32);
	LOG_ASSERT_STRING_MAX_LENGTH(paymentType.ToString(),16);
    
    NSString* orderIdStr=[NSString stringWithUTF8String:orderId.c_str()];
    NSString* itemIdStr=[NSString stringWithUTF8String:itemId.c_str()];
    NSString* currencyTypeStr=[NSString stringWithUTF8String:currencyType.ToString().c_str()];
    NSString* paymentTypeStr=[NSString stringWithUTF8String:paymentType.ToString().c_str()];
    
    [TDGAVirtualCurrency onChargeRequst:orderIdStr iapId:itemIdStr currencyAmount:currencyAmount currencyType:currencyTypeStr virtualCurrencyAmount:virtualCurrencyAmount paymentType:paymentTypeStr];
    [TDGAVirtualCurrency onChargeSuccess:orderIdStr];
}



#pragma endregion Payment

#pragma region Reward
void TalkingDataAnalyzer::RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)
{
	LOG_ASSERT_STRING_MAX_LENGTH(reason,32);
    NSString* reasonStr=[NSString stringWithUTF8String:reason.c_str()];
    [TDGAVirtualCurrency onReward:virtualCurrencyAmount reason:reasonStr];

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
    NSString* itemNameStr=[NSString stringWithUTF8String:itemName.c_str()];
    [TDGAItem onPurchase:itemNameStr itemNumber:count priceInVirtualCurrency:virtualCurrencyAmount];

}

void TalkingDataAnalyzer::Use(const StringRef& itemName,int count/*=1*/,double price/*=0*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(itemName,32);
    NSString* itemNameStr=[NSString stringWithUTF8String:itemName.c_str()];
    [TDGAItem onUse:itemNameStr itemNumber:count];
}


#pragma endregion Purchase


#pragma region Mission

void TalkingDataAnalyzer::BeginMission(const StringRef& missionId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,32);
    NSString* missionIdStr=[NSString stringWithUTF8String:missionId.c_str()];
    [TDGAMission onBegin:missionIdStr];

}

void TalkingDataAnalyzer::CompeleteMission(const StringRef& missionId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,32);
    NSString* missionIdStr=[NSString stringWithUTF8String:missionId.c_str()];
    [TDGAMission onCompleted:missionIdStr];

}

void TalkingDataAnalyzer::FailedMission(const StringRef& missionId,const StringRef& reason/*=StringRef::Empty*/)
{
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,32);
	LOG_ASSERT_STRING_MAX_LENGTH(missionId,16);
    NSString* missionIdStr=[NSString stringWithUTF8String:missionId.c_str()];
    NSString* reasonStr=[NSString stringWithUTF8String:reason.c_str()];
    [TDGAMission onFailed:missionIdStr failedCause:reasonStr];
}

#pragma endregion Mission

#pragma region Event

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	LOG_ASSERT_COLLECTION_MAX_COUNT(attributes,10);
    NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSDictionary* dict=[[NSMutableDictionary alloc] init];
    
	FOR_EACH_COLLECTION(i,attributes)
	{
		LOG_ASSERT_STRING_MAX_LENGTH(i->Key,32);
		LOG_ASSERT_STRING_MAX_LENGTH(i->Value,32);
        NSString* keyStr=[NSString stringWithUTF8String:i->Key.c_str()];
         NSString* valueStr=[NSString stringWithUTF8String:i->Value.c_str()];
        
        [dict setValue:valueStr forKey:keyStr];

	}

    [TalkingDataGA onEvent:eventIdStr eventData:dict];

}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
    LOG_ASSERT_COLLECTION_MAX_COUNT(attributes,10);
    NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSDictionary* dict=[[NSMutableDictionary alloc] init];
    
	FOR_EACH_COLLECTION(i,attributes)
	{
		LOG_ASSERT_STRING_MAX_LENGTH(i->Key,32);
        NSString* keyStr=[NSString stringWithUTF8String:i->Key.c_str()];
       
        NSNumber* val=[NSNumber numberWithInt:i->Value];
        [dict setValue:val forKey:keyStr];
	}
    
    [TalkingDataGA onEvent:eventIdStr eventData:dict];
    

}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
     NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    [TalkingDataGA onEvent:eventIdStr eventData:nil];
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	Dictionary<HeapString,HeapString> dict;
	dict.Add(HeapString("Label"),HeapString(label));
	LogEvent(eventId,dict);
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,int count)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	//NOT SUPPORTED

	Dictionary<HeapString,int> dict;
	dict.Add(HeapString("Count"),count);
	LogEvent(eventId,dict);
}

void TalkingDataAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label,int count)
{
	LOG_ASSERT_STRING_MAX_LENGTH(eventId,32);
	Dictionary<HeapString,int> dict;
	dict.Add(label,count);
	LogEvent(eventId,dict);
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
	[TalkingDataGA setLatitude:latitude longitude:longitude];
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

MEDUSA_END;
