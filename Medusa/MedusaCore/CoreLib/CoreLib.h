// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#include <list>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdarg>
#include <cassert>
#include <ctime>
#include <typeinfo>
#include <math.h>
#include <assert.h>

#include <stdio.h>
#include <ios>
#include <stdarg.h>
#include <sys/stat.h>   
#include <fcntl.h>   
#include <stdlib.h>  
#include <fstream>
#include <memory>
#include <stdint.h> 
#include <initializer_list>
#include <functional>
#include <atomic>
#include <utility>
#include <stdint.h>

#include <cmath>
#include <cstddef>  // for std::ptrdiff_t
#include <cstdio>
#include <algorithm>
#include <limits>
#include <stdexcept>

#include <cctype>
#include <cerrno>
#include <climits>
#include <chrono>


//curl
#ifndef HAVE_CONFIG_H
#define HAVE_CONFIG_H
#endif

#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif

#ifndef BUILDING_LIBCURL
#define BUILDING_LIBCURL
#endif


#if _SECURE_SCL
# include <iterator>
#endif

#ifdef MEDUSA_WINDOWS
#include "CoreLib/win/CoreLib_win.h"

#elif MEDUSA_IOS
#include "CoreLib/ios/CoreLib_ios.h"

#elif MEDUSA_MAC

#elif MEDUSA_ANDROID
#include "CoreLib/android/CoreLib_android.h"
#elif MEDUSA_LINUX
#include "CoreLib/linux/CoreLib_linux.h"
#else

#endif


#ifdef MEDUSA_VFP
#include "CoreLib/Common/vfp/matrix_impl.h"
#endif

#ifdef MEDUSA_NEON
#include "CoreLib/Common/neon/math_neon.h"
#include "CoreLib/Common/neon/neon_matrix_impl.h"
#endif


#ifdef MEDUSA_XML
//pre declare
namespace pugi
{
	class xml_node;
	class xml_document;
}

#endif