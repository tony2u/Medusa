// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "TestPreCompiled.h"
#include "TestSettings.h"



TestSettings::~TestSettings()
{

}
const TestSettings& TestSettings::Instance()
{
	return *(TestSettings*)Application::Instance().Game()->BaseSettings();
}

MemoryByteData TestSettings::CoderKey() const
{
	const static byte key[] = "123456";
	return MemoryByteData::FromStatic(key,6);
}

