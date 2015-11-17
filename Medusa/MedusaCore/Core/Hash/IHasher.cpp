// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "IHasher.h"

MEDUSA_BEGIN;


void IHasher::Process(const void* input, size_t length)
{
	Process((const byte*)input, length);
}


void IHasher::Process(const StringRef& str)
{
	Process((const byte*)str.c_str(), str.Length());
}
void IHasher::Process(const WStringRef& str)
{
	Process((const byte*)str.c_str(), str.Length()*sizeof(wchar_t));
}
MEDUSA_END;
