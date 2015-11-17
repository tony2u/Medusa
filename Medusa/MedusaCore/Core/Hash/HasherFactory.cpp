// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Core/Hash/HasherFactory.h"
#include "Core/Hash/CRC32C.h"
#include "Core/Hash/MD5.h"
#include "Core/Hash/SHA1.h"

MEDUSA_BEGIN;


HasherFactory::HasherFactory()
{
	Register<CRC32C>(HasherType::CRC32C);
	Register<MD5>(HasherType::MD5);
	Register<SHA1>(HasherType::SHA1);
}

MEDUSA_END;
