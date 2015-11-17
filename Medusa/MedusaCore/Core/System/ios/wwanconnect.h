// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
// Direct from Apple. Thank you Apple
#pragma once
#ifdef TARGET_OS_IPHONE

#include <CoreFoundation/CoreFoundation.h>
#include <assert.h>

#define kTestHost	"www.whatismyip.com"
#define kTestPort	80		

typedef void (*ConnectClientCallBack)(void *refCon);


struct MyStreamInfoStruct{
	CFWriteStreamRef		wStreamRef;
	CFReadStreamRef			rStreamRef;
	ConnectClientCallBack	clientCB;
	void					*refCon;
	CFStreamError			error;
	Boolean					errorOccurred;
	Boolean					isConnected;
	Boolean					isStreamInitd;
	Boolean					isClientSet;
};

typedef struct MyStreamInfoStruct MyStreamInfo;
typedef struct MyStreamInfoStruct *MyStreamInfoPtr;
typedef struct __MyInfoRef *MyInfoRef;

/*
 *  StartWWAN()
 *  
 *  Discussion:
 *    This function will initiate a Wireless Wide Area Network (WWAN)
 *     connection by using the CFSocketStream API to connect with a 
 *     server system defined by kTestHost:kTestPort above.
 *     No communications are expected to happen over the CFSocketStream
 *     connection.
 *  
 *    clientCB:
 *     if the connection is opened, the callback routine, if not nullptr
 *     will be called. function defintion - see ConnectClientCallBack above
 *     
 *    refCon:
 *     if a client callback, clientCB is defined, then the refCon
 *      parameter will be the argument to the client callback
 *
 *    return:
 *     if the WWAN connection is successful, a MyInfoRef value is returned
 *     The MyInfoRef value must be passed to StopWWAN to stop the WWAN
 *     connection.
 *     A nullptr result indicates that the connection was unsuccessful
 *    
 */
extern MyInfoRef StartWWAN(ConnectClientCallBack clientCB, void *refCon);

/*
 *  StopWWAN()
 *  
 *  Discussion:
 *    This function closes the CFSocketStream which was used to establish the
 *    WWAN connection. Once the WWAN connection has been started, BSD
 *    network functions can be used to communicate across the WWAN connection.
 *    As of the writing of this sample, there is no guarantee that the use of
 *    only BSD socket API's will maintain the WWAN connection.
 *  
 *    infoRef:
 *     pass in the MyInfoRef result from the StartWWAN function.
 *     
 */

extern void StopWWAN(MyInfoRef infoRef);


#endif
