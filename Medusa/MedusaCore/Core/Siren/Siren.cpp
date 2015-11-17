// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "Siren.h"
#include "Core/IO/FileSystem.h"

MEDUSA_BEGIN;

namespace Siren
{
	namespace internal
	{
		MemoryByteData ReadAllData(const FileIdRef& fileId)
		{
			return FileSystem::Instance().ReadAllData(fileId);
		}

		

	}
}
MEDUSA_END;

