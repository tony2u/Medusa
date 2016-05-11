// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.

//#include "MedusaCorePreCompiled.h"
#ifdef MEDUSA_IOS

#include "Environment.h"
#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import "UIDevice+Reachability.h"


MEDUSA_BEGIN;



HeapString Environment::GetMacAddress()
{
	int					mib[6];
	size_t				len;
	char				*buf;
	unsigned char		*ptr;
	struct if_msghdr	*ifm;
	struct sockaddr_dl	*sdl;
	
	mib[0] = CTL_NET;
	mib[1] = AF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_LINK;
	mib[4] = NET_RT_IFLIST;
	
	if ((mib[5] = if_nametoindex("en0")) == 0) {
		printf("Error: if_nametoindex error\n");
		return HeapString::Empty;
	}
	
	if (sysctl(mib, 6, nullptr, &len, nullptr, 0) < 0) {
		printf("Error: sysctl, take 1\n");
		return HeapString::Empty;
	}
	
	if ((buf = (char*)malloc(len)) == nullptr) {
		printf("Could not allocate memory. error!\n");
		return HeapString::Empty;
	}
	
	if (sysctl(mib, 6, buf, &len, nullptr, 0) < 0) {
		printf("Error: sysctl, take 2");
        free(buf);
		return HeapString::Empty;
	}
	
	ifm = (struct if_msghdr *)buf;
	sdl = (struct sockaddr_dl *)(ifm + 1);
	ptr = (unsigned char *)LLADDR(sdl);
	// NSString *outstring = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
	NSString *outstring = [NSString stringWithFormat:@"%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
	free(buf);
	NSString* result= [outstring uppercaseString];
	const char* pStr=[result cStringUsingEncoding:NSUTF8StringEncoding];
	return HeapString(pStr);
}


bool Environment::IsNetworkAvailable()
{
    return true;
   //return [[UIDevice currentDevice] networkAvailable]==YES;
}

uint Environment::GetCPUCount() const
{
    size_t len;
    unsigned int ncpu;
    
    len = sizeof(ncpu);
    sysctlbyname ("hw.ncpu",&ncpu,&len,NULL,0);
    
    return ncpu;

	//return get_nprocs();
}

bool Environment::GetScreenSize(uint& outWidth, uint& outHeight)const
{
    float scale=[[UIScreen mainScreen] scale];
	auto size= [[UIScreen mainScreen] bounds].size;
	outWidth=(uint)(size.width*scale);
	outHeight=(uint)(size.height*scale);
	return true;
}

bool Environment::RequireFullScreen() const
{
	return true;
}

CPUArchitectures Environment::Architecture() const
{
#if defined(__i386__)
	return CPUArchitectures::X86;
#elif defined(__X86_64__)
	return CPUArchitectures::X64;
#elif defined(__arm__)
	#if defined(__ARM_ARCH_6__)
		return CPUArchitectures::ArmV6;
	#elif defined(__ARM_ARCH_7__)
		return CPUArchitectures::ArmV7;
	#elif defined(__ARM_ARCH_7S__)
		return CPUArchitectures::ArmV7S;
	#else
		return CPUArchitectures::ArmV7S;
	#endif
#elif defined(__arm64__)
	return CPUArchitectures::Arm64;
#else
	return CPUArchitectures::Unknow;
#endif
}

PublishDevices Environment::Device() const
{
	if([[UIScreen mainScreen] scale]>1.0)
	{
		return PublishDevices::hd;
	}
	return PublishDevices::sd;
}

PublishLanguages Environment::Language() const
{
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

	if ([currentLanguage isEqualToString:@"zh-cn"]) return PublishLanguages::zhcn;
	if ([currentLanguage isEqualToString:@"en-us"]) return PublishLanguages::enus;

	return PublishLanguages::enus;
}


MEDUSA_END;

#endif