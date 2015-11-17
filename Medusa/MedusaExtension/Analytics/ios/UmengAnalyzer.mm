// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaExtensionPreCompiled.h"
#include "Analytics/UmengAnalyzer.h"
#include "Core/String/StringParser.h"
#include "Core/Log/Log.h"

#ifdef MEDUSA_ANALYTICS

#ifdef MEDUSA_ANALYTICS_UMENG
#include "ExtensionLib/ios/Umeng/MobClick.h"
#include "ExtensionLib/ios/Umeng/MobClickGameAnalytics.h"
#endif

#endif
using namespace Medusa;

@interface UmengOnlineCallbackHandler : NSObject
{
    UmengAnalyzer* Analyzer;
}
-(void)OnReady:(NSNotification*)notification;
-(id)initWithAnalyzer:(UmengAnalyzer*)analyzer;
@end

@implementation UmengOnlineCallbackHandler
-(id)initWithAnalyzer:(UmengAnalyzer*)analyzer
{
    Analyzer=analyzer;
    return self;
}
-(void)OnReady:(NSNotification*)notification
{
    AnalyticsOnlineConfigDelegate callback= Analyzer->GetOnlineConfigDelegate();
    callback();
}

@end
MEDUSA_BEGIN;



bool UmengAnalyzer::Initialize()
{
    mNotificationHost=nullptr;
    NSString* appKey=[NSString stringWithUTF8String:mAppKey.c_str()];
    NSString* channelId=[NSString stringWithUTF8String:mChannelId.c_str()];
    
    [MobClick startWithAppkey:appKey reportPolicy:(ReportPolicy)mPolicy channelId:channelId];
    
    
    //print test device ingo
    /*
    Class cls = NSClassFromString(@"UMANUtil");
    SEL deviceIDSelector = @selector(openUDIDString);
    NSString *deviceID = nil;
    if(cls && [cls respondsToSelector:deviceIDSelector]){
        deviceID = [cls performSelector:deviceIDSelector];
    }
    NSLog(@"{\"oid\": \"%@\"}", deviceID);
    */
	return true;
}

bool UmengAnalyzer::Uninitialize()
{
    if (mNotificationHost!=nullptr) {
        [[NSNotificationCenter defaultCenter] removeObserver:(__bridge UmengOnlineCallbackHandler*)mNotificationHost name:UMOnlineConfigDidFinishedNotification object:nil];
        mNotificationHost=nullptr;
        mNotificationHost=nullptr;
    }
    
	return true;
}

void UmengAnalyzer::EnableLog(bool val)
{
	[MobClick setLogEnabled:val?YES:NO];
}

void UmengAnalyzer::EnableCrashReport(bool val)
{
    [MobClick setCrashReportEnabled:val?YES:NO];
}

#pragma region Account

void UmengAnalyzer::InitAccount(const StringRef& gameServerName,const StringRef& accountId,const StringRef& accountName,int level/*=1*/,int age/*=18*/,AnalyticsAccountType accountType/*=AnalyticsAccountType::Registered*/,AnalyticsAccountGender gender/*=AnalyticsAccountGender::Unknown*/)
{
    NSString* accoutIdStr=[NSString stringWithUTF8String:accountId.c_str()];
    NSString* gameServerStr=[NSString stringWithUTF8String:gameServerName.c_str()];
	[MobClickGameAnalytics setUserID:accoutIdStr sex:(int)gender age:age platform:gameServerStr];
    UpdateAccountLevel(level);
}

void UmengAnalyzer::UpdateAccountLevel(int level)
{
    auto str=StringParser::ToString(level);
    NSString* levelStr=[NSString stringWithUTF8String:str.c_str()];
    [MobClickGameAnalytics setUserLevel:levelStr];
}

#pragma endregion Account

#pragma region Payment

void UmengAnalyzer::RequestPay(const StringRef& itemId,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
    NSString* itemStr=[NSString stringWithUTF8String:itemId.c_str()];
    [MobClickGameAnalytics pay:currencyAmount source:paymentType.ToInt() item:itemStr amount:1 price:virtualCurrencyAmount];
}

void UmengAnalyzer::SucceedPay(const StringRef& orderId)
{

}

void UmengAnalyzer::RequestAndSucceedPay(const StringRef& itemId,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double virtualCurrencyAmount,AnalyticsPaymentType paymentType,const StringRef& orderId/*=StringRef::Empty*/)
{
    NSString* itemStr=[NSString stringWithUTF8String:itemId.c_str()];
    [MobClickGameAnalytics pay:currencyAmount source:paymentType.ToInt() item:itemStr amount:itemCount price:virtualCurrencyAmount/itemCount];
}



#pragma endregion Payment

#pragma region Reward
void UmengAnalyzer::RewardCurrency(double virtualCurrencyAmount,const StringRef& reason)
{
        [MobClickGameAnalytics bonus:virtualCurrencyAmount source:AnalyticsRewardType::FromGame.ToInt()];
}

void UmengAnalyzer::RewardItem(const StringRef& itemName,int itemCount,double currencyAmount,AnalyticsCurrencyType currencyType,double price,const StringRef& reason)
{
    
    NSString* itemStr=[NSString stringWithUTF8String:itemName.c_str()];

    [MobClickGameAnalytics bonus:itemStr amount:itemCount price:price source:AnalyticsRewardType::FromGame.ToInt()];
    
}

#pragma endregion Reward

#pragma region Purchase
void UmengAnalyzer::Purchase(const StringRef& itemName,int count,double virtualCurrencyAmount)
{
      NSString* itemStr=[NSString stringWithUTF8String:itemName.c_str()];
    [MobClickGameAnalytics buy:itemStr amount:count price:virtualCurrencyAmount/count];
}

void UmengAnalyzer::Use(const StringRef& itemName,int count/*=1*/,double price/*=0*/)
{
    NSString* itemStr=[NSString stringWithUTF8String:itemName.c_str()];
    [MobClickGameAnalytics use:itemStr amount:count price:price];
}


#pragma endregion Purchase


#pragma region Mission

void UmengAnalyzer::BeginMission(const StringRef& missionId)
{
    NSString* missionIdStr=[NSString stringWithUTF8String:missionId.c_str()];
    [MobClickGameAnalytics startLevel:missionIdStr];
}

void UmengAnalyzer::CompeleteMission(const StringRef& missionId)
{
    NSString* missionIdStr=[NSString stringWithUTF8String:missionId.c_str()];
    [MobClickGameAnalytics finishLevel:missionIdStr];
}

void UmengAnalyzer::FailedMission(const StringRef& missionId,const StringRef& reason/*=StringRef::Empty*/)
{
    NSString* missionIdStr=[NSString stringWithUTF8String:missionId.c_str()];
    [MobClickGameAnalytics failLevel:missionIdStr];
}

#pragma endregion Mission

#pragma region Event

void UmengAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes)
{
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
    
    [MobClick event:eventIdStr attributes:dict];
}

void UmengAnalyzer::LogEvent(const StringRef& eventId,const Dictionary<HeapString,int>& attributes)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSDictionary* dict=[[NSMutableDictionary alloc] init];
    
	FOR_EACH_COLLECTION(i,attributes)
	{
		LOG_ASSERT_STRING_MAX_LENGTH(i->Key,32);
        NSString* keyStr=[NSString stringWithUTF8String:i->Key.c_str()];
        
        NSNumber* val=[NSNumber numberWithInt:i->Value];
        [dict setValue:val forKey:keyStr];
	}
    [MobClick event:eventIdStr attributes:dict];
}

void UmengAnalyzer::LogEvent(const StringRef& eventId)
{
    NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    [MobClick event:eventIdStr];
}

void UmengAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* labelStr=[NSString stringWithUTF8String:label.c_str()];
    [MobClick event:eventIdStr label:labelStr];
}

void UmengAnalyzer::LogEvent(const StringRef& eventId,int count)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    [MobClick event:eventIdStr acc:count];
}

void UmengAnalyzer::LogEvent(const StringRef& eventId,const StringRef& label,int count)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* labelStr=[NSString stringWithUTF8String:label.c_str()];
    [MobClick event:eventIdStr label:labelStr acc:count];
}

void UmengAnalyzer::BeginEvent(const StringRef& eventId)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    [MobClick beginEvent:eventIdStr];
}

void UmengAnalyzer::BeginEvent(const StringRef& eventId,const StringRef& label)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* labelStr=[NSString stringWithUTF8String:label.c_str()];
    [MobClick beginEvent:eventIdStr label:labelStr];
}

void UmengAnalyzer::EndEvent(const StringRef& eventId)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    [MobClick endEvent:eventIdStr];
}

void UmengAnalyzer::EndEvent(const StringRef& eventId,const StringRef& label)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* labelStr=[NSString stringWithUTF8String:label.c_str()];
    [MobClick endEvent:eventIdStr label:labelStr];
}

void UmengAnalyzer::BeginEventWithName(const StringRef& eventId,const StringRef& primaryKey,const Dictionary<HeapString,HeapString>& attributes)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* primaryKeyStr=[NSString stringWithUTF8String:primaryKey.c_str()];
    NSDictionary* dict=[[NSMutableDictionary alloc] init];
    
	FOR_EACH_COLLECTION(i,attributes)
	{
		LOG_ASSERT_STRING_MAX_LENGTH(i->Key,32);
		LOG_ASSERT_STRING_MAX_LENGTH(i->Value,32);
        NSString* keyStr=[NSString stringWithUTF8String:i->Key.c_str()];
        NSString* valueStr=[NSString stringWithUTF8String:i->Value.c_str()];
        
        [dict setValue:valueStr forKey:keyStr];
        
	}
    
    [MobClick beginEvent:eventIdStr primarykey:primaryKeyStr attributes:dict];
}

void UmengAnalyzer::EndEventWithName(const StringRef& eventId,const StringRef& primaryKey)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* primaryKeyStr=[NSString stringWithUTF8String:primaryKey.c_str()];
    [MobClick endEvent:eventIdStr primarykey:primaryKeyStr];
}

void UmengAnalyzer::LogEventTime(const StringRef& eventId,int microseconds)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    [MobClick event:eventIdStr durations:microseconds];
}

void UmengAnalyzer::LogEventTime(const StringRef& eventId,const StringRef& label,int microseconds)
{
 NSString* eventIdStr=[NSString stringWithUTF8String:eventId.c_str()];
    NSString* labelStr=[NSString stringWithUTF8String:label.c_str()];
    [MobClick event:eventIdStr label:labelStr durations:microseconds];
}

void UmengAnalyzer::LogEventTime(const StringRef& eventId,const Dictionary<HeapString,HeapString>& attributes,int microseconds)
{
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
    [MobClick event:eventIdStr attributes:dict durations:microseconds];
}

void UmengAnalyzer::LogPageStay(const StringRef& pageName,int seconds)
{
 NSString* pageStr=[NSString stringWithUTF8String:pageName.c_str()];
    [MobClick logPageView:pageStr seconds:seconds];
}

void UmengAnalyzer::BeginPageStay(const StringRef& pageName)
{
NSString* pageStr=[NSString stringWithUTF8String:pageName.c_str()];
    [MobClick beginLogPageView:pageStr];
}

void UmengAnalyzer::EndPageStay(const StringRef& pageName)
{
NSString* pageStr=[NSString stringWithUTF8String:pageName.c_str()];
    [MobClick endLogPageView:pageStr];
}


#pragma endregion Event

#pragma region Location

void UmengAnalyzer::SetLocation(double latitude,double longitude)
{
    [MobClick setLatitude:latitude longitude:longitude];
}

#pragma endregion Location

#pragma region OnlineConfig

void UmengAnalyzer::SetOnlineConfigDelegate(AnalyticsOnlineConfigDelegate handler)
{
    mDelegate=handler;
    UmengOnlineCallbackHandler* host=[[UmengOnlineCallbackHandler alloc] initWithAnalyzer:this];
    mNotificationHost=(__bridge void*)host;
    [[NSNotificationCenter defaultCenter] addObserver:host selector:@selector(OnReady:) name:UMOnlineConfigDidFinishedNotification object:nil];
}

void UmengAnalyzer::UpdateConfig()
{
    [MobClick updateOnlineConfig];
}

HeapString UmengAnalyzer::GetConfigString(const StringRef& key)
{
    NSString* keyStr=[NSString stringWithUTF8String:key.c_str()];
    NSString* result=[MobClick getConfigParams:keyStr];
    return HeapString(result.UTF8String);
}



#pragma endregion OnlineConfig


MEDUSA_END;
