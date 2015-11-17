// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Siren/SirenHeader.h"
#include "Core/IO/IFileLoadable.h"
#include "SirenProtocol.h"
#include "Siren.h"
#include "Core/IO/FileInfo.h"

MEDUSA_BEGIN;

template<typename T>
class ISirenConfig :public IFileLoadable
{
public:
	virtual bool LoadFromData(StringRef path, const MemoryByteData& data, uint format = (uint)-1)override
	{
		SirenProtocol protocol = (SirenProtocol)format;
		RETURN_FALSE_IF_FALSE(Siren::DeserializeTo(data, ((T&)*this), protocol));
		return OnLoaded();
	}
protected:
	virtual uint OnCheckFormat(StringRef path)const override
	{
		FileType fileType = FileInfo::ExtractType(path);
		switch (fileType)
		{
			case FileType::json:
				return (uint)SirenProtocol::Json;
			default:
				return (uint)SirenProtocol::Compact;
		}
	}
	virtual bool OnLoaded() { return true; }
};

MEDUSA_END;