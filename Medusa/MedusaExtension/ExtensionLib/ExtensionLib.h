// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once

#ifdef MEDUSA_WINDOWS
#include "ExtensionLib/win/ExtensionLib_win.h"

#elif MEDUSA_IOS
#include "ExtensionLib/ios/ExtensionLib_ios.h"

#elif MEDUSA_ANDROID
#include "ExtensionLib/android/ExtensionLib_android.h"

#endif


