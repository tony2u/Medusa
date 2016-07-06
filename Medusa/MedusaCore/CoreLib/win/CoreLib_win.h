// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once


#ifdef MEDUSA_WINDOWS
////////////////////////////////////////////////////////////////////////// Windows
//#if 0
//#include <Windows.h>
//#else
//#define _WINSOCKAPI_
//#include <Windows.h>
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//#endif
//#pragma comment(lib,"wsock32.lib")		//add socket lib, or it'll be failed

#define _WINSOCKAPI_
#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <direct.h>
#include <process.h>
typedef int socklen_t;



#ifdef MEDUSA_VLD
#include "CoreLib/win/vld/vld.h"
#endif

#ifdef MEDUSA_MEMORY_LEAK_DETECT
#include "CoreLib/win/MemoryLeakDetector.h"
#endif


#ifdef MEDUSA_POSIX_THREADING
#include "CoreLib/win/pthread/pthread.h"
#include "CoreLib/win/pthread/sched.h"
#include "CoreLib/win/pthread/semaphore.h"
#pragma comment(lib,"pthreadVC2.lib")
#endif

//#include <threadpoolapiset.h>
//#pragma comment(lib,"Ws2_32.lib")		//have to include this or it will failed
//#pragma comment(lib,"Wldap32.lib")		//have to include this or it will failed

#endif