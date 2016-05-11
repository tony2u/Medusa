// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaCorePreCompiled.h"
#include "FileId.h"
#include "Core/IO/Path.h"
#include "Core/IO/FileInfo.h"


MEDUSA_BEGIN;


bool FileId::operator<(const FileId& fileId) const
{
	if (Order < fileId.Order)
	{
		return true;
	}
	else if (Order == fileId.Order)
	{
		return Name < fileId.Name;
	}

	return false;
}

FileId FileId::ParseFrom(const StringRef& name)
{
	FileId result(name);
	intp dirIndex = result.Name.LastIndexOfAny(Path::DirectorySeparatorChars);
	if (dirIndex > 0)
	{
		result.Name.RemoveAt(0, dirIndex + 1);
	}

	intp index = result.Name.IndexOf('-');
	if (index >= 0)
	{
		intp endIndex = result.Name.LastIndexOf('.');
		if (endIndex >= 0)
		{
			HeapString orderString = result.Name.SubString(index + 1, endIndex - index - 1);
			result.Order = StringParser::StringTo<uint>(orderString);
			result.Name.RemoveAt(index, endIndex - index);
		}
		else
		{
			result.Name.RemoveAt(index, result.Name.Length() - index);
			result.Order = 0;
		}
	}

	return result;
}


HeapString FileId::ToString(const PublishTarget& tag /*= PublishTarget::MatchAll*/) const
{
	return ToRef().ToString(tag);
}

bool FileId::IsPath() const
{
	return Path::IsPath(Name);
}

FileType FileId::Type() const
{
	return FileInfo::ExtractType(Name);
}


const FileId FileId::Empty;

SIREN_METADATA(FileId, 6);
SIREN_FIELD_METADATA_STRUCT(0, FileId, Name, 4);
SIREN_FIELD_METADATA(1, FileId, Order, 5, 0, false);

MEDUSA_END;

