// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#ifdef MEDUSA_ANDROID
//add socket lib
#include <android/log.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>


#include <sys/resource.h>
#include <sys/types.h>   
#include <sys/socket.h>   //Linux only
#include <sys/time.h>   //Linux only
#include <sys/stat.h>
#include <sys/uio.h>   //Linux only
#include <sys/wait.h>   //Linux only
#include <sys/un.h>   //Linux only
#include <sys/sysinfo.h>   //Linux only
#include <sys/select.h>   //Linux only
#include <netinet/in.h>   //Linux only
#include <arpa/inet.h>   //Linux only
#include <time.h>   
#include <errno.h>   
#include <fcntl.h>
#include <netdb.h>   //Linux only
#include <signal.h>   
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
#include <unistd.h>  //Linux only
#include <stdarg.h>	//Linux only
#include <ctype.h>	//Linux only
#include <dirent.h>
#include <type_traits>
#include <iomanip>
#include <unwind.h>
#include <dlfcn.h>

#include <poll.h>
#include "pthread.h"
#include "sched.h"
#include "semaphore.h"

#include "CoreLib/android/uuid/uuid.h"

#include <zlib.h>
#include<netdb.h>

#endif