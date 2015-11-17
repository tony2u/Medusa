#pragma once
#if defined(_WIN64)||defined(_WIN32)||defined(WIN32)||defined(WIN64)
#include "curl_config_win.h"
#elif __ANDROID__
#include "curl_config_android.h"
#elif __APPLE__
#include "curl_config_ios.h"
#endif

